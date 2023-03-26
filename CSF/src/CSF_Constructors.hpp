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

    // TODO: Test the array of vectors constructor
    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    SparseMatrix<T, indexT, compressionLevel, columnMajor>::SparseMatrix(CSF::SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector vec[], size_t size)
    {
        // ensure the vectors are all the same length
        for (size_t i = 1; i < size; i++)
        {
            if (vec[i].length() != vec[0].length())
            {
                std::cerr << "Error: Vectors are not all the same length" << std::endl;
                exit(1);
            }
        }

        if (columnMajor)
        {
            outerDim = size;
            innerDim = vec[0].length();
            numCols = size;
            numRows = vec[0].length();
        }
        else
        {
            outerDim = vec[0].length();
            innerDim = size;
            numCols = vec[0].length();
            numRows = size;
        }

        //allocate memory for data
        try {
            data = (void**)malloc(outerDim * sizeof(void *));
            endPointers = (void**)malloc(outerDim * sizeof(void *));
        } catch (const std::exception& e) {
            std::cerr << e.what() << '\n';
        }

        for (size_t i = 0; i < outerDim; i++)
        {
            try {
                data[i] = malloc(vec[i].byteSize());
            } catch (const std::exception& e) {
                std::cerr << e.what() << '\n';
            }
            memcpy(data[i], vec[i].data(), vec[i].byteSize());
            endPointers[i] = (char*)data[i] + vec[i].byteSize();

            nnz += vec[i].nonZeros();
            compSize += vec[i].byteSize();
        }

        //  set the val_t and index_t
        val_t = encodeVal();
        index_t = sizeof(indexT);

        // malloc space for the meta data
        metadata = new uint32_t[NUM_META_DATA];

        // Set the meta data
        metadata[0] = compressionLevel;
        metadata[1] = innerDim;
        metadata[2] = outerDim;
        metadata[3] = nnz;
        metadata[4] = val_t;
        metadata[5] = index_t;

        compSize += NUM_META_DATA * sizeof(uint32_t) + (outerDim * sizeof(void *) * 2);

        // run the user checks
        if constexpr (DEBUG)
            userChecks();
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

    //TODO: Deep Copy Constructor (largely untested)
    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    SparseMatrix<T, indexT, compressionLevel, columnMajor>::SparseMatrix(CSF::SparseMatrix<T, indexT, compressionLevel, columnMajor> &mat)
    {
        // Set the number of rows, columns and non-zero elements
        innerDim = mat.innerSize();
        outerDim = mat.outerSize();

        numRows = mat.rows();
        numCols = mat.cols();

        nnz = mat.nonZeros();

        compSize = mat.compressionSize();

        //allocate memory for data, I think something in here fails
        try {
            data = (void**)malloc(outerDim * sizeof(void *));
            endPointers = (void**)malloc(outerDim * sizeof(void *));
        } catch (const std::exception& e) {
            std::cerr << e.what() << '\n';
        }

        for (size_t i = 0; i < outerDim; i++)
        {
            try {
                data[i] = malloc(mat.getVecSize(i));
            } catch (const std::exception& e) {
                std::cerr << e.what() << '\n';
            }
            memcpy(data[i], mat.getVecPointer(i), mat.getVecSize(i));
            endPointers[i] = (char*)data[i] + mat.getVecSize(i);
        }

        //allocate memory for metadata
        metadata = new uint32_t[NUM_META_DATA];
        for (size_t i = 0; i < NUM_META_DATA; i++)
        {
            metadata[i] = mat.metadata[i];
        }

        index_t = mat.index_t;

        encodeVal();

        userChecks();
    }

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    SparseMatrix<T, indexT, compressionLevel, columnMajor>::SparseMatrix(std::map<indexT, std::unordered_map<T, std::vector<indexT>>> &map, uint32_t num_rows, uint32_t num_cols)
    {
        // set class variables
        if constexpr (columnMajor) {
            innerDim = num_rows;
            outerDim = num_cols;
        } else {
            innerDim = num_cols;
            outerDim = num_rows;
        }

        numRows = num_rows;
        numCols = num_cols;

        val_t = encodeVal();
        index_t = sizeof(indexT);

        // allocate memory for the data
        try {
            data = (void**)malloc(outerDim * sizeof(void *));
            endPointers = (void**)malloc(outerDim * sizeof(void *));
        } catch (const std::exception& e) {
            std::cerr << e.what() << '\n';
        }

        
    }

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    SparseMatrix<T, indexT, compressionLevel, columnMajor>::~SparseMatrix()
    {
        // delete the meta data
        if (metadata != nullptr) {
            delete[] metadata;
        }

        // free the data
        for (size_t i = 0; i < outerDim; i++)
        {
            if (data[i] != nullptr)
                free(data[i]);
        }

        // free data
        if (data != nullptr)
            free(data);

        // free the end pointers
        if (endPointers != nullptr)
            free(endPointers);
    }

}