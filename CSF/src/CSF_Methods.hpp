#pragma once

#include <vector>
#include <iostream>

#define META_DATA_SIZE 28
#define NUM_META_DATA 7

#define ONE_BYTE_MAX 255
#define TWO_BYTE_MAX 65535
#define FOUR_BYTE_MAX 4294967295

namespace CSF
{
    template <typename T, typename T_index, int compression_level>
    void SparseMatrix<T, T_index, compression_level>::allocate_memory()
    {
        // Malloc memory for the data, never worse then CSC so allocate CSC amount
        // plus space for the value and row, col indicies, and a buffer zone

        size_t csc_size = num_nonzeros * sizeof(T) + num_nonzeros * sizeof(T_index) + num_cols * sizeof(T_index);
        size_t comp_size_guess = META_DATA_SIZE + (sizeof(uint64_t) * num_cols) + csc_size;

        try {
            begin_ptr = malloc(comp_size_guess);
        } catch (std::bad_alloc &e) {
            std::cout << "Error allocating memory for compression" << std::endl;
            throw e;
        }

        // Set the pointer to the start of the data
        compression_size = comp_size_guess;
        comp_ptr = begin_ptr;
    }

    template <typename T, typename T_index, int compression_level>
    uint8_t SparseMatrix<T, T_index, compression_level>::byte_width(size_t size)
    {
        if (size <= ONE_BYTE_MAX) {
            return 1;
        } else if (size <= TWO_BYTE_MAX) {
            return 2;
        } else if (size <= FOUR_BYTE_MAX) {
            return 4;
        } else {
            return 8;
        }
    }

    template <typename T, typename T_index, int compression_level>
    void SparseMatrix<T, T_index, compression_level>::user_checks() {
        // throw an error if the matrix has less than one rows or columns or nonzero values
        if (num_rows < 1 || num_cols < 1 || num_nonzeros < 1)
            throw std::invalid_argument("The matrix must have at least one row, column, and nonzero value");

        // check that T_index is not floating point
        if (std::is_floating_point<T_index>::value)
            throw std::invalid_argument("The index type must be a non-floating point type");

        // check the compression level is either 1, 2, or 3
        if (compression_level < 1 || compression_level > 3)
            throw std::invalid_argument("The compression level must be either 1, 2, or 3");

        // check that T and T_index are numeric types
        if (!std::is_arithmetic<T>::value || !std::is_arithmetic<T_index>::value)
            throw std::invalid_argument("The value and index types must be numeric types");

        // check that the index type is not a bool
        if (std::is_same<T_index, bool>::value)
            throw std::invalid_argument("The value and index types must not be bool");

        // check that the row and col types can hold the number of rows and columns
        if (num_rows > std::numeric_limits<T_index>::max() || num_cols > std::numeric_limits<T_index>::max())
            throw std::invalid_argument("The number of rows and columns must be less than the maximum value of the index type");

        check_valt(val_t);
    }

    template <typename T, typename T_index, int compression_level>
    uint32_t SparseMatrix<T, T_index, compression_level>::encode_valt() {
        uint8_t byte0 = sizeof(T);
        uint8_t byte1 = std::is_floating_point<T>::value ? 1 : 0;
        uint8_t byte2 = std::is_signed_v<T> ? 1 : 0;
        uint8_t byte3 = 0;

        return (byte3 << 24) | (byte2 << 16) | (byte1 << 8) | byte0;
    }

