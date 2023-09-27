/**
 * @file VCSC_Private_Methods.hpp
 * @author Skyler Ruiter and Seth Wolfgang
 * @brief Private Methods for VCSC Sparse Matrices
 * @version 0.1
 * @date 2023-07-03
 */

#pragma once

namespace IVSparse {

    // Encodes the value type of the matrix in a uint32_t
    template <typename T, typename indexT, bool columnMajor>
    void SparseMatrix<T, indexT, 2, columnMajor>::encodeValueType() {
        uint8_t byte0 = sizeof(T);
        uint8_t byte1 = std::is_floating_point<T>::value ? 1 : 0;
        uint8_t byte2 = std::is_signed_v<T> ? 1 : 0;
        uint8_t byte3 = columnMajor ? 1 : 0;

        val_t = (byte3 << 24) | (byte2 << 16) | (byte1 << 8) | byte0;
    }

    // Checks if the value type is correct for the matrix
    template <typename T, typename indexT, bool columnMajor>
    void SparseMatrix<T, indexT, 2, columnMajor>::checkValueType() {
        uint8_t byte0 = val_t & 0xFF;
        uint8_t byte1 = (val_t >> 8) & 0xFF;
        uint8_t byte2 = (val_t >> 16) & 0xFF;
        uint8_t byte3 = (val_t >> 24) & 0xFF;
        assert(byte0 == sizeof(T) && "Value type size does not match");
        assert(byte1 == std::is_floating_point_v<T> &&
               "Value type is not floating point");
        assert(byte2 == std::is_signed_v<T> && "Value type is not signed");
        assert(byte3 == columnMajor && "Major direction does not match");
    }

    // performs some simple user checks on the matrices metadata
    template <typename T, typename indexT, bool columnMajor>
    void SparseMatrix<T, indexT, 2, columnMajor>::userChecks() {
        assert((innerDim > 1 || outerDim > 1 || nnz > 1) &&
               "The matrix must have at least one row, column, and nonzero value");
        assert(std::is_floating_point<indexT>::value == false &&
               "The index type must be a non-floating point type");
        assert((std::is_arithmetic<T>::value && std::is_arithmetic<indexT>::value) &&
               "The value and index types must be numeric types");
        assert((std::is_same<indexT, bool>::value == false) &&
               "The index type must not be bool");
        assert((innerDim < std::numeric_limits<indexT>::max() &&
                outerDim < std::numeric_limits<indexT>::max()) &&
               "The number of rows and columns must be less than the maximum value "
               "of the index type");
        checkValueType();
    }

    // Calculates the current byte size of the matrix in memory
    template <typename T, typename indexT, bool columnMajor>
    void SparseMatrix<T, indexT, 2, columnMajor>::calculateCompSize() {
        // set compSize to zero
        compSize = 0;

        // add the size of the metadata
        // compSize += META_DATA_SIZE;

  // iterate through the map and add the size of each column
  for (uint32_t i = 0; i < outerDim; i++) {
    compSize += sizeof(T) * data[i].size(); //values
    compSize += sizeof(indexT) * data[i].size(); // counts

    // iterate over the map and get all the indices
    for (auto it = data[i].begin(); it != data[i].end(); ++it) {
      compSize += sizeof(indexT) * it->second.size();
    }

    compSize += sizeof(indexT); // len
  }
}

    // Compression Algorithm for going from CSC to IVCSC
    template <typename T, typename indexT, bool columnMajor>
    template <typename T2, typename indexT2>
    void SparseMatrix<T, indexT, 2, columnMajor>::compressCSC(T2* vals, indexT2* innerIndices, indexT2* outerPointers) {
        // ---- Stage 1: Setup the Matrix ---- //

        // set the value and index types of the matrix
        encodeValueType();
        index_t = sizeof(indexT);

        // allocate space for metadata
        metadata = new uint32_t[NUM_META_DATA];
        metadata[0] = 2;
        metadata[1] = innerDim;
        metadata[2] = outerDim;
        metadata[3] = nnz;
        metadata[4] = val_t;
        metadata[5] = index_t;

        // run the user checks on the metadata
        #ifdef IVSPARSE_DEBUG
        userChecks();
        #endif

  data.reserve(outerDim);

        // ---- Stage 2: Construct the Dictionary For Each Column ---- //

  // Loop through each column and construct a middle data structre for the matrix
  #ifdef IVSPARSE_HAS_OPENMP
  #pragma omp parallel for
  #endif
  for (uint32_t i = 0; i < outerDim; i++) {

    // get the map for the current column
    data[i] = std::unordered_map<T, std::vector<indexT>>();


    // check if the current column is empty
    if (outerPointers[i] == outerPointers[i + 1]) {
      continue;
    }

    // loop through each value in the column and add it to dict
    for (indexT2 j = outerPointers[i]; j < outerPointers[i + 1]; j++) {

      // check if the value is already in the dictionary or not
      if (data[i].find(vals[j]) != data[i].end()) {

        // add the index
        data[i][vals[j]].push_back(innerIndices[j]);

      } else {
        // add the value
        data[i][vals[j]] = std::vector<indexT>{innerIndices[j]};
      }

            }  // end value loop

  }  // end column loop

        calculateCompSize();

    }  // end compressCSC

}  // end namespace IVSparse