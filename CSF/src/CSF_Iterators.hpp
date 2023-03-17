#pragma once
#define META_DATA_SIZE 28 // number of bytes in metadata (7 * 4)
#define NUM_META_DATA 7 // number of metadata values

namespace CSF {
    //** ------------------------------------------------------------------------------------------------------------------ **//
    //** --------------------------------------------- InnerIterator Class (2 & 3) --------------------------------------------- **//
    //** ------------------------------------------------------------------------------------------------------------------ **//

    // ---------------- InnerIterator Constructors ---------------- //

    template <typename T, typename T_index, int compression_level>
    SparseMatrix<T, T_index, compression_level>::InnerIterator::InnerIterator(CSF::SparseMatrix<T, T_index, compression_level>& matrix, uint64_t col) {
        data = matrix.beginPtr();
        assert(col < matrix.cols());

        // matrix.write("matrix.bin");
        // set to begining of data
        currentIndex = data;

        // Reads in the metadata (initializes class variables)
        readMetaData();

        // Skips metadata and goes to first column
        currentIndex = (void*)((char*)(currentIndex)+META_DATA_SIZE); // ?goes to first col pointer?
        goToColumn(col); // skips past col_p and delim to the start of actual data

        /*
            Here I grab the address of the start of the next column or the end of the matrix.
            I subtract index size of the run because the iterator will need to look for the very last delimitor of the column
            to know when to stop; otherwise it will go past the end and cause a segfault.

            index size of the run    ->    *((char*)currentIndex + valueWidth);
        */
        int indexWidth = *((char*)currentIndex + valueWidth);
        endOfCol = (col == matrix.cols() - 1) ? matrix.endPtr() : (char*)getColumnAddress(col + 1) - indexWidth;

        //A zero vector exists within the matrix if the column pointer is equal to the previous pointer
        // std::cout << "col: " << col << "/" << matrix.cols() - 1 << std::endl;
        // std::cout << "currentIndex: " << currentIndex << std::endl;
        // std::cout << "getColumnAddress(col - 1): " << getColumnAddress(col + 1) << std::endl << std::endl;

        //zero column
        if (col != matrix.cols() - 1 && currentIndex == getColumnAddress(col + 1)) {
            // std::cout << "Zero vector exists at column: " << col << std::endl;
            currentIndex = endOfCol;
            value = (T*)index;

        }
        //end of matrix
        else if ((char*)currentIndex >= (char*)endOfCol - indexWidth) {
            // std::cout << "At end: " << col << std::endl;
            currentIndex = endOfCol;
            *value = 0;

        }
        else {
            // Ensures the matrix is not empty
            // std::cout << "endOfCol: " << endOfCol << " Matrix end" << matrix.endPtr() << std::endl;
            // std::cout << "currentIndex: " << currentIndex << std::endl;
            // std::cout << "cols: " << matrix.cols() << std::endl;

            value = (T*)(currentIndex);
            currentIndex = (char*)(currentIndex)+valueWidth;
            // std::cout << "value: " << *value << std::endl;
            // Read in the width of this run's indices and go to first index
            newIndexWidth = *(uint8_t*)(currentIndex);
            currentIndex = (char*)(currentIndex)+1;
            assert(currentIndex < endOfCol);

        }



    }

    template <typename T, typename T_index, int compression_level>
    SparseMatrix<T, T_index, compression_level>::InnerIterator::InnerIterator(const char* filePath) {
        readFile(filePath);

        // read first 28 bytes of fileData put it into params -> metadata
        // uint32_t params[NUM_META_DATA];

        memcpy(&metadata, currentIndex, META_DATA_SIZE);
        currentIndex = (char*)(currentIndex)+META_DATA_SIZE;

        // valueWidth is set and the first value is read in
        valueWidth = metadata[4];
        goToColumn(0);

        value = (T*)(currentIndex);
        currentIndex = (char*)(currentIndex)+valueWidth;

        // Read in the width of this run's indices and go to first index
        newIndexWidth = *(uint8_t*)(currentIndex);
        currentIndex = (char*)(currentIndex)+1;
    }

    // ------------------------------- InnerIterator Methods ----------------------------------- //

    // ---------------- Public Methods ---------------- //

    template <typename T, typename T_index, int compression_level>
    uint32_t* SparseMatrix<T, T_index, compression_level>::InnerIterator::getMetaData() { return metadata; }

