/**
 * @file CSF_Private_Methods.hpp
 * @author Skyler Ruiter and Seth Wolfgang
 * @brief Private helper methods for the CSF class.
 * @version 0.1
 * @date 2023-06-21
 */

#pragma once

namespace CSF {

    // CSC to CSF Compression Algorithm
    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    template <typename T2, typename indexT2>
    void SparseMatrix<T, indexT, compressionLevel, columnMajor>::compressCSC(T2* vals, indexT2* innerIndices, indexT2* outerPointers) {

        // ---- Stage 1: Setup the Matrix ---- //

        // set the value and index types of the matrix
        encodeValueType();
        index_t = sizeof(indexT);

        // allocate space for metadata
        metadata = new uint32_t[NUM_META_DATA];

        // setup the rest of the metadata
        metadata[0] = compressionLevel;
        metadata[1] = innerDim;
        metadata[2] = outerDim;
        metadata[3] = nnz;
        metadata[4] = val_t;
        metadata[5] = index_t;

        // run the user checks on the metadata
        #ifdef CSF_DEBUG
        userChecks();
        #endif

        // allocate space for the data
        try {
            data = (void**)calloc(outerDim, sizeof(void*));
            endPointers = (void**)calloc(outerDim, sizeof(void*));
        }
        catch (std::bad_alloc& e) {
            std::cout << "Error: " << e.what() << std::endl;
            exit(1);
        }

        if constexpr (compressionLevel == 2) {
            // allocate space for the value array size
            try {
                valueArraySize = (indexT*)malloc(outerDim * sizeof(indexT));
                valueArray = (T**)malloc(outerDim * sizeof(T*));
                countsArray = (indexT**)malloc(outerDim * sizeof(indexT*));
            }
            catch (std::bad_alloc& e) {
                std::cout << "Error: " << e.what() << std::endl;
                exit(1);
            }
        }

        // ---- Stage 2: Construct the Dictionary For Each Column ---- //

        // Loop through each column and construct a middle data structre for the matrix
        #ifdef CSF_PARALLEL
        #pragma omp parallel for
        #endif
        for (uint32_t i = 0; i < outerDim; i++) {
            // create the data structure to temporarily hold the data
            std::map<T2, std::vector<indexT2>> dict; // Key = value, Value = vector of indices

            // check if the current column is empty
            if (outerPointers[i] == outerPointers[i + 1]) {
                data[i] = nullptr;
                endPointers[i] = nullptr;

                if constexpr (compressionLevel == 2) {
                    valueArraySize[i] = 0;
                    valueArray[i] = nullptr;
                    countsArray[i] = nullptr;
                }
                continue;
            }

            // loop through each value in the column and add it to dict
            for (indexT2 j = outerPointers[i]; j < outerPointers[i + 1]; j++) {

                // check if the value is already in the dictionary or not
                if (dict.find(vals[j]) != dict.end()) {

                    // add the index to the vector

                    // if compression level 3 positive delta encode the index during insertion
                    if constexpr (compressionLevel == 3) {
                        // positive delta encode (PDE)
                        dict[vals[j]].push_back(innerIndices[j] - dict[vals[j]][1]);

                        // update the last index (stored in the second index of the vector)
                        dict[vals[j]][1] = innerIndices[j];

                        // update the maximum delta (stored in the first index of the vector)
                        if (dict[vals[j]][dict[vals[j]].size() - 1] > dict[vals[j]][0]) {
                            dict[vals[j]][0] = dict[vals[j]][dict[vals[j]].size() - 1];
                        }
                    }
                    else {
                        // if not compression level 3 just add the index
                        dict[vals[j]].push_back(innerIndices[j]);
                    }
                }
                else {
                    // if value not already in the dictionary add it

                    // create a new vector for the indices
                    dict[vals[j]] = std::vector<indexT2>{ innerIndices[j] };

                    // if compression level 3 add the maximum delta and the last index
                    if constexpr (compressionLevel == 3) {
                        dict[vals[j]].push_back(innerIndices[j]);
                        dict[vals[j]].push_back(innerIndices[j]);
                    }
                }

            } // end of value loop

            // ---- Stage 3: Find and Allocate Size of Column Data ---- //

            // create a variable to hold the size of the column
            size_t outerByteSize = 0;
            size_t performanceVecSize = 0;

            // loop through dictionary finding the byte size of the total column data
            if constexpr (compressionLevel == 3) {
                for (auto& pair : dict) {
                    // change first value to be byte width of the maximum delta
                    pair.second[0] = byteWidth(pair.second[0]);

                    // add the size of the run to the size of the column
                    //* value + index width + indices * index width + delimiter (index width)
                    outerByteSize += sizeof(T) + 1 + (pair.second[0] * (pair.second.size() - 2)) + pair.second[0];
                }
            }
            else {
                // loop through the dictionary and calculate the size of the column
                for (auto& pair : dict) {
                    outerByteSize += (sizeof(indexT) * pair.second.size() + 1);

                    performanceVecSize++;
                }
            }

            // allocate space for the column
            try {
                data[i] = malloc(outerByteSize);
            }
            catch (std::bad_alloc& e) {
                std::cout << "Error: " << e.what() << std::endl;
                exit(1);
            }

            // if compression level 2 allocate space for the performance vectors
            if constexpr (compressionLevel == 2) {
                try {
                    valueArray[i] = (T*)malloc(performanceVecSize * sizeof(T));
                    countsArray[i] = (indexT*)malloc(performanceVecSize * sizeof(indexT));
                }
                catch (std::bad_alloc& e) {
                    std::cout << "Error: " << e.what() << std::endl;
                    exit(1);
                }

                valueArraySize[i] = performanceVecSize;

                performanceVecSize = 0;
            }

            // ---- Stage 4: Write the Data To Memory ---- //

            // get a help pointer for moving through raw memory
            void* helpPtr = data[i];

            // loop through the dictionary and write to memory
            for (auto& pair : dict) {

                // if compression level 2 write the value to the performance vector
                // We don't write delimitors or valueArray indices to helpPtr, only row indices
                if constexpr (compressionLevel == 2) {
                    valueArray[i][performanceVecSize] = pair.first;
                    countsArray[i][performanceVecSize] = pair.second.size();
                    performanceVecSize++;
                }
                else {
                    // Write the value to memory
                    *(T*)helpPtr = (T)pair.first;
                    helpPtr = (T*)helpPtr + 1;

                    // also write the index width
                    *(uint8_t*)helpPtr = (uint8_t)pair.second[0];
                    helpPtr = (uint8_t*)helpPtr + 1;
                }

                // loop through the indices and write them to memory
                for (size_t k = 0; k < pair.second.size(); k++) {

                    // if compression level 3 skip the first two indices and cast the index
                    if constexpr (compressionLevel == 3) {
                        if (k == 0 || k == 1) {
                            continue;
                        }

                        // create a type of the correct width
                        switch (pair.second[0]) {
                        case 1:
                            *(uint8_t*)helpPtr = (uint8_t)pair.second[k];
                            helpPtr = (uint8_t*)helpPtr + 1;
                            break;
                        case 2:
                            *(uint16_t*)helpPtr = (uint16_t)pair.second[k];
                            helpPtr = (uint16_t*)helpPtr + 1;
                            break;
                        case 4:
                            *(uint32_t*)helpPtr = (uint32_t)pair.second[k];
                            helpPtr = (uint32_t*)helpPtr + 1;
                            break;
                        case 8:
                            *(uint64_t*)helpPtr = (uint64_t)pair.second[k];
                            helpPtr = (uint64_t*)helpPtr + 1;
                            break;
                        }
                    }
                    else {
                        // else just write the index

                        *(indexT*)helpPtr = (indexT)pair.second[k];
                        helpPtr = (indexT*)helpPtr + 1;
                    }
                } // End of index loop

                // write the delimiter to memory

                // write the delimiter
                if constexpr (compressionLevel == 3) {
                    // write a delimiter of the correct width
                    switch (pair.second[0]) {
                    case 1:
                        *(uint8_t*)helpPtr = (uint8_t)DELIM;
                        helpPtr = (uint8_t*)helpPtr + 1;
                        break;
                    case 2:
                        *(uint16_t*)helpPtr = (uint16_t)DELIM;
                        helpPtr = (uint16_t*)helpPtr + 1;
                        break;
                    case 4:
                        *(uint32_t*)helpPtr = (uint32_t)DELIM;
                        helpPtr = (uint32_t*)helpPtr + 1;
                        break;
                    case 8:
                        *(uint64_t*)helpPtr = (uint64_t)DELIM;
                        helpPtr = (uint64_t*)helpPtr + 1;
                        break;
                    }
                }
                // Set a pointer to the end of the data
                endPointers[i] = helpPtr;

            } // End of dictionary loop

            calculateCompSize();

        } // end of column loop
    }

