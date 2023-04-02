#pragma once

#include <vector>
#include <map>
#include <iostream>

#define META_DATA_SIZE 24
#define NUM_META_DATA 6

#define ONE_BYTE_MAX 255
#define TWO_BYTE_MAX 65535
#define FOUR_BYTE_MAX 4294967295

// Debug flag for performance testing (set to true to be faster)
#define DEBUG false

namespace CSF {

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    template <typename T2, typename indexT2>
    void SparseMatrix<T, indexT, compressionLevel, columnMajor>::compress(T2* vals, indexT2* innerIndices, indexT2* outerPtr) {

        // set the val_t and index_t
        val_t = encodeVal();
        index_t = sizeof(indexT);

        // malloc space for the meta data
        metadata = new uint32_t[NUM_META_DATA];

        // Set the meta data
        metadata[0] = compressionLevel;
        metadata[1] = innerDim;
        metadata[2] = outerDim;
        metadata[3] = nnz;
        metadata[4] = val_t;
        metadata[5] = index_t;

        // run the user checks
        if constexpr (DEBUG)
            userChecks();

        // malloc space for the data
        try {
            data = (void**)malloc(outerDim * sizeof(void*));
            endPointers = (void**)malloc(outerDim * sizeof(void*));
        }
        catch (std::bad_alloc& e) {
            std::cout << "Error: " << e.what() << std::endl;
            exit(1);
        }

        // loop through each column
        #pragma omp parallel for
        for (size_t i = 0; i < outerDim; i++)
        {
            // construct the dictionary

            // create a std::map that holds value as the key and a vector of indices as the value
            std::map<T2, std::vector<indexT2>> dict;

            // check if the column is empty
            if (outerPtr[i] == outerPtr[i + 1]) {

                // set the data and end pointers to null
                data[i] = nullptr;
                endPointers[i] = nullptr;

                continue;
            }

            for (indexT2 j = outerPtr[i]; j < outerPtr[i + 1]; j++) {

                // if the value is already in the dictionary
                if (dict.find(vals[j]) != dict.end()) {

                    // add the index to the vector
                    if constexpr (compressionLevel == 3) {

                        // positive delta encode
                        dict[vals[j]].push_back(innerIndices[j] - dict[vals[j]][1]);

                        // update the last index
                        dict[vals[j]][1] = innerIndices[j];

                        // update the max delta
                        if (dict[vals[j]][dict[vals[j]].size() - 1] > dict[vals[j]][0]) {

                            dict[vals[j]][0] = dict[vals[j]][dict[vals[j]].size() - 1];
                        }
                    }
                    else {
                        dict[vals[j]].push_back(innerIndices[j]);
                    }
                }
                else {

                    // create a new vector with the index
                    dict[vals[j]] = std::vector<indexT2>{ innerIndices[j] };

                    if constexpr (compressionLevel == 3) {

                        dict[vals[j]].push_back(innerIndices[j]);
                        dict[vals[j]].push_back(innerIndices[j]);
                    }
                }

            } // end val loop

            size_t outerByteSize = 0;

            // malloc space for the column
            if constexpr (compressionLevel == 3) {
                for (auto& pair : dict) {
                    pair.second[0] = byteWidth(pair.second[0]);
                    outerByteSize += sizeof(T) + 1 + (pair.second[0] * (pair.second.size() - 2)) + pair.second[0];
                }
            }
            else {
                // loop through the dictionary and calculate the size of the column
                for (auto& pair : dict) {
                    outerByteSize += sizeof(T) + 1 + (sizeof(indexT) * pair.second.size()) + sizeof(indexT);
                }
            }

            try {
                data[i] = malloc(outerByteSize);
            }
            catch (std::bad_alloc& e) {
                std::cout << "Error: " << e.what() << std::endl;
                exit(1);
            }

            //! print out the dictionary
            // for (auto &pair : dict) {
            //     std::cout << pair.first << ": ";
            //     for (indexT k = 0; k < pair.second.size(); k++) {
            //         std::cout << pair.second[k] << " ";
            //     }
            //     std::cout << std::endl;
            // }

            void* helpPtr = data[i];

            // loop through the dictionary and write the data to the column
            for (auto& pair : dict) {

                // write the value
                *(T*)helpPtr = (T)pair.first;
                helpPtr = (T*)helpPtr + 1;

                // write the index width
                if constexpr (compressionLevel == 3) {
                    *(uint8_t*)helpPtr = (uint8_t)pair.second[0];
                    helpPtr = (uint8_t*)helpPtr + 1;
                }
                else {
                    *(uint8_t*)helpPtr = sizeof(indexT);
                    helpPtr = (uint8_t*)helpPtr + 1;
                }

                // write the indices
                for (size_t k = 0; k < pair.second.size(); k++) {
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
                        *(indexT*)helpPtr = (indexT)pair.second[k];
                        helpPtr = (indexT*)helpPtr + 1;
                    }
                }

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
                else {
                    *(indexT*)helpPtr = (indexT)DELIM;
                    helpPtr = (indexT*)helpPtr + 1;
                }

                // set the end ptr
                endPointers[i] = helpPtr;

            } // end dict loop

        } // end outer loop

