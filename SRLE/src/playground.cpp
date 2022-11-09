//use byteIterator to iterate through the bytes of the file
//     //read in the first 28 bytes -> metadata
#include <iostream>
#include <iterator>
// #include "const_iterator.cpp"
#include "const_array_iterator.cpp"
using namespace std;
int main(){
    const_array_iterator* iter = new const_array_iterator("input.bin");
    // iter->operator++();


    while(iter->operator bool()) {
        iter->operator++();
    }

    
    return 0;
}
