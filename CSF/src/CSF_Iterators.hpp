#pragma once
# define META_DATA_SIZE 28

namespace CSF {    
template <typename T, typename indexType, int compressionLevel>
    class Iterator {

    private:
        uint64_t index = 0;
        uint32_t valueWidth;
        uint32_t numRows;
        uint32_t numColumns;
        uint8_t newIndexWidth;
        void* data;
        void* endOfData;
        void* currentIndex;
        T* value;
        bool firstIndex = true; 
        bool atFirstIndex = true;
        uint32_t metadata[7];

    public:

        /**
         * @brief Construct a new CSFiterator object using a CSF::SparseMatrix
         *
         * @param filePath
         */

        Iterator(CSF::SparseMatrix<T, indexType, compressionLevel>& matrix) {

            //Sets the beginnign and end of the data
            data = matrix.beginPtr();
            endOfData = matrix.endPtr();
            currentIndex = data;

            //Reads in the metadata
            readMetaData();

            //Skips metadata and goes to first column
            currentIndex = static_cast<char*>(currentIndex) + META_DATA_SIZE;
            goToColumn(0);

            //Insures the matrix is not empty
            assert(currentIndex < endOfData);

            value = static_cast<T*>(currentIndex);
            currentIndex = static_cast<char*>(currentIndex) + valueWidth;

            // Read in the width of this run's indices and go to first index
            newIndexWidth = *static_cast<uint8_t*>(currentIndex);
            currentIndex = static_cast<char*>(currentIndex) + 1;

            // std::cout << "value: " << value << std::endl;
            // std::cout << "newIndexWidth: " << (int)newIndexWidth << std::endl;
        }

        /**
         * @brief Construct a new Iterator object using a file
         * 
         * @param filePath 
         */

        Iterator(const char* filePath) {
            readFile(filePath);

            // read first 28 bytes of fileData put it into params -> metadata
            uint32_t params[8];

            memcpy(&params, currentIndex, META_DATA_SIZE);
            currentIndex = static_cast<char*>(currentIndex) + META_DATA_SIZE;

            // valueWidth is set and the first value is read in
            valueWidth = params[4];
            goToColumn(0);

            value = static_cast<T*>(currentIndex);
            currentIndex = static_cast<char*>(currentIndex) + valueWidth;

            // Read in the width of this run's indices and go to first index
            newIndexWidth = *static_cast<uint8_t*>(currentIndex);
            currentIndex = static_cast<char*>(currentIndex) + 1;

            // std::cout << "value: " << value << std::endl;
            // std::cout << "newIndexWidth: " << (int)newIndexWidth << std::endl;
        }

        /**
         * @brief Reads in the metadata from the file
         * 
         */
        uint32_t* getMetaData() {
            return metadata;
        }

        /**
         * @brief Getter for matrix data
         * 
         *
        */
        void* getData() { return data; }

        /**
         * @brief Returns the value of the run.
         *
         * @return T&
         */

        void* getEnd() {return endOfData; }

        T& operator * () {
            return *value;
        };

        /**
         * @brief Equality operator of this iterator and another iterator
         *
         * @param other
         * @return true
         * @return false
         */

        bool operator == (const Iterator& other) {
            return currentIndex == other.getIndex();
        }

        /**
         * @brief Inequality operator of this iterator and another iterator
         *
         * @param other
         * @return true
         * @return false
         */

        bool operator != (const Iterator& other) {
            return currentIndex != other.getIndex();
        }

        /**
         * @brief Less than operator of this iterator and another iterator
         *
         * @param other
         * @return true
         * @return false
         */

        bool operator < (const Iterator& other) {
            return currentIndex < other.getIndex();
        }

        /**
         * @brief Greater than operator of this iterator and another iterator
         *
         * @param other
         * @return true
         * @return false
         */

        bool operator > (const Iterator& other) {
            return currentIndex > other.getIndex();
        }

        /**
         * @brief Getter for the index of the iterator
         *
         */

        uint64_t getIndex() { return index; }

        /**
         * @brief TODO: I do not want this in the final product
         *
         * @return true
         * @return false
         */

        bool atBeginningOfRun() { return atFirstIndex; }

        /**
         * @brief Increment operator for the iterator
         * 
         * This handles the basic usage of the iterator. The iterator will go through each index of the CSF::SparseMatrix and return the index of where it is.
         * The iterator will change value when it hits the assigned delimitor as set by the CSF::SparseMatrix. Each delimitor is a collection of 0s that are the size
         * of the index. Only the first index may be a zero, in which case the iterator will return a zero, but not recognize it as a delimitor.
         * 
         * 
         * @return uint64_t
         */

