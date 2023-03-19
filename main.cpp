#include "CSF/SparseMatrix"
#include "misc/matrix_creator.cpp"
#include <functional>

#define COMPRESSION_LEVEL 2
#define VAL_TYPE uint64_t
#define INDEX_TYPE uint64_t

// Main testing functions
template<typename T> bool vectorMultiplicationBench(int numRows, int numCols, int sparsity, uint64_t seed);
template<typename T> bool InnerIteratorBenchmark(int numRows, int numCols, int sparsity, uint64_t seed);
template<typename T> bool ScalarMultiplicationBench(int numRows, int numCols, int sparsity, uint64_t seed);

//Generative functions
template <typename T> Eigen::SparseMatrix<T> generateMatrix(Eigen::SparseMatrix<T>& eigenMatrix, int sparsity, uint64_t seed);
template <typename T> CSF::SparseMatrix<VAL_TYPE, INDEX_TYPE, COMPRESSION_LEVEL> generateVector(int numCols, int value);

//Printing Functions
template<typename T, typename indexType, int compressionLevel> void printValues(CSF::SparseMatrix<T, indexType, compressionLevel> matrix);
template<typename T, typename indexType, int compressionLevel> void printValuesInTwo(CSF::SparseMatrix<T, indexType, compressionLevel> matrix, CSF::SparseMatrix<T, indexType, compressionLevel> matrix2);
template<typename T, typename indexType, int compressionLevel> void printIndices(CSF::SparseMatrix<T, indexType, compressionLevel> matrix);

//Checker functions
template<typename T, typename indexType, int compressionLevel> T getSum(CSF::SparseMatrix<T, indexType, compressionLevel> matrix);
template<typename T> T getSum(Eigen::SparseMatrix<T> matrix);

//Test Driver
template<typename T> void testDriver(std::function<T(T, T, T, T)> lambda, int iterations);



int main() {

    //Commented out areas for specific matrices
    // InnerIteratorBenchmark<VAL_TYPE>(100, 100, 50, 1288115545);
    // ScalarMultiplicationBench<VAL_TYPE>(100, 100, 50, 1296273897);

    testDriver<VAL_TYPE>(InnerIteratorBenchmark<VAL_TYPE>, 10000);
    std::cout << "Finished InnerIterator Test" << std::endl << std::endl;
    testDriver<VAL_TYPE>(ScalarMultiplicationBench<VAL_TYPE>, 10000);
    std::cout << "Finished Scalar Test" << std::endl << std::endl;
    testDriver<VAL_TYPE>(vectorMultiplicationBench<VAL_TYPE>, 10000);
    std::cout << "Finished Vector/Matrix Multiplication Test" << std::endl << std::endl;

    std::cout << "\u001b[32mEverything Runs!!\u001b[0m" << std::endl;
    return 1;
}

template <typename T>
void testDriver(std::function<T(T, T, T, T)> lambda, int iterations) {
    int64_t matrixSeed;
    int64_t numRows;
    int64_t numCols;
    int64_t sparsity;
    int64_t fails = 0;

    for (int i = 0; i <= iterations; i++) {
        matrixSeed = rand();
        numRows = rand() % 100 + 1;
        numCols = rand() % 100 + 1;
        sparsity = rand() % 1 + 1;
        // std::cout << "i: " << i << std::endl;
        // std::cout << "numRows: " << numRows << std::endl;
        // std::cout << "numCols: " << numCols << std::endl;
        // std::cout << "sparsity: " << sparsity << std::endl;
        // std::cout << "Matrix seed: " << matrixSeed << std::endl;


        if (!lambda(numRows, numCols, sparsity, matrixSeed)) {

            std::cerr << "Something went wrong" << std::endl;
            std::cerr << "numRows: " << numRows << std::endl;
            std::cerr << "numCols: " << numCols << std::endl;
            std::cerr << "sparsity: " << sparsity << std::endl;
            std::cerr << "Matrix seed: " << matrixSeed << std::endl;
            std::cerr << "i: " << i << std::endl;
            fails++;
            std::cout << "\u001b[31mFAIL\u001b[0m" << std::endl;
            // exit(1);
        }
    }
    std::cout << "\u001b[31mNumber of fails: " << fails << "\u001b[0m" << std::endl;
}


/**
 * @brief This function is used to test the InnerIterators. It generates a random matrix, converts it to CSF,
 *  and then iterates through the matrix using the CSF InnerIterator, the InnerIterator
 *  InnerIterator, and the generic CSC InnerIterator. The total sum of all values is
 *  calculated and compared to ensure that the InnerIterators are working properly.
 *
 * @param numRows
 * @param numCols
 * @param sparsity
 * @param seed
 * @return true
 * @return false
 */

