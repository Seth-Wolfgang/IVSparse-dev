#pragma once
#define META_DATA_SIZE 28 // number of bytes in metadata (7 * 4)
#define NUM_META_DATA 7   // number of metadata values

namespace CSF
{
    //** ------------------------------------------------------------------------------------------------------------------ **//
    //** --------------------------------------------- Iterator Class (2 & 3) --------------------------------------------- **//
    //** ------------------------------------------------------------------------------------------------------------------ **//

    // ---------------- Iterator Constructors ---------------- //

    template <typename T, typename T_index, int compression_level>
    SparseMatrix<T, T_index, compression_level>::Iterator::Iterator(CSF::SparseMatrix<T, T_index, compression_level> &matrix)
    {
        data = matrix.beginPtr();
        endOfData = matrix.endPtr();

        // set to begining of data
        currentIndex = data;

        // Reads in the metadata (initializes class variables)
        readMetaData();

        // Skips metadata and goes to first column
        currentIndex = (void *)((char *)(currentIndex) + META_DATA_SIZE); // ?goes to first col pointer?
        goToColumn(0);                                                    // skips past col_p and delim to the start of actual data

        // Insures the matrix is not empty
        assert(currentIndex < endOfData);

        value = (T *)(currentIndex);
        currentIndex = (char *)(currentIndex) + valueWidth;

        // Read in the width of this run's indices and go to first index
        newIndexWidth = *(uint8_t *)(currentIndex);
        currentIndex = (char *)(currentIndex) + 1;
    }

    template <typename T, typename T_index, int compression_level>
    SparseMatrix<T, T_index, compression_level>::Iterator::Iterator(const char *filePath)
    {
        readFile(filePath);

        // read first 28 bytes of fileData put it into params -> metadata
        uint32_t params[NUM_META_DATA];

        memcpy(&params, currentIndex, META_DATA_SIZE);
        currentIndex = (char *)(currentIndex) + META_DATA_SIZE;

        // valueWidth is set and the first value is read in
        valueWidth = params[4];
        goToColumn(0);

        value = (T *)(currentIndex);
        currentIndex = (char *)(currentIndex) + valueWidth;

        // Read in the width of this run's indices and go to first index
        newIndexWidth = *(uint8_t *)(currentIndex);
        currentIndex = (char *)(currentIndex) + 1;
    }

    // ------------------------------- Iterator Methods ----------------------------------- //

    // ---------------- Public Methods ---------------- //

    template <typename T, typename T_index, int compression_level>
    uint32_t *SparseMatrix<T, T_index, compression_level>::Iterator::getMetaData() { return metadata; }

    template <typename T, typename T_index, int compression_level>
    void *SparseMatrix<T, T_index, compression_level>::Iterator::getData() { return data; }

    template <typename T, typename T_index, int compression_level>
    void *SparseMatrix<T, T_index, compression_level>::Iterator::getEnd() { return endOfData; }

    template <typename T, typename T_index, int compression_level>
    T &SparseMatrix<T, T_index, compression_level>::Iterator::operator*() { return *value; }

    template <typename T, typename T_index, int compression_level>
    bool SparseMatrix<T, T_index, compression_level>::Iterator::operator==(const Iterator &other) { return currentIndex == other.getIndex(); }

    template <typename T, typename T_index, int compression_level>
    bool SparseMatrix<T, T_index, compression_level>::Iterator::operator!=(const Iterator &other) { return currentIndex != other.getIndex(); }

    template <typename T, typename T_index, int compression_level>
    bool SparseMatrix<T, T_index, compression_level>::Iterator::operator<(const Iterator &other) { return currentIndex < other.getIndex(); }

    template <typename T, typename T_index, int compression_level>
    bool SparseMatrix<T, T_index, compression_level>::Iterator::operator>(const Iterator &other) { return currentIndex > other.getIndex(); }

    template <typename T, typename T_index, int compression_level>
    uint64_t SparseMatrix<T, T_index, compression_level>::Iterator::getIndex() { return index; }

    template <typename T, typename T_index, int compression_level>
    bool SparseMatrix<T, T_index, compression_level>::Iterator::atBeginningOfRun() { return atFirstIndex; }

    template <typename T, typename T_index, int compression_level>
    uint64_t SparseMatrix<T, T_index, compression_level>::Iterator::operator++(int)
    {
        uint64_t newIndex = interpretPointer(newIndexWidth);

        // If newIndex is 0 and not the first index, then the index is a delimitor
        if (newIndex == 0 && !firstIndex)
        {

            // Value is the first index of the run
            value = (T *)(currentIndex);
            currentIndex = (char *)(currentIndex) + valueWidth;

            // newIndexWidth is the second value in the run
            newIndexWidth = *(uint8_t *)(currentIndex);
            currentIndex = (char *)(currentIndex) + 1;

            // Make index 0 as it is a new run
            memset(&index, 0, 8);

            // Returns the first index of the run
            index = interpretPointer(newIndexWidth);
            atFirstIndex = true;
            return index;
        }

        firstIndex = false;
        atFirstIndex = false;

        // Depending on if the CSF::SparseMatrix is at compression level 2 or 3, we handle the index differently
        // Compression level 3 is postive delta encoded, so we return the sum of the current index and the previous ones
        if constexpr (compression_level == 2)
            return newIndex;
        else
            return index += newIndex;
    }

