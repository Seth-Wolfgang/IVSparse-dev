#pragma once

// Debug flag for performance testing (set to true to be faster)
#define DEBUG true

// Number of meta data values
#define NUM_META_DATA 6

// Standard Libraries for include
#include <type_traits>
#include <iostream>
#include <iomanip>

namespace CSF {

    template <typename T, typename T_index, uint8_t compression_level>
    SparseMatrix<T, T_index, compression_level>::SparseMatrix() {}

    template <typename T, typename T_index, uint8_t compression_level>
    SparseMatrix<T, T_index, compression_level>::SparseMatrix(Eigen::SparseMatrix<T> &mat) {
        // Set the number of rows, columns and non-zero elements
        rows = mat.rows();
        cols = mat.cols();
        nnz = mat.nonZeros();

        compressCSC(mat.valuePtr(), mat.innerIndexPtr(), mat.outerIndexPtr());
        
        // for (size_t i = 0; i < cols; i++) {
            // std::cout << "Col " << getColSize(i) << std::endl;
            // std::cout << ((uint64_t*)data[i]) << " To " << ((uint64_t*)data[i] + getColSize(i)) << std::endl;
        // }




    }

    template <typename T, typename T_index, uint8_t compression_level>
    SparseMatrix<T, T_index, compression_level>::~SparseMatrix() {
        // delete the meta data
        delete[] meta_data;

        // free the data
        for (size_t i = 0; i < cols; i++) {
            free(data[i]);
        }

        // free data
        free(data);

        // free the end pointers
        free(end_pointers);
    }

}