#pragma once

namespace CSF {

    //* New Return Scalar Matrix Multiplication *//
    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    CSF::SparseMatrix<T, indexT, compressionLevel, columnMajor> SparseMatrix<T, indexT, compressionLevel, columnMajor>::operator*(T scalar) const {

        // make a copy of the matrix
        CSF::SparseMatrix<T, indexT, compressionLevel, columnMajor> newMatrix(*this);

        //! Parallelize this
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
     * @brief Matrix x Matrix multiplication operator TODO: (WIP)
     *
     * @tparam T
     * @tparam indexT
     * @tparam compressionLevel
     * @tparam columnMajor
     * @param mat
     * @return SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector
     */

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    Eigen::MatrixXd SparseMatrix<T, indexT, compressionLevel, columnMajor>::operator*(Eigen::MatrixXd mat) {
        return matrixMultiply(mat);
    }

    /**
     * @brief Matrix x Vector multiplication operator helper function using Eigen::VectorXd
     * 
     * @param vec 
     * @return Eigen::MatrixXd 
     */

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    inline Eigen::MatrixXd SparseMatrix<T, indexT, compressionLevel, columnMajor>::vectorMultiply(Eigen::VectorXd& vec) {        
        #ifdef CSF_DEBUG
            // check that the vector is the correct size
            assert(vec.rows() == outerDim && "The vector must be the same size as the number of columns in the matrix!");
        #endif

        Eigen::VectorXd eigenTemp(innerDim, 1);
        eigenTemp.setZero();

        // iterate over the vector and multiply the corresponding row of the matrix by the vecIter value
        for (int i = 0; i < vec.rows(); ++i) {
            if(vec(i) == 0) continue;
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
    inline Eigen::VectorXd SparseMatrix<T, indexT, compressionLevel, columnMajor>::vectorMultiply(typename SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector& vec) {
        // check that the vector is the correct size
        #ifdef CSF_DEBUG
        if (vec.length() != outerDim)
            throw std::invalid_argument("The vector must be the same size as the number of columns in the matrix!");
        #endif

        Eigen::VectorXd eigenTemp(innerDim, 1);
        eigenTemp.setZero();

        // iterate over the vector and multiply the corresponding row of the matrix by the vecIter value
        for (typename SparseMatrix<T, indexT, compressionLevel>::InnerIterator vecIter(vec); vecIter; ++vecIter) {
            for (typename SparseMatrix<T, indexT, compressionLevel>::InnerIterator matIter(*this, vecIter.row()); matIter; ++matIter) {
                eigenTemp.coeffRef(matIter.row()) += matIter.value() * vecIter.value();
            }
        }
        return eigenTemp;
    }
    
    /**
     * @brief Matrix x Matrix multiplication operator helper function
     * 
     * @tparam T 
     * @tparam indexT 
     * @tparam compressionLevel 
     * @tparam columnMajor 
     * @param mat 
     * @return Eigen::MatrixXd 
     */

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    inline Eigen::MatrixXd SparseMatrix<T, indexT, compressionLevel, columnMajor>::matrixMultiply(Eigen::MatrixXd& mat) {
        // check that the matrix is the correct size
        #ifdef CSF_DEBUG
        if (mat.rows() != outerDim)
            throw std::invalid_argument("The matrix must be the same size as the number of columns in the matrix!");
        #endif

        Eigen::MatrixXd newMatrix = Eigen::MatrixXd::Zero(innerDim, 0);

        // iterate over the vector and multiply the corresponding vector of the parameter matrix "mat"
        for (int i = 0; i < mat.outerSize(); i++) {
            newMatrix.conservativeResize(innerDim, newMatrix.cols() + 1);
            Eigen::VectorXd vec = mat.col(i);
            newMatrix.col(i) = vectorMultiply(vec);
        }

        return newMatrix;
    }

}