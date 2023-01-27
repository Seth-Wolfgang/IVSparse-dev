

namespace CSF {

    template <typename T>
    class SparseMatrix::iterator {

    private:
        uint64_t index = 0;
        uint64_t* colPointers;
        uint32_t valueWidth;
        uint8_t newIndexWidth;
        char* fileData;
        void* endOfData;
        void* currentIndex;
        T value;
        bool firstIndex = true;

        /**
         * @brief Reads in the column pointers from the data
         *
         */

        void readColumnPointers() {

            memcpy(&colPointers, currentIndex, interpretPointer(8));

            for (int i = 0; i < interpretPointer(8); i++) {
                cout << colPointers[i] << endl;
            }
        }


        /**
         * @brief Helper method for the constructor. 
         * 
         */

        void setup() {
            uint32_t params[5];

            memcpy(&params, currentIndex, 20);
            currentIndex = static_cast<char*>(currentIndex) + 20;

            // valueWidth is set and the first value is read in
            valueWidth = params[4];
            value = interpretPointer(valueWidth);

            readColumnPointers();

            // Read in the width of this run's indices and go to first index
            newIndexWidth = *static_cast<uint8_t*>(currentIndex);
            currentIndex = static_cast<char*>(currentIndex) + 1;
        }

    public:
        /**
         * @brief Construct a new CSFiterator object
         *
         * @param filePath
         */

        iterator(const CSF::SparseMatrix& matrix) {

            //Sets start and end
            currentIndex = matrix.getData();
            endOfData = matrix.getEnd();

            //General setup for the contstructor
            setup();

        }

        iterator(const CSF::SparseMatrix& matrix, int column = 0) {

            //Sets start and end
            currentIndex = matrix.getData();
            endOfData = matrix.getEnd();

            //General setup for the contstructor
            setup();

            //Skips to column specified
            readColumnPointers(column);
        }


        iterator(const char* filePath, int column = 0) {
            readFile(filePath);

            //General setup for the contstructor
            setup();

            //Skips to column specified
            readColumnPointers(column);

        }

        /**
         * @brief Returns the value of the run.
         *
         * @return T&
         */

        T& operator*() { return value; };

        /**
         * @brief Increment the iterator
         *
         * @return uint64_t
         */

        uint64_t operator++() < 3 >
        {
            uint64_t newIndex = interpretPointer(newIndexWidth);

            // cout << "newIndex: " << newIndex << endl;
            // cout << "width: " << (int)newIndexWidth << endl;
            // cout << "value " << value << endl << endl;

            // If newIndex is 0 and not the first index, then the index is a delimitor
            if (newIndex == 0 && !firstIndex) {
                // Value is the first index of the run
                value = interpretPointer(valueWidth);

                // newIndexWidth is the second value in the run
                newIndexWidth = *static_cast<uint8_t*>(currentIndex);
                currentIndex = static_cast<char*>(currentIndex) + 1;

                memset(&index, 0, 8);

                // cout << "value2 " << value << endl;
                // cout << "width2: " << (int)newIndexWidth << endl;

                // Returns the first index of the run
                index = interpretPointer(newIndexWidth);
                firstIndex = true;
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
            fileData = (char*)malloc(sizeof(char*) * sizeOfFile);

            // Read file into memory
            fseek(file, 0, SEEK_SET);
            fread(fileData, sizeOfFile, 1, file);
            fclose(file);

            currentIndex = fileData;
            endOfData = fileData + sizeOfFile;
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
                // cout << static_cast<int>(*static_cast<uint8_t*>(currentIndex)) << endl;
                cout << "Invalid width: " << width << endl;
                exit(-1);
                break;
            }

            currentIndex = static_cast<char*>(currentIndex) + width;
            return newIndex;
        }
    };

}