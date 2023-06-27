/**
 * @file CSF_BLAS.hpp
 * @author Skyler Ruiter and Seth Wolfgang
 * @brief File for BLAS level routines and other matrix calculations.
 * @version 0.1
 * @date 2023-06-23
 */

#pragma once

namespace CSF {

    //* BLAS Level 1 Routines *//

    // Scalar Multiply
    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    inline CSF::SparseMatrix<T, indexT, compressionLevel, columnMajor> SparseMatrix<T, indexT, compressionLevel, columnMajor>::scalarMultiply(T scalar) {

        // Deep copy the matrix
        CSF::SparseMatrix<T, indexT, compressionLevel, columnMajor> newMatrix(*this);

        // If performance vectors are active use them for the scalar multiplication
        if constexpr (compressionLevel == 2) {
            #pragma omp parallel for schedule(dynamic)
            for (int i = 0; i < outerDim; i++) {
                for (int j = 0; j < valueArraySize[i]; j++) {
                    newMatrix.valueArray[i][j] *= scalar;
                }
            }
            return newMatrix;
        }

        // else use the iterator
        #pragma omp parallel for schedule(dynamic)
        for (uint32_t i = 0; i < this->outerDim; ++i) {
            for (typename SparseMatrix<T, indexT, compressionLevel, columnMajor>::InnerIterator it(newMatrix, i); it; ++it) {
                if (it.isNewRun()) {
                    it.coeff(it.value() * scalar);
                }
            }
        }
        return newMatrix;
    }

    // In Place Scalar Multiply
    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    inline void SparseMatrix<T, indexT, compressionLevel, columnMajor>::inPlaceScalarMultiply(T scalar) {

        // if performance vectors are active use them for the scalar multiplication
        if constexpr (compressionLevel == 2) {

            #pragma omp parallel for schedule(dynamic)
            for (int i = 0; i < outerDim; i++) {
                for (int j = 0; j < valueArraySize[i]; j++) {
                    valueArray[i][j] *= scalar;
                }
            }
            return;
        }

        // else use the iterator
        #pragma omp parallel for schedule(dynamic)
        for (uint32_t i = 0; i < outerDim; ++i) {
            for (typename SparseMatrix<T, indexT, compressionLevel, columnMajor>::InnerIterator it(*this, i); it; ++it) {
                if (it.isNewRun()) {
                    it.coeff(it.value() * scalar);
                }
            }
        }
    }

    //* BLAS Level 2 Routines *//

    // Matrix Vector Multiplication (Eigen::VectorXd * CSF::SparseMatrix)
    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    inline Eigen::VectorXd SparseMatrix<T, indexT, compressionLevel, columnMajor>::vectorMultiply(Eigen::VectorXd& vec) {
        // check that the vector is the correct size
        assert(vec.rows() == outerDim && "The vector must be the same size as the number of columns in the matrix!");

        Eigen::Matrix<T, -1, 1> eigenTemp(innerDim, 1);
        eigenTemp.setZero();

        // iterate over the vector and multiply the corresponding row of the matrix by the vecIter value
        #pragma omp parallel for schedule(dynamic)
        for (int i = 0; i < vec.rows(); ++i) {
            if (vec(i) == 0) continue;
            for (typename SparseMatrix<T, indexT, compressionLevel, columnMajor>::InnerIterator matIter(*this, i); matIter; ++matIter) {
                eigenTemp.coeffRef(matIter.row()) += matIter.value() * vec(i);
            }
        }
        return eigenTemp;
    }

    // Matrix Vector Multiplication (CSF::SparseMatrix::Vector * CSF::SparseMatrix)
    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    inline Eigen::VectorXd SparseMatrix<T, indexT, compressionLevel, columnMajor>::vectorMultiply(typename SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector& vec) {
        if (vec.length() != outerDim)
            throw std::invalid_argument("The vector must be the same size as the number of columns in the matrix!");

        Eigen::Matrix<T, -1, 1> newVector = Eigen::Matrix<T, -1, 1>::Zero(innerDim, 1);

        //#pragma omp parallel for schedule(dynamic)
        for (typename SparseMatrix<T, indexT, compressionLevel, columnMajor>::InnerIterator vecIter(vec); vecIter; ++vecIter) {
            for (typename SparseMatrix<T, indexT, compressionLevel, columnMajor>::InnerIterator matIter(*this, vecIter.row()); matIter; ++matIter) {
                newVector.coeffRef(matIter.row()) += matIter.value() * vecIter.value();
            }
        }
        return newVector;
    }

