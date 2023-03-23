#include <chrono> 
#include "benchmarkAnalysis.cpp"
#include <Eigen/Sparse>

int main() {
    std::vector<uint64_t> data;
    std::vector<uint32_t> matrixData;
    std::vector<uint32_t> inner;
    std::vector<uint32_t> outer;
    std::vector<uint32_t> values;

    readFile(matrixData, inner, outer, values);

    BenchAnalysis bench = BenchAnalysis(matrixData, redundancy, matrixDensity);

    for (int i = 0; i < 10; i++) {
        constructorBenchmark(data, inner, outer, values);
        innerIteratorBenchmark(data, eigen, csf, csf2, csf3);
        scalarMultiplicationBenchmark(data, eigen, csf, csf2, csf3);
        vectorMultiplicationBenchmark(data, eigen, csf, csf2, csf3);
        matrixMultiplicationBenchmark(data, eigen, csf, csf2, csf3);

        bench.pushData(data);
        data.clear();
    }



    bench.printTimestoCSV();
    bench.printMatrixAttributesToCSV();
}

void readFile(std::vector<uint>& matrixData,
              std::vector<uint32_t>& inner,
              std::vector<uint32_t>& outer,
              std::vector<uint32_t>& values) {
    //read a file in the rutherford-boeing format

}

void constructorBenchmark(std::vector<uint64_t>& data,
                          std::vector<uint32_t>& inner,
                          std::vector<uint32_t>& outer,
                          std::vector<uint32_t>& values) {

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

void innerIteratorBenchmark(std::vector<uint64_t>& data,
                            Eigen::SparseMatrix<T> eigen,
                            CSF::SparseMatrix<T, indexType, 1> csf,
                            CSF::SparseMatrix<T, indexType, 2> csf2,
                            CSF::SparseMatrix<T, indexType, 3> csf3) {
    std::chrono::time_point<std::chrono::system_clock> start, end;

    //Eigen
    start = std::chrono::system_clock::now();
    for (int i = 0; i < eigen.outerSize(); ++i) {
        for (Eigen::SparseMatrix<T>::InnerIterator it(eigen, i); it; ++it) {
            it.value();
        }
    }
    end = std::chrono::system_clock::now();

    data.push_back(std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count());

    //CSF 1
    // start = std::chrono::system_clock::now();
    // for (int i = 0; i < csf.outerSize(); ++i) {
    //     for (CSF::SparseMatrix<T, indexType, 1>::InnerIterator it(csf, i); it; ++it) {
    //         it.value();
    //     }
    // }
    // end = std::chrono::system_clock::now();

    // data.push_back(std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count());
    data.push_back(0);

    //CSF 2
    start = std::chrono::system_clock::now();
    for (int i = 0; i < csf2.outerSize(); ++i) {
        for (CSF::SparseMatrix<T, indexType, 2>::InnerIterator it(csf2, i); it; ++it) {
            it.value();
        }
    }
    end = std::chrono::system_clock::now();

    data.push_back(std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count());

    //CSF 3
    start = std::chrono::system_clock::now();
    for (int i = 0; i < csf3.outerSize(); ++i) {
        for (CSF::SparseMatrix<T, indexType, 3>::InnerIterator it(csf3, i); it; ++it) {
            it.value();
        }
    }
    end = std::chrono::system_clock::now();

    data.push_back(std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count());

}

void scalarMultiplicationBenchmark(std::vector<uint64_t>& data,
                                   Eigen::SparseMatrix<T> eigen,
                                   CSF::SparseMatrix<T, indexType, 1> csf,
                                   CSF::SparseMatrix<T, indexType, 2> csf2,
                                   CSF::SparseMatrix<T, indexType, 3> csf3) {
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

void vectorMultiplicationBenchmark(
    std::vector<uint64_t>& data,
    Eigen::SparseMatrix<T> eigen,
    CSF::SparseMatrix<T, indexType, 1> csf,
    CSF::SparseMatrix<T, indexType, 2> csf2,
    CSF::SparseMatrix<T, indexType, 3> csf3,
    Eigen::Matrix<T, Eigen::Dynamic, 1> eigenVector) {

    std::chrono::time_point<std::chrono::system_clock> start, end;

    //Eigen
    start = std::chrono::system_clock::now();
    eigen * eigenVector;
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
    csf2 * csf2Vector;
    end = std::chrono::system_clock::now();

    data.push_back(std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count());

    //CSF 3
    start = std::chrono::system_clock::now();
    csf3 * csf3Vector;
    end = std::chrono::system_clock::now();

    data.push_back(std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count());

}


// void matrixMultiplicationBenchmark(std::vector<uint64_t>& data,
//                                    Eigen::SparseMatrix<T> eigen,
//                                    CSF::SparseMatrix<T, indexType, 1> csf,
//                                    CSF::SparseMatrix<T, indexType, 2> csf2,
//                                    CSF::SparseMatrix<T, indexType, 3> csf3,
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
