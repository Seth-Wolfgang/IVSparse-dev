/**
 * @file CSF_Constructors.hpp
 * @author Skyler Ruiter and Seth Wolfgang
 * @brief All the constructors for the CSF Sparse Matrix base class.
 * @version 0.1
 * @date 2023-06-23
 */

#pragma once

namespace CSF {

    // Destructor
    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    SparseMatrix<T, indexT, compressionLevel, columnMajor>::~SparseMatrix() {
        // delete the meta data
        if (metadata != nullptr) {
            delete [] metadata;
        }

        // free the data
        for (size_t i = 0; i < outerDim; i++) {
            if (data[i] != nullptr)
                free(data[i]);
        }

        // free data
        if (data != nullptr)
            free(data);

        // free the end pointers
        if (endPointers != nullptr)
            free(endPointers);

        if constexpr (compressionLevel == 2) {
            // if value array and counts are not null, free them
            if (valueArray != nullptr) {
                for (uint32_t i = 0; i < outerDim; i++) {
                    if (valueArray[i] != nullptr || valueArray[i] != NULL) {
                        free(valueArray[i]);
                    }
                }
                free(valueArray);
            }

            if (countsArray != nullptr) {
                for (uint32_t i = 0; i < outerDim; i++) {
                    if (countsArray[i] != nullptr) {
                        free(countsArray[i]);
                    }
                }
                free(countsArray);
            }

            free(valueArraySize);
        }
    }

    // Default Constructor
    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    SparseMatrix<T, indexT, compressionLevel, columnMajor>::SparseMatrix() {
        val_t = 0;
        index_t = 0;
    }

    // Eigen Constructor
    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    SparseMatrix<T, indexT, compressionLevel, columnMajor>::SparseMatrix(Eigen::SparseMatrix<T>& mat) {
        // check if the matrix is empty
        if (mat.nonZeros() == 0) {
            val_t = 0;
            index_t = 0;

            data = nullptr;
            endPointers = nullptr;
            metadata = nullptr;
            return;
        }

        // make sure the matrix is compressed
        mat.makeCompressed();

        // get the number of rows and columns
        numRows = mat.rows();
        numCols = mat.cols();

        outerDim = columnMajor ? numCols : numRows;
        innerDim = columnMajor ? numRows : numCols;

        // get the number of non-zero elements
        nnz = mat.nonZeros();

        // call the compression function
        compressCSC(mat.valuePtr(), mat.innerIndexPtr(), mat.outerIndexPtr());
    }

    // Eigen Row Major Constructor
    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    SparseMatrix<T, indexT, compressionLevel, columnMajor>::SparseMatrix(Eigen::SparseMatrix<T, Eigen::RowMajor> &mat) {
        // check if the matrix is empty
        if (mat.nonZeros() == 0) {
            val_t = 0;
            index_t = 0;

            data = nullptr;
            endPointers = nullptr;
            metadata = nullptr;
            return;
        }

        // make sure the matrix is compressed
        mat.makeCompressed();

        // get the number of rows and columns
        numRows = mat.rows();
        numCols = mat.cols();

        outerDim = numRows;
        innerDim = numCols;

        // get the number of non-zero elements
        nnz = mat.nonZeros();

        // call the compression function
        compressCSC(mat.valuePtr(), mat.innerIndexPtr(), mat.outerIndexPtr());
    }

    // Deep Copy Constructor
    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    SparseMatrix<T, indexT, compressionLevel, columnMajor>::SparseMatrix(const CSF::SparseMatrix<T, indexT, compressionLevel, columnMajor> &other) { *this = other; }

    // Conversion Constructor
    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    template <uint8_t otherCompressionLevel>
    SparseMatrix<T, indexT, compressionLevel, columnMajor>::SparseMatrix(CSF::SparseMatrix<T, indexT, otherCompressionLevel, columnMajor> &other) {
        // check if the matrix is empty
        if (other.nonZeros() == 0) {
            val_t = 0;
            index_t = 0;

            data = nullptr;
            endPointers = nullptr;
            metadata = nullptr;
            return;
        }

        // if already the right compression level
        if constexpr (otherCompressionLevel == compressionLevel) {
            *this = other;
            return;
        }

        // make a temporary matrix of the correct compression level
        CSF::SparseMatrix<T, indexT, compressionLevel, columnMajor> temp;

        // convert other to the right compression level
        if constexpr (otherCompressionLevel == 1) {
            if constexpr (compressionLevel == 2) {
                temp = other.toCSF2();
            } else {
                temp = other.toCSF3();
            }
        } else if constexpr (otherCompressionLevel == 2 && compressionLevel == 3) {
            temp = other.toCSF3();
        } else if constexpr (otherCompressionLevel == 3 && compressionLevel == 2) {
            temp = other.toCSF2();
        }

        // other should be the same compression level as this now
        *this = temp;

        // run the user checks
        #ifdef CSF_DEBUG
        userChecks();
        #endif
    }

