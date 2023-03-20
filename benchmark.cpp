#include "CSF/SparseMatrix"
#include "misc/matrix_creator.cpp"
#include <functional>
#include <chrono>
#include <iostream>
#include <vector>
#include <numeric>


#define SEED 1
#define COMPRESSION_LEVEL 3
#define VAL_TYPE int
#define INDEX_TYPE uint64_t

// Test Driver
template <typename T> void testDriver(int numRows, int numCols, int sparsity, int iterations);

// Generative Functions
template <typename T> Eigen::SparseMatrix<T> generateMatrix(Eigen::SparseMatrix<T>& eigenMatrix, int sparsity);
template <typename T> Eigen::SparseMatrix<T> generateMatrix(Eigen::SparseMatrix<T>& eigenMatrix, int sparsity, int value);

// Benchmark Functions
template <typename T> void vectorBenchmark(int rows, int cols, int sparsity);


/************************************************************
 *    TODO *                                                *
 *         CSF VS EIGEN                                     *
 *         - MATRIX COLUMN SUMS                             *
 *         - SCALAR MULTIPLICATION                          *
 *         - VECTOR MULTIPLICATION                          *
 *         - CONSTRUCTION FROM FILE                         *
 *                                                          *
 *         CSF<A> VS CSF<B>                                 *
 *         NEW CSF CONSTRUCTOR VS OLD CSF CONSTRUCTOR       *
 *         NEW ITERATOR VS OLD ITERATOR                     *
 *                                                          *
 *                                                          *
 *                                                          *
 *         CURRENT FOCUS                                    *
 *            - SMART METHOD FOR CONDUCTING TESTS           *
 *            - ANALYSIS FUNCTIONS                          *
 *            - WRITING RESULTS TO FILE (JSON?)             *
 *                                                          *
 *                                                          *
 ***********************************************************/



int main() {

    //Commented out areas for specific matrices
    // InnerIteratorBenchmark<VAL_TYPE>(100, 100, 50, 1288115545);
    // ScalarMultiplicationBench<VAL_TYPE>(100, 100, 50, 1296273897);


    testDriver<VAL_TYPE>(100000, 1, 1, 10);

    std::cout << "\u001b[32mDone!\u001b[0m" << std::endl;
    return 1;
}

template <typename T>
void testDriver(int numRows, int numCols, int sparsity, int iterations) {
    float average;
    std::vector<uint64_t> times = std::vector<uint64_t>();

    for (int i = 0; i < iterations; i++) {
        vectorBenchmark<T>(numRows, 1, sparsity);

    }

    average = std::reduce(times.begin(), times.end()) / times.size();
    std::cout << "Average Time: " << average << std::endl;
}



template <typename T>
void vectorBenchmark(int rows, int cols, int sparsity) {
    std::chrono::time_point<std::chrono::system_clock> start, end;

    //Create Eigen Matrix
    start = std::chrono::system_clock::now();
    Eigen::SparseMatrix<T> eigenMatrix(rows, 1);
    eigenMatrix = generateMatrix<T>(eigenMatrix, sparsity, 1);
    eigenMatrix.makeCompressed();
    end = std::chrono::system_clock::now();

    uint64_t eigenConstructTime = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    std::cout << "Eigen Matrix Filled With 1's (1xN) Generation Time: " << eigenConstructTime << "ns" << std::endl;

    //Create CSF Matrix
    start = std::chrono::system_clock::now();
    CSF::SparseMatrix<T, INDEX_TYPE, COMPRESSION_LEVEL> csfMatrix(eigenMatrix);
    end = std::chrono::system_clock::now();

    uint64_t csfConstructTime = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    std::cout << "CSF Matrix (1xN) Generation time (Eigen Constructor): " << csfConstructTime << "ns" << std::endl;

    start = std::chrono::system_clock::now();
    T eigenTotal = 0;
    for (typename Eigen::SparseMatrix<T>::InnerIterator it(eigenMatrix, 0); it; ++it) {
        eigenTotal += it.value();
    }
    end = std::chrono::system_clock::now();

    uint64_t eigenSumTime = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    std::cout << "Eigen Matrix (1xN) Column Sum Time: " << eigenSumTime << "ns" << std::endl;

    start = std::chrono::system_clock::now();
    T csfTotal = 0;
    for (typename CSF::SparseMatrix<T, INDEX_TYPE, COMPRESSION_LEVEL>::InnerIterator it(csfMatrix, 0); it; it++) {
        csfTotal += *it;
    }
    end = std::chrono::system_clock::now();

    uint64_t csfSumTime = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    std::cout << "CSF Matrix (1xN) Column Sum Time: " << csfSumTime << "ns" << std::endl;

    assert(eigenTotal == csfTotal);
}







/**
 * @brief Fills a matrix with random values at a specified sparsity
 *
 */

template <typename T>
Eigen::SparseMatrix<T> generateMatrix(Eigen::SparseMatrix<T>& eigenMatrix, int sparsity) {
    // generate a random sparse matrix
    rng randMatrixGen = rng(SEED);
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

/**
 * @brief Fills matrix with a specified value. Addition option for sparsity is inclduded
 *
 */
template <typename T>
Eigen::SparseMatrix<T> generateMatrix(Eigen::SparseMatrix<T>& eigenMatrix, int sparsity, int value) {
    // generate a random sparse matrix
    rng randMatrixGen = rng(SEED);
    int numRows = eigenMatrix.rows();
    int numCols = eigenMatrix.cols();

    eigenMatrix.reserve(Eigen::VectorXi::Constant(numRows, numCols * numRows));
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            if (randMatrixGen.draw<int>(i, j, sparsity)) {
                eigenMatrix.insert(i, j) = value;
            }
        }
    }
    return eigenMatrix;
}