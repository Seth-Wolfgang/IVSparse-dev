#include "../include/CPP_Lib.hpp"

using namespace std;

template<typename T>
class const_array_iterator {
    //todo:
    //clean the vocabulary
    //turn into a sub class of skyler's constructor
    private:
        uint32_t rowType;       //= params[1];
        uint32_t nRows;         //= params[2];
        uint32_t colType;       //= params[3];
        uint32_t nCols;         //= params[4];
        uint32_t valueWidth;    //= params[5];
        uint8_t newIndexWidth; //basically how many bytes we read, NOT ACTUALLY THE TYPE
        char* end;
        char* fileData;
        void* arrayPointer;
        uint64_t index = 0;
        T value;
        uint64_t sum = 0;
        bool firstIndex = true;

    public:
      
    const_array_iterator(const char* filePath) {

        //set up the iterator
        readFile(filePath);
        //read first 28 bytes of fileData put it into params -> metadata
        uint32_t params[5];
        
        memcpy(&params, arrayPointer, 24); //28 is subject to change depending on magic bytes
        arrayPointer+=24; //first delimitor is 4 bytes
    //delete this comment
        rowType       = params[0];
        nRows         = params[1];
        colType       = params[2];
        nCols         = params[3];
        int x = 5
        valueWidth    = params[4];
        cout << "valueWidth: " << valueWidth << endl;

        memcpy(&value, arrayPointer, valueWidth);
        arrayPointer += valueWidth;
        newIndexWidth =  *static_cast<uint8_t*>(arrayPointer);
        arrayPointer++; //this should make it point to first index
        
        cout << "value: " << value << endl;
        cout << "newIndexWidth: " << newIndexWidth << endl;

        // for debugging
        //  for(int i = 0; i < 5; i++) {
        //      cout << i << " " << params[i] << endl;
        // }


    }//end of constructor


    //todo make this return type T 
    T& operator * () {return value;}; 


    uint64_t operator++() {
        uint64_t newIndex = interpretNewIndex(); 
       
        // printf("newIndexWidth: %d\n", newIndexWidth);
        // cout << "arrayPointer position: " <<  ((char*)arrayPointer - fileData) << endl; 
        // printf("Array Pointer Value: %d\n", *static_cast<uint8_t*>(arrayPointer));
        // printf("Prev Array Pointer Value: %d\n", *static_cast<uint8_t*>(arrayPointer-1));
        // cout << "Value: " << value << endl;
        cout << "newIndex: " << newIndex << endl << endl;

        if(newIndex == 0 && !firstIndex){
            // cout << " flag !" << endl;

            memcpy(&value, arrayPointer, valueWidth);
            arrayPointer += valueWidth; 
            // cout << "arrayPointer position: " <<  ((char*)arrayPointer - fileData) << endl; 

            memcpy(&newIndexWidth, arrayPointer, 1);
            arrayPointer++;
            
            // cout << endl << "value: " << value << endl;
            // cout << "newIndexWidth: " << static_cast<int>(newIndexWidth) << endl;
            
            memset(&index, 0, 8);
            memcpy(&index, arrayPointer, newIndexWidth);
            firstIndex = true;
            return index += newIndex;
        }

        firstIndex = false;
        return index += newIndex;
    }

    // const uint64_t operator++() {
    //     uint64_t newIndex = interpretNewIndex(); 
       
    //     printf("newIndexWidth: %d\n", newIndexWidth);
    //     cout << "arrayPointer position: " <<  ((char*)arrayPointer - fileData) << endl; 
    //     printf("Array Pointer Value: %d\n", *static_cast<uint8_t*>(arrayPointer));
    //     printf("Prev Array Pointer Value: %d\n", *static_cast<uint8_t*>(arrayPointer-1));
    //     cout << "Value: " << value << endl;
    //     cout << "newIndex: " << newIndex << endl << endl;

