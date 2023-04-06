#pragma once

#include <vector>
#include <map>
#include <iostream>
#include <omp.h>

#define META_DATA_SIZE 24
#define NUM_META_DATA 6

#define ONE_BYTE_MAX 255
#define TWO_BYTE_MAX 65535
#define FOUR_BYTE_MAX 4294967295

// Debug flag for performance testing (set to true to be faster)
#define DEBUG false

namespace CSF {

    //* New Return Scalar Matrix Multiplication *//
    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    CSF::SparseMatrix<T, indexT, compressionLevel, columnMajor> SparseMatrix<T, indexT, compressionLevel, columnMajor>::operator*(T scalar) const
    {

        // make a copy of the matrix
        CSF::SparseMatrix<T, indexT, compressionLevel, columnMajor> newMatrix(*this);

        for (uint32_t i = 0; i < this->outerDim; ++i)
        {
            for (typename SparseMatrix<T, indexT, compressionLevel>::InnerIterator it(newMatrix, i); it; ++it)
            {
                if (it.isNewRun())
                {
                    it.coeff(it.value() * scalar);
                }
            }
        }

        return newMatrix;
        
    }

    //* In Place Scalar Matrix Multiplication *//
    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    void SparseMatrix<T, indexT, compressionLevel, columnMajor>::operator*=(T scalar)
    {
        for (uint32_t i = 0; i < this->outerDim; ++i)
        {
            for (typename SparseMatrix<T, indexT, compressionLevel>::InnerIterator it(*this, i); it; ++it)
            {
                if (it.isNewRun())
                {
                    it.coeff(it.value() * scalar);
                }
            }
        }
    }

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    typename CSF::SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector SparseMatrix<T, indexT, compressionLevel, columnMajor>::operator*(SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector &vec)
    {
        // check that the vector is the correct size
        if (vec.length() != outerDim)
            throw std::invalid_argument("The vector must be the same size as the number of columns in the matrix!");

        Eigen::SparseMatrix<T> eigenTemp(outerDim, 1);
        eigenTemp.reserve(outerDim);

        // iterate over the vector and multiply the corresponding row of the matrix by the vecIter value
        for (typename SparseMatrix<T, indexT, compressionLevel>::InnerIterator vecIter(vec); vecIter; ++vecIter)
        {
            for (typename SparseMatrix<T, indexT, compressionLevel>::InnerIterator matIter(*this, vecIter.getIndex()); matIter; ++matIter)
            {
                eigenTemp.coeffRef(vecIter.row(), 0) += matIter.value() * vecIter.value();
            }
        }
        eigenTemp.makeCompressed();
        // TODO: This is unnecessary overhead
        return SparseMatrix<T, indexT, compressionLevel, columnMajor>(eigenTemp).getVector(0);
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
    SparseMatrix<T, indexT, compressionLevel, columnMajor> SparseMatrix<T, indexT, compressionLevel, columnMajor>::operator*(SparseMatrix<T, indexT, compressionLevel, columnMajor> &mat)
    {
        // check that the matrix is the correct size
        if (mat.outerSize() != innerDim)
            throw std::invalid_argument("The matrix's outer dimension must be the same as the inner dimension of the matrix");

        SparseMatrix<T, indexT, compressionLevel, columnMajor> newMatrix;

        // iterate over the vector and multiply the corresponding vector of the parameter matrix "mat"
        for (uint32_t i = 0; i < mat.outerSize(); ++i)
        {
            SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector newVector(mat, i);
            SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector tempVector(*this * newVector);
            newMatrix.append(tempVector);
        }

        return newMatrix;
    }
}