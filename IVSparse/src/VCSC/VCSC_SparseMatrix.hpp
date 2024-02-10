/**
 * @file VCSC_SparseMatrix.hpp
 * @author Skyler Ruiter and Seth Wolfgang
 * @brief Header File for VCSC Sparse Matrix Declarations
 * @version 0.1
 * @date 2023-07-03
 */

#pragma once

namespace IVSparse {

    /**
     * The VCSC Sparse Matrix Class is a version of the CSC format. The difference
     * is that CSC is base CSC but VCSC is CSC with run length encoding and a vector
     * that keeps track of the number of occurances of a value in a column. This
     * allows for fast level 1 BLAS operations and still compresses more with
     * redundant data than CSC.
     */
    template <typename T, typename indexT = uint32_t, bool columnMajor = 1>
    class VCSC {
        private:
        //* The Matrix Data *//

        T** values = nullptr;        // The values of the matrix
        indexT** counts = nullptr;   // The counts of the matrix
        indexT** indices = nullptr;  // The indices of the matrix

        indexT* valueSizes = nullptr;  // The sizes of the value arrays
        indexT* indexSizes = nullptr;  // The sizes of the index arrays

        uint32_t innerDim = 0;  // The inner dimension of the matrix
        uint32_t outerDim = 0;  // The outer dimension of the matrix

        uint32_t numRows = 0;  // The number of rows in the matrix
        uint32_t numCols = 0;  // The number of columns in the matrix

        uint32_t nnz = 0;  // The number of non-zero values in the matrix

        size_t compSize = 0;  // The size of the compressed matrix in bytes

        //* The Value and Index Types *//

        uint32_t val_t;  // Information about the value type (size, signededness, etc.)
        uint32_t index_t;  // Information about the index type (size)

        uint32_t* metadata = nullptr;  // The metadata of the matrix

        //* Private Methods *//

        // Calculates the number of bytes needed to store a value
        inline uint8_t byteWidth(size_t size);

        //* Private Methods *//

        // Compression Algorithm for going from CSC to VCSC or IVCSCC
        template <typename T2, typename indexT2>
        void compressCSC(T2* vals, indexT2* innerIndices, indexT2* outerPointers);

        // Encodes the value type of the matrix
        void encodeValueType();

        // Checks if the value type is correct for the matrix
        void checkValueType();

        // performs some simple user checks on the matrices metadata
        void userChecks();

        // Calculates the current byte size of the matrix in memory
        void calculateCompSize();

        // Scalar Multiplication
        inline IVSparse::VCSC<T, indexT, columnMajor> scalarMultiply(T scalar);

        // In Place Scalar Multiplication
        inline void inPlaceScalarMultiply(T scalar);

        // Matrix Vector Multiplication
        inline Eigen::Matrix<T, -1, 1> vectorMultiply(Eigen::Matrix<T, -1, 1>& vec);

        // helper for ostream operator
        void printHelper(std::ostream& stream);
        void printHelper(std::stringstream& stream);



        public:

        // Gets the number of rows in the matrix
        uint32_t rows() const { return numRows; }

        // Gets the number of columns in the matrix
        uint32_t cols() const { return numCols; }

        // Gets the inner dimension of the matrix
        uint32_t innerSize() const { return innerDim; }

        // Gets the outer dimension of the matrix
        uint32_t outerSize() const { return outerDim; }

        // Gets the number of non-zero elements in the matrix
        uint32_t nonZeros() const { return nnz; }

        // Gets the number of bytes needed to store the matrix
        size_t byteSize() const { return compSize; }


        //* Nested Subclasses *//

        // The Iterator Class for VCSC Matrices
        class InnerIterator;

        //* Constructors and Destructor *//
        /** @name Constructors
         */
         ///@{

