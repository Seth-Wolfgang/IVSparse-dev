/**
 * @file CSF2_BLAS.hpp
 * @author Skyler Ruiter and Seth Wolfgang
 * @brief BLAS Routines and Other Matrix Calculations for CSF2 Sparse Matrices
 * @version 0.1
 * @date 2023-07-03
 */

#pragma once

namespace CSF {

    //* BLAS Level 1 Routines *//

    // Scalar Multiply
    template <typename T, typename indexT, bool columnMajor>
    inline CSF::SparseMatrix<T, indexT, 2, columnMajor> SparseMatrix<T, indexT, 2, columnMajor>::scalarMultiply(T scalar) {

        // Deep copy the matrix
        CSF::SparseMatrix<T, indexT, 2, columnMajor> newMatrix(*this);

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

    // Matrix Vector Multiplication (Eigen::VectorXd * CSF::SparseMatrix)
    template <typename T, typename indexT, bool columnMajor>
    inline Eigen::VectorXd SparseMatrix<T, indexT, 2, columnMajor>::vectorMultiply(Eigen::VectorXd& vec) {
        // check that the vector is the correct size
        assert(vec.rows() == outerDim && "The vector must be the same size as the number of columns in the matrix!");

        Eigen::Matrix<T, -1, 1> eigenTemp(innerDim, 1);
        eigenTemp.setZero();

        // iterate over the vector and multiply the corresponding row of the matrix by the vecIter value
        #pragma omp parallel for schedule(dynamic)
        for (int i = 0; i < vec.rows(); ++i) {
            if (vec(i) == 0) continue;
            for (typename SparseMatrix<T, indexT, 2, columnMajor>::InnerIterator matIter(*this, i); matIter; ++matIter) {
                eigenTemp.coeffRef(matIter.row()) += matIter.value() * vec(i);
            }
        }
        return eigenTemp;
    }

    // Matrix Vector Multiplication (CSF::SparseMatrix::Vector * CSF::SparseMatrix)
    template <typename T, typename indexT, bool columnMajor>
    inline Eigen::VectorXd SparseMatrix<T, indexT, 2, columnMajor>::vectorMultiply(typename SparseMatrix<T, indexT, 2, columnMajor>::Vector& vec) {
        if (vec.length() != outerDim)
            throw std::invalid_argument("The vector must be the same size as the number of columns in the matrix!");

        Eigen::Matrix<T, -1, 1> newVector = Eigen::Matrix<T, -1, 1>::Zero(innerDim, 1);

        //#pragma omp parallel for schedule(dynamic)
        for (typename SparseMatrix<T, indexT, 2, columnMajor>::InnerIterator vecIter(vec); vecIter; ++vecIter) {
            for (typename SparseMatrix<T, indexT, 2, columnMajor>::InnerIterator matIter(*this, vecIter.row()); matIter; ++matIter) {
                newVector.coeffRef(matIter.row()) += matIter.value() * vecIter.value();
            }
        }
        return newVector;
    }

    //* BLAS Level 3 Routines *//

    // Matrix Vector Multiplication (CSF::SparseMatrix * Eigen::Matrix)
    template <typename T, typename indexT, bool columnMajor>
    inline Eigen::Matrix<T, -1, -1> SparseMatrix<T, indexT, 2, columnMajor>::matrixMultiply(Eigen::Matrix<T, -1, -1>& mat) {
        // check that the matrix is the correct size
        if (mat.rows() != outerDim)
            throw std::invalid_argument("The left matrix must be the same size as the number of columns in the right matrix!");

        Eigen::Matrix<T, -1, -1> newMatrix = Eigen::Matrix<T, -1, -1>::Zero(innerDim, mat.cols());

        //pragma omp parallel for schedule(dynamic)
        for (int col = 0; col < mat.cols(); col++) {
            for (int row = 0; row < mat.rows(); row++) {
                for (typename SparseMatrix<T, indexT, 2, columnMajor>::InnerIterator matIter(*this, row); matIter; ++matIter) {
                    newMatrix.coeffRef(matIter.row(), col) += matIter.value() * mat(row, col);
                }
            }
        }
        return newMatrix;
    }

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
    inline std::vector<T>  SparseMatrix<T, indexT, 2, columnMajor>::maxRowCoeff() {
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

} // namespace CSF