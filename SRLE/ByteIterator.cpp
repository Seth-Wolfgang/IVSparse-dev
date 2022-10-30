//create an iterator struct
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <iterator>
#include <cstddef>
#include <fstream>

using namespace std;

class ByteIterator {

    private:
        std::ifstream fileStream;
        int dataTypes[4] = {1, 2, 4, 8};
        uint32_t magicByteSize;
        uint32_t rowType;
        uint32_t nRows;
        uint32_t colType;
        uint32_t nCols;
        uint32_t valueType;
        uint32_t oldIndexType;
        int newIndexType; //basically how many bytes we read, NOT ACTUALLY THE TYPE
        int delimitor = 0;
        char* ptr;
        
    public:
    //constructor
    //read in first few bytes for data
    
   ByteIterator(string filePath) {
        //read in first few bytes for data
        //set up the iterator
        uint32_t params[7];
        char* buffer;
        fileStream(filePath, std::ios::binary);
        if (fileStream.is_open()) {
            for(int i = 0; i < 7; i++) {
                fileStream.read(&buffer, 4);
                fileStream.seekg(4, ios::cur);
                params[i] = (uint32_t)buffer;

                if(data == delimitor) {
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

    //constructor
    ByteIterator(char* ptr) : ptr(ptr) {}

    //returns value or pointer 
    char& operator*() {return *ptr;}; //should return value to char, even if reading a binary file

    //prefix increment
    //template<Typename T> //create a table and way to check data type
    ByteIterator& operator++() {
        fileStream.seekg(newIndexType);
        read(*ptr, newIndexType); 
        if(*ptr == delimitor) { //delimiter is the size of indices, this is ok since only a couple will be large
            prepareNextValue();
            detectDataType();

        }
        //read until delimiter
        //then increment based off of how many bytes are needed to represent the next value
        //incrememnt until next signed bit and read in the column indices
    }
    
    //equality operators -> REPLACE WITH ABILITY TO WORK WITH MANY BYTES
    // bool operator==(const ByteIterator& start, const ByteIterator& end) {return start.ptr == end.ptr;} 
    // bool operator!=(const ByteIterator& start, const ByteIterator& end) {return start.ptr != end.ptr;}

    void detectCompression(){
    //have user input for what kind of compression level they want
    //seamlessly detect compression type
    //COO -> uses n+1 size for col pointer
    //VSE -> 
    //vSRLE -> done (kinda)
    }

    void prepareNextValue(){
        seek(1, ios::cur);
        read(*ptr, sizeof(valueType));
        seek(1, ios::cur); //change
    }

    void detectDataType(){
       read(*ptr, sizeof(uint8_t));
       newIndexType = *ptr;
       seek(1, ios::cur);
    }
};