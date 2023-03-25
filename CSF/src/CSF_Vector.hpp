#pragma once
#define META_DATA_SIZE 24 // number of bytes in metadata (6 * 4)
#define NUM_META_DATA 6   // number of metadata values

namespace CSF {


    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector::Vector() {}

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector::Vector(CSF::SparseMatrix<T, indexT, compressionLevel, columnMajor> &mat, uint32_t vec) {
        // get the length of the vector
        size = mat.getVecSize(vec);
        
        // set data pointer
        data = malloc(size);

        // copy the vector data into the vector
        memcpy(data, mat.getVecPointer(vec), size);
        
        // if the size is 0 then the vector is empty
        if (size == 0) {
            endPtr = nullptr;
            return;
        }

        innerDim = mat.innerSize();

        // set the end pointer
        endPtr = (uint8_t *)data + size;
        // endPtr = (uint8_t *)data + ((char*)mat.getVecPointer(vec) -  (char*)mat.endPointers[vec]);
        // std::cout << "endPtr: " << endPtr << std::endl;
    }

    // Deep copy constructor
    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector::Vector(CSF::SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector &vec) {
        // set data pointer
        data = vec.begin();

        // get the length of the vector
        size = vec.byteSize();

        // if the size is 0 then the vector is empty
        if (size == 0) {
            endPtr = nullptr;
            return;
        }

        innerDim = vec.innerSize();

        // set the end pointer
        endPtr = (uint8_t *)data + size;
    }

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    uint32_t SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector::innerSize() { return innerDim; }

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    uint32_t SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector::outerSize() { return 1; }

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    uint32_t SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector::nonZeros() { return nnz; }

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    void *SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector::begin() { return data; }

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    void *SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector::end() { return endPtr; }

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    size_t SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector::byteSize() { return size; }

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

}