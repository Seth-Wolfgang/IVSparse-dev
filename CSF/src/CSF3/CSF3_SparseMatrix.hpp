/**
 * @file CSF3_SparseMatrix.hpp
 * @author Skyler Ruiter and Seth Wolfgang
 * @brief CSF3 Sparse Matrix Class Declarations
 * @version 0.1
 * @date 2023-07-03
 */

#pragma once

namespace CSF {

    /**
     * @tparam T The data type of the values in the matrix
     * @tparam indexT The data type of the indices in the matrix
     * @tparam compressionLevel The compression level used
     * @tparam columnMajor Whether the matrix is stored in column major format
     *
     * A class to represent a sparse matrix compressed in the Compressed Sparse Fiber format (CSF). \n \n
     * CSF Sparse Matrix is a read-only matrix class optimized for sparse-dense computation in cases where values
     * are highly redundant. For such cases, sparse fiber storage can reduce memory footprint by up to 50% compared to
     * standard sparse compression. CSF also increases the ability to further compress index arrays within each fiber.
     * This default templated version is for compression3 specifically. For compression level 1 and 2 there
     * are template specializations.
     */
    template <typename T, typename indexT = uint64_t, uint8_t compressionLevel = 3, bool columnMajor = true>
    class SparseMatrix : public SparseMatrixBase {

        private:

        //* The Matrix Data *//

        void** data = nullptr; // The data of the matrix
        void** endPointers = nullptr; // The pointers to the end of each column

        //* Private Methods *//

        // Compression Algorithm for going from CSC to CSF2 or CSF3
        template <typename T2, typename indexT2>
        void compressCSC(T2 *vals, indexT2 *innerIndices, indexT2 *outerPointers);

        // Takes info about the value type and encodes it into a single uint32_t
        void encodeValueType();

        // Checks the value type matches the class template T
        void checkValueType();

        // Does checks on the class to ensure it is valid
        void userChecks();

        // Method to calcuate and set the byte size of the matrix in memory
        void calculateCompSize();

        // Private Helper Constructor for tranposing a CSF matrix
        SparseMatrix(std::unordered_map<T, std::vector<indexT>> maps[], uint32_t num_rows, uint32_t num_cols);

        // Scalar Multiplication
        inline CSF::SparseMatrix<T, indexT, compressionLevel, columnMajor> scalarMultiply(T scalar);

        // In Place Scalar Multiplication
        inline void inPlaceScalarMultiply(T scalar);

        // Matrix Vector Multiplication
        inline Eigen::VectorXd vectorMultiply(Eigen::VectorXd &vec);

        // Matrix Vector Multiplication 2 (with CSF Vector)
        inline Eigen::VectorXd vectorMultiply(typename SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector &vec);

        // Matrix Matrix Multiplication
        inline Eigen::Matrix<T, -1, -1> matrixMultiply(Eigen::Matrix<T, -1, -1> &mat);



        public:

        //* Nested Subclasses *//

        // Vector Class for CSF3 Sparse Matrix
        class Vector;

        // Iterator Class for CSF3 Sparse Matrix
        class InnerIterator;

        //* Constructors *//
        /** @name Constructors
         */
        ///@{

        /**
         * Construct an empty CSF matrix \n \n
         * The matrix will have 0 rows and 0 columns and
         * will not be initialized with any values. All data
         * will be set to nullptr.
         *
         * @warning This constructor is not recommended for use as updating a CSF matrix is not well supported.
         */
        SparseMatrix() {};

        /**
         * Empty Constructor \n \n
         * Takes in the number of rows and cols desired for an all zero matrix
         * of the specified size. All data will be set to nullptr.
         */
        SparseMatrix(uint32_t num_rows, uint32_t num_cols);

