#include "CSF/SparseMatrix"
#include "misc/matrix_creator.cpp"
#include <functional>

template<typename T> bool iteratorBenchmark(int numRows, int numCols, int sparsity, uint64_t seed, int compressionLevel);
template<typename T> bool ScalarMultiplicationBench(int numRows, int numCols, int sparsity, uint64_t seed, int compressionLevel);
template<typename T> Eigen::SparseMatrix<T> generateMatrix(int numRows, int numCols, int sparsity, uint64_t seed);
template<typename T, typename indexType, int compressionLevel> T getSum(CSF::SparseMatrix<T, indexType, compressionLevel> matrix);
template<typename T> T getSum(Eigen::SparseMatrix<T> matrix);
template<typename T, typename indexType, int compressionLevel> void printValues(CSF::SparseMatrix<T, indexType, compressionLevel> matrix);
template<typename T, typename indexType, int compressionLevel> void printValuesInTwo(CSF::SparseMatrix<T, indexType, compressionLevel> matrix, CSF::SparseMatrix<T, indexType, compressionLevel> matrix2);
template<typename T> void testDriver(std::function<T(T, T, T, T, T)> lambda, int iterations, int compressionLevel);

int main() {

    testDriver<int>(iteratorBenchmark<int>, 100, 3);
    std::cout << "Finished iterator Test" << std::endl << std::endl;
    testDriver<int>(ScalarMultiplicationBench<int>, 100, 3);
    std::cout << "Finished Scalar Test" << std::endl << std::endl;

    std::cout << "\u001b[32mEverything worked!!\u001b[0m" << std::endl;
    return 1;
}

template <typename T>
void testDriver(std::function<T(T, T, T, T, T)> lambda, int iterations, int compressionLevel) {
    int matrixSeed = rand();
    int numRows = rand() % 1000 + 1;
    int numCols = rand() % 1000 + 1;
    int sparsity = 10;

    for (int i = 0; i <= iterations; i++) {
        matrixSeed = rand();
        numRows = rand() % 100 + 1;
        numCols = rand() % 100 + 1;
        sparsity = rand() % 1 + 1;
        std::cout << "i: " << i << std::endl;

        if (!lambda(numRows, numCols, sparsity, matrixSeed + 1, 3)) {

            std::cerr << "Something went wrong" << std::endl;
            std::cerr << "numRows: " << numRows << std::endl;
            std::cerr << "numCols: " << numCols << std::endl;
            std::cerr << "sparsity: " << sparsity << std::endl;
            std::cerr << "Matrix seed: " << matrixSeed << std::endl;
            std::cerr << "i: " << i << std::endl;
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
bool iteratorBenchmark(int numRows, int numCols, int sparsity, uint64_t seed, int compressionLevel) {

    // generating a large random eigen sparse
    Eigen::SparseMatrix<T> eigenMatrix(numRows, numCols);
    eigenMatrix = generateMatrix<T>(numRows, numCols, sparsity, seed);
    eigenMatrix.makeCompressed();

    // Converting to CSF
    CSF::SparseMatrix<T,T,3> CSFMatrix(eigenMatrix);

    //Getting totals
    T CSFTotal = getSum<T,T, 3>(CSFMatrix);
    T eigenTotal = getSum<T>(eigenMatrix);

    if (CSFTotal == eigenTotal) {
        return true;
    }
    else {
        std::cout << "CSF Total: " << CSFTotal << std::endl;
        std::cout << "Eigen Total: " << eigenTotal << std::endl;
        std::cout << "off by: " << CSFTotal - eigenTotal << std::endl;
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
bool ScalarMultiplicationBench(int numRows, int numCols, int sparsity, uint64_t seed, int compressionLevel) {

    // generating a large random eigen sparse
    Eigen::SparseMatrix<T> eigenMatrix(numRows, numCols);
    eigenMatrix = generateMatrix<T>(numRows, numCols, sparsity, seed);
    eigenMatrix.makeCompressed();

    // Converting to CSF
    CSF::SparseMatrix<T,T,3> CSFMatrix(eigenMatrix);
    CSF::SparseMatrix<T,T,3> CSFMatrix2(eigenMatrix);

    // Getting totals
    T eigenTotal = getSum<T>(eigenMatrix);
    T originalTotal = getSum<T>(CSFMatrix);
    assert(originalTotal == eigenTotal);

    CSF::scalarMultiply<T, T, 3>(CSFMatrix, 2);
    T scaledTotal = getSum<T>(CSFMatrix);

    std::cout << "Original Matrix: " << originalTotal << "\tScaled Matrix: " << scaledTotal << std::endl;
    std::cout << "should be: : " << 2 * originalTotal << std::endl;
    std::cout << "Off by: " << scaledTotal - (2 * originalTotal) << std::endl;

    printValuesInTwo<T, T, 3>(CSFMatrix, CSFMatrix2);
    return (scaledTotal == 2 * originalTotal);

//     return true;
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
template <typename T, typename indexType, int compressionLevel>
void printValues(CSF::SparseMatrix<T, indexType, compressionLevel> matrix) {
    CSF::Iterator<T, T, compressionLevel> newIter(matrix);
    T value = *newIter;

    while (newIter) {
        newIter++;
        if (*newIter != value) {
            std::cout << *newIter << std::endl;
            value = *newIter;
        }
    }
}


template<typename T, typename indexType, int compressionLevel> 
void printValuesInTwo(CSF::SparseMatrix<T, indexType, compressionLevel> matrix, CSF::SparseMatrix<T, indexType, compressionLevel> matrix2){
    CSF::Iterator<T, indexType, compressionLevel> newIter(matrix);
    CSF::Iterator<T, indexType, compressionLevel> newIter2(matrix2);
    T value = *newIter;

    while (newIter) {
        newIter++;
        newIter2++;
        if (*newIter != value) {
            std::cout << *newIter2 << "\t" << *newIter << std::endl;
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

template <typename T, typename indexType, int compressionLevel>
T getSum(CSF::SparseMatrix<T, indexType, compressionLevel> matrix) {
    T CSFTotal = 0;
    CSF::Iterator<T, T, compressionLevel> newIter = CSF::Iterator<T, T, compressionLevel>(matrix);
    T value = *newIter;
    // std::cout << newIter.getColumnAddress(0) << std::endl;
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

template <typename T>
Eigen::SparseMatrix<T> generateMatrix(int numRows, int numCols, int sparsity, uint64_t seed) {
    // generate a random sparse matrix
    rng randMatrixGen = rng(seed);

    Eigen::SparseMatrix<T> eigenMatrix(numRows, numCols);
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



