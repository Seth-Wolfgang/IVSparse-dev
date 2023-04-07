#pragma once

namespace CSF {

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    SparseMatrix<T, indexT, compressionLevel, columnMajor>::SparseMatrix() {}

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    SparseMatrix<T, indexT, compressionLevel, columnMajor>::SparseMatrix(Eigen::SparseMatrix<T>& mat) {

        mat.makeCompressed();

        // Set the number of rows, columns and non-zero elements
        if (columnMajor) {
            innerDim = mat.rows();
            outerDim = mat.cols();
        } else {
            innerDim = mat.cols();
            outerDim = mat.rows();
        }

        numRows = mat.rows();
        numCols = mat.cols();

        nnz = mat.nonZeros();

        compress(mat.valuePtr(), mat.innerIndexPtr(), mat.outerIndexPtr());
    }

    // TODO: Test the array of vectors constructor
    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    SparseMatrix<T, indexT, compressionLevel, columnMajor>::SparseMatrix(CSF::SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector vec[], size_t size) {
        
        // ensure the vectors are all the same length
        for (size_t i = 1; i < size; i++) {
            if (vec[i].length() != vec[0].length()) {
                std::cerr << "Error: Vectors are not all the same length" << std::endl;
                exit(1);
            }
        }

        if (columnMajor) {
            outerDim = size;
            innerDim = vec[0].length();
            numCols = size;
            numRows = vec[0].length();
        }
        else {
            outerDim = vec[0].length();
            innerDim = size;
            numCols = vec[0].length();
            numRows = size;
        }

        //allocate memory for data
        try {
            data = (void**)malloc(outerDim * sizeof(void*));
            endPointers = (void**)malloc(outerDim * sizeof(void*));
        }
        catch (const std::exception& e) {
            std::cerr << e.what() << '\n';
        }

        for (size_t i = 0; i < outerDim; i++) {
            try {
                data[i] = malloc(vec[i].byteSize());
            }
            catch (const std::exception& e) {
                std::cerr << e.what() << '\n';
            }
            memcpy(data[i], vec[i].data(), vec[i].byteSize());
            endPointers[i] = (char*)data[i] + vec[i].byteSize();

            nnz += vec[i].nonZeros();
            compSize += vec[i].byteSize();
        }

        //  set the val_t and index_t
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

        compSize += NUM_META_DATA * sizeof(uint32_t) + (outerDim * sizeof(void*) * 2);

        // run the user checks
        if constexpr (DEBUG)
            userChecks();
    }

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    SparseMatrix<T, indexT, compressionLevel, columnMajor>::SparseMatrix(Eigen::SparseMatrix<T, Eigen::RowMajor>& mat) {

        mat.makeCompressed();

        // Set the number of rows, columns and non-zero elements
        innerDim = mat.cols();
        outerDim = mat.rows();

        numRows = mat.rows();
        numCols = mat.cols();

        nnz = mat.nonZeros();

        compress(mat.valuePtr(), mat.innerIndexPtr(), mat.outerIndexPtr());
    }

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    template <typename T2, typename indexT2>
    SparseMatrix<T, indexT, compressionLevel, columnMajor>::SparseMatrix(T2 *vals, indexT2 *innerIndices, indexT2 *outerPtr, uint32_t num_rows, uint32_t num_cols, uint32_t nnz)
    {
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

        compress(vals, innerIndices, outerPtr);
    }

