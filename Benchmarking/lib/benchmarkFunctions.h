
#include <chrono> 
#include "../../CSF/SparseMatrix"
#include <unordered_set>
#include "../benchmarkAnalysis.cpp"
#include "mmio.c"
#include <Eigen/Dense>
#include <Eigen/Sparse>


#define VALUE_TYPE double
#define INDEX_TYPE int
#define NUM_OF_BENCHMARKS 15

// Function to read Matrix Market files
template <typename T>
void readFile(std::vector<Eigen::Triplet<T>>& eigenTriplet, std::vector<double>& matrixData, char* filename);

double calculateEntropy(const Eigen::SparseMatrix<double>& mat);

template <typename T>
void EigenConstructorBenchmark(Eigen::SparseMatrix<T>& eigen, std::vector<uint64_t>& data);

template <typename T, typename indexT>
void CSF2ConstructorBenchmark(Eigen::SparseMatrix<T>& eigen, std::vector<uint64_t>& data);

template <typename T, typename indexT>
void CSF3ConstructorBenchmark(Eigen::SparseMatrix<T>& eigen, std::vector<uint64_t>& data);

template <typename T>
void EigenInnerIteratorBenchmark(Eigen::SparseMatrix<T>& eigen, std::vector<uint64_t>& data);

template <typename T, typename indexT>
void CSF2InnerIteratorBenchmark(CSF::SparseMatrix<T, indexT, 2> csf2, std::vector<uint64_t>& data);

template <typename T, typename indexT>
void CSF3InnerIteratorBenchmark(CSF::SparseMatrix<T, indexT, 3> csf3, std::vector<uint64_t>& data);

template <typename T>
void EigenScalarMultiplicationBenchmark(Eigen::SparseMatrix<T>& eigen, std::vector<uint64_t>& data);

template <typename T, typename indexT>
void CSF2ScalarMultiplicationBenchmark(CSF::SparseMatrix<T, indexT, 2> csf2, std::vector<uint64_t>& data);

template <typename T, typename indexT>
void CSF3scalarMultiplicationBenchmark(CSF::SparseMatrix<T, indexT, 3> csf3, std::vector<uint64_t>& data);

template <typename T>
void EigenVectorMultiplicationBenchmark(Eigen::SparseMatrix<T>& eigen, std::vector<uint64_t>& data);

template <typename T, typename indexT>
void CSF2VectorMultiplicationBenchmark(Eigen::SparseMatrix<T>& eigen, CSF::SparseMatrix<T, indexT, 2> csf2, std::vector<uint64_t>& data);

template <typename T, typename indexT>
void CSF3VectorMultiplicationBenchmark(Eigen::SparseMatrix<T>& eigen, CSF::SparseMatrix<T, indexT, 3> csf3, std::vector<uint64_t>& data);
 
 template <typename T>
void EigenMemoryFootprintBenchmark(std::vector<uint64_t>& data, std::vector<Eigen::Triplet<T>>& eigenTriplet, uint32_t inner, uint32_t outer);
 
 template <typename T, typename indexT>
void CSF2MemoryFootprintBenchmark(std::vector<uint64_t>& data, std::vector<Eigen::Triplet<T>>& eigenTriplet, uint32_t inner, uint32_t outer);
 
 template <typename T, typename indexT>
void CSF3MemoryFootprintBenchmark(std::vector<uint64_t>& data, std::vector<Eigen::Triplet<T>>& eigenTriplet, uint32_t inner, uint32_t outer);
  