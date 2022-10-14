#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>

using namespace std;

void decodeFile(vector<int> &newVector, string fileName);
void encodeFile(vector<int> myVector, string fileName) {


int main() {
    std::ifstream newFile;
    string filePath = ("Research\\SRLE\\inputFiles\\test.txt");
    vector<int> vec;
    decodeFile(vec, filePath);

    for (int i = 0; i < vec.size(); i++) {
        std::cout << vec[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}


void decodeFile(vector<int> &newVector, string fileName) {
    std::ifstream newFile;
    newFile.open(fileName);
    if (newFile.is_open()) {
        std::istream_iterator<int> byteRead(newFile);
        std::istream_iterator<int> end;
        int counter;
        int newValue;
        while (byteRead != end) {
            if (*byteRead < 0) { // if the value is negative, then its a new value for the matrix
                newValue = *byteRead; //IMPORTANT NOTE: actual values are set to negative as a delimitor
                counter = 0;
            } 
            else { //else its a counter for the number of times the value is repeated
                counter += *byteRead;
                for(int j = 0; j < counter; j++){
                    newVector.push_back(0);
                }
                newVector.push_back(newValue);
            }            
            byteRead++;
        }
    } else {
        cout << "File not found" << endl;
    }
    newFile.close();
}

// example: 1 5 10 23 44
// turns to 1 5 5 13 31

void encodeFile(vector<int> myVector, string fileName) {
    ofstream newFile;
    newFile.open(fileName);
    std::ostream_iterator<int> byteWrite(newFile);
    std::ostream_iterator<int> end;
    int counter = 0;

    while(byteWrite != end) {
        
    }

    newFile.close();
}
