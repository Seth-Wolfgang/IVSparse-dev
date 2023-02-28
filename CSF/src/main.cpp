#include "include/CSF_Lib.hpp"
#include <functional>
template<typename T> bool iteratorBenchmark(int numRows, int numCols, int sparsity, uint64_t seed);
template<typename T> bool BLASBenchmark(int numRows, int numCols, int sparsity, uint64_t seed);
template<typename E> Eigen::SparseMatrix<E> generateMatrix(int numRows, int numCols, int sparsity, uint64_t seed);
template<typename T> T getSum(CSF::SparseMatrix matrix);
template<typename T> T getSum(Eigen::SparseMatrix<T> matrix);
template<typename T> void printValuesInTwo(CSF::SparseMatrix matrix, CSF::SparseMatrix matrix2);
template<typename T> void printValues(CSF::SparseMatrix matrix, CSF::SparseMatrix matrix2);
template <typename T> void testDriver(std::function<T(T, T,T, T)> lambda, int iterations);

int main() {

    //TODO replace drivers with lambdas
    testDriver<int>(iteratorBenchmark<int>, 100);
    cout << "Finished iterator Test" << endl << endl;
    testDriver<int>(BLASBenchmark<int>, 100);
    // cout << "Finished Scalar Test" << endl << endl;

    cout << "\u001b[32mEverything worked!!\u001b[0m" << endl;
    return 1;
}

template <typename T>
void testDriver(std::function<T(T, T, T, T)> lambda, int iterations) {
    int matrixSeed = rand();
    int numRows = rand() % 1000 + 1;
    int numCols = rand() % 1000 + 1;
    int sparsity = 10;

    for (int i = 0; i <= iterations; i++) {
        matrixSeed = rand();
        numRows = rand() % 100 + 1;
        numCols = rand() % 100 + 1;
        sparsity = rand() % 1 + 1;
        std::cout << "i: " << i << endl;
        // std::cout << "numRows: " << numRows << endl;
        // std::cout << "numCols: " << numCols << endl;
        // std::cout << "sparsity: " << sparsity << endl;
        // std::cout << "Matrix seed: " << matrixSeed << endl;
        if (!lambda(numRows, numCols, sparsity, matrixSeed + 1)) {

            std::cerr << "Something went wrong" << endl;
            std::cerr << "numRows: " << numRows << endl;
            std::cerr << "numCols: " << numCols << endl;
            std::cerr << "sparsity: " << sparsity << endl;
            std::cerr << "Matrix seed: " << matrixSeed << endl;
            std::cerr << "i: " << i << endl;
            exit(1);
        }
    }
}


/**
 * @brief This function is used to test the iterators. It generates a random matrix, converts it to CSF,
 *  and then iterates through the matrix using the CSF iterator, the InnerIterator
 *  iterator, and the generic CSC iterator. The total sum of all values is
 *  calculated and compared to ensure that the iterators are working properly.
 *
 * @param numRows
 * @param numCols
 * @param sparsity
 * @param seed
 * @return true
 * @return false
 */

template<typename T>
bool iteratorBenchmark(int numRows, int numCols, int sparsity, uint64_t seed) {

    // generating a large random eigen sparse
    Eigen::SparseMatrix<T> eigenMatrix(numRows, numCols);
    eigenMatrix = generateMatrix<T>(numRows, numCols, sparsity, seed);
    eigenMatrix.makeCompressed();

    // Converting to CSF
    CSF::SparseMatrix CSFMatrix = CSF::SparseMatrix(eigenMatrix);

    //Getting totals
    T CSFTotal = getSum<T>(CSFMatrix);
    T eigenTotal = getSum<T>(eigenMatrix);

    if (CSFTotal == eigenTotal) {
        return true;
    }
    else {
        cout << "CSF Total: " << CSFTotal << endl;
        cout << "Eigen Total: " << eigenTotal << endl;
        cout << "off by: " << CSFTotal - eigenTotal << endl;
        return false;
    }
}

/**
 * @brief This function is used to test the BLAS functions. It generates a random matrix, converts it to CSF
 * and then performs a matrix multiplication using the CSF matrix and the Eigen matrix. The results are compared
 *
 * @tparam T
 * @param numRows
 * @param numCols
 * @param sparsity
 * @param seed
 * @return true
 * @return false
 */

