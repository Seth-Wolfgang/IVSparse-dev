#pragma once

#include <vector>
#include <map>
#include <iostream>

#define META_DATA_SIZE 24
#define NUM_META_DATA 6

#define ONE_BYTE_MAX 255
#define TWO_BYTE_MAX 65535
#define FOUR_BYTE_MAX 4294967295

namespace CSF {

    template <typename T, typename T_index, uint8_t compression_level>
    template <typename T2, typename T_index2>
    void SparseMatrix<T, T_index, compression_level>::compressCSC(T2 *vals, T_index2 *row_ind, T_index2 *col_ptr) {

        // set the val_t and index_t
        val_t = encode_valt();
        index_t = sizeof(T_index);

        // malloc space for the meta data
        meta_data = new uint32_t[NUM_META_DATA];

        // Set the meta data
        meta_data[0] = compression;
        meta_data[1] = rows;
        meta_data[2] = cols;
        meta_data[3] = nnz;
        meta_data[4] = val_t;
        meta_data[5] = index_t;

        // run the user checks
        user_checks();

        // malloc space for the data
        try {
            data = (void **)malloc(cols * sizeof(void*));
            end_pointers = (void **)malloc(cols * sizeof(void*));
        } catch (std::bad_alloc &e) {
            std::cout << "Error: " << e.what() << std::endl;
            exit(1);
        }

        // loop through each column
        //#pragma omp parallel for
        for (size_t i = 0; i < cols; i++) {
            // construct the dictionary

            // create a std::map that holds value as the key and a vector of indices as the value
            std::map<T2, std::vector<T_index2>> dict;

            for (T_index2 j = col_ptr[i]; j < col_ptr[i + 1]; j++) {

                // check if the column is empty
                if (col_ptr[i] == col_ptr[i + 1]) {
                    
                    // set the data and end pointers to null
                    data[i] = nullptr;
                    end_pointers[i] = nullptr;
                    
                    break;
                }

                // if the value is already in the dictionary
                if (dict.find(vals[j]) != dict.end()) {

                    // add the index to the vector
                    if (compression == 3) {

                        // positive delta encode
                        dict[vals[j]].push_back(row_ind[j] - row_ind[j - 1]);
                        
                        // update the max delta
                        if ((row_ind[j] - row_ind[j - 1]) > dict[vals[j]][0]) {

                            dict[vals[j]][0] = row_ind[j] - row_ind[j - 1];
                        }

                    } else {

                        dict[vals[j]].push_back(row_ind[j]);
                    }

                } else {

                    // create a new vector with the index
                    dict[vals[j]] = std::vector<T_index2>{row_ind[j]};

                    if (compression == 3) {

                        dict[vals[j]].push_back(row_ind[j]);
                    }
                }

            } // end val loop

            size_t col_size = 0;

            // malloc space for the column
            if (compression == 3) {
                for (auto &pair : dict) {
                    pair.second[0] = byte_width(pair.second[0]);
                    col_size += sizeof(T) + 1 + (pair.second[0] * (pair.second.size() - 1)) + pair.second[0];
                }
            } else {
                // loop through the dictionary and calculate the size of the column
                for (auto &pair : dict) {
                    col_size += sizeof(T) + 1 + (sizeof(T_index) * pair.second.size()) + sizeof(T_index);
                }
            }

            compression_size += col_size;

            try {
                data[i] = malloc(col_size);
            } catch (std::bad_alloc &e) {
                std::cout << "Error: " << e.what() << std::endl;
                exit(1);
            }

            //! print out the dictionary
            // for (auto &pair : dict) {
            //     std::cout << pair.first << ": ";
            //     for (auto k = 0; k < pair.second.size(); k++) {
            //         std::cout << pair.second[k] << " ";
            //     }
            //     std::cout << std::endl;
            // }

            void *comp_ptr = data[i];

            // loop through the dictionary and write the data to the column
            for (auto &pair : dict) {

                // write the value
                *(T *)comp_ptr = (T)pair.first;
                comp_ptr = (T *)comp_ptr + 1;

                // write the index width
                if (compression == 3) {
                    *(uint8_t *)comp_ptr = (uint8_t)pair.second[0];
                    comp_ptr = (uint8_t *)comp_ptr + 1;
                } else {
                    *(uint8_t *)comp_ptr = sizeof(T_index);
                    comp_ptr = (uint8_t *)comp_ptr + 1;
                }

                // write the indices
                for (size_t k = 0; k < pair.second.size(); k++) {
                    if (compression == 3) {
                        if (k == 0) {
                            continue;
                        }

                        // create a type of the correct width
                        switch (pair.second[0]) {
                            case 1:
                                *(uint8_t *)comp_ptr = (uint8_t)pair.second[k];
                                comp_ptr = (uint8_t *)comp_ptr + 1;
                                break;
                            case 2:
                                *(uint16_t *)comp_ptr = (uint16_t)pair.second[k];
                                comp_ptr = (uint16_t *)comp_ptr + 1;
                                break;
                            case 4:
                                *(uint32_t *)comp_ptr = (uint32_t)pair.second[k];
                                comp_ptr = (uint32_t *)comp_ptr + 1;
                                break;
                            case 8:
                                *(uint64_t *)comp_ptr = (uint64_t)pair.second[k];
                                comp_ptr = (uint64_t *)comp_ptr + 1;
                                break;
                        }
                    } else {
                        *(T_index *)comp_ptr = (T_index)pair.second[k];
                        comp_ptr = (T_index *)comp_ptr + 1;
                    }
                }

                // write the delimiter
                if (compression == 3) {
                    // write a delimiter of the correct width
                    switch (pair.second[0]) {
                        case 1:
                            *(uint8_t *)comp_ptr = (uint8_t)DELIM;
                            comp_ptr = (uint8_t *)comp_ptr + 1;
                            break;
                        case 2:
                            *(uint16_t *)comp_ptr = (uint16_t)DELIM;
                            comp_ptr = (uint16_t *)comp_ptr + 1;
                            break;
                        case 4:
                            *(uint32_t *)comp_ptr = (uint32_t)DELIM;
                            comp_ptr = (uint32_t *)comp_ptr + 1;
                            break;
                        case 8:
                            *(uint64_t *)comp_ptr = (uint64_t)DELIM;
                            comp_ptr = (uint64_t *)comp_ptr + 1;
                            break;
                    }
                } else {
                    *(T_index *)comp_ptr = (T_index)DELIM;
                    comp_ptr = (T_index *)comp_ptr + 1;
                }

                // set the end ptr
                end_pointers[i] = comp_ptr;

            } // end dict loop


        } // end col loop

        compression_size += META_DATA_SIZE + (sizeof(void *) * cols) * 2;

    } // end compressCSC


