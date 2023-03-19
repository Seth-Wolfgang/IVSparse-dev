#pragma once

#define DELIM 0

namespace CSF {

    template <typename T, typename T_index=uint64_t, uint8_t compression_level=3>
    class SparseMatrix {
        private:

        const uint8_t delim = DELIM;

        uint32_t rows = 0;
        uint32_t cols = 0;
        uint32_t nnz = 0;

        uint32_t val_t;
        uint32_t index_t;

        size_t compression_size;
        uint8_t compression = compression_level;

        void **data;
        void **end_pointers;
        uint32_t *meta_data;

        template <typename T2, typename T_index2>
        void compressCSC(T2 *vals, T_index2 *row_ind, T_index2 *col_ptr);

        uint8_t byte_width(size_t size);

        uint32_t encode_valt();

        void check_valt(uint32_t valt);

        void user_checks();

        public:

        SparseMatrix();

        SparseMatrix(Eigen::SparseMatrix<T> &mat);

        // template <typename T2, typename T_index2>
        // SparseMatrix(T2 *vals, T_index2 *row_ind, T_index2 *col_ptr, size_t nnz, size_t rows, size_t cols);

        ~SparseMatrix();

        void write(const char *filename);

        void *getColPointer(uint32_t col);

        size_t getColSize(uint32_t col);

        uint32_t innerSize();

        uint32_t outerSize();

        class Column{};

        class InnerIterator;
    };


    template <typename T, typename T_index>
    class SparseMatrix<T, T_index, 1> {
        private:

        const uint8_t delim = DELIM;

        uint32_t rows = 0;
        uint32_t cols = 0;
        uint32_t nnz = 0;

        uint32_t val_t;
        uint32_t index_t;

        size_t compression_size;
        uint8_t compression = 1;

        T *vals;
        T_index *row_ind;
        T_index *col_ptr;

        void user_checks();

        uint32_t encode_valt();

        void check_valt(uint32_t valt);

        uint8_t byte_width(size_t size);

        public:

        SparseMatrix();

        SparseMatrix(Eigen::SparseMatrix<T> &mat);

        ~SparseMatrix();

        void *valuePtr();

        void *innerIndexPtr();

        void *outerIndexPtr();

        Eigen::SparseMatrix<T> toEigen();

        size_t compressionSize();

        void write(const char *filename);

        uint32_t innerSize();

        uint32_t outerSize();

        uint32_t nonZeros();

        bool operator==(const SparseMatrix<T, T_index, 1> &other);

        bool operator!=(const SparseMatrix<T, T_index, 1> &other);

        class InnerIterator;
    };


    template <typename T, typename T_index, uint8_t compression_level>
    class SparseMatrix<T, T_index, compression_level>::InnerIterator {
        private:

        T_index column;
        T_index row;
        T val;

        T_index new_row;

        uint8_t index_width = 1;

        void *data;
        void *end_ptr;

        bool atFirst = true;

        void decodeIndex();

        public:

        InnerIterator();

        InnerIterator(SparseMatrix<T, T_index, compression_level> &mat, uint32_t col);

        void operator++(int);

        T_index index();

        T_index col();

        T value();

        bool operator==(const InnerIterator &other);

        bool operator!=(const InnerIterator &other);

        bool operator<(const InnerIterator &other);

        bool operator>(const InnerIterator &other);

        T operator*();

        operator bool() { return end_ptr >= data; };
        
    };

}