    template <typename T, typename T_index, int compression_level>
    T_index SparseMatrix<T, T_index, compression_level>::InnerIterator::getColIndex() { return currentCol; }

    template <typename T, typename T_index, int compression_level>
    void* SparseMatrix<T, T_index, compression_level>::InnerIterator::getData() { return data; }

    template <typename T, typename T_index, int compression_level>
    void* SparseMatrix<T, T_index, compression_level>::InnerIterator::getEnd() { return endOfCol; }

    template <typename T, typename T_index, int compression_level>
    T& SparseMatrix<T, T_index, compression_level>::InnerIterator::operator*() { return *value; }

    template <typename T, typename T_index, int compression_level>
    bool SparseMatrix<T, T_index, compression_level>::InnerIterator::operator==(const InnerIterator& other) { return currentIndex == other.getIndex(); }

    template <typename T, typename T_index, int compression_level>
    bool SparseMatrix<T, T_index, compression_level>::InnerIterator::operator!=(const InnerIterator& other) { return currentIndex != other.getIndex(); }

    template <typename T, typename T_index, int compression_level>
    bool SparseMatrix<T, T_index, compression_level>::InnerIterator::operator<(const InnerIterator& other) { return currentIndex < other.getIndex(); }

    template <typename T, typename T_index, int compression_level>
    bool SparseMatrix<T, T_index, compression_level>::InnerIterator::operator>(const InnerIterator& other) { return currentIndex > other.getIndex(); }

    template <typename T, typename T_index, int compression_level>
    uint64_t SparseMatrix<T, T_index, compression_level>::InnerIterator::getIndex() { return index; }

    template <typename T, typename T_index, int compression_level>
    bool SparseMatrix<T, T_index, compression_level>::InnerIterator::atBeginningOfRun() { return atFirstIndex; }

    template <typename T, typename T_index, int compression_level>
    void SparseMatrix<T, T_index, compression_level>::InnerIterator::reset() {
        currentIndex = data;

        goToColumn(0);

        value = (T*)(currentIndex);
        currentIndex = (char*)(currentIndex)+valueWidth;

        // Read in the width of this run's indices and go to first index
        newIndexWidth = *(uint8_t*)(currentIndex);
        currentIndex = (char*)(currentIndex)+1;
    }

    template <typename T, typename T_index, int compression_level>
    uint64_t SparseMatrix<T, T_index, compression_level>::InnerIterator::operator++(int) {

        uint64_t newIndex = interpretPointer(newIndexWidth);

        // If newIndex is 0 and not the first index, then the index is a delimitor
        if (newIndex == 0 && !firstIndex) {

            // Value is the first index of the run
            value = (T*)(currentIndex);
            currentIndex = (char*)(currentIndex)+valueWidth;

            // newIndexWidth is the second value in the run
            newIndexWidth = *(uint8_t*)(currentIndex);
            currentIndex = (char*)(currentIndex)+1;

            // update currentCol to the next column
            while (currentIndex > getColumnAddress(currentCol + 1)) {
                currentCol++;
            }


            // std::cout << "currentIndex: " << currentIndex << std::endl;
            // std::cout << "endOfCol: " << endOfCol << std::endl;

            // if (currentIndex >= endOfCol) {
            //     exit(1);
            // }

            // Make index 0 as it is a new run
            memset(&index, 0, 8);

            // Returns the first index of the run
            index = interpretPointer(newIndexWidth);

            // std::cout << "index: " << index << std::endl;

            atFirstIndex = true;
            return index;
        }

        firstIndex = false;
        atFirstIndex = false;

        // std::cout << "newIndex: " << newIndex << std::endl;

        // Depending on if the CSF::SparseMatrix is at compression level 2 or 3, we handle the index differently
        // Compression level 3 is postive delta encoded, so we return the sum of the current index and the previous ones
        if constexpr (compression_level == 2) {
            index = newIndex;
            return newIndex;
        }
        else
            return index += newIndex;
    }

    template <typename T, typename T_index, int compression_level>
    char* SparseMatrix<T, T_index, compression_level>::InnerIterator::getColumn(uint64_t column) {
        // TODO: optimize this function

        // Reseets InnerIterator to the beginning and sends it to the corresponding column
        InnerIterator it = *this;
        it.index = 0;
        it.goToColumn(column);
        it.currentIndex = (char*)(it.currentIndex) + 1;
        it.value = it.interpretPointer(it.valueWidth);
        char* columnData = (char*)calloc(it.numRows, sizeof(T));

        if (numColumns != 1)
            it.endOfCol = (char*)(data)+*((uint64_t*)(data)+META_DATA_SIZE + ((column + 1) * sizeof(uint64_t)));

        // copy data into new array
        while (it) {
            it++;
            columnData[it.index] = value;
        }

        return columnData;
    }