    template <typename T, typename T_index, int compression_level>
    void SparseMatrix<T, T_index, compression_level>::check_valt(uint32_t valt) {
        uint8_t byte0 = valt & 0xFF;
        uint8_t byte1 = (valt >> 8) & 0xFF;
        uint8_t byte2 = (valt >> 16) & 0xFF;
        //uint8_t byte3 = (valt >> 24) & 0xFF;

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
    size_t SparseMatrix<T, T_index, compression_level>::byte_size() { return compression_size; }

    template <typename T, typename T_index, int compression_level>
    void *SparseMatrix<T, T_index, compression_level>::beginPtr() { return begin_ptr; }

    // beginPtr() method but const
    template <typename T, typename T_index, int compression_level>
    const void *SparseMatrix<T, T_index, compression_level>::beginPtr() const { return begin_ptr; }

    template <typename T, typename T_index, int compression_level>
    void *SparseMatrix<T, T_index, compression_level>::endPtr() { return comp_ptr; }

    template <typename T, typename T_index, int compression_level>
    bool SparseMatrix<T, T_index, compression_level>::operator==(const SparseMatrix<T, T_index, compression_level> &other) {
        // check that the number of rows, columns, and nonzeros are the same
        if (num_rows != other.num_rows || num_cols != other.num_cols || num_nonzeros != other.num_nonzeros)
            return false;

        // check that the value type is the same
        if (val_t != other.val_t)
            return false;

        // check that the data is the same
        if (memcmp(begin_ptr, other.beginPtr(), compression_size) != 0)
            return false;

        return true;
    }

    template <typename T, typename T_index, int compression_level>
    bool SparseMatrix<T, T_index, compression_level>::operator!=(const SparseMatrix<T, T_index, compression_level> &other) {
        return !(*this == other);
    }

    template <typename T, typename T_index, int compression_level>
    void SparseMatrix<T, T_index, compression_level>::print() {
        std::cout << "Number of rows: " << num_rows << std::endl;
        std::cout << "Number of columns: " << num_cols << std::endl;
        std::cout << "Number of nonzeros: " << num_nonzeros << std::endl;
        std::cout << "Compression level: " << compression_level << std::endl;
        std::cout << "Compression size: " << compression_size << std::endl;
    }

    template <typename T, typename T_index, int compression_level>
    T SparseMatrix<T, T_index, compression_level>::coeff(size_t row, size_t col) {
        // check that the row and column are within bounds
        if (row >= num_rows || col >= num_cols)
            throw std::out_of_range("The row and column must be within the bounds of the matrix");
        
        // get an iterator to the first element in the col
        CSF::SparseMatrix<T, T_index, compression_level>::Iterator it(*this);

        if (col > 0)
            it.goToColumn(col);

        T val = 0;

        // while the iterator hasn't hit the next column keep going
        while (it.getColIndex() == col) {
            it++;
            std::cout << "Value at row: " << it.getIndex() << ", col: " << it.getColIndex() << " is " << *it << std::endl;
            // if the row matches the row we are looking for, return the value
            if (it.getIndex() == row) {
                val = *it;
                break;
            }
        }

        return val;
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
    uint32_t SparseMatrix<T, T_index, compression_level>::rows() { return num_rows; }

    template <typename T, typename T_index, int compression_level>
    uint32_t SparseMatrix<T, T_index, compression_level>::cols() { return num_cols; }

    template <typename T, typename T_index, int compression_level>
    uint32_t SparseMatrix<T, T_index, compression_level>::nonzeros() { return num_nonzeros; }

    template <typename T, typename T_index, int compression_level>
    uint32_t SparseMatrix<T, T_index, compression_level>::compLvl() { return compression_level; }

    template <typename T, typename T_index, int compression_level>
    CSF::SparseMatrix<T, T_index, 1> SparseMatrix<T, T_index, compression_level>::to_csf1()
    {
        // Steps: convert to eigen triplet triplet, convert to eigen, convert to CSF1

        // create a triplet vector
        std::vector<Eigen::Triplet<T>> triplet;

        // reserve space for the triplet vector
        triplet.reserve(num_nonzeros);

        // create an iterator for the matrix
        CSF::SparseMatrix<T, T_index, compression_level>::Iterator it(*this);

        // iterate over the matrix
        while (it) {
            it++;
            triplet.push_back(Eigen::Triplet<T>(it.getIndex(), it.getColIndex(), *it));
        }

        // create an eigen sparse matrix
        Eigen::SparseMatrix<T> eigen_mat(num_rows, num_cols);

        // set the triplet vector
        eigen_mat.setFromTriplets(triplet.begin(), triplet.end());

        // convert to CSF1
        return CSF::SparseMatrix<T, T_index, 1>(eigen_mat);

    }

    template <typename T, typename T_index, int compression_level>
    Eigen::SparseMatrix<T> SparseMatrix<T, T_index, compression_level>::to_eigen() {
        // create a triplet vector
        std::vector<Eigen::Triplet<T>> triplet;

        // reserve space for the triplet vector
        triplet.reserve(num_nonzeros);

        // create an iterator for the matrix
        CSF::SparseMatrix<T, T_index, compression_level>::Iterator it(*this);

        // iterate over the matrix
        while (it) {
            it++;
            triplet.push_back(Eigen::Triplet<T>(it.getIndex(), it.getColIndex(), *it));
        }

        // create an eigen sparse matrix
        Eigen::SparseMatrix<T> eigen_mat(num_rows, num_cols);

        // set the triplet vector
        eigen_mat.setFromTriplets(triplet.begin(), triplet.end());

        return eigen_mat;
    }


    // --------- Compression Level 1 Methods ---------

    template <typename T, typename T_index>
    uint8_t SparseMatrix<T, T_index, 1>::byte_width(size_t size)
    {
        if (size <= ONE_BYTE_MAX) {
            return 1;
        } else if (size <= TWO_BYTE_MAX) {
            return 2;
        } else if (size <= FOUR_BYTE_MAX) {
            return 4;
        } else {
            return 8;
        }
    }

    template <typename T, typename T_index>
    template <typename new_T>
    CSF::SparseMatrix<new_T, T_index, 1> SparseMatrix<T, T_index, 1>::change_val_type() {
        // ensure that the new value type is not the same as the old value type
        if (std::is_same<new_T, T>::value)
            throw std::invalid_argument("The new value type must be different than the old value type.");

        // ensure that the new value type is arithmetic or throw an error
        if (!std::is_arithmetic<new_T>::value)
            throw std::invalid_argument("The new value type must be arithmetic. (int, float, double, etc.)");
        
        // create a new matrix with the new value type and return it
        
        // create an array to convert the values to
        new_T *new_values = new new_T[num_nonzeros];

        // get a pointer to the values in the matrix
        T *old_values = vals;

        // convert the values
        for (size_t i = 0; i < num_nonzeros; i++) {
            new_values[i] = (new_T)(old_values[i]);
        }

        // create a new matrix
        CSF::SparseMatrix<new_T, T_index, 1> new_mat(&new_values, &indexes, &col_p, num_nonzeros, num_rows, num_cols);

        // free the memory
        delete[] new_values;

        return new_mat;
    }

    template <typename T, typename T_index>
    template <typename new_T_index>
    CSF::SparseMatrix<T, new_T_index, 1> SparseMatrix<T, T_index, 1>::change_idx_type() {
        // ensure that the new index type is not the same as the old index type
        if (std::is_same<new_T_index, T_index>::value)
            throw std::invalid_argument("The new index type must be different than the old index type.");

        // ensure that the new index type is arithmetic or throw an error
        if (!std::is_arithmetic<new_T_index>::value)
            throw std::invalid_argument("The new index type must be arithmetic. (int, float, double, etc.)");

        // ensure the the new index type is not floating point or bool
        if (std::is_floating_point<new_T_index>::value || std::is_same<new_T_index, bool>::value)
            throw std::invalid_argument("The new index type must be an integer type.");
        
        // create a new matrix with the new index type and return it

        // create an array to convert the indexes to
        new_T_index *new_indexes = new new_T_index[num_nonzeros];
        new_T_index *new_col_p = new new_T_index[num_cols + 1];

        // get a pointer to the indexes in the matrix
        T_index *old_indexes = indexes;
        T_index *old_col_p = col_p;

        // convert the indexes
        for (size_t i = 0; i < num_nonzeros; i++) {
            new_indexes[i] = (new_T_index)(old_indexes[i]);
        }

        for (size_t i = 0; i < num_cols + 1; i++) {
            new_col_p[i] = (new_T_index)(old_col_p[i]);
        }

        // create a new matrix
        CSF::SparseMatrix<T, new_T_index, 1> new_mat(&vals, &new_indexes, &new_col_p, num_nonzeros, num_rows, num_cols);

        // free the memory
        delete[] new_indexes;
        delete[] new_col_p;

        return new_mat;
    }

    template <typename T, typename T_index>
    uint32_t SparseMatrix<T, T_index, 1>::rows() { return num_rows; }

    template <typename T, typename T_index>
    uint32_t SparseMatrix<T, T_index, 1>::cols() { return num_cols; }

    template <typename T, typename T_index>
    uint32_t SparseMatrix<T, T_index, 1>::nonzeros() { return num_nonzeros; }

    template <typename T, typename T_index>
    uint32_t SparseMatrix<T, T_index, 1>::compLvl() { return compression; }

    template <typename T, typename T_index>
    size_t SparseMatrix<T, T_index, 1>::byte_size() { return compression_size; }

    template <typename T, typename T_index>
    void *SparseMatrix<T, T_index, 1>::valuePtr() { return vals; }

    template <typename T, typename T_index>
    void *SparseMatrix<T, T_index, 1>::indexPtr() { return indexes; }

    template <typename T, typename T_index>
    void *SparseMatrix<T, T_index, 1>::colPtr() { return col_p; }

    template <typename T, typename T_index>
    bool SparseMatrix<T, T_index, 1>::operator==(const SparseMatrix<T, T_index, 1> &other) {        
        // check that the number of rows, columns, and nonzeros are the same
        if (num_rows != other.num_rows || num_cols != other.num_cols || num_nonzeros != other.num_nonzeros)
            return false;

        // check that the value type is the same
        if (val_t != other.val_t)
            return false;

        // check that the data is the same
        if (memcmp(vals, other.vals, num_nonzeros * sizeof(T)) != 0)
            return false;

        // check that the indexes are the same
        if (memcmp(indexes, other.indexes, num_nonzeros * sizeof(T_index)) != 0)
            return false;

        // check that the column pointers are the same
        if (memcmp(col_p, other.col_p, (num_cols + 1) * sizeof(T_index)) != 0)
            return false;

        return true;
    }

    template <typename T, typename T_index>
    bool SparseMatrix<T, T_index, 1>::operator!=(const SparseMatrix<T, T_index, 1> &other) {
        return !(*this == other);
    }

    template <typename T, typename T_index>
    void SparseMatrix<T, T_index, 1>::user_checks()
    {
        // throw an error if the matrix has less than one rows or columns or nonzero values
        if (num_rows < 1 || num_cols < 1 || num_nonzeros < 1)
            throw std::invalid_argument("The matrix must have at least one row, column, and nonzero value");

        // check that T_index is not floating point
        if (std::is_floating_point<T_index>::value)
            throw std::invalid_argument("The index type must be a non-floating point type");

        // check that T and T_index are numeric types
        if (!std::is_arithmetic<T>::value || !std::is_arithmetic<T_index>::value)
            throw std::invalid_argument("The value and index types must be numeric types");

        // check that the index type is not a bool
        if (std::is_same<T_index, bool>::value)
            throw std::invalid_argument("The value and index types must not be bool");

        check_valt(val_t);
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
        //uint8_t byte3 = (valt >> 24) & 0xFF;

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
        uint32_t meta[NUM_META_DATA] = {compression, row_t, col_t, val_t, num_rows, num_cols, num_nonzeros};

        // write the metadata
        fwrite(meta, sizeof(uint32_t), NUM_META_DATA, fp);

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