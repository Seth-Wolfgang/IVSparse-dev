#pragma once
#define META_DATA_SIZE 24 // number of bytes in metadata (7 * 4)
#define NUM_META_DATA 6 // number of metadata values

namespace CSF {
    //** ------------------------------------------------------------------------------------------------------------------ **//
    //** --------------------------------------------- InnerIterator Class (2 & 3) --------------------------------------------- **//
    //** ------------------------------------------------------------------------------------------------------------------ **//

    // ---------------- InnerIterator Constructors ---------------- //

    template <typename T, typename T_index, uint8_t compression_level>
    SparseMatrix<T, T_index, compression_level>::InnerIterator::InnerIterator(CSF::SparseMatrix<T, T_index, compression_level>& matrix, uint32_t col) {

        // Sets the column
        this->column = col;

        // Sets the data pointer to the specified column of the matrix
        data = matrix.getColPointer(col);

        // Reads the matrix's metadata
        // readMetaData();

        // If the column is all zeros, set the data to the end pointer
        if (data == nullptr) {
            // Trips bool operator
            data = end_ptr;
            return;
        }

        // Sets the end pointer
        uint32_t col_size = matrix.getColSize(col);
        end_ptr = (uint8_t*)data + col_size;

        // Points value to the first value in the column
        val = (T*)data;
        data = (uint8_t*)data + sizeof(T);

        // Sets row width to the width of the first run
        indexWidth = *(uint8_t*)data;
        data = (uint8_t*)data + sizeof(uint8_t);


        decodeIndex();
        row = new_row;
    }

    template <typename T, typename T_index, uint8_t compression_level>
    SparseMatrix<T, T_index, compression_level>::InnerIterator::InnerIterator(SparseMatrix<T, T_index, compression_level>::Vector& vec) {
        // set the column to -1
        this->column = 0;

        // set the data pointer
        data = vec.begin();

        // If the column is all zeros, set the data to the end pointer
        if (data == nullptr) {
            // Trips bool operator
            data = end_ptr;
            return;
        }

        // set the end pointer
        end_ptr = vec.end();

        val = (T*)data;
        data = (uint8_t*)data + sizeof(T);

        indexWidth = *(uint8_t*)data;
        data = (uint8_t*)data + sizeof(uint8_t);

        decodeIndex();
        row = new_row;

    }

     // ------------------------------- InnerIterator Methods ----------------------------------- //

     // ---------------- Public Methods ---------------- //

    // template <typename T, typename T_index, uint8_t compression_level>
    // uint32_t* SparseMatrix<T, T_index, compression_level>::InnerIterator::getMetaData() { return metadata; }

    template <typename T, typename T_index, uint8_t compression_level>
    T_index SparseMatrix<T, T_index, compression_level>::InnerIterator::col() { return column; }

    template <typename T, typename T_index, uint8_t compression_level>
    T SparseMatrix<T, T_index, compression_level>::InnerIterator::value() { return *val; }

    template <typename T, typename T_index, uint8_t compression_level>
    T& SparseMatrix<T, T_index, compression_level>::InnerIterator::operator*() { return *val; }

    template <typename T, typename T_index, uint8_t compression_level>
    bool SparseMatrix<T, T_index, compression_level>::InnerIterator::operator==(const InnerIterator& other) { return data == other.getIndex(); }

    template <typename T, typename T_index, uint8_t compression_level>
    bool SparseMatrix<T, T_index, compression_level>::InnerIterator::operator!=(const InnerIterator& other) { return data != other.getIndex(); }

    template <typename T, typename T_index, uint8_t compression_level>
    bool SparseMatrix<T, T_index, compression_level>::InnerIterator::operator<(const InnerIterator& other) { return data < other.getIndex(); }

    template <typename T, typename T_index, uint8_t compression_level>
    bool SparseMatrix<T, T_index, compression_level>::InnerIterator::operator>(const InnerIterator& other) { return data > other.getIndex(); }

    template <typename T, typename T_index, uint8_t compression_level>
    T_index SparseMatrix<T, T_index, compression_level>::InnerIterator::index() { return row; }

    template <typename T, typename T_index, uint8_t compression_level>
    bool SparseMatrix<T, T_index, compression_level>::InnerIterator::atBeginningOfRun() { return firstIndex; }

    // template <typename T, typename T_index, uint8_t compression_level>
    // void SparseMatrix<T, T_index, compression_level>::InnerIterator::operator++(int) {
        
    //     if (data == end_ptr) {
    //         return;
    //     }
        
    //     data = (uint8_t*)data + indexWidth;

    //     decodeIndex();

    //     // If new_row is 0 and not the first row, then the row is a delimitor
    //     if (new_row == 0){// && !firstIndex) {

    //         data = (uint8_t*)data + indexWidth;

    //         // val is the first row of the run
    //         val = (T*)data;
    //         data = (char*)data + sizeof(T);

    //         // indexWidth is the second val in the run
    //         indexWidth = *(uint8_t*)data;
    //         data = (uint8_t*)data + sizeof(uint8_t);

    //         // update currentCol to the next column

    //         // Make row 0 as it is a new run
    //         decodeIndex();
    //         row = new_row;

    //         return;
    //         firstIndex = true;
    //     }

    //     firstIndex = false;

    //     // Depending on if the CSF::SparseMatrix is at compression level 2 or 3, we handle the row differently
    //     // Compression level 3 is postive delta encoded, so we return the sum of the current row and the previous ones
    //     if constexpr (compression_level == 2) {
    //         row = new_row;
    //     }
    //     else
    //         row += new_row;
    // }

    template <typename T, typename T_index, uint8_t compression_level>
    void SparseMatrix<T, T_index, compression_level>::InnerIterator::operator++()
    {

        data = (uint8_t *)data + indexWidth;

        decodeIndex();

        // If new_row is 0 and not the first row, then the row is a delimitor
        if (new_row == 0) {

            if (data >= (uint8_t *)end_ptr - indexWidth) [[unlikely]] {
                return;
            }

            data = (uint8_t *)data + indexWidth;


            // val is the first row of the run
            val = (T *)data; //! HERE SOMEWHERE
            data = (char *)data + sizeof(T);

            // indexWidth is the second val in the run
            indexWidth = *(uint8_t *)data;
            data = (uint8_t *)data + sizeof(uint8_t);

            // update currentCol to the next column

            // Make row 0 as it is a new run
            decodeIndex();
            row = new_row;

            return;
        }


        // Depending on if the CSF::SparseMatrix is at compression level 2 or 3, we handle the row differently
        // Compression level 3 is postive delta encoded, so we return the sum of the current row and the previous ones
        if constexpr (compression_level == 2) {
            row = new_row;
        } else
            row += new_row;
    }

    // ---------------- Private Methods ---------------- //

    template <typename T, typename T_index, uint8_t compression_level>
    void SparseMatrix<T, T_index, compression_level>::InnerIterator::decodeIndex() {

        switch (indexWidth) {
        case 1:
            new_row = (T_index) * (uint8_t*)data;
            break;
        case 2:
            new_row = (T_index) * (uint16_t*)data;
            break;
        case 4:
            new_row = (T_index) * (uint32_t*)data;
            break;
        case 8:
            new_row = (T_index) * (uint64_t*)data;
            break;
        }
    }


    //** ------------------------------------------------------------------------------------------------------------------ **//
    //** ----------------------------------------------- InnerIterator Class (1) ----------------------------------------------- **//
    //** ------------------------------------------------------------------------------------------------------------------ **//


    // ---------------- Public Methods ---------------- //
}