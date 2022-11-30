library(Rcpp)
library(RcppClock)
library(RcppEigen)
sourceCpp("src\\playground.cpp")
iteratorBenchmark(10, 10, 5.0)