    //     if(newIndex == 0){
    //         cout << " flag !" << endl;
    //         memcpy(&value, arrayPointer, valueWidth);
    //         arrayPointer += valueWidth; 
    //         cout << "arrayPointer position: " <<  ((char*)arrayPointer - fileData) << endl; 

    //         memcpy(&newIndexWidth, arrayPointer, 1);
    //         arrayPointer++;
            
    //         cout << endl << "value: " << value << endl;
    //         cout << "newIndexWidth: " << static_cast<int>(newIndexWidth) << endl;
            
    //         memset(&index, 0, 8);
    //         memcpy(&index, arrayPointer, newIndexWidth);
    //     }
    //     cout << "NewIndex before return: " << newIndex << endl;
    //     return index += newIndex;
    // }

    // template<typename indexType> 
    // const uint64_t operator++() { 
    //     //TODO template metaprogramming
    //     //todo through an exception if we request something smaller than the size of the index
    //     uint64_t newIndex = 0; //get rid of in future versions
    //     memcpy(&newIndex, arrayPointer, newIndexWidth);
    //     arrayPointer += newIndexWidth;
    //     sum += value;
    //     if(newIndex == 0 && index != 0){ //change that
    //         memcpy(&value, arrayPointer, valueWidth);
    //         arrayPointer += valueWidth; 
    //         memcpy(&newIndexWidth, arrayPointer, 1);
    //         arrayPointer++;
    //         cout << endl << "value: " << value << endl;
    //         cout << "newIndexWidth: " << *(uint8_t*)newIndexWidth << endl;
    //         memset(&index, 0, 8);
    //         memcpy(&index, arrayPointer, newIndexWidth);
    //     }
    //     return index += newIndex;
    // }


    // equality operator
    operator bool() { return end >= arrayPointer;} //change to not equal at the end


    // reads in the file and stores it in a char* 
    // inline void readFile(string filePath){ 
    //     ifstream fileStream;
    //     fileStream.open(filePath, ios::binary | ios::out);
    //     fileStream.seekg(0, ios::end);
    //     int sizeOfFile = fileStream.tellg();
    //     fileData = (char*)malloc(sizeof(char*)*sizeOfFile);
    //     fileStream.seekg(0, ios::beg);
    //     fileStream.read(fileData, sizeOfFile);
    //     fileStream.close();
    //     arrayPointer = fileData;
    //     end = fileData + sizeOfFile;
    //     }


    inline uint64_t interpretNewIndex(){
        uint64_t newIndex = 0;

        switch (newIndexWidth){
            case 1:
                newIndex = static_cast<uint64_t>(*static_cast<uint8_t*>(arrayPointer));
                break;
            case 2:
                newIndex =  static_cast<uint64_t>(*static_cast<uint8_t*>(arrayPointer));
                break;
            case 4:
                newIndex =  static_cast<uint64_t>(*static_cast<uint8_t*>(arrayPointer));
                break;
            case 8:
                newIndex =  static_cast<uint64_t>(*static_cast<uint8_t*>(arrayPointer));
                break;
            default:
                cout << static_cast<int>(*static_cast<uint8_t*>(arrayPointer)) << endl;
                cout << "Invalid width: " << newIndexWidth << endl;
                printf("%d\n", newIndexWidth);
                break;
        }
        
        arrayPointer += newIndexWidth;

        return newIndex;
    }

    //marginally faster 
    inline void readFile(const char* filePath){
        //read a file using the C fopen function and store to fileData
        FILE* file = fopen(filePath, "rb");
        
        fseek(file, 0, SEEK_END);
        int sizeOfFile = ftell(file);
        fileData = (char*)malloc(sizeof(char*)*sizeOfFile);

        fseek(file, 0, SEEK_SET);

        fread(fileData, sizeOfFile, 1, file);
        fclose(file);
        // cout << "Size of file: " << sizeOfFile << endl;
        arrayPointer = fileData;
        end = fileData + sizeOfFile;
    }
};