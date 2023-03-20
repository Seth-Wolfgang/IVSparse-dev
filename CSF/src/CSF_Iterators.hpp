#pragma once
#define META_DATA_SIZE 24 // number of bytes in metadata (6 * 4)
#define NUM_META_DATA 6   // number of metadata values

namespace CSF {

    template <typename T, typename T_index, uint8_t compression_level>
    SparseMatrix<T, T_index, compression_level>::InnerIterator::InnerIterator(SparseMatrix<T, T_index, compression_level> &mat, uint32_t col) {
        // Set the column
        this->column = col;

        // set the data pointer
        data = mat.getColPointer(col);

        // if nullptr then the col is empty
        if (data == nullptr) {
            end_ptr = nullptr;
            return;
        }

        // set the end pointer
        size_t col_size = mat.getColSize(col);
        end_ptr = (uint8_t *)data + col_size;

        val = *(T *)data;
        data = (uint8_t *)data + sizeof(T);

        index_width = *(uint8_t *)data;
        data = (uint8_t *)data + sizeof(uint8_t);

        decodeIndex();
        row = new_row;
    }

    template <typename T, typename T_index, uint8_t compression_level>
    SparseMatrix<T, T_index, compression_level>::InnerIterator::InnerIterator(SparseMatrix<T, T_index, compression_level>::Vector &vec) {
        // set the column to -1
        this->column = 0;

        // set the data pointer
        data = vec.begin();

        // if nullptr then the col is empty
        if (data == nullptr) {
            end_ptr = nullptr;
            return;
        }

        // set the end pointer
        end_ptr = vec.end();

        val = *(T *)data;
        data = (uint8_t *)data + sizeof(T);

        index_width = *(uint8_t *)data;
        data = (uint8_t *)data + sizeof(uint8_t);

        decodeIndex();
        row = new_row;

    }

    //! NEED TO FIND VALGRIND INVALID READ ERRORS IN HERE SOMEWHERE !//
    //* there are two invalid reads per col, one of size 1 and one of size 4 *//
    template <typename T, typename T_index, uint8_t compression_level>
    void SparseMatrix<T, T_index, compression_level>::InnerIterator::operator++(int) {

        // if data or end_ptr is null then return
        if (data == nullptr || end_ptr == nullptr) {
            return;
        }

        // iterate the data pointer
        data = (uint8_t *)data + index_width;

        // get the new index
        decodeIndex();

        // if the new index is 0 and atFirst is false it's a delimiter
        if (new_row == 0) {

            // move past delimiter
            data = (uint8_t *)data + index_width;

            // get the new value
            val = *(T *)data;
            data = (uint8_t *)data + sizeof(T);

            // get the new index width
            index_width = *(uint8_t *)data;
            data = (uint8_t *)data + sizeof(uint8_t);

            // get the new index
            decodeIndex();
            row = new_row;

        } else {

            if constexpr (compression_level == 3) {
                row += new_row;
            } else {
                row = new_row;
            }
        }
        
    }

    template <typename T, typename T_index, uint8_t compression_level>
    void SparseMatrix<T, T_index, compression_level>::InnerIterator::decodeIndex() {
        
        switch (index_width) {
            case 1:
                new_row = (T_index)*(uint8_t *)data;
                break;
            case 2:
                new_row = (T_index)*(uint16_t *)data;
                break;
            case 4:
                new_row = (T_index)*(uint32_t *)data;
                break;
            case 8:
                new_row = (T_index)*(uint64_t *)data;
                break;
        }

    }

    template <typename T, typename T_index, uint8_t compression_level>
    T_index SparseMatrix<T, T_index, compression_level>::InnerIterator::index() { return row; }

    template <typename T, typename T_index, uint8_t compression_level>
    T_index SparseMatrix<T, T_index, compression_level>::InnerIterator::col() { return column; }

    template <typename T, typename T_index, uint8_t compression_level>
    T SparseMatrix<T, T_index, compression_level>::InnerIterator::value() { return val; }

    template <typename T, typename T_index, uint8_t compression_level>
    bool SparseMatrix<T, T_index, compression_level>::InnerIterator::operator==(const InnerIterator &other) {
        return data == other.data;
    }

    template <typename T, typename T_index, uint8_t compression_level>
    bool SparseMatrix<T, T_index, compression_level>::InnerIterator::operator!=(const InnerIterator &other) {
        return data != other.data;
    }

    template <typename T, typename T_index, uint8_t compression_level>
    bool SparseMatrix<T, T_index, compression_level>::InnerIterator::operator<(const InnerIterator &other) {
        return data < other.data;
    }

    template <typename T, typename T_index, uint8_t compression_level>
    bool SparseMatrix<T, T_index, compression_level>::InnerIterator::operator>(const InnerIterator &other) {
        return data > other.data;
    }

    
}