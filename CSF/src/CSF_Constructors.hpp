#pragma once

// Debug flag for performance testing (set to true to be faster)
#define DEBUG true

// Number of meta data values
#define NUM_META_DATA 6

// Standard Libraries for include
#include <type_traits>
#include <iostream>
#include <iomanip>

namespace CSF
{

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    SparseMatrix<T, indexT, compressionLevel, columnMajor>::SparseMatrix() {}

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    SparseMatrix<T, indexT, compressionLevel, columnMajor>::SparseMatrix(Eigen::SparseMatrix<T> &mat)
    {
        // Set the number of rows, columns and non-zero elements
        if (columnMajor) {
            innerDim = mat.rows();
            outerDim = mat.cols();
        } else {
            innerDim = mat.cols();
            outerDim = mat.rows();
        }
        nnz = mat.nonZeros();

        if (columnMajor) {
            compress(mat.valuePtr(), mat.innerIndexPtr(), mat.outerIndexPtr());
        } else {
            compress(mat.valuePtr(), mat.outerIndexPtr(), mat.innerIndexPtr());
        }
    }

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    SparseMatrix<T, indexT, compressionLevel, columnMajor>::~SparseMatrix()
    {
        // delete the meta data
        delete[] metadata;

        // free the data
        for (size_t i = 0; i < outerDim; i++)
        {
            free(data[i]);
        }

        // free data
        free(data);

        // free the end pointers
        free(endPointers);
    }

}