    // template <typename T, typename T_index, int compression_level>
    // CSF::InnerIterator<T, T_index, compression_level> SparseMatrix<T, T_index, compression_level>::InnerIterator::getColumn(uint64_t column) {
    //     InnerIterator* it = new InnerIterator(*this); //Creates a shallow copy of the InnerIterator
    //     it.goToColumn(column);
    //     it.setEnd(goToColumn(column + 1));

    //     return *it;
    // }

    template <typename T, typename T_index, int compression_level>
    void SparseMatrix<T, T_index, compression_level>::InnerIterator::setRunValue(T newValue) { *value = newValue; }

    template <typename T, typename T_index, int compression_level>
    void* SparseMatrix<T, T_index, compression_level>::InnerIterator::getColumnAddress(uint64_t column) {
        //! Check for out of bounds col?
        // move data to desired column pointer, dereference it, and add it to the data pointer to go to desired column
        return (void*)((char*)data + *((uint64_t*)((char*)data + META_DATA_SIZE + (column * sizeof(uint64_t)))));
    }

    template <typename T, typename T_index, int compression_level>
    void SparseMatrix<T, T_index, compression_level>::InnerIterator::goToColumn(int column) {
        currentIndex = getColumnAddress(column);
        currentCol = column;
    }

    template <typename T, typename T_index, int compression_level>
    int SparseMatrix<T, T_index, compression_level>::InnerIterator::compareAddress(void* address) {

        if (currentIndex < address) {
            return -1;
        }
        else if (currentIndex == address) {
            return 0;
        }

        //else return greater than
        return 1;
    }


    // ---------------- Private Methods ---------------- //

    template <typename T, typename T_index, int compression_level>
    void SparseMatrix<T, T_index, compression_level>::InnerIterator::readMetaData() {

        //uint32_t params[NUM_META_DATA];
        memcpy(&metadata, currentIndex, META_DATA_SIZE);


        // metadata[0] compression type
        // metadata[1] row type
        // metadata[2] column type
        // metadata[3] value type
        // metadata[4] # of rows
        // metadata[5] # of columns
        // metadata[6] # of nonzeros

        valueWidth = metadata[3] & 0xF;
        // std::cout << "valueWidth: " << (int)valueWidth << std::endl;
        numRows = metadata[4];
        numColumns = metadata[5];
    }

    template <typename T, typename T_index, int compression_level>
    void SparseMatrix<T, T_index, compression_level>::InnerIterator::readFile(const char* filePath) {
        FILE* file = fopen(filePath, "rb");

        // Find end of file and allocate size
        fseek(file, 0, SEEK_END);
        int sizeOfFile = ftell(file);
        data = (char*)malloc(sizeof(char*) * sizeOfFile);

        // Read file into memory
        fseek(file, 0, SEEK_SET);
        fread(data, sizeOfFile, 1, file);
        fclose(file);

        currentIndex = data;
    }

    template <typename T, typename T_index, int compression_level>
    uint64_t SparseMatrix<T, T_index, compression_level>::InnerIterator::interpretPointer(int width) {

        uint64_t newIndex = 0;

        // Case statement takes in 1,2,4, or 8 otherwise the width is invalid
        switch (width) {
        case 1:
            newIndex = (uint64_t)(*(uint8_t*)(currentIndex));
            break;
        case 2:
            newIndex = (uint64_t)(*(uint16_t*)(currentIndex));
            break;
        case 4:
            newIndex = (uint64_t)(*(uint32_t*)(currentIndex));
            break;
        case 8:
            newIndex = (uint64_t)(*(uint64_t*)(currentIndex));
            break;
        default:
            if (endOfCol == currentIndex) {
                std::cerr << "Invalid width: " << width << std::endl;
                exit(-1);
            }

            break;
        }
        currentIndex = (char*)(currentIndex)+width;
        return newIndex;
    }


    //** ------------------------------------------------------------------------------------------------------------------ **//
    //** ----------------------------------------------- InnerIterator Class (1) ----------------------------------------------- **//
    //** ------------------------------------------------------------------------------------------------------------------ **//


    // ---------------- Public Methods ---------------- //
}