    // Raw CSC Constructor
    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    template <typename T2, typename indexT2>
    SparseMatrix<T, indexT, compressionLevel, columnMajor>::SparseMatrix(T2* vals, indexT2* innerIndices, indexT2* outerPtr, uint32_t num_rows, uint32_t num_cols, uint32_t nnz) {

        // see if the matrix is empty
        if (nnz == 0) [[unlikely]] {
            val_t = 0;
            index_t = 0;

            data = nullptr;
            endPointers = nullptr;
            metadata = nullptr;

            return;
        }

            if (columnMajor) {
                innerDim = num_rows;
                outerDim = num_cols;
            }
            else {
                innerDim = num_cols;
                outerDim = num_rows;
            }

        numRows = num_rows;
        numCols = num_cols;

        this->nnz = nnz;

        compressCSC(vals, innerIndices, outerPtr);
    }

    // CSF Vector Constructor
    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    SparseMatrix<T, indexT, compressionLevel, columnMajor>::SparseMatrix(typename CSF::SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector& vec) {
        // if it is the matrix is empty and we need to construct it
        if (columnMajor) {
            numRows = vec.getLength();
            numCols = 1;
            innerDim = numRows;
            outerDim = numCols;
        }
        else {
            numRows = 1;
            numCols = vec.getLength();
            innerDim = numCols;
            outerDim = numRows;
        }

        // see if the vector is empty
        if (vec.nonZeros() == 0) [[unlikely]] {
            nnz = 0;
            compSize = 0;
            data = nullptr;
            endPointers = nullptr;
            metadata = nullptr;
            return;
        }

        nnz = vec.nonZeros();

        encodeValueType();
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

        // if the performance vectors are on add those too
        if constexpr (compressionLevel == 2) {
            valueArray = (T **)malloc(sizeof(T *));
            countsArray = (uint32_t **)malloc(sizeof(uint32_t *));
            valueArraySize = (uint32_t *)malloc(sizeof(uint32_t));

            valueArraySize[0] = vec.valueArraySize;
            valueArray[0] = (T *)malloc(vec.valueArraySize * sizeof(T));
            countsArray[0] = (uint32_t *)malloc(vec.valueArraySize * sizeof(uint32_t));

            memcpy(valueArray[0], vec.valueArray, vec.valueArraySize * sizeof(T));
            memcpy(countsArray[0], vec.countsArray, vec.valueArraySize * sizeof(uint32_t));
        }

        calculateCompSize();

        // run the user checks
        #ifdef CSF_DEBUG
        userChecks();
        #endif
    }

    // Array of Vectors Constructor
    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    SparseMatrix<T, indexT, compressionLevel, columnMajor>::SparseMatrix(std::vector<typename CSF::SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector> &vecs)
    {
        CSF::SparseMatrix<T, indexT, compressionLevel, columnMajor> temp(vecs[0]);

        for (size_t i = 1; i < vecs.size(); i++)
        {
            temp.append(vecs[i]);
        }

        *this = temp;

        // run the user checks
        #ifdef CSF_DEBUG
        userChecks();
        #endif

        calculateCompSize();
    }

