// #include <RcppEigen.h>
#include <chrono>
#include <cstdint>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <cstring>
#include <bits/stdc++.h>
#include <map>
#include <vector>
#include <Eigen/Sparse>
// #include <RcppClock.h>
// #include <Rcpp.h>

void iteratorBenchmark(int numRows, int numCols, int sparsity, uint64_t seed);
template<typename T> Eigen::SparseMatrix<T> generateMatrix(int numRows, int numCols, int sparsity, uint64_t seed);
