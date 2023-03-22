#include <iostream>
#include "CSF/SparseMatrix"
#include "misc/matrix_creator.cpp"
#include <chrono>

template <typename T, typename T_index, int compressionLevel> void iteratorTest();

int main() {

    int numRows = 1000;
    int numCols = 1000;
    int sparsity = 20;
    uint64_t seed = 1952575394;

    Eigen::SparseMatrix<int> myMatrix_e(numRows, numCols);
    myMatrix_e.reserve(Eigen::VectorXi::Constant(numRows, numCols));
    myMatrix_e = generateMatrix<int>(numRows, numCols, sparsity, seed);
    myMatrix_e.prune(0);
    myMatrix_e.makeCompressed();

    // std::cout << myMatrix_e << std::endl;

    CSF::SparseMatrix<int> myMatrix_csf(myMatrix_e);


    // print out the byte size of the matrix
    std::cout << "size: " << myMatrix_csf.compressionSize() << std::endl;


    // writing the CSF sparse to a file
    myMatrix_csf.write("test.csf");

    // get the column size of column 8
    std::cout << "col size: " << myMatrix_csf.getColSize(8) << std::endl;


    // sum all values in the eigen matrix
    int sum_e = 0;
    for (int k = 0; k < myMatrix_e.outerSize(); ++k)
        for (Eigen::SparseMatrix<int>::InnerIterator it(myMatrix_e, k); it; ++it)
            sum_e += it.value();

    // sum all values in the CSF matrix
    int sum_csf = 0;
    for (uint32_t k = 0; k < myMatrix_csf.innerSize(); ++k)
        for (CSF::SparseMatrix<int>::InnerIterator it(myMatrix_csf, k); it; ++it) {
            // std::cout << it.value() << " " << it.index() << " " << it.col() << std::endl;
            sum_csf += it.value();
        }
    // sum_csf += it.value();

// compare the sums
    std::cout << "sum_e: " << sum_e << std::endl;
    std::cout << "sum_csf: " << sum_csf << std::endl;

    for (int i = 0; i < 10; i++) {
        iteratorTest<int, uint64_t, 2>();
        std::cout << "test " << i << " passed" << std::endl;
    }


    return 0;
}

template <typename T, typename T_index, int compressionLevel>
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

    CSF::SparseMatrix<T, T_index, compressionLevel> myMatrix_csf(myMatrix_e);

    // myMatrix_csf.write("test.csf");

    T sum_csf = 0;
    for (uint32_t k = 0; k < myMatrix_csf.outerSize(); ++k)
        for (typename CSF::SparseMatrix<T, T_index, compressionLevel>::InnerIterator it(myMatrix_csf, k); it; ++it)
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

