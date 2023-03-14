/**
 * @file CSF_SparseMatrix.hpp
 * @author Skyler Ruiter (ruitersk@mail.gvsu.edu) & Seth Wolfgang (wolfgans@mail.gvsu.edu)
 * @brief Definitions for the CSF SparseMatrix class
 * @version 0.1
 * @date 2023-02-27
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#pragma once

#define DELIM 0

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
        const uint8_t delim = DELIM;

        uint32_t num_rows = 0;
        uint32_t num_cols = 0;
        uint32_t num_nonzeros = 0;

        uint32_t row_t;
        uint32_t col_t;
        uint32_t val_t;

        size_t compression_size;
        uint32_t compression = compression_level;

        void *begin_ptr;
        void *comp_ptr;

        void allocate_memory();

        uint32_t encode_valt();

        void check_valt(uint32_t valt);

        uint8_t byte_width(size_t size);

        uint64_t* create_metadata();

        void user_checks();

        template <typename values_type, typename rows_type, typename cols_type>
        void compress(values_type *vals, rows_type *indexes, cols_type *col_p);

        double redundancy_check();

    public:
        SparseMatrix();

        SparseMatrix(Eigen::SparseMatrix<T> &mat, bool destroy = false);

        template <typename values_t, typename row_ind, typename col_ind>
        SparseMatrix(values_t **vals, row_ind **indexes, col_ind **col_p,
                     size_t non_zeros, size_t row_num, size_t col_num,
                     bool destroy = false);

        SparseMatrix(const char *filename);

        SparseMatrix(CSF::SparseMatrix<T, T_index, compression_level> &mat);

        SparseMatrix(typename CSF::SparseMatrix<T, T_index, compression_level>::Iterator &iter);

        ~SparseMatrix();

        void write(const char *filename);

        CSF::SparseMatrix<T, T_index, 1> to_csf1();

        Eigen::SparseMatrix<T> to_eigen();

        T coeff(size_t row, size_t col);

        void *beginPtr();

        const void *beginPtr() const;

        void *endPtr();

        size_t byte_size();

        uint32_t rows();

        uint32_t cols();

        uint32_t nonzeros();

        uint32_t compLvl();

        void print();

        bool operator==(const CSF::SparseMatrix<T, T_index, compression_level> &other);

        bool operator!=(const CSF::SparseMatrix<T, T_index, compression_level> &other);

        class Iterator;
    };

    template <typename T, typename T_index, int compression_level>
    class SparseMatrix<T, T_index, compression_level>::Iterator {
        private:
        uint64_t index = 0;

        uint32_t valueWidth;
        uint32_t numRows;    // of matrix
        uint32_t numColumns; // of matrix

        uint8_t newIndexWidth;

        void *data;      // beginptr
        void *endOfData; // endptr

        void *currentIndex; //* ITERATOR MOVEMENT POINTER

        T_index currentCol;
        T *value;

        bool firstIndex = true;   // boolean check for first index
        bool atFirstIndex = true; // boolean check for if at first index

        uint32_t metadata[7]; // array for the metadata

    public:
        Iterator(CSF::SparseMatrix<T, T_index, compression_level> &matrix);

        Iterator(const char *filePath);

        uint32_t *getMetaData();

        void reset();

        void *getData();

        T getValue();

        void *getEnd();

        T &operator*();

        bool operator==(const Iterator &other);

        bool operator!=(const Iterator &other);

        bool operator<(const Iterator &other);

        bool operator>(const Iterator &other);

        uint64_t getIndex();

        T_index getColIndex();

        bool atBeginningOfRun();

        uint64_t operator++(int);

        operator bool() { return endOfData != currentIndex; }

        char *getColumn(uint64_t column);

        // CSF::Iterator<T, T_index, compression_level> getColumn(uint64_t column);

        void setRunValue(T newValue);

        inline void *getColumnAddress(uint64_t column);

        void goToColumn(int column);

        bool compareAddress(void *address);

    private:
        void readMetaData();

        inline void readFile(const char *filePath);

        inline uint64_t interpretPointer(int width);

        void setEnd(void *end);
    };


    template <typename T, typename T_index>
    class SparseMatrix<T, T_index, 1> {
        const uint8_t delim = 0;

        uint32_t num_rows = 0;
        uint32_t num_cols = 0;
        uint32_t num_nonzeros = 0;

        uint32_t row_t;
        uint32_t col_t;
        uint32_t val_t;

        size_t compression_size;
        uint32_t compression = 1;

        void *begin_ptr;
        void *comp_ptr;

        T* vals;
        T_index* indexes;
        T_index* col_p;

        void allocate_memory();

        void user_checks();

        uint32_t encode_valt();

        void check_valt(uint32_t valt);

        uint8_t byte_width(size_t size);

    public:
        SparseMatrix();

        SparseMatrix(Eigen::SparseMatrix<T> &mat, bool destroy = false);

        template <typename T2, typename T_index2, int compression_level>
        SparseMatrix(CSF::SparseMatrix<T2, T_index2, compression_level> &mat);

        template <typename values_t, typename row_ind, typename col_ind>
        SparseMatrix(values_t **vals, row_ind **indexes, col_ind **col_p,
                     size_t non_zeros, size_t row_num, size_t col_num,
                     bool destroy = false);

        SparseMatrix(CSF::SparseMatrix<T, T_index, 1> &mat);

        SparseMatrix(const char *filename);

        ~SparseMatrix();

        CSF::SparseMatrix<T, T_index, 3> to_csf3(bool destroy = false);

        CSF::SparseMatrix<T, T_index, 2> to_csf2(bool destroy = false);

        Eigen::SparseMatrix<T> to_eigen();

        void* valuePtr();
    
        void* indexPtr();

        void* colPtr();

        size_t byte_size();

        void write(const char *filename);

        uint32_t rows();

        uint32_t cols();

        uint32_t nonzeros();

        uint32_t compLvl();

        template <typename new_T>
        CSF::SparseMatrix<new_T, T_index, 1> change_val_type();

        template <typename new_T_index>
        CSF::SparseMatrix<T, new_T_index, 1> change_idx_type();

        bool operator==(const CSF::SparseMatrix<T, T_index, 1> &other);

        bool operator!=(const CSF::SparseMatrix<T, T_index, 1> &other);

        class Iterator {};
    };

}