// #include "../variations/CSFIterator.cpp"
#include "../variations/GenericCSCIterator.cpp"
#include "../variations/rng.cpp"
// #include "../variations/CSFMatrix.cpp"
#include "CPP_Lib.hpp"

void iteratorBenchmark(int numRows, int numCols, int sparsity, uint64_t seed);
template <typename T> Eigen::SparseMatrix<T> generateMatrix(int numRows, int numCols, int sparsity, uint64_t seed);
