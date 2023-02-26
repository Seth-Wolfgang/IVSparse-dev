#pragma once

#include <vector>
#include <iostream>

namespace CSF
{
    template <typename T, typename T_index, int compression_level>
    void SparseMatrix<T, T_index, compression_level>::allocate_memory()
    {
        // Malloc memory for the data, never worse then CSC so allocate CSC amount
        // plus space for the value and row, col indicies, and a buffer zone

        size_t csc_size = num_nonzeros * sizeof(T) + num_nonzeros * sizeof(T_index) + num_cols * sizeof(T_index);
        size_t comp_size_guess = 28 + (8 * num_cols) + csc_size;

        try {
            begin_ptr = malloc(comp_size_guess);
        } catch (std::bad_alloc &e) {
            std::cout << "Error allocating memory for compression" << std::endl;
            throw e;
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

    template <typename T, typename T_index, int compression_level>
    uint32_t SparseMatrix<T, T_index, compression_level>::encode_valt() {
        uint8_t byte0 = sizeof(T);
        uint8_t byte1 = std::is_floating_point_v<T> ? 1 : 0;
        uint8_t byte2 = std::is_signed_v<T> ? 1 : 0;
        uint8_t byte3 = 0;

        return (byte3 << 24) | (byte2 << 16) | (byte1 << 8) | byte0;
    }

    template <typename T, typename T_index, int compression_level>
    void SparseMatrix<T, T_index, compression_level>::check_valt(uint32_t valt) {
        uint8_t byte0 = valt & 0xFF;
        uint8_t byte1 = (valt >> 8) & 0xFF;
        uint8_t byte2 = (valt >> 16) & 0xFF;
        uint8_t byte3 = (valt >> 24) & 0xFF;

        if (byte0 != sizeof(T)) {
            std::cout << "Error: Value type size does not match" << std::endl;
            throw std::runtime_error("Value type size does not match, correct size is " + std::to_string(sizeof(T)) + "");
        }

        if (byte1 != std::is_floating_point_v<T>) {
            std::cout << "Error: Value type is not floating point" << std::endl;
            throw std::runtime_error("Value type is not floating point when it should be");
        }

        if (byte2 != std::is_signed_v<T>) {
            std::cout << "Error: Value type is not signed" << std::endl;
            throw std::runtime_error("Value type is not signed when it should be");
        }
    }

    // ---- Member Functions ----
    template <typename T, typename T_index, int compression_level>
    size_t SparseMatrix<T, T_index, compression_level>::byte_size()
    {
        return compression_size;
    }

    template <typename T, typename T_index, int compression_level>
    const void *SparseMatrix<T, T_index, compression_level>::beginPtr()
    {
        return begin_ptr;
    }

    template <typename T, typename T_index, int compression_level>
    const void *SparseMatrix<T, T_index, compression_level>::endPtr()
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
        //CSF::SparseMatrix<T, T_index, compression_level>::Iterator;

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
    void *SparseMatrix<T, T_index, 1>::valuePtr()
    {
        return vals;
    }

    template <typename T, typename T_index>
    const void *SparseMatrix<T, T_index, 1>::indexPtr()
    {
        return indexes;
    }

    template <typename T, typename T_index>
    const void *SparseMatrix<T, T_index, 1>::colPtr()
    {
        return col_p;
    }

    template <typename T, typename T_index>
    uint32_t SparseMatrix<T, T_index, 1>::encode_valt()
    {
        uint8_t byte0 = sizeof(T);
        uint8_t byte1 = std::is_floating_point_v<T> ? 1 : 0;
        uint8_t byte2 = std::is_signed_v<T> ? 1 : 0;
        uint8_t byte3 = 0;

        return (byte3 << 24) | (byte2 << 16) | (byte1 << 8) | byte0;
    }

    template <typename T, typename T_index>
    void SparseMatrix<T, T_index, 1>::check_valt(uint32_t valt)
    {
        uint8_t byte0 = valt & 0xFF;
        uint8_t byte1 = (valt >> 8) & 0xFF;
        uint8_t byte2 = (valt >> 16) & 0xFF;
        uint8_t byte3 = (valt >> 24) & 0xFF;

        if (byte0 != sizeof(T))
        {
            std::cout << "Error: Value type size does not match" << std::endl;
            throw std::runtime_error("Value type size does not match, correct size is " + std::to_string(sizeof(T)) + "");
        }

        if (byte1 != std::is_floating_point_v<T>)
        {
            std::cout << "Error: Value type is not floating point" << std::endl;
            throw std::runtime_error("Value type is not floating point when it should be");
        }

        if (byte2 != std::is_signed_v<T>)
        {
            std::cout << "Error: Value type is not signed" << std::endl;
            throw std::runtime_error("Value type is not signed when it should be");
        }
    }

    template <typename T, typename T_index>
    void SparseMatrix<T, T_index, 1>::write(const char *filename)
    {
        // write data to file
        FILE *fp = fopen(filename, "wb");

        // construct the metadata
        // * <compression, row_t, col_t, val_t, num_rows, num_cols, num_nonzeros, [[col_pointers] [vals] [indexes]]>
        uint32_t metadata[7] = {compression, row_t, col_t, val_t, num_rows, num_cols, num_nonzeros};

        // write the metadata
        fwrite(metadata, sizeof(uint32_t), 7, fp);

        // write the col_p
        fwrite(col_p, sizeof(T_index), num_cols + 1, fp);

        // write the vals
        fwrite(vals, sizeof(T), num_nonzeros, fp);

        // write the indexes
        fwrite(indexes, sizeof(T_index), num_nonzeros, fp);

        fclose(fp);
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
        // construct triplet list from CSC
        std::vector<Eigen::Triplet<T>> tripletList;
        tripletList.reserve(num_nonzeros);

        for (uint32_t i = 0; i < num_cols; i++)
        {
            for (uint32_t j = col_p[i]; j < col_p[i + 1]; j++)
            {
                tripletList.push_back(Eigen::Triplet<T>(indexes[j], i, vals[j]));
            }
        }

        // construct the Eigen matrix
        Eigen::SparseMatrix<T> eigen(num_rows, num_cols);
        eigen.setFromTriplets(tripletList.begin(), tripletList.end());

        // return the Eigen matrix
        return eigen;
    }
}