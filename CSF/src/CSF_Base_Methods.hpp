/**
 * @file CSF_Base_Methods.hpp
 * @author Skyler Ruiter and Seth Wolfgang
 * @brief CSF Sparse Matrix Base Methods
 * @version 0.1
 * @date 2023-07-03
 */

#pragma once

namespace CSF {

    inline uint8_t SparseMatrixBase::byteWidth(size_t size) {
        if (size <= ONE_BYTE_MAX) {
            return 1;
        } else if (size <= TWO_BYTE_MAX) {
            return 2;
        } else if (size <= FOUR_BYTE_MAX) {
            return 4;
        } else {
            return 8;
        }
    }

    uint32_t SparseMatrixBase::rows() const { return numRows; }

    uint32_t SparseMatrixBase::cols() const { return numCols; }

    uint32_t SparseMatrixBase::innerSize() const { return innerDim; }

    uint32_t SparseMatrixBase::outerSize() const { return outerDim; }

    uint32_t SparseMatrixBase::nonZeros() const { return nnz; }

    size_t SparseMatrixBase::byteSize() const { return compSize; }

}