    //Deep Copy Constructor
    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    SparseMatrix<T, indexT, compressionLevel, columnMajor>::SparseMatrix(const CSF::SparseMatrix<T, indexT, compressionLevel, columnMajor>& mat) {
        // Set the number of rows, columns and non-zero elements
        innerDim = mat.innerSize();
        outerDim = mat.outerSize();

        numRows = mat.rows();
        numCols = mat.cols();

        nnz = mat.nonZeros();

        compSize = mat.compressionSize();

        try {
            data = (void**)malloc(outerDim * sizeof(void*));
            endPointers = (void**)malloc(outerDim * sizeof(void*));
        }
        catch (const std::exception& e) {
            std::cerr << e.what() << '\n';
        }

        #pragma omp parallel for
        for (size_t i = 0; i < outerDim; i++) {
            try {
                data[i] = malloc(mat.getVecSize(i));
            }
            catch (const std::exception& e) {
                std::cerr << e.what() << '\n';
            }
            memcpy(data[i], mat.getVecPointer(i), mat.getVecSize(i));
            endPointers[i] = (char*)data[i] + mat.getVecSize(i);
        }

        //allocate memory for metadata
        metadata = new uint32_t[NUM_META_DATA];
        memcpy(metadata, mat.metadata, NUM_META_DATA * sizeof(uint32_t));

        index_t = mat.index_t;

        encodeVal();
    }

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    SparseMatrix<T, indexT, compressionLevel, columnMajor>::SparseMatrix(std::map<indexT, std::unordered_map<T, std::vector<indexT>>>& map, uint32_t num_rows, uint32_t num_cols) {
        // set class variables
        if constexpr (columnMajor) {
            innerDim = num_rows;
            outerDim = num_cols;
        }
        else {
            innerDim = num_cols;
            outerDim = num_rows;
        }

        numRows = num_rows;
        numCols = num_cols;

        val_t = encodeVal();
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

        // loop through the map
        for (auto &col : map) {

            // loop through col and find the byte size
            size_t byteSize = 0;
            if constexpr (compressionLevel == 3) {
                for (auto &val : col.second) {
                    byteSize += sizeof(T) + 1 + (val.second[val.second.size() - 1] * (val.second.size() - 1) + val.second[val.second.size() - 1]);
                }
            } else {
                for (auto &val : col.second) {
                    byteSize += sizeof(T) + 1 + (sizeof(indexT) * val.second.size()) + sizeof(indexT);
                }
            }

            // allocate memory for the vector
            try {
                data[col.first] = malloc(byteSize);
            }
            catch (const std::exception& e) {
                std::cerr << e.what() << '\n';
            }

            // set the end pointer
            endPointers[col.first] = (char*)data[col.first] + byteSize;

            // compress the column
            void *helpPtr = data[col.first];

            for (auto &val : col.second) {
                if constexpr (compressionLevel == 3)
                    nnz += val.second.size() - 1;
                else
                    nnz += val.second.size();

                // write the value
                *(T*)helpPtr = val.first;
                helpPtr = (char*)helpPtr + sizeof(T);

                // write the index width
                if constexpr (compressionLevel == 3) {
                    *(uint8_t *)helpPtr = (uint8_t)val.second[val.second.size() - 1];
                    helpPtr = (uint8_t *)helpPtr + 1;
                } else {
                    *(uint8_t *)helpPtr = (uint8_t)sizeof(indexT);
                    helpPtr = (uint8_t *)helpPtr + 1;
                }

                // write the indices
                for (size_t k = 0; k < val.second.size(); k++)
                {

                    if constexpr (compressionLevel == 3)
                    {
                        if (k == val.second.size() - 1)
                            break;

                        switch (val.second[val.second.size() - 1])
                        {
                        case 1:
                            *(uint8_t *)helpPtr = (uint8_t)val.second[k];
                            helpPtr = (uint8_t *)helpPtr + 1;
                            break;
                        case 2:
                            *(uint16_t *)helpPtr = (uint16_t)val.second[k];
                            helpPtr = (uint16_t *)helpPtr + 1;
                            break;
                        case 4:
                            *(uint32_t *)helpPtr = (uint32_t)val.second[k];
                            helpPtr = (uint32_t *)helpPtr + 1;
                            break;
                        case 8:
                            *(uint64_t *)helpPtr = (uint64_t)val.second[k];
                            helpPtr = (uint64_t *)helpPtr + 1;
                            break;
                        }
                    }
                    else
                    {
                        *(indexT *)helpPtr = val.second[k];
                        helpPtr = (indexT *)helpPtr + 1;
                    }
                }

                // write the delimiter
                if constexpr (compressionLevel == 3)
                {
                    // write a delimiter of the correct width
                    switch (val.second[val.second.size() - 1])
                    {
                    case 1:
                        *(uint8_t *)helpPtr = (uint8_t)DELIM;
                        helpPtr = (uint8_t *)helpPtr + 1;
                        break;
                    case 2:
                        *(uint16_t *)helpPtr = (uint16_t)DELIM;
                        helpPtr = (uint16_t *)helpPtr + 1;
                        break;
                    case 4:
                        *(uint32_t *)helpPtr = (uint32_t)DELIM;
                        helpPtr = (uint32_t *)helpPtr + 1;
                        break;
                    case 8:
                        *(uint64_t *)helpPtr = (uint64_t)DELIM;
                        helpPtr = (uint64_t *)helpPtr + 1;
                        break;
                    }
                }
                else
                {
                    *(indexT *)helpPtr = (indexT)DELIM;
                    helpPtr = (indexT *)helpPtr + 1;
                }
            }
        }

        compSize += META_DATA_SIZE + (sizeof(void *) * outerDim) * 2;

        // add up the size of each col and add it to compSize
        for (size_t i = 0; i < outerDim; i++)
        {
            compSize += (uint8_t *)endPointers[i] - (uint8_t *)data[i];
        }

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
    }

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    SparseMatrix<T, indexT, compressionLevel, columnMajor>::SparseMatrix(typename CSF::SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector &vec) {
        // if it is the matrix is empty and we need to construct it
        if (columnMajor)
        {
            numRows = vec.length();
            numCols = 1;
            innerDim = numRows;
            outerDim = numCols;
        }
        else
        {
            numRows = 1;
            numCols = vec.length();
            innerDim = numCols;
            outerDim = numRows;
        }

        nnz = vec.nonZeros();
        compSize = vec.byteSize() + sizeof(void *) * 2;

        val_t = encodeVal();
        index_t = sizeof(indexT);

        // malloc the data
        try
        {
            data = (void **)malloc(sizeof(void *));
            endPointers = (void **)malloc(sizeof(void *));
        }
        catch (std::bad_alloc &e)
        {
            throw std::bad_alloc();
        }

        // malloc the vector
        try
        {
            // if vector is empty set the data to null
            if (vec.begin() == vec.end())
            {
                data[0] = nullptr;
                endPointers[0] = nullptr;
            }
            else
            {
                data[0] = malloc(vec.byteSize());
                endPointers[0] = (char *)data[0] + vec.byteSize();
            }
        }
        catch (std::bad_alloc &e)
        {
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

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    SparseMatrix<T, indexT, compressionLevel, columnMajor>::SparseMatrix(const char *filename)
    {
        FILE *fp = fopen(filename, "rb");

        if (fp == nullptr)
        {
            throw std::runtime_error("File not found");
        }

        // read the meta data
        metadata = new uint32_t[NUM_META_DATA];

        fread(metadata, sizeof(uint32_t), NUM_META_DATA, fp);

        // set the meta data
        innerDim = metadata[1];
        outerDim = metadata[2];
        nnz = metadata[3];
        val_t = metadata[4];
        index_t = metadata[5];

        if (columnMajor) {
            numRows = innerDim;
            numCols = outerDim;
        } else {
            numRows = outerDim;
            numCols = innerDim;
        }

        if constexpr (DEBUG)
            userChecks();

        // malloc the data
        try
        {
            data = (void **)malloc(sizeof(void *) * outerDim);
            endPointers = (void **)malloc(sizeof(void *) * outerDim);
        }
        catch (std::bad_alloc &e)
        {
            throw std::bad_alloc();
        }

        // read the data
        for (size_t i = 0; i < outerDim; i++)
        {
            // get the size of the column
            uint64_t size;
            fread(&size, sizeof(uint64_t), 1, fp);

            // malloc the column
            try
            {
                data[i] = malloc(size);
                endPointers[i] = (char *)data[i] + size;
            }
            catch (std::bad_alloc &e)
            {
                throw std::bad_alloc();
            }
        }

        // read the data
        for (size_t i = 0; i < outerDim; i++)
        {
            fread(data[i], 1, (uint8_t *)endPointers[i] - (uint8_t *)data[i], fp);
        }

        fclose(fp);

        // calculate comp size
        compSize = META_DATA_SIZE + (sizeof(void *) * outerDim) * 2;

        for (size_t i = 0; i < outerDim; i++)
        {
            compSize += (uint8_t *)endPointers[i] - (uint8_t *)data[i];
        }
    }

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    SparseMatrix<T, indexT, compressionLevel, columnMajor>::~SparseMatrix() {
        // delete the meta data
        if (metadata != nullptr) {
            delete[] metadata;
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
    }

}