         /**
          * Construct an empty IVSparse matrix \n \n
          * The matrix will have 0 rows and 0 columns and
          * will not be initialized with any values. All data
          * will be set to nullptr.
          *
          * @attention This constructor is not recommended for use as updating a
          * IVSparse matrix is not well supported.
          */
        VCSC() {};

        // Private Helper Constructor for tranposing a IVSparse matrix
        VCSC(std::unordered_map<T, std::vector<indexT>>* maps, uint32_t num_rows, uint32_t num_cols);


        /**
         * @param mat The Eigen Sparse Matrix to be compressed
         *
         * Eigen Sparse Matrix Constructor \n \n
         * This constructor takes an Eigen Sparse Matrix and compresses it into a
         * IVSparse matrix.
         */
        VCSC(Eigen::SparseMatrix<T, 0>& mat);

        /**
         * @param mat The Eigen Sparse Matrix to be compressed
         *
         * Eigen Sparse Matrix Constructor (Row Major) \n \n
         * Same as previous constructor but for Row Major Eigen Sparse Matrices.
         */
        VCSC(Eigen::SparseMatrix<T, 1>& mat);

        /**
         * @tparam compressionLevel2 The compression level of the IVSparse matrix to
         * convert
         * @param mat The IVSparse matrix to convert
         *
         * Convert a IVSparse matrix of a different compression level to this
         * compression level. \n \n This constructor takes in a IVSparse matrix of the
         * same storage order, value, and index type and converts it to a different
         * compresion level. This is useful for converting between compression levels
         * without having to go through the CSC format.
         */
        VCSC(IVSparse::IVCSC<T, columnMajor>& other);

        /**
         * @param other The IVSparse matrix to be copied
         *
         * Deep Copy Constructor \n \n
         * This constructor takes in a VCSC matrix and creates a deep copy of it.
         */
        VCSC(const IVSparse::VCSC<T, indexT, columnMajor>& other);

        /**
         * Raw CSC Constructor \n \n
         * This constructor takes in raw CSC storage format pointers and converts it
         * to a VCSC matrix. One could also take this information and convert to an
         * Eigen Sparse Matrix and then to a VCSC matrix.
         */
        template <typename T2, typename indexT2>
        VCSC(T2* vals, indexT2* innerIndices, indexT2* outerPtr, uint32_t num_rows, uint32_t num_cols, uint32_t nnz);

        /**
         * COO Tuples Constructor \n \n
         * This constructor takes in a list of tuples in COO format which can be
         * unsorted but without duplicates. The tuples are sorted and then converted
         * to a IVSparse matrix.
         *
         * @note COO is (row, col, value) format.
         */
        template <typename T2, typename indexT2>
        VCSC(std::vector<std::tuple<indexT2, indexT2, T2>>& entries, uint64_t num_rows, uint32_t num_cols, uint32_t nnz);

        /**
         * @param filename The filepath of the matrix to be read in
         *
         * File Constructor \n \n
         * Given a filepath to a VCSC matrix written to file this constructor will
         * read in the matrix and construct it.
         */
        VCSC(char* filename);

        /**
         * @brief Destroy the Sparse Matrix object
         */
        ~VCSC();

        ///@}

        //* Getters *//
        /**
         * @name Getters
         */
         ///@{


         /**
          * @returns T The value at the specified row and column. Returns 0 if the
          * value is not found.
          *
          * Get the value at the specified row and column
          *
          * @note Users cannot update individual values in a IVSparse matrix.
          *
          * @warning This method is not efficient and should not be used in performance
          * critical code.
          */
        T coeff(uint32_t row, uint32_t col);

        /**
         * @returns true If the matrix is stored in column major format
         * @returns false If the matrix is stored in row major format
         *
         * See the storage order of the IVSparse matrix.
         */
        bool isColumnMajor() const;

        /**
         * @param vec The vector to get the values for
         * @returns A pointer to the values of a given vector in a VCSC Matrix
         */
        T* getValues(uint32_t vec) const;

