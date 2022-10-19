#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <string>

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
    readBinaryFile("inputFiles/test.bin", buffer);

    // Print the contents of the file
    copy(buffer.begin(), buffer.end(), ostream_iterator<int>(cout, " "));
    cout << endl;

    // Write the binary file
    writeBinaryFile("inputFiles/test2.bin", buffer);

    return 0;
}