#pragma once

// Debug flag for performance testing (set to true to be faster)
#define DEBUG false

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

        mat.makeCompressed();

        // Set the number of rows, columns and non-zero elements
        innerDim = mat.rows();
        outerDim = mat.cols();

        numRows = mat.rows();
        numCols = mat.cols();

        nnz = mat.nonZeros();
        
        compress(mat.valuePtr(), mat.innerIndexPtr(), mat.outerIndexPtr());
    }

    //Untested constrctor for Sparse Matrix from an array of vectors
    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    SparseMatrix<T, indexT, compressionLevel, columnMajor>::SparseMatrix(CSF::SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector vec[])
    {

        // Set the number of rows, columns and non-zero elements
        innerDim = vec.innerSize();
        outerDim = sizeof(vec / sizeof(vec[0]));

        numRows = innerDim;
        numCols = outerDim;

        nnz = 0;

        data = malloc(outerDim * sizeof(void *));
        for(int i = 0; i < outerDim; i++){
            data[i] = malloc(vec[i].byteSize());
            memcpy(data[i], vec[i].begin(), vec[i].byteSize());
            nnz += vec[i].nonZeros();
        }

        //TODO: replace with .append() method when implemented
        // for(auto v : vec){
        //     *this.append(v);
        // }
        
    }

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    SparseMatrix<T, indexT, compressionLevel, columnMajor>::SparseMatrix(Eigen::SparseMatrix<T, Eigen::RowMajor> &mat)
    {

        mat.makeCompressed();

        // Set the number of rows, columns and non-zero elements
        innerDim = mat.cols();
        outerDim = mat.rows();

        numRows = mat.rows();
        numCols = mat.cols();

        nnz = mat.nonZeros();

        compress(mat.valuePtr(), mat.innerIndexPtr(), mat.outerIndexPtr());
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