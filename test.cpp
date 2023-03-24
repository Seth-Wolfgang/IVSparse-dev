#include <iostream>
#include "CSF/SparseMatrix"
#include "misc/matrix_creator.cpp"
#include <chrono>

template <typename T, typename indexT, int compressionLevel> void iteratorTest();

int main() {

    int numRows = 50;
    int numCols = 50;
    int sparsity = 4;
    uint64_t seed = 1952575394;

    Eigen::SparseMatrix<int> myMatrix_e(numRows, numCols);
    myMatrix_e.reserve(Eigen::VectorXi::Constant(numRows, numCols));
    myMatrix_e = generateMatrix<int>(numRows, numCols, sparsity, seed);
    myMatrix_e.prune(0);
    myMatrix_e.makeCompressed();

    // convert myMatrix_e to row major
    Eigen::SparseMatrix<int, Eigen::RowMajor> myMatrix_erow = myMatrix_e.transpose();

    // make a row major eigen matrix
    Eigen::SparseMatrix<int, Eigen::RowMajor> myMatrix_e_row(numRows, numCols);
    myMatrix_e_row.reserve(Eigen::VectorXi::Constant(numRows, numCols));
    myMatrix_e_row = generateMatrix<int>(numRows, numCols, sparsity, seed);
    myMatrix_e_row.prune(0);
    myMatrix_e_row.makeCompressed();

    std::cout << myMatrix_e_row << std::endl;

    CSF::SparseMatrix<int> myMatrix_csf(myMatrix_e);

    CSF::SparseMatrix<int, uint32_t, 3, false> myMatrix_csf_row(myMatrix_e_row);

    // perform triplet batch insertion on the CSF matrix
    std::vector<Eigen::Triplet<int>> tripletList;
    tripletList.reserve(myMatrix_e.nonZeros());

    // loop through myMatrix_csf_row
    for (uint32_t k = 0; k < myMatrix_csf_row.outerSize(); ++k) {
        for (CSF::SparseMatrix<int, uint32_t, 3, false>::InnerIterator it(myMatrix_csf_row, k); it; ++it) {
            tripletList.push_back(Eigen::Triplet<int>(it.getIndex(), it.outerDim(), it.value()));
        }
    }

    // create a new Eigen matrix from the triplet list
    Eigen::SparseMatrix<int, Eigen::RowMajor> myMatrix_e_row2(numRows, numCols);
    myMatrix_e_row2.setFromTriplets(tripletList.begin(), tripletList.end());

    std::cout << myMatrix_e_row2 << std::endl;


    //std::cout << myMatrix_e << std::endl;
    //std::cout << myMatrix_erow << std::endl;







    // sum all values in the eigen matrix
    int sum_e = 0;
    for (int k = 0; k < myMatrix_e.outerSize(); ++k)
        for (Eigen::SparseMatrix<int>::InnerIterator it(myMatrix_e, k); it; ++it)
            sum_e += it.value();

    // sum all values in the CSF matrix
    int sum_csf = 0;
    for (uint32_t k = 0; k < myMatrix_csf.outerSize(); ++k) {
        for (CSF::SparseMatrix<int>::InnerIterator it(myMatrix_csf, k); it; ++it) {
            sum_csf += it.value();
        }
    }

    // compare the sums
    std::cout << "sum_e: " << sum_e << std::endl;
    std::cout << "sum_csf: " << sum_csf << std::endl;

    // for (int i = 0; i < 10; i++) {
    //     iteratorTest<int, uint64_t, 2>();
    //     std::cout << "test " << i << " passed" << std::endl;
    // }


    return 0;
}

template <typename T, typename indexT, int compressionLevel>
void iteratorTest() {

    int numRows = rand() % 1000 + 10;
    int numCols = rand() % 1000 + 10;
    int sparsity = rand() % 100 + 1;
    uint64_t seed = rand();

    Eigen::SparseMatrix<T> myMatrix_e(numRows, numCols);
    myMatrix_e.reserve(Eigen::VectorXi::Constant(numCols, numRows));
    myMatrix_e = generateMatrix<T>(numRows, numCols, sparsity, seed);
    // myMatrix_e.prune(0);
    // myMatrix_e.makeCompressed();

    // std::cout << myMatrix_e << std::endl;

    CSF::SparseMatrix<T, indexT, compressionLevel> myMatrix_csf(myMatrix_e);

    // myMatrix_csf.write("test.csf");

    T sum_csf = 0;
    for (uint32_t k = 0; k < myMatrix_csf.outerSize(); ++k)
        for (typename CSF::SparseMatrix<T, indexT, compressionLevel>::InnerIterator it(myMatrix_csf, k); it; ++it)
            sum_csf += it.value();

    T sum_e = 0;
    for (int k = 0; k < myMatrix_e.outerSize(); ++k)
        for (typename Eigen::SparseMatrix<T>::InnerIterator it(myMatrix_e, k); it; ++it) {
            sum_e += it.value();

        }
    if (sum_csf - sum_e > 1) [[unlikely]] {
        std::cout << "sum_csf: " << sum_csf << " sum_e: " << sum_e << std::endl;
        std::cout << sum_csf - sum_e << std::endl;
        assert(sum_csf == sum_e);
    }
}

