/**
 * @file IVCSC_Parallel_Operators.hpp
 * @author Skyler Ruiter and Seth Wolfgang
 * @brief Parallel Operators VCSC Sparse Matrices
 *        Note: These files are for algorithms that required changes to the algorithm to be parallelized.
 *        Trivially parallelizable algorithms are in the original file.
 * @version 0.1
 * @date 2024-03-08
 */

namespace IVSparse {


    template <typename T, typename indexT, bool columnMajor>
    Eigen::Matrix<T, -1, -1> VCSC<T, indexT, columnMajor>::operator* (Eigen::Matrix<T, -1, -1>& mat) {
        #ifdef IVSPARSE_DEBUG
        // check that the matrix is the correct size
        if (mat.rows() != numCols)
            throw std::invalid_argument(
                "The left matrix must have the same # of rows as columns in the right "
                "matrix!");
        #endif

        Eigen::Matrix<T, -1, -1> newMatrix = Eigen::Matrix<T, -1, -1>::Zero(mat.cols(), numRows);
        Eigen::Matrix<T, -1, -1> matTranspose = mat.transpose();
        std::vector<std::mutex> mutexList(innerDim);

        // orientation of Sparse * Dense)
        #pragma omp parallel for
        for (uint32_t i = 0; i < outerDim; ++i) {
            for (typename VCSC<T, indexT, columnMajor>::InnerIterator matIter(*this, i); matIter; ++matIter) {
                std::lock_guard<std::mutex> lock(mutexList[matIter.getIndex()]);
                if constexpr (columnMajor) {
                    newMatrix.col(matIter.getIndex()) += matTranspose.col(i) * matIter.value();
                }
                else {
                    newMatrix.col(i) += matTranspose.col(matIter.getIndex()) * matIter.value();
                }
            }
        }

        return newMatrix.transpose();
    }

    template <typename T, typename indexT, bool columnMajor>
    Eigen::Matrix<T, -1, -1>  VCSC<T, indexT, columnMajor>::operator* (const Eigen::Ref<const Eigen::Matrix<T, -1, -1>>& mat) {
        #ifdef IVSPARSE_DEBUG
        // check that the matrix is the correct size
        if (mat.rows() != numCols)
            throw std::invalid_argument(
                "The left matrix must have the same # of rows as columns in the right "
                "matrix!");
        #endif

        Eigen::Matrix<T, -1, -1> newMatrix = Eigen::Matrix<T, -1, -1>::Zero(mat.cols(), numRows);
        Eigen::Matrix<T, -1, -1> matTranspose = mat.transpose();
        std::vector<std::mutex> mutexList(innerDim);

        // orientation of Sparse * Dense)
        #pragma omp parallel for
        for (uint32_t i = 0; i < outerDim; ++i) {
            for (typename VCSC<T, indexT, columnMajor>::InnerIterator matIter(*this, i); matIter; ++matIter) {
                std::lock_guard<std::mutex> lock(mutexList[matIter.getIndex()]);
                if constexpr (columnMajor) {
                    newMatrix.col(matIter.getIndex()) += matTranspose.col(i) * matIter.value();
                }
                else {
                    newMatrix.col(i) += matTranspose.col(matIter.getIndex()) * matIter.value();
                }
            }
        }

        return newMatrix.transpose();
    }






}