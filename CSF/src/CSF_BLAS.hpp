#pragma once

namespace CSF {

    //* New Return Scalar Matrix Multiplication *//
    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    CSF::SparseMatrix<T, indexT, compressionLevel, columnMajor> SparseMatrix<T, indexT, compressionLevel, columnMajor>::operator*(T scalar) const {

        // make a copy of the matrix
        CSF::SparseMatrix<T, indexT, compressionLevel, columnMajor> newMatrix(*this);

        // #pragma omp parallel for schedule(dynamic)
        for (uint32_t i = 0; i < this->outerDim; ++i) {
            for (typename SparseMatrix<T, indexT, compressionLevel>::InnerIterator it(newMatrix, i); it; ++it) {
                if (it.isNewRun()) {
                    it.coeff(it.value() * scalar);
                }
            }
        }
        return newMatrix;
    }

    /**
     * @brief Scalar multiplication operator
     *
     * @tparam T
     * @tparam indexT
     * @tparam compressionLevel
     * @tparam columnMajor
     * @param scalar
     */

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    void SparseMatrix<T, indexT, compressionLevel, columnMajor>::operator*=(T scalar) {
        //! Parallelize this
        for (uint32_t i = 0; i < this->outerDim; ++i) {
            for (typename SparseMatrix<T, indexT, compressionLevel>::InnerIterator it(*this, i); it; ++it) {
                if (it.isNewRun()) {
                    it.coeff(it.value() * scalar);
                }
            }
        }
    }

    /**
     * @brief Matrix x Vector multiplication operator with an Eigen::VectorXd
     *
     * @tparam T
     * @tparam indexT
     * @tparam compressionLevel
     * @tparam columnMajor
     * @param vec
     * @return Eigen::VectorXd
     */

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    Eigen::VectorXd SparseMatrix<T, indexT, compressionLevel, columnMajor>::operator*(Eigen::VectorXd& vec) {
        return vectorMultiply(vec);
    }


    /**
     * @brief Matrix x Vector multiplication operator
     *
     * @tparam T
     * @tparam indexT
     * @tparam compressionLevel
     * @tparam columnMajor
     * @param vec
     * @return Eigen::VectorXd
     */

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    Eigen::VectorXd SparseMatrix<T, indexT, compressionLevel, columnMajor>::operator*(SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector& vec) {
        return vectorMultiply(vec);
    }

    /**
     * @brief Matrix x Matrix multiplication operator
     *
     * @tparam T
     * @tparam indexT
     * @tparam compressionLevel
     * @tparam columnMajor
     * @param mat
     * @return SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector
     */

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    Eigen::Matrix<T, -1, -1> SparseMatrix<T, indexT, compressionLevel, columnMajor>::operator*(Eigen::Matrix<T, -1, -1> mat) {
        return matrixMultiply(mat);
    }

    /**
     * @brief Matrix x Vector multiplication operator helper function using Eigen::VectorXd
     *
     * @param vec
     * @return Eigen::Matrix<T, -1,-1>
     */

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

    /**
     * @brief Matrix x Matrix multiplication operator helper function using CSF::Vector
     *
     * @tparam T
     * @tparam indexT
     * @tparam compressionLevel
     * @tparam columnMajor
     * @param vec
     * @return Eigen::VectorXd
     */

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

    /**
     * @brief Matrix x Matrix multiplication operator helper function
     *
     * @tparam T
     * @tparam indexT
     * @tparam compressionLevel
     * @tparam columnMajor
     * @param mat
     * @return Eigen::Matrix<T, -1,-1>
     */

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
}
