
#pragma once
#define META_DATA_SIZE 28

namespace CSF {
    template <typename T, typename IndexType, 1>
    class Iterator<T, IndexType, 1> {

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

        Iterator(CSF::SparseMatrix<T, IndexType, 3>& matrix) {

            /**
             * @brief Construct a new CSFiterator object using a CSF::SparseMatrix
             *
             * @param filePath
             */

            Iterator(CSF::SparseMatrix<T, indexType, compressionLevel>&matrix) {

                //Sets the beginnign and end of the data
                data = matrix.beginPtr();
                endOfData = matrix.endPtr();
                currentIndex = data;

                //Reads in the metadata
                readMetaData();

                //Skips metadata and goes to first column
                currentIndex = static_cast<char*>(currentIndex) + META_DATA_SIZE;
                goToColumn(0);

                // To make sure the matrix isn't empty or in some way invalid
                // assert(currentIndex < endOfData);
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

                // Sets the metadata based on the file
                readMetaData();

                //Uses the column pointer to go to the first column
                goToColumn(0);
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

            void* getEnd() { return endOfData; }

            /**
             * @brief Returns the value of the run.
             *
             * @return 
             */

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

            bool operator == (const Iterator & other) {
                return currentIndex == other.getIndex();
            }

            /**
             * @brief Inequality operator of this iterator and another iterator
             *
             * @param other
             * @return true
             * @return false
             */

            bool operator != (const Iterator & other) {
                return currentIndex != other.getIndex();
            }

            /**
             * @brief Less than operator of this iterator and another iterator
             *
             * @param other
             * @return true
             * @return false
             */

            bool operator < (const Iterator & other) {
                return currentIndex < other.getIndex();
            }

            /**
             * @brief Greater than operator of this iterator and another iterator
             *
             * @param other
             * @return true
             * @return false
             */

            bool operator > (const Iterator & other) {
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

        }
    }
}