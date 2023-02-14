#pragma once

#include <vector>

namespace CSF
{
    template <typename T, typename T_index, int compression_level>
    void SparseMatrix<T, T_index, compression_level>::allocate_memory()
    {
        // Malloc memory for the data, never worse then CSC so allocate CSC amount
        // plus space for the value and row, col indicies, and a buffer zone

        size_t csc_size = num_nonzeros * val_t + num_nonzeros * row_t + num_cols * col_t;
        size_t comp_size_guess = 28 + (8 * num_cols) + csc_size * 3;

        begin_ptr = malloc(comp_size_guess);

        // Check if memory was allocated
        if (!begin_ptr)
        {
            throw std::bad_alloc();
        }

        // Set the pointer to the start of the data
        comp_ptr = begin_ptr;
    }

    template <typename T, typename T_index, int compression_level>
    uint8_t SparseMatrix<T, T_index, compression_level>::byte_width(size_t size)
    {
        switch (size)
        {
        case 0 ... 255:
            return 1;
        case 256 ... 65535:
            return 2;
        case 65536 ... 4294967295:
            return 4;
        default:
            return 8;
        }
    }

    // ---- Member Functions ----
    template <typename T, typename T_index, int compression_level>
    size_t SparseMatrix<T, T_index, compression_level>::byte_size()
    {
        return compression_size;
    }

    template <typename T, typename T_index, int compression_level>
    void *SparseMatrix<T, T_index, compression_level>::beginPtr()
    {
        return begin_ptr;
    }

    template <typename T, typename T_index, int compression_level>
    void *SparseMatrix<T, T_index, compression_level>::endPtr()
    {
        return comp_ptr;
    }

    // write data to file
    template <typename T, typename T_index, int compression_level>
    void SparseMatrix<T, T_index, compression_level>::write(const char *filename)
    {
        // write data to file
        FILE *fp = fopen(filename, "wb");
        fwrite(begin_ptr, 1, compression_size, fp);
        fclose(fp);
    }

    template <typename T, typename T_index, int compression_level>
    uint32_t SparseMatrix<T, T_index, compression_level>::rows()
    {
        return num_rows;
    }

    template <typename T, typename T_index, int compression_level>
    uint32_t SparseMatrix<T, T_index, compression_level>::cols()
    {
        return num_cols;
    }

    template <typename T, typename T_index, int compression_level>
    uint32_t SparseMatrix<T, T_index, compression_level>::nonzeros()
    {
        return num_nonzeros;
    }

    template <typename T, typename T_index, int compression_level>
    uint32_t SparseMatrix<T, T_index, compression_level>::compLvl()
    {
        return compression_level;
    }

    template <typename T, typename T_index, int compression_level>
    CSF::SparseMatrix<T, T_index, 1> SparseMatrix<T, T_index, compression_level>::to_csf1()
    {
        // Steps: convert to eigen triplet triplet, convert to eigen, convert to CSF1

        // create a triplet vector
        std::vector<Eigen::Triplet<T>> triplet;

        // reserve space for the triplet vector
        triplet.reserve(num_nonzeros);

        // use iterator to go through the data
        CSF::SparseMatrix<T, T_index, compression_level>::Iterator

    }


    // --------- Compression Level 1 Methods ---------

    template <typename T, typename T_index>
    uint8_t SparseMatrix<T, T_index, 1>::byte_width(size_t size)
    {
        switch (size)
        {
        case 0 ... 255:
            return 1;
        case 256 ... 65535:
            return 2;
        case 65536 ... 4294967295:
            return 4;
        default:
            return 8;
        }
    }

    template <typename T, typename T_index>
    uint32_t SparseMatrix<T, T_index, 1>::rows()
    {
        return num_rows;
    }

    template <typename T, typename T_index>
    uint32_t SparseMatrix<T, T_index, 1>::cols()
    {
        return num_cols;
    }

    template <typename T, typename T_index>
    uint32_t SparseMatrix<T, T_index, 1>::nonzeros()
    {
        return num_nonzeros;
    }

    template <typename T, typename T_index>
    uint32_t SparseMatrix<T, T_index, 1>::compLvl()
    {
        return compression;
    }

    template <typename T, typename T_index>
    size_t SparseMatrix<T, T_index, 1>::byte_size()
    {
        return compression_size;
    }

    template <typename T, typename T_index>
    CSF::SparseMatrix<T, T_index, 3> SparseMatrix<T, T_index, 1>::to_csf3(bool destroy) 
    {
        // create a new CSF3 matrix using vals, indexes, and col_p
        CSF::SparseMatrix<T, T_index, 3> csf3(&vals, &indexes, &col_p, num_nonzeros, num_rows, num_cols, destroy);

        // return the new matrix
        return csf3;
    }

    template <typename T, typename T_index>
    CSF::SparseMatrix<T, T_index, 2> SparseMatrix<T, T_index, 1>::to_csf2(bool destroy) 
    {
        // create a new CSF2 matrix using vals, indexes, and col_p
        CSF::SparseMatrix<T, T_index, 2> csf2(&vals, &indexes, &col_p, num_nonzeros, num_rows, num_cols, destroy);

        // return the new matrix
        return csf2;
    }

    template <typename T, typename T_index>
    Eigen::SparseMatrix<T> SparseMatrix<T, T_index, 1>::to_eigen()
    {

    }
}