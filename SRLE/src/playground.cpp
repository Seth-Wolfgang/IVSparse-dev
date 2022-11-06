//use byteIterator to iterate through the bytes of the file
//     //read in the first 28 bytes -> metadata
#include <iostream>
#include <iterator>
#include "const_iterator.cpp"
using namespace std;
int main(){
    const_iterator* iter = new const_iterator("input.bin");
    //iter++;

   
    while(iter->atEnd()){
        iter->operator++();
    }

    // iter->operator++();
    // iter->operator++();
    // iter->operator++();
   // cout << *iter++ << endl;

    // while(iter){

    // }

}
