#pragma once

namespace CSF {

    /**
     * @brief Computes the norm (or length) of the CSF::SparseMatrix::Vector
     * 
     * @tparam T
     * @tparam indexT
     * @tparam compressionLevel
     * @tparam columnMajor
     * 
     * @return double
    */

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    inline double SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector::norm() {
        double norm = 0;

        if constexpr (compressionLevel == 2) {
            if (performanceVecsOn) {
                #pragma omp parallel for schedule(dynamic)
                for (int i = 0; i < value_arr_size; i++) {
                    norm += value_arr[i] * value_arr[i] * counts_arr[i];
                }
                return sqrt(norm);
            }
        }
        for (typename SparseMatrix<T, indexT, compressionLevel, columnMajor>::InnerIterator it(*this); it; ++it) {
            norm += it.value() * it.value();
        }
        return sqrt(norm);
    }
    
        /**
     * @brief Computes the sum of all elements in the CSF::SparseMatrix::Vector
     * 
     * @tparam T
     * @tparam indexT
     * @tparam compressionLevel
     * @tparam columnMajor
     * 
     * @return double
    */

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    inline T SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector::sum() {
        double sum = 0;

        if constexpr (compressionLevel == 2) {
            if (performanceVecsOn) {
                #pragma omp parallel for schedule(dynamic)
                for (int i = 0; i < value_arr_size; i++) {
                    sum += value_arr[i] * counts_arr[i];
                }
                return sum;
            }
        }

        for (typename SparseMatrix<T, indexT, compressionLevel, columnMajor>::InnerIterator it(*this); it; ++it) {
            sum += it.value();
        }
        return sum;
    }

    /**
     * @brief In place scalar multiplication for CSF::SparseMatrix::Vector
     * 
     * @tparam T
     * @tparam indexT
     * @tparam compressionLevel
     * @tparam columnMajor
    */

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    void SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector::operator*=(T scalar) {

        if constexpr (compressionLevel == 2) {
            if (performanceVecsOn) {
                #pragma omp parallel for schedule(dynamic)
                for (int i = 0; i < value_arr_size; i++) {
                    value_arr[i] *= scalar;
                }
                return;
            }
        }

        for (typename SparseMatrix<T, indexT, compressionLevel, columnMajor>::InnerIterator it(*this); it; ++it) {
            if (it.isNewRun()) {
                it.coeff(it.value() * scalar);
            }
        }
    }


    /**
     * @brief Scalar multiplication for CSF::SparseMatrix::Vector
     * 
     * @tparam T
     * @tparam indexT
     * @tparam compressionLevel
     * @tparam columnMajor
     * 
     * @param scalar
     * 
     * @return CSF::SparseMatrix::Vector
    */

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    typename CSF::SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector::operator*(T scalar) {

        typename CSF::SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector newVector(*this);
        if constexpr (compressionLevel == 2) {
            if (performanceVecsOn) {
                #pragma omp parallel for schedule(dynamic)
                for (int i = 0; i < outerDim; i++) {
                    for (int j = 0; j < value_arr_size; j++) {
                        newVector.value_arr[i][j] *= scalar;
                    }
                }
                return newVector;
            }
        }

        #pragma omp parallel for schedule(dynamic)
        for (typename SparseMatrix<T, indexT, compressionLevel, columnMajor>::InnerIterator it(newVector); it; ++it) {
            if (it.isNewRun()) {
                it.coeff(it.value() * scalar);
            }
        }

        return newVector;
    }

    /**
     * @brief Computes the dot product between a CSF vector and Eigen::Vector 
     * 
     * @tparam T
     * @tparam indexT
     * @tparam compressionLevel
     * 
     * @param other
     * 
     * @return double
    */

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    double SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector::dot(Eigen::Vector<T,-1>& other) {
        double dot = 0;

        for (typename SparseMatrix<T, indexT, compressionLevel, columnMajor>::InnerIterator it(*this); it; ++it) {
            dot += it.value() * other.coeff(it.row());
        }

        return dot;
    }

    /**
     *  @brief Computes the dot product between a CSF vector and Eigen::SparseVector
     * 
     * @tparam T
     * @tparam indexT
     * @tparam compressionLevel
     * @tparam columnMajor
     * 
     * @param other 
     * 
     * @return double
    */

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    double SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector::dot(Eigen::SparseVector<T,-1>& other) {
        double dot = 0;

        for (typename SparseMatrix<T, indexT, compressionLevel, columnMajor>::InnerIterator it(*this); it; ++it) {
            dot += it.value() * other.coeff(it.row());
        }
        return dot;
    }


}