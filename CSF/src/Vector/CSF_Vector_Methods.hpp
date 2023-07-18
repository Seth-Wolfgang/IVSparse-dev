#pragma once

namespace CSF {

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector::Vector() {
        data = nullptr;
        endPtr = nullptr;
        size = 0;
        length = 0;
    }

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector::Vector(CSF::SparseMatrix<T, indexT, compressionLevel, columnMajor>& mat, uint32_t vec) {

        #ifdef CSF_DEBUG
        // make sure the vector is in bounds
        assert((vec >= 0 && vec < mat.outerSize()) && "Vector index out of bounds");

        // make sure the matrix is not empty
        assert((mat.outerSize() > 0 && mat.innerSize() > 0) && "Matrix is empty");
        #endif

        // get the length of the vector
        size = mat.getVectorSize(vec);
        length = mat.innerSize();

        // if the size is 0 then the vector is empty
        if (size == 0) {
            data = nullptr;
            endPtr = nullptr;
            return;
        }

        // set data pointer
        try {
            data = malloc(size);
        }
        catch (std::bad_alloc& e) {
            std::cerr << e.what() << '\n';
        }

        // copy the vector data into the vector
        memcpy(data, mat.vectorPointer(vec), size);

        // set the end pointer
        endPtr = (uint8_t*)data + size;

        if (compressionLevel == 2) {
            valueArraySize = mat.valueArraySize[vec];

            // allocate space for the value array
            try {
                valueArray = (T*)malloc(sizeof(T) * valueArraySize);
                countsArray = (uint32_t*)malloc(sizeof(uint32_t) * valueArraySize);
            }
            catch (std::bad_alloc& e) {
                std::cerr << e.what() << '\n';
            }

            // copy the value array
            memcpy(valueArray, mat.valueArray[vec], sizeof(T) * valueArraySize);

            // copy the counts array
            memcpy(countsArray, mat.countsArray[vec], sizeof(uint32_t) * valueArraySize);
        }

        // set the nnz
        if (nnz == 0 && size > 0) {
            // make an iterator for the vector
            CSF::SparseMatrix<T, indexT, compressionLevel, columnMajor>::InnerIterator it(*this);

            // iterate through the vector until the index is found
            while (it) {
                nnz++;
                ++it;
            }
        }

    }

