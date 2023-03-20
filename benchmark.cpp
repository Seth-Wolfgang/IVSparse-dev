#include "CSF/SparseMatrix"
#include "misc/matrix_creator.cpp"
#include <functional>
#include <chronos>

#define COMPRESSION_LEVEL 2
#define VAL_TYPE uint64_t
#define INDEX_TYPE uint64_t


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

template <typename T, typename indexType, int compressionLevel>
void vectorBenchmark(int rows, int sparsity){
    //Create Eigen Matrix
    Eigen::SparseMatrix<T> eigenMatrix = createEigenMatrix<T>(rows, sparsity);

    //Create CSF Matrix
    CSF::SparseMatrix<T, indexType, compressionLevel> csfMatrix(eigenMatrix);


}