template<typename T>
bool BLASBenchmark(int numRows, int numCols, int sparsity, uint64_t seed) {

    // generating a large random eigen sparse
    Eigen::SparseMatrix<T> eigenMatrix(numRows, numCols);
    eigenMatrix = generateMatrix<T>(numRows, numCols, sparsity, seed);
    eigenMatrix.makeCompressed();

    // Converting to CSF
    CSF::SparseMatrix CSFMatrix = CSF::SparseMatrix(eigenMatrix);
    CSF::SparseMatrix CSFMatrix2 = CSF::SparseMatrix(eigenMatrix);

    // Getting totals
    T eigenTotal = getSum<T>(eigenMatrix);
    T originalTotal = getSum<T>(CSFMatrix);
    assert(originalTotal == eigenTotal);

    scalarMultiply<T>(CSFMatrix, 2);
    T scaledTotal = getSum<T>(CSFMatrix);

    // cout << "Original Matrix: " << originalTotal << "\tScaled Matrix: " << scaledTotal << endl;
    // cout << "should be: : " << 2 * originalTotal << endl;
    // cout << "Off by: " << scaledTotal - (2 * originalTotal) << endl;

    // printValuesInTwo<T>(CSFMatrix, CSFMatrix2);

    return (scaledTotal == 2 * originalTotal);
}


/****************************************************************************************************
 *                                                                                                  *
 *                                                                                                  *
 *                                        HELPER FUNCTIONS                                          *
 *                                                                                                  *
 *                                                                                                  *
 ****************************************************************************************************/

 /**
  * @brief Prints all values in CSF matrix
  *
  */
template <typename T>
void printValues(CSF::SparseMatrix matrix) {
    CSF::Iterator<T> newIter = CSF::Iterator<T>(matrix);
    T value = *newIter;

    while (newIter) {
        newIter++;
        if (*newIter != value) {
            cout << *newIter << endl;
            value = *newIter;

        }
    }
}

template <typename T>
void printValuesInTwo(CSF::SparseMatrix matrix, CSF::SparseMatrix matrix2) {
    CSF::Iterator<T> newIter = CSF::Iterator<T>(matrix);
    CSF::Iterator<T> newIter2 = CSF::Iterator<T>(matrix2);
    T value = *newIter;

    while (newIter) {
        newIter++;
        newIter2++;
        if (*newIter != value) {
            cout << *newIter2 << "\t" << *newIter << endl;
            value = *newIter;

        }
    }
}

/**
 * @brief Returns the sum of all values in the matrix
 *
 * @tparam T
 * @param matrix
 * @return uint64_t
 */

template <typename T>
T getSum(CSF::SparseMatrix matrix) {
    T CSFTotal = 0;
    CSF::Iterator<T> newIter = CSF::Iterator<T>(matrix);
    T value = *newIter;

    while (newIter) {
        newIter++;
        CSFTotal += *newIter;
        if (*newIter != value) {
            value = *newIter;
        }
    }

    return CSFTotal;
}

/**
 * @brief Returns the sum of all values in the matrix
 *
 * @tparam T
 * @param matrix
 * @return uint64_t
 */

template <typename T>
T getSum(Eigen::SparseMatrix<T> matrix) {
    T eigenTotal = 0;
    for (int i = 0; i < matrix.cols(); ++i) {
        for (typename Eigen::SparseMatrix<T>::InnerIterator it(matrix, i); it; ++it) {
            eigenTotal += it.value();
        }
    }
    return eigenTotal;
}

/**
 * @brief This function creates a random Eigens sparse matrix
 *
 * @tparam E
 * @param numRows
 * @param numCols
 * @param sparsity
 * @param seed
 * @return Eigen::SparseMatrix<E>
 */

template <typename E>
Eigen::SparseMatrix<E> generateMatrix(int numRows, int numCols, int sparsity, uint64_t seed) {
    // generate a random sparse matrix
    rng randMatrixGen = rng(seed);

    Eigen::SparseMatrix<E> eigenMatrix(numRows, numCols);
    eigenMatrix.reserve(Eigen::VectorXi::Constant(numRows * 100, numCols * 100));
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            if (randMatrixGen.draw<int>(i, j, sparsity)) {
                eigenMatrix.insert(i, j) = 100 * randMatrixGen.uniform<double>(j);
            }
        }
    }
    return eigenMatrix;
}



