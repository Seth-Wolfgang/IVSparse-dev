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
class const_array_iterator {
    //todo:
    //clean the vocabulary
    //**does read seek?**
    //remove seek from this and refactor reads back into methods
    private:
        uint32_t magicByteSize;
        uint32_t rowType;
        uint32_t nRows;
        uint32_t colType;
        uint32_t nCols;
        uint32_t valueWidth;
        uint32_t oldIndexType; //should not be set to uint_32t -> store both new and old into one byte
        int row;
        bool zeroIsIndex = false;
        int sizeOfFile;
        
        int newIndexWidth = 1; //basically how many bytes we read, NOT ACTUALLY THE TYPE
        char* end;
        int index = 0;

    public:
        int value;
        char* fileData;
        char* arrayPointer;

    //constructor
    //read in first few bytes for data
   const_array_iterator(const char* filePath) {
        //read in first few bytes for data
        //set up the iterator
        readFile(filePath);
        //read in the first 28 bytes -> metadata
        //read first 28 bytes of fileData put it into params
        uint32_t params[7];
        for(int i = 0; i < 8; i++) {
            params[i] = (int) *arrayPointer;
            arrayPointer+=4;
        }

        value = *(uint8_t*)&arrayPointer[0];
        arrayPointer++;
        newIndexWidth = *(uint8_t*)&arrayPointer[0];
        arrayPointer++;
        cout << "value: " << value << endl;
        cout << "newIndexWidth: " << newIndexWidth << endl;

        if(arrayPointer[0] == 0) {
            zeroIsIndex = true;
        }

        // magicByteSize = params[0]; //change later
        // rowType       = params[1];
        // nRows         = params[2];
        // colType       = params[3];
        // nCols         = params[4];
        // valueWidth    = params[5];
        // oldIndexType  = params[6];

        for(int i = 0; i < 7; i++) {
            cout << params[i] << endl;
        }

        // if(*fileBuffer == 0) { //it should equal 0
        //     fileStream.read(fileBuffer, valueWidth);
        //     value = *fileBuffer;
        //     fileStream.read(fileBuffer, 1);
        //     newIndexWidth = *fileBuffer;

        //     if(fileStream.peek() == 0) {
        //         zeroIsIndex = true;
        //     }
        //         // cout << "value:" << value << endl;
        //         // cout << "newIndexWidth:" << newIndexWidth << endl;
        // } else {
        //     cout << "Too many/few parameters!" << endl;
        // }
    }//end of constructor

    //NO VECTOR TYPES

    //LOOK INTO 
    //https://en.cppreference.com/w/cpp/language/partial_specialization

    //returns value - need to change this. I want it to return the value we are currently looking at
    char& operator * () const {return *arrayPointer;}; //should return value to char, even if reading a binary file
    
    //create operator for returning current pointer value?

    //prefix increment
    //template<Typename T> //create a table and way to check data type
    const void operator++() {
        uint index; // good for now
        // cout <<  *(uint*)&arrayPointer[0] << " ";
        switch (newIndexWidth){
            case 1:
                index = *(uint8_t*)&arrayPointer[0];
                break;
            case 2:
                index = *(uint16_t*)&arrayPointer[0];
                break;
            case 4:
                index = *(uint32_t*)&arrayPointer[0];
                break;
            case 8:
                index = *(uint64_t*)&arrayPointer[0];
                break;
            default:
                //cout << "Invalid width" << endl;
                break;
        }
        cout << index << " ";
        arrayPointer += newIndexWidth;

        if(index == 0 && !zeroIsIndex){
            value = arrayPointer[0];
            arrayPointer++;
            newIndexWidth = arrayPointer[0];
            arrayPointer++;
            cout << "value: " << value << endl;
            cout << "newIndexWidth: " << newIndexWidth << endl;
           
            if(arrayPointer[0] == 0) {
                zeroIsIndex = true;
                return;
            }
        }
        zeroIsIndex = false;

        /*
        if width is 1, 2, 4, or 8
        
        create a templated helper function to read in the value
        width will control the size of the value we read in

        return the data type of fileBuffer 

        */

    }
        //read until delimiter
        //then increment based off of how many bytes are needed to represent the next value
        //incrememnt until next signed bit and read in the column indices
    
    
    // equality operator
    
    operator bool() {return end - arrayPointer >= 0;}


    // template <typename T> 
    // inline T incrementHelper(T index) { //Todo: TEST TO SEE IF INLINE IS FASTER
    //     //next value of fileData
    //     //read in the next value
                
    //     return = cast<T>(arrayPointer[0]);    
    // }

    //reads in the file and stores it in a char* 
    inline void readFile(string filePath){
        ifstream fileStream;
        fileStream.open(filePath, ios::binary | ios::out);
        
        fileStream.seekg(0, ios::end);
        int sizeOfFile = fileStream.tellg();
        fileData = (char*)malloc(sizeof(char*)*sizeOfFile);

        fileStream.seekg(0, ios::beg);
        fileStream.read(fileData, sizeOfFile);
        
        fileStream.close();

        arrayPointer = fileData;
        end = fileData + sizeOfFile;
        }
};