        /**
         * @param vec The vector to get the counts for
         * @returns A pointer to the value counts of a given vector in a VCSC Matrix
         */
        indexT* getCounts(uint32_t vec) const;

        /**
         * @param vec The vector to get the indices for
         * @returns A pointer to the indices of a given vector in a VCSC Matrix
         */
        indexT* getIndices(uint32_t vec) const;

        /**
         * @param vec The vector to get the unique values for
         * @returns The number of unique values in a given vector in a VCSC Matrix
         */
        indexT getNumUniqueVals(uint32_t vec) const;

        /**
         * @param vec The vector to get the the number of indices for
         * @returns The number of indices (nonzeros) in a given vector in a VCSC
         * Matrix
         */
        indexT getNumIndices(uint32_t vec) const;

        ///@}

        //* Calculations *//
        /**
         * @name Calculations
         */
         ///@{

         /**
          * @returns A vector of the sum of each vector along the outer dimension.
          */
        inline Eigen::Matrix<T, -1, -1> colSum();

        /**
         * @returns A vector of the sum of each vector along the inner dimension.
         */
        inline Eigen::Matrix<T, -1, -1> rowSum();


        /**
         * Note: axis = 0 for a column sum and axis = 1 for row sum.
         *       For min coefficient in matrix, there is an overloaded
         *       method without a paramter.
         *
         * @returns An Eigen::Matrix of the min value along specified axis
        */

        inline Eigen::Matrix<T, -1, -1> min(int axis);

        /**
         * @returns The min value in the matrix.
         */

        inline T min();

        /**
         * Note: axis = 0 for a column sum and axis = 1 for row sum.
         *       For max coefficient in matrix, there is an overloaded
         *       method without a paramter.
         *
         * @returns An Eigen::Matrix of the max value along specified axis
        */

        inline Eigen::Matrix<T, -1, -1> max(int axis);

        /**
         * @returns The max value in the matrix.
         */

        inline T max();

        /**
         * @returns The trace of the matrix.
         *
         * @note Only works for square matrices.
         */
        template<typename T2 = T, std::enable_if_t<std::is_integral<T2>::value, bool> = true>
        inline int64_t trace();

        template<typename T2 = T, std::enable_if_t<std::is_floating_point<T2>::value, bool> = true>
        inline double trace();

        /**
         * @returns The sum of all the values in the matrix.
         */
        template<typename T2 = T, std::enable_if_t<std::is_integral<T2>::value, bool> = true>
        inline int64_t sum();

        template<typename T2 = T, std::enable_if_t<std::is_floating_point<T2>::value, bool> = true>
        inline double sum();

        /**
         * @returns The frobenius norm of the matrix.
         */
        inline double norm();

        /**
         * @returns Returns the length of the specified vector.
         */
         // inline double vectorLength(uint32_t vec);

         ///@}

         //* Utility Methods *//
         /**
          * @name Utility Methods
          */
          ///@{

          /**
           * @param filename The filename of the matrix to write to
           *
           * This method writes the IVSparse matrix to a file in binary format.
           * This can then be read in later using the file constructor.
           * Currently .ivsparse is the perfered file extension.
           *
           * @note Useful to split a matrix up and then write each part separately.
           */
        void write(char* filename);


        /**
        * @param filename The filename of the matrix to read from
        *
        * This method overwrites the current matrix with the matrix read in from the
        * file. The file must be written by the write method.
        *
       */


        void read(char* filename);

        /**
         * Prints "IVSparse Matrix:" followed by the dense representation of the
         * matrix to the console.
         *
         * @note Useful for debugging but only goes up to 100 of either dimension.
         */
        void print();

        /**
         * @returns The current matrix as a IVCSC Matrix.
         */
        IVSparse::IVCSC<T, columnMajor> toIVCSC();

        /**
         * @returns An Eigen Sparse Matrix constructed from the VCSC matrix data.
         */
        Eigen::SparseMatrix<T, columnMajor ? Eigen::ColMajor : Eigen::RowMajor> toEigen();

