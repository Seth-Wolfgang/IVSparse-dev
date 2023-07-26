/**
 * @file CSF2_BLAS.hpp
 * @author Skyler Ruiter and Seth Wolfgang
 * @brief BLAS Routines and Other Matrix Calculations for VCSC Sparse Matrices
 * @version 0.1
 * @date 2023-07-03
 */

#pragma once

namespace IVSparse {

    //* BLAS Level 1 Routines *//

    // Scalar Multiply
    template <typename T, typename indexT, bool columnMajor>
    inline IVSparse::SparseMatrix<T, indexT, 2, columnMajor> SparseMatrix<T, indexT, 2, columnMajor>::scalarMultiply(T scalar) {

        // Deep copy the matrix
        IVSparse::SparseMatrix<T, indexT, 2, columnMajor> newMatrix(*this);

        // If performance vectors are active use them for the scalar multiplication
        #pragma omp parallel for schedule(dynamic)
        for (int i = 0; i < outerDim; i++) {
            for (int j = 0; j < valueSizes[i]; j++) {
                newMatrix.values[i][j] *= scalar;
            }
        }
        return newMatrix;
    }

    // In Place Scalar Multiply
    template <typename T, typename indexT, bool columnMajor>
    inline void SparseMatrix<T, indexT, 2, columnMajor>::inPlaceScalarMultiply(T scalar) {

        // if performance vectors are active use them for the scalar multiplication
        #pragma omp parallel for schedule(dynamic)
        for (int i = 0; i < outerDim; i++) {
            for (int j = 0; j < valueSizes[i]; j++) {
                values[i][j] *= scalar;
            }
        }
    }

    //* BLAS Level 2 Routines *//

    // Matrix Vector Multiplication (IVSparse::SparseMatrix * Eigen::Vector)
    template <typename T, typename indexT, bool columnMajor>
    inline Eigen::Matrix<T, -1, 1> SparseMatrix<T, indexT, 2, columnMajor>::vectorMultiply(Eigen::Matrix<T, -1, 1>& vec) {
        // check that the vector is the correct size
        assert(vec.rows() == outerDim && "The vector must be the same size as the number of columns in the matrix!");
        Eigen::Matrix<T, -1, 1> eigenTemp = Eigen::Matrix<T, -1, 1>::Zero(innerDim, 1);

        // iterate over the vector and multiply the corresponding row of the matrix by the vecIter value
        #pragma omp parallel for schedule(dynamic)
        for (int i = 0; i < outerDim; i++) {
            for (typename SparseMatrix<T, indexT, 2, columnMajor>::InnerIterator matIter(*this, i); matIter; ++matIter) {
                eigenTemp(matIter.row()) += vec(matIter.col()) * matIter.value();
            }
        }
        return eigenTemp;
    }



    // Matrix Vector Multiplication (IVSparse::SparseMatrix * IVSparse::SparseMatrix::Vector)
    template <typename T, typename indexT, bool columnMajor>
    inline Eigen::Matrix<T, -1, 1> SparseMatrix<T, indexT, 2, columnMajor>::vectorMultiply(typename SparseMatrix<T, indexT, 2, columnMajor>::Vector& vec) {
        if (vec.length() != outerDim)
            throw std::invalid_argument("The vector must be the same size as the number of columns in the matrix!");

        Eigen::Matrix<T, -1, 1> newVector = Eigen::Matrix<T, -1, 1>::Zero(innerDim, 1);

        // #pragma omp parallel for schedule(dynamic)
        for (typename SparseMatrix<T, indexT, 2, columnMajor>::InnerIterator vecIter(vec); vecIter; ++vecIter) {
            for (typename SparseMatrix<T, indexT, 2, columnMajor>::InnerIterator matIter(*this, vecIter.row()); matIter; ++matIter) {
                newVector(matIter.row()) += matIter.value() * vecIter.value();
            }
        }
        return newVector;
    }

    //* BLAS Level 3 Routines *//
    //Matrix multiplication has been moved to the VCSC_Operator.hpp file


    //* Other Matrix Calculations *//

    // Finds the Outer Sum of the Matrix
    template <typename T, typename indexT, bool columnMajor>
    inline std::vector<T> SparseMatrix<T, indexT, 2, columnMajor>::outerSum() {
        std::vector<T> outerSum = std::vector<T>(outerDim);

        #pragma omp parallel for schedule(dynamic)
        for (int i = 0; i < outerDim; i++) {
            for (int j = 0; j < valueSizes[i]; j++) {
                outerSum[i] += values[i][j] * counts[i][j];
            }
        }
        return outerSum;
    }

