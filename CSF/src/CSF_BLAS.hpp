#pragma once

namespace CSF {

    //* New Return Scalar Matrix Multiplication *//
    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    CSF::SparseMatrix<T, indexT, compressionLevel, columnMajor> SparseMatrix<T, indexT, compressionLevel, columnMajor>::operator*(T scalar) {

        CSF::SparseMatrix<T, indexT, compressionLevel, columnMajor> newMatrix(*this);

        if constexpr (compressionLevel == 2) {
            if (performanceVecsOn) {
                #pragma omp parallel for schedule(dynamic)
                for (int i = 0; i < outerDim; i++) {
                    for (int j = 0; j < value_arr_size[i]; j++) {
                        newMatrix.value_arr[i][j] *= scalar;
                    }
                }
                return newMatrix;

            }
        }
    
        #pragma omp parallel for schedule(dynamic)
        for (uint32_t i = 0; i < this->outerDim; ++i) {
            for (typename SparseMatrix<T, indexT, compressionLevel>::InnerIterator it(newMatrix, i); it; ++it) {
                if (it.isNewRun()) {
                    it.coeff(it.value() * scalar);
                }
            }
        }


        return newMatrix;
    }

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    void SparseMatrix<T, indexT, compressionLevel, columnMajor>::operator*=(T scalar) {
        // make a copy of this
        if constexpr (compressionLevel == 2) {
            if (performanceVecsOn) {
                #pragma omp parallel for schedule(dynamic)
                for (int i = 0; i < outerDim; i++) {
                    for (int j = 0; j < value_arr_size[i]; j++) {
                        value_arr[i][j] *= scalar;
                    }
                }
            }
            return;
        }
        #pragma omp parallel for schedule(dynamic)
        for (uint32_t i = 0; i < outerDim; ++i) {
            for (typename SparseMatrix<T, indexT, compressionLevel>::InnerIterator it(*this, i); it; ++it) {
                if (it.isNewRun()) {
                    it.coeff(it.value() * scalar);
                }
            }
        }
    }

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    Eigen::VectorXd SparseMatrix<T, indexT, compressionLevel, columnMajor>::operator*(Eigen::VectorXd& vec) {
        return vectorMultiply(vec);
    }


    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    Eigen::VectorXd SparseMatrix<T, indexT, compressionLevel, columnMajor>::operator*(SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector& vec) {
        return vectorMultiply(vec);
    }

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    Eigen::Matrix<T, -1, -1> SparseMatrix<T, indexT, compressionLevel, columnMajor>::operator*(Eigen::Matrix<T, -1, -1> mat) {
        return matrixMultiply(mat);
    }

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    inline Eigen::Matrix<T, -1, -1> SparseMatrix<T, indexT, compressionLevel, columnMajor>::vectorMultiply(Eigen::VectorXd& vec) {
        // check that the vector is the correct size
        #ifdef CSF_DEBUG
        assert(vec.rows() == outerDim && "The vector must be the same size as the number of columns in the matrix!");
        #endif

        Eigen::Matrix<T, -1, 1> eigenTemp(innerDim, 1);
        eigenTemp.setZero();

        // iterate over the vector and multiply the corresponding row of the matrix by the vecIter value
        for (int i = 0; i < vec.rows(); ++i) {
            if (vec(i) == 0) continue;
            for (typename SparseMatrix<T, indexT, compressionLevel>::InnerIterator matIter(*this, i); matIter; ++matIter) {
                eigenTemp.coeffRef(matIter.row()) += matIter.value() * vec(i);
            }
        }
        return eigenTemp;
    }

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    inline Eigen::Matrix<T, -1, 1> SparseMatrix<T, indexT, compressionLevel, columnMajor>::vectorMultiply(typename SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector& vec) {
        // check that the vector is the correct size
        #ifdef CSF_DEBUG
        if (vec.length() != outerDim)
            throw std::invalid_argument("The vector must be the same size as the number of columns in the matrix!");
        #endif

        Eigen::Matrix<T, -1, 1> newVector = Eigen::Matrix<T, -1, 1>::Zero(innerDim, 1);

        // iterate over the vector and multiply the corresponding row of the matrix by the vecIter value
        for (typename SparseMatrix<T, indexT, compressionLevel>::InnerIterator vecIter(vec); vecIter; ++vecIter) {
            for (typename SparseMatrix<T, indexT, compressionLevel>::InnerIterator matIter(*this, vecIter.row()); matIter; ++matIter) {
                newVector.coeffRef(matIter.row()) += matIter.value() * vecIter.value();
            }
        }
        return newVector;
    }


