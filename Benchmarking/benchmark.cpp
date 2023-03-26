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

#define 

#include "lib/benchmarkFunctions.h"

int main(int argc, char** argc) {
    typedef Eigen::Triplet<double> eigenTriplet;
    std::vector<uint64_t> data;
    std::vector<uint32_t> matrixData;

    // Records the matrix ID
    matrixData.push_back(argv[2]);

    // Read in the matrix market file
    readFile(argv, eigenTriplet, matrixData);

    BenchAnalysis bench = BenchAnalysis(matrixData, redundancy, matrixDensity);

    // Create the Eigen matrix
    Eigen::SparseMatrix<double> eigen(matrixData[1], matrixData[2]);
    eigen.reserve(matrixData[3]);
    eigen.setFromTriplets(eigenTriplet.begin(), eigenTriplet.end());
    eigen.makeCompressed();

    // Create the CSF matrices
    CSFMatrix<double, int, 1> csf(eigen);
    CSFMatrix2<double, int, 2> csf2(eigen);
    CSFMatrix3<double, int, 3> csf3(eigen);

    // Runs each benchmark 100 times
    for (int i = 0; i < NUM_OF_ITERATIONS; i++) {
        constructorBenchmark(data, inner, outer, values);
        innerIteratorBenchmark(data, eigen, csf, csf2, csf3);
        scalarMultiplicationBenchmark(data, eigen, csf, csf2, csf3);
        vectorMultiplicationBenchmark(data, eigen, csf, csf2, csf3);
        matrixMultiplicationBenchmark(data, eigen, csf, csf2, csf3);

        bench.pushData(data);
        data.clear();
    }

    // Class to calculate the maxes and averages of the benchmarking data
    bench.printTimestoCSV();
    bench.printMatrixAttributesToCSV();
}

/**
 * @brief A procedure to read in a matrix market file and map it to a vector of triplets
 *        This also maps the matrix attributes to a vector
 * @param eigenTriplet
 * @param matrixData
 */

void readFile(char** argv, Eigen::Triplet& eigenTriplet, std::vector<uint32_t>& matrixData) {
    int retCode;
    MM_typecode matcode;
    FILE* f;
    int rows, cols, nonzeros;
    int i, * I, * J;
    double* val;

    // Check for correct number of arguments
    if (argc < 2) {
        fprintf(stderr, "Usage: %s currentFile\n", argv[0]);
    }
    else {
        if ((f = fopen(argv[1], "r")) == NULL)
            std::cout << "\033[31;1;4mError: Could not open matrix file!\033[0m" << std::endl;
        exit(1);
    }

    // Makes sure the banner can be read
    if (mm_read_banner(f, &matcode) != 0) {
        std::cout << "\033[31;1;4mError: Could not process Matrix Market banner.\033[0m" << std::endl;
        exit(1);
    }

    // Makes sure the matrix is not complex
    if (!mm_is_complex(matcode) && mm_is_matrix(matcode)) {
        std::cout << "\033[31;1;4mError: This application does not support \033[0m" << std::endl;
        std::cout << "\033[31;1;4mMarket Market type: \033[0m" << mm_typecode_to_str(matcode) << std::endl;
        std::cout << "Matrix might be complex or not a matrix"
            exit(1);
    }

    // Reads the dimensions and number of nonzeros
    if ((retCode = mm_read_mtx_crd_size(f, &rows, &cols, &nonzeros)) != 0) {
        std::cout << "\033[31;1;4mError: Could not read matrix dimensions.\033[0m" << std::endl;
        exit(1);
    }

    // Allocate memory for the matrix
    I = (int*)malloc(nz * sizeof(int));
    J = (int*)malloc(nz * sizeof(int));
    val = (double*)malloc(nz * sizeof(double));

    // Read the matrix
    for (i = 0; i < nz; i++) {
        fscanf(f, "%d %d %lg\n", &I[i], &J[i], &val[i]);
        I[i]--;  /* adjust from 1-based to 0-based */
        J[i]--;
    }

    // Close the file
    if (f != stdin) fclose(f);

    // Create the Eigen triplet
    for (int i = 0; i < nz; i++) {
        eigenTriplet.push_back(T(I[i], J[i], val[i]));
    }

    // Create the matrix data
    matrixData.push_back(rows);
    matrixData.push_back(cols);
    matrixData.push_back(nonzeros);

    // Calculate matrix redundancy

    //use a hash to store unique values
    std::unordered_set<double> uniqueValues;

    //iterates through the values and inserts them into the hash to record unique values
    //the length of the hash is then divided by the number of nonzeros to get the redundancy
    for (int i = 0; i < nonzeros; i++) {
        uniqueValues.insert(val[i]);
    }
    matrixData.push_back(1 - (uniqueValues.length() / nonzeros));

    // Calculate matrix density
    matrixData.push_back(nonzeros / (rows * cols));

    // Free the memory
    free(I);
    free(J);
    free(val);
}