template<typename T>
bool InnerIteratorBenchmark(int numRows, int numCols, int sparsity, uint64_t seed) {
    // generating a large random eigen sparse
    Eigen::SparseMatrix<VAL_TYPE> eigenMatrix(numRows, numCols);
    eigenMatrix = generateMatrix<VAL_TYPE>(eigenMatrix, sparsity, seed);
    eigenMatrix.makeCompressed();

    // Check if the matrix is empty
    while (getSum<VAL_TYPE>(eigenMatrix) == 0) {
        seed = rand();
        generateMatrix<VAL_TYPE>(eigenMatrix, sparsity, seed);
        eigenMatrix.makeCompressed();
        // std::cout << "Matrix is empty, regenerating" << std::endl;
        // std::cout << "new seed: " << seed << std::endl;

    }

    // std::cout << eigenMatrix << std::endl;


    // Converting to CSF
    CSF::SparseMatrix<VAL_TYPE, INDEX_TYPE, COMPRESSION_LEVEL> CSFMatrix(eigenMatrix);

    // std::cout << eigenMatrix << std::endl;
    // CSFMatrix.write("matrix.bin");

    //Getting totals
    T CSFTotal = getSum<VAL_TYPE, INDEX_TYPE, COMPRESSION_LEVEL>(CSFMatrix);
    T eigenTotal = getSum<VAL_TYPE>(eigenMatrix);


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
bool ScalarMultiplicationBench(int numRows, int numCols, int sparsity, uint64_t seed) {

    // // generating a large random eigen sparse
    Eigen::SparseMatrix<VAL_TYPE> eigenMatrix(numRows, numCols);
    eigenMatrix = generateMatrix<VAL_TYPE>(eigenMatrix, sparsity, seed);
    eigenMatrix.makeCompressed();
    // Converting to CSF

    // Check if the matrix is empty
    while (getSum<VAL_TYPE>(eigenMatrix) == 0) {
        seed = rand();
        generateMatrix<VAL_TYPE>(eigenMatrix, sparsity, seed);
        eigenMatrix.makeCompressed();
        // std::cout << "Matrix is empty, regenerating" << std::endl;
        // std::cout << "new seed: " << seed << std::endl;

    }
    // std::cout << eigenMatrix << std::endl;

    // Converting to CSF
    CSF::SparseMatrix<VAL_TYPE, INDEX_TYPE, COMPRESSION_LEVEL> CSFMatrix(eigenMatrix);


    // Getting totals
    T eigenTotal = getSum<VAL_TYPE>(eigenMatrix);
    T originalTotal = getSum<VAL_TYPE>(CSFMatrix);
    assert(originalTotal == eigenTotal);

    // Scaling the matrix
    CSFMatrix * 2;
    T scaledTotal = getSum<VAL_TYPE>(CSFMatrix);

    if (scaledTotal == 2 * originalTotal) {
        return true;
    }
    else {
        std::cout << "scaledTotal Total: " << scaledTotal << std::endl;
        std::cout << "Eigen Total: " << eigenTotal << std::endl;
        std::cout << "off by: " << scaledTotal - eigenTotal << std::endl;
        return false;
    }
}

template<typename T>
bool vectorMultiplicationBench(int numRows, int numCols, int sparsity, uint64_t seed) {
    int value = 2;
    //Generate the test matrix
    Eigen::SparseMatrix<VAL_TYPE> eigenMatrix(numRows, numCols);
    eigenMatrix = generateMatrix<VAL_TYPE>(eigenMatrix, sparsity, seed);
    eigenMatrix.makeCompressed();

    // Converting to CSF
    CSF::SparseMatrix<VAL_TYPE, INDEX_TYPE, COMPRESSION_LEVEL> CSFMatrix(eigenMatrix);
    CSF::SparseMatrix<VAL_TYPE, INDEX_TYPE, COMPRESSION_LEVEL> CSFVector(generateVector<VAL_TYPE>(numCols, value));

    // Check if the matrix is empty
    while (getSum<VAL_TYPE>(eigenMatrix) == 0) {
        seed = rand();
        generateMatrix<VAL_TYPE>(eigenMatrix, sparsity, seed);
        eigenMatrix.makeCompressed();
        // std::cout << "Matrix is empty, regenerating" << std::endl;
        // std::cout << "new seed: " << seed << std::endl;

    }

    // std::cout << eigenMatrix << std::endl;

    // CSFVector.write("vector.bin");
    // CSFMatrix.write("matrix.bin");

    // Getting totals
    // T eigenTotal = getSum<VAL_TYPE>(eigenMatrix);
    T originalTotal = getSum<VAL_TYPE>(CSFMatrix);
    // assert(originalTotal == eigenTotal);

    CSFMatrix * CSFVector;
    T scaledTotal = getSum<VAL_TYPE>(CSFMatrix);


    if (scaledTotal == 2 * originalTotal) {
        return true;
    }
    else {
        std::cout << "Original Matrix: " << originalTotal << "\tScaled Matrix: " << scaledTotal << std::endl;
        std::cout << "Off by: " << scaledTotal - (2 * originalTotal) << std::endl;
        return false;
    }


}


/****************************************************************************************************
 *                                                                                                  *
 *                                                                                                  *
 *                                        HELPER FUNCTIONS                                          *
 *                                                                                                  *
 *                                                                                                  *
 ****************************************************************************************************/

 /**
  * @brief This function is used to generate a dense CSF vector
  *
  * @tparam T
  * @param numRows
  * @param value
  * @return CSF::SparseMatrix<T, T, 3>
  */

  //Doesn't work???
template <typename T>
CSF::SparseMatrix<VAL_TYPE, INDEX_TYPE, COMPRESSION_LEVEL> generateVector(int numRows, int value) {
    // generating a large random eigen sparse
    Eigen::SparseMatrix<VAL_TYPE> eigenMatrix(numRows, 1);

    //generate an eigen matrix consisting of one row filled with value
    Eigen::SparseMatrix<VAL_TYPE> eigenVector(numRows, 1);
    eigenVector.reserve(Eigen::VectorXi::Constant(numRows, 1));

    //filling the vector with the value
    for (int i = 0; i < numRows; i++) {
        eigenVector.insert(i, 0) = value;
    }

    eigenVector.makeCompressed();

    // Converting to CSF
    CSF::SparseMatrix<VAL_TYPE, INDEX_TYPE, COMPRESSION_LEVEL> CSFVector(eigenVector);
    return CSFVector;
}

/**
 * @brief Prints all values in CSF matrix
 *
 */
template <typename T, typename indexType, int compressionLevel>
void printValues(CSF::SparseMatrix<T, indexType, compressionLevel> matrix) {
    typename CSF::SparseMatrix<T, T, compressionLevel>::InnerIterator newIter(matrix);
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
void printValuesInTwo(CSF::SparseMatrix<T, indexType, compressionLevel> matrix, CSF::SparseMatrix<T, indexType, compressionLevel> matrix2) {
    typename CSF::SparseMatrix<T, indexType, compressionLevel>::InnerIterator newIter(matrix);
    typename CSF::SparseMatrix<T, indexType, compressionLevel>::InnerIterator newIter2(matrix2);
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
 * @brief Prints all indices in CSF matrix
 *
 *
 * @tparam T
 * @tparam indexType
 * @tparam compressionLevel
 * @param matrix
 */

template<typename T, typename indexType, int compressionLevel>
void printIndices(CSF::SparseMatrix<T, indexType, compressionLevel> matrix) {
    typename CSF::SparseMatrix<T, uint64_t, COMPRESSION_LEVEL>::InnerIterator newIter(matrix);
    T value = *newIter;
    std::cout << "Value: " << value << std::endl;
    while (newIter) {
        newIter++;
        if (*newIter != value) {
            value = *newIter;
            std::cout << "Value: " << value << std::endl;
        }
        std::cout << "\t: " << newIter.getIndex() << std::endl;
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

    for (uint32_t i = 0; i < matrix.cols(); i++) {
        for (typename CSF::SparseMatrix<T, indexType, COMPRESSION_LEVEL>::InnerIterator it(matrix, i); it; it++) {
            CSFTotal += *it;
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
Eigen::SparseMatrix<T> generateMatrix(Eigen::SparseMatrix<T>& eigenMatrix, int sparsity, uint64_t seed) {
    // generate a random sparse matrix
    rng randMatrixGen = rng(seed);
    int numRows = eigenMatrix.rows();
    int numCols = eigenMatrix.cols();

    eigenMatrix.reserve(Eigen::VectorXi::Constant(numRows * 100, numCols * 100));
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            if (randMatrixGen.draw<int>(i, j, sparsity)) {
                eigenMatrix.insert(i, j) = ceil(10 * randMatrixGen.uniform<double>(j));
            }
        }
    }
    return eigenMatrix;
}



   