    // Method to get the byte width of a number
    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    uint8_t SparseMatrix<T, indexT, compressionLevel, columnMajor>::byteWidth(size_t size) {
        if (size <= ONE_BYTE_MAX) {
            return 1;
        }
        else if (size <= TWO_BYTE_MAX) {
            return 2;
        }
        else if (size <= FOUR_BYTE_MAX) {
            return 4;
        }
        else {
            return 8;
        }
    }

    // Encodes the value type of the matrix in a uint32_t
    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    void SparseMatrix<T, indexT, compressionLevel, columnMajor>::encodeValueType() {
        uint8_t byte0 = sizeof(T);
        uint8_t byte1 = std::is_floating_point<T>::value ? 1 : 0;
        uint8_t byte2 = std::is_signed_v<T> ? 1 : 0;
        uint8_t byte3 = columnMajor ? 1 : 0;

        val_t = (byte3 << 24) | (byte2 << 16) | (byte1 << 8) | byte0;
    }

    // Checks if the value type is correct for the matrix
    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    void SparseMatrix<T, indexT, compressionLevel, columnMajor>::checkValueType() {
        uint8_t byte0 = val_t & 0xFF;
        uint8_t byte1 = (val_t >> 8) & 0xFF;
        uint8_t byte2 = (val_t >> 16) & 0xFF;
        uint8_t byte3 = (val_t >> 24) & 0xFF;

        assert(byte0 == sizeof(T) && "Value type size does not match");

        assert(byte1 == std::is_floating_point_v<T> && "Value type is not floating point");

        assert(byte2 == std::is_signed_v<T> && "Value type is not signed");

        assert(byte3 == columnMajor && "Major direction does not match");
    }

