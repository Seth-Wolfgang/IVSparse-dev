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
    //For debugging
    argv[1] = (char*)malloc(100);
    argv[2] = (char*)malloc(10);
    strcpy(argv[1], "testMatrix.mtx");
    strcpy(argv[2], "6");
    argc = 2;


    // Checks to make sure the correct number of arguments are passed
    if (argc < 2) {
        fprintf(stderr, "Usage: %s currentFile\n", argv[0]);
        exit(1);
    }

    // Data vectors
    std::vector<Eigen::Triplet<VALUE_TYPE>> eigenTriplet;
    std::vector<uint64_t> data;
    std::vector<double> matrixData;

    // Records the matrix ID
    matrixData.push_back(std::stoi(argv[2]));

    // Read in the matrix market file
    readFile<VALUE_TYPE>(eigenTriplet, matrixData, argv[1]);
    std::cout << "Matrix Data\tID:" << matrixData[0] << ",  Rows: " << matrixData[1] << ", Cols: " << matrixData[2] << ", Nonzeros: " << matrixData[3] << std::endl;

    // Class to calculate the maxes and averages of the benchmarking data
    // and print the data to a csv
    BenchAnalysis bench = BenchAnalysis(matrixData);
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

    // Create the CSF matrices
    // CSF::SparseMatrix<VALUE_TYPE, INDEX_TYPE, 1> csf(eigen);
    CSF::SparseMatrix<VALUE_TYPE, INDEX_TYPE, 2> csf2(eigen);
    CSF::SparseMatrix<VALUE_TYPE, INDEX_TYPE, 3> csf3(eigen);

    // Runs each benchmark 100 times
    for (int i = 0; i < NUM_ITERATIONS; i++) {
        constructorBenchmark<VALUE_TYPE, INDEX_TYPE>(data, eigenTriplet, matrixData[1], matrixData[2]);
        innerIteratorBenchmark<VALUE_TYPE, INDEX_TYPE>(data, eigen, csf2, csf3);
        scalarMultiplicationBenchmark<VALUE_TYPE, INDEX_TYPE>(data, eigen, csf2, csf3);
        vectorMultiplicationBenchmark<VALUE_TYPE, INDEX_TYPE>(data, eigen, csf2, csf3);
        // matrixMultiplicationBenchmark(data, eigen, csf, csf2, csf3);
        data.push_back(0);
        data.push_back(0);
        data.push_back(0);
        data.push_back(0);

        //memory bench goes here
        data.push_back(0);
        data.push_back(0);
        data.push_back(0);
        data.push_back(0);
        
        bench.pushData(data);
        data.clear();
        std::cout << "Iteration " << i << " complete" << std::endl;
    }

    // Class to calculate the maxes and averages of the benchmarking data
    bench.printTimesToCSV();
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

    // Allocate memory for the matrix
    I = (int*)malloc(nonzeros * sizeof(int));
    J = (int*)malloc(nonzeros * sizeof(int));
    val = (double*)malloc(nonzeros * sizeof(double));

    // Read the matrix
    for (i = 0; i < nonzeros; i++) {
        fscanf(f, "%d %d %lg\n", &I[i], &J[i], &val[i]);
        I[i]--;  /* adjust from 1-based to 0-based */
        J[i]--;
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
    matrixData.push_back(nonzeros / (rows * cols));

    // Free the memory
    free(I);
    free(J);
    free(val);
}

template <typename T, typename indexT>
void constructorBenchmark(std::vector<uint64_t>& data, std::vector<Eigen::Triplet<T>>& eigenTriplet, uint32_t inner, uint32_t outer) {

    //Timer
    std::chrono::time_point<std::chrono::system_clock> start, end;

    //benchmark the Eigen constructor
    start = std::chrono::system_clock::now();
    Eigen::SparseMatrix<T> eigen(inner, outer);
    eigen.setFromTriplets(eigenTriplet.begin(), eigenTriplet.end());
    eigen.makeCompressed();
    end = std::chrono::system_clock::now();

    data.push_back(std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count());

    // //benchmark the CSF constructor
    // start = std::chrono::system_clock::now();
    // CSF::SparseMatrix<T, int, 1> csf(eigen);
    // end = std::chrono::system_clock::now();

    // data.push_back(std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count());
    data.push_back(0);

    //benchmark the CSF2 constructor
    start = std::chrono::system_clock::now();
    CSF::SparseMatrix<T, int, 2> csf2(eigen);
    end = std::chrono::system_clock::now();

    data.push_back(std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count());

    //benchmark the CSF3 constructor
    start = std::chrono::system_clock::now();
    CSF::SparseMatrix<T, int, 3> csf3(eigen);
    end = std::chrono::system_clock::now();

    data.push_back(std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count());

}

template <typename T, typename indexT>
void innerIteratorBenchmark(std::vector<uint64_t>& data, Eigen::SparseMatrix<T> eigen,
                            // CSF::SparseMatrix<T, indexT, 1> csf,
                            CSF::SparseMatrix<T, indexT, 2> csf2,
                            CSF::SparseMatrix<T, indexT, 3> csf3) {
    std::chrono::time_point<std::chrono::system_clock> start, end;

    //Eigen
    start = std::chrono::system_clock::now();
    for (int i = 0; i < eigen.outerSize(); ++i) {
        for (Eigen::SparseMatrix<double>::InnerIterator it(eigen, i); it; ++it) {
            it.value();
        }
    }
    end = std::chrono::system_clock::now();

    data.push_back(std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count());

    //CSF 1
    // start = std::chrono::system_clock::now();
    // for (int i = 0; i < csf.outerSize(); ++i) {
    //     for (typename CSF::SparseMatrix<double, indexT, 1>::InnerIterator it(csf, i); it; ++it) {
    //         it.value();
    //     }
    // }
    // end = std::chrono::system_clock::now();

    // data.push_back(std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count());
    data.push_back(0);

    //CSF 2
    start = std::chrono::system_clock::now();
    for (uint32_t i = 0; i < csf2.outerSize(); ++i) {
        for (typename CSF::SparseMatrix<double, indexT, 2>::InnerIterator it(csf2, i); it; ++it) {
            it.value();
        }
    }
    end = std::chrono::system_clock::now();

    data.push_back(std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count());

    //CSF 3
    start = std::chrono::system_clock::now();
    for (uint32_t i = 0; i < csf3.outerSize(); ++i) {
        for (typename CSF::SparseMatrix<double, indexT, 3>::InnerIterator it(csf3, i); it; ++it) {
            it.value();
        }
    }
    end = std::chrono::system_clock::now();

    data.push_back(std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count());

}

