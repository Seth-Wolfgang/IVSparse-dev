
#include <chrono> 
#include "../../CSF/SparseMatrix"
#include <unordered_set>
#include "../benchmarkAnalysis.cpp"
#include "mmio.c"
#include "../armadillo"
#include <Eigen/Dense>
#include <Eigen/Sparse>
#include <iterator>
#include <iostream>
#include <string>

#define VALUE_TYPE double
#define INDEX_TYPE int
#define NUM_OF_BENCHMARKS 28

// Function to read Matrix Market files
template <typename T>
void readFile(std::vector<Eigen::Triplet<T>>& eigenTriplet, std::vector<double>& matrixData, char* filename);

double calculateEntropy(const Eigen::SparseMatrix<double>& mat);

double averageRedundancy(const Eigen::SparseMatrix<double>& matrix);

template <typename T, uint8_t compressionLevel>
bool checkMatrixEquality(Eigen::SparseMatrix<T>& eigen, CSF::SparseMatrix<T, INDEX_TYPE, compressionLevel>& csf);

template <typename T>
void EigenConstructorBenchmark(std::vector<Eigen::Triplet<T>>& eigenTriplet, std::vector<uint64_t>& data, int rows, int cols);

template <typename T, typename indexT>
void CSF2ConstructorBenchmark(Eigen::SparseMatrix<T>& eigen, std::vector<uint64_t>& data);

template <typename T, typename indexT>
void CSF3ConstructorBenchmark(Eigen::SparseMatrix<T>& eigen, std::vector<uint64_t>& data);

template <typename T>
void ArmadilloConstructorBenchmark(std::vector<Eigen::Triplet<T>>& eigenTriplet, std::vector<uint64_t>& data, int rows, int cols);

template <typename T>
void EigenInnerIteratorBenchmark(Eigen::SparseMatrix<T> eigen, std::vector<uint64_t>& data);

template <typename T, typename indexT>
void CSF2InnerIteratorBenchmark(CSF::SparseMatrix<T, indexT, 2> csf2, std::vector<uint64_t>& data);

template <typename T, typename indexT>
void CSF3InnerIteratorBenchmark(CSF::SparseMatrix<T, indexT, 3> csf3, std::vector<uint64_t>& data);

template <typename T>
void ArmadilloInnerIteratorBenchmark(arma::sp_mat& mat, std::vector<uint64_t>& data);

template <typename T>
void EigenScalarMultiplicationBenchmark(Eigen::SparseMatrix<T> eigen, std::vector<uint64_t>& data);

template <typename T, typename indexT>
void CSF2ScalarMultiplicationBenchmark(CSF::SparseMatrix<T, indexT, 2> csf2, std::vector<uint64_t>& data);

template <typename T, typename indexT>
void CSF3scalarMultiplicationBenchmark(CSF::SparseMatrix<T, indexT, 3> csf3, std::vector<uint64_t>& data);

template <typename T>
void ArmadilloScalarMultiplicationBenchmark(arma::sp_mat mat, std::vector<uint64_t>& data);

template <typename T>
void EigenVectorMultiplicationBenchmark(Eigen::SparseMatrix<T>& eigen, std::vector<uint64_t>& data);

template <typename T, typename indexT>
void CSF2VectorMultiplicationBenchmark(Eigen::SparseMatrix<T>& eigen, CSF::SparseMatrix<T, indexT, 2>& csf2, std::vector<uint64_t>& data);

template <typename T, typename indexT>
void CSF3VectorMultiplicationBenchmark(Eigen::SparseMatrix<T>& eigen, CSF::SparseMatrix<T, indexT, 3>& csf3, std::vector<uint64_t>& data);

template <typename T>
void ArmadilloVectorMultiplicationBenchmark(arma::sp_mat& mat, std::vector<uint64_t>& data);

template <typename T>
void EigenMemoryFootprintBenchmark(std::vector<uint64_t>& data, std::vector<Eigen::Triplet<T>>& eigenTriplet, uint32_t inner, uint32_t outer);

template <typename T, typename indexT>
void CSF2MemoryFootprintBenchmark(std::vector<uint64_t>& data, std::vector<Eigen::Triplet<T>>& eigenTriplet, uint32_t inner, uint32_t outer);

template <typename T, typename indexT>
void CSF3MemoryFootprintBenchmark(std::vector<uint64_t>& data, std::vector<Eigen::Triplet<T>>& eigenTriplet, uint32_t inner, uint32_t outer);

template <typename T>
void ArmadilloMemoryFootprintBenchmark(std::vector<uint64_t>& data, std::vector<Eigen::Triplet<T>>& eigenTriplet, uint32_t inner, uint32_t outer);

template <typename T>
void eigenTransposeBenchmark(Eigen::SparseMatrix<T>& eigen, std::vector<uint64_t>& data);

template <typename T, typename indexT>
void CSF2TransposeBenchmark(CSF::SparseMatrix<T, indexT, 2>& csf2, std::vector<uint64_t>& data);

template <typename T, typename indexT>
void CSF3TransposeBenchmark(CSF::SparseMatrix<T, indexT, 3>& csf3, std::vector<uint64_t>& data);

template <typename T>
void ArmadilloTransposeBenchmark(arma::sp_mat& mat, std::vector<uint64_t>& data);

template <typename T>
void eigenMatrixMultiplicationBenchmark(Eigen::SparseMatrix<T>& eigen, std::vector<uint64_t>& data);

template <typename T, typename indexT>
void CSF2MatrixMultiplicationBenchmark(Eigen::SparseMatrix<T>& eigen, CSF::SparseMatrix<T, indexT, 2>& csf2, std::vector<uint64_t>& data);

template <typename T, typename indexT>
void CSF3MatrixMultiplicationBenchmark(Eigen::SparseMatrix<T>& eigen, CSF::SparseMatrix<T, indexT, 3>& csf3, std::vector<uint64_t>& data);

template <typename T>
void ArmadilloMatrixMultiplicationBenchmark(arma::sp_mat& mat, std::vector<uint64_t>& data);

