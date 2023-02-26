#pragma once


namespace CSF {

    
    template <typename T, typename T_index=uint64_t, int compression_level=3>
    class SparseMatrix {
        const uint8_t delim = 0;

        uint32_t num_rows = 0;
        uint32_t num_cols = 0;
        uint32_t num_nonzeros = 0;

        uint32_t row_t;
        uint32_t col_t;
        uint32_t val_t;

        size_t compression_size;
        uint32_t compression = compression_level;

        void *comp_ptr;
        void *begin_ptr;


        void allocate_memory();

        uint32_t encode_valt();

        void check_valt(uint32_t valt);

        uint8_t byte_width(size_t size);

        uint64_t* create_metadata();

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

        ~SparseMatrix();

        void write(const char *filename);

        CSF::SparseMatrix<T, T_index, 1> to_csf1();

        // as<CSF::SparseMatrix<T, T_index, 3>(){};

        // template <class to>
        // to as(){
            
        // }

        Eigen::SparseMatrix<T> to_eigen();

        const void *beginPtr();

        const void *endPtr();

        size_t byte_size();

        uint32_t rows();

        uint32_t cols();

        uint32_t nonzeros();

        uint32_t compLvl();

        class Iterator;
    };


    
    template <typename T, typename T_index>
    class SparseMatrix<T, T_index, 1> {
        const uint8_t delim = 0;

        uint32_t num_rows;
        uint32_t num_cols;
        uint32_t num_nonzeros;

        uint32_t row_t;
        uint32_t col_t;
        uint32_t val_t;

        size_t compression_size;
        uint32_t compression = 1;

        void *comp_ptr;
        void *begin_ptr;

        T* vals;
        T_index* indexes;
        T_index* col_p;

        void allocate_memory();

        uint32_t encode_valt();

        void check_valt(uint32_t valt);

        uint8_t byte_width(size_t size);

    public:
        SparseMatrix();

        SparseMatrix(Eigen::SparseMatrix<T> &mat, bool destroy = false);

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

        const void* valuePtr();

        const void* indexPtr();

        const void* colPtr();

        size_t byte_size();

        void write(const char *filename);

        uint32_t rows();

        uint32_t cols();

        uint32_t nonzeros();

        uint32_t compLvl();

        class Iterator;
    };

}