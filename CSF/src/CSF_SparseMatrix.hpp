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

        public:

        SparseMatrix();

        SparseMatrix(Eigen::SparseMatrix<T> &mat);

        // template <typename T2, typename T_index2>
        // SparseMatrix(T2 *vals, T_index2 *row_ind, T_index2 *col_ptr, size_t nnz, size_t rows, size_t cols);

        ~SparseMatrix();
    };


    // template <typename T, typename T_index>
    // class SparseMatrix<T, T_index, 1> {

    // };

}