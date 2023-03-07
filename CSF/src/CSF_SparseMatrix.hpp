/**
 * @file CSF_SparseMatrix.hpp
 * @author Skyler Ruiter (ruitersk@mail.gvsu.edu)
 * @brief Definitions for the CSF SparseMatrix class
 * @version 0.1
 * @date 2023-02-27
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#pragma once

namespace CSF {

    /**
     * @brief Default class definition of the CSF::SparseMatrix class
     * 
     * The CSF Sparse Matrix is a compressed sparse matrix format that is designed to be
     * 
     * optimized to real world redundant data with a strong negative binomial distribution.
     * 
     * @tparam T The value type of the matrix
     * @tparam T_index The index type of the matrix
     * @tparam compression_level The compression level of the matrix
     */
    template <typename T, typename T_index=uint64_t, int compression_level=3>
    class SparseMatrix {
        /**
         * @brief The delimiter used to separate runs of values
         * 
         */
        const uint8_t delim = 0;

        /**
         * @brief The number of rows in the matrix
         * 
         */
        uint32_t num_rows = 0;

        /**
         * @brief The number of columns in the matrix
         * 
         */
        uint32_t num_cols = 0;

        /**
         * @brief The number of non-zero values in the matrix
         * 
         */
        uint32_t num_nonzeros = 0;


        /**
         * @brief The number of bytes used to store the row index
         * 
         */
        uint32_t row_t;

        /**
         * @brief The number of bytes used to store the column index
         * 
         */
        uint32_t col_t;

        /**
         * @brief First byte is sizeof(T), second is if T is signed, third is if T is floating point
         * 
         * with the last byte being zero.
         * 
         */
        uint32_t val_t;

        /**
         * @brief The size of the compressed matrix in bytes
         * 
         */
        size_t compression_size;

        /**
         * @brief The compression level of the matrix
         * 
         */
        uint32_t compression = compression_level;

        /**
         * @brief The pointer to the beginning of the uncompressed matrix
         *
         */
        void *begin_ptr;

        /**
         * @brief The pointer to the end of the compressed matrix
         * 
         */
        void *comp_ptr;

        /**
         * @brief Private function that allocates initial memory for the matrix
         * 
         * given a few parematers and allocating the wost case scenario for memory
         * 
         * which is CSC plus space for metadata.
         * 
         * @throw std::bad_alloc The malloc call failed
         * 
         * @return void
         */
        void allocate_memory();

        /**
         * @brief Private function that encodes the val_t variable
         * 
         * so that the first byte is sizeof(T), the second byte is if T is signed,
         * 
         * the third byte is if T is floating point, and the last byte is zero.
         * 
         * @return uint32_t The encoded val_t variable
         */
        uint32_t encode_valt();

        /**
         * @brief checks that the val_t is encoded correctly compared to T.
         * 
         * Helpful for constructing from an existing compressed matrix.
         * 
         * @throw std::runtime_error The val_t is not encoded correctly
         * 
         * @param valt The val_t variable to check 
         * 
         * @return void
         */
        void check_valt(uint32_t valt);

        /**
         * @brief Private function that returns the number of bytes needed to store a value
         * 
         * @param size The size of the value to store
         * 
         * @return uint8_t The number of bytes needed to store the value
         */
        uint8_t byte_width(size_t size);

        /**
         * @brief Private function that creates the metadata for the compressed matrix
         * 
         * @return uint64_t* The pointer to the column pointers in the data
         */
        uint64_t* create_metadata();

        /**
         * @brief Performs a series of user checks on the template parameters
         * 
         * and the class variables to ensure the class is being used correctly.
         * 
         * @ref check_valt() is called as a part of this function.
         * 
         * @throw std::invalid_argument The template parameters are invalid
         * 
         * @return void
         */
        void user_checks();

        /**
         * @brief The primiary workhorse function that compresses the matrix
         * 
         * given a CSC matrix and is called whenever compressing to lvl 2 or 3.
         * 
         * @tparam values_type The type of the value array passed
         * @tparam rows_type The type of the row index array passed
         * @tparam cols_type The type of the column pointer array passed
         * 
         * @param vals The array of all values in the passed matrix
         * @param indexes The array of all row indexes in the passed matrix
         * @param col_p The array of all column pointers in the passed matrix
         * 
         * @return void
         * 
         * @ref user_checks() is called as a part of this function.
         * @ref create_metadata() is called as a part of this function.
         * @ref byte_width() is called as a part of this function.
         * 
         * @throw std::invalid_argument The template parameters are invalid
         * @throw std::bad_alloc The realloc call failed
         */
        template <typename values_type, typename rows_type, typename cols_type>
        void compress(values_type *vals, rows_type *indexes, cols_type *col_p);

        /**
         * @brief Currently non-functional method that checks the redundancy of the matrix
         * 
         * to help determine the memory overhead before compression.
         * 
         * @return double The approximate redundancy of the matrix
         */
        double redundancy_check();

    public:
        /**
         * @brief Empty constructor for the SparseMatrix class
         * 
         * @return An empty SparseMatrix object with no allocation
         */
        SparseMatrix();

        /**
         * @brief Construct a new Sparse Matrix object from an Eigen::SparseMatrix<T>
         * 
         * @param mat The eigen matrix to construct from
         * @param destroy If true the values in the matrix will be all replaced with 0
         * 
         * @return A SparseMatrix object with the same values as the passed matrix
         * 
         * @throw std::invalid_argument The matrix is row major
         * @throw std::bad_alloc The malloc call failed
         */
        SparseMatrix(Eigen::SparseMatrix<T> &mat, bool destroy = false);

        /**
         * @brief Construct a new Sparse Matrix object from a raw CSC matrix
         *
         * @tparam values_t the type of the values array
         * @tparam row_ind the type of the row index array
         * @tparam col_ind the type of the column pointer array
         * 
         * @param vals the values array
         * @param indexes the row index array
         * @param col_p the column pointer array
         * @param non_zeros the number of non-zero elements in the matrix
         * @param row_num the number of rows in the matrix
         * @param col_num the number of columns in the matrix
         * @param destroy If true the values in the matrix will be all replaced with 0
         * 
         * @return A SparseMatrix object with the same values as the passed matrix
         * 
         * @throw std::bad_alloc The malloc call failed
         */
        template <typename values_t, typename row_ind, typename col_ind>
        SparseMatrix(values_t **vals, row_ind **indexes, col_ind **col_p,
                     size_t non_zeros, size_t row_num, size_t col_num,
                     bool destroy = false);

        /**
         * @brief Construct a new Sparse Matrix object from a file
         * 
         * @param filename the file to read the CSF matrix from
         * 
         * @return A SparseMatrix object with the same values as the passed file
         * 
         * @throw std::invalid_argument The file doesn't exist
         * @throw std::bad_alloc The malloc call failed
         */
        SparseMatrix(const char *filename);

        /**
         * @brief Construct a new Sparse Matrix object from an existing CSF::SparseMatrix
         * 
         * @param mat the matrix to deep copy
         * 
         * @return A SparseMatrix object with the same values as the passed matrix
         * 
         * @throw std::bad_alloc The malloc call failed
         */
        SparseMatrix(CSF::SparseMatrix<T, T_index, compression_level> &mat);

        /**
         * @brief Destroy the Sparse Matrix object
         * 
         */
        ~SparseMatrix();

        /**
         * @brief writes the sparse matrix to a file
         * 
         * @param filename the file to write the matrix to
         * 
         * @return void
         */
        void write(const char *filename);

        /**
         * @brief decompresses the matrix to a CSF::SparseMatrix<T, T_index, 1> object
         * 
         * which is a CSC matrix implemenation.
         * 
         * @return CSF::SparseMatrix<T, T_index, 1> The decompressed matrix
         */
        CSF::SparseMatrix<T, T_index, 1> to_csf1();

        /**
         * @brief Turns the CSF matrix into an equivalent Eigen::SparseMatrix<T>
         * 
         * @return Eigen::SparseMatrix<T> The equivalent Eigen matrix
         */
        Eigen::SparseMatrix<T> to_eigen();

        /**
         * @brief Returns a pointer to the beginning of the compressed matrix
         * 
         * @return void* 
         */
        void *beginPtr();

        /**
         * @brief Returns a pointer to the end of the compressed matrix
         * 
         * @return void* 
         */
        void *endPtr();

        /**
         * @brief Returns the size of the compressed matrix in bytes
         * 
         * @return size_t the size of the compressed matrix in bytes
         */
        size_t byte_size();

        /**
         * @brief Returns the number of rows in the matrix
         * 
         * @return uint32_t the number of rows in the matrix
         */
        uint32_t rows();

        /**
         * @brief Returns the number of columns in the matrix
         * 
         * @return uint32_t the number of columns in the matrix
         */
        uint32_t cols();

        /**
         * @brief Returns the number of non-zero elements in the matrix
         * 
         * @return uint32_t the number of non-zero elements in the matrix
         */
        uint32_t nonzeros();

        /**
         * @brief Returns the compression level of the matrix
         * 
         * @return uint32_t the compression level of the matrix
         */
        uint32_t compLvl();

        /**
         * @brief The iterator class for the CSF::SparseMatrix
         * 
         */
        class Iterator;


        // TO ADD
        // 1. colstack (append) and splice functions
        // 2. .rows() and .cols() functions
        // 3. .coeff() function
        // 4. overload () operator (numpy or splicing syntax)
        // col subclass (to work as a vector) matrix.col(i).dot(yada...)
    };

    /**
     * @brief compression level 1 specialization of the CSF::SparseMatrix class which is CSC format
     *
     * @tparam T The value type of the matrix
     * @tparam T_index The index type of the matrix
     */
    template <typename T, typename T_index>
    class SparseMatrix<T, T_index, 1> {
        /**
         * @brief The delimiter used to separate runs of values
         *
         */
        const uint8_t delim = 0;

        /**
         * @brief The number of rows in the matrix
         *
         */
        uint32_t num_rows = 0;

        /**
         * @brief The number of columns in the matrix
         *
         */
        uint32_t num_cols = 0;

        /**
         * @brief The number of non-zero values in the matrix
         *
         */
        uint32_t num_nonzeros = 0;

        /**
         * @brief The number of bytes used to store the row index
         *
         */
        uint32_t row_t;

        /**
         * @brief The number of bytes used to store the column index
         *
         */
        uint32_t col_t;

        /**
         * @brief First byte is sizeof(T), second is if T is signed, third is if T is floating point
         *
         * with the last byte being zero.
         *
         */
        uint32_t val_t;

        /**
         * @brief The size of the compressed matrix in bytes
         *
         */
        size_t compression_size;

        /**
         * @brief The compression level of the matrix (1)
         *
         */
        uint32_t compression = 1;

        /**
         * @brief The pointer to the beginning of the uncompressed matrix
         *
         */
        void *begin_ptr;

        /**
         * @brief The pointer to the end of the compressed matrix
         *
         */
        void *comp_ptr;

        /**
         * @brief The pointer to the values of the matrix
         * 
         */
        T* vals;

        /**
         * @brief The pointer to the row indexes of the matrix
         * 
         */
        T_index* indexes;

        /**
         * @brief The pointer to the column pointers of the matrix
         * 
         */
        T_index* col_p;

        /**
         * @brief Private function that allocates initial memory for the matrix
         *
         * given a few parematers and allocating the wost case scenario for memory
         *
         * which is CSC plus space for metadata.
         *
         * @throw std::bad_alloc The malloc call failed
         *
         * @return void
         */
        void allocate_memory();

        /**
         * @brief Performs a series of user checks on the template parameters
         *
         * and the class variables to ensure the class is being used correctly.
         *
         * @ref check_valt() is called as a part of this function.
         *
         * @throw std::invalid_argument The template parameters are invalid
         *
         * @return void
         */
        void user_checks();

        /**
         * @brief Private function that encodes the val_t variable
         *
         * so that the first byte is sizeof(T), the second byte is if T is signed,
         *
         * the third byte is if T is floating point, and the last byte is zero.
         *
         * @return uint32_t The encoded val_t variable
         */
        uint32_t encode_valt();

        /**
         * @brief checks that the val_t is encoded correctly compared to T.
         *
         * Helpful for constructing from an existing compressed matrix.
         *
         * @throw std::runtime_error The val_t is not encoded correctly
         *
         * @param valt The val_t variable to check
         *
         * @return void
         */
        void check_valt(uint32_t valt);

        /**
         * @brief Private function that returns the number of bytes needed to store a value
         *
         * @param size The size of the value to store
         *
         * @return uint8_t The number of bytes needed to store the value
         */
        uint8_t byte_width(size_t size);

    public:
        /**
         * @brief Empty constructor for the SparseMatrix class
         *
         * @return An empty SparseMatrix object with no allocation
         */
        SparseMatrix();

        /**
         * @brief Construct a new Sparse Matrix object from an Eigen::SparseMatrix<T>
         *
         * @param mat The eigen matrix to construct from
         *
         * @param destroy If true the values in the matrix will be all replaced with 0
         *
         * @return A SparseMatrix object with the same values as the passed matrix
         *
         * @throw std::invalid_argument The matrix is row major
         *
         * @throw std::bad_alloc The malloc call failed
         */
        SparseMatrix(Eigen::SparseMatrix<T> &mat, bool destroy = false);

        /**
         * @brief Construct a new Sparse Matrix object from a raw CSC matrix
         *
         * @tparam values_t the type of the values array
         * @tparam row_ind the type of the row index array
         * @tparam col_ind the type of the column pointer array
         *
         * @param vals the values array
         * @param indexes the row index array
         * @param col_p the column pointer array
         * @param non_zeros the number of non-zero elements in the matrix
         * @param row_num the number of rows in the matrix
         * @param col_num the number of columns in the matrix
         * @param destroy If true the values in the matrix will be all replaced with 0
         *
         * @return A SparseMatrix object with the same values as the passed matrix
         *
         * @throw std::bad_alloc The malloc call failed
         */
        template <typename values_t, typename row_ind, typename col_ind>
        SparseMatrix(values_t **vals, row_ind **indexes, col_ind **col_p,
                     size_t non_zeros, size_t row_num, size_t col_num,
                     bool destroy = false);

        /**
         * @brief Construct a new Sparse Matrix object from an existing CSF::SparseMatrix
         *
         * @param mat the matrix to deep copy
         *
         * @return A SparseMatrix object with the same values as the passed matrix
         *
         * @throw std::bad_alloc The malloc call failed
         */
        SparseMatrix(CSF::SparseMatrix<T, T_index, 1> &mat);

        /**
         * @brief Construct a new Sparse Matrix object from a file
         *
         * @param filename the file to read the CSF matrix from
         *
         * @return A SparseMatrix object with the same values as the passed file
         *
         * @throw std::invalid_argument The file doesn't exist
         * @throw std::bad_alloc The malloc call failed
         */
        SparseMatrix(const char *filename);

        /**
         * @brief Destroy the Sparse Matrix object
         *
         */
        ~SparseMatrix();

        /**
         * @brief compresses the matrix to compression level 3 (CSF) and returns it
         * 
         * @param destroy if the original matrix is allowed to be destroyed
         * 
         * @return CSF::SparseMatrix<T, T_index, 3> the compressed matrix
         */
        CSF::SparseMatrix<T, T_index, 3> to_csf3(bool destroy = false);

        /**
         * @brief compresses the matrix to compression level 2 (CSF) and returns it
         *
         * @param destroy if the original matrix is allowed to be destroyed
         *
         * @return CSF::SparseMatrix<T, T_index, 2> the compressed matrix
         */
        CSF::SparseMatrix<T, T_index, 2> to_csf2(bool destroy = false);

        /**
         * @brief turns the CSF 1 matrix into an Eigen::SparseMatrix<T> using triplet format
         * 
         * @return Eigen::SparseMatrix<T> the Eigen matrix from CSF 1
         */
        Eigen::SparseMatrix<T> to_eigen();

        /**
         * @brief returns a pointer to the values of the matrix
         * 
         * @return void* the pointer to the values
         */
        void* valuePtr();

        /**
         * @brief returns a pointer to the row indexes of the matrix
         * 
         * @return void* the pointer to the row indexes
         */
        void* indexPtr();

        /**
         * @brief returns a pointer to the column pointers of the matrix
         * 
         * @return void* the pointer to the column pointers
         */
        void* colPtr();

        /**
         * @brief returns the size of the values array in bytes
         * 
         * @return size_t the size of the values array in bytes
         */
        size_t byte_size();

        /**
         * @brief writes the sparse matrix to a file
         *
         * @param filename the file to write the matrix to
         *
         * @return void
         */
        void write(const char *filename);

        /**
         * @brief Returns the number of rows in the matrix
         *
         * @return uint32_t the number of rows in the matrix
         */
        uint32_t rows();

        /**
         * @brief Returns the number of columns in the matrix
         *
         * @return uint32_t the number of columns in the matrix
         */
        uint32_t cols();

        /**
         * @brief Returns the number of non-zero elements in the matrix
         *
         * @return uint32_t the number of non-zero elements in the matrix
         */
        uint32_t nonzeros();

        /**
         * @brief Returns the compression level of the matrix
         *
         * @return uint32_t the compression level of the matrix
         */
        uint32_t compLvl();

        /**
         * @brief The iterator class for the CSF::SparseMatrix, this one is specialized for CSF 1
         *
         */
        class Iterator {};
    };

}