        uint64_t operator++(int) {
            uint64_t newIndex = interpretPointer(newIndexWidth);

            // If newIndex is 0 and not the first index, then the index is a delimitor
            if (newIndex == 0 && !firstIndex) {

                // Value is the first index of the run
                value = static_cast<T*>(currentIndex);
                currentIndex = static_cast<char*>(currentIndex) + valueWidth;

                // newIndexWidth is the second value in the run
                newIndexWidth = *static_cast<uint8_t*>(currentIndex);
                currentIndex = static_cast<char*>(currentIndex) + 1;

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
            if constexpr (compressionLevel == 2)
                return newIndex;
            else
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
         * @brief Gets the data of a specified column (WIP)
         *
         * @param column
         * @return char*
         */

         char* getColumn(uint64_t column) {
             //TODO: optimize this function

             //Reseets iterator to the beginning and sends it to the corresponding column
             Iterator it = *this;
             it.index = 0;
             it.goToColumn(column);
             it.currentIndex = static_cast<char*>(it.currentIndex) + 1;
             it.value = it.interpretPointer(it.valueWidth);
             char* columnData = (char*)calloc(it.numRows, sizeof(T));

             if (numColumns != 1) it.endOfData = static_cast<char*>(data) + *(static_cast<uint64_t*>(data) + META_DATA_SIZE + ((column + 1) * 8));

             //copy data into new array
             while (it) {
                 it++;
                 columnData[it.index] = value;
             }

             return columnData;
         }

         /**
          * @brief Returns an iterator to the specified column (WIP)
          *
          * @param column
          * @return CSF::Iterator<T>
          */

        // CSF::Iterator<T, indexType, compressionLevel> getColumn(uint64_t column) {
        //     Iterator* it = new Iterator(*this); //Creates a shallow copy of the iterator
        //     it.goToColumn(column);
        //     it.setEnd(goToColumn(column + 1));

        //     return *it;
        // }


        /**
         * @brief Sets a new value at the current run. NOTE: This will set the value for all indices in the run
         *
         * @param newValue
         */

        void setRunValue(T newValue) {
            *value = newValue;
        }

        /**
         * @brief Get the address of a specified column
         *
         * @param column
         * @return void*
         */

        inline void* getColumnAddress(uint64_t column) {
            /*
            char* data + METADATASIZE + column * sizeof(uint64_t) goes to the column pointer specified
            Why char*? -> so we only add 1 * the rest of the sum of metadatasize and column * sizeof(uint64_t)
            
            cast to uint64_t so that we grab 8 bytes from memory.
            dereference the pointer to get the value of the pointer.
            Then we add temp to data to go to the column we need. Data is casted to char* because we only want to add 1 * temp.
            then we convert to void* so we have the memory address.

            */
            //  uint64_t temp = *((uint64_t*)((char*)data + METADATASIZE + (column * sizeof(uint64_t))))
            return (void*)((char*)data +  *((uint64_t*)((char*)data + META_DATA_SIZE + (column * sizeof(uint64_t)))));
        }

        /**
         * @brief Sends the iterator to a specific column.
         * @param column
         */

        void goToColumn(int column) {
            currentIndex = getColumnAddress(column);
        }

        /**
         * @brief Compares the address of the iterator with a given address. 
         * NOTE: This should only be used to compare with an iterator pointing
         * to the same CSF::SparseMatrix.
         *
         * address will be less than currentIndex when we need a true.
         * This is becasue operator++ will be set to the first index of a run
         * and address will point to the first byte of the value
         *
         * @param address
         * @return
         */

        bool compareAddress(void* address) {
            return currentIndex >= address;
        }


    private:
        /**
         * @brief Read a file into memory
         *
         * @param filePath
         */

        void readMetaData(){
            uint32_t params[7];
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

        inline void readFile(const char* filePath) {
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
            endOfData = data + sizeOfFile;
        }

        /**
         * @brief Read in the next index from the file based on a variable width
         *
         * @param width
         * @return uint64_t
         */

        inline uint64_t interpretPointer(int width) {
            uint64_t newIndex = 0;

            // Case statement takes in 1,2,4, or 8 otherwise the width is invalid
            switch (width) {
            case 1:
                newIndex = static_cast<uint64_t>(*static_cast<uint8_t*>(currentIndex));
                break;
            case 2:
                newIndex = static_cast<uint64_t>(*static_cast<uint16_t*>(currentIndex));
                break;
            case 4:
                newIndex = static_cast<uint64_t>(*static_cast<uint32_t*>(currentIndex));
                break;
            case 8:
                newIndex = static_cast<uint64_t>(*static_cast<uint64_t*>(currentIndex));
                break;
            default:
                if (endOfData == currentIndex) {
                    std::cerr << "Invalid width: " << width << std::endl;
                    exit(-1);
                }

                break;
            }
            // std::cout << "newIndex: " << newIndex << std::endl;
            currentIndex = static_cast<char*>(currentIndex) + width;
            return newIndex;
        }

        /**
         * @brief Set the ending address of the iterator
         *
         * @param end
         */

        void setEnd(void* end) {
            endOfData = end;
        }


    }; // end of iterator
}
