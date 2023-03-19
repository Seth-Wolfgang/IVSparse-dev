#pragma once

#include <vector>
#include <map>
#include <iostream>

#define META_DATA_SIZE 28
#define NUM_META_DATA 6

#define ONE_BYTE_MAX 255
#define TWO_BYTE_MAX 65535
#define FOUR_BYTE_MAX 4294967295

namespace CSF {

    template <typename T, typename T_index, uint8_t compression_level>
    template <typename T2, typename T_index2>
    void SparseMatrix<T, T_index, compression_level>::compressCSC(T2 *vals, T_index2 *row_ind, T_index2 *col_ptr) {
        
        // malloc space for the meta data
        meta_data = new uint32_t[NUM_META_DATA];

        // Set the meta data
        meta_data[0] = compression;
        meta_data[1] = rows;
        meta_data[2] = cols;
        meta_data[3] = nnz;
        meta_data[4] = sizeof(T); //! change later
        meta_data[5] = sizeof(T_index);

        // malloc space for the data
        try {
            data = (void **)malloc(cols * sizeof(void*));
            end_pointers = (void **)malloc(cols * sizeof(void*));
        } catch (std::bad_alloc &e) {
            std::cout << "Error: " << e.what() << std::endl;
            exit(1);
        }

        // loop through each column
        for (size_t i = 0; i < cols; i++) {
            // construct the dictionary

            // create a std::map that holds value as the key and a vector of indices as the value
            std::map<T2, std::vector<T_index2>> dict;

            for (T_index2 j = col_ptr[i]; j < col_ptr[i + 1]; j++) {

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

            try {
                data[i] = malloc(col_size);
            } catch (std::bad_alloc &e) {
                std::cout << "Error: " << e.what() << std::endl;
                exit(1);
            }

            // loop through the dictionary and write the data to the column
            for (auto &pair : dict) {

                void *comp_ptr = data[i];

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
                for (auto k = 0; k < pair.second.size(); k++) {
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

} // end namespace CSF