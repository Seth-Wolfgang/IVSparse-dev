#include <iostream>
#include "CSF/SparseMatrix"
#include "misc/matrix_creator.cpp"
#include <chrono>

template <typename T, typename indexT, int compressionLevel> void iteratorTest();
void getMat(Eigen::SparseMatrix<int>& myMatrix_e);

int main() {


    Eigen::SparseMatrix<int> myMatrix_e(10, 10);

    getMat(myMatrix_e);

    // std::cout << myMatrix_e << std::endl;

    Eigen::SparseMatrix<int, Eigen::RowMajor> myMatrix_e_row(myMatrix_e);

    std::cout << myMatrix_e_row << std::endl;


    CSF::SparseMatrix<int, uint32_t, 3> myMatrix_csf(myMatrix_e);

    // myMatrix_csf.write("test.csf");

    std::cout << std::endl;

    CSF::SparseMatrix<int, uint32_t, 3, false> myMatrix_csf_row(myMatrix_e_row);

    // myMatrix_csf_row.write("test_row.csf");

    // create an empty sparse matrix
    Eigen::SparseMatrix<int> myMatrix_e2(10, 10);

    // loop through myMatrix_csf and add the values to myMatrix_e2
    for (uint32_t k = 0; k < myMatrix_csf.outerSize(); ++k)
        for (typename CSF::SparseMatrix<int, uint32_t, 3>::InnerIterator it(myMatrix_csf, k); it; ++it)
            myMatrix_e2.coeffRef(it.row(), it.col()) += it.value();


    // create an empty sparse matrix
    Eigen::SparseMatrix<int, Eigen::RowMajor> myMatrix_e2_row(10, 10);

    // loop through myMatrix_csf_row and add the values to myMatrix_e2_row
    for (uint32_t k = 0; k < myMatrix_csf_row.outerSize(); ++k)
        for (typename CSF::SparseMatrix<int, uint32_t, 3, false>::InnerIterator it(myMatrix_csf_row, k); it; ++it)
            myMatrix_e2_row.coeffRef(it.row(), it.col()) += it.value();


    std::cout << "FROM CSF" << std::endl;
    std::cout << myMatrix_e2_row << std::endl;

    #pragma omp parallel for num_threads(15)
    for (int i = 0; i < 1000000; i++) {
        iteratorTest<float, uint64_t, 2>();
        std::cout << "Test " << i << " passed" << std::endl;
    }
    return 0;
}

template <typename T, typename indexT, int compressionLevel>
void iteratorTest() {

    int numRows = rand() % 100 + 10;
    int numCols = rand() % 100 + 10;
    int sparsity = rand() % 1 + 1;
    uint64_t seed = rand();

    // Eigen::SparseMatrix<T> eigenTemp(numRows, numCols);
    // eigenTemp.reserve(Eigen::VectorXi::Constant(numRows, numCols));

    // for (int i = 0; i < numRows; i++) {
    //     for(int j = 0; j < numCols; j++) {
    //         eigenTemp.insert(i, j) = 2;
    //     }
    // }

    // CSF::SparseMatrix<T, indexT, compressionLevel> tempMatrix(eigenTemp);
    // typename CSF::SparseMatrix<T, indexT, compressionLevel> myVec(tempMatrix, 0);

    Eigen::SparseMatrix<T> myMatrix_e(numRows, numCols);
    myMatrix_e.reserve(Eigen::VectorXi::Constant(numCols, numRows));
    myMatrix_e = generateMatrix<T>(numRows, numCols, sparsity, seed);
    myMatrix_e.makeCompressed();

    // std::cout << myMatrix_e << std::endl;

    CSF::SparseMatrix<T, indexT, compressionLevel> myMatrix_csf(myMatrix_e);


    // myMatrix_csf.write("test.csf");
    myMatrix_csf * 2;

    myMatrix_e = myMatrix_e * 2;


    T sum_e = 0;
    for (int k = 0; k < myMatrix_e.outerSize(); ++k)
        for (typename Eigen::SparseMatrix<T>::InnerIterator it(myMatrix_e, k); it; ++it) {
            sum_e += it.value();
        }

    // std::cout << "sum_e: " << sum_e << std::endl;

    T sum_csf = 0;
    for (uint32_t k = 0; k < myMatrix_csf.outerSize(); ++k)
        for (typename CSF::SparseMatrix<T, indexT, compressionLevel>::InnerIterator it(myMatrix_csf, k); it; ++it)
            sum_csf += it.value();


    // std::cout << "sum_csf: " << sum_csf << " sum_e: " << sum_e << std::endl;

    if (sum_csf - sum_e > 1 || sum_csf == 0) {
        std::cout << "Rows: " << numRows << " Cols: " << numCols << " Sparsity: " << sparsity << " Seed: " << seed << std::endl;
        // if (sum_csf - sum_e * 2 > 1) [[unlikely]] {
        std::cout << "sum_csf: " << sum_csf << " sum_e: " << sum_e << std::endl;
        // std::cout << sum_csf - sum_e * 2 << std::endl;
        assert(sum_csf == sum_e);
    }
}


void getMat(Eigen::SparseMatrix<int>& myMatrix_e) {
    // declare an eigen sparse matrix of both types

    // col 0
    myMatrix_e.insert(0, 0) = 1;
    myMatrix_e.insert(2, 0) = 2;
    myMatrix_e.insert(3, 0) = 3;
    myMatrix_e.insert(5, 0) = 1;
    myMatrix_e.insert(6, 0) = 3;
    myMatrix_e.insert(7, 0) = 8;

    // col 1
    myMatrix_e.insert(3, 1) = 1;
    myMatrix_e.insert(4, 1) = 3;
    myMatrix_e.insert(5, 1) = 8;
    myMatrix_e.insert(6, 1) = 7;
    myMatrix_e.insert(8, 1) = 1;
    myMatrix_e.insert(9, 1) = 2;

    // col 2
    myMatrix_e.insert(0, 2) = 2;
    myMatrix_e.insert(2, 2) = 2;
    myMatrix_e.insert(5, 2) = 1;
    myMatrix_e.insert(7, 2) = 3;
    myMatrix_e.insert(9, 2) = 1;

    // col 3

    // col 4
    myMatrix_e.insert(0, 4) = 1;
    myMatrix_e.insert(3, 4) = 1;
    myMatrix_e.insert(4, 4) = 3;
    myMatrix_e.insert(6, 4) = 2;
    myMatrix_e.insert(7, 4) = 1;

    // col 5
    myMatrix_e.insert(0, 5) = 8;
    myMatrix_e.insert(2, 5) = 1;
    myMatrix_e.insert(3, 5) = 4;
    myMatrix_e.insert(5, 5) = 3;
    myMatrix_e.insert(7, 5) = 1;
    myMatrix_e.insert(8, 5) = 2;

    // col 6
    myMatrix_e.insert(3, 6) = 6;
    myMatrix_e.insert(5, 6) = 1;
    myMatrix_e.insert(7, 6) = 3;

    // col 7
    myMatrix_e.insert(2, 7) = 3;
    myMatrix_e.insert(4, 7) = 4;
    myMatrix_e.insert(5, 7) = 1;
    myMatrix_e.insert(8, 7) = 2;
    myMatrix_e.insert(9, 7) = 3;

    // col 8
    myMatrix_e.insert(0, 8) = 2;
    myMatrix_e.insert(2, 8) = 1;
    myMatrix_e.insert(3, 8) = 2;
    myMatrix_e.insert(5, 8) = 3;
    myMatrix_e.insert(7, 8) = 3;
    myMatrix_e.insert(9, 8) = 1;

    // col 9
    myMatrix_e.insert(3, 9) = 2;
    myMatrix_e.insert(4, 9) = 4;
    myMatrix_e.insert(7, 9) = 1;
    myMatrix_e.insert(8, 9) = 1;

    myMatrix_e.makeCompressed();

}