    //* BLAS Level 3 Routines *//

    // Matrix Vector Multiplication (CSF::SparseMatrix * Eigen::Matrix)
    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    inline Eigen::Matrix<T, -1, -1> SparseMatrix<T, indexT, compressionLevel, columnMajor>::matrixMultiply(Eigen::Matrix<T, -1, -1>& mat) {
        // check that the matrix is the correct size
        if (mat.rows() != outerDim)
            throw std::invalid_argument("The left matrix must be the same size as the number of columns in the right matrix!");

        Eigen::Matrix<T, -1, -1> newMatrix = Eigen::Matrix<T, -1, -1>::Zero(innerDim, mat.cols());

        //pragma omp parallel for schedule(dynamic)
        for (int col = 0; col < mat.cols(); col++) {
            for (int row = 0; row < mat.rows(); row++) {
                for (typename SparseMatrix<T, indexT, compressionLevel, columnMajor>::InnerIterator matIter(*this, row); matIter; ++matIter) {
                    newMatrix.coeffRef(matIter.row(), col) += matIter.value() * mat(row, col);
                }
            }
        }
        return newMatrix;
    }

    //* Other Matrix Calculations *//

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    inline std::vector<T> SparseMatrix<T, indexT, compressionLevel, columnMajor>::outerSum() {
        std::vector<T> outerSum = std::vector<T>(outerDim);

        if constexpr (compressionLevel == 2) {

            #pragma omp parallel for schedule(dynamic)
            for (int i = 0; i < outerDim; i++) {
                for (int j = 0; j < valueArraySize[i]; j++) {
                    outerSum[i] += valueArray[i][j] * countsArray[i][j];
                }
            }
            return outerSum;
        }

        #pragma omp parallel for schedule(dynamic)
        for (int i = 0; i < outerDim; i++) {
            for (typename SparseMatrix<T, indexT, compressionLevel, columnMajor>::InnerIterator it(*this, i); it; ++it) {
                outerSum[i] += it.value();
            }
        }
        return outerSum;
    }


    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    inline std::vector<T> SparseMatrix<T, indexT, compressionLevel, columnMajor>::innerSum() {
        std::vector<T> innerSum = std::vector<T>(innerDim);

        #pragma omp parallel for schedule(dynamic)
        for (int i = 0; i < outerDim; i++) {
            for (typename SparseMatrix<T, indexT, compressionLevel, columnMajor>::InnerIterator it(*this, i); it; ++it) {
                innerSum[it.row()] += it.value();
            }
        }
        return innerSum;
    }

    //! Make aware of storage order?
    template<typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    inline std::vector<T> SparseMatrix<T, indexT, compressionLevel, columnMajor>::maxColCoeff() {
        std::vector<T> maxCoeff = std::vector<T>(innerDim);

        if constexpr (compressionLevel == 2) {
            #pragma omp parallel for schedule(dynamic)
            for (int i = 0; i < outerDim; i++) {
                for (int j = 0; j < valueArraySize[i]; j++) {
                    if (valueArray[i][j] > maxCoeff[i]) {
                        maxCoeff[i] = valueArray[i][j];
                    }
                }
            }
            return maxCoeff;
        }

        #pragma omp parallel for schedule(dynamic)
        for (int i = 0; i < outerDim; i++) {
            for (typename SparseMatrix<T, indexT, compressionLevel, columnMajor>::InnerIterator it(*this, i); it; ++it) {
                if (it.value() > maxCoeff[i]) {
                    maxCoeff[i] = it.value();
                }
            }
        }
        return maxCoeff;
    }

    template<typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    inline std::vector<T>  SparseMatrix<T, indexT, compressionLevel, columnMajor>::maxRowCoeff() {
        std::vector<T> maxCoeff = std::vector<T>(innerDim);

        #pragma omp parallel for schedule(dynamic)
        for (int i = 0; i < outerDim; i++) {
            for (typename SparseMatrix<T, indexT, compressionLevel, columnMajor>::InnerIterator it(*this, i); it; ++it) {
                if (it.value() > maxCoeff[it.row()]) {
                    maxCoeff[it.row()] = it.value();
                }
            }
        }
        return maxCoeff;
    }

