/**
 * @file CSF1_SparseMatrix.hpp
 * @author Skyler Ruiter and Seth Wolfgang
 * @brief  The CSF1 Sparse Matrix Class Definitions
 * @version 0.1
 * @date 2023-06-22
 */

#pragma once

namespace CSF
{

    /**
     * @tparam T The data type of the values in the matrix
     * @tparam indexT The data type of the indices in the matrix
     * @tparam columnMajor Whether the matrix is stored in column major format
     * 
     * The Compression Level 1 CSF Template Specialized Class \n \n
     * This class is the template specialization of the CSF::SparseMatrix class for compression level 1.
     * It is the most basic CSF matrix and is uses CSC storage as an interface between easier to use formats and 
     * deeper compression levels of CSF.
     */
    template <typename T, typename indexT, bool columnMajor>
    class SparseMatrix<T, indexT, 1, columnMajor>
    {
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

        //* The Matrix Data *//
        T *vals = nullptr; // The values of the matrix
        indexT *innerIdx = nullptr; // The inner indices of the matrix
        indexT *outerPtr = nullptr; // The outer pointers of the matrix

        uint32_t *metadata = nullptr; // The metadata of the matrix

        //* Private Class Methods *//

        // Small method to calcuate the size a value takes up in bytes
        inline uint8_t byteWidth(size_t size);

        // Takes info about the value type and encodes it into a single uint32_t
        void encodeValueType();

        // Checks the value type matches the class template T
        void checkValueType();

        // Does checks on the class to ensure it is valid
        void userChecks();

        // Converts the CSF1 Matrix to CSF2
        CSF::SparseMatrix<T, indexT, 2, columnMajor> toCSF2();

        // Converts the CSF1 Matrix to CSF3
        CSF::SparseMatrix<T, indexT, 3, columnMajor> toCSF3();

        public:
        //* Nested Subclasses *//

        // Vector Class
        class Vector;

        // Iterator Classes
        class InnerIterator;

        //* Constructors & Destructor *//

        //* Constructors *//
        /** @name Constructors
         */
        ///@{

        /**
         * Construct an empty CSF1 matrix \n \n
         * The matrix will have 0 rows and 0 columns and
         * will not be initialized with any values. All data
         * will be set to nullptr.
         *
         * @warning This constructor is not recommended for use as updating a CSF matrix is not well supported.
         */
        SparseMatrix();

        /**
         * @param mat The Eigen Sparse Matrix to be compressed
         *
         * Eigen Sparse Matrix Constructor \n \n
         * This constructor takes an Eigen Sparse Matrix and compresses it into a CSF1 matrix.
         */
        SparseMatrix(Eigen::SparseMatrix<T> &mat);

        /**
         * @param mat The Eigen Sparse Matrix to be compressed
         *
         * Eigen Sparse Matrix Constructor (Row Major) \n \n
         * Same as previous constructor but for Row Major Eigen Sparse Matrices.
         */
        SparseMatrix(Eigen::SparseMatrix<T, Eigen::RowMajor> &mat);

        /**
         * @tparam otherCompressionLevel The compression level of the CSF matrix to convert
         * @param mat The CSF matrix to convert
         *
         * Convert a CSF matrix of a different compression level to level 1. \n \n
         * This constructor takes in a CSF matrix of the same storage order, value, and index type and converts it to
         * CSC format. This is useful for converting between compression levels without having to
         * go through the CSC format.
         *
         * @note Needs More Testing also not a copying constructor.
         */
        template <uint8_t otherCompressionLevel>
        SparseMatrix(CSF::SparseMatrix<T, indexT, otherCompressionLevel, columnMajor> &mat);

        /**
         * @param other The CSF matrix to be copied
         *
         * Deep Copy Constructor \n \n
         * This constructor takes in a CSF matrix and creates a deep copy of it.
         *
         * @note Needs More Testing
         */
        SparseMatrix(const CSF::SparseMatrix<T, indexT, 1, columnMajor> &other);

        /**
         * Raw CSC Constructor \n \n
         * This constructor takes in raw CSC storage format pointers and converts it to a CSF1 matrix.
         * One could also take this information and convert to an Eigen Sparse Matrix and then to a CSF1 matrix.
         *
         * @note Needs More Testing
         */
        template <typename T2, typename indexT2>
        SparseMatrix(T2 *vals, indexT2 *innerIndices, indexT2 *outerPtr, uint32_t num_rows, uint32_t num_cols, uint32_t nnz);

        /**
         * @param vec The vector to construct the matrix from
         *
         * CSF1 Vector Constructor \n \n
         * This constructor takes in a single CSF1 vector and creates a one column/row CSF1 matrix.
         *
         * @note Needs More Testing
         */
        SparseMatrix(typename CSF::SparseMatrix<T, indexT, 1, columnMajor>::Vector &vec);

