#pragma once

namespace CSF {
    template <typename T, typename T_index, int compression_level>
    void SparseMatrix<T, T_index, compression_level>::allocate_memory()
    {
        // Malloc memory for the data, never worse then CSC so allocate CSC amount
        // space for the value and row, col indicies, and a buffer zone

        size_t csc_size = num_nonzeros * val_t + num_nonzeros * row_t + num_cols * col_t + 300;

        begin_ptr = malloc(csc_size);

        // Check if memory was allocated
        if (!begin_ptr)
        {
            throw std::bad_alloc();
        }

        is_allocated = true;

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
        // ! write data to file
        FILE *fp = fopen(filename, "wb");
        fwrite(begin_ptr, 1, compression_size, fp);
        fclose(fp);
    }
}