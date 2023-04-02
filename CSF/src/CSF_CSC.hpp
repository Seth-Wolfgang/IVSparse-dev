#pragma once

#include <iostream>

#define DELIM 0

#define META_DATA_SIZE 24
#define NUM_META_DATA 6

#define ONE_BYTE_MAX 255
#define TWO_BYTE_MAX 65535
#define FOUR_BYTE_MAX 4294967295

#define DEBUG false

// for CSF1 details

namespace CSF {

    //* Constructors & Destructor *//

    // default empty constructor
    template <typename T, typename indexT, bool columnMajor>
    SparseMatrix<T, indexT, 1, columnMajor>::SparseMatrix() {
        
    }

    // eigen sparse matrix constructor
    template <typename T, typename indexT, bool columnMajor>
    SparseMatrix<T, indexT, 1, columnMajor>::SparseMatrix(Eigen::SparseMatrix<T> &mat) {
        
        mat.makeCompressed();

        innerDim = mat.innerSize();
        outerDim = mat.outerSize();

        numRows = mat.rows();
        numCols = mat.cols();

        nnz = mat.nonZeros();

        val_t = encodeVal();
        index_t = sizeof(indexT);

        compSize = sizeof(T) * nnz + sizeof(indexT) * (nnz + outerDim + 1) + META_DATA_SIZE;

        vals = new T[nnz];
        innerIdx = new indexT[nnz];
        outerPtr = new indexT[outerDim + 1];

        metadata = new uint32_t[NUM_META_DATA];

        metadata[0] = 1;
        metadata[1] = innerDim;
        metadata[2] = outerDim;
        metadata[3] = nnz;
        metadata[4] = val_t;
        metadata[5] = index_t;

        memcpy(vals, mat.valuePtr(), sizeof(T) * nnz);
        memcpy(innerIdx, mat.innerIndexPtr(), sizeof(indexT) * nnz);
        memcpy(outerPtr, mat.outerIndexPtr(), sizeof(indexT) * (outerDim + 1));

        // run user checks
        if (DEBUG) { userChecks(); }
    }

    // eigen sparse matrix constructor (row major)
    template <typename T, typename indexT, bool columnMajor>
    SparseMatrix<T, indexT, 1, columnMajor>::SparseMatrix(Eigen::SparseMatrix<T, Eigen::RowMajor> &mat)
    {
        mat.makeCompressed();

        innerDim = mat.innerSize();
        outerDim = mat.outerSize();

        numRows = mat.rows();
        numCols = mat.cols();

        nnz = mat.nonZeros();

        val_t = encodeVal();
        index_t = sizeof(indexT);

        compSize = sizeof(T) * nnz + sizeof(indexT) * (nnz + outerDim + 1) + META_DATA_SIZE;

        vals = new T[nnz];
        innerIdx = new indexT[nnz];
        outerPtr = new indexT[outerDim + 1];

        metadata = new uint32_t[NUM_META_DATA];

        metadata[0] = 1;
        metadata[1] = innerDim;
        metadata[2] = outerDim;
        metadata[3] = nnz;
        metadata[4] = val_t;
        metadata[5] = index_t;

        memcpy(vals, mat.valuePtr(), sizeof(T) * nnz);
        memcpy(innerIdx, mat.innerIndexPtr(), sizeof(indexT) * nnz);
        memcpy(outerPtr, mat.outerIndexPtr(), sizeof(indexT) * (outerDim + 1));

        // run user checks
        if (DEBUG) { userChecks(); }
    }

    // deep copy constructor
    template <typename T, typename indexT, bool columnMajor>
    SparseMatrix<T, indexT, 1, columnMajor>::SparseMatrix(CSF::SparseMatrix<T, indexT, 1, columnMajor> &mat)
    {
        innerDim = mat.innerDim;
        outerDim = mat.outerDim;

        numRows = mat.numRows;
        numCols = mat.numCols;

        nnz = mat.nnz;

        val_t = mat.val_t;
        index_t = mat.index_t;

        compSize = mat.compSize;

        vals = new T[nnz];
        innerIdx = new indexT[nnz];
        outerPtr = new indexT[outerDim + 1];

        metadata = new uint32_t[NUM_META_DATA];

        metadata[0] = 1;
        metadata[1] = innerDim;
        metadata[2] = outerDim;
        metadata[3] = nnz;
        metadata[4] = val_t;
        metadata[5] = index_t;

        memcpy(vals, mat.vals, sizeof(T) * nnz);
        memcpy(innerIdx, mat.innerIdx, sizeof(indexT) * nnz);
        memcpy(outerPtr, mat.outerPtr, sizeof(indexT) * (outerDim + 1));

        // run user checks
        if (DEBUG) { userChecks(); }
    }

