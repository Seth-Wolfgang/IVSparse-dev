#pragma once
#define META_DATA_SIZE 24 // number of bytes in metadata (6 * 4)
#define NUM_META_DATA 6   // number of metadata values

namespace CSF {

    template <typename T, typename T_index, uint8_t compression_level>
    SparseMatrix<T, T_index, compression_level>::Vector::Vector(CSF::SparseMatrix<T, T_index, compression_level> &mat, uint32_t col) {
        // set data pointer
        data = mat.getColPointer(col);

        // get the length of the vector
        size = mat.getColSize(col);

        // if the size is 0 then the vector is empty
        if (size == 0) {
            end_ptr = nullptr;
            return;
        }

        // set the end pointer
        end_ptr = (uint8_t *)data + size;
    }

    template <typename T, typename T_index, uint8_t compression_level>
    void *SparseMatrix<T, T_index, compression_level>::Vector::begin() { return data; }

    template <typename T, typename T_index, uint8_t compression_level>
    void *SparseMatrix<T, T_index, compression_level>::Vector::end() { return end_ptr; }

    template <typename T, typename T_index, uint8_t compression_level>
    size_t SparseMatrix<T, T_index, compression_level>::Vector::byteSize() { return size; }

    template <typename T, typename T_index, uint8_t compression_level>
    T SparseMatrix<T, T_index, compression_level>::Vector::operator[](uint32_t index) {
        // make an iterator for the vector
        CSF::SparseMatrix<T, T_index, compression_level>::InnerIterator it(*this);

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