    // performs some simple user checks on the matrices metadata
    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    void SparseMatrix<T, indexT, compressionLevel, columnMajor>::userChecks() {

        assert((innerDim > 1 || outerDim > 1 || nnz > 1) && "The matrix must have at least one row, column, and nonzero value");

        assert(std::is_floating_point<indexT>::value == false && "The index type must be a non-floating point type");

        assert((compressionLevel == 2 || compressionLevel == 3) && "The compression level must be either 2, or 3");

        assert((std::is_arithmetic<T>::value && std::is_arithmetic<indexT>::value) && "The value and index types must be numeric types");

        assert((std::is_same<indexT, bool>::value == false) && "The index type must not be bool");

        assert((innerDim < std::numeric_limits<indexT>::max() && outerDim < std::numeric_limits<indexT>::max()) && "The number of rows and columns must be less than the maximum value of the index type");

        checkValueType();
    }

    // Calculates the current byte size of the matrix in memory
    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    void SparseMatrix<T, indexT, compressionLevel, columnMajor>::calculateCompSize() {

        // set compSize to zero
        compSize = 0;

        // add the size of the metadata
        compSize += META_DATA_SIZE;

        // add the size of the data pointers
        compSize += (sizeof(void*) * outerDim) * 2;

        // add the size of the data itself
        for (uint32_t i = 0; i < outerDim; i++) {
            if (data[i] != nullptr && this->getVectorSize(i) != 0 && data[i] != NULL) {
                compSize += *((uint8_t**)endPointers + i) - *((uint8_t**)data + i);
            }
        }

        // if performance vectors are on add them to the compression size
        if constexpr (compressionLevel == 2) {
            compSize += (sizeof(T*) * outerDim);
            compSize += (sizeof(indexT*) * outerDim);

            compSize += (sizeof(indexT) * outerDim);

            for (uint32_t i = 0; i < outerDim; i++) {
                compSize += (sizeof(T) * valueArraySize[i]);
                compSize += (sizeof(indexT) * valueArraySize[i]);
            }
        }
    }

}