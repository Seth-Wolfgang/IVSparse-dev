#include "../CSF/SparseMatrix"
#include "../misc/matrix_creator.cpp"


/**
 * @brief Genearates a random sparse matrix using Eigen
 *
 *
 *
 * @tparam T
 * @param numRows
 * @param numCols
 * @param sparsity
 * @param seed
 * @return
 */

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

/**
 * @brief Generates a random sparse matrix using Eigen, and converts it to CSF
 *
 * @tparam T
 * @tparam indexType
 * @tparam compressionLevel
 * @param numRows
 * @param numCols
 * @param sparsity
 * @param seed
 * @return CSF::SparseMatrix<T, indexType, compressionLevel>
 */

template<typename T, typename indexType, int compressionLevel>
CSF::SparseMatrix<T, indexType, compressionLevel> getCSFMatrix(int numRows, int numCols, int sparsity, int seed) {

    //Generating a random sparse matrix using Eigen, because we know it works
    Eigen::SparseMatrix<T> eigenMatrix(numRows, numCols);
    eigenMatrix = generateEigenMatrix<T>(numRows, numCols, sparsity, seed);
    eigenMatrix.makeCompressed();

    // Converting to CSF
    return CSF::SparseMatrix<T, indexType, compressionLevel>(eigenMatrix);
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
    typename CSF::SparseMatrix<T, indexType, compressionLevel>::Iterator newIter(matrix);
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
 * @brief Generates a vector consisting of one row filled with value
 *
 *
 * @tparam T data type of vector elements
 * @param numRows The number of rows in the vector
 * @param value The value in all elements of the matrix
 * @return
 */

template <typename T, typename indexType, int compressionLevel>
CSF::SparseMatrix<T, indexType, compressionLevel> generateVector(int numRows, int value) {
    // generating a large random eigen sparse
    Eigen::SparseMatrix<T> eigenMatrix(numRows, 1);

    //generate an eigen matrix consisting of one row filled with value
    Eigen::SparseMatrix<T> eigenVector(numRows, 1);
    eigenVector.reserve(Eigen::VectorXi::Constant(numRows, 1));

    //filling the vector with the value
    for (int i = 0; i < numRows; i++) {
        eigenVector.insert(i, 0) = value;
    }

    eigenVector.makeCompressed();

    // Converting to CSF
    CSF::SparseMatrix<T, indexType, compressionLevel> CSFVector(eigenVector);
    return CSFVector;
}

/**
 * @brief Generates a vector given an array
 *
 * @param array array of values to be used in the vector
 * @param numRows number of rows in the vector
 * @return CSF::SparseMatrix<T, T, 3>
 */
template <typename T, typename indexType, int compressionLevel>
CSF::SparseMatrix<T, T, 3> generateVector(int numRows, T* array) {
    // generating a large random eigen sparse
    Eigen::SparseMatrix<T> eigenMatrix(numRows, 1);

    //generate an eigen matrix consisting of one row filled with value
    Eigen::SparseMatrix<T> eigenVector(numRows, 1);
    eigenVector.reserve(Eigen::VectorXi::Constant(numRows, 1));

    //filling the vector with the value
    for (int i = 0; i < numRows; i++) {
        eigenVector.insert(i, 0) = array[i];
    }

    eigenVector.makeCompressed();

    // Converting to CSF
    CSF::SparseMatrix<T, indexType, compressionLevel> CSFVector(eigenVector);
    return CSFVector;
}