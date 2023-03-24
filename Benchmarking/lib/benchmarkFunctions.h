
#include <chrono> 
#include "../benchmarkAnalysis.cpp"
#include <Eigen/Sparse>
#incldue "mmio.h"

// Function to read Matrix Market files
void readFile(Eigen::Triplet& eigenTriplet, std::vector<uint32_t>& matrixData);

// Function to test the speed of each constructor
void constructorBenchmark(std::vector<uint64_t>& data, Eigen::Triplet eigenTriplet);

// Function to test the speed of each iterator
void innerIteratorBenchmark(std::vector<uint64_t>& data, Eigen::Triplet eigenTriplet3);

// Function to test the speed of scalar multiplication
void scalarMultiplicationBenchmark(std::vector<uint64_t>& data, Eigen::Triplet eigenTriplet);

// Function to test the speed of vector multiplication
void vectorMultiplicationBenchmark(
    std::vector<uint64_t>& data, Eigen::Triplet eigenTriplet);

// Function to test the speed of matrix multiplication
// void matrixMultiplicationBenchmark(std::vector<uint64_t>& data, Eigen::Triplet eigenTriplet);
// Function to the memory footprint of each compression method
// void memoryFootprintBenchmark(std::vector<uint64_t>& data, Eigen::Triplet eigenTriplet);