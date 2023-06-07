#pragma once

namespace CSF {

    //* Private Methods *//

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

        #ifdef CSF_DEBUG
        userChecks();
        #endif

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
        #ifdef CSF_PARALLEL
        #pragma omp parallel for
        #endif
        for (size_t i = 0; i < outerDim; i++) {
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
            // compSize += ((uint8_t *)endPointers)[i] - ((uint8_t *)data)[i];
            compSize += *((uint8_t**)endPointers + i) - *((uint8_t**)data + i);
            // compSize += (uint8_t *)endPointers[i] - (uint8_t *)data[i];

            // printf("Start: %p  End: %p  Difference: %d\n", *((uint8_t**)data + i), *((uint8_t**)endPointers + i), *((uint8_t**)endPointers + i) - *((uint8_t**)data + i));
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
    uint32_t SparseMatrix<T, indexT, compressionLevel, columnMajor>::encodeVal() {
        uint8_t byte0 = sizeof(T);
        uint8_t byte1 = std::is_floating_point<T>::value ? 1 : 0;
        uint8_t byte2 = std::is_signed_v<T> ? 1 : 0;
        uint8_t byte3 = columnMajor ? 1 : 0;

        return (byte3 << 24) | (byte2 << 16) | (byte1 << 8) | byte0;
    }

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    void SparseMatrix<T, indexT, compressionLevel, columnMajor>::checkVal() {
        uint8_t byte0 = val_t & 0xFF;
        uint8_t byte1 = (val_t >> 8) & 0xFF;
        uint8_t byte2 = (val_t >> 16) & 0xFF;
        uint8_t byte3 = (val_t >> 24) & 0xFF;


        assert(byte0 == sizeof(T) && "Value type size does not match");

        assert(byte1 == std::is_floating_point_v<T> && "Value type is not floating point");

        assert(byte2 == std::is_signed_v<T> && "Value type is not signed");

        assert(byte3 == columnMajor && "Major direction does not match");

    }

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    void SparseMatrix<T, indexT, compressionLevel, columnMajor>::userChecks() {
        
        assert((innerDim > 1 || outerDim > 1 || nnz > 1) && "The matrix must have at least one row, column, and nonzero value");

        assert(std::is_floating_point<indexT>::value == false && "The index type must be a non-floating point type");

        assert((compressionLevel == 1 || compressionLevel == 2 || compressionLevel == 3) && "The compression level must be either 1, 2, or 3");

        assert((std::is_arithmetic<T>::value && std::is_arithmetic<indexT>::value) && "The value and index types must be numeric types");

        assert((std::is_same<indexT, bool>::value == false) && "The index type must not be bool");

        assert((innerDim < std::numeric_limits<indexT>::max() && outerDim < std::numeric_limits<indexT>::max()) && "The number of rows and columns must be less than the maximum value of the index type");

        checkVal();
    }

    //* Getters *//

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    void* SparseMatrix<T, indexT, compressionLevel, columnMajor>::getVecPointer(uint32_t vec) const { return data[vec]; }

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    size_t SparseMatrix<T, indexT, compressionLevel, columnMajor>::getVecSize(uint32_t vec) const { return (char*)endPointers[vec] - (char*)data[vec]; }

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    uint32_t SparseMatrix<T, indexT, compressionLevel, columnMajor>::innerSize() const { return innerDim; }

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    uint32_t SparseMatrix<T, indexT, compressionLevel, columnMajor>::outerSize() const { return outerDim; }

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    uint32_t SparseMatrix<T, indexT, compressionLevel, columnMajor>::rows() const { return numRows; }

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    uint32_t SparseMatrix<T, indexT, compressionLevel, columnMajor>::cols() const { return numCols; }

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    uint32_t SparseMatrix<T, indexT, compressionLevel, columnMajor>::nonZeros() const { return nnz; }

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    size_t SparseMatrix<T, indexT, compressionLevel, columnMajor>::compressionSize() const { return compSize; }

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    typename SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector SparseMatrix<T, indexT, compressionLevel, columnMajor>::getVector(uint32_t vec) {
        
        #ifdef CSF_DEBUG
            // check if the vector is out of bounds
            assert((vec < outerDim && vec >= 0) && "Vector index out of bounds");
        #endif

        // return a CSF vector
        CSF::SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector newVector(*this, vec);

        return newVector;
    }

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    T SparseMatrix<T, indexT, compressionLevel, columnMajor>::coeff(uint32_t row, uint32_t col) {
        return (*this)(row, col);
    }

    //* Utility Methods *//

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    void SparseMatrix<T, indexT, compressionLevel, columnMajor>::write(const char* filename) {
        // open the file
        FILE* fp = fopen(filename, "wb");

        // write the metadata
        fwrite(metadata, 1, sizeof(uint32_t) * NUM_META_DATA, fp);

        // write the distance between the end and start pointers
        for (uint32_t i = 0; i < outerDim; i++) {
            uint64_t size = (char*)endPointers[i] - (char*)data[i];
            fwrite(&size, 1, sizeof(uint64_t), fp);
        }

        // int test = 0;
        // fwrite(data[test], 1, (char *)endPointers[test] - (char *)data[test], fp);

        // write each column
        for (uint32_t i = 0; i < outerDim; i++) {
            fwrite(data[i], 1, (char*)endPointers[i] - (char*)data[i], fp);
        }

        // close the file
        fclose(fp);
    }

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    void SparseMatrix<T, indexT, compressionLevel, columnMajor>::print() {
        std::cout << this << std::endl;
    }

    //* Operator Overloads *//

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    bool SparseMatrix<T, indexT, compressionLevel, columnMajor>::operator==(const SparseMatrix<T, indexT, compressionLevel, columnMajor>& other) {
        // check if the two matrices are equal

        // check if the rows, columns, and nnz are equal
        if (innerDim != other.innerDim || outerDim != other.outerDim || nnz != other.nnz)
            return false;

        // iterate through both matrices and check if the values are equal
        for (uint32_t i = 0; i < outerDim; i++) {

            // check if the column sizes are equal
            if (getVecSize(i) != other.getVecSize(i))
                return false;

            // check if the columns are equal
            if (memcmp(data[i], other.data[i], getVecSize(i)) != 0)
                return false;
        }

        return true;
    }

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    bool SparseMatrix<T, indexT, compressionLevel, columnMajor>::operator!=(const SparseMatrix<T, indexT, compressionLevel, columnMajor>& other) {
        return !(*this == other);
    }

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    typename SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector SparseMatrix<T, indexT, compressionLevel, columnMajor>::operator[](uint32_t vec) {

        #ifdef CSF_DEBUG
            // check if the vector is out of bounds
            assert((vec < outerDim && vec >= 0) && "Vector index out of bounds");
        #endif

        // return a CSF vector
        CSF::SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector newVector(*this, vec);

        return newVector;
    }

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    CSF::SparseMatrix<T, indexT, compressionLevel, columnMajor>& SparseMatrix<T, indexT, compressionLevel, columnMajor>::operator=(const CSF::SparseMatrix<T, indexT, compressionLevel, columnMajor>& other) {
        
        // check for an empty matrix
        if (other.data == nullptr) {
            // delete the old data
            for (uint32_t i = 0; i < outerDim; i++)
                free(data[i]);

            free(data);

            free(endPointers);

            delete[] metadata;

            // set the metadata to null
            metadata = nullptr;

            // set the data to null
            data = nullptr;

            endPointers = nullptr;

            // set the dimensions to 0
            outerDim = 0;
            innerDim = 0;
            numRows = 0;
            numCols = 0;
            nnz = 0;
            compSize = 0;

            // return the matrix
            return *this;
        }

        // check for self assignment
        if (this == &other)
            return *this;


        // delete the old data
        for (uint32_t i = 0; i < outerDim; i++)
            free(data[i]);

        free(data);

        free(endPointers);

        delete[] metadata;

        // allocate metadata
        metadata = new uint32_t[NUM_META_DATA];

        // copy the metadata
        memcpy(metadata, other.metadata, sizeof(uint32_t) * NUM_META_DATA);

        // allocate the data
        try {
            data = (void**)malloc(sizeof(void*) * outerDim);
            endPointers = (void**)malloc(sizeof(void*) * outerDim);
        }
        catch (std::bad_alloc& ba) {
            std::cerr << "bad_alloc caught: " << ba.what() << '\n';
        }

        // copy the data
        for (uint32_t i = 0; i < outerDim; i++) {
            try {
                data[i] = malloc(other.getVecSize(i));
            }
            catch (std::bad_alloc& ba) {
                std::cerr << "bad_alloc caught: " << ba.what() << '\n';
            }
            memcpy(data[i], other.data[i], other.getVecSize(i));
            endPointers[i] = (char*)data[i] + other.getVecSize(i);
        }

        // copy the pointers
        innerDim = other.innerDim;
        outerDim = other.outerDim;
        numRows = other.numRows;
        numCols = other.numCols;
        nnz = other.nnz;
        compSize = other.compSize;

        return *this;
    }

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    T SparseMatrix<T, indexT, compressionLevel, columnMajor>::operator()(uint32_t row, uint32_t col) {
        // check if the row and column are in bounds
        if (row >= numRows || col >= numCols)
            throw std::out_of_range("Row or column out of range");

        // check if the matrix is column major
        if (columnMajor) {
            // get the vector
            CSF::SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector vec = (*this)[col];

            // return the value
            return vec[row];
        }
        else {
            // get the vector
            CSF::SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector vec = (*this)[row];

            // return the value
            return vec[col];
        }
    }

    //* Conversion/Transformation Methods *//

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

            #ifdef CSF_DEBUG
            userChecks();
            #endif
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

                    // find the max value in the vector
                    size_t max = col.second[0];

                    // delta encode the vector
                    for (uint32_t i = col.second.size() - 1; i > 0; --i) {
                        col.second[i] -= col.second[i - 1];
                        if ((size_t)col.second[i] > max)
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

    // slice method that returns an array of vectors
    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    typename CSF::SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector* SparseMatrix<T, indexT, compressionLevel, columnMajor>::slice(uint32_t start, uint32_t end) {
        #ifdef CSF_DEBUG
            // check that the start and end are valid
            assert(start < outerDim && end <= outerDim && start < end && "Invalid start and end values!");
        #endif

        // create a new array of vectors
        CSF::SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector* vectors = new CSF::SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector[end - start];

        // iterate over the matrix
        #ifdef CSF_PARALLEL
        #pragma omp parallel for
        #endif
        for (uint32_t i = start; i < end; ++i) {
            // create a new vector
            CSF::SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector vec(*this, i);

            // add the vector to the array
            vectors[i - start] = vec;
        }

        return vectors;
    }

    // to eigen method
    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    Eigen::SparseMatrix<T, columnMajor ? Eigen::ColMajor : Eigen::RowMajor> SparseMatrix<T, indexT, compressionLevel, columnMajor>::toEigen() {

        #ifdef CSF_DEBUG
            // assert that the matrix is not empty
            assert(outerDim > 0 && "Cannot convert an empty matrix to an Eigen matrix!");
        #endif

        // create a new sparse matrix
        Eigen::SparseMatrix<T, columnMajor ? Eigen::ColMajor : Eigen::RowMajor> eigenMatrix(numRows, numCols);

        // iterate over the matrix
        for (uint32_t i = 0; i < outerDim; ++i) {
            for (typename SparseMatrix<T, indexT, compressionLevel>::InnerIterator it(*this, i); it; ++it) {
                // add the value to the matrix
                eigenMatrix.insert(it.row(), it.col()) = it.value();
            }
        }

        // finalize the matrix
        eigenMatrix.makeCompressed();

        // return the matrix
        return eigenMatrix;
    }

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    CSF::SparseMatrix<T, indexT, 1, columnMajor> SparseMatrix<T, indexT, compressionLevel, columnMajor>::toCSF1() {
        // make an eigen matrix
        Eigen::SparseMatrix<T, columnMajor ? Eigen::ColMajor : Eigen::RowMajor> eigenMatrix = *this.toEigen();

        // make a csf1 matrix
        CSF::SparseMatrix<T, indexT, 1, columnMajor> csf1Matrix(eigenMatrix);

        // return the matrix
        return csf1Matrix;
    }

    // template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    // std::ostream& operator<<(std::ostream &os, const CSF::SparseMatrix<T, indexT, compressionLevel, columnMajor> &mat) { //not working
    // // std::ostream& SparseMatrix<T, indexT, compressionLevel, columnMajor>::operator<<(std::ostream &os) {

    //     T matrix[mat.rows()][mat.cols()];

    //     for (int i = 0; i < mat.cols(); i++){
    //         for(typename CSF::SparseMatrix<T, indexT, compressionLevel, columnMajor>::InnerIterator it(mat, i); it; ++it){
    //             matrix[it.row()][it.col()] = it.value();
    //         }
    //     }

    //     for (int i = 0; i < mat.rows(); i++){
    //         for (int j = 0; j < mat.cols(); j++){
    //             os << matrix[i][j] << " ";
    //         }
    //         os << std::endl;
    //     }
    //     return os;
    // }

} // end namespace CSF