#pragma once

namespace CSF {

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector::Vector() {}

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector::Vector(CSF::SparseMatrix<T, indexT, compressionLevel, columnMajor>& mat, uint32_t vec) {
        // get the vecLength of the vector
        size = mat.getVecSize(vec);
        vecLength = mat.innerSize();

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
        memcpy(data, mat.getVecPointer(vec), size);

        // set the end pointer
        endPtr = (uint8_t*)data + size;
    }

    // Deep copy constructor
    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector::Vector(CSF::SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector& vec) {
        // set data pointer //! TODO: This is a shallow copy
        data = vec.begin();

        // get the vecLength of the vector
        size = vec.byteSize();

        // if the size is 0 then the vector is empty
        if (size == 0) {
            endPtr = nullptr;
            return;
        }

        vecLength = vec.length();

        // set the end pointer
        endPtr = (uint8_t*)data + size;
    }

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector::Vector(std::unordered_map<T, std::vector<indexT>>& map, uint32_t vecLength) {
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

        // set the vecLength
        this->vecLength = vecLength;

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
    }

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    uint32_t SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector::length() { return vecLength; }

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    uint32_t SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector::outerSize() { return 1; }

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    uint32_t SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector::nonZeros() {
        if (nnz == 0 && size > 0) {
            // make an iterator for the vector
            CSF::SparseMatrix<T, indexT, compressionLevel, columnMajor>::InnerIterator it(*this);

            // iterate through the vector until the index is found
            while (it) {
                nnz++;
                ++it;
            }
        }

        return nnz;

    }

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    void* SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector::begin() { return data; }

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    void* SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector::end() { return endPtr; }

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    size_t SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector::byteSize() { return size; }

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    typename SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector::operator=(typename SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector &other) {
        // copy the data //! doesn't copy?
        data = other.data;
        endPtr = other.endPtr;
        size = other.size;
        vecLength = other.vecLength;
        nnz = other.nnz;

        // return the vector
        return other;
    }

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    T SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector::operator[](uint32_t index) {
        // make an iterator for the vector
        CSF::SparseMatrix<T, indexT, compressionLevel, columnMajor>::InnerIterator it(*this);

        // iterate through the vector until the index is found
        while (it) {
            if (it.index() == index) {
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

}