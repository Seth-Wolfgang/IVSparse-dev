/**
 * @file CSFIterator.cpp
 * @author Seth Wolfgang
 * @brief Iterator for CSF compressed matrices. 
 * @version 0.6
 * @date 2023-01-11
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "../include/CPP_Lib.hpp"

using namespace std;

template<typename T>
class CSFIterator {

    private:
        uint64_t index = 0;
        uint32_t valueWidth;   
        uint8_t newIndexWidth; 
        char* fileData;
        void* endOfData;
        void* currentIndex;
        T value;
        bool firstIndex = true;


    /**
     * @brief Read a file into memory
     * 
     * @param filePath 
     */

    inline void readFile(const char* filePath){
        FILE* file = fopen(filePath, "rb");
        
        //Find end of file and allocate size
        fseek(file, 0, SEEK_END);
        int sizeOfFile = ftell(file);
        fileData = (char*)malloc(sizeof(char*)*sizeOfFile);

        //Read file into memory
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

    inline uint64_t interpretPointer(int width){
        uint64_t newIndex = 0;

        //Case statement takes in 1,2,4, or 8 otherwise the width is invalid
        switch (width){
            case 1:
                newIndex = static_cast<uint64_t>(*static_cast<uint8_t*>(currentIndex));
                break;
            case 2:
                newIndex =  static_cast<uint64_t>(*static_cast<uint16_t*>(currentIndex));
                break;
            case 4:
                newIndex =  static_cast<uint64_t>(*static_cast<uint32_t*>(currentIndex));
                break;
            case 8:
                newIndex =  static_cast<uint64_t>(*static_cast<uint64_t*>(currentIndex));
                break;
            default:
                cout << "Invalid width: " << width << endl;
                exit(-1);
                break;
        }

        currentIndex = static_cast<char*>(currentIndex) + width;
        return newIndex;
    }

    public:

    /**
     * @brief Construct a new CSFiterator object
     * 
     * @param filePath 
     */

    CSFIterator(const char* filePath) {
        readFile(filePath);

        //read first 28 bytes of fileData put it into params -> metadata
        uint32_t params[8];
        memcpy(&params, currentIndex, 20); 
        currentIndex = static_cast<char*>(currentIndex) + 20;

        //valueWidth is set and the first value is read in
        valueWidth    = params[4];
        value = interpretPointer(valueWidth);  

        //Read in the width of this run's indices and go to first index
        newIndexWidth = *static_cast<uint8_t*>(currentIndex);
        currentIndex = static_cast<char*>(currentIndex) + 1;
        
        cout << "value: " << value << endl;
        cout << "newIndexWidth: " << (int)newIndexWidth << endl;
    }

    /**
     * @brief Returns the value of the run.
     * 
     * @return T& 
     */

    T& operator * () {return value;}; 

    /**
     * @brief Increment the iterator
     * 
     * @return uint64_t 
     */

    uint64_t operator++() {
        uint64_t newIndex = interpretPointer(newIndexWidth); 
       
        //If newIndex is 0 and not the first index, then the index is a delimitor
        if(newIndex == 0 && !firstIndex){
            //Value is the first index of the run
            value = interpretPointer(valueWidth); 

            //newIndexWidth is the second value in the run
            newIndexWidth = *static_cast<uint8_t*>(currentIndex);
            currentIndex = static_cast<char*>(currentIndex) + 1;
            
            memset(&index, 0, 8);

            //Returns the first index of the run
            index = interpretPointer(newIndexWidth);
            firstIndex = true;
            return index;
        }

        //Returns the next index of the run for positive delta encoded runs
        firstIndex = false;
        return index += newIndex;
    }


    /**
     * @brief Check if the iterator is at the end of the the data
     * 
     * @return true 
     * @return false 
     */

    operator bool() { return endOfData != currentIndex;}

};