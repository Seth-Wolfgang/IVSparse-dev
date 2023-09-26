/**
 * @file VCSC_Operators.hpp
 * @author Skyler Ruiter and Seth Wolfgang
 * @brief Operator Overloads for VCSC Sparse Matrices
 * @version 0.1
 * @date 2023-07-03
 */

#pragma once

namespace IVSparse {

// Assignment Operator
template <typename T, typename indexT, bool columnMajor>
SparseMatrix<T, indexT, 2, columnMajor> &SparseMatrix<T, indexT, 2, columnMajor>::operator=(
    const IVSparse::SparseMatrix<T, indexT, 2, columnMajor> &other) {
  
  // check if the matrices are the same
  if (this != &other) {
    // free the memory
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

    // copy the metadata
    memcpy(metadata, other.metadata, sizeof(uint32_t) * NUM_META_DATA);

    // set the index and value types
    encodeValueType();
    index_t = other.index_t;

    data.reserve(outerDim);

    // copy the data
    for (uint32_t i = 0; i < outerDim; i++) {
      // copy the map of the other matrix
      data[i].swap(other.data[i]);
    }

    // calculate comp size
    calculateCompSize();
  }

  // return the new matrix
  return *this;

}  // end assignment operator

// Equality Operator
template <typename T, typename indexT, bool columnMajor>
bool SparseMatrix<T, indexT, 2, columnMajor>::operator==(
    const SparseMatrix<T, indexT, 2, columnMajor> &other) {
  
  // first check the metadata using memcompare
  if (memcmp(metadata, other.metadata, sizeof(uint32_t) * NUM_META_DATA) != 0) {
    return false;
  }

  // check if the underlying maps are the same for each column
  for (uint32_t i = 0; i < outerDim; i++) {
    if (data[i] != other.data[i]) {
      return false;
    }
  }

  // if all of the above checks pass then the matrices are equal
  return true;
}

// Inequality Operator
template <typename T, typename indexT, bool columnMajor>
bool SparseMatrix<T, indexT, 2, columnMajor>::operator!=(const SparseMatrix<T, indexT, 2, columnMajor> &other) {
  return !(*this == other);
}

// Coefficent Access Operator
template <typename T, typename indexT, bool columnMajor>
T SparseMatrix<T, indexT, 2, columnMajor>::operator()(uint32_t row, uint32_t col) {
  
  #ifdef IVSPARSE_DEBUG
    // check if the row and column are in bounds
    assert((row < numRows && row >= 0) && "Row index out of bounds");
    assert((col < numCols && col >= 0) && "Column index out of bounds");
  #endif
  
  #ifdef IVSPARSE_DEBUG
  // check if the row and column are in bounds
  if (row >= numRows || col >= numCols) {
    std::cerr << "Error: Index out of bounds" << std::endl;
    exit(1);
  }
  #endif

  uint32_t vector = columnMajor ? col : row;
  uint32_t index = columnMajor ? row : col;

  // get an iterator for the desired vector
  for (typename SparseMatrix<T, indexT, 2, columnMajor>::InnerIterator it(*this, vector); it; ++it) {
    if (it.getIndex() == (indexT)index) {
      return it.value();
    }
  }

  // if the index is not found return 0
  return 0;
}

// Vector Access Operator
template <typename T, typename indexT, bool columnMajor>
typename SparseMatrix<T, indexT, 2, columnMajor>::Vector SparseMatrix<T, indexT, 2, columnMajor>::operator[](uint32_t vec) {

  #ifdef IVSPARSE_DEBUG
  // check if the vector is out of bounds
  assert((vec < outerDim && vec >= 0) && "Vector index out of bounds");
  #endif

  // return a IVSparse vector
  typename IVSparse::SparseMatrix<T, indexT, 2, columnMajor>::Vector newVector(*this, vec);

  return newVector;
}

// Outstream Operator
template <typename T, typename indexT, bool columnMajor>
std::ostream &operator<<(std::ostream &os, IVSparse::SparseMatrix<T, indexT, 2, columnMajor> &mat) {

  #ifndef IVSPARSE_DEBUG
  if (mat.cols() > 110) {
    std::cout << "IVSparse matrix is too large to print" << std::endl;
    return os;
  }
  #endif

  // create a matrix to store the full matrix representation of the IVSparse
  // matrix
  T **matrix = new T *[mat.rows()];
  for (size_t i = 0; i < mat.rows(); i++) {
    matrix[i] = (T *)calloc(mat.cols(), sizeof(T));
  }

  // Build the full matrix representation of the the IVSparse matrix
  for (size_t i = 0; i < mat.cols(); i++) {
    for (typename IVSparse::SparseMatrix<T, indexT, 2,
                                         columnMajor>::InnerIterator it(mat, i);
         it; ++it) {
      // std::cout << "it.row(): " << it.row() << " col: " << it.col() << "
      // value: " << it.value() << std::endl;
      matrix[it.row()][it.col()] = it.value();
    }
  }

  // store all of matrix into the output stream
  for (size_t i = 0; i < mat.rows(); i++) {
    for (size_t j = 0; j < mat.cols(); j++) {
      os << matrix[i][j] << " ";
    }
    os << std::endl;
  }

  for (int i = 0; i < mat.rows(); i++) {
    free(matrix[i]);
  }
  delete[] matrix;

  return os;

}  // end outstream operator

//* BLAS Operators *//

// Scalar Multiplication
template <typename T, typename indexT, bool columnMajor>
IVSparse::SparseMatrix<T, indexT, 2, columnMajor> SparseMatrix<T, indexT, 2, columnMajor>::operator*(T scalar) {
  return scalarMultiply(scalar);
}

// In place scalar multiplication
template <typename T, typename indexT, bool columnMajor> void SparseMatrix<T, indexT, 2, columnMajor>::operator*=(T scalar) {
  return inPlaceScalarMultiply(scalar);
}

// // IVSparse Matrix * IVSparse Vector Multiplication
// template <typename T, typename indexT, bool columnMajor>
// Eigen::Matrix<T, -1, 1>SparseMatrix<T, indexT, 2,
// columnMajor>::operator*(SparseMatrix<T, indexT, 2, columnMajor>::Vector& vec)
// {
//     return vectorMultiply(vec);
// }

// Matrix Vector Multiplication (IVSparse Eigen -> Eigen)
template <typename T, typename indexT, bool columnMajor>
Eigen::Matrix<T, -1, 1> SparseMatrix<T, indexT, 2, columnMajor>::operator*(Eigen::Matrix<T, -1, 1> &vec) {
  return vectorMultiply(vec);
}

// Matrix Matrix Multiplication (IVSparse Eigen -> Eigen)
template <typename T, typename indexT, bool columnMajor>
Eigen::Matrix<T, -1, -1> SparseMatrix<T, indexT, 2, columnMajor>::operator*(Eigen::Matrix<T, -1, -1> &mat) {
  
  #ifdef IVSPARSE_DEBUG
  // check that the matrix is the correct size
  if (mat.rows() != numCols)
    throw std::invalid_argument(
        "The left matrix must have the same # of rows as columns in the right "
        "matrix!");
  #endif

  Eigen::Matrix<T, -1, -1> newMatrix = Eigen::Matrix<T, -1, -1>::Zero(mat.cols(), numRows);
  Eigen::Matrix<T, -1, -1> matTranspose = mat.transpose();

  // Fix Parallelism issue (race condition because of partial sums and orientation of Sparse * Dense)
  for (uint32_t col = 0; col < numCols; col++) {
    for (typename SparseMatrix<T, indexT, 2, columnMajor>::InnerIterator matIter(*this, col); matIter; ++matIter) {
      newMatrix.col(matIter.row()) += matTranspose.col(col) * matIter.value();
    }
  }
  return newMatrix.transpose();
}

}  // end namespace IVSparse