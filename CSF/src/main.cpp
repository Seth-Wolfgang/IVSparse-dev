
template<typename T> void iteratorBenchmarkDriver(int iterations);
template<typename T> void BLASBenchmarkDriver(int iterations);
template<typename T> bool iteratorBenchmark(int numRows, int numCols, int sparsity, uint64_t seed);
template<typename T> bool BLASBenchmark(int numRows, int numCols, int sparsity, uint64_t seed);
template<typename E> Eigen::SparseMatrix<E> generateMatrix(int numRows, int numCols, int sparsity, uint64_t seed);
template<typename T> uint64_t getSum(CSF::SparseMatrix matrix);
template<typename T> uint64_t getSum(Eigen::SparseMatrix<T> matrix);

int main() {


    // cout << iteratorBenchmark<float>(10, 10, 1, 10) << endl;

    iteratorBenchmarkDriver<int>(1);
    BLASBenchmarkDriver<int>(100);

    cout << "\u001b[32mEverything worked!!\u001b[0m" << endl;
    return 1;
}

/**
 * @brief Abstraction for running BLASBenchmark
 * 
 * @tparam T 
 * @param iterations 
 */

template<typename T>
void BLASBenchmarkDriver(int iterations){

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
        if (!BLASBenchmark<int>(numRows, numCols, sparsity, matrixSeed)) {
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
 * @brief Abstraction for running iteratorBenchmark many times
 * 
 * @tparam T 
 * @param iterations 
 */

template <typename T>
void iteratorBenchmarkDriver(int iterations) {

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
        if (!iteratorBenchmark<int>(numRows, numCols, sparsity, matrixSeed + 1)) {

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
    T value = 0;
    T CSFTotal = 0;
    T eigenTotal = 0;
    T genericTotal = 0;

    // generating a large random eigen sparse
    Eigen::SparseMatrix<T> myMatrix(numRows, numCols);
    myMatrix = generateMatrix<T>(numRows, numCols, sparsity, seed);
    myMatrix.makeCompressed();

    // Converting to CSF
    CSF::SparseMatrix CSFMatrix = CSF::SparseMatrix(myMatrix);

    //////////////////////////////CSF Iterator//////////////////////////////

    CSF::Iterator<T> newIter = CSF::Iterator<T>(CSFMatrix);

    while (newIter) {
        newIter++;
        CSFTotal += *newIter;
        if (*newIter != value) {
            value = *newIter;
        }
    }

    //////////////////////////////CSC innerIterator////////////////////////////////
    // generating a large random eigen sparse
    // The next two blocks do essentially the same as the first but only go through the CSC matrix

    for (int i = 0; i < numCols; ++i) {
        for (typename Eigen::SparseMatrix<T>::InnerIterator it(myMatrix, i); it; ++it) {
            eigenTotal += it.value();
        }
    }

    //////////////////////////////GENERIC CSC Iterator////////////////////////////////
    GenericCOOIterator<T> iter2 = GenericCOOIterator<T>(myMatrix);
    while (iter2.operator bool()) {
        genericTotal += iter2.operator*();
        iter2.operator++();
    }

    if (genericTotal == eigenTotal && eigenTotal == CSFTotal) {
        return true;
    }
    else {
        cout << "CSF Total: " << CSFTotal << endl;
        cout << "Eigen Total: " << eigenTotal << endl;
        cout << "Generic Total: " << genericTotal << endl;
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
bool BLASBenchmark(int numRows, int numCols, int sparsity, uint64_t seed){
    
    // generating a large random eigen sparse
    Eigen::SparseMatrix<T> myMatrix(numRows, numCols);
    myMatrix = generateMatrix<T>(numRows, numCols, sparsity, seed);
    myMatrix.makeCompressed();

    // Converting to CSF
    CSF::SparseMatrix CSFMatrix = CSF::SparseMatrix(myMatrix);
    CSF::SparseMatrix CSFMatrix2= scalarMultiply<T>(CSFMatrix, 2);
    
    cout << "Scaled Matrix: " << getSum<T>(CSFMatrix2) << "\tOriginal Matrix x 2: " << getSum<T>(CSFMatrix) << endl;

    return (getSum<T>(CSFMatrix2) == (2 * getSum<T>(CSFMatrix)));
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

    Eigen::SparseMatrix<E> myMatrix(numRows, numCols);
    myMatrix.reserve(Eigen::VectorXi::Constant(numRows * 100, numCols * 100));
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
 * @brief Returns the sum of all values in the matrix
 * 
 * @tparam T 
 * @param matrix 
 * @return uint64_t 
 */

template <typename T>
uint64_t getSum(CSF::SparseMatrix matrix) {
    uint64_t CSFTotal = 0;
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
uint64_t getSum(Eigen::SparseMatrix<T> matrix) {
    uint64_t eigenTotal = 0;
    for (int i = 0; i < matrix.cols(); ++i) {
        for (typename Eigen::SparseMatrix<T>::InnerIterator it(matrix, i); it; ++it) {
            eigenTotal += it.value();
        }
    }
    return eigenTotal;
}