        compSize += META_DATA_SIZE + (sizeof(void*) * outerDim) * 2;

        // add up the size of each col and add it to compSize
        for (size_t i = 0; i < outerDim; i++) {
            compSize += (size_t)endPointers[i] - (size_t)data[i];
        }

    } // end compress

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

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    void SparseMatrix<T, indexT, compressionLevel, columnMajor>::write(const char* filename) {
        // open the file
        FILE* fp = fopen(filename, "wb");

        // write the metadata
        fwrite(metadata, 1, sizeof(uint32_t) * NUM_META_DATA, fp);

        // write the distance between the end and start pointers
        for (uint32_t i = 0; i < outerDim; i++)
        {
            size_t size = (char *)endPointers[i] - (char *)data[i];
            fwrite(&size, 1, sizeof(size_t), fp);
        }

        // int test = 0;
        // fwrite(data[test], 1, (char *)endPointers[test] - (char *)data[test], fp);

        // write each column
        for (uint32_t i = 0; i < outerDim; i++)
        {
            fwrite(data[i], 1, (char *)endPointers[i] - (char *)data[i], fp);
        }

        // close the file
        fclose(fp);
    }

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    uint32_t SparseMatrix<T, indexT, compressionLevel, columnMajor>::encodeVal() {
        uint8_t byte0 = sizeof(T);
        uint8_t byte1 = std::is_floating_point<T>::value ? 1 : 0;
        uint8_t byte2 = std::is_signed_v<T> ? 1 : 0;
        uint8_t byte3 = 0;

        return (byte3 << 24) | (byte2 << 16) | (byte1 << 8) | byte0;
    }

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    void SparseMatrix<T, indexT, compressionLevel, columnMajor>::checkVal() {
        uint8_t byte0 = val_t & 0xFF;
        uint8_t byte1 = (val_t >> 8) & 0xFF;
        uint8_t byte2 = (val_t >> 16) & 0xFF;
        // uint8_t byte3 = (val_t >> 24) & 0xFF;


        if (byte0 != sizeof(T))
        {
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

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    void SparseMatrix<T, indexT, compressionLevel, columnMajor>::userChecks() {
        // throw an error if the matrix has less than one rows or columns or nonzero values
        if (innerDim < 1 || outerDim < 1 || nnz < 1)
            throw std::invalid_argument("The matrix must have at least one row, column, and nonzero value");

        // check that indexT is not floating point
        if (std::is_floating_point<indexT>::value)
            throw std::invalid_argument("The index type must be a non-floating point type");

        // check the compression level is either 1, 2, or 3
        if (compressionLevel < 1 || compressionLevel > 3)
            throw std::invalid_argument("The compression level must be either 1, 2, or 3");

        // check that T and indexT are numeric types
        if (!std::is_arithmetic<T>::value || !std::is_arithmetic<indexT>::value)
            throw std::invalid_argument("The value and index types must be numeric types");

        // check that the index type is not a bool
        if (std::is_same<indexT, bool>::value)
            throw std::invalid_argument("The value and index types must not be bool");

        // check that the row and col types can hold the number of rows and columns
        if (innerDim > std::numeric_limits<indexT>::max() || outerDim > std::numeric_limits<indexT>::max())
            throw std::invalid_argument("The number of rows and columns must be less than the maximum value of the index type");

        checkVal();
    }

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    void* SparseMatrix<T, indexT, compressionLevel, columnMajor>::getVecPointer(uint32_t vec) { return data[vec]; }

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    size_t SparseMatrix<T, indexT, compressionLevel, columnMajor>::getVecSize(uint32_t vec) { return (char*)endPointers[vec] - (char*)data[vec]; }

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    uint32_t SparseMatrix<T, indexT, compressionLevel, columnMajor>::innerSize() { return innerDim; }

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    uint32_t SparseMatrix<T, indexT, compressionLevel, columnMajor>::outerSize() { return outerDim; }

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    uint32_t SparseMatrix<T, indexT, compressionLevel, columnMajor>::rows() { return numRows; }

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    uint32_t SparseMatrix<T, indexT, compressionLevel, columnMajor>::cols() { return numCols; }

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    uint32_t SparseMatrix<T, indexT, compressionLevel, columnMajor>::nonZeros() { return nnz; }

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    size_t SparseMatrix<T, indexT, compressionLevel, columnMajor>::compressionSize() { return compSize; }

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    typename SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector SparseMatrix<T, indexT, compressionLevel, columnMajor>::getVector(uint32_t vec) {
        // return a CSF vector
        CSF::SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector newVector(*this, vec);

        return newVector;
    }

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    void SparseMatrix<T, indexT, compressionLevel, columnMajor>::operator * (T scalar) {
        ;

        for (uint32_t i = 0; i < this->outerDim; ++i) {
            for (typename SparseMatrix<T, indexT, compressionLevel>::InnerIterator it(*this, i); it; ++it) {
                if (it.isNewRun()) {
                    it.coeff(it.value() * scalar);
                }
            }
        }
        // return mat;
    }

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    typename CSF::SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector SparseMatrix<T, indexT, compressionLevel, columnMajor>::operator*(SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector& vec) {
        // check that the vector is the correct size
        if (vec.length() != outerDim)
            throw std::invalid_argument("The vector must be the same size as the number of columns in the matrix!");

        Eigen::SparseMatrix<T> eigenTemp(outerDim, 1);
        eigenTemp.reserve(outerDim);

        // iterate over the vector and multiply the corresponding row of the matrix by the vecIter value
        for (typename SparseMatrix<T, indexT, compressionLevel>::InnerIterator vecIter(vec); vecIter; ++vecIter) {
            for (typename SparseMatrix<T, indexT, compressionLevel>::InnerIterator matIter(*this, vecIter.getIndex()); matIter; ++matIter) {
                eigenTemp.coeffRef(vecIter.row(), 0) += matIter.value() * vecIter.value();
            }
        }
        eigenTemp.makeCompressed();
        //TODO: This is unnecessary overhead
        return SparseMatrix<T, indexT, compressionLevel, columnMajor>(eigenTemp).getVector(0);
    }


    /**
     * @brief Matrix x Matrix multiplication operator
     *
     * @tparam T
     * @tparam indexT
     * @tparam compressionLevel
     * @tparam columnMajor
     * @param mat
     * @return SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector
     */

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    SparseMatrix<T, indexT, compressionLevel, columnMajor> SparseMatrix<T, indexT, compressionLevel, columnMajor>::operator*(SparseMatrix<T, indexT, compressionLevel, columnMajor>& mat) {
        // check that the matrix is the correct size
        if (mat.outerSize() != innerDim)
            throw std::invalid_argument("The matrix's outer dimension must be the same as the inner dimension of the matrix");

        SparseMatrix<T, indexT, compressionLevel, columnMajor> newMatrix;

        // iterate over the vector and multiply the corresponding vector of the parameter matrix "mat"
        for (uint32_t i = 0; i < mat.outerSize(); ++i) {
            SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector newVector(mat, i);
            SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector tempVector(*this * newVector);
            newMatrix.append(tempVector);
        }

        return newMatrix;
    }

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    void SparseMatrix<T, indexT, compressionLevel, columnMajor>::append(typename CSF::SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector& vec) {
        // check if the matrix is empty
        if (compSize == 0 && nnz == 0 && numCols == 0 && numRows == 0) [[unlikely]] {

            // if it is the matrix is empty and we need to construct it
            if (columnMajor) {
                numRows = vec.length();
                numCols = 1;
                innerDim = numRows;
                outerDim = numCols;
            }
            else {
                numRows = 1;
                numCols = vec.length();
                innerDim = numCols;
                outerDim = numRows;
            }

            nnz = vec.nonZeros();
            compSize = vec.byteSize() + sizeof(void*) * 2;

            val_t = encodeVal();
            index_t = sizeof(indexT);

            // malloc the data
            try {
                data = (void**)malloc(sizeof(void*));
                endPointers = (void**)malloc(sizeof(void*));
            }
            catch (std::bad_alloc& e) {
                throw std::bad_alloc();
            }

            // malloc the vector
            try {
                // if vector is empty set the data to null
                if (vec.begin() == vec.end()) {
                    data[0] = nullptr;
                    endPointers[0] = nullptr;
                }
                else {
                    data[0] = malloc(vec.byteSize());
                    endPointers[0] = (char*)data[0] + vec.byteSize();
                }
            }
            catch (std::bad_alloc& e) {
                throw std::bad_alloc();
            }

            // copy the vector into the matrix
            // if the vector is not empty
            if (vec.begin() != vec.end())
                memcpy(data[0], vec.begin(), vec.byteSize());

            metadata = new uint32_t[NUM_META_DATA];

            // Set the meta data
            metadata[0] = compressionLevel;
            metadata[1] = innerDim;
            metadata[2] = outerDim;
            metadata[3] = nnz;
            metadata[4] = val_t;
            metadata[5] = index_t;

            compSize += sizeof(uint32_t) * NUM_META_DATA;

            // run the user checks
            if constexpr (DEBUG)
                userChecks();
        }
        else {

            // check if the vector is empty, if so change the implementation details
            if (vec.begin() == vec.end()) [[unlikely]] {

                if (columnMajor) {
                    numCols++;
                }
                else {
                    numRows++;
                }
                outerDim++;

                // realloc the data to be one larger
                try {
                    data = (void**)realloc(data, outerDim * sizeof(void*));
                    endPointers = (void**)realloc(endPointers, outerDim * sizeof(void*));
                }
                catch (std::bad_alloc& e) {
                    throw std::bad_alloc();
                }

                // set the new vector to nullptr
                data[outerDim - 1] = nullptr;
                endPointers[outerDim - 1] = nullptr;

                compSize += sizeof(void*) * 2;

                return;

            }
            else {

                // check that the vector is the correct size
                if ((vec.length() != innerDim))
                    throw std::invalid_argument("The vector must be the same size as the outer dimension of the matrix!");

                outerDim++;
                nnz += vec.nonZeros();
                if (columnMajor) {
                    numCols++;
                }
                else {
                    numRows++;
                }

                // realloc the data to be one larger
                try {
                    data = (void**)realloc(data, outerDim * sizeof(void*));
                    endPointers = (void**)realloc(endPointers, outerDim * sizeof(void*));
                }
                catch (std::bad_alloc& e) {
                    throw std::bad_alloc();
                }

                // malloc the new vector
                try {
                    data[outerDim - 1] = malloc(vec.byteSize());
                    endPointers[outerDim - 1] = (char*)data[outerDim - 1] + vec.byteSize();
                }
                catch (std::bad_alloc& e) {
                    throw std::bad_alloc();
                }

                // copy the vector into the new space
                memcpy(data[outerDim - 1], vec.begin(), vec.byteSize());

                // update the compression size
                compSize += vec.byteSize();
                compSize += sizeof(void*) * 2;
            }

        }
    }

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    CSF::SparseMatrix<T, indexT, compressionLevel, columnMajor> SparseMatrix<T, indexT, compressionLevel, columnMajor>::transpose() {
        // create an ordered map of unordered maps to store the values
        std::map<indexT, std::unordered_map<T, std::vector<indexT>>> transposedMap;

        // iterate over the matrix
        for (uint32_t i = 0; i < outerDim; ++i) {
            for (typename SparseMatrix<T, indexT, compressionLevel>::InnerIterator it(*this, i); it; ++it) {
                // add the value to the map
                if constexpr (columnMajor) {
                    transposedMap[it.row()][it.value()].push_back(it.col());
                }
                else {
                    transposedMap[it.col()][it.value()].push_back(it.row());
                }
            }
        }

        // if compression level is 3 positive delta encode the vectors of indices
        if (compressionLevel == 3) {
            for (auto& row : transposedMap) {
                for (auto& col : row.second) {
                    // sort the vector
                    // std::sort(col.second.begin(), col.second.end());
                    size_t max = col.second[0];
                    // delta encode the vector
                    for (uint32_t i = col.second.size() - 1; i > 0; --i) {
                        col.second[i] -= col.second[i - 1];
                        if (col.second[i] > max)
                            max = col.second[i];
                    }

                    max = byteWidth(max);
                    // append max to the vector
                    col.second.push_back(max);
                }
            }
        }

        // create a new matrix passing in transposedMap
        CSF::SparseMatrix<T, indexT, compressionLevel, columnMajor> transposedMatrix(transposedMap, numCols, numRows);

        return transposedMatrix;
    }


} // end namespace CSF