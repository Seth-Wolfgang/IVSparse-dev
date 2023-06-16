#pragma once

namespace CSF {

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    SparseMatrix<T, indexT, compressionLevel, columnMajor>::SparseMatrix() {
        val_t = 0;
        index_t = 0;

        data = nullptr;
        endPointers = nullptr;
        metadata = nullptr;
    }

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    SparseMatrix<T, indexT, compressionLevel, columnMajor>::SparseMatrix(Eigen::SparseMatrix<T>& mat) {

        // see if the matrix is empty
        if (mat.nonZeros() == 0) [[unlikely]] {
            val_t = 0;
            index_t = 0;

            data = nullptr;
            endPointers = nullptr;
            metadata = nullptr;

            return;
        }

        mat.makeCompressed();

        // Set the number of rows, columns and non-zero elements
        if (columnMajor) {
            innerDim = mat.rows();
            outerDim = mat.cols();
        }
        else {
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

#ifdef CSF_DEBUG
        // ensure the vectors are all the same length
        for (size_t i = 1; i < size; i++) {
            assert(vec[i].length() == vec[i - 1].length() && "All vectors must be the same length!");
        }

        // size is greater than 0
        assert(size > 0 && "The size of the array must be greater than 0!");
#endif

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

        bool exception_occurred = false;
        std::string exception_msg;

#pragma omp parallel for shared(exception_occurred, exception_msg)
        for (size_t i = 0; i < outerDim; i++) {
            if (!exception_occurred) {
                try {
                    data[i] = malloc(vec[i].byteSize());
                }
                catch (const std::exception& e) {
#pragma omp critical
                    {
                        exception_occurred = true;
                        exception_msg = e.what();
                    }
#pragma omp cancel for
                }
                if (!exception_occurred) {
                    memcpy(data[i], vec[i].data(), vec[i].byteSize());
                    endPointers[i] = (char*)data[i] + vec[i].byteSize();

#pragma omp atomic
                    nnz += vec[i].nonZeros();
#pragma omp atomic
                    compSize += vec[i].byteSize();
                }
            }
        }

        if (exception_occurred) {
            std::cerr << exception_msg << '\n';
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
#ifdef CSF_DEBUG
        userChecks();
#endif
    }

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    SparseMatrix<T, indexT, compressionLevel, columnMajor>::SparseMatrix(Eigen::SparseMatrix<T, Eigen::RowMajor>& mat) {

        // see if the matrix is empty
        if (mat.nonZeros() == 0) [[unlikely]] {
            val_t = 0;
            index_t = 0;

            data = nullptr;
            endPointers = nullptr;
            metadata = nullptr;

            return;
        }

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

        compress(vals, innerIndices, outerPtr);
    }

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    SparseMatrix<T, indexT, compressionLevel, columnMajor>::SparseMatrix(std::unordered_map<T, std::vector<indexT>> maps[], uint32_t num_rows, uint32_t num_cols) {

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
        numRows = num_cols;
        numCols = num_rows;

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

        //* logic here

        // loop through the array
        #ifdef CSF_PARALLEL
        #pragma omp parallel for
        #endif
        for (size_t i = 0; i < outerDim; i++) {

            // check if the column is empty
            if (maps[i].empty()) [[unlikely]] {
                continue;
            }

            size_t byteSize = 0;
            if constexpr (compressionLevel == 3) {
                // loop through the vectors of the map
                for (auto& val : maps[i]) {
                    // add the size of the vector to the byteSize
                    byteSize += sizeof(T) + 1 + (val.second[val.second.size() - 1] * (val.second.size() - 1) + val.second[val.second.size() - 1]);
                }
            }
            else {
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

            // compress the column
            void* helpPtr = data[i];

            for (auto& val : maps[i]) {

                if constexpr (compressionLevel == 3) {
                    nnz += val.second.size() - 1;
                }
                else {
                    nnz += val.second.size();
                }

                // set the value
                *(T*)helpPtr = val.first;
                helpPtr = (char*)helpPtr + sizeof(T);

                // write the index width
                if constexpr (compressionLevel == 3) {
                    *(uint8_t*)helpPtr = (uint8_t)val.second[val.second.size() - 1];
                    helpPtr = (uint8_t*)helpPtr + 1;
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
                else {
                    *(indexT*)helpPtr = (indexT)DELIM;
                    helpPtr = (indexT*)helpPtr + 1;
                }

            }

        }

        //* end logic

        compSize += META_DATA_SIZE + (sizeof(void*) * outerDim) * 2;

        // add up the size of each col and add it to compSize
        for (size_t i = 0; i < outerDim; i++) {
            compSize += (uint8_t*)endPointers[i] - (uint8_t*)data[i];
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
#ifdef CSF_DEBUG
        userChecks();
#endif
    }

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    SparseMatrix<T, indexT, compressionLevel, columnMajor>::SparseMatrix(typename CSF::SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector& vec) {
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
#ifdef CSF_DEBUG
        userChecks();
#endif
    }

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    SparseMatrix<T, indexT, compressionLevel, columnMajor>::SparseMatrix(const char* filename) {
        FILE* fp = fopen(filename, "rb");

        if (fp == nullptr) {
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
        }
        else {
            numRows = outerDim;
            numCols = innerDim;
        }

        // run the user checks
#ifdef CSF_DEBUG
        userChecks();
#endif

        // malloc the data
        try {
            data = (void**)malloc(sizeof(void*) * outerDim);
            endPointers = (void**)malloc(sizeof(void*) * outerDim);
        }
        catch (std::bad_alloc& e) {
            throw std::bad_alloc();
        }

        // read the data
        for (size_t i = 0; i < outerDim; i++) {
            // get the size of the column
            uint64_t size;
            fread(&size, sizeof(uint64_t), 1, fp);

            // malloc the column
            try {
                data[i] = malloc(size);
                endPointers[i] = (char*)data[i] + size;
            }
            catch (std::bad_alloc& e) {
                throw std::bad_alloc();
            }
        }

        // read the data
        for (size_t i = 0; i < outerDim; i++) {
            fread(data[i], 1, (uint8_t*)endPointers[i] - (uint8_t*)data[i], fp);
        }

        fclose(fp);

        // calculate comp size
        compSize = META_DATA_SIZE + (sizeof(void*) * outerDim) * 2;

        for (size_t i = 0; i < outerDim; i++) {
            compSize += (uint8_t*)endPointers[i] - (uint8_t*)data[i];
        }
    }

    // generalized conversion constructor
    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    template <uint8_t compressionLevel2>
    SparseMatrix<T, indexT, compressionLevel, columnMajor>::SparseMatrix(CSF::SparseMatrix<T, indexT, compressionLevel2, columnMajor>& mat) {
        // takes any CSF matrix and converts it to a compressionLevel matrix (of compression level 2 or 3 due to template specialization)

        // see if the matrix is empty
        if (mat.nonZeros() == 0) [[unlikely]] {
            val_t = 0;
            index_t = 0;

            data = nullptr;
            endPointers = nullptr;
            metadata = nullptr;

            return;
        }

        CSF::SparseMatrix<T, indexT, compressionLevel, columnMajor> mat2;

        // if the incoming matrix is CSF 1
        if constexpr (compressionLevel2 == 1) {
            // if the desired compression is level 2
            if constexpr (compressionLevel == 2) {
                // convert the incoming matrix to CSF 2
                mat2 = mat.toCSF2();

            }
            else if constexpr (compressionLevel == 3) {
                // convert the incoming matrix to CSF 3
                mat2 = mat.toCSF3();
            }
        }
        else if constexpr (compressionLevel2 == 2) {
            if constexpr (compressionLevel == 2) {
                // copy mat and put it in mat2
                mat2 = mat;
                performanceVecsOn = mat.performanceVecsOn;
                if (performanceVecsOn) {
                    value_arr = (T**)malloc(sizeof(T*) * mat.outerDim);
                    counts_arr = (uint32_t**)malloc(sizeof(uint32_t*) * mat.outerDim);

                    value_arr_size = (uint32_t*)malloc(sizeof(uint32_t) * mat.outerDim);
                    memcpy(value_arr_size, mat.value_arr_size, sizeof(uint32_t) * mat.outerDim);

                    for (int i = 0; i < mat.outerDim; i++) {

                        value_arr[i] = (T*)malloc(sizeof(T*) * mat.value_arr_size[i]);
                        counts_arr[i] = (uint32_t*)malloc(sizeof(uint32_t*) * mat.value_arr_size[i]);

                        memcpy(value_arr[i], mat.value_arr[i], sizeof(T) * mat.value_arr_size[i]);
                        memcpy(counts_arr[i], mat.counts_arr[i], sizeof(uint32_t) * mat.value_arr_size[i]);
                    }

                }

            }
            else if constexpr (compressionLevel == 3) {
                // convert the incoming matrix to CSF 3 by going through eigen first
                Eigen::SparseMatrix<T> matEigen = mat.toEigen();
                CSF::SparseMatrix<T, indexT, compressionLevel, columnMajor> mat3(matEigen);

                mat2 = mat3;
            }
        }
        else if constexpr (compressionLevel2 == 3) {
            if constexpr (compressionLevel == 3) {
                // do nothing because the incoming matrix is already CSF 3
                mat2 = mat;
            }
            else if constexpr (compressionLevel == 2) {
                // convert the incoming matrix to CSF 2 by going through eigen first
                Eigen::SparseMatrix<T> matEigen = mat.toEigen();
                CSF::SparseMatrix<T, indexT, compressionLevel, columnMajor> mat3(matEigen);

                mat2 = mat3;
            }
        }


        // Set the number of rows, columns and non-zero elements
        innerDim = mat2.innerSize();
        outerDim = mat2.outerSize();

        numRows = mat2.rows();
        numCols = mat2.cols();

        nnz = mat2.nonZeros();

        compSize = mat2.compressionSize();

        try {
            data = (void**)malloc(outerDim * sizeof(void*));
            endPointers = (void**)malloc(outerDim * sizeof(void*));
        }
        catch (const std::exception& e) {
            std::cerr << e.what() << '\n';
        }

        // #ifdef CSF_PARALLEL
        // #pragma omp parallel for
        // #endif
        for (size_t i = 0; i < outerDim; i++) {
            try {
                data[i] = malloc(mat2.getVecSize(i));
            }
            catch (const std::exception& e) {
                //! Potential Parallelism issue here
                std::cerr << e.what() << '\n';
            }
            memcpy(data[i], mat2.getVecPointer(i), mat2.getVecSize(i));
            endPointers[i] = (char*)data[i] + mat2.getVecSize(i);
        }

        //allocate memory for metadata
        metadata = new uint32_t[NUM_META_DATA];
        memcpy(metadata, mat2.metadata, NUM_META_DATA * sizeof(uint32_t));

        index_t = mat2.index_t;

        val_t = encodeVal();

        std::cout << std::endl;
        for (int i = 0; i < outerDim; i++) {
            std::cout << "value_arr[" << i << "]: ";
            for (int j = 0; j < value_arr_size[i]; j++) {
                std::cout << value_arr[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }


    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    SparseMatrix<T, indexT, compressionLevel, columnMajor>::SparseMatrix(const CSF::SparseMatrix<T, indexT, compressionLevel, columnMajor>& other) {

        // do a deep copy of the matrix

        // Set the number of rows, columns and non-zero elements
        innerDim = other.innerSize();
        outerDim = other.outerSize();

        numRows = other.rows();
        numCols = other.cols();

        nnz = other.nonZeros();

        compSize = other.compressionSize();

        try {
            data = (void**)malloc(outerDim * sizeof(void*));
            endPointers = (void**)malloc(outerDim * sizeof(void*));
        }
        catch (const std::exception& e) {
            std::cerr << e.what() << '\n';
        }

        // if (other.isPerformanceVecsOn()) {
        //     performanceVecsOn = true;
        //     value_arr = (T*)malloc(sizeof(T**) * other.outerDim);
        //     counts_arr = (uint32_t*)malloc(sizeof(T**) * other.outerDim);

        //     value_arr_size = (uint32_t*)malloc(sizeof(uint32_t*) * other.outerDim);
        //     memcpy(value_arr, other.value_arr, sizeof(uint32_t) * outerDim);

        //     for (int i = 0; i < outerDim; i++) {
        //         value_arr[i] = (T*)malloc(sizeof(T*) * value_arr_size[i]);
        //         counts_arr[i] = (uint32_t*)malloc(sizeof(uint32_t*) * value_arr_size[i]);
        //     }
        // }


        // #ifdef CSF_PARALLEL
        // #pragma omp parallel for
        // #endif
        for (size_t i = 0; i < outerDim; i++) {
            try {
                data[i] = malloc(other.getVecSize(i));
            }
            catch (const std::exception& e) {
                //! Potential Parallelism issue here
                std::cerr << e.what() << '\n';
            }
            memcpy(data[i], other.getVecPointer(i), other.getVecSize(i));
            endPointers[i] = (char*)data[i] + other.getVecSize(i);
        }

        //allocate memory for metadata
        metadata = new uint32_t[NUM_META_DATA];
        memcpy(metadata, other.metadata, NUM_META_DATA * sizeof(uint32_t));

        index_t = other.index_t;
        val_t = encodeVal();

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

        if constexpr (compressionLevel == 2) {
            // if value array and counts are not null, free them
            if (value_arr != nullptr) {
                for (int i = 0; i < outerDim; i++) {
                    if (value_arr[i] != nullptr) {
                        free(value_arr[i]);
                    }
                }
                free(value_arr);
            }

            if (counts_arr != nullptr) {
                for (int i = 0; i < outerDim; i++) {
                    if (counts_arr[i] != nullptr) {
                        free(counts_arr[i]);
                    }
                }
                free(counts_arr);
            }

            if (value_arr_size != nullptr) {
                free(value_arr_size);
            }
        }
    }

}