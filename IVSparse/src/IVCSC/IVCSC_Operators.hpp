/**
 * @file IVCSC_Operators.hpp
 * @author Skyler Ruiter and Seth Wolfgang
 * @brief Operator Overloads for IVCSC Sparse Matrices
 * @version 0.1
 * @date 2023-07-03
 */

#pragma once

namespace IVSparse {

    // Assignment Operator
    template <typename T, bool columnMajor>
    IVCSC<T, columnMajor>& IVCSC<T, columnMajor>::operator=(const IVSparse::IVCSC<T, columnMajor>& other) {

        if (this != &other) {
            // free old data
            if (data != nullptr) {
                for (uint32_t i = 0; i < outerDim; i++) {
                    if (data[i] != nullptr) {
                        free(data[i]);
                    }
                }
                free(data);
            }
            if (endPointers != nullptr) {
                free(endPointers);
            }
            if (metadata != nullptr) {
                delete[] metadata;
            }

            // set the dimensions
            numRows = other.numRows;
            numCols = other.numCols;
            outerDim = other.outerDim;
            innerDim = other.innerDim;
            nnz = other.nnz;
            compSize = other.compSize;

            // allocate the memory
            try {
                data = (void**)malloc(outerDim * sizeof(void*));
                endPointers = (void**)malloc(outerDim * sizeof(void*));
                metadata = new uint32_t[NUM_META_DATA];
            }
            catch (std::bad_alloc& e) {
                std::cerr << "Error: Could not allocate memory for IVSparse matrix"
                    << std::endl;
                exit(1);
            }

            // copy the metadata
            memcpy(metadata, other.metadata, sizeof(uint32_t) * NUM_META_DATA);

            // set the index and value types
            encodeValueType();
            index_t = other.index_t;

            // copy the data
            for (uint32_t i = 0; i < outerDim; i++) {
                // if the vector is empty, set the data pointer to nullptr
                if (other.data[i] == nullptr) {
                    data[i] = nullptr;
                    endPointers[i] = nullptr;
                    continue;
                }

                try {
                    data[i] = malloc(other.getVectorByteSize(i));
                }
                catch (std::bad_alloc& e) {
                    std::cerr << "Error: Could not allocate memory for IVSparse matrix"
                        << std::endl;
                    exit(1);
                }

                memcpy(data[i], other.data[i], other.getVectorByteSize(i));
                endPointers[i] = (uint8_t*)data[i] + other.getVectorByteSize(i);
            }
        }
        return *this;
    }

    // Equality Operator
    template <typename T, bool columnMajor>
    bool IVCSC<T, columnMajor>::operator==(const IVCSC<T, columnMajor>& other) const {

        // first check the metadata using memcompare
        if (memcmp(metadata, other.metadata, sizeof(uint32_t) * NUM_META_DATA) != 0)
            return false;

        // iterate through the data and compare each element
        for (uint32_t i = 0; i < outerDim; i++) {
            if (memcmp(data[i], other.data[i], getVectorByteSize(i)) != 0) return false;
        }

        return true;
    }

    // Inequality Operator
    template <typename T, bool columnMajor>
    bool IVCSC<T, columnMajor>::operator!=(const IVCSC<T, columnMajor>& other) {

        return !(*this == other);
    }

    // Coefficent Access Operator
    template <typename T, bool columnMajor>
    T IVCSC<T, columnMajor>::operator()(uint32_t row, uint32_t col) {
        #ifdef IVSPARSE_DEBUG
        // check if the row and column are in bounds
        if (row >= numRows || col >= numCols) {
            std::cerr << "Error: Index out of bounds" << std::endl;
            exit(1);
        }
        #endif

        uint32_t vector = columnMajor ? col : row;
        uint32_t index = columnMajor ? row : col;

        // if the vector is empty return 0
        if (data[vector] == nullptr) return 0;

        // get an iterator for the desired vector
        for (typename IVCSC<T, columnMajor>::InnerIterator it(*this, vector); it; ++it) {
            if (it.getIndex() == (size_t)index) {
                return it.value();
            }
        }

        // if the index is not found return 0
        return 0;
    }


    //* BLAS Operators *//

    // Scalar Multiplication
    template <typename T, bool columnMajor>
    IVSparse::IVCSC<T, columnMajor> IVCSC<T, columnMajor>::operator*(T scalar) {
        return scalarMultiply(scalar);
    }

    // In place scalar multiplication
    template <typename T, bool columnMajor>
    void IVCSC<T, columnMajor>::operator*=(T scalar) {
        inPlaceScalarMultiply(scalar);
    }

    // Matrix Vector Multiplication (IVSparse Eigen -> Eigen)
    template <typename T, bool columnMajor>
    Eigen::Matrix<T, -1, 1> IVCSC<T, columnMajor>::operator*(Eigen::Matrix<T, -1, 1>& vec) {

        return vectorMultiply(vec);
    }

    // Matrix Matrix Multiplication (IVSparse Eigen -> Eigen)
    template <typename T, bool columnMajor>
    Eigen::Matrix<T, -1, -1> IVCSC<T, columnMajor>::operator*(Eigen::Matrix<T, -1, -1>& mat) {

        #ifdef IVSPARSE_DEBUG
        // check that the matrix is the correct size
        if (mat.rows() != numCols)
            throw std::invalid_argument(
                "The left matrix must have the same # of rows as columns in the right "
                "matrix!");
        #endif

        Eigen::Matrix<T, -1, -1> newMatrix = Eigen::Matrix<T, -1, -1>::Zero(mat.cols(), numRows);
        Eigen::Matrix<T, -1, -1> matTranspose = mat.transpose();

        // #ifdef IVSPARSE_HAS_OPENMP
        // #pragma omp parallel for
        // #endif
        for (uint32_t col = 0; col < numCols; col++) {
            for (typename IVCSC<T, columnMajor>::InnerIterator matIter(*this, col); matIter; ++matIter) {
                newMatrix.col(matIter.row()) += matTranspose.col(col) * matIter.value();
            }
        }
        return newMatrix.transpose();
    }

    template <typename T, bool columnMajor>
    Eigen::Matrix<T, -1, -1>  IVCSC<T, columnMajor>::operator* (const Eigen::Ref<const Eigen::Matrix<T, -1, -1>>& mat) {

        #ifdef IVSPARSE_DEBUG
        // check that the matrix is the correct size
        if (mat.rows() != numCols)
            throw std::invalid_argument(
                "The left matrix must have the same # of rows as columns in the right "
                "matrix!");
        #endif

        Eigen::Matrix<T, -1, -1> newMatrix = Eigen::Matrix<T, -1, -1>::Zero(mat.cols(), numRows);
        Eigen::Matrix<T, -1, -1> matTranspose = mat.transpose();

        // Fix Parallelism issue (race condition because of partial sums and
        // orientation of Sparse * Dense)
        for (uint32_t col = 0; col < numCols; col++) {
            for (typename IVCSC<T, columnMajor>::InnerIterator matIter(*this, col); matIter; ++matIter) {
                newMatrix.col(matIter.row()) += matTranspose.col(col) * matIter.value();
            }
        }
        return newMatrix.transpose();
    }

    template <typename T, bool columnMajor>
    inline Eigen::Matrix<T, -1, 1> IVCSC<T, columnMajor>::operator*(const Eigen::Ref<const Eigen::Matrix<T, -1, 1>>& vec) {

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

} // namespace IVSparse