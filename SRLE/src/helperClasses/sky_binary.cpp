#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <string>
#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <ctime>
#include <random>


using namespace std;

// Function to read a binary file
//template <typename T>
void readBinaryFile(const char* filename, vector<char>& buffer)
{
    // Open the file
    ifstream file(filename, ios::binary);

    // Get the starting point of the file
    streampos begin, end;
    begin = file.tellg();

    // Get the ending point of the file
    file.seekg(0, ios::end);
    end = file.tellg();

    // Get the size of the file
    int size = end - begin;

    // Go back to the starting point
    file.seekg(0, ios::beg);

    // Read the file
    buffer.resize(size);
    file.read(&buffer[0], size);
}

// Function to write a binary file
template <typename T>
void writeBinaryFile(const char* filename, vector<T>& buffer)
{
    // Open the file
    ofstream file(filename, ios::binary | ios::app);

    // Write the file

    file.write((char*)&buffer[0], buffer.size()* sizeof(T));
    file.close();
}


void writeBinaryFile(const char* filename, char buffer)
{
    // Open the file
    ofstream file(filename, ios::binary | ios::app);

    // Write the file

    file.write((char*)&buffer, sizeof(char));
    file.close();
}


int main() {
    // Read the binary file
    vector<uint32_t> params = {1,1,1,1,1,1,1,0};
    vector<char> values = {1, 2, 4, 8};
    vector<char> newIndexWidths = {1, 2, 4, 8};
    vector<uint8_t> buffer1Byte = {3,5,6,7,2,1,2,4,8,2,6,7,8,7,5,4,2,254,2};
    vector<uint16_t> buffer2Byte = {3,5,6,7,2,2,2,4,8,2,6,7,8,7,5,4,2,258,2};
    vector<uint32_t> buffer4Byte = {3,5,6,7,2,4,2,4,8,2,6,7,8,7,5,4,2,65530,2};
    vector<uint64_t> buffer8Byte = {3,5,6,7,8,2,4,8,2,6,7,8,7,5,4,2,4294963172,2,};
    char zero = 0;
    // Print the contents of the file
    // copy(buffer.begin(), buffer.end(), ostream_iterator<uint16_t>(cout, " "));
    // cout << endl;
    




    // First create an instance of an engine.
    random_device rnd_device;
    // Specify the engine and distribution.
    mt19937 mersenne_engine {rnd_device()};  // Generates random integers
    uniform_int_distribution<int> dist {1, 52};
    
    auto gen = [&dist, &mersenne_engine](){
                   return dist(mersenne_engine);
               };

    vector<uint16_t> v = {};


    //generate(begin(v), end(v), gen);
    for(int i = 0; i < 10000; i++){
        v.push_back(i);
        v.at(i);
    }

    writeBinaryFile("input.bin", params);


    writeBinaryFile("input.bin", values.at(3));
    writeBinaryFile("input.bin", newIndexWidths.at(1));
    writeBinaryFile("input.bin", v);


    // writeBinaryFile("input.bin", values.at(0));
    // writeBinaryFile("input.bin", newIndexWidths.at(0));

    // for(int i = 0; i < 100; i++){
    //     writeBinaryFile("input.bin", buffer1Byte);
    // }

    

    // writeBinaryFile("input.bin", zero);
    // writeBinaryFile("input.bin", values.at(1));
    // writeBinaryFile("input.bin", newIndexWidths.at(1));

    // for(int i = 0; i < 100; i++){
    //     writeBinaryFile("input.bin", buffer2Byte);
    // }
    // writeBinaryFile("input.bin", zero);
    // writeBinaryFile("input.bin", zero);


    // writeBinaryFile("input.bin", values.at(3));
    // writeBinaryFile("input.bin", newIndexWidths.at(3));
    // for(int i = 0; i < 100; i++){
    //     writeBinaryFile("input.bin", buffer8Byte);
    // }
    // writeBinaryFile("input.bin", zero);
    // writeBinaryFile("input.bin", zero);
    // writeBinaryFile("input.bin", zero);
    // writeBinaryFile("input.bin", zero);
    // writeBinaryFile("input.bin", zero);
    // writeBinaryFile("input.bin", zero);
    // writeBinaryFile("input.bin", zero);
    // writeBinaryFile("input.bin", zero);

    // writeBinaryFile("input.bin", values.at(2));
    // writeBinaryFile("input.bin", newIndexWidths.at(2));

    // for(int i = 0; i < 100; i++){
    //     writeBinaryFile("input.bin", buffer4Byte);
    // }
    
    return 0;
}