    template<typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    inline std::vector<T> SparseMatrix<T, indexT, compressionLevel, columnMajor>::minColCoeff() {
        std::vector<T> minCoeff = std::vector<T>(innerDim);

        if constexpr (compressionLevel == 2) {
            #pragma omp parallel for schedule(dynamic)
            for (int i = 0; i < outerDim; i++) {
                for (int j = 0; j < valueArraySize[i]; j++) {
                    if (valueArray[i][j] < minCoeff[i]) {
                        minCoeff[i] = valueArray[i][j];
                    }
                }
            }
            return minCoeff;
        }

        for (int i = 0; i < outerDim; i++) {
            for (typename SparseMatrix<T, indexT, compressionLevel, columnMajor>::InnerIterator it(*this, i); it; ++it) {
                if (it.value() < minCoeff[i]) {
                    minCoeff[i] = it.value();
                }
            }
        }
        return minCoeff;
    }

    template<typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    inline std::vector<T> SparseMatrix<T, indexT, compressionLevel, columnMajor>::minRowCoeff() {
        std::vector<T> minCoeff = std::vector<T>(innerDim);
        memset(minCoeff.data(), 0xF, innerDim * sizeof(T));

        for (int i = 0; i < outerDim; i++) {
            for (typename SparseMatrix<T, indexT, compressionLevel, columnMajor>::InnerIterator it(*this, i); it; ++it) {
                if (it.value() < minCoeff[it.row()]) {
                    minCoeff[it.row()] = it.value();
                }
            }
        }
        return minCoeff;
    }

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    inline T SparseMatrix<T, indexT, compressionLevel, columnMajor>::trace() {
        assert(innerDim == outerDim && "Trace is only defined for square matrices!");

        T trace = 0;
        for (int i = 0; i < outerDim; i++) {
            for (typename SparseMatrix<T, indexT, compressionLevel, columnMajor>::InnerIterator it(*this, i); it; ++it) {
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

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    inline T SparseMatrix<T, indexT, compressionLevel, columnMajor>::sum() {
        T sum = 0;

        if constexpr (compressionLevel == 2) {
            #pragma omp parallel for schedule(dynamic)
            for (int i = 0; i < outerDim; i++) {
                for (int j = 0; j < valueArraySize[i]; j++) {
                    sum += valueArray[i][j] * countsArray[i][j];
                }
            }
            return sum;
        }

        for (int i = 0; i < outerDim; i++) {
            for (typename SparseMatrix<T, indexT, compressionLevel, columnMajor>::InnerIterator it(*this, i); it; ++it) {
                sum += it.value();
            }
        }
        return sum;
    }

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    inline double SparseMatrix<T, indexT, compressionLevel, columnMajor>::norm() {
        double norm = 0;

        if constexpr (compressionLevel == 2) {
            #pragma omp parallel for schedule(dynamic)
            for (int i = 0; i < outerDim; i++) {
                for (int j = 0; j < valueArraySize[i]; j++) {
                    norm += valueArray[i][j] * valueArray[i][j] * countsArray[i][j];
                }
            }
            return sqrt(norm);
        }

        for (int i = 0; i < outerDim; i++) {
            for (typename SparseMatrix<T, indexT, compressionLevel, columnMajor>::InnerIterator it(*this, i); it; ++it) {
                norm += it.value() * it.value();
            }
        }
        return sqrt(norm);
    }

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    inline double SparseMatrix<T, indexT, compressionLevel, columnMajor>::vectorLength(uint32_t col) {
        double norm = 0;

        if constexpr (compressionLevel == 2) {
            #pragma omp parallel for schedule(dynamic)
            for (int i = 0; i < valueArraySize[col]; i++) {
                norm += valueArray[col][i] * valueArray[col][i] * countsArray[col][i];
            }
            return sqrt(norm);
        }

        for (typename SparseMatrix<T, indexT, compressionLevel, columnMajor>::InnerIterator it(*this, col); it; ++it) {
            norm += it.value() * it.value();
        }
        return sqrt(norm);

    }
}
