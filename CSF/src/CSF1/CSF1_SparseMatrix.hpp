/**
 * @file CSF1_SparseMatrix.hpp
 * @author Skyler Ruiter and Seth Wolfgang
 * @brief Header File for CSF1 Sparse Matrix Declarations
 * @version 0.1
 * @date 2023-07-03
 */

#pragma once

namespace CSF {

    /**
     * 
     * The CSF1 Sparse Matrix Class is a version of the CSC format and is the most 
     * basic version of the CSF format. Mostly used for ease of use with other compression
     * levels and with other libraries. This is a good baseline to compare against the other
     * compression levels as well.
     * 
     * @warning This class does not have BLAS support like the other two compression levels.
     * If one needs CSC BLAS support, Eigen is a good library to use.
     */
    template <typename T, typename indexT, bool columnMajor>
    class SparseMatrix<T, indexT, 1, columnMajor> : public SparseMatrixBase {

    private:

        //* The Matrix Data *//
        T* vals = nullptr; // The values of the matrix
        indexT* innerIdx = nullptr; // The inner indices of the matrix
        indexT* outerPtr = nullptr; // The outer pointers of the matrix

        //* Private Methods *//

        // Encodes the value type of the matrix in a uint32_t
        void encodeValueType();

        // Checks if the value type is correct for the matrix
        void checkValueType();

        // performs some simple user checks on the matrices metadata
        void userChecks();

        // Calculates the current byte size of the matrix in memory
        void calculateCompSize();

        // Scalar Multiplication
        inline CSF::SparseMatrix<T, indexT, 1, columnMajor> scalarMultiply(T scalar);

        // In Place Scalar Multiplication
        inline void inPlaceScalarMultiply(T scalar);

        // Matrix Vector Multiplication
        inline Eigen::VectorXd vectorMultiply(Eigen::VectorXd& vec);

        // Matrix Vector Multiplication 2 (with CSF Vector)
        inline Eigen::VectorXd vectorMultiply(typename SparseMatrix<T, indexT, 1, columnMajor>::Vector& vec);

        // Matrix Matrix Multiplication
        inline Eigen::Matrix<T, -1, -1> matrixMultiply(Eigen::Matrix<T, -1, -1>& mat);



    public:

        //* Nested Subclasses *//

        // Vector Class for CSF1 Sparse Matrices
        class Vector;

        // Iterator Class for CSF1 Sparse Matrices
        class InnerIterator;

        //* Constructors and Destructor *//
        /** @name Constructors
         */
        ///@{

        /**
         * Construct an empty CSF matrix \n \n
         * The matrix will have 0 rows and 0 columns and
         * will not be initialized with any values. All data
         * will be set to nullptr.
         *
         * @attention This constructor is not recommended for use as updating a CSF matrix is not well supported.
         */
        SparseMatrix() {};

        SparseMatrix(Eigen::SparseMatrix<T>& mat);

        SparseMatrix(Eigen::SparseMatrix<T, Eigen::RowMajor>& mat);

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
        SparseMatrix(CSF::SparseMatrix<T, indexT, compressionLevel2, columnMajor>& other);

        SparseMatrix(const CSF::SparseMatrix<T, indexT, 1, columnMajor>& other);

        template <typename T2, typename indexT2>
        SparseMatrix(T2* vals, indexT2* innerIndices, indexT2* outerPtr, uint32_t num_rows, uint32_t num_cols, uint32_t nnz);

        /**
         * Raw CSC Constructor \n \n
         * This constructor takes in raw CSC storage format pointers and converts it to a CSF1 matrix.
         * One could also take this information and convert to an Eigen Sparse Matrix and then to a CSF1 matrix.
         */
        template <typename T2, typename indexT2>
        SparseMatrix(std::vector<std::tuple<indexT2, indexT2, T2>> entries, uint32_t num_rows, uint32_t num_cols, uint32_t nnz);

        SparseMatrix(typename CSF::SparseMatrix<T, indexT, 1, columnMajor>::Vector& vec);

        SparseMatrix(std::vector<typename CSF::SparseMatrix<T, indexT, 1, columnMajor>::Vector>& vecs);

        SparseMatrix(const char* filename);

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
         */
        T coeff(uint32_t row, uint32_t col);

        /**
         * @returns true If the matrix is stored in column major format
         * @returns false If the matrix is stored in row major format
         *
         * See the storage order of the CSF matrix.
         */
        bool isColumnMajor() const;

        T* getValues(uint32_t vec) const;

        indexT* getInnerIndices(uint32_t vec) const;

        indexT* getOuterPointers() const;

        /**
         * @param vec The vector to get a copy of
         * @returns Vector The vector copy returned
         *
         * Get a copy of a CSF vector from the CSF matrix such as the first column.
         *
         * @note Can only get vectors in the storage order of the matrix.
         */
        typename CSF::SparseMatrix<T, indexT, 1, columnMajor>::Vector getVector(uint32_t vec);

        void write(const char* filename);

        /**
         * Prints "CSF Matrix:" followed by the dense representation of the matrix to the console.
         *
         * @note Useful for debugging but only goes up to 100 of either dimension.
         */
        void print();

        /**
         * @returns The current matrix as a CSF2 Matrix.
         */
        CSF::SparseMatrix<T, indexT, 2, columnMajor> toCSF2();

        /**
         * @returns The current matrix as a CSF3 Matrix.
         */
        CSF::SparseMatrix<T, indexT, 3, columnMajor> toCSF3();

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
         * @returns A transposed version of the CSF1 matrix.
         */
        CSF::SparseMatrix<T, indexT, 1, columnMajor> transpose();

        /**
         * Transposes the matrix in place instead of returning a new matrix.
         */
        void inPlaceTranspose();

        void append(typename SparseMatrix<T, indexT, 1, columnMajor>::Vector& vec);

        /**
         * @returns A vector of CSF vectors that represent a slice of the CSF matrix.
         */
        std::vector<typename CSF::SparseMatrix<T, indexT, 1, columnMajor>::Vector> slice(uint32_t start, uint32_t end);

        CSF::SparseMatrix<T, indexT, 1, columnMajor>& operator=(const CSF::SparseMatrix<T, indexT, 1, columnMajor>& other);

        bool operator==(const SparseMatrix<T, indexT, 1, columnMajor>& other);

        bool operator!=(const SparseMatrix<T, indexT, 1, columnMajor>& other);

        // Coefficient Access Operator
        T operator()(uint32_t row, uint32_t col);

        // Vector Access Operator
        typename CSF::SparseMatrix<T, indexT, 1, columnMajor>::Vector operator[](uint32_t vec);

        CSF::SparseMatrix<T, indexT, 1, columnMajor> operator*(T scalar);

        void operator*=(T scalar);

        Eigen::VectorXd operator*(Eigen::VectorXd& vec);

        Eigen::VectorXd operator*(typename SparseMatrix<T, indexT, 1, columnMajor>::Vector& vec);

        Eigen::Matrix<T, -1, -1> operator*(Eigen::Matrix<T, -1, -1> mat);

        inline double vectorLength(uint32_t col);

        inline double norm();

        inline T sum();

        inline T trace();

        inline std::vector<T> maxColCoeff();

        inline std::vector<T> minRowCoeff();

        inline std::vector<T> maxRowCoeff();

        inline std::vector<T> minColCoeff();

        inline std::vector<T> outerSum();

        inline std::vector<T> innerSum();

    };

}