    template <typename T, typename T_index, uint8_t compression_level>
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

    template <typename T, typename T_index, uint8_t compression_level>
    void SparseMatrix<T, T_index, compression_level>::write(const char *filename) {
        // open the file
        FILE *fp = fopen(filename, "wb");

        // write the metadata
        fwrite(meta_data, 1, sizeof(uint32_t) * NUM_META_DATA, fp);

        // write the distance between the end and start pointers
        for (uint32_t i = 0; i < cols; i++) {
            size_t size = (char *)end_pointers[i] - (char *)data[i];
            fwrite(&size, 1, sizeof(size_t), fp);
        }

        // int test = 1;
        // fwrite(data[test], 1, (char *)end_pointers[test] - (char *)data[test], fp);

        // write each column
        for (uint32_t i = 0; i < cols; i++) {
            fwrite(data[i], 1, (char *)end_pointers[i] - (char *)data[i], fp);
        }

        // close the file  
        fclose(fp);

    }

    template <typename T, typename T_index, uint8_t compression_level>
    uint32_t SparseMatrix<T, T_index, compression_level>::encode_valt() {
        uint8_t byte0 = sizeof(T);
        uint8_t byte1 = std::is_floating_point<T>::value ? 1 : 0;
        uint8_t byte2 = std::is_signed_v<T> ? 1 : 0;
        uint8_t byte3 = 0;

        return (byte3 << 24) | (byte2 << 16) | (byte1 << 8) | byte0;
    }

    template <typename T, typename T_index, uint8_t compression_level>
    void SparseMatrix<T, T_index, compression_level>::check_valt(uint32_t valt)
    {
        uint8_t byte0 = valt & 0xFF;
        uint8_t byte1 = (valt >> 8) & 0xFF;
        uint8_t byte2 = (valt >> 16) & 0xFF;
        // uint8_t byte3 = (valt >> 24) & 0xFF;

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

    template <typename T, typename T_index, uint8_t compression_level>
    void SparseMatrix<T, T_index, compression_level>::user_checks()
    {
        // throw an error if the matrix has less than one rows or columns or nonzero values
        if (rows < 1 || cols < 1 || nnz < 1)
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
        if (rows > std::numeric_limits<T_index>::max() || cols > std::numeric_limits<T_index>::max())
            throw std::invalid_argument("The number of rows and columns must be less than the maximum value of the index type");

        check_valt(val_t);
    }

    template <typename T, typename T_index, uint8_t compression_level>
    void* SparseMatrix<T, T_index, compression_level>::getColPointer(uint32_t col) { return data[col]; }

    template <typename T, typename T_index, uint8_t compression_level>
    size_t SparseMatrix<T, T_index, compression_level>::getColSize(uint32_t col) { return (char *)end_pointers[col] - (char *)data[col]; }

    template <typename T, typename T_index, uint8_t compression_level>
    uint32_t SparseMatrix<T, T_index, compression_level>::innerSize() { return rows; }

    template <typename T, typename T_index, uint8_t compression_level>
    uint32_t SparseMatrix<T, T_index, compression_level>::outerSize() { return cols; }

} // end namespace CSF