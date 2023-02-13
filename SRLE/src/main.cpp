#include "include/CSF.hpp"
#include "include/CSF_Lib.hpp"
template<typename T> bool iteratorBenchmark(int numRows, int numCols, int sparsity, uint64_t seed);
template<typename E> Eigen::SparseMatrix<E> generateMatrix(int numRows, int numCols, int sparsity, uint64_t seed);


int main() {
    int matrixSeed = rand();
    int numRows = rand() % 1000 + 1;
    int numCols = rand() % 1000 + 1;

    int sparsity = 10;

    // cout << iteratorBenchmark<float>(10, 10, 1, 10) << endl;

    for (int i = 0; i <= 1000; i++) {
        matrixSeed = rand();
        numRows = rand() % 100 + 1;
        numCols = rand() % 100 + 1;
        sparsity = rand() % 1 + 1;
        std::cout << "i: " << i << endl;
        std::cout << "numRows: " << numRows << endl;
        std::cout << "numCols: " << numCols << endl;
        std::cout << "sparsity: " << sparsity << endl;
        std::cout << "Matrix seed: " << matrixSeed << endl;
        if(!iteratorBenchmark<float>(numRows, numCols, sparsity, matrixSeed + 1)) {

            std::cerr << "Something went wrong" << endl;
            std::cerr << "numRows: " << numRows << endl;
            std::cerr << "numCols: " << numCols << endl;
            std::cerr << "sparsity: " << sparsity << endl;
            std::cerr << "Matrix seed: " << matrixSeed << endl;
            std::cerr << "i: " << i << endl;
            return 0;
        }
    }
    cout << "\u001b[32mEverything worked!!\u001b[0m" << endl;
    return 1;
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
    GenericCSCIterator<T> iter2 = GenericCSCIterator<T>(myMatrix);
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