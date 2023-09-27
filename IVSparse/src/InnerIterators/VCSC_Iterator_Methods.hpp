/**
 * @file VCSC_Iterator_Methods.hpp
 * @author Skyler Ruiter and Seth Wolfgang
 * @brief Iterator Methods for VCSC Sparse Matrices
 * @version 0.1
 * @date 2023-07-03
 */

#pragma once

namespace IVSparse {

    //* Constructors *//

    // Matrix Constructor
    template <typename T, typename indexT, bool columnMajor>
    inline SparseMatrix<T, indexT, 2, columnMajor>::InnerIterator::InnerIterator(IVSparse::SparseMatrix<T, indexT, 2, columnMajor>& matrix, uint32_t vec) {

        #ifdef IVSPARSE_DEBUG
        assert(vec < matrix.outerDim && vec >= 0 && "The vector index is out of bounds!");
        #endif

  // check if the vector is empty
  if (matrix.getMap(vec)->size() == 0) {
    return;
  }

  // set the map to the internal map
  data = matrix.getMap(vec);

  valIter = data->begin();
  idxIter = data->begin()->second.begin();

  // get the first value
  val = valIter->first;

  // get the first value in the first vector
  index = valIter->second.front();

  outer = vec;
}

// Vector Constructor
template <typename T, typename indexT, bool columnMajor>
SparseMatrix<T, indexT, 2, columnMajor>::InnerIterator::InnerIterator(SparseMatrix<T, indexT, 2, columnMajor>::Vector &vector) {
  // check if the vector is empty
  if (vector.nonZeros() == 0) {
    return;
  }

  // set the map to the internal map
  this->data = vector.getData();

  this->val = data->begin()->first;
  this->index = *(data->begin()->second->begin());

  this->valIter = data->begin();
  this->idxIter = data->begin()->second->begin();

  outer = 0;
}

    //* Getters *//


// Get the value
template <typename T, typename indexT, bool columnMajor>
T SparseMatrix<T, indexT, 2, columnMajor>::InnerIterator::value() {
  return val;
}

    // Get the index
    template <typename T, typename indexT, bool columnMajor>
    indexT SparseMatrix<T, indexT, 2, columnMajor>::InnerIterator::getIndex() {
        return index;
    }

// Get a pointer to the value
template <typename T, typename indexT, bool columnMajor>
inline void SparseMatrix<T, indexT, 2, columnMajor>::InnerIterator::coeff(T newValue) {
  *val = newValue;
}

    // Get the current row
    template <typename T, typename indexT, bool columnMajor>
    indexT SparseMatrix<T, indexT, 2, columnMajor>::InnerIterator::row() {
        if constexpr (!columnMajor) {
            return outer;
        }
        else {
            return index;
        }
    }

    // Get the current column
    template <typename T, typename indexT, bool columnMajor>
    indexT SparseMatrix<T, indexT, 2, columnMajor>::InnerIterator::col() {
        if constexpr (!columnMajor) {
            return index;
        }
        else {
            return outer;
        }
    }

    //* Operator Overloads *//

    // Dereference Operator
    template <typename T, typename indexT, bool columnMajor>
    T& SparseMatrix<T, indexT, 2, columnMajor>::InnerIterator::operator*() {
        return *val;
    }

// Equality Operator
template <typename T, typename indexT, bool columnMajor>
bool SparseMatrix<T, indexT, 2, columnMajor>::InnerIterator::operator==(const InnerIterator &other) {
  return data == other.data;
}

// Inequality Operator
template <typename T, typename indexT, bool columnMajor>
bool SparseMatrix<T, indexT, 2, columnMajor>::InnerIterator::operator!=(const InnerIterator &other) {
  return data != other.data;
}

// Less Than Operator
template <typename T, typename indexT, bool columnMajor>
bool SparseMatrix<T, indexT, 2, columnMajor>::InnerIterator::operator<(const InnerIterator &other) {
  return data < other.data;
}

// Greater Than Operator
template <typename T, typename indexT, bool columnMajor>
bool SparseMatrix<T, indexT, 2, columnMajor>::InnerIterator::operator>(const InnerIterator &other) {
  return data > other.data;
}

// Increment Operator
template <typename T, typename indexT, bool columnMajor>
inline void SparseMatrix<T, indexT, 2, columnMajor>::InnerIterator::operator++() {
  
  // increment the index iterator
  idxIter++;

  // check if the index iterator is at the end of the current vector
  if (idxIter == valIter->second.end()) {
    // increment the value iterator
    valIter++;

    // check if the value iterator is at the end of the map
    if (valIter == data->end()) {
      // set the value iterator to the end of the map
      valIter = data->end();
      return;
    }

    // set the index to the beginning of the next vector
    index = *(valIter->second.begin());
    idxIter = valIter->second.begin();
    val = valIter->first;
    return;
  }

  // set the index to the next index in the current vector
  index = *idxIter;
  return;

    }  // end operator++

}  // end namespace IVSparse