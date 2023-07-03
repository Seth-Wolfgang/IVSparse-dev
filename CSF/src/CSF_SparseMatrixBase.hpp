#pragma once

namespace CSF {

    class SparseMatrixBase {

        private:

        //* The Matrix Info *//
        uint32_t innerDim = 0; // The inner dimension of the matrix
        uint32_t outerDim = 0; // The outer dimension of the matrix

        uint32_t numRows = 0; // The number of rows in the matrix
        uint32_t numCols = 0; // The number of columns in the matrix

        uint32_t nnz = 0; // The number of non-zero values in the matrix

        size_t compSize = 0; // The size of the compressed matrix in bytes

        //* The Value and Index Types *//
        uint32_t val_t;   // Information about the value type (size, signededness, etc.)
        uint32_t index_t; // Information about the index type (size)

        uint32_t *metadata = nullptr; // The metadata of the matrix

        //* Private Methods *//

        inline uint8_t byteWidth(size_t size);

        virtual void encodeValueType() = 0;

        virtual void checkValueType() = 0;

        virtual void userChecks() = 0;

        virtual void calculateCompSize() = 0;
        
        public:

        template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
        friend class SparseMatrix;

        //* Constructors *//

        SparseMatrixBase() {};

        //* Getters *//

        template <typename T>
        T coeff(uint32_t row, uint32_t col);

        uint32_t rows() const;

        uint32_t cols() const;

        uint32_t innerSize() const;

        uint32_t outerSize() const;

        uint32_t nonZeros() const;

        size_t byteSize() const;

        virtual void write(const char *filename) = 0;

        virtual void print() = 0;

    };



}