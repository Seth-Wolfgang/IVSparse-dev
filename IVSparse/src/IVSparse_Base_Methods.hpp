/**
 * @file IVSparse_Base_Methods.hpp
 * @author Skyler Ruiter and Seth Wolfgang
 * @brief IVSparse Sparse Matrix Base Methods
 * @version 0.1
 * @date 2023-07-03
 */

#pragma once

namespace IVSparse {

// Calculates the number of bytes needed to store a value
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

// Gets the number of rows in the matrix
uint32_t SparseMatrixBase::rows() const { return numRows; }

// Gets the number of columns in the matrix
uint32_t SparseMatrixBase::cols() const { return numCols; }

// Gets the inner dimension of the matrix
uint32_t SparseMatrixBase::innerSize() const { return innerDim; }

// Gets the outer dimension of the matrix
uint32_t SparseMatrixBase::outerSize() const { return outerDim; }

// Gets the number of non-zero elements in the matrix
uint32_t SparseMatrixBase::nonZeros() const { return nnz; }

// Gets the number of bytes needed to store the matrix
size_t SparseMatrixBase::byteSize() const { return compSize; }

}  // namespace IVSparse