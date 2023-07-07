/**
 * @file CSF1_BLAS.hpp
 * @author Skyler Ruiter and Seth Wolfgang
 * @brief BLAS for CSF1 Sparse Matrices (WIP)
 * @version 0.1
 * @date 2023-07-03
 */

#pragma once

namespace CSF {

    //* BLAS Level 1 Routines *//

    // Scalar Multiply
    template <typename T, typename indexT, bool columnMajor>
    inline CSF::SparseMatrix<T, indexT, 1, columnMajor> SparseMatrix<T, indexT, 1, columnMajor>::scalarMultiply(T scalar) {
        // Deep copy the matrix
        CSF::SparseMatrix<T, indexT, 1, columnMajor> newMatrix(*this);

        // else use the iterator
        #pragma omp parallel for schedule(dynamic)
        for (uint32_t i = 0; i < this->outerDim; ++i) {
            for (typename SparseMatrix<T, indexT, 1, columnMajor>::InnerIterator it(newMatrix, i); it; ++it) {
                if (it.isNewRun()) {
                    it.coeff(it.value() * scalar);
                }
            }
        }
        return newMatrix;
    }

    // In Place Scalar Multiply
    template <typename T, typename indexT, bool columnMajor>
    inline void SparseMatrix<T, indexT, 1, columnMajor>::inPlaceScalarMultiply(T scalar) {
        // else use the iterator
        #pragma omp parallel for schedule(dynamic)
        for (int i = 0; i < nnz; i++) {
            vals[i] *= scalar;
        }
            
    }

    //* BLAS Level 2 Routines *//

    // Matrix Vector Multiplication (Eigen::VectorXd * CSF::SparseMatrix)
    template <typename T, typename indexT, bool columnMajor>
    inline Eigen::VectorXd SparseMatrix<T, indexT, 1, columnMajor>::vectorMultiply(Eigen::VectorXd& vec) {
        // check that the vector is the correct size
        assert(vec.rows() == outerDim && "The vector must be the same size as the number of columns in the matrix!");

        Eigen::Matrix<T, -1, 1> eigenTemp(innerDim, 1);
        eigenTemp.setZero();

        // iterate over the vector and multiply the corresponding row of the matrix by the vecIter value
        #pragma omp parallel for schedule(dynamic)
        for (int i = 0; i < vec.rows(); ++i) {
            if (vec(i) == 0) continue;
            for (typename SparseMatrix<T, indexT, 1, columnMajor>::InnerIterator matIter(*this, i); matIter; ++matIter) {
                eigenTemp.coeffRef(matIter.row()) += matIter.value() * vec(i);
            }
        }
        return eigenTemp;
    }

    // Matrix Vector Multiplication (CSF::SparseMatrix::Vector * CSF::SparseMatrix)
    template <typename T, typename indexT, bool columnMajor>
    inline Eigen::VectorXd SparseMatrix<T, indexT, 1, columnMajor>::vectorMultiply(typename SparseMatrix<T, indexT, 1, columnMajor>::Vector& vec) {
        if (vec.length() != outerDim)
            throw std::invalid_argument("The vector must be the same size as the number of columns in the matrix!");

        Eigen::Matrix<T, -1, 1> newVector = Eigen::Matrix<T, -1, 1>::Zero(innerDim, 1);

        // #pragma omp parallel for schedule(dynamic)
        for (typename SparseMatrix<T, indexT, 1, columnMajor>::InnerIterator vecIter(vec); vecIter; ++vecIter) {
            for (typename SparseMatrix<T, indexT, 1, columnMajor>::InnerIterator matIter(*this, vecIter.row()); matIter; ++matIter) {
                newVector.coeffRef(matIter.row()) += matIter.value() * vecIter.value();
            }
        }
        return newVector;
    }

    //* BLAS Level 3 Routines *//

    // Matrix Vector Multiplication (CSF::SparseMatrix * Eigen::Matrix)
    template <typename T, typename indexT, bool columnMajor>
    inline Eigen::Matrix<T, -1, -1> SparseMatrix<T, indexT, 1, columnMajor>::matrixMultiply(Eigen::Matrix<T, -1, -1>& mat) {
        // check that the matrix is the correct size
        if (mat.rows() != outerDim)
            throw std::invalid_argument("The left matrix must be the same size as the number of columns in the right matrix!");

        Eigen::Matrix<T, -1, -1> newMatrix = Eigen::Matrix<T, -1, -1>::Zero(innerDim, mat.cols());

        #pragma omp parallel for schedule(dynamic)
        for (int col = 0; col < mat.cols(); col++) {
            for (int row = 0; row < mat.rows(); row++) {
                for (typename SparseMatrix<T, indexT, 1, columnMajor>::InnerIterator matIter(*this, row); matIter; ++matIter) {
                    newMatrix.coeffRef(matIter.row(), col) += matIter.value() * mat(row, col);
                }
            }
        }
        return newMatrix;
    }

    //* Other Matrix Calculations *//

    template <typename T, typename indexT, bool columnMajor>
    inline std::vector<T> SparseMatrix<T, indexT, 1, columnMajor>::outerSum() {
        std::vector<T> outerSum = std::vector<T>(outerDim);

        #pragma omp parallel for schedule(dynamic)
        for (int i = 0; i < outerDim; i++) {
            for (typename SparseMatrix<T, indexT, 1, columnMajor>::InnerIterator it(*this, i); it; ++it) {
                outerSum[i] += it.value();
            }
        }
        return outerSum;
    }


