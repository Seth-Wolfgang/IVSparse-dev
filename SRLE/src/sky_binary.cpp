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
    ofstream file(filename, ios::binary);

    // Write the file
    file.write((char*)&buffer[0], buffer.size());
}

int main() {
    // Read the binary file
    vector<char> buffer;
    readBinaryFile("input.bin", buffer);

    // Print the contents of the file
    copy(buffer.begin(), buffer.end(), ostream_iterator<int>(cout, " "));
    cout << endl;

    buffer = {1,1,1,1,1,1,1,0,1,1,3,5,6,7,0,2,1,2,4,8,2,6,7,8,7,5,4,2,54,2,0};
    // Write the binary file
    writeBinaryFile("input.bin", buffer);

    return 0;
}