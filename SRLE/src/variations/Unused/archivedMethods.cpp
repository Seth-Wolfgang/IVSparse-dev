   template<typename indexType> 
    const uint64_t operator++() { 
        //todo through an exception if we request something smaller than the size of the index
        uint64_t newIndex = 0; //get rid of in future versions
        memcpy(&newIndex, arrayPointer, newIndexWidth);
        arrayPointer += newIndexWidth;
        sum += value;
        if(newIndex == 0 && index != 0){ //change that
            memcpy(&value, arrayPointer, valueWidth);
            arrayPointer += valueWidth; 
            memcpy(&newIndexWidth, arrayPointer, 1);
            arrayPointer++;
            cout << endl << "value: " << value << endl;
            cout << "newIndexWidth: " << *(uint8_t*)newIndexWidth << endl;
            memset(&index, 0, 8);
            memcpy(&index, arrayPointer, newIndexWidth);
        }
        return index += newIndex;
    }

        /**
     * @brief Reads in the file and stores it in a void* array
     * 
     * @param filePath 
     */

    inline void readFile(string filePath){ 
        ifstream fileStream;

        //open file
        fileStream.open(filePath, ios::binary | ios::out);
        fileStream.seekg(0, ios::end);

        //get size of file
        int sizeOfFile = fileStream.tellg();
        matrixData = (char*)malloc(sizeof(char*)*sizeOfFile);
        fileStream.seekg(0, ios::beg);

        //read file into array
        fileStream.read(matrixData, sizeOfFile);
        fileStream.close();

        //set array pointer to start of array
        //and set end to end of array
        arrayPointer = matrixData;
        end = matrixData + sizeOfFile;
    }

        const uint64_t operator++() {
             uint64_t newIndex = interpretPointer(); 
            
             printf("newIndexWidth: %d\n", newIndexWidth);
             cout << "arrayPointer position: " <<  ((char*)arrayPointer - matrixData) << endl; 
             printf("Array Pointer Value: %d\n", *static_cast<uint8_t*>(arrayPointer));
             printf("Prev Array Pointer Value: %d\n", *static_cast<uint8_t*>(arrayPointer-1));
             cout << "Value: " << value << endl;
             cout << "newIndex: " << newIndex << endl << endl;
        
             if(newIndex == 0){
                 cout << " flag !" << endl;
                 memcpy(&value, arrayPointer, valueWidth);
                 arrayPointer += valueWidth; 
                 cout << "arrayPointer position: " <<  ((char*)arrayPointer - matrixData) << endl; 
        
                 memcpy(&newIndexWidth, arrayPointer, 1);
                 arrayPointer++;
                 
                 cout << endl << "value: " << value << endl;
                 cout << "newIndexWidth: " << static_cast<int>(newIndexWidth) << endl;
                 
                 memset(&index, 0, 8);
                 memcpy(&index, arrayPointer, newIndexWidth);
             }
             cout << "NewIndex before return: " << newIndex << endl;
             return index += newIndex;
    }
