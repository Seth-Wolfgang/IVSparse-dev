/**
 * @file IVCSC_BLAS.hpp
 * @author Skyler Ruiter and Seth Wolfgang
 * @brief BLAS Routines and Other Matrix Calculations for IVCSC Sparse Matrices
 * @version 0.1
 * @date 2023-07-03
 */

#pragma once

namespace IVSparse {

    //* BLAS Level 1 Routines *//

    // Scalar Multiply
    template <typename T, bool columnMajor>
    inline IVSparse::IVCSC<T, columnMajor> IVCSC<T, columnMajor>::scalarMultiply(T scalar) {
        // Deep copy the matrix
        IVSparse::IVCSC<T, columnMajor> newMatrix(*this);

        // else use the iterator
        #ifdef IVSPARSE_HAS_OPENMP
        #pragma omp parallel for
        #endif
        for (uint32_t i = 0; i < this->outerDim; ++i) {
            for (typename IVCSC<T, columnMajor>::InnerIterator it(newMatrix, i); it; ++it) {
                if (it.isNewRun()) {
                    it.coeff(it.value() * scalar);
                }
            }
        }
        return newMatrix;
    }

    // In Place Scalar Multiply
    template <typename T, bool columnMajor>
    inline void IVCSC<T, columnMajor>::inPlaceScalarMultiply(T scalar) {

        // else use the iterator
        #ifdef IVSPARSE_HAS_OPENMP
        #pragma omp parallel for
        #endif
        for (uint32_t i = 0; i < outerDim; ++i) {
            for (typename IVCSC<T, columnMajor>::InnerIterator it(*this, i); it; ++it) {
                if (it.isNewRun()) {
                    it.coeff(it.value() * scalar);
                }
            }
        }
    }

    //* BLAS Level 2 Routines *//

    // Matrix Vector Multiplication (Eigen::VectorXd * IVSparse::IVCSC)
    template <typename T, bool columnMajor>
    inline Eigen::Matrix<T, -1, 1> IVCSC<T, columnMajor>::vectorMultiply(Eigen::Matrix<T, -1, 1>& vec) {

        #ifdef IVSPARSE_DEBUG
        // check that the vector is the correct size
        assert(vec.rows() == outerDim &&
               "The vector must be the same size as the number of columns in the "
               "matrix!");
        #endif

        Eigen::Matrix<T, -1, 1> eigenTemp = Eigen::Matrix<T, -1, 1>::Zero(innerDim, 1);

        // iterate over the vector and multiply the corresponding row of the matrix by the vecIter value

        for (uint32_t i = 0; i < outerDim; i++) {
            for (typename IVCSC<T, columnMajor>::InnerIterator matIter(*this, i); matIter; ++matIter) {
                eigenTemp(matIter.row()) += vec(matIter.col()) * matIter.value();
            }
        }
        return eigenTemp;
    }

    //* BLAS Level 3 Routines *//
    // Matrix multiplication has been moved to the IVCSC_Operator.hpp file

    //* Other Matrix Calculations *//

    template <typename T, bool columnMajor>
    inline std::vector<T> IVCSC<T, columnMajor>::outerSum() {
        std::vector<T> outerSum = std::vector<T>(outerDim);

        #ifdef IVSPARSE_HAS_OPENMP
        #pragma omp parallel for
        #endif
        for (int i = 0; i < outerDim; i++) {
            for (typename IVCSC<T, columnMajor>::InnerIterator it(*this, i); it; ++it) {
                outerSum[i] += it.value();
            }
        }
        return outerSum;
    }

    template <typename T, bool columnMajor>
    inline std::vector<T> IVCSC<T, columnMajor>::innerSum() {
        std::vector<T> innerSum = std::vector<T>(innerDim);

        #ifdef IVSPARSE_HAS_OPENMP
        #pragma omp parallel for
        #endif
        for (int i = 0; i < outerDim; i++) {
            for (typename IVCSC<T, columnMajor>::InnerIterator it(*this, i); it; ++it) {
                innerSum[it.row()] += it.value();
            }
        }
        return innerSum;
    }

    template <typename T, bool columnMajor>
    inline std::vector<T> IVCSC<T, columnMajor>::maxColCoeff() {

        std::vector<T> maxCoeff = std::vector<T>(innerDim);

        #ifdef IVSPARSE_HAS_OPENMP
        #pragma omp parallel for
        #endif
        for (int i = 0; i < outerDim; i++) {
            for (typename IVCSC<T, columnMajor>::InnerIterator it(*this, i); it; ++it) {
                if (it.value() > maxCoeff[i]) {
                    maxCoeff[i] = it.value();
                }
            }
        }
        return maxCoeff;
    }