    // file constructor
    template <typename T, typename indexT, bool columnMajor>
    SparseMatrix<T, indexT, 1, columnMajor>::SparseMatrix(const char *filename)
    {

    }

    // COO constructor
    // TODO: add support for this constructor

    // destructor
    template <typename T, typename indexT, bool columnMajor>
    SparseMatrix<T, indexT, 1, columnMajor>::~SparseMatrix()
    {
        if (vals != nullptr) { delete[] vals; }
        if (innerIdx != nullptr) { delete[] innerIdx; }
        if (outerPtr != nullptr) { delete[] outerPtr; }
        if (metadata != nullptr) { delete[] metadata; }
    }

    //* Private Class Methods *//

    template <typename T, typename indexT, bool columnMajor>
    uint8_t SparseMatrix<T, indexT, 1, columnMajor>::byteWidth(size_t size) {
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

    template <typename T, typename indexT, bool columnMajor>
    uint32_t SparseMatrix<T, indexT, 1, columnMajor>::encodeVal() {
        uint8_t byte0 = sizeof(T);
        uint8_t byte1 = std::is_floating_point<T>::value ? 1 : 0;
        uint8_t byte2 = std::is_signed_v<T> ? 1 : 0;
        uint8_t byte3 = 0;

        return (byte3 << 24) | (byte2 << 16) | (byte1 << 8) | byte0;
    }

    template <typename T, typename indexT, bool columnMajor>
    void SparseMatrix<T, indexT, 1, columnMajor>::checkVal() {
        uint8_t byte0 = val_t & 0xFF;
        uint8_t byte1 = (val_t >> 8) & 0xFF;
        uint8_t byte2 = (val_t >> 16) & 0xFF;
        // uint8_t byte3 = (val_t >> 24) & 0xFF;

        if (byte0 != sizeof(T))
        {
            std::cout << "Error: Value type size does not match" << std::endl;
            throw std::runtime_error("Value type size does not match, correct size is " + std::to_string(sizeof(T)) + "");
        }

        if (byte1 != std::is_floating_point_v<T>)
        {
            std::cout << "Error: Value type is not floating point" << std::endl;
            throw std::runtime_error("Value type is not floating point when it should be");
        }

        if (byte2 != std::is_signed_v<T>)
        {
            std::cout << "Error: Value type is not signed" << std::endl;
            throw std::runtime_error("Value type is not signed when it should be");
        }
    }

    template <typename T, typename indexT, bool columnMajor>
    void SparseMatrix<T, indexT, 1, columnMajor>::userChecks()
    {
        // throw an error if the matrix has less than one rows or columns or nonzero values
        if (innerDim < 1 || outerDim < 1 || nnz < 1)
            throw std::invalid_argument("The matrix must have at least one row, column, and nonzero value");

        // check that indexT is not floating point
        if (std::is_floating_point<indexT>::value)
            throw std::invalid_argument("The index type must be a non-floating point type");

        // check that T and indexT are numeric types
        if (!std::is_arithmetic<T>::value || !std::is_arithmetic<indexT>::value)
            throw std::invalid_argument("The value and index types must be numeric types");

        // check that the index type is not a bool
        if (std::is_same<indexT, bool>::value)
            throw std::invalid_argument("The value and index types must not be bool");

        // check that the row and col types can hold the number of rows and columns
        if (innerDim > std::numeric_limits<indexT>::max() || outerDim > std::numeric_limits<indexT>::max())
            throw std::invalid_argument("The number of rows and columns must be less than the maximum value of the index type");

        checkVal();
    }

    //* Utility Methods *//

    template <typename T, typename indexT, bool columnMajor>
    void SparseMatrix<T, indexT, 1, columnMajor>::print()
    {

    }

    template <typename T, typename indexT, bool columnMajor>
    void SparseMatrix<T, indexT, 1, columnMajor>::write(const char *filename)
    {

    }

    //* Getters & Setters *//

    template <typename T, typename indexT, bool columnMajor>
    uint32_t SparseMatrix<T, indexT, 1, columnMajor>::innerSize() { return innerDim; }

    template <typename T, typename indexT, bool columnMajor>
    uint32_t SparseMatrix<T, indexT, 1, columnMajor>::outerSize() { return outerDim; }

    template <typename T, typename indexT, bool columnMajor>
    uint32_t SparseMatrix<T, indexT, 1, columnMajor>::rows() { return numRows; }

    template <typename T, typename indexT, bool columnMajor>
    uint32_t SparseMatrix<T, indexT, 1, columnMajor>::cols() { return numCols; }

    template <typename T, typename indexT, bool columnMajor>
    uint32_t SparseMatrix<T, indexT, 1, columnMajor>::nonZeros() { return nnz; }

    template <typename T, typename indexT, bool columnMajor>
    size_t SparseMatrix<T, indexT, 1, columnMajor>::compressionSize() { return compSize; }

    template <typename T, typename indexT, bool columnMajor>
    T *SparseMatrix<T, indexT, 1, columnMajor>::values() { return vals; }

    template <typename T, typename indexT, bool columnMajor>
    indexT *SparseMatrix<T, indexT, 1, columnMajor>::innerIdxPtr() { return innerIdx; }

    template <typename T, typename indexT, bool columnMajor>
    indexT *SparseMatrix<T, indexT, 1, columnMajor>::outerPtrs() { return outerPtr; }

    //* Conversion Methods *//

    template <typename T, typename indexT, bool columnMajor>
    Eigen::SparseMatrix<T> SparseMatrix<T, indexT, 1, columnMajor>::toEigen() 
    {

    }

    template <typename T, typename indexT, bool columnMajor>
    CSF::SparseMatrix<T, indexT, 2, columnMajor > SparseMatrix<T, indexT, 1, columnMajor>::toCSF2()
    {

    }

    template <typename T, typename indexT, bool columnMajor>
    CSF::SparseMatrix<T, indexT, 3, columnMajor> SparseMatrix<T, indexT, 1, columnMajor>::toCSF3()
    {

    }

    template <typename T, typename indexT, bool columnMajor>
    CSF::SparseMatrix<T, indexT, 1, columnMajor> SparseMatrix<T, indexT, 1, columnMajor>::transpose()
    {

    }

    template <typename T, typename indexT, bool columnMajor>
    void SparseMatrix<T, indexT, 1, columnMajor>::append(SparseMatrix<T, indexT, 1, columnMajor>::Vector &vec)
    {

    }

    //* Overloaded Operators *//

    template <typename T, typename indexT, bool columnMajor>
    bool SparseMatrix<T, indexT, 1, columnMajor>::operator==(const SparseMatrix<T, indexT, 1, columnMajor> &other)
    {
        return false;
    }

    template <typename T, typename indexT, bool columnMajor>
    bool SparseMatrix<T, indexT, 1, columnMajor>::operator!=(const SparseMatrix<T, indexT, 1, columnMajor> &other)
    {
        return false;
    }

    template <typename T, typename indexT, bool columnMajor>
    T SparseMatrix<T, indexT, 1, columnMajor>::operator()(uint32_t row, uint32_t col)
    {

    }

    //* CSF1 InnerIterator Class *//


        //* Private Methods *//


        //* Constructors & Destructor *//


        //* Overloaded Operators *//


        //* Getters & Setters *//


        //* Utility Methods *//



    //* End of CSF1 InnerIterator Class *//

    //* CSF1 Vector Class *//

        //* Constructors & Destructor *//

        template <typename T, typename indexT, bool columnMajor>
        SparseMatrix<T, indexT, 1, columnMajor>::Vector::Vector() 
        {

        }

        template <typename T, typename indexT, bool columnMajor>
        SparseMatrix<T, indexT, 1, columnMajor>::Vector::Vector(CSF::SparseMatrix<T, indexT, 1, columnMajor> &mat, uint32_t vec) 
        {

        }

        template <typename T, typename indexT, bool columnMajor>
        SparseMatrix<T, indexT, 1, columnMajor>::Vector::Vector(CSF::SparseMatrix<T, indexT, 1, columnMajor>::Vector &vec) 
        {

        }

        template <typename T, typename indexT, bool columnMajor>
        SparseMatrix<T, indexT, 1, columnMajor>::Vector::~Vector() 
        {

        }

        //* Getters *//

        template <typename T, typename indexT, bool columnMajor>
        uint32_t SparseMatrix<T, indexT, 1, columnMajor>::Vector::length() { return vecLength; }

        template <typename T, typename indexT, bool columnMajor>
        uint32_t SparseMatrix<T, indexT, 1, columnMajor>::Vector::nonZeros()  { return nnz; }

        template <typename T, typename indexT, bool columnMajor>
        T *SparseMatrix<T, indexT, 1, columnMajor>::Vector::values() { return vals; }

        template <typename T, typename indexT, bool columnMajor>
        indexT *SparseMatrix<T, indexT, 1, columnMajor>::Vector::indexPtr() { return indices; }

        template <typename T, typename indexT, bool columnMajor>
        size_t SparseMatrix<T, indexT, 1, columnMajor>::Vector::byteSize() { return size; }

        //* Overloaded Operators *//

        template <typename T, typename indexT, bool columnMajor>
        T SparseMatrix<T, indexT, 1, columnMajor>::Vector::operator[](uint32_t index) 
        {

        }

        //* Utility Methods *//

        template <typename T, typename indexT, bool columnMajor>
        void SparseMatrix<T, indexT, 1, columnMajor>::Vector::write(const char *filename)
        {

        }

    //* End CSF1 Vector Class *//

    //* Misc. Methods *//
}