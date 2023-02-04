#pragma once
namespace CSF {
    template <typename T, int compression_level>
    class SparseMatrix {
        private:
            //* Constructor data

            // Compression delimiter
            uint8_t delim = 0;

            // dimensions and size of sparse matrix
            uint32_t num_rows;
            uint32_t num_cols;
            uint32_t num_nonzeros;

            // Data types for matrix values_t and indices
            uint32_t row_t;
            uint32_t col_t;
            uint32_t val_t;

            // compression size and level
            size_t compression_size;

            bool is_allocated = false;

            // void pointers for compression
            void *comp_ptr;
            void *begin_ptr;

            void allocate_memory();

            uint8_t byte_width(size_t size);
        
        public:

            SparseMatrix(Eigen::SparseMatrix<T>& mat, bool destroy = false);

            template <typename values_t, typename row_ind, typename col_ind>
            SparseMatrix(values_t **vals, row_ind **indexes, col_ind **col_p,
                         size_t non_zeros, size_t row_num, size_t col_num,
                         bool destroy = false);

            SparseMatrix(const char *filename);

            ~SparseMatrix();

            size_t byte_size();

            void* begin();

            void* end();

            void write(const char *filename);

            //class Iterator;

            // class Col {
                
            //     template <typename index_t>
            //     Col (index_t col) {
            //         it = Iterator(matrix, col)
            //     }

            //     Eigen::Vector<T, 1, -1> operator*(Eigen::Vector<T, 1, -1>) {

            //     }

            //     private:
            //         Iterator& it;
            // }


            // Column(index_t col) {
            //     Col()
            //     // pass in data for column needed
            // }

    };
}