    // Deep copy constructor
    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector::Vector(CSF::SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector& vec) {
        // set the size
        size = vec.size;

        // set the length
        length = vec.length;

        // if the size is 0 then the vector is empty
        if (size == 0) {
            data = nullptr;
            endPtr = nullptr;
            return;
        }

        // set data pointer
        try {
            data = malloc(size);
        }
        catch (std::bad_alloc& e) {
            std::cerr << e.what() << '\n';
        }

        // if performance vectors are on copy those as well
        if (vec.performanceVectors) {
            performanceVectors = true;

            valueArraySize = vec.valueArraySize;

            // allocate space for the value array
            try {
                valueArray = (T*)malloc(sizeof(T) * valueArraySize);
                countsArray = (uint32_t*)malloc(sizeof(uint32_t) * valueArraySize);
            }
            catch (std::bad_alloc& e) {
                std::cerr << e.what() << '\n';
            }

            // copy the value array
            memcpy(valueArray, vec.valueArray, sizeof(T) * valueArraySize);

            // copy the counts array
            memcpy(countsArray, vec.countsArray, sizeof(uint32_t) * valueArraySize);
        }

        // copy the vector data into the vector
        memcpy(data, vec.data, size);

        // set the end pointer
        endPtr = (uint8_t*)data + size;

        // set the nnz
        nnz = vec.nonZeros();

        #ifdef CSF_DEBUG
        userChecks();
        #endif
    }

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector::Vector(std::unordered_map<T, std::vector<indexT>>& map, uint32_t length) {
        // loop through and get the size to store the data
        size = 0;
        if constexpr (compressionLevel == 3) {
            for (auto& it : map) {
                size += sizeof(T) + 1 + (it.second[it.second.size() - 1] * (it.second.size() - 1)) + it.second[it.second.size() - 1];
            }
        }
        else {
            for (auto& it : map) {
                size += sizeof(T) + 1 + (sizeof(indexT) * it.second.size()) + sizeof(indexT);
            }
        }

        // set the length
        this->length = length;

        // if the size is 0 then the vector is empty
        if (size == 0) {
            data = nullptr;
            endPtr = nullptr;
            return;
        }

        // set data pointer
        try {
            data = malloc(size);
        }
        catch (std::bad_alloc& e) {
            std::cout << "Error: " << e.what() << std::endl;
            exit(1);
        }

        // set the end pointer
        endPtr = (uint8_t*)data + size;

        void* helpPtr = data;

        // loop through the map and copy the data into the vector
        for (auto& it : map) {
            if constexpr (compressionLevel == 3)
                nnz += it.second.size() - 1;
            else
                nnz += it.second.size();

            // write the value
            *(T*)helpPtr = it.first;
            helpPtr = (uint8_t*)helpPtr + sizeof(T);

            // write the index width
            if constexpr (compressionLevel == 3) {
                *(uint8_t*)helpPtr = (uint8_t)it.second[it.second.size() - 1];
                helpPtr = (uint8_t*)helpPtr + 1;
            }
            else {
                *(uint8_t*)helpPtr = sizeof(indexT);
                helpPtr = (uint8_t*)helpPtr + 1;
            }

            // write the indices
            for (size_t k = 0; k < it.second.size(); k++) {

                if constexpr (compressionLevel == 3) {
                    if (k == it.second.size() - 1)
                        break;

                    switch (it.second[it.second.size() - 1]) {
                    case 1:
                        *(uint8_t*)helpPtr = (uint8_t)it.second[k];
                        helpPtr = (uint8_t*)helpPtr + 1;
                        break;
                    case 2:
                        *(uint16_t*)helpPtr = (uint16_t)it.second[k];
                        helpPtr = (uint16_t*)helpPtr + 1;
                        break;
                    case 4:
                        *(uint32_t*)helpPtr = (uint32_t)it.second[k];
                        helpPtr = (uint32_t*)helpPtr + 1;
                        break;
                    case 8:
                        *(uint64_t*)helpPtr = (uint64_t)it.second[k];
                        helpPtr = (uint64_t*)helpPtr + 1;
                        break;
                    }
                }
                else {
                    *(indexT*)helpPtr = it.second[k];
                    helpPtr = (indexT*)helpPtr + 1;
                }
            }

            // write the delimiter
            if constexpr (compressionLevel == 3) {
                // write a delimiter of the correct width
                switch (it.second[it.second.size() - 1]) {
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

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector::~Vector() {
        if (data != nullptr) {
            free(data);
        }

        if (valueArray != nullptr) {
            free(valueArray);
            free(countsArray);
        }
    }

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    void SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector::userChecks() {
        assert(std::is_floating_point<indexT>::value == false && "The index type must be a non-floating point type");

        assert((compressionLevel == 1 || compressionLevel == 2 || compressionLevel == 3) && "The compression level must be either 1, 2, or 3");

        assert((std::is_arithmetic<T>::value && std::is_arithmetic<indexT>::value) && "The value and index types must be numeric types");

        assert((std::is_same<indexT, bool>::value == false) && "The index type must not be bool");
    }

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    uint32_t SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector::innerSize() { return length; }

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    uint32_t SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector::outerSize() { return 1; }

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    uint32_t SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector::nonZeros() { return nnz; }

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    void* SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector::begin() { return data; }

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    void* SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector::end() { return endPtr; }

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    size_t SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector::byteSize() { return size; }

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    T SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector::coeff(uint32_t index) { return (*this)[index]; }

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    uint32_t SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector::getLength() { return length; }

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    void SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector::setPerformanceVectors(bool on) {

    }

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    bool SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector::performanceVectorsInitialized() { return performanceVectors; }

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    void SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector::undoPerformanceVecs() {

        if (!performanceVectors) {
            return;
        }
        performanceVectors = false;

        free(valueArray);
        free(countsArray);
        valueArraySize = 0;
    }

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    void SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector::activatePerformanceVecs() {

        if (performanceVectors) {
            return;
        }
        performanceVectors = true;

        std::vector<T> values;
        std::vector<uint32_t> countsVector;

        for (typename SparseMatrix<T, indexT, compressionLevel>::InnerIterator it(*this); it; ++it) {
            if (it.isNewRun()) {
                values.push_back(it.value());
                countsVector.push_back(1);
                valueArraySize++;
            }
            else {
                countsVector[countsVector.size() - 1]++;
            }
        }

        try {
            valueArray = (T*)malloc(sizeof(T) * valueArraySize);
            memcpy(valueArray, values.data(), sizeof(T) * valueArraySize);

            countsArray = (uint32_t*)malloc(sizeof(uint32_t) * valueArraySize);
            memcpy(countsArray, countsVector.data(), sizeof(uint32_t) * valueArraySize);
        }
        catch (std::bad_alloc& e) {
            std::cout << "Error: " << e.what() << std::endl;
            exit(1);
        }

        values.clear();
        countsVector.clear();

        compSize += valueArraySize * sizeof(T) + valueArraySize * sizeof(uint32_t);
    }

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    typename SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector::operator=(typename SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector& other) {
        // check if the vector is the same
        if (this == &other) {
            return *this;
        }

        // free the data if it is not null
        if (data != nullptr) {
            free(data);
        }

        if (valueArray != nullptr) {
            free(valueArray);
            free(countsArray);
        }

        // copy the data
        data = (uint8_t*)malloc(other.size);
        memcpy(data, other.data, other.size);

        // set the size
        size = other.size;

        // set the length
        length = other.length;

        // set the nnz
        nnz = other.nnz;

        // set the end pointer
        endPtr = (uint8_t*)data + size;

        if (other.performanceVectors) {
            valueArray = (T*)malloc(sizeof(T) * other.valueArraySize);
            countsArray = (uint32_t*)malloc(sizeof(uint32_t) * other.valueArraySize);

            memcpy(countsArray, other.countsArray, sizeof(uint32_t) * other.valueArraySize);
            memcpy(valueArray, other.valueArray, sizeof(T) * other.valueArraySize);

            valueArraySize = other.valueArraySize;
        }

        // return this
        return *this;
    }

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    T SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector::operator[](uint32_t index) {

        #ifdef CSF_DEBUG
        // check if the index is out of bounds
        assert(index < length && "The index is out of bounds");
        #endif

        // make an iterator for the vector
        CSF::SparseMatrix<T, indexT, compressionLevel, columnMajor>::InnerIterator it(*this);

        // iterate through the vector until the index is found
        while (it) {
            if (it.getIndex() == (indexT)index) {
                return it.value();
            }
            ++it;
        }

        // if the index is not found then return 0
        return 0;
    }

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    void SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector::write(const char* filename) {
        // open the file
        FILE* fp = fopen(filename, "wb");

        // write the data
        fwrite(data, size, 1, fp);

        // close the file
        fclose(fp);
    }

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    void SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector::print() {

        // if length is larger than 100 then print then don't print
        if (length > 100) {
            std::cout << "Vector is too large to print" << std::endl;
            return;
        }

        std::cout << "Vector: ";
        std::cout << std::endl;

        // print a dense vector
        for (uint32_t i = 0; i < length; i++) {
            std::cout << (*this)[i] << " ";
        }

        std::cout << std::endl;
    }

    // get values method
    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    T* SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector::getValues() {
        return valueArray;
    }

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    uint32_t* SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector::getCounts() {
        return countsArray;
    }

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    uint32_t SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector::getValueArraySize() {
        return valueArraySize;
    }