        /**
         * @param mat The Eigen Sparse Matrix to be compressed
         *
         * Eigen Sparse Matrix Constructor \n \n
         * This constructor takes an Eigen Sparse Matrix and compresses it into a CSF matrix.
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
         * @tparam compressionLevel2 The compression level of the CSF matrix to convert
         * @param mat The CSF matrix to convert
         *
         * Convert a CSF matrix of a different compression level to this compression level. \n \n
         * This constructor takes in a CSF matrix of the same storage order, value, and index type and converts it to
         * a different compresion level. This is useful for converting between compression levels without having to
         * go through the CSC format.
         */
        template <uint8_t compressionLevel2>
        SparseMatrix(CSF::SparseMatrix<T, indexT, compressionLevel2, columnMajor> &other);

        /**
         * @param other The CSF matrix to be copied
         *
         * Deep Copy Constructor \n \n
         * This constructor takes in a CSF matrix and creates a deep copy of it.
         */
        SparseMatrix(const CSF::SparseMatrix<T, indexT, compressionLevel, columnMajor> &other);

        /**
         * Raw CSC Constructor \n \n
         * This constructor takes in raw CSC storage format pointers and converts it to a CSF matrix.
         * One could also take this information and convert to an Eigen Sparse Matrix and then to a CSF matrix.
         */
        template <typename T2, typename indexT2>
        SparseMatrix(T2 *vals, indexT2 *innerIndices, indexT2 *outerPtr, uint32_t num_rows, uint32_t num_cols, uint32_t nnz);

        /**
         * COO Tuples Constructor \n \n
         * This constructor takes in a list of tuples in COO format which can be unsorted but without duplicates.
         * The tuples are sorted and then converted to a CSF matrix.
         * 
         * @note COO is (row, col, value) format.
         */
        template <typename T2, typename indexT2>
        SparseMatrix(std::vector<std::tuple<indexT2, indexT2, T2>> entries, uint32_t num_rows, uint32_t num_cols, uint32_t nnz);

        /**
         * @param vec The vector to construct the matrix from
         *
         * CSF Vector Constructor \n \n
         * This constructor takes in a single CSF vector and creates a one column/row CSF matrix.
         */
        SparseMatrix(typename CSF::SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector &vec);

        /**
         * @param vecs The vector of CSF vectors to construct from.
         *
         * Vector of CSF Vectors Constructor \n \n
         * This constructor takes in an vector of CSF vectors and creates a CSF matrix from them.
         */
        SparseMatrix(std::vector<typename CSF::SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector> &vecs);

        /**
         * @param filename The filepath of the matrix to be read in
         *
         * File Constructor \n \n
         * Given a filepath to a CSF matrix written to file this constructor will read in the matrix and construct it.
         */
        SparseMatrix(const char *filename);

        /**
         * @brief Destroy the Sparse Matrix object
         */
        ~SparseMatrix();

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
         * @returns true If the matrix is stored in column major format
         * @returns false If the matrix is stored in row major format
         *
         * See the storage order of the CSF matrix.
         */
        bool isColumnMajor() const;

        /**
         * @param vec The vector to get the pointer to
         * @returns void* The pointer to the vector
         *
         * Get a pointer to a vector in the CSF matrix such as the first column.
         *
         * @note Can only get vectors in the storage order of the matrix.
         */
        void *vectorPointer(uint32_t vec);

        /**
         * @param vec The vector to get a copy of
         * @returns Vector The vector copy returned
         *
         * Get a copy of a CSF vector from the CSF matrix such as the first column.
         *
         * @note Can only get vectors in the storage order of the matrix.
         */
        typename CSF::SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector getVector(uint32_t vec);

        /**
         * @param vec The vector to get the size of
         * @returns size_t The size of the vector in bytes
         *
         * Get the size of a vector in the CSF matrix in bytes.
         *
         * @note Can only get vectors in the storage order of the matrix.
         */
        size_t getVectorSize(uint32_t vec) const;

        ///@}

        //* Calculations *//
        /**
         * @name Calculations
         */
        ///@{