    // File Constructor
    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    SparseMatrix<T, indexT, compressionLevel, columnMajor>::SparseMatrix(const char *filename)
    {
        FILE *fp = fopen(filename, "rb");

        if (fp == nullptr) { throw std::runtime_error("Error: Could not open file"); }

        // read the metadata
        metadata = new uint32_t[NUM_META_DATA];
        fread(metadata, sizeof(uint32_t), NUM_META_DATA, fp);

        // set the matrix info
        innerDim = metadata[1];
        outerDim = metadata[2];
        nnz = metadata[3];
        val_t = metadata[4];
        index_t = metadata[5];

        // if the compression level of the file is different than the compression level of the class
        if (metadata[0] != compressionLevel) {
            // throw an error
            throw std::runtime_error("Error: Compression level of file does not match compression level of class");
        }

        numRows = columnMajor ? innerDim : outerDim;
        numCols = columnMajor ? outerDim : innerDim;

        // allocate the memory
        try {
            data = (void **)malloc(outerDim * sizeof(void *));
            endPointers = (void **)malloc(outerDim * sizeof(void *));
        } catch (std::bad_alloc &e) {
            std::cerr << "Error: Could not allocate memory for CSF matrix" << std::endl;
            exit(1);
        }

        // if compression level 2 do the performance vectors
        if constexpr (compressionLevel == 2) {
            try {
                valueArray = (T **)malloc(outerDim * sizeof(T *));
                countsArray = (uint32_t **)malloc(outerDim * sizeof(uint32_t *));
                valueArraySize = (uint32_t *)malloc(outerDim * sizeof(uint32_t));
            } catch (std::bad_alloc &e) {
                std::cerr << "Error: Could not allocate memory for CSF matrix" << std::endl;
                exit(1);
            }

            // set all the arrays to nullptr
            for (size_t i = 0; i < outerDim; i++) {
                valueArray[i] = nullptr;
                countsArray[i] = nullptr;
            }

            // read the performance vectors size
            for (size_t i = 0; i < outerDim; i++) {
                fread(&valueArraySize[i], sizeof(uint32_t), 1, fp);
            }

            // read in the values vector
            for (size_t i = 0; i < outerDim; i++) {
                if (valueArraySize[i] == 0) {
                    continue;
                }

                try {
                    valueArray[i] = (T *)malloc(valueArraySize[i] * sizeof(T));
                } catch (std::bad_alloc &e) {
                    std::cerr << "Error: Could not allocate memory for CSF matrix" << std::endl;
                    exit(1);
                }

                fread(valueArray[i], sizeof(T), valueArraySize[i], fp);
            }

            // read in the counts vector
            for (size_t i = 0; i < outerDim; i++) {
                if (valueArraySize[i] == 0) { continue; }

                try {
                    countsArray[i] = (uint32_t *)malloc(valueArraySize[i] * sizeof(uint32_t));
                } catch (std::bad_alloc &e) {
                    std::cerr << "Error: Could not allocate memory for CSF matrix" << std::endl;
                    exit(1);
                }
                fread(countsArray[i], sizeof(uint32_t), valueArraySize[i], fp);
            }

            // read the data
            for (size_t i = 0; i < outerDim; i++) {
                uint64_t size = 0;

                if (valueArraySize[i] == 0) { continue; }

                // calculate the size of the column data
                for (size_t j = 0; j < valueArraySize[i]; j++) {
                    size += (sizeof(indexT) * countsArray[i][j]);
                }

                // malloc the column
                try {
                    data[i] = malloc(size);
                    endPointers[i] = (char *)data[i] + size;
                } catch (std::bad_alloc &e) {
                    std::cerr << "Error: Could not allocate memory for CSF matrix" << std::endl;
                    exit(1);
                }
                fread(data[i], 1, (uint8_t *)endPointers[i] - (uint8_t *)data[i], fp);
            }

            // close the file
            fclose(fp);

            // calculate the compresssion size
            calculateCompSize();

            // run the user checks
            #ifdef CSF_DEBUG
            userChecks();
            #endif

            return;
        }

        // get the vector sizes and allocate memory
        for (size_t i = 0; i < outerDim; i++) {
            // get the size of the column
            uint64_t size;
            fread(&size, sizeof(uint64_t), 1, fp);

            // malloc the column
            try {
                data[i] = malloc(size);
                endPointers[i] = (char *)data[i] + size;
            } catch (std::bad_alloc &e) {
                throw std::bad_alloc();
            }
        }

        // read the data
        for (size_t i = 0; i < outerDim; i++) {
            fread(data[i], 1, (uint8_t *)endPointers[i] - (uint8_t *)data[i], fp);
        }

        // close the file
        fclose(fp);

        // calculate the compresssion size
        calculateCompSize();

        // run the user checks
        #ifdef CSF_DEBUG
        userChecks();
        #endif
    }