    template <typename T, typename T_index, int compression_level>
    char *SparseMatrix<T, T_index, compression_level>::Iterator::getColumn(uint64_t column)
    {
        // TODO: optimize this function

        // Reseets iterator to the beginning and sends it to the corresponding column
        Iterator it = *this;
        it.index = 0;
        it.goToColumn(column);
        it.currentIndex = (char *)(it.currentIndex) + 1;
        it.value = it.interpretPointer(it.valueWidth);
        char *columnData = (char *)calloc(it.numRows, sizeof(T));

        if (numColumns != 1)
            it.endOfData = (char *)(data) + *((uint64_t *)(data) + META_DATA_SIZE + ((column + 1) * sizeof(uint64_t)));

        // copy data into new array
        while (it)
        {
            it++;
            columnData[it.index] = value;
        }

        return columnData;
    }

    // template <typename T, typename T_index, int compression_level>
    // CSF::Iterator<T, T_index, compression_level> SparseMatrix<T, T_index, compression_level>::Iterator::getColumn(uint64_t column) {
    //     Iterator* it = new Iterator(*this); //Creates a shallow copy of the iterator
    //     it.goToColumn(column);
    //     it.setEnd(goToColumn(column + 1));

    //     return *it;
    // }

    template <typename T, typename T_index, int compression_level>
    void SparseMatrix<T, T_index, compression_level>::Iterator::setRunValue(T newValue) { *value = newValue; }

    template <typename T, typename T_index, int compression_level>
    void *SparseMatrix<T, T_index, compression_level>::Iterator::getColumnAddress(uint64_t column)
    {
        //! Check for out of bounds col?
        // move data to desired column pointer, dereference it, and add it to the data pointer to go to desired column
        return (void *)((char *)data + *((uint64_t *)((char *)data + META_DATA_SIZE + (column * sizeof(uint64_t)))));
    }

    template <typename T, typename T_index, int compression_level>
    void SparseMatrix<T, T_index, compression_level>::Iterator::goToColumn(int column) { currentIndex = getColumnAddress(column); }

    template <typename T, typename T_index, int compression_level>
    bool SparseMatrix<T, T_index, compression_level>::Iterator::compareAddress(void *address) { return currentIndex >= address; }

    // ---------------- Private Methods ---------------- //

    //! doesn't actually update the metadata variable?
    template <typename T, typename T_index, int compression_level>
    void SparseMatrix<T, T_index, compression_level>::Iterator::readMetaData()
    {

        uint32_t params[NUM_META_DATA];
        memcpy(&params, currentIndex, META_DATA_SIZE);

        // params[0] compression type
        // params[1] row type
        // params[2] column type
        // params[3] value type
        // params[4] # of rows
        // params[5] # of columns
        // params[6] # of nonzeros

        valueWidth = params[3] & 0xFFFF;
        numRows = params[4];
        numColumns = params[5];
    }

    template <typename T, typename T_index, int compression_level>
    void SparseMatrix<T, T_index, compression_level>::Iterator::readFile(const char *filePath)
    {
        FILE *file = fopen(filePath, "rb");

        // Find end of file and allocate size
        fseek(file, 0, SEEK_END);
        int sizeOfFile = ftell(file);
        data = (char *)malloc(sizeof(char *) * sizeOfFile);

        // Read file into memory
        fseek(file, 0, SEEK_SET);
        fread(data, sizeOfFile, 1, file);
        fclose(file);

        currentIndex = data;
        endOfData = data + sizeOfFile;
    }

    template <typename T, typename T_index, int compression_level>
    uint64_t SparseMatrix<T, T_index, compression_level>::Iterator::interpretPointer(int width)
    {
        uint64_t newIndex = 0;

        // Case statement takes in 1,2,4, or 8 otherwise the width is invalid
        switch (width)
        {
        case 1:
            newIndex = (uint64_t)(*(uint8_t *)(currentIndex));
            break;
        case 2:
            newIndex = (uint64_t)(*(uint16_t *)(currentIndex));
            break;
        case 4:
            newIndex = (uint64_t)(*(uint32_t *)(currentIndex));
            break;
        case 8:
            newIndex = (uint64_t)(*(uint64_t *)(currentIndex));
            break;
        default:
            if (endOfData == currentIndex)
            {
                std::cerr << "Invalid width: " << width << std::endl;
                exit(-1);
            }

            break;
        }
        currentIndex = (char *)(currentIndex) + width;
        return newIndex;
    }

    template <typename T, typename T_index, int compression_level>
    void SparseMatrix<T, T_index, compression_level>::Iterator::setEnd(void *end) { endOfData = end; }

    //** ------------------------------------------------------------------------------------------------------------------ **//
    //** ----------------------------------------------- Iterator Class (1) ----------------------------------------------- **//
    //** ------------------------------------------------------------------------------------------------------------------ **//

    // ---------------- Public Methods ---------------- //
}
