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

//Wolfgang iterator
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
        
        int newIndexWidth; //basically how many bytes we read, NOT ACTUALLY THE TYPE
        streampos start, end;
        char* fileBuffer = (char*)malloc(sizeof(char*)*2); //*current* pointer -> change to current value
        int index = 0;

    public:
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
        fileStream.seekg(-2, ios::end); //keep this, but add a new class that reads a raw memory array
        end = fileStream.tellg();      //read whole file and append to an array
        fileStream.seekg(0, ios::beg);

        //read in the first 28 bytes -> metadata
        if (fileStream.is_open()) {
            for(int i = 0; i < 8; i++) {
                fileStream.read(fileBuffer, 4);
                params[i] = (int) *fileBuffer;
            }
            
            magicByteSize = params[0]; //change later
            rowType       = params[1];
            nRows         = params[2];
            colType       = params[3];
            nCols         = params[4];
            valueWidth    = params[5];
            oldIndexType  = params[6];
            cout << "Parameters set" << endl;

            for(int i = 0; i < 7; i++) {
                cout << params[i] << endl;
            }

            if(*fileBuffer == 0) { //it should equal 0
                fileStream.read(fileBuffer, valueWidth);
                value = *fileBuffer;
                fileStream.read(fileBuffer, 1);
                newIndexWidth = *fileBuffer;
                // cout << "value:" << value << endl;
                // cout << "newIndexWidth:" << newIndexWidth << endl;
            } else {
                cout << "Too many/few parameters!" << endl;
            }
        }
        else {
            cout << "File not found" << endl;
        }
    }//end of constructor

    //NO VECTOR TYPES

    //LOOK INTO 
    //https://en.cppreference.com/w/cpp/language/partial_specialization

    //returns value - need to change this. I want it to return the value we are currently looking at
    char& operator * () const {return *fileBuffer;}; //should return value to char, even if reading a binary file
    
    //create operator for returning current pointer value?

    //prefix increment
    //template<Typename T> //create a table and way to check data type
    const void operator++() {
        fileStream.read(&fileBuffer[0], newIndexWidth);
        //index += *fileBuffer;
        cout <<  *(uint*)&fileBuffer[0] << " ";

        if((int)*fileBuffer == 0 ) { //delimiter is the size of indices, this is ok since only a couple will be large
            index = 0; //resetting +delta
            //cout << "Found delimiter" << endl;
            fileStream.read(fileBuffer, valueWidth);
            value = *fileBuffer;
            fileStream.read(fileBuffer, 1);
            newIndexWidth = *fileBuffer;

            if(fileStream.peek() == 0){
                 //something something this is an index something
            }
            
            cout << endl << "value:" << value << endl;
            cout << "newIndexWidth:" << newIndexWidth << endl;
        }
}
        //read until delimiter
        //then increment based off of how many bytes are needed to represent the next value
        //incrememnt until next signed bit and read in the column indices
    
    
    // equality operator
    
    // error: passing ‘const ifstream’ {aka ‘const std::basic_ifstream<char>’} as ‘this’ argument discards qualifiers
    operator bool() {return fileStream.peek() != EOF;} //needs to be const!
};