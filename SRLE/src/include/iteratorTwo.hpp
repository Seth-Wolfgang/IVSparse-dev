    template <typename T>
    class Iterator {

    private:
        uint64_t index = 0;
        uint32_t valueWidth;
        uint32_t numRows;
        uint32_t numColumns;
        uint8_t indexWidth;
        void* data;
        void* endOfData;
        void* currentIndex; 
        T value;
        bool firstIndex = true;


        void goToColumn(int column) {
            //20 bytes into the file, the column pointers are stored. Each column pointer is 8 bytes long so we can
            //multiply the column number by 8 to get the offset of the column pointer we want.
            //columns are 0 indexed 

            //TODO: implemet a way of checking if currentIndex points to next column
            //TODO: optimize this function

            currentIndex = static_cast<char*>(data) + 20 + 8 * column;
            // currentIndex = static_cast<char*>(currentIndex) + 8 * column;

            uint64_t temp;
            memcpy(&temp, currentIndex, 8);

            //We can use currentIndex to get the address of the column we want and avoid a temporary variable.
            currentIndex = static_cast<char*>(data) + temp;
        }

    public:

        /**
         * @brief Construct a new CSFiterator object
         *
         * @param filePath
         */

        Iterator(CSF::SparseMatrix& matrix) {
            data = matrix.getData();
            endOfData = matrix.getEnd();
            currentIndex = data;

            // read first 20 bytes of fileData put it into params -> metadata
            uint32_t params[5];

            memcpy(&params, currentIndex, 20);
            indexWidth = params[0];
            numRows = params[3];
            numColumns = params[4];

            //Skips metadata and goes to first column
            currentIndex = static_cast<char*>(currentIndex) + 20;
            goToColumn(0);

            //Insures the matrix is not empty
            assert(currentIndex < endOfData);

            // valueWidth is set and the first value is read in
            valueWidth = params[2];
            value = interpretPointer(valueWidth);

            // Read in the width of this run's indices and go to first index
            currentIndex = static_cast<char*>(currentIndex) + 1;
        }

        Iterator(const char* filePath) {
            readFile(filePath);

            // read first 28 bytes of fileData put it into params -> metadata
            uint32_t params[8];

            memcpy(&params, currentIndex, 20);
            currentIndex = static_cast<char*>(currentIndex) + 20;

            // valueWidth is set and the first value is read in
            valueWidth = params[4];
            value = interpretPointer(valueWidth);
            goToColumn(0);

            // Read in the width of this run's indices and go to first index
            currentIndex = static_cast<char*>(currentIndex) + 1;
        }

        /**
         * @brief Returns the value of the run.
         *
         * @return T&
         */

        const T& operator * () { return value; };

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

        uint64_t operator++(int) {
            index = interpretPointer(indexWidth);

            // If newIndex is 0 and not the first index, then the index is a delimitor
            if (index == 0 && !firstIndex) {
                // Value is the first index of the run
                value = interpretPointer(valueWidth);

                // newIndexWidth is the second value in the run
                currentIndex = static_cast<char*>(currentIndex) + 1;

                // Returns the first index of the run
                index = interpretPointer(indexWidth);
                return index;
            }

            // Returns the next index of the run for positive delta encoded runs
            firstIndex = false;
            return index;
        }

        /**
         * @brief Check if the iterator is at the end of the the data
         *
         * @return true
         * @return false
         */

        operator bool() { return endOfData != currentIndex; }
    
    private:
        /**
         * @brief Read a file into memory
         *
         * @param filePath
         */

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
                    cerr << "Invalid width: " << width << std::endl;
                    exit(-1);
                }

                break;
            }
            currentIndex = static_cast<char*>(currentIndex) + width;
            return newIndex;
        }

    }; // end of iterator