    /*
        NOT WORKING
    */
    //  template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    //  inline Eigen::Matrix<T, -1,-1> SparseMatrix<T, indexT, compressionLevel, columnMajor>::matrixMultiply(Eigen::Matrix<T, -1,-1>& mat) {
    //      // check that the matrix is the correct size
    //     #ifdef CSF_DEBUG
    //      if (mat.rows() != outerDim)
    //          throw std::invalid_argument("The matrix must be the same size as the number of columns in the matrix!");
    //     #endif

    //      Eigen::Matrix<T, -1,-1> newMatrix = Eigen::Matrix<T, -1,-1>::Zero(innerDim, mat.cols());

    //     #pragma omp parallel for
    //      for (int i = 0; i < this->rows() * mat.cols(); ++i) {
    //          // linear indexing considers a matrix as a vector, in this case we let it be column-major
    //          int col = i / this->rows(); // integer division!
    //          int row = i % this->rows(); // modulus of integer division!
    //          for (typename SparseMatrix<T, indexT, compressionLevel>::InnerIterator matIter(*this, row); matIter; ++matIter) {
    //              newMatrix.coeffRef(row, col) += matIter.value() * mat(row, col);
    //          }
    //      }
    //      return newMatrix;
    //  }

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    inline Eigen::Matrix<T, -1, -1> SparseMatrix<T, indexT, compressionLevel, columnMajor>::matrixMultiply(Eigen::Matrix<T, -1, -1>& mat) {
        // check that the matrix is the correct size
        #ifdef CSF_DEBUG
        if (mat.rows() != outerDim)
            throw std::invalid_argument("The matrix must be the same size as the number of columns in the matrix!");
        #endif

        Eigen::Matrix<T, -1, -1> newMatrix = Eigen::Matrix<T, -1, -1>::Zero(innerDim, mat.cols());

        // #pragma omp parallel for num_threads(8)
        for (int col = 0; col < mat.cols(); col++) {
            for (int row = 0; row < mat.rows(); row++) {
                for (typename SparseMatrix<T, indexT, compressionLevel>::InnerIterator matIter(*this, row); matIter; ++matIter) {
                    newMatrix.coeffRef(matIter.row(), col) += matIter.value() * mat(row, col);
                }
            }
        }
        return newMatrix;
    }

    /**
     * @brief Returns the sum of each column of the matrix
     * 
     * @tparam T
     * @tparam indexT
     * @tparam compressionLevel
     * @tparam columnMajor
     * 
     * @return T*
    */

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    inline T* SparseMatrix<T, indexT, compressionLevel, columnMajor>::outerSum() {
        T* outerSum = (T*)calloc(outerDim, sizeof(T));

        if constexpr (compressionLevel == 2) {
            if (performanceVecsOn) {

                #pragma omp parallel for schedule(dynamic)
                for (int i = 0; i < outerDim; i++) {
                    for (int j = 0; j < value_arr_size[i]; j++) {
                        outerSum[i] += value_arr[i][j] * counts_arr[i][j];
                    }
                }
                return outerSum;
            }
        }

        for (int i = 0; i < outerDim; i++) {
            for (typename SparseMatrix<T, indexT, compressionLevel>::InnerIterator it(*this, i); it; ++it) {
                outerSum[i] += it.value();
            }
        }
        return outerSum;
    }

    /**
     * @brief Returns the sum of each row of the matrix
     * 
     * @tparam T
     * @tparam indexT
     * @tparam compressionLevel
     * @tparam columnMajor
     * 
     * @return T*
    */

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    inline T* SparseMatrix<T, indexT, compressionLevel, columnMajor>::innerSum() {
        T* innerSum = (T*)calloc(innerDim, sizeof(T));

        for (int i = 0; i < outerDim; i++) {
            for (typename SparseMatrix<T, indexT, compressionLevel>::InnerIterator it(*this, i); it; ++it) {
                innerSum[it.row()] += it.value();
            }
        }
        return innerSum;
    }

    /**
     * @brief Returns the maximum value in each column of the matrix
     * 
     * @tparam T
     * @tparam indexT
     * @tparam compressionLevel
     * @tparam columnMajor
     * 
     * @return T*
    */

