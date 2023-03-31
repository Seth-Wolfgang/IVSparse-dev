/**
 * @file benchmark.cpp
 * @author Seth Wolfgang
 * @brief Automated benchmarking for CSF and Eigen using matrix market files
 * @version 0.1
 * @date 2023-03-19
 *
 * @copyright Copyright (c) 2023
 *
 * Matrix market exmaple code used
 * Source: https://math.nist.gov/MatrixMarket/mmio/c/example_read.c
 */

#define NUM_ITERATIONS 100


#include "lib/benchmarkFunctions.h"

int main(int argc, char** argv) {
    if (argc == 1) {
        argv[1] = (char*)malloc(sizeof(char) * 100);
        argv[1] = "testMatrix.mtx";
        argv[2] = "1";
        argc = 3;
    }


    // Checks to make sure the correct number of arguments are passed
    if (argc < 3) {
        fprintf(stderr, "Usage: %s currentFile\n", argv[0]);
        exit(1);
    }

    // Data vectors
    std::vector<Eigen::Triplet<VALUE_TYPE>> eigenTriplet;
    std::vector<uint64_t> data(15, 0);
    std::vector<double> matrixData;


    // Records the matrix ID
    matrixData.push_back(std::stoi(argv[2]));

    // Read in the matrix market file
    readFile<VALUE_TYPE>(eigenTriplet, matrixData, argv[1]);
    std::cout << "Matrix Data\tID:" << matrixData[0] << ",  Rows: " << matrixData[1] << ", Cols: " << matrixData[2] << ", Nonzeros: " << matrixData[3] << std::endl;

    // Class to calculate the maxes and averages of the benchmarking data
    // and print the data to a csv

    // Create the Eigen matrix
    eigenTriplet.reserve(matrixData[3]);
    for (uint32_t i = 0; i < matrixData[1]; i++) {
        for (uint32_t j = 0; j < matrixData[2]; j++) {
            eigenTriplet.push_back(Eigen::Triplet<VALUE_TYPE>(i, j, 1));
        }
    }
    Eigen::SparseMatrix<VALUE_TYPE> eigen(matrixData[1], matrixData[2]);
    eigen.reserve(matrixData[3]);
    eigen.setFromTriplets(eigenTriplet.begin(), eigenTriplet.end());
    eigen.makeCompressed();

    // Calculate matrix entropy
    matrixData.push_back(calculateEntropy(eigen));
    BenchAnalysis bench = BenchAnalysis(matrixData);

    // Create the CSF matrices
    // CSF::SparseMatrix<VALUE_TYPE, INDEX_TYPE, 1> csf(eigen);
    CSF::SparseMatrix<VALUE_TYPE, INDEX_TYPE, 2> csf2(eigen);
    CSF::SparseMatrix<VALUE_TYPE, INDEX_TYPE, 3> csf3(eigen);

    // Random array to select a random benchmark
    const int myList[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
    int tempList[NUM_OF_BENCHMARKS];


    int currentlySelected = -1;
    int randNum = rand() % NUM_OF_BENCHMARKS;
    int listSize = NUM_OF_BENCHMARKS;

    // Runs each benchmark 100 times
    for (int i = 0; i < NUM_ITERATIONS; i++) {
        mempcpy(&tempList, myList, sizeof(myList));
        listSize = NUM_OF_BENCHMARKS;

        while (listSize > 0) {
            currentlySelected = -1;

            // Helps to select numbers in a random order - very poorly optimized, but somewhat efficient
            while (currentlySelected == -1) {
                randNum = rand() % listSize;
                currentlySelected = tempList[randNum];
                if (currentlySelected != -1) {
                    for (int k = randNum; k < listSize - 1; k++) tempList[k] = tempList[k + 1];
                    listSize--;
                }
            }

            // Runs the selected benchmark
            switch (currentlySelected) {
            case 0:
                EigenConstructorBenchmark<VALUE_TYPE>(eigen, data);
                continue;
            case 1:
                CSF2ConstructorBenchmark<VALUE_TYPE, INDEX_TYPE>(eigen, data);
                continue;
            case 2:
                CSF3ConstructorBenchmark<VALUE_TYPE, INDEX_TYPE>(eigen, data);
                continue;
            case 3:
                EigenInnerIteratorBenchmark<VALUE_TYPE>(eigen, data);
                continue;
            case 4:
                CSF2InnerIteratorBenchmark<VALUE_TYPE, INDEX_TYPE>(csf2, data);
                continue;
            case 5:
                CSF3InnerIteratorBenchmark<VALUE_TYPE, INDEX_TYPE>(csf3, data);
                continue;
            case 6:
                EigenScalarMultiplicationBenchmark<VALUE_TYPE>(eigen, data);
                continue;
            case 7:
                CSF2ScalarMultiplicationBenchmark<VALUE_TYPE, INDEX_TYPE>(csf2, data);
                continue;
            case 8:
                CSF3scalarMultiplicationBenchmark<VALUE_TYPE, INDEX_TYPE>(csf3, data);
                continue;
            case 9:
                EigenVectorMultiplicationBenchmark<VALUE_TYPE>(eigen, data);
                continue;
            case 10:
                CSF2VectorMultiplicationBenchmark<VALUE_TYPE, INDEX_TYPE>(eigen, csf2, data);
                continue;
            case 11:
                CSF3VectorMultiplicationBenchmark<VALUE_TYPE, INDEX_TYPE>(eigen, csf3, data);
                continue;
            case 12:
                EigenMemoryFootprintBenchmark<VALUE_TYPE>(data, eigenTriplet, matrixData[1], matrixData[2]);
                continue;
            case 13:
                CSF2MemoryFootprintBenchmark<VALUE_TYPE, INDEX_TYPE>(data, eigenTriplet, matrixData[1], matrixData[2]);
                continue;
            case 14:
                CSF3MemoryFootprintBenchmark<VALUE_TYPE, INDEX_TYPE>(data, eigenTriplet, matrixData[1], matrixData[2]);
                continue;
            }
        }

        bench.pushData(data);
        std::vector<uint64_t> data(NUM_OF_BENCHMARKS, 0);
        std::cout << "Iteration " << i << " complete!" << std::endl;
    }


    // Class to calculate the maxes and averages of the benchmarking data
    bench.printTimesToCSV();
    return 1;
}

/**
 * @brief A procedure to read in a matrix market file and map it to a vector of triplets
 *        This also maps the matrix attributes to a vector
 * @param eigenTriplet
 * @param matrixData
 */
template <typename T>
void readFile(std::vector<Eigen::Triplet<T>>& eigenTriplet, std::vector<double>& matrixData, char* filename) {
    int retCode;
    MM_typecode matcode;
    FILE* f;
    int rows, cols, nonzeros;
    int i, * I, * J;
    double* val;

    // Check for correct number of arguments


    if ((f = fopen(filename, "r")) == NULL) {
        std::cout << "\033[31;1;4mError: Could not open matrix file!\033[0m" << std::endl;
        exit(1);
    }

    // Makes sure the banner can be read
    if (mm_read_banner(f, &matcode) != 0) {
        std::cout << "\033[31;1;4mError: Could not process Matrix Market banner.\033[0m" << std::endl;
        exit(1);
    }

    // Makes sure the matrix is not complex
    if (mm_is_complex(matcode) && !mm_is_matrix(matcode)) {
        std::cout << "\033[31;1;4mError: This application does not support \033[0m" << std::endl;
        std::cout << "\033[31;1;4mMarket Market type: \033[0m" << mm_typecode_to_str(matcode) << std::endl;
        std::cout << "Matrix might be complex or not a matrix";
        exit(1);
    }

    // Reads the dimensions and number of nonzeros
    if ((retCode = mm_read_mtx_crd_size(f, &rows, &cols, &nonzeros)) != 0) {
        std::cout << "\033[31;1;4mError: Could not read matrix dimensions.\033[0m" << std::endl;
        exit(1);
    }

    if (cols > 30000 || rows > 30000) {
        std::cout << "\033[31;1;4mMatrix too large, skipping...\033[0m" << std::endl;
        exit(1);
    }

    // Allocate memory for the matrix
    I = (int*)malloc(nonzeros * sizeof(int));
    J = (int*)malloc(nonzeros * sizeof(int));
    val = (double*)malloc(nonzeros * sizeof(double));

    // Read the matrix
    if (mm_is_pattern(matcode)) {
        for (i = 0; i < nonzeros; i++) {
            fscanf(f, "%d %d\n", &I[i], &J[i]);
            val[i] = 1.0;
            I[i]--;  /* adjust from 1-based to 0-based */
            J[i]--;
        }
    }
    else {
        for (i = 0; i < nonzeros; i++) {
            fscanf(f, "%d %d %lg\n", &I[i], &J[i], &val[i]);
            I[i]--;  /* adjust from 1-based to 0-based */
            J[i]--;
        }

    }

    // Close the file
    if (f != stdin) fclose(f);

    // Create the Eigen triplet
    for (int i = 0; i < nonzeros; i++) {
        eigenTriplet.push_back(Eigen::Triplet<VALUE_TYPE>(I[i], J[i], val[i]));
    }

    // Create the matrix data
    matrixData.push_back(rows);
    matrixData.push_back(cols);
    matrixData.push_back(nonzeros);

    //use a hash to store unique values
    std::unordered_set<double> uniqueValues;

    //iterates through the values and inserts them into the hash to record unique values
    for (int i = 0; i < nonzeros; i++) {
        uniqueValues.insert(val[i]);
    }
    matrixData.push_back(1.0 - ((double)uniqueValues.size() / nonzeros));

    // Calculate matrix density
    matrixData.push_back((double)nonzeros / (double)(rows * cols));

    // Free the memory
    free(I);
    free(J);
    free(val);
}

//https://www.phind.com/search?cache=e2eb22ba-3690-4155-a8f1-18a61dad9cbe
// "Calculate entropy of an Eigen::Sparse matrix in C++"
// Plus some modifications
double calculateEntropy(const Eigen::SparseMatrix<double>& mat) {
    std::unordered_map<double, int> counts;
    int nnz = mat.nonZeros();
    double val;
    for (int k = 0; k < mat.outerSize(); ++k) {
        for (typename Eigen::SparseMatrix<double>::InnerIterator it(mat, k); it; ++it) {
            val = it.value();
            ++counts[val];
        }
    }
    double H = 1;
    double inv_nnz = 1.0 / nnz;
    for (const auto& [val, count] : counts) {
        double p = count * inv_nnz;
        H += p * std::log2(p);
    }
    return H;
}

/**
 * @brief Benchmark for the Eigen::SparseMatrix constructor
 *
 */

template <typename T>
void EigenConstructorBenchmark(Eigen::SparseMatrix<T>& eigen, std::vector<uint64_t>& data) {

    //Timer
    std::chrono::time_point<std::chrono::system_clock> start, end;

    //benchmark the Eigen constructor
    start = std::chrono::system_clock::now();
    Eigen::SparseMatrix<T> eigenMat(eigen);
    eigenMat.makeCompressed();
    end = std::chrono::system_clock::now();
    data.at(0) = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
}

/**
 * @brief Benchmark for the CSF2 constructor
 *
 */

template <typename T, typename indexT>
void CSF2ConstructorBenchmark(Eigen::SparseMatrix<T>& eigen, std::vector<uint64_t>& data) {
    std::chrono::time_point<std::chrono::system_clock> start, end;

    //benchmark the CSF2 constructor
    start = std::chrono::system_clock::now();
    CSF::SparseMatrix<T, int, 2> csf2(eigen);
    end = std::chrono::system_clock::now();

    data.at(1) = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
}

/**
 * @brief Benchmark for the CSF3 constructor
 *
 */

template <typename T, typename indexT>
void CSF3ConstructorBenchmark(Eigen::SparseMatrix<T>& eigen, std::vector<uint64_t>& data) {
    std::chrono::time_point<std::chrono::system_clock> start, end;

    //benchmark the CSF3 constructor
    start = std::chrono::system_clock::now();
    CSF::SparseMatrix<T, int, 3> csf3(eigen);
    end = std::chrono::system_clock::now();

    data.at(2) = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
}

/**
 * @brief Benchmark for the Eigen::SparseMatrix InnerIterator
 *
 */

template <typename T>
void EigenInnerIteratorBenchmark(Eigen::SparseMatrix<T>& eigen, std::vector<uint64_t>& data) {
    std::chrono::time_point<std::chrono::system_clock> start, end;

    //Eigen
    start = std::chrono::system_clock::now();
    for (int i = 0; i < eigen.outerSize(); ++i) {
        for (Eigen::SparseMatrix<double>::InnerIterator it(eigen, i); it; ++it) {
            it.value();
        }
    }
    end = std::chrono::system_clock::now();

    data.at(3) = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
}

/**
 * @brief Benchmark for the CSF2 InnerIterator
 *
 */

template <typename T, typename indexT>
void CSF2InnerIteratorBenchmark(CSF::SparseMatrix<T, indexT, 2> csf2, std::vector<uint64_t>& data) {
    std::chrono::time_point<std::chrono::system_clock> start, end;

    //CSF 2
    start = std::chrono::system_clock::now();
    for (uint32_t i = 0; i < csf2.outerSize(); ++i) {
        for (typename CSF::SparseMatrix<double, indexT, 2>::InnerIterator it(csf2, i); it; ++it) {
            it.value();
        }
    }
    end = std::chrono::system_clock::now();

    data.at(4) = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
}

/**
 * @brief Benchmark for the CSF3 InnerIterator
 *
 */

template <typename T, typename indexT>
void CSF3InnerIteratorBenchmark(CSF::SparseMatrix<T, indexT, 3> csf3, std::vector<uint64_t>& data) {
    std::chrono::time_point<std::chrono::system_clock> start, end;

    //CSF 3
    start = std::chrono::system_clock::now();
    for (uint32_t i = 0; i < csf3.outerSize(); ++i) {
        for (typename CSF::SparseMatrix<double, indexT, 3>::InnerIterator it(csf3, i); it; ++it) {
            it.value();
        }
    }
    end = std::chrono::system_clock::now();

    data.at(5) = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
}

/**
 * @brief Benchmark for the Eigen::SparseMatrix Scalar Multiplication
 *
 */

template <typename T>
void EigenScalarMultiplicationBenchmark(Eigen::SparseMatrix<T>& eigen, std::vector<uint64_t>& data) {
    std::chrono::time_point<std::chrono::system_clock> start, end;

    //Eigen
    start = std::chrono::system_clock::now();
    eigen * 2;
    end = std::chrono::system_clock::now();

    data.at(6) = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
}

/**
 * @brief Benchmark for the CSF2 Scalar Multiplication
 *
 */

template <typename T, typename indexT>
void CSF2ScalarMultiplicationBenchmark(CSF::SparseMatrix<T, indexT, 2> csf2, std::vector<uint64_t>& data) {
    std::chrono::time_point<std::chrono::system_clock> start, end;

    //CSF 2
    start = std::chrono::system_clock::now();
    csf2 * 2;
    // csf2 = csf2 * 2;
    end = std::chrono::system_clock::now();
    data.at(7) = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
}

/**
 * @brief Benchmark for the CSF3 Scalar Multiplication
 *
 */

template <typename T, typename indexT>
void CSF3scalarMultiplicationBenchmark(CSF::SparseMatrix<T, indexT, 3> csf3, std::vector<uint64_t>& data) {
    std::chrono::time_point<std::chrono::system_clock> start, end;

    //CSF 3
    start = std::chrono::system_clock::now();
    csf3 * 2;
    // csf3 = csf3 * 2;
    end = std::chrono::system_clock::now();

    data.at(8) = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
}

/**
 * @brief Benchmark for the Eigen::SparseMatrix Vector Multiplication
 *
 */

template <typename T>
void EigenVectorMultiplicationBenchmark(Eigen::SparseMatrix<T>& eigen, std::vector<uint64_t>& data) {
    std::chrono::time_point<std::chrono::system_clock> start, end;

    // Eigen Vectors
    Eigen::SparseMatrix<T> eigenTempVector(eigen.cols(), 1);
    Eigen::VectorXd eigenVector(eigen.cols());
    eigenTempVector.reserve(eigen.cols());

    // Filling eigen vectors
    for (int i = 0; i < eigen.cols(); ++i) {
        eigenTempVector.insert(i, 0) = 2;
        eigenVector(i) = 2.0;
    }

    //Eigen
    start = std::chrono::system_clock::now();
    Eigen::MatrixXd resultEigen = eigen * eigenVector;
    end = std::chrono::system_clock::now();
    data.at(9) = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
}

/**
 * @brief Benchmark for the CSF2 Vector Multiplication
 *
 */

template <typename T, typename indexT>
void CSF2VectorMultiplicationBenchmark(Eigen::SparseMatrix<T>& eigen, CSF::SparseMatrix<T, indexT, 2> csf2, std::vector<uint64_t>& data) {
    std::chrono::time_point<std::chrono::system_clock> start, end;

    // Eigen Vectors
    Eigen::SparseMatrix<T> eigenTempVector(eigen.cols(), 1);
    eigenTempVector.reserve(eigen.cols());

    // Filling eigen vectors
    for (int i = 0; i < eigen.cols(); ++i) {
        eigenTempVector.insert(i, 0) = 2;
    }

    CSF::SparseMatrix<T, indexT, 2> csf2TempVector(eigenTempVector);
    typename CSF::SparseMatrix<T, indexT, 2>::Vector csf2Vector(csf2TempVector, 0);

    //CSF 2
    start = std::chrono::system_clock::now();
    typename CSF::SparseMatrix<T, indexT, 2>::Vector result2(csf2 * csf2Vector);
    end = std::chrono::system_clock::now();

    data.at(10) = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

}

/**
 * @brief Benchmark for the CSF3 Vector Multiplication
 *
 */

template <typename T, typename indexT>
void CSF3VectorMultiplicationBenchmark(Eigen::SparseMatrix<T>& eigen, CSF::SparseMatrix<T, indexT, 3> csf3, std::vector<uint64_t>& data) {
    std::chrono::time_point<std::chrono::system_clock> start, end;

    // Eigen Vectors
    Eigen::SparseMatrix<T> eigenTempVector(eigen.cols(), 1);
    eigenTempVector.reserve(eigen.cols());

    // Filling eigen vectors
    for (int i = 0; i < eigen.cols(); ++i) {
        eigenTempVector.insert(i, 0) = 2;
    }

    // Creating CSF Vectors
    CSF::SparseMatrix<T, indexT, 3> csf3TempVector(eigenTempVector);
    typename CSF::SparseMatrix<T, indexT, 3>::Vector csf3Vector(csf3TempVector, 0);

    //CSF 3
    start = std::chrono::system_clock::now();
    typename CSF::SparseMatrix<T, indexT, 3>::Vector result3(csf3 * csf3Vector);
    end = std::chrono::system_clock::now();

    data.at(11) = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
}

/**
 * @brief Benchmark for the Eigen::SparseMatrix Memory Footprint Benchmark
 *
 */

template <typename T>
void EigenMemoryFootprintBenchmark(std::vector<uint64_t>& data, std::vector<Eigen::Triplet<T>>& eigenTriplet, uint32_t inner, uint32_t outer) {
    //Create Eigen Matrix
    Eigen::SparseMatrix<VALUE_TYPE> eigenMatrix(inner, outer);
    eigenMatrix.setFromTriplets(eigenTriplet.begin(), eigenTriplet.end());
    eigenMatrix.makeCompressed();

    data.at(12) = eigenMatrix.rows() * eigenMatrix.cols() * sizeof(VALUE_TYPE) + eigenMatrix.nonZeros();

}

/**
 * @brief CSF2 Memory Footprint Benchmark
 *
 */

template <typename T, typename indexT>
void CSF2MemoryFootprintBenchmark(std::vector<uint64_t>& data, std::vector<Eigen::Triplet<T>>& eigenTriplet, uint32_t inner, uint32_t outer) {
    //Create Eigen Matrix
    Eigen::SparseMatrix<VALUE_TYPE> eigenMatrix(inner, outer);
    eigenMatrix.setFromTriplets(eigenTriplet.begin(), eigenTriplet.end());
    eigenMatrix.makeCompressed();

    // CSF Construction
    CSF::SparseMatrix<VALUE_TYPE, INDEX_TYPE, 2> csf2Matrix(eigenMatrix);
    data.at(13) = csf2Matrix.compressionSize();

}

/**
 * @brief CSF3 Memory Footprint Benchmark
 *
 */

template <typename T, typename indexT>
void CSF3MemoryFootprintBenchmark(std::vector<uint64_t>& data, std::vector<Eigen::Triplet<T>>& eigenTriplet, uint32_t inner, uint32_t outer) {
    //Create Eigen Matrix
    Eigen::SparseMatrix<VALUE_TYPE> eigenMatrix(inner, outer);
    eigenMatrix.setFromTriplets(eigenTriplet.begin(), eigenTriplet.end());
    eigenMatrix.makeCompressed();

    // CSF Construction
    CSF::SparseMatrix<VALUE_TYPE, INDEX_TYPE, 3> csf3Matrix(eigenMatrix);
    data.at(14) = csf3Matrix.compressionSize();
}

