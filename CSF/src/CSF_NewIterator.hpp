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


    /**
     * @brief Construct a new SparseMatrix<T, T_index, compression_level>::InnerIterator::InnerIterator object
     *
     * TODO: needs to be redone
     *
     * @tparam T
     * @tparam T_index
     * @tparam compression_level
     * @param filePath
     */
     // template <typename T, typename T_index, uint8_tcompression_level>
     // SparseMatrix<T, T_index, compression_level>::InnerIterator::InnerIterator(const char* filePath) {
         // readFile(filePath);

         // // read first 28 bytes of fileData put it into params -> metadata
         // // uint32_t params[NUM_META_DATA];

         // memcpy(&metadata, data, META_DATA_SIZE);
         // data = (char*)(data)+META_DATA_SIZE;

         // // valueWidth is set and the first value is read in
         // valueWidth = metadata[4];
         // goToColumn(0);

         // val = (T*)(data);
         // data = (char*)(data)+valueWidth;

         // // Read in the width of this run's indices and go to first row
         // indexWidth = *(uint8_t*)(data);
         // data = (char*)(data)+1;
     // }

     // ------------------------------- InnerIterator Methods ----------------------------------- //

     // ---------------- Public Methods ---------------- //

    // template <typename T, typename T_index, uint8_t compression_level>
    // uint32_t* SparseMatrix<T, T_index, compression_level>::InnerIterator::getMetaData() { return metadata; }

    template <typename T, typename T_index, uint8_t compression_level>
    T_index SparseMatrix<T, T_index, compression_level>::InnerIterator::col() { return column; }

    template <typename T, typename T_index, uint8_t compression_level>
    T SparseMatrix<T, T_index, compression_level>::InnerIterator::value() { return *val; }

    // template <typename T, typename T_index, uint8_t compression_level>
    // T& SparseMatrix<T, T_index, compression_level>::InnerIterator::operator*() { return *val; }

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
    // void SparseMatrix<T, T_index, compression_level>::InnerIterator::reset() {
    //     data = data;

    //     goToColumn(0);

    //     val = (T*)(data);
    //     data = (char*)(data)+valueWidth;

    //     // Read in the width of this run's indices and go to first row
    //     indexWidth = *(uint8_t*)(data);
    //     data = (char*)(data)+1;
    // }

    template <typename T, typename T_index, uint8_t compression_level>
    void SparseMatrix<T, T_index, compression_level>::InnerIterator::operator++(int) {
        data = (uint8_t*)data + indexWidth;

        decodeIndex();

        // If new_row is 0 and not the first row, then the row is a delimitor
        if (new_row == 0){// && !firstIndex) {

            data = (uint8_t*)data + indexWidth;

            // val is the first row of the run
            val = (T*)data;
            data = (char*)data + sizeof(T);

            // indexWidth is the second val in the run
            indexWidth = *(uint8_t*)data;
            data = (uint8_t*)data + sizeof(uint8_t);

            // update currentCol to the next column

            // Make row 0 as it is a new run
            decodeIndex();
            row = new_row;

            row = new_row;
            firstIndex = true;
        }

        firstIndex = false;

        // Depending on if the CSF::SparseMatrix is at compression level 2 or 3, we handle the row differently
        // Compression level 3 is postive delta encoded, so we return the sum of the current row and the previous ones
        if constexpr (compression_level == 2) {
            row = new_row;
        }
        else
            row += new_row;
    }

    // template <typename T, typename T_index, uint8_tcompression_level>
    // char* SparseMatrix<T, T_index, compression_level>::InnerIterator::getColumn(uint64_t column) {
    //     // TODO: optimize this function

    //     // Reseets InnerIterator to the beginning and sends it to the corresponding column
    //     InnerIterator it = *this;
    //     it.index = 0;
    //     it.goToColumn(column);
    //     it.data = (char*)(it.data) + 1;
    //     it.val = it.interpretPointer(it.valueWidth);
    //     char* columnData = (char*)calloc(it.numRows, sizeof(T));

    //     if (numColumns != 1)
    //         it.endOfCol = (char*)(data)+*((uint64_t*)(data)+META_DATA_SIZE + ((column + 1) * sizeof(uint64_t)));

    //     // copy data into new array
    //     while (it) {
    //         it++;
    //         columnData[it.index] = val;
    //     }

    //     return columnData;
    // }

    // template <typename T, typename T_index, uint8_tcompression_level>
    // CSF::InnerIterator<T, T_index, compression_level> SparseMatrix<T, T_index, compression_level>::InnerIterator::getColumn(uint64_t column) {
    //     InnerIterator* it = new InnerIterator(*this); //Creates a shallow copy of the InnerIterator
    //     it.goToColumn(column);
    //     it.setEnd(goToColumn(column + 1));

    //     return *it;
    // }

    // template <typename T, typename T_index, uint8_tcompression_level>
    // void SparseMatrix<T, T_index, compression_level>::InnerIterator::setRunValue(T newValue) { *val = newValue; }

    // ---------------- Private Methods ---------------- //

    // template <typename T, typename T_index, uint8_t compression_level>
    // void SparseMatrix<T, T_index, compression_level>::InnerIterator::readMetaData() {

    //     //uint32_t params[NUM_META_DATA];
    //     memcpy(&metadata, data, META_DATA_SIZE);


    //     // metadata[0] compression type
    //     // metadata[1] row type
    //     // metadata[2] column type
    //     // metadata[3] value type
    //     // metadata[4] # of rows
    //     // metadata[5] # of columns
    //     // metadata[6] # of nonzeros

    //     valueWidth = metadata[3] & 0xF;
    //     numRows = metadata[4];
    //     numColumns = metadata[5];
    // }

    // template <typename T, typename T_index, uint8_tcompression_level>
    // void SparseMatrix<T, T_index, compression_level>::InnerIterator::readFile(const char* filePath) {
    //     FILE* file = fopen(filePath, "rb");

    //     // Find end of file and allocate size
    //     fseek(file, 0, SEEK_END);
    //     int sizeOfFile = ftell(file);
    //     data = (char*)malloc(sizeof(char*) * sizeOfFile);

    //     // Read file into memory
    //     fseek(file, 0, SEEK_SET);
    //     fread(data, sizeOfFile, 1, file);
    //     fclose(file);

    //     data = data;
    // }

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