    // Finds the Inner Sum of the Matrix
    template <typename T, typename indexT, bool columnMajor>
    inline std::vector<T> SparseMatrix<T, indexT, 2, columnMajor>::innerSum() {
        std::vector<T> innerSum = std::vector<T>(innerDim);

        #pragma omp parallel for schedule(dynamic)
        for (int i = 0; i < outerDim; i++) {
            for (typename SparseMatrix<T, indexT, 2, columnMajor>::InnerIterator it(*this, i); it; ++it) {
                innerSum[it.row()] += it.value();
            }
        }
        return innerSum;
    }

    // Finds the maximum value in each column
    template <typename T, typename indexT, bool columnMajor>
    inline std::vector<T> SparseMatrix<T, indexT, 2, columnMajor>::maxColCoeff() {
        std::vector<T> maxCoeff = std::vector<T>(innerDim);

        #pragma omp parallel for schedule(dynamic)
        for (int i = 0; i < outerDim; i++) {
            for (int j = 0; j < valueSizes[i]; j++) {
                if (values[i][j] > maxCoeff[i]) {
                    maxCoeff[i] = values[i][j];
                }
            }
        }
        return maxCoeff;
    }

    // Finds the maximum value in each row
    template <typename T, typename indexT, bool columnMajor>
    inline std::vector<T> SparseMatrix<T, indexT, 2, columnMajor>::maxRowCoeff() {
        std::vector<T> maxCoeff = std::vector<T>(innerDim);

        #pragma omp parallel for schedule(dynamic)
        for (int i = 0; i < outerDim; i++) {
            for (typename SparseMatrix<T, indexT, 2, columnMajor>::InnerIterator it(*this, i); it; ++it) {
                if (it.value() > maxCoeff[it.row()]) {
                    maxCoeff[it.row()] = it.value();
                }
            }
        }
        return maxCoeff;
    }

    // Finds the minimum value in each column
    template <typename T, typename indexT, bool columnMajor>
    inline std::vector<T> SparseMatrix<T, indexT, 2, columnMajor>::minColCoeff() {
        std::vector<T> minCoeff = std::vector<T>(innerDim);

        #pragma omp parallel for schedule(dynamic)
        for (int i = 0; i < outerDim; i++) {
            for (int j = 0; j < valueSizes[i]; j++) {
                if (values[i][j] < minCoeff[i]) {
                    minCoeff[i] = values[i][j];
                }
            }
        }
        return minCoeff;
    }

    // Finds the minimum value in each row
    template <typename T, typename indexT, bool columnMajor>
    inline std::vector<T> SparseMatrix<T, indexT, 2, columnMajor>::minRowCoeff() {
        std::vector<T> minCoeff = std::vector<T>(innerDim);
        memset(minCoeff.data(), 0xF, innerDim * sizeof(T));

        for (int i = 0; i < outerDim; i++) {
            for (typename SparseMatrix<T, indexT, 2, columnMajor>::InnerIterator it(*this, i); it; ++it) {
                if (it.value() < minCoeff[it.row()]) {
                    minCoeff[it.row()] = it.value();
                }
            }
        }
        return minCoeff;
    }

    // Calculates the trace of the matrix
    template <typename T, typename indexT, bool columnMajor>
    inline T SparseMatrix<T, indexT, 2, columnMajor>::trace() {
        assert(innerDim == outerDim && "Trace is only defined for square matrices!");

        T trace = 0;
        for (int i = 0; i < outerDim; i++) {
            for (typename SparseMatrix<T, indexT, 2, columnMajor>::InnerIterator it(*this, i); it; ++it) {
                if (it.row() == i) {
                    trace += it.value();
                }
                else if (it.row() > i) {
                    continue;
                }
            }
        }
        return trace;
    }

    // Calculates the sum of the matrix
    template <typename T, typename indexT, bool columnMajor>
    inline T SparseMatrix<T, indexT, 2, columnMajor>::sum() {
        T sum = 0;

        #pragma omp parallel for schedule(dynamic)
        for (int i = 0; i < outerDim; i++) {
            for (int j = 0; j < valueSizes[i]; j++) {
                sum += values[i][j] * counts[i][j];
            }
        }
        return sum;
    }

    // Calculates the norm of the matrix
    template <typename T, typename indexT, bool columnMajor>
    inline double SparseMatrix<T, indexT, 2, columnMajor>::norm() {
        double norm = 0;

        #pragma omp parallel for schedule(dynamic)
        for (int i = 0; i < outerDim; i++) {
            for (int j = 0; j < valueSizes[i]; j++) {
                norm += values[i][j] * values[i][j] * counts[i][j];
            }
        }
        return sqrt(norm);
    }

    // Finds the length of a certain column
    template <typename T, typename indexT, bool columnMajor>
    inline double SparseMatrix<T, indexT, 2, columnMajor>::vectorLength(uint32_t col) {
        double norm = 0;

        #pragma omp parallel for schedule(dynamic)
        for (int i = 0; i < valueSizes[col]; i++) {
            norm += values[col][i] * values[col][i] * counts[col][i];
        }
        return sqrt(norm);
    }

} // namespace IVSparse
