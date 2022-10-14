#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>

using namespace std;

// Function to read a binary file
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

int main() {
    // Read the binary file
    vector<char> buffer;
    readBinaryFile("test.txt", buffer);

    // Print the contents of the file
    copy(buffer.begin(), buffer.end(), ostream_iterator<char>(cout, " "));
    cout << endl;

    return 0;
}