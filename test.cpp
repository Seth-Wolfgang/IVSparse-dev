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

    // make a row major eigen matrix
    Eigen::SparseMatrix<int, Eigen::RowMajor> myMatrix_e_row(numRows, numCols);
    myMatrix_e_row.reserve(Eigen::VectorXi::Constant(numRows, numCols));
    myMatrix_e_row = generateMatrix<int>(numRows, numCols, sparsity, seed);
    myMatrix_e_row.prune(0);
    myMatrix_e_row.makeCompressed();

    // std::cout << myMatrix_e << std::endl;

    CSF::SparseMatrix<int> myMatrix_csf(myMatrix_e);

    // convert the matrix back to eigen
    //Eigen::SparseMatrix<int> myMatrix_e2 = myMatrix_csf.toEigen();

    std::cout << myMatrix_e2 << std::endl;

    CSF::SparseMatrix<int, uint32_t, 3, false> myMatrix_csf_row(myMatrix_e_row);

    // write the matrix to a file
    myMatrix_csf_row.write("test2.csf");

    // std::cout << myMatrix_e_row << std::endl;

    // print out the byte size of the matrix
    std::cout << "size: " << myMatrix_csf.compressionSize() << std::endl;


    // writing the CSF sparse to a file
    myMatrix_csf.write("test.csf");

    // get the column size of column 8
    std::cout << "col size: " << myMatrix_csf.getVecSize(8) << std::endl;


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

