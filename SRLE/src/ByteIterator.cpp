//create an iterator struct
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <iterator>
#include <cstddef>
#include <fstream>
#define DELIMITER 0;

using namespace std;

class const_iterator {
    //todo:
    //clean the vocabulary
    //**does read seek?**
    //remove seek from this and refactor reads back into methods
    private:
        std::ifstream fileStream;
        int dataTypes[4] = {1, 2, 3, 4, 8};
        uint32_t magicByteSize;
        uint32_t rowType;
        uint32_t nRows;
        uint32_t colType;
        uint32_t nCols;
        uint32_t valueType;
        uint32_t oldIndexType; //should not be set to uint_32t -> store both new and old into one byte
        int newIndexType; //basically how many bytes we read, NOT ACTUALLY THE TYPE
        streampos start, end;
        int delimitor = 0;
        char* ptr; //*current* pointer -> change to current value
        
    public:
    //constructor
    //read in first few bytes for data
    
   ByteIterator(const char* filePath) {
        //read in first few bytes for data
        //set up the iterator
        uint32_t params[7];
        char* buffer; // allocate some memory (maybe?)
        fileStream.open(filePath, ios::binary);
        
        //record start and end
        start = fileStream.tellg();
        fileStream.seekg(0, ios::end); //keep this, but add a new class that reads a raw memory array
        end = fileStream.tellg();      //read whole file and append to an array
        fileStream.seekg(0, ios::beg);

        //read in the first 28 bytes -> metadata
        if (fileStream.is_open()) {
            for(int i = 0; i < 7; i++) {
                fileStream.read(buffer, 4);
                fileStream.seekg(4, ios::cur);
                params[i] = (int) *buffer;

                if(*buffer == delimitor) {
                    break;
                }
            }
            
        magicByteSize = params[0]; //change later
        rowType       = params[2];
        nRows         = params[3];
        colType       = params[4];
        nCols         = params[5];
        valueType     = params[6];
        oldIndexType  = params[6];
        std::cout << "Parameters set" << std::endl;


        }
        else {
            std::cout << "File not found" << std::endl;
        }

    }

    //NO VECTOR TYPES

    //LOOK INTO 
    //https://en.cppreference.com/w/cpp/language/partial_specialization

    //returns value - need to change this. I want it to return the value we are currently looking at
    char& operator*() const {return *ptr;}; //should return value to char, even if reading a binary file
    
    //create operator for returning current pointer value?

    //prefix increment
    //template<Typename T> //create a table and way to check data type
    ByteIterator& operator++() {
        fileStream.seekg(newIndexType);
        fileStream.read(ptr, newIndexType); //IMPORTANT -> CHECK IF THIS ITERATES BY ITSELF
        //cast?
        //
        if(*ptr == DELIMITER) { //delimiter is the size of indices, this is ok since only a couple will be large
            prepareNextValue();
            detectDataType();
        }
        //read until delimiter
        //then increment based off of how many bytes are needed to represent the next value
        //incrememnt until next signed bit and read in the column indices
    }
    
    //equality operators -> REPLACE WITH ABILITY TO WORK WITH MANY BYTES
    // operator bool() const {return ptr < end;} //closer I want,  error: ‘bool ByteIterator::operator!=()’ must have exactly one argument

    void detectCompression(){
    //have user input for what kind of compression level they want
    //seamlessly detect compression type
    //COO -> uses n+1 size for col pointer
    //VSE -> 
    //vSRLE -> done (kinda)
    }

    void prepareNextValue(){
        fileStream.seekg(1, ios::cur);
        fileStream.read(ptr, sizeof(valueType));
        fileStream.seekg(1, ios::cur);
    }

    void detectDataType(){
       fileStream.read(ptr, sizeof(uint8_t));
       newIndexType = *ptr;
       fileStream.seekg(1, ios::cur);
    }
};
