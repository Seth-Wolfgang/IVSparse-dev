#include "../IVSparse/SparseMatrix"
// #include "../misc/matrix_creator.cpp"
#include <limits>

class rng
{
private:
    uint64_t state;

public:
    rng(uint64_t state) : state(state) {}

    void advance_state()
    {
        state ^= state << 19;
        state ^= state >> 7;
        state ^= state << 36;
    }

    uint64_t operator*() const
    {
        return state;
    }

    uint64_t rand()
    {
        uint64_t x = state ^ (state << 38);
        x ^= x >> 13;
        x ^= x << 23;

        return x;
    }

    uint64_t rand(uint64_t i)
    {
        // advance i
        i ^= i << 19;
        i ^= i >> 7;
        i ^= i << 36;

        // add i to state
        uint64_t x = state + i;

        // advance state
        x ^= x << 38;
        x ^= x >> 13;
        x ^= x << 23;

        return x;
    }

    uint64_t rand(uint64_t i, uint64_t j)
    {
        uint64_t x = rand(i);

        // advance j
        j ^= j >> 7;
        j ^= j << 23;
        j ^= j >> 8;

        // add j to state
        x += j;

        // advance state
        x ^= x >> 7;
        x ^= x << 53;
        x ^= x >> 4;

        return x;
    }

    template <typename T>
    T sample(T max_value)
    {
        return rand() % max_value;
    }

    template <typename T>
    T sample(uint64_t i, T max_value)
    {
        return rand(i) % max_value;
    }

    template <typename T>
    T sample(uint64_t i, uint64_t j, T max_value)
    {
        return rand(i, j) % max_value;
    }

    template <typename T>
    bool draw(T probability)
    {
        return sample(probability) == 0;
    }

    template <typename T>
    bool draw(uint64_t i, T probability)
    {
        return sample(i, probability) == 0;
    }

    template <typename T>
    bool draw(uint64_t i, uint64_t j, T probability)
    {
        sample(i, j, probability);
        return sample(i, j, probability) == 0;
    }

    template <typename T>
    double uniform()
    {
        T x = (T)rand() / UINT64_MAX;
        return x - std::floor(x);
    }

    template <typename T>
    double uniform(uint64_t i)
    {
        T x = (T)rand(i) / UINT64_MAX;
        return x - std::floor(x);
    }

    template <typename T>
    double uniform(uint64_t i, uint64_t j)
    {
        T x = (T)rand(i, j) / UINT64_MAX;
        return x - std::floor(x);
    }
};

/**
 * @brief Genearates a random sparse matrix using Eigen
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
Eigen::SparseMatrix<T> generateEigenMatrix(int numRows, int numCols, int sparsity, uint64_t seed)
{
    // generate a random sparse matrix
    rng randMatrixGen = rng(seed);

    Eigen::SparseMatrix<T> myMatrix(numRows, numCols);
    myMatrix.reserve(Eigen::VectorXi::Constant(numCols, numRows));

    for (int i = 0; i < numRows; i++)
    {
        for (int j = 0; j < numCols; j++)
        {
            if (randMatrixGen.draw<int>(i, j, sparsity))
            {
                myMatrix.insert(i, j) = rand() % 100 + 1;
            }
        }
    }

    myMatrix.makeCompressed();
    return myMatrix;
}

/**
 * @brief Generates a random sparse matrix using Eigen, and converts it to IVSparse
 *
 * @tparam T
 * @tparam indexType
 * @tparam compressionLevel
 * @param numRows
 * @param numCols
 * @param sparsity
 * @param seed
 * @return IVSparse::SparseMatrix<T, indexType, compressionLevel>
 */

template <typename T, typename indexType, int compressionLevel>
IVSparse::SparseMatrix<T, indexType, compressionLevel> getCSFMatrix(int numRows, int numCols, int sparsity, int seed)
{

    // Generating a random sparse matrix using Eigen, because we know it works
    Eigen::SparseMatrix<T> eigenMatrix(numRows, numCols);
    generateEigenMatrix<T>(eigenMatrix, sparsity, seed);
    eigenMatrix.makeCompressed();

    // Converting to IVSparse
    return IVSparse::SparseMatrix<T, indexType, compressionLevel>(eigenMatrix);
}

/**
 * @brief Returns the sum of all values in the matrix
 *
 * @tparam T
 * @param matrix
 * @return uint64_t
 */

template <typename T, typename indexType, int compressionLevel>
T getSumCSF(IVSparse::SparseMatrix<T, indexType, compressionLevel> matrix)
{
    T CSFTotal = 0;

    for (indexType k = 0; k < matrix.outerSize(); ++k)
    {
        for (typename IVSparse::SparseMatrix<T, indexType, compressionLevel>::InnerIterator it(matrix, k); it; ++it)
        {
            CSFTotal += it.value();
            // std::cout << it.value() << " " << it.index() << " " << it.col() << std::endl;
            // std::cout << CSFTotal << std::endl;
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
T getSum(Eigen::SparseMatrix<T> matrix)
{
    T eigenTotal = 0;
    for (int i = 0; i < matrix.cols(); ++i)
    {
        for (typename Eigen::SparseMatrix<T>::InnerIterator it(matrix, i); it; ++it)
        {
            // std::cout << it.value() << " " << it.index() << " " << it.col() << std::endl;
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
IVSparse::SparseMatrix<T, indexType, compressionLevel> generateVector(int numRows, int value)
{
    // generating a large random eigen sparse
    Eigen::SparseMatrix<T> eigenMatrix(numRows, 1);

    // generate an eigen matrix consisting of one row filled with value
    Eigen::SparseMatrix<T> eigenVector(numRows, 1);
    eigenVector.reserve(Eigen::VectorXi::Constant(numRows, 1));

    // filling the vector with the value
    for (int i = 0; i < numRows; i++)
    {
        eigenVector.insert(i, 0) = value;
    }

    eigenVector.makeCompressed();

    // Converting to IVSparse
    IVSparse::SparseMatrix<T, indexType, compressionLevel> CSFVector(eigenVector);
    return CSFVector;
}

/**
 * @brief Generates a vector given an array
 *
 * @param array array of values to be used in the vector
 * @param numRows number of rows in the vector
 * @return IVSparse::SparseMatrix<T, T, 3>
 */
template <typename T, typename indexType, int compressionLevel>
IVSparse::SparseMatrix<T, T, 3> generateVector(int numRows, T *array)
{
    // generating a large random eigen sparse
    Eigen::SparseMatrix<T> eigenMatrix(numRows, 1);

    // generate an eigen matrix consisting of one row filled with value
    Eigen::SparseMatrix<T> eigenVector(numRows, 1);
    eigenVector.reserve(Eigen::VectorXi::Constant(numRows, 1));

    // filling the vector with the value
    for (int i = 0; i < numRows; i++)
    {
        eigenVector.insert(i, 0) = array[i];
    }

    eigenVector.makeCompressed();

    // Converting to IVSparse
    IVSparse::SparseMatrix<T, indexType, compressionLevel> CSFVector(eigenVector);
    return CSFVector;
}

/**
 * @brief Returns a large number based on the type of the template
 *        For larger types, a sufficiently large number is returned.
 *        i.e. uint32_t and uint64_t return 50,000
 *
 * @return T
 */

template <typename T>
T getLargeNumber()
{
    T max = std::numeric_limits<T>::max();
    if constexpr (sizeof(T) >= 4)
    {
        return 1000;
    }
    else
    {
        return 100;
    }
}
