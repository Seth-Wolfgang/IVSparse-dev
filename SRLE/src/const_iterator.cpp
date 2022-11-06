//create an iterator struct
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <iterator>
#include <cstddef>
#include <fstream>
#define DELIMITER 0

using namespace std;

class const_iterator {
    //todo:
    //clean the vocabulary
    //**does read seek?**
    //remove seek from this and refactor reads back into methods
    private:
        ifstream fileStream;
        uint32_t magicByteSize;
        uint32_t rowType;
        uint32_t nRows;
        uint32_t colType;
        uint32_t nCols;
        uint32_t valueWidth;
        uint32_t oldIndexType; //should not be set to uint_32t -> store both new and old into one byte
        int newIndexWidth = 1; //basically how many bytes we read, NOT ACTUALLY THE TYPE
        streampos start, end;
        char* runIndex = (char*)malloc(sizeof(char)); //*current* pointer -> change to current value

    public:
        streampos getCurrentPosition();

        int value;

    //constructor
    //read in first few bytes for data
   const_iterator(string filePath) {
        //read in first few bytes for data
        //set up the iterator
        uint32_t params[7];
        fileStream.open(filePath, ios::binary | ios::out);
        
        //record start and end
        start = fileStream.tellg();
        fileStream.seekg(0, ios::end); //keep this, but add a new class that reads a raw memory array
        end = fileStream.tellg();      //read whole file and append to an array
        fileStream.seekg(0, ios::beg);

        //read in the first 28 bytes -> metadata
        if (fileStream.is_open()) {
            for(int i = 0; i < 8; i++) {
                fileStream.read(runIndex, 1);
                params[i] = (int) *runIndex;

                if(*runIndex == 0) {
                    fileStream.read(runIndex, 1);
                    value = *runIndex;
                    fileStream.read(runIndex, 1);
                    newIndexWidth = *runIndex;
                    // cout << "value:" << value << endl;
                    // cout << "newIndexWidth:" << newIndexWidth << endl;
                }
            }
            
        magicByteSize = params[0]; //change later
        rowType       = params[1];
        nRows         = params[2];
        colType       = params[3];
        nCols         = params[4];
        valueWidth     = params[5];
        oldIndexType  = params[6];
        cout << "Parameters set" << endl;

        }
        else {
            cout << "File not found" << endl;
        }
    }

    //NO VECTOR TYPES

    //LOOK INTO 
    //https://en.cppreference.com/w/cpp/language/partial_specialization

    //returns value - need to change this. I want it to return the value we are currently looking at
    char& operator * () const {return *runIndex;}; //should return value to char, even if reading a binary file
    
    //create operator for returning current pointer value?

    //prefix increment
    //template<Typename T> //create a table and way to check data type
    const void operator++() {
        //fileStream.seekg(newIndexWidth, ios::cur);
        //cast?
        fileStream.read(runIndex, newIndexWidth);
        cout << (int)*runIndex << " ";
        
        if(*runIndex == 0 ) { //delimiter is the size of indices, this is ok since only a couple will be large
            cout << "Found delimiter" << endl;
            if(fileStream.tellg() >= end){
                cout << "End of file" << endl;
                return;
            }
            fileStream.read(runIndex, valueWidth);
            value = *runIndex;
            fileStream.read(runIndex, 1);
            newIndexWidth = *runIndex;
            
             cout << "value:" << value << endl;
             cout << "newIndexWidth:" << newIndexWidth << endl;
        }
}
        //read until delimiter
        //then increment based off of how many bytes are needed to represent the next value
        //incrememnt until next signed bit and read in the column indices
    
    
    // equality operator
    operator bool() {
        return fileStream.tellg() < end;
        }
        

    void prepareNextValue(){
        // cout << "Preparing next value" << endl;
        // cout << "Value width: " << valueWidth << endl;
    }

    void detectDataType(){
        // cout << "Detecting data type" << endl;
        fileStream.read(runIndex, 0);
        // cout << "New index type: " << *runIndex << endl;
        newIndexWidth = *runIndex;
        // cout << "set newIndexWidth " << newIndexWidth << endl;
        //fileStream.seekg(1, ios::cur);
    }

};