void constructorBenchmark(std::vector<uint64_t>& data, Eigen::Triplet eigenTriplet) {

    //Timer
    std::chrono::time_point<std::chrono::system_clock> start, end;

    //benchmark the Eigen constructor
    start = std::chrono::system_clock::now();
    Eigen::SparseMatrix<T> eigen(inner, outer);
    eigen.setFromTriplets();
    eigen.makeCompressed();
    end = std::chrono::system_clock::now();

    data.push_back(std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count());

    //benchmark the CSF constructor
    start = std::chrono::system_clock::now();
    CSF::SparseMatrix<T, int, 1> csf(eigen);
    end = std::chrono::system_clock::now();

    data.push_back(std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count());

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

void innerIteratorBenchmark(std::vector<uint64_t>& data, Eigen::Triplet& eigenTriplet) {
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
    //     for (CSF::SparseMatrix<double, indexType, 1>::InnerIterator it(csf, i); it; ++it) {
    //         it.value();
    //     }
    // }
    // end = std::chrono::system_clock::now();

    // data.push_back(std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count());
    data.push_back(0);

    //CSF 2
    start = std::chrono::system_clock::now();
    for (int i = 0; i < csf2.outerSize(); ++i) {
        for (CSF::SparseMatrix<double, indexType, 2>::InnerIterator it(csf2, i); it; ++it) {
            it.value();
        }
    }
    end = std::chrono::system_clock::now();

    data.push_back(std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count());

    //CSF 3
    start = std::chrono::system_clock::now();
    for (int i = 0; i < csf3.outerSize(); ++i) {
        for (CSF::SparseMatrix<double, indexType, 3>::InnerIterator it(csf3, i); it; ++it) {
            it.value();
        }
    }
    end = std::chrono::system_clock::now();

    data.push_back(std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count());

}

void scalarMultiplicationBenchmark(std::vector<uint64_t>& data, Eigen::Triplet eigenTriplet) {
    std::chrono::time_point<std::chrono::system_clock> start, end;

    //Eigen
    start = std::chrono::system_clock::now();
    eigen = eigen * 2;
    end = std::chrono::system_clock::now();

    data.push_back(std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count());

    //CSF 1
    // start = std::chrono::system_clock::now();
    // csf = csf * 2;
    // end = std::chrono::system_clock::now();

    // data.push_back(std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count());
    data.push_back(0);

    //CSF 2
    start = std::chrono::system_clock::now();
    csf2 = csf2 * 2;
    end = std::chrono::system_clock::now();

    data.push_back(std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count());

    //CSF 3
    start = std::chrono::system_clock::now();
    csf3 = csf3 * 2;
    end = std::chrono::system_clock::now();

    data.push_back(std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count());

}

void vectorMultiplicationBenchmark(std::vector<uint64_t>& data, Eigen::Triplet eigenTriplet) {

    std::chrono::time_point<std::chrono::system_clock> start, end;

    //Eigen
    start = std::chrono::system_clock::now();
    eigen* eigenVector;
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
    csf2* csf2Vector;
    end = std::chrono::system_clock::now();

    data.push_back(std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count());

    //CSF 3
    start = std::chrono::system_clock::now();
    csf3* csf3Vector;
    end = std::chrono::system_clock::now();

    data.push_back(std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count());

}


// void matrixMultiplicationBenchmark(std::vector<uint64_t>& data, Eigen::Triplet eigenTriplet) {

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