template <typename T, typename indexT>
void scalarMultiplicationBenchmark(std::vector<uint64_t>& data, Eigen::SparseMatrix<T> eigen,
                                   //    CSF::SparseMatrix<T, indexT, 1> csf,
                                   CSF::SparseMatrix<T, indexT, 2> csf2,
                                   CSF::SparseMatrix<T, indexT, 3> csf3) {
    std::chrono::time_point<std::chrono::system_clock> start, end;

    //Eigen
    start = std::chrono::system_clock::now();
    // eigen = eigen * 2;
    eigen * 2;
    end = std::chrono::system_clock::now();

    data.push_back(std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count());

    //CSF 1
    // start = std::chrono::system_clock::now();
    // csf = csf * 2;
    // csf * 2;
    // end = std::chrono::system_clock::now();

    // data.push_back(std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count());
    data.push_back(0);

    //CSF 2
    start = std::chrono::system_clock::now();
    csf2 * 2;
    // csf2 = csf2 * 2;
    end = std::chrono::system_clock::now();
    data.push_back(std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count());

    //CSF 3
    start = std::chrono::system_clock::now();
    csf3 * 2;
    // csf3 = csf3 * 2;
    end = std::chrono::system_clock::now();

    data.push_back(std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count());
}

template <typename T, typename indexT>
void vectorMultiplicationBenchmark(std::vector<uint64_t>& data, Eigen::SparseMatrix<T> eigen,
                                   //    CSF::SparseMatrix<T, indexT, 1> csf,
                                   CSF::SparseMatrix<T, indexT, 2> csf2,
                                   CSF::SparseMatrix<T, indexT, 3> csf3) {
    std::chrono::time_point<std::chrono::system_clock> start, end;

    //Vectors
    Eigen::SparseMatrix<T> eigenTempVector(eigen.rows(), 1);
    Eigen::SparseVector<T> eigenVector(eigen.rows());
    eigenTempVector.reserve(eigen.cols());
    eigenVector.reserve(eigen.cols());
    for (int i = 0; i < eigen.cols(); ++i) {
        eigenTempVector.insert(i, 0) = 2;
        eigenVector.insert(i) = 2;
    }
    CSF::SparseMatrix<T, indexT, 2> csf2TempVector(eigenTempVector);
    CSF::SparseMatrix<T, indexT, 3> csf3TempVector(eigenTempVector);
    // CSF::SparseMatrix<T, indexT, 1>::Vector csfVector(csfTempVector);
    typename CSF::SparseMatrix<T, indexT, 2>::Vector csf2Vector(csf2TempVector, 0);
    typename CSF::SparseMatrix<T, indexT, 3>::Vector csf3Vector(csf3TempVector, 0);

    //Eigen
    start = std::chrono::system_clock::now();
    Eigen::SparseMatrix<T> resultEigen = eigen * eigenVector;
    end = std::chrono::system_clock::now();

    data.push_back(std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count());

    //CSF 1
    // start = std::chrono::system_clock::now();
    // csf * csfVector;
    // end = std::chrono::system_clock::now();

    // data.push_back(std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count());
    data.push_back(0);

    //CSF 2
    start = std::chrono::system_clock::now();
    typename CSF::SparseMatrix<T, indexT, 2>::Vector result2(csf2 * csf2Vector);
    end = std::chrono::system_clock::now();

    data.push_back(std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count());

    //CSF 3
    start = std::chrono::system_clock::now();
    typename CSF::SparseMatrix<T, indexT, 3>::Vector result3(csf3 * csf3Vector);
    end = std::chrono::system_clock::now();

    data.push_back(std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count());

}


// void matrixMultiplicationBenchmark(std::vector<uint64_t>& data,
//                                    Eigen::SparseMatrix<T> eigen,
//                                    CSF::SparseMatrix<T, indexT, 1> csf,
//                                    CSF::SparseMatrix<T, indexT, 2> csf2,
//                                    CSF::SparseMatrix<T, indexT, 3> csf3,
//                                    Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic> eigenMatrix) {

//     std::chrono::time_point<std::chrono::system_clock> start, end;

//     //Eigen
//     start = std::chrono::system_clock::now();
//     eigen* eigenMatrix;
//     end = std::chrono::system_clock::now();

//     data.push_back(std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count());

//     //CSF 1
//     // start = std::chrono::system_clock::now();
//     // csf * csfMatrix;
//     // end = std::chrono::system_clock::now();

//     // data.push_back(std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count());
//     data.push_back(0);

//     //CSF 2
//     start = std::chrono::system_clock::now();
//     csf2* csf2Matrix;
//     end = std::chrono::system_clock::now();

//     data.push_back(std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count());

//     //CSF 3
//     start = std::chrono::system_clock::now();
//     csf3* csf3Matrix;
//     end = std::chrono::system_clock::now();

//     data.push_back(std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count());
// }

// void memoryBenchmark () {

// }