#include "../src/include/CSF.hpp"

template <typename T>
Eigen::SparseMatrix<T> generateEigenMatrix(int numRows, int numCols, int sparsity, uint64_t seed) {
    // generate a random sparse matrix
    rng randMatrixGen = rng(seed);

    Eigen::SparseMatrix<T> myMatrix(numRows, numCols);
    myMatrix.reserve(Eigen::VectorXi::Constant(numRows * numRows, numCols * numCols));
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            if (randMatrixGen.draw<int>(i, j, sparsity)) {
                myMatrix.insert(i, j) = 100 * randMatrixGen.uniform<double>(j);
            }
        }
    }
    return myMatrix;
}

template<typename T>
CSF::SparseMatrix getCSFMatrix(int numRows, int numCols, int sparsity, int seed) {

    //Generating a random sparse matrix using Eigen, because we know it works
    Eigen::SparseMatrix<T> eigenMatrix(numRows, numCols); 
    eigenMatrix = generateEigenMatrix<T>(numRows, numCols, sparsity, seed);
    eigenMatrix.makeCompressed();

    // Converting to CSF
    return CSF::SparseMatrix(eigenMatrix);
}

template<typename T>
CSF::SparseMatrix getCSFMatrix(Eigen::SparseMatrix<T> myMatrix) {
    return CSF::SparseMatrix(myMatrix);
}

template <typename T>
uint64_t getEigenTotal(Eigen::SparseMatrix<T> matrix) {
    uint64_t sum = 0;
    for (int i = 0; i < matrix.cols(); ++i) {
        for (typename Eigen::SparseMatrix<T>::InnerIterator it(matrix, i); it; ++it) {
            sum += it.value();
        }
    }
    return sum;
}

/**
 * @brief Get the Sum of all values in the CSF matrix
 * 
 * @param matrix 
 * @return uint64_t 
 */

template<typename T>
uint64_t getSum(CSF::SparseMatrix matrix) {
    uint64_t sum = 0;
    CSF::Iterator<T> iter = CSF::Iterator<T>(matrix);
    while (iter) {
        iter++;
        sum += *iter;
    }
    return sum;
}

template<typename T>
void getSumNoReturn(CSF::SparseMatrix matrix) {
    uint64_t sum = 0;
    CSF::Iterator<T> iter = CSF::Iterator<T>(matrix);
    while (iter) {
        iter++;
        sum += *iter;
    }
}