        /**
         * @returns A vector of the sum of each vector along the outer dimension.
         */
        inline std::vector<T> outerSum();

        /**
         * @returns A vector of the sum of each vector along the inner dimension.
         */
        inline std::vector<T> innerSum();

        /**
         * @returns A vector of the maximum value in each column.
         */
        inline std::vector<T> maxColCoeff();

        /**
         * @returns A vector of the maximum value in each row.
         */
        inline std::vector<T> maxRowCoeff();

        /**
         * @returns A vector of the minimum value in each column.
         */
        inline std::vector<T> minColCoeff();

        /**
         * @returns A vector of the minimum value in each row.
         */
        inline std::vector<T> minRowCoeff();

        /**
         * @returns The trace of the matrix.
         *
         * @note Only works for square matrices.
         */
        inline T trace();

        /**
         * @returns The sum of all the values in the matrix.
         */
        inline T sum();

        /**
         * @returns The frobenius norm of the matrix.
         */
        inline double norm();

        /**
         * @returns Returns the length of the specified vector.
         */
        inline double vectorLength(uint32_t vec);

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
         * @returns The current matrix as uncompressed to CSC format.
         */
        CSF::SparseMatrix<T, indexT, 1, columnMajor> toCSF1();

        /**
         * @returns The current matrix as a CSF2 Matrix.
         */
        CSF::SparseMatrix<T, indexT, 2, columnMajor> toCSF2();

        /**
         * @returns An Eigen Sparse Matrix constructed from the CSF matrix data.
         */
        Eigen::SparseMatrix<T, columnMajor ? Eigen::ColMajor : Eigen::RowMajor> toEigen();

        ///@}

        //* Matrix Manipulation Methods *//
        /**
         * @name Matrix Manipulation Methods
         */
        ///@{

        /**
         * @returns A transposed version of the CSF matrix.
         *
         * @warning This method is not very efficient for CSF2 and CSF3 matrices.
         */
        CSF::SparseMatrix<T, indexT, compressionLevel, columnMajor> transpose();

        /**
         * Transposes the matrix in place instead of returning a new matrix.
         *
         * @warning This method is not very efficient for CSF2 and CSF3 matrices.
         */
        void inPlaceTranspose();

        /**
         * @param vec The vector to append to the matrix in the correct storage order.
         *
         * Appends a CSF vector to the current matrix in the storage order of the matrix.
         */
        void append(typename SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector &vec);

        /**
         * @returns A vector of CSF vectors that represent a slice of the CSF matrix.
         */
        std::vector<typename CSF::SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector> slice(uint32_t start, uint32_t end);

        ///@}

        //* Operator Overloads *//

        // Assignment Operator
        CSF::SparseMatrix<T, indexT, compressionLevel, columnMajor> &operator=(const CSF::SparseMatrix<T, indexT, compressionLevel, columnMajor> &other);

        // Equality Operator
        bool operator==(const SparseMatrix<T, indexT, compressionLevel, columnMajor> &other);

        // Inequality Operator
        bool operator!=(const SparseMatrix<T, indexT, compressionLevel, columnMajor> &other);

        // Coefficient Access Operator
        T operator()(uint32_t row, uint32_t col);

        // Vector Access Operator
        typename CSF::SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector operator[](uint32_t vec);

        // Scalar Multiplication
        CSF::SparseMatrix<T, indexT, compressionLevel, columnMajor> operator*(T scalar);

        // In Place Scalar Multiplication
        void operator*=(T scalar);

        // Matrix Vector Multiplication
        Eigen::VectorXd operator*(Eigen::VectorXd &vec);

        // Matrix Vector Multiplication 2 (with CSF Vector)
        Eigen::VectorXd operator*(typename SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector &vec);

        // Matrix Matrix Multiplication
        Eigen::Matrix<T, -1, -1> operator*(Eigen::Matrix<T, -1, -1> mat);
    
    }; // End of SparseMatrix Class

} // End of CSF Namespace