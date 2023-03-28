
#include <chrono> 
#include "../../CSF/SparseMatrix"
#include <unordered_set>
#include "../benchmarkAnalysis.cpp"
#include "mmio.c"

#define VALUE_TYPE double
#define INDEX_TYPE int

// Function to read Matrix Market files
template <typename T>
void readFile(std::vector<Eigen::Triplet<T>>& eigenTriplet, std::vector<double>& matrixData, char* filename);

// Function to test the speed of each constructor
template <typename T, typename indexT>
void constructorBenchmark(std::vector<uint64_t>& data, std::vector<Eigen::Triplet<T>>& eigenTriplet, uint32_t inner, uint32_t outer);

// Function to test the speed of each iterator
template <typename T, typename indexT>
void innerIteratorBenchmark(std::vector<uint64_t>& data, Eigen::SparseMatrix<T> eigen,
                            // CSF::SparseMatrix<T, indexT, 1> csf,
                            CSF::SparseMatrix<T, indexT, 2> csf2,
                            CSF::SparseMatrix<T, indexT, 3> csf3);

// Function to test the speed of scalar multiplication
template <typename T, typename indexT>
void scalarMultiplicationBenchmark(std::vector<uint64_t>& data, Eigen::SparseMatrix<T> eigen,
                                //    CSF::SparseMatrix<T, indexT, 1> csf,
                                   CSF::SparseMatrix<T, indexT, 2> csf2,
                                   CSF::SparseMatrix<T, indexT, 3> csf3);

// Function to test the speed of vector multiplication
template <typename T, typename indexT>
void vectorMultiplicationBenchmark(std::vector<uint64_t>& data, Eigen::SparseMatrix<T> eigen,
                                //    CSF::SparseMatrix<T, indexT, 1> csf,
                                   CSF::SparseMatrix<T, indexT, 2> csf2,
                                   CSF::SparseMatrix<T, indexT, 3> csf3);

// Function to test the speed of matrix multiplication
// void matrixMultiplicationBenchmark(std::vector<uint64_t>& data, Eigen::Triplet eigenTriplet);

// Function to the memory footprint of each compression method
template <typename T, typename indexT>
void memoryFootprintBenchmark(std::vector<uint64_t>& data, std::vector<Eigen::Triplet<T>>& eigenTriplet, uint32_t inner, uint32_t outer);