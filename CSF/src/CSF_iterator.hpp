#pragma once

#include <iostream>

using std::cout;
using std::endl;

namespace CSF {


// CSC iterator (compression level 1)
template <typename T, typename T_index>
class SparseMatrix<T, T_index, 1> {
    public:
    class Iterator {
        public:
        int hi = 3;

        Iterator() {
            cout << "hi skyler" << endl;
        }
    };
};

// General case iterator (compression levels 2 and 3)
template <typename T, typename T_index, int compression_level>
class SparseMatrix<T, T_index, compression_level>::Iterator {

    private:
        uint64_t index = 0;
        uint32_t valueWidth;
        uint32_t numRows;
        uint32_t numColumns;
        uint8_t newIndexWidth;
        void *data;
        void *endOfData;
        void *currentIndex;
        void *tempPointer;
        T value;
        bool firstIndex = true;

        /**
         * @brief Get address of a specified column
         * @param column
         */

        void goToColumn(int column)
        {
            // 20 bytes into the file, the column pointers are stored. Each column pointer is 8 bytes long so we can
            // multiply the column number by 8 to get the offset of the column pointer we want.
            // columns are 0 indexed

            // TODO: implemet a way of checking if currentIndex points to next column

            currentIndex = static_cast<char *>(data) + 20 + 8 * column;
            memcpy(currentIndex, currentIndex, 8);
            currentIndex = static_cast<char *>(data) + *static_cast<char *>(currentIndex);
        }

    public:
        /**
         * @brief Construct a new CSFiterator object
         *
         * @param filePath
         */

        int hi = 4;
        Iterator() {
            std::cout << "hello" << std::endl;
        }

        Iterator(CSF::SparseMatrix<T, T_index, compression_level> &matrix)
        {
            data = matrix.beginPtr();
            endOfData = matrix.endPtr();
            currentIndex = data;

            // read first 28 bytes of fileData put it into params -> metadata
            uint32_t params[5];

            memcpy(&params, currentIndex, 20);
            numRows = params[3];
            numColumns = params[4];

            currentIndex = static_cast<char *>(currentIndex) + 20;
            goToColumn(0);

            // valueWidth is set and the first value is read in
            valueWidth = params[2];
            value = interpretPointer(valueWidth);

            // Read in the width of this run's indices and go to first index
            newIndexWidth = *static_cast<uint8_t *>(currentIndex);
            currentIndex = static_cast<char *>(currentIndex) + 1;

            // cout << "value: " << value << endl;
            // cout << "newIndexWidth: " << (int)newIndexWidth << endl;
        }

        Iterator(const char *filePath)
        {
            readFile(filePath);

            // read first 28 bytes of fileData put it into params -> metadata
            uint32_t params[8];

            memcpy(&params, currentIndex, 20);
            currentIndex = static_cast<char *>(currentIndex) + 20;

            // valueWidth is set and the first value is read in
            valueWidth = params[4];
            value = interpretPointer(valueWidth);
            goToColumn(0);

            // Read in the width of this run's indices and go to first index
            newIndexWidth = *static_cast<uint8_t *>(currentIndex);
            currentIndex = static_cast<char *>(currentIndex) + 1;

            // cout << "value: " << value << endl;
            // cout << "newIndexWidth: " << (int)newIndexWidth << endl;
        }

        /**
         * @brief Returns the value of the run.
         *
         * @return T&
         */

        const T &operator*() { return value; };
        const T getValue() { return value; }

        /**
         * @brief Getter for the index of the iterator
         *
         */
        uint64_t getIndex() { return index; }

        /**
         * @brief Increment the iterator
         *
         * @return uint64_t
         */

        uint64_t operator++(int)
        {
            uint64_t newIndex = interpretPointer(newIndexWidth);

            // cout << "newIndex: " << newIndex << endl;
            // cout << "width: " << (int)newIndexWidth << endl;
            // cout << "value " << value << endl << endl;

            // If newIndex is 0 and not the first index, then the index is a delimitor
            if (newIndex == 0 && !firstIndex)
            {
                // Value is the first index of the run
                value = interpretPointer(valueWidth);

                // newIndexWidth is the second value in the run
                newIndexWidth = *static_cast<uint8_t *>(currentIndex);
                currentIndex = static_cast<char *>(currentIndex) + 1;

                memset(&index, 0, 8);

                cout << "new value " << value << endl;
                cout << "new width: " << (int)newIndexWidth << endl;

                // Returns the first index of the run
                index = interpretPointer(newIndexWidth);
                // (index == 0) ? (firstIndex = true) : (firstIndex = false);
                // firstIndex = true;
                return index;
            }

            // Returns the next index of the run for positive delta encoded runs
            firstIndex = false;
            return index += newIndex;
        }

        /**
         * @brief Check if the iterator is at the end of the the data
         *
         * @return true
         * @return false
         */

        operator bool() { return endOfData != currentIndex; }

        /**
         * @brief Gets the data of a specified column
         *
         * @param column
         * @return char*
         */

        char *getColumn(uint64_t column)
        {
            // TODO: optimize this function
            Iterator it = *this;
            it.index = 0;
            it.goToColumn(column);
            it.currentIndex = static_cast<char *>(it.currentIndex) + 1;
            it.value = it.interpretPointer(it.valueWidth);
            char *columnData = (char *)calloc(it.numRows, sizeof(T));

            if (numColumns != 1)
                it.endOfData = static_cast<char *>(data) + *(static_cast<uint64_t *>(data) + 20 + ((column + 1) * 8));

            // copy data into new array
            while (it)
            {
                it++;
                columnData[it.index] = value;
            }

            return columnData;
        }

    private:
        /**
         * @brief Read a file into memory
         *
         * @param filePath
         */

        inline void readFile(const char *filePath)
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

        /**
         * @brief Read in the next index from the file based on a variable width
         *
         * @param width
         * @return uint64_t
         */

        inline uint64_t interpretPointer(int width)
        {
            uint64_t newIndex = 0;

            // Case statement takes in 1,2,4, or 8 otherwise the width is invalid
            switch (width)
            {
            case 1:
                newIndex = static_cast<uint64_t>(*static_cast<uint8_t *>(currentIndex));
                break;
            case 2:
                newIndex = static_cast<uint64_t>(*static_cast<uint16_t *>(currentIndex));
                break;
            case 4:
                newIndex = static_cast<uint64_t>(*static_cast<uint32_t *>(currentIndex));
                break;
            case 8:
                newIndex = static_cast<uint64_t>(*static_cast<uint64_t *>(currentIndex));
                break;
            default:

                if (endOfData == currentIndex)
                {
                    cout << "Value: " << value << endl;
                    cout << static_cast<int>(*static_cast<uint8_t *>(currentIndex)) << endl;
                    cout << "Invalid width: " << width << endl;
                    exit(-1);
                }

                break;
            }
            // cout << "newIndex: " << newIndex << endl;
            currentIndex = static_cast<char *>(currentIndex) + width;
            return newIndex;
        }

    // end of iterator
};

}