#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <string>
#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <cstring>


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


void writeBinaryFile(const char* filename, char& buffer)
{
    // Open the file
    ofstream file(filename, ios::binary | ios::app);

    // Write the file

    file.write((char*)&buffer, sizeof(char));
    file.close();
}

void writeBinaryFileFloat(const char* filename, double& buffer)
{
    // Open the file
    ofstream file(filename, ios::binary | ios::app);

    // Write the file

    file.write((char*)&buffer, sizeof(double));
    file.close();
}

int main() {
    // Read the binary file

    vector<uint32_t> params = {1,1,1,1,1,8,1,0};
    vector<double> values = {32.432, 53.35, 9.32, 0.001};
    vector<char> newIndexWidths = {1, 2, 4, 8};
    vector<uint8_t> buffer1Byte = {0,3,5,6,7,2,1,2,4,8,2,6,7,8,7,5,4,2,254,2,0};
    vector<uint16_t> buffer2Byte = {3,5,6,7,2,2,2,4,8,2,6,7,8,7,5,4,2,258,2,0};
    vector<uint32_t> buffer4Byte = {3,5,6,7,2,4,2,4,8,2,6,7,8,7,5,4,2,65530,2,0};
    vector<uint64_t> buffer8Byte = {3,5,6,7,8,2,4,8,2,6,7,8,7,5,4,2,4294963172,2,};

    // Print the contents of the file
    // copy(buffer.begin(), buffer.end(), ostream_iterator<uint16_t>(cout, " "));
    // cout << endl;
    

    
    writeBinaryFile("input.bin", params);
    writeBinaryFileFloat("input.bin", values.at(0));
    writeBinaryFile("input.bin", newIndexWidths.at(0));
    writeBinaryFile("input.bin", buffer1Byte);
    writeBinaryFileFloat("input.bin", values.at(1));
    writeBinaryFile("input.bin", newIndexWidths.at(1));
    writeBinaryFile("input.bin", buffer2Byte);
    writeBinaryFileFloat("input.bin", values.at(2));
    writeBinaryFile("input.bin", newIndexWidths.at(2));
    writeBinaryFile("input.bin", buffer4Byte);
    writeBinaryFileFloat("input.bin", values.at(3));
    writeBinaryFile("input.bin", newIndexWidths.at(3));
    writeBinaryFile("input.bin", buffer8Byte);


    return 0;
}