    template <typename T, typename indexT, bool columnMajor>
    inline std::vector<T> SparseMatrix<T, indexT, 1, columnMajor>::innerSum() {
        std::vector<T> innerSum = std::vector<T>(innerDim);

        #pragma omp parallel for schedule(dynamic)
        for (int i = 0; i < outerDim; i++) {
            for (typename SparseMatrix<T, indexT, 1, columnMajor>::InnerIterator it(*this, i); it; ++it) {
                innerSum[it.row()] += it.value();
            }
        }
        return innerSum;
    }

    //! Make aware of storage order?
    template<typename T, typename indexT, bool columnMajor>
    inline std::vector<T> SparseMatrix<T, indexT, 1, columnMajor>::maxColCoeff() {
        std::vector<T> maxCoeff = std::vector<T>(innerDim);

        #pragma omp parallel for schedule(dynamic)
        for (int i = 0; i < outerDim; i++) {
            for (typename SparseMatrix<T, indexT, 1, columnMajor>::InnerIterator it(*this, i); it; ++it) {
                if (it.value() > maxCoeff[i]) {
                    maxCoeff[i] = it.value();
                }
            }
        }
        return maxCoeff;
    }

    template<typename T, typename indexT, bool columnMajor>
    inline std::vector<T>  SparseMatrix<T, indexT, 1, columnMajor>::maxRowCoeff() {
        std::vector<T> maxCoeff = std::vector<T>(innerDim);

        #pragma omp parallel for schedule(dynamic)
        for (int i = 0; i < outerDim; i++) {
            for (typename SparseMatrix<T, indexT, 1, columnMajor>::InnerIterator it(*this, i); it; ++it) {
                if (it.value() > maxCoeff[it.row()]) {
                    maxCoeff[it.row()] = it.value();
                }
            }
        }
        return maxCoeff;
    }

    template<typename T, typename indexT, bool columnMajor>
    inline std::vector<T> SparseMatrix<T, indexT, 1, columnMajor>::minColCoeff() {
        std::vector<T> minCoeff = std::vector<T>(innerDim);

        #pragma omp parallel for schedule(dynamic)
        for (int i = 0; i < outerDim; i++) {
            for (typename SparseMatrix<T, indexT, 1, columnMajor>::InnerIterator it(*this, i); it; ++it) {
                if (it.value() < minCoeff[i]) {
                    minCoeff[i] = it.value();
                }
            }
        }
        return minCoeff;
    }

    template<typename T, typename indexT, bool columnMajor>
    inline std::vector<T> SparseMatrix<T, indexT, 1, columnMajor>::minRowCoeff() {
        std::vector<T> minCoeff = std::vector<T>(innerDim);
        memset(minCoeff.data(), 0xF, innerDim * sizeof(T));

        #pragma omp parallel for schedule(dynamic)
        for (int i = 0; i < outerDim; i++) {
            for (typename SparseMatrix<T, indexT, 1, columnMajor>::InnerIterator it(*this, i); it; ++it) {
                if (it.value() < minCoeff[it.row()]) {
                    minCoeff[it.row()] = it.value();
                }
            }
        }
        return minCoeff;
    }

    template <typename T, typename indexT, bool columnMajor>
    inline T SparseMatrix<T, indexT, 1, columnMajor>::trace() {
        assert(innerDim == outerDim && "Trace is only defined for square matrices!");

        T trace = 0;
        #pragma omp parallel for schedule(dynamic)
        for (int i = 0; i < outerDim; i++) {
            for (typename SparseMatrix<T, indexT, 1, columnMajor>::InnerIterator it(*this, i); it; ++it) {
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

    template <typename T, typename indexT, bool columnMajor>
    inline T SparseMatrix<T, indexT, 1, columnMajor>::sum() {
        T sum = 0;

        #pragma omp parallel for schedule(dynamic)
        for (int i = 0; i < outerDim; i++) {
            for (typename SparseMatrix<T, indexT, 1, columnMajor>::InnerIterator it(*this, i); it; ++it) {
                sum += it.value();
            }
        }
        return sum;
    }

    template <typename T, typename indexT, bool columnMajor>
    inline double SparseMatrix<T, indexT, 1, columnMajor>::norm() {
        double norm = 0;

        #pragma omp parallel for schedule(dynamic)
        for (int i = 0; i < outerDim; i++) {
            for (typename SparseMatrix<T, indexT, 1, columnMajor>::InnerIterator it(*this, i); it; ++it) {
                norm += it.value() * it.value();
            }
        }
        return sqrt(norm);
    }

    template <typename T, typename indexT, bool columnMajor>
    inline double SparseMatrix<T, indexT, 1, columnMajor>::vectorLength(uint32_t col) {
        double norm = 0;

        // #pragma omp parallel for schedule(dynamic)
        for (typename SparseMatrix<T, indexT, 1, columnMajor>::InnerIterator it(*this, col); it; ++it) {
            norm += it.value() * it.value();
        }
        return sqrt(norm);
    }

}