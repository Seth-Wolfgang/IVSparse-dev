/**
 * @file VCSC_BLAS.hpp
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
    inline IVSparse::VCSC<T, indexT, columnMajor> VCSC<T, indexT, columnMajor>::scalarMultiply(T scalar) {
        // Deep copy the matrix
        IVSparse::VCSC<T, indexT, columnMajor> newMatrix(*this);

        // If performance vectors are active use them for the scalar multiplication
        #ifdef IVSPARSE_HAS_OPENMP
        #pragma omp parallel for
        #endif
        for (int i = 0; i < outerDim; i++) {
            for (int j = 0; j < valueSizes[i]; j++) {
                newMatrix.values[i][j] *= scalar;
            }
        }
        return newMatrix;
    }

    // In Place Scalar Multiply
    template <typename T, typename indexT, bool columnMajor>
    inline void VCSC<T, indexT, columnMajor>::inPlaceScalarMultiply(T scalar) {
        // if performance vectors are active use them for the scalar multiplication
        #ifdef IVSPARSE_HAS_OPENMP
        #pragma omp parallel for
        #endif
        for (int i = 0; i < outerDim; i++) {
            for (int j = 0; j < valueSizes[i]; j++) {
                values[i][j] *= scalar;
            }
        }
    }

    //* BLAS Level 2 Routines *//

    // Matrix Vector Multiplication (IVSparse::SparseMatrix * Eigen::Vector)
    template <typename T, typename indexT, bool columnMajor>
    inline Eigen::Matrix<T, -1, 1> VCSC<T, indexT, columnMajor>::vectorMultiply(Eigen::Matrix<T, -1, 1>& vec) {

        #ifdef IVSPARSE_DEBUG
        // check that the vector is the correct size
        assert(vec.rows() == outerDim &&
               "The vector must be the same size as the number of columns in the "
               "matrix!");
        #endif

        Eigen::Matrix<T, -1, 1> eigenTemp = Eigen::Matrix<T, -1, 1>::Zero(innerDim, 1);

        // iterate over the vector and multiply the corresponding row of the matrix by the vecIter value
        for (uint32_t i = 0; i < outerDim; i++) {
            for (typename VCSC<T, indexT, columnMajor>::InnerIterator matIter(*this, i); matIter; ++matIter) {
                eigenTemp(matIter.row()) += vec(matIter.col()) * matIter.value();
            }
        }
        return eigenTemp;
    }

    //* BLAS Level 3 Routines *//
    // Matrix multiplication has been moved to the VCSC_Operator.hpp file

    //* Other Matrix Calculations *//

    // Finds the Outer Sum of the Matrix
    template <typename T, typename indexT, bool columnMajor>
    inline Eigen::Matrix<T, -1, -1> VCSC<T, indexT, columnMajor>::colSum() {
        Eigen::Matrix<T, -1, -1> colSum = Eigen::Matrix<T, -1, -1>::Zero(numCols, 1);

        if constexpr (columnMajor) {
            #ifdef IVSPARSE_HAS_OPENMP
            #pragma omp parallel for
            #endif
            for (int i = 0; i < numCols; i++) {
                for (int j = 0; j < valueSizes[i]; j++) {
                    colSum(i, 0) += values[i][j] * counts[i][j];
                }
            }
            return colSum;
        }
        else {
            #ifdef IVSPARSE_HAS_OPENMP
            // #pragma omp parallel for
            #endif
            for (int i = 0; i < numRows; i++) {
                for (typename VCSC<T, indexT, columnMajor>::InnerIterator it(*this, i);it; ++it) {
                    colSum(it.col(), 0) += it.value();
                }
            }
            return colSum;
        }

    }

    // Finds the Inner Sum of the Matrix
    template <typename T, typename indexT, bool columnMajor>
    inline Eigen::Matrix<T, -1, -1> VCSC<T, indexT, columnMajor>::rowSum() {
        Eigen::Matrix<T, -1, -1> rowSum = Eigen::Matrix<T, -1, -1>::Zero(numRows, 1);

        if constexpr (columnMajor) {
            #ifdef IVSPARSE_HAS_OPENMP
            // #pragma omp parallel for
            #endif
            for (int i = 0; i < numCols; i++) {
                for (typename VCSC<T, indexT, columnMajor>::InnerIterator it(*this, i);it; ++it) {
                    rowSum(it.getIndex(), 0) += it.value();
                }
            }
            return rowSum;
        }
        else {
            #ifdef IVSPARSE_HAS_OPENMP
            #pragma omp parallel for
            #endif
            for (int i = 0; i < numRows; i++) {
                for (int j = 0; j < valueSizes[i]; j++) {
                    rowSum(i, 0) += values[i][j] * counts[i][j];
                }
            }
            return rowSum;
        }
    }


    template <typename T, typename indexT, bool columnMajor>
    inline Eigen::Matrix<T, -1, -1> VCSC<T, indexT, columnMajor>::max(int axis) {

        Eigen::Matrix<T, -1, -1> maxCoeff;

        // Axis 0 for col, Axis 1 for row. Like SciPy
        switch (axis) {
        case 0: // MAX COLUMN COEFFICIENTS

            // This is set to a singular column for caching purposes
            // This is transposed in the final return statement
            maxCoeff = Eigen::Matrix<T, -1, -1>::Constant(numCols, 1, std::numeric_limits<T>::min());

            #ifdef IVSPARSE_HAS_OPENMP
            // #pragma omp parallel for
            #endif
            for (int i = 0; i < outerDim; i++) {
                for (typename VCSC<T, indexT, columnMajor>::InnerIterator it(*this, i); it; ++it) {
                    if (it.value() > maxCoeff(it.col(), 0)) {
                        maxCoeff(it.col(), 0) = it.value();
                    }
                }
            }
            break;

        case 1: // MAX ROW COEFFICIENTS
            maxCoeff = Eigen::Matrix<T, -1, -1>::Constant(numRows, 1, std::numeric_limits<T>::min());

            #ifdef IVSPARSE_HAS_OPENMP
            // #pragma omp parallel for
            #endif
            for (int i = 0; i < outerDim; i++) {
                for (typename VCSC<T, indexT, columnMajor>::InnerIterator it(*this, i); it; ++it) {
                    if (it.value() > maxCoeff(it.row(), 0)) {
                        maxCoeff(it.row(), 0) = it.value();
                    }
                }
            }
            break;
        } // end switch

        // If the maxCoeff is still the initialized value, set it to 0
        for (int i = 0; i < maxCoeff.rows(); i++) 
            if (maxCoeff(i, 0) == std::numeric_limits<T>::min()) 
                maxCoeff(i, 0) = 0;
            
        
        if (!axis) {
            return maxCoeff.transpose();
        }
        else {
            return maxCoeff;
        }
    }

    template <typename T, typename indexT, bool columnMajor>
    inline Eigen::Matrix<T, -1, -1> VCSC<T, indexT, columnMajor>::min(int axis) {

        Eigen::Matrix<T, -1, -1> minCoeff;

        // Axis 0 for col, Axis 1 for row. Like SciPy
        switch (axis) {
        case 0: // MIN COLUMN COEFFICIENTS
            minCoeff = Eigen::Matrix<T, -1, -1>::Constant(numCols, 1, std::numeric_limits<T>::max());

            #ifdef IVSPARSE_HAS_OPENMP
            // #pragma omp parallel for
            #endif
            for (int i = 0; i < outerDim; i++) {
                for (typename VCSC<T, indexT, columnMajor>::InnerIterator it(*this, i); it; ++it) {
                    if (it.value() < minCoeff(it.col(), 0)) {
                        minCoeff(it.col(), 0) = it.value();
                    }
                }
            }
            break;

        case 1: // MIN ROW COEFFICIENTS
            minCoeff = Eigen::Matrix<T, -1, -1>::Constant(numRows, 1, std::numeric_limits<T>::max());

            #ifdef IVSPARSE_HAS_OPENMP
            // #pragma omp parallel for
            #endif
            for (int i = 0; i < outerDim; i++) {
                for (typename VCSC<T, indexT, columnMajor>::InnerIterator it(*this, i); it; ++it) {
                    if (it.value() < minCoeff(it.row(), 0)) {
                        minCoeff(it.row(), 0) = it.value();
                    }
                }
            }
            break;
        } // end switch

        // reset any values that are still max
        for (int i = 0; i < minCoeff.rows(); i++) {
            if (minCoeff(i, 0) == std::numeric_limits<T>::max()) {
                minCoeff(i, 0) = 0;
            }
        }

        if (!axis) {
            return minCoeff.transpose();
        }
        else {
            return minCoeff;
        }

    }


    template <typename T, typename indexT, bool columnMajor>
    inline T VCSC<T, indexT, columnMajor>::max() {

        T maxCoeff = std::numeric_limits<T>::min();

        #ifdef IVSPARSE_HAS_OPENMP
        // #pragma omp parallel for
        #endif
        for (int i = 0; i < outerDim; i++) {
            for (typename VCSC<T, indexT, columnMajor>::InnerIterator it(*this, i); it; ++it) {
                if (it.value() > maxCoeff) {
                    maxCoeff = it.value();
                }
            }
        }

        if (maxCoeff == std::numeric_limits<T>::min())
            return 0;
        else
            return maxCoeff;
    }

    template <typename T, typename indexT, bool columnMajor>
    inline T VCSC<T, indexT, columnMajor>::min() {

        T minCoeff = std::numeric_limits<T>::max();

        #ifdef IVSPARSE_HAS_OPENMP
        // #pragma omp parallel for
        #endif
        for (int i = 0; i < outerDim; i++) {
            for (typename VCSC<T, indexT, columnMajor>::InnerIterator it(*this, i); it; ++it) {
                if (it.value() < minCoeff) {
                    minCoeff = it.value();
                }
            }
        }

        if (minCoeff == std::numeric_limits<T>::max() || (uint64_t)nnz < (uint64_t)numRows * (uint64_t)numCols)
            return 0;
        else
            return minCoeff;
    }


    template <typename T, typename indexT, bool columnMajor>
    template<typename T2, std::enable_if_t<std::is_integral<T2>::value, bool>>
    inline int64_t VCSC<T, indexT, columnMajor>::trace() {

        #ifdef IVSPARSE_DEBUG
        assert(innerDim == outerDim && "Trace is only defined for square matrices!");
        #endif

        int64_t trace = 0;
        for (int i = 0; i < outerDim; i++) {
            for (typename VCSC<T, indexT, columnMajor>::InnerIterator it(*this, i); it; ++it) {
                if (it.getIndex() == i) {
                    trace += it.value();
                }
                else if (it.getIndex() > i) {
                    continue;
                }
            }
        }
        return trace;
    }

    template <typename T, typename indexT, bool columnMajor>
    template<typename T2, std::enable_if_t<std::is_floating_point<T2>::value, bool>>
    inline double VCSC<T, indexT, columnMajor>::trace() {

        #ifdef IVSPARSE_DEBUG
        assert(innerDim == outerDim && "Trace is only defined for square matrices!");
        #endif

        double trace = 0;
        for (int i = 0; i < outerDim; i++) {
            for (typename VCSC<T, indexT, columnMajor>::InnerIterator it(*this, i); it; ++it) {
                if (it.getIndex() == i) {
                    trace += it.value();
                }
                else if (it.getIndex() > i) {
                    continue;
                }
            }
        }
        return trace;
    }

    // Calculates the sum of the matrix
    // template <typename std::is_floating_point<T>, typename indexT, bool columnMajor>
    // inline double VCSC<T, indexT, columnMajor>::sum() {
    //     T sum = 0;
    //     // std::vector<T> outerSum = this->outerSum();

    //     #ifdef IVSPARSE_HAS_OPENMP
    //     #pragma omp parallel for reduction(+ : sum)
    //     #endif
    //     for (int i = 0; i < outerDim; i++) {
    //         for (int j = 0; j < valueSizes[i]; j++) {
    //             sum += values[i][j] * counts[i][j];
    //         }
    //     }
    //     return sum;
    // }

    template <typename T, typename indexT, bool columnMajor>
    template<typename T2, std::enable_if_t<std::is_integral<T2>::value, bool>>
    inline int64_t VCSC<T, indexT, columnMajor>::sum() {
        int64_t sum = 0;

        #ifdef IVSPARSE_HAS_OPENMP
        #pragma omp parallel for reduction(+ : sum)
        #endif
        for (int i = 0; i < outerDim; i++) {
            for (int j = 0; j < valueSizes[i]; j++) {
                sum += static_cast<int64_t>(values[i][j]) * static_cast<int64_t>(counts[i][j]);
            }
        }
        return sum;
    }


    template <typename T, typename indexT, bool columnMajor>
    template<typename T2, std::enable_if_t<std::is_floating_point<T2>::value, bool>>
    inline double VCSC<T, indexT, columnMajor>::sum() {
        double sum = 0;

        #ifdef IVSPARSE_HAS_OPENMP
        #pragma omp parallel for reduction(+ : sum)
        #endif
        for (int i = 0; i < outerDim; i++) {
            for (int j = 0; j < valueSizes[i]; j++) {
                sum += values[i][j] * counts[i][j];
            }
        }
        return sum;
    }


    // Calculates the norm of the matrix
    template <typename T, typename indexT, bool columnMajor>
    inline double VCSC<T, indexT, columnMajor>::norm() {
        double norm = 0;

        #ifdef IVSPARSE_HAS_OPENMP
        #pragma omp parallel for reduction(+ : norm)
        #endif
        for (int i = 0; i < outerDim; i++) {
            for (int j = 0; j < valueSizes[i]; j++) {
                norm += values[i][j] * values[i][j] * counts[i][j];
            }
        }
        return sqrt(norm);
    }



    // Finds the length of a certain column
    // template <typename T, typename indexT, bool columnMajor>
    // inline double VCSC<T, indexT, columnMajor>::vectorLength(uint32_t col) {

    //     #ifdef IVSPARSE_DEBUG
    //     assert(col < outerDim && col >= 0 && "Column index out of bounds!");
    //     #endif

    //     double norm = 0;

    //     #ifdef IVSPARSE_HAS_OPENMP
    //     #pragma omp parallel for reduction(+ : norm)
    //     #endif
    //     for (int i = 0; i < valueSizes[col]; i++) {
    //         norm += values[col][i] * values[col][i] * counts[col][i];
    //     }
    //     return sqrt(norm);
    // }

}  // namespace IVSparse