        ///@}

        //* Matrix Manipulation Methods *//
        /**
         * @name Matrix Manipulation Methods
         */
         ///@{

         /**
          * @returns A transposed version of the IVSparse matrix.
          *
          * @warning This method is not very efficient for VCSC and IVCSC matrices.
          */
        IVSparse::VCSC<T, indexT, columnMajor> transpose();

        /**
         * Transposes the matrix in place instead of returning a new matrix.
         *
         * @warning This method is not very efficient for VCSC and IVCSC matrices.
         */
        void inPlaceTranspose();

        /**
         * @param vec The vector to append to the matrix in the correct storage order.
         *
         * Appends a IVSparse vector to the current matrix in the storage order of the
         * matrix.
         */
        void append(VCSC<T, indexT, columnMajor>& mat);

        /**
         * @param mat The matrix to append to the matrix in the correct storage order.
         *
         * Appends an Eigen::SparseMatrix to the current matrix in the storage order of the
         * matrix. This converts the Eigen::SparseMatrix to an IVSparse matrix.
         */

        inline void append(Eigen::SparseMatrix<T, columnMajor ? Eigen::ColMajor : Eigen::RowMajor>& mat);

        /**
         * @brief Appends a raw CSC matrix to the current matrix. Assumes correct storage order.
         * @tparam T2
         * @tparam indexT2
         * @param vals
         * @param innerIndices
         * @param outerPtr
         * @param num_rows
         * @param num_cols
         * @param nnz
         */
        template <typename T2, typename indexT2>
        inline void append(T2* vals, indexT2* innerIndices, indexT2* outerPtr, uint32_t num_rows, uint32_t num_cols, uint32_t nnz);


        /**
         * @returns A matrix that represent a slice of the
         * IVSparse matrix.
         */
        IVSparse::VCSC<T, indexT, columnMajor> slice(uint32_t start, uint32_t end);

        ///@}

        //* Operator Overloads *//

        friend std::ostream& operator<< (std::ostream& stream, IVSparse::VCSC<T, indexT, columnMajor>& mat) {
            mat.printHelper(stream);
            return stream;
        }

        friend std::stringstream& operator<< (std::stringstream& stream, IVSparse::VCSC<T, indexT, columnMajor>& mat) {
            mat.printHelper(stream);
            return stream;
        }

        // Assignment Operator
        IVSparse::VCSC<T, indexT, columnMajor>& operator=(const IVSparse::VCSC<T, indexT, columnMajor>& other);

        // Assignment Operator
        IVSparse::VCSC<T, indexT, columnMajor>& operator=(IVSparse::IVCSC<T, columnMajor>& other);

        // Equality Operator
        bool operator==(const VCSC<T, indexT, columnMajor>& other) const;

        // Inequality Operator
        bool operator!=(const VCSC<T, indexT, columnMajor>& other);

        // Coefficient Access Operator
        T operator()(uint32_t row, uint32_t col);

        // Scalar Multiplication
        IVSparse::VCSC<T, indexT, columnMajor> operator*(T scalar);

        // In Place Scalar Multiplication
        void operator*=(T scalar);

        // Matrix Vector Multiplication
        Eigen::Matrix<T, -1, 1> operator*(Eigen::Matrix<T, -1, 1>& vec);
        Eigen::Matrix<T, -1, 1> operator*(const Eigen::Ref<const Eigen::Matrix<T, -1, 1>>& mat);

        // Matrix Matrix Multiplication
        Eigen::Matrix<T, -1, -1> operator*(Eigen::Matrix<T, -1, -1>& mat);
        Eigen::Matrix<T, -1, -1> operator*(const Eigen::Ref<const Eigen::Matrix<T, -1, -1>>& mat);


    };  // End of VCSC Sparse Matrix Class

}  // namespace IVSparse