    template<typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    inline T* SparseMatrix<T, indexT, compressionLevel, columnMajor>::maxColCoeff() {
        T* maxCoeff = (T*)calloc(outerDim, sizeof(T));

        if constexpr (compressionLevel == 2) {
            if (performanceVecsOn) {
                #pragma omp parallel for schedule(dynamic)
                for (int i = 0; i < outerDim; i++) {
                    for (int j = 0; j < value_arr_size[i]; j++) {
                        if (value_arr[i][j] > maxCoeff[i]) {
                            maxCoeff[i] = value_arr[i][j];
                        }
                    }
                }
                return maxCoeff;
            }
        }

        for (int i = 0; i < outerDim; i++) {
            for (typename SparseMatrix<T, indexT, compressionLevel>::InnerIterator it(*this, i); it; ++it) {
                if (it.value() > maxCoeff[i]) {
                    maxCoeff[i] = it.value();
                }
            }
        }
        return maxCoeff;
    }

    /**
     * @brief Returns the maximum value in each row of the matrix
     * 
     * @tparam T
     * @tparam indexT
     * @tparam compressionLevel
     * @tparam columnMajor
     * 
     * @return T*
    */

    template<typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    inline T* SparseMatrix<T, indexT, compressionLevel, columnMajor>::maxRowCoeff() {
        T* maxCoeff = (T*)calloc(innerDim, sizeof(T));
        for (int i = 0; i < outerDim; i++) {
            for (typename SparseMatrix<T, indexT, compressionLevel>::InnerIterator it(*this, i); it; ++it) {
                if (it.value() > maxCoeff[it.row()]) {
                    maxCoeff[it.row()] = it.value();
                }
            }
        }
        return maxCoeff;
    }

    /**
     * @brief Returns the minimum value in each column of the matrix
     * 
     * @tparam T
     * @tparam indexT
     * @tparam compressionLevel
     * @tparam columnMajor
     * 
     * @return T*
    */

    template<typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    inline T* SparseMatrix<T, indexT, compressionLevel, columnMajor>::minColCoeff() {
        T* minCoeff = (T*)calloc(outerDim, sizeof(T));
        for (int i = 0; i < outerDim; i++) {
            for (typename SparseMatrix<T, indexT, compressionLevel>::InnerIterator it(*this, i); it; ++it) {
                if (it.value() < minCoeff[i]) {
                    minCoeff[i] = it.value();
                }
            }
        }
        return minCoeff;
    }

    /**
     * @brief Returns the minimum value in each row of the matrix
     * 
     * @tparam T
     * @tparam indexT
     * @tparam compressionLevel
     * @tparam columnMajor
     * 
     * @return T*
    */

    template<typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    inline T* SparseMatrix<T, indexT, compressionLevel, columnMajor>::minRowCoeff() {
        T* minCoeff = (T*)calloc(innerDim, sizeof(T));
        memset(minCoeff, 0xF, innerDim * sizeof(T));

        for (int i = 0; i < outerDim; i++) {
            for (typename SparseMatrix<T, indexT, compressionLevel>::InnerIterator it(*this, i); it; ++it) {
                if (it.value() < minCoeff[it.row()]) {
                    minCoeff[it.row()] = it.value();
                }
            }
        }
        return minCoeff;
    }

    /**
     * @brief Returns the trace of the matrix
     * 
     * @tparam T
     * @tparam indexT
     * @tparam compressionLevel
     * @tparam columnMajor
     * 
     * @return T*
    */

    template<typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    inline T SparseMatrix<T, indexT, compressionLevel, columnMajor>::trace() {
        assert(innerDim == outerDim && "Trace is only defined for square matrices!");

        T trace = 0;
        for (int i = 0; i < outerDim; i++) {
            for (typename SparseMatrix<T, indexT, compressionLevel>::InnerIterator it(*this, i); it; ++it) {
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

    /**
     * @brief Returns the sum of all the elements in the matrix
     * 
     * @tparam T
     * @tparam indexT
     * @tparam compressionLevel
     * @tparam columnMajor
     * 
     * @return T*
    */

    template<typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    inline T SparseMatrix<T, indexT, compressionLevel, columnMajor>::sum() {
        T sum = 0;

        if constexpr (compressionLevel == 2) {
            if (performanceVecsOn) {
                            std::cout << "Using new" << std::endl;

                #pragma omp parallel for schedule(dynamic)
                for (int i = 0; i < outerDim; i++) {
                    for (int j = 0; j < value_arr_size[i]; j++) {
                        sum += value_arr[i][j] * counts_arr[i][j];
                    }
                }
                return sum;
            }
        }

        for (int i = 0; i < outerDim; i++) {
            for (typename SparseMatrix<T, indexT, compressionLevel>::InnerIterator it(*this, i); it; ++it) {
                sum += it.value();
            }
        }
        return sum;
    }
}