    template <typename T, bool columnMajor>
    inline std::vector<T> IVCSC<T, columnMajor>::maxRowCoeff() {

        std::vector<T> maxCoeff = std::vector<T>(innerDim);

        #ifdef IVSPARSE_HAS_OPENMP
        #pragma omp parallel for
        #endif
        for (int i = 0; i < outerDim; i++) {
            for (typename IVCSC<T, columnMajor>::InnerIterator it(*this, i); it; ++it) {
                if (it.value() > maxCoeff[it.row()]) {
                    maxCoeff[it.row()] = it.value();
                }
            }
        }
        return maxCoeff;
    }

    template <typename T, bool columnMajor>
    inline std::vector<T> IVCSC<T, columnMajor>::minColCoeff() {

        std::vector<T> minCoeff = std::vector<T>(innerDim);

        #ifdef IVSPARSE_HAS_OPENMP
        #pragma omp parallel for
        #endif
        for (int i = 0; i < outerDim; i++) {
            for (typename IVCSC<T, columnMajor>::InnerIterator it(*this, i); it; ++it) {
                if (it.value() < minCoeff[i]) {
                    minCoeff[i] = it.value();
                }
            }
        }
        return minCoeff;
    }

    template <typename T, bool columnMajor>
    inline std::vector<T> IVCSC<T, columnMajor>::minRowCoeff() {
        std::vector<T> minCoeff = std::vector<T>(innerDim);
        memset(minCoeff.data(), 0xF, innerDim * sizeof(T));

        #ifdef IVSPARSE_HAS_OPENMP
        #pragma omp parallel for
        #endif
        for (int i = 0; i < outerDim; i++) {
            for (typename IVCSC<T, columnMajor>::InnerIterator it(*this, i); it; ++it) {
                if (it.value() < minCoeff[it.row()]) {
                    minCoeff[it.row()] = it.value();
                }
            }
        }
        return minCoeff;
    }

    template <typename T, bool columnMajor>
    template<typename T2, std::enable_if_t<std::is_integral<T2>::value, bool>>
    inline int64_t IVCSC<T, columnMajor>::trace() {

        #ifdef IVSPARSE_DEBUG
        assert(innerDim == outerDim && "Trace is only defined for square matrices!");
        #endif

        int64_t trace = 0;
        for (int i = 0; i < outerDim; i++) {
            for (typename IVCSC<T, columnMajor>::InnerIterator it(*this, i); it; ++it) {
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

    template <typename T, bool columnMajor>
    template<typename T2, std::enable_if_t<std::is_floating_point<T2>::value, bool>>
    inline double IVCSC<T, columnMajor>::trace() {

        #ifdef IVSPARSE_DEBUG
        assert(innerDim == outerDim && "Trace is only defined for square matrices!");
        #endif

        double trace = 0;
        for (int i = 0; i < outerDim; i++) {
            for (typename IVCSC<T, columnMajor>::InnerIterator it(*this, i); it; ++it) {
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

    template <typename T, bool columnMajor>
    template<typename T2, std::enable_if_t<std::is_integral<T2>::value, bool>>
    inline int64_t IVCSC<T, columnMajor>::sum() {
        int64_t sum = 0;

        #ifdef IVSPARSE_HAS_OPENMP
        #pragma omp parallel for reduction(+ : sum)
        #endif
        for (int i = 0; i < outerDim; i++) {
            for (typename IVCSC<T, columnMajor>::InnerIterator it(*this, i); it; ++it) {
                sum += it.value();
            }
        }
        return sum;
    }

    template <typename T, bool columnMajor>
    template<typename T2, std::enable_if_t<std::is_floating_point<T2>::value, bool>>
    inline double IVCSC<T, columnMajor>::sum() {
        double sum = 0;

        #ifdef IVSPARSE_HAS_OPENMP
        #pragma omp parallel for reduction(+ : sum)
        #endif
        for (int i = 0; i < outerDim; i++) {
            for (typename IVCSC<T, columnMajor>::InnerIterator it(*this, i); it; ++it) {
                sum += it.value();
            }
        }
        return sum;
    }

    template <typename T, bool columnMajor>
    inline double IVCSC<T, columnMajor>::norm() {
        double norm = 0;

        #ifdef IVSPARSE_HAS_OPENMP
        #pragma omp parallel for reduction(+ : norm)
        #endif
        for (int i = 0; i < outerDim; i++) {
            for (typename IVCSC<T, columnMajor>::InnerIterator it(*this, i);
                 it; ++it) {
                norm += it.value() * it.value();
            }
        }
        return sqrt(norm);
    }

    template <typename T, bool columnMajor>
    inline double IVCSC<T, columnMajor>::vectorLength(uint32_t col) {

        #ifdef IVSPARSE_DEBUG
        assert(col < outerDim && col >= 0 && "The column index is out of bounds!");
        #endif

        double norm = 0;

        for (typename IVCSC<T, columnMajor>::InnerIterator it(*this, col);
             it; ++it) {
            norm += it.value() * it.value();
        }
        return sqrt(norm);
    }

}  // namespace IVSparse