        /**
         * @param filename The filepath of the matrix to be read in
         *
         * File Constructor \n \n
         * Given a filepath to a CSF1 matrix written to file this constructor will read in the matrix and construct it.
         *
         * @note Needs More Testing
         */
        SparseMatrix(const char *filename);

        /**
         * @brief Destroy the Sparse Matrix object
         */
        ~SparseMatrix();

        ///@}

        //* Utility Methods *//
        /**
         * @name Utility Methods
         */
        ///@{

        /**
         * @param filename The filename of the matrix to write to
         *
         * This method writes the CSF matrix to a file in binary format.
         * This can then be read in later using the file constructor.
         * Currently .csf is the perfered file extension.
         *
         * @note Useful to split a matrix up and then write each part separately.
         */
        void write(const char *filename);

        /**
         * Prints "CSF Matrix:" followed by the dense representation of the matrix to the console.
         *
         * @note Useful for debugging but only goes up to 100 of either dimension.
         */
        void print();

        /**
         * @returns true If the matrix is stored in column major format
         * @returns false If the matrix is stored in row major format
         *
         * See the storage order of the CSF matrix.
         */
        bool isColumnMajor() const;

        ///@}

        //* Getters *//
        /**
         * @name Getters
         */
        ///@{

        /**
         * @returns T The value at the specified row and column. Returns 0 if the value is not found.
         *
         * Get the value at the specified row and column
         *
         * @note Users cannot update individual values in a CSF matrix.
         *
         * @warning This method is not efficient and should not be used in performance critical code.
         */
        T coeff(uint32_t row, uint32_t col);

        /**
         * @param vec The vector to get a copy of
         * @returns Vector The vector copy returned
         *
         * Get a copy of a CSF1 vector from the CSF1 matrix such as the first column.
         *
         * @note Can only get vectors in the storage order of the matrix.
         */
        typename CSF::SparseMatrix<T, indexT, 1, columnMajor>::Vector getVector(uint32_t vec);

        /**
         * @param vec The vector to get the size of
         * @returns size_t The size of the vector
         *
         * Get the size of a vector in the CSF matrix in bytes.
         *
         * @note Can only get vectors in the storage order of the matrix.
         */
        size_t getVectorSize(uint32_t vec) const;

        /**
         * @returns The Inner Dimension of the matrix
         */
        uint32_t innerSize() const;

        /**
         * @returns The Outer Dimension of the matrix
         */
        uint32_t outerSize() const;

        /**
         * @returns The number of rows in the matrix
         */
        uint32_t rows() const;

        /**
         * @returns The number of columns in the matrix
         */
        uint32_t cols() const;

        /**
         * @returns The number of non-zero entries in the matrix
         */
        uint32_t nonZeros() const;

        /**
         * @returns The total number of bytes the matrix takes up in memory
         */
        size_t byteSize() const;

        /**
         * @returns A Pointer to the values of the CSC matrix
         */
        T *values();

        /**
         * @returns A Pointer to the inner indices of the CSC matrix
         */
        indexT *innerIdxPtr();

        /**
         * @returns A Pointer to the outer pointers of the CSC matrix
         */
        indexT *outerPtrs();

        ///@}

        //* Matrix Manipulation Methods *//
        /**
         * @name Matrix Manipulation Methods
         */
        ///@{

        /**
         * @returns An Eigen Sparse Matrix constructed from the CSF matrix data.
         */
        Eigen::SparseMatrix<T> toEigen();

        /**
         * @returns A transposed version of the CSF matrix.
         */
        CSF::SparseMatrix<T, indexT, 1, columnMajor> transpose();

        /**
         * Transposes the matrix in place instead of returning a new matrix.
         */
        void inPlaceTranspose();

        /**
         * @param vec The vector to append to the matrix in the correct storage order.
         *
         * Appends a CSF vector to the current matrix in the storage order of the matrix.
         */
        void append(typename SparseMatrix<T, indexT, 1, columnMajor>::Vector &vec);

        ///@}

        //* Operator Overloads *//

        // Assignment Operator
        CSF::SparseMatrix<T, indexT, 1, columnMajor> &operator=(const CSF::SparseMatrix<T, indexT, 1, columnMajor> &other);

        // Equality Operators
        bool operator==(const SparseMatrix<T, indexT, 1, columnMajor> &other);
        bool operator!=(const SparseMatrix<T, indexT, 1, columnMajor> &other);

        // Coefficient Access Operator
        T operator()(uint32_t row, uint32_t col);

        // Vector Access Operator
        typename CSF::SparseMatrix<T, indexT, 1, columnMajor>::Vector operator[](uint32_t vec);
    };

}