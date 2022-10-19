#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <string>
#include <Eigen>

using namespace std;

// Class for our compressed sparse matrix
class DeBruinesComp {
    public:
        // Constructor for the class (needs to compress a raw byte array)
        // May take a level of compression as a parameter
        // and the raw character array
        DeBruinesComp() {

        }
        
        // Iterator for the compressed sparse matrix
        struct ByteIterator {
            
        };

        // Public member function to read in a binary file from disk to a char vector
        void readBinaryFile(const char *filename, vector<char> &buffer) {
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
            file.read(&data[0], size);
        }

        // Wrapper to convert to other sparse matrix types

    private:
        vector<char> data;
        int compression_level;
};