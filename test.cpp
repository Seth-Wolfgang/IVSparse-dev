#include <iostream>
#include "CSF/SparseMatrix"
#include "misc/matrix_creator.cpp"
#include <chrono>

template <typename T, typename indexT, int compressionLevel> void iteratorTest();
void getMat(Eigen::SparseMatrix<int>& myMatrix_e);

int main() {

    // * Row Major Testing * //
    Eigen::SparseMatrix<int> myMatrix_e(10, 10);

    getMat(myMatrix_e);

    Eigen::SparseMatrix<int, Eigen::RowMajor> myMatrix_er(myMatrix_e);

    std::cout << myMatrix_e << std::endl;



    // * Transpose Testing * //

    // // create a CSF matrix from the eigen matrix
    // CSF::SparseMatrix<int, uint64_t, 3> myMatrix_csf(myMatrix_e);

    // // transpose the CSF matrix
    // CSF::SparseMatrix<int, uint64_t, 3> myMatrix_csf_t = myMatrix_csf.transpose();

    // // loop through all values in the CSF matrix and append them to an empty eigen matrix
    // Eigen::SparseMatrix<int> myMatrix_e_t(10, 10);
    // for (uint32_t k = 0; k < myMatrix_csf_t.outerSize(); ++k)
    //     for (typename CSF::SparseMatrix<int, uint64_t, 3>::InnerIterator it(myMatrix_csf_t, k); it; ++it)
    //         myMatrix_e_t.insert(it.row(), it.col()) = it.value();

    // // print the eigen matrix
    // std::cout << myMatrix_e_t << std::endl;



    // * Multiplication Testing * //

    // create a csf matrix
    CSF::SparseMatrix<int, uint64_t, 3> myMatrix_csf(myMatrix_e);

    // multiply the csf matrix by itself
    CSF::SparseMatrix<int, uint64_t, 3> myMatrix_csf2 = myMatrix_csf * myMatrix_csf;

    // turn the csf matrix into an eigen matrix
    Eigen::SparseMatrix<int> myMatrix_e2(10, 10);
    myMatrix_e2 = myMatrix_csf2.toEigen();

    std::cout << myMatrix_e2 << std::endl;

    // * CSF Iterator Testing * //
    // #pragma omp parallel for num_threads(15)
    // for (int i = 0; i < 1000000; i++) {
    //     iteratorTest<int, uint64_t, 3>();
    //     std::cout << "Test " << i << " passed" << std::endl;
    // }
    return 0;
}

template <typename T, typename indexT, int compressionLevel>
void iteratorTest() {

    int numRows = 100;//rand() % 1000 + 10;
    int numCols = 100;//rand() % 1000 + 10;
    int sparsity = rand() % 1 + 1;
    uint64_t seed = rand();

    Eigen::SparseMatrix<T> myMatrix_e(numRows, numCols);
    myMatrix_e.reserve(Eigen::VectorXi::Constant(numCols, numRows));
    myMatrix_e = generateMatrix<T>(numRows, numCols, sparsity, seed);
    myMatrix_e.makeCompressed();

    // std::cout << myMatrix_e << std::endl;

    CSF::SparseMatrix<T, indexT, compressionLevel> myMatrix_csf(myMatrix_e);
    CSF::SparseMatrix<T, indexT, compressionLevel> myMatrix_csf2(myMatrix_e);


    // myMatrix_csf.write("test.csf");

    myMatrix_e = myMatrix_e * myMatrix_e;

    myMatrix_csf = myMatrix_csf * myMatrix_csf2;


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

