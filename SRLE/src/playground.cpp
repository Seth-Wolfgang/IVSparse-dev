//use byteIterator to iterate through the bytes of the file
//     //read in the first 28 bytes -> metadata
#include <iostream>
#include <iterator>
// #include "const_iterator.cpp"
#include "const_array_iterator.cpp"
using namespace std;
int main(){
    const_array_iterator<double>* iter = new const_array_iterator<double>("input.bin");
    // iter->operator++();
    double value = 0;

    while(iter->operator bool()) {
        iter->operator++();
        if(iter->operator *() != value){
            cout << iter->operator *() << endl;
            value =  iter->operator *();
        }
    }

    
    return 0;
}