    // Private Tranpose Constructor
    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    SparseMatrix<T, indexT, compressionLevel, columnMajor>::SparseMatrix(std::unordered_map<T, std::vector<indexT>> maps [], uint32_t num_rows, uint32_t num_cols) {

        if constexpr (compressionLevel == 2) {
            valueArray = (T**)calloc(sizeof(T*), num_rows);
            countsArray = (indexT**)calloc(sizeof(indexT*), num_rows);
            valueArraySize = (indexT*)malloc(sizeof(indexT) * num_rows);
        }
        

        // set class variables
        if constexpr (columnMajor) {
            innerDim = num_cols;
            outerDim = num_rows;
        }
        else {
            innerDim = num_rows;
            outerDim = num_cols;
        }

        numRows = num_cols;
        numCols = num_rows;
        encodeValueType();
        index_t = sizeof(indexT);

        // allocate memory for the data
        try {
            data = (void**)malloc(outerDim * sizeof(void*));
            endPointers = (void**)malloc(outerDim * sizeof(void*));
        }
        catch (const std::exception& e) {
            std::cerr << e.what() << '\n';
        }

        // set all data and endpointers to the nullptr
        for (size_t i = 0; i < outerDim; i++) {
            data[i] = nullptr;
            endPointers[i] = nullptr;
        }

        //* logic here

        // loop through the array
        #ifdef CSF_PARALLEL
        #pragma omp parallel for
        #endif
        for (size_t i = 0; i < outerDim; i++) {

            // check if the column is empty
            if (maps[i].empty()) [[unlikely]] { continue; }

            size_t byteSize = 0;
            if constexpr (compressionLevel == 3) {
                // loop through the vectors of the map
                for (auto& val : maps[i]) {
                    // add the size of the vector to the byteSize
                    byteSize += sizeof(T) + 1 + (val.second[val.second.size() - 1] * (val.second.size() - 1) + val.second[val.second.size() - 1]);
                }
            }
            else {
                valueArray[i] = (T*)malloc(sizeof(T) * maps[i].size());                
                countsArray[i] = (indexT*)malloc(sizeof(indexT) * maps[i].size());
                valueArraySize[i] = 0;
                // loop through the vectors of the map
                for (auto& val : maps[i]) {
                    // add the size of the vector to the byteSize
                    byteSize += sizeof(T) + (sizeof(indexT) * val.second.size()) + sizeof(indexT);
                }
            }

            // allocate memory for the vector
            try {
                data[i] = malloc(byteSize);
            }
            catch (const std::exception& e) {
                std::cerr << e.what() << '\n';
            }

            // set the end pointer
            endPointers[i] = (char*)data[i] + byteSize;

            // compressCSC the column
            void* helpPtr = data[i];

            for (auto& val : maps[i]) {

                if constexpr (compressionLevel == 3) {
                    nnz += val.second.size() - 1;

                    // set the value
                    *(T *)helpPtr = val.first;
                    helpPtr = (char *)helpPtr + sizeof(T);
                    *(uint8_t *)helpPtr = (uint8_t)val.second[val.second.size() - 1];
                    helpPtr = (uint8_t *)helpPtr + 1;
                }
                else {
                    nnz += val.second.size();
                    valueArraySize[i]++;
                    countsArray[i][valueArraySize[i] - 1] = val.second.size();
                    valueArray[i][valueArraySize[i] - 1] = val.first;
                }

                // write the indices
                for (size_t k = 0; k < val.second.size(); k++) {

                    if constexpr (compressionLevel == 3) {
                        if (k == val.second.size() - 1)
                            break;

                        switch (val.second[val.second.size() - 1]) {
                        case 1:
                            *(uint8_t*)helpPtr = (uint8_t)val.second[k];
                            helpPtr = (uint8_t*)helpPtr + 1;
                            break;
                        case 2:
                            *(uint16_t*)helpPtr = (uint16_t)val.second[k];
                            helpPtr = (uint16_t*)helpPtr + 1;
                            break;
                        case 4:
                            *(uint32_t*)helpPtr = (uint32_t)val.second[k];
                            helpPtr = (uint32_t*)helpPtr + 1;
                            break;
                        case 8:
                            *(uint64_t*)helpPtr = (uint64_t)val.second[k];
                            helpPtr = (uint64_t*)helpPtr + 1;
                            break;
                        }
                    }
                    else {
                        *(indexT*)helpPtr = val.second[k];
                        helpPtr = (indexT*)helpPtr + 1;
                        // countsArray[i][valueArraySize[i] - 1]++;
                    }
                }

                // write the delimiter
                if constexpr (compressionLevel == 3) {
                    // write a delimiter of the correct width
                    switch (val.second[val.second.size() - 1]) {
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
            }
        }

        //* end logic

        metadata = new uint32_t[NUM_META_DATA];

        // Set the meta data
        metadata[0] = compressionLevel;
        metadata[1] = innerDim;
        metadata[2] = outerDim;
        metadata[3] = nnz;
        metadata[4] = val_t;
        metadata[5] = index_t;

        // run the user checks
        #ifdef CSF_DEBUG
        userChecks();
        #endif
        calculateCompSize();
    }

}