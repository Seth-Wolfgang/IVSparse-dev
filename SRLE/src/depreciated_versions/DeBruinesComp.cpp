/* Authors: Skyler Ruiter & Seth Wolfgang 2022 */
#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <cstdint>
//#include "Eigen/Sparse"


using namespace std;

/* DeBruinesComp To-Do List:
    * Get a complete list of requirements and actually write down the details of the program
    * Write the compression algorithm in constructor
        * one for already compressed data and one constructor for not?
    * Write function to decompress data
    * finalize read and write functions
    * Decide on correct metadata for file format
        * Create File Signiture Bytes
        * Store compression level as metadata
    * Decide on ALL THE ITERATOR STUFF EWWWW
        * Work through all of the massive amounts of logic for each compression type
    * Write wrapper functions to Eigen::SparseMatrix and other sparse matrix types
    * Decide on compression levels
    * Make the compression data type fluid (i.e. allow for different data types)
    * Parallelize the IO (and compression?)
    * Make a better looking directory structure (header files n stuff)
*/

/* Questions to Answer:
    * when he says raw byte array being passed to the constructor as input, is it just a whole column filled with 0's too?
        Or is it passed as CSC format or something?
    * Is the read function already compressed or not? and do we check?
    * Is there metadata that only needs to live on the disk and not the actual program?
    * In the grand scheme of a whole matrix is it stored as a vector of vectors
        (because we only work with 1 column at a time I think)
        So is the logic for things like matrix multiplication working with a vector of vectors?
*/

// Class for our compressed sparse matrix
class DeBruinesComp {

private:
    vector<unsigned char> data = {0x36, 0x12, 0x12};
    int compression_level;

public:
    // TODO: Constructor for the class (needs to compress an array)
    template <typename idx_t, typename val_t>
    DeBruinesComp(const vector<val_t> &idx, const vector<idx_t> &row, const vector<idx_t> &col, const vector<int> &dim) {
        // Iterate through the raw array and compress it

        

        for (int i = 0; i < data.size(); i++)
            cout << (uint16_t) data[i] << " ";
        }
        
        // TODO: Iterator for the compressed sparse matrix
        struct ByteIterator {
            
        };

        //  TODO: Public member function to read in a binary file from disk to a char vector
        void read(const char *filename, vector<uint8_t> &buffer) {
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

            // TODO: Check if the file is correct format (otherwise compress it to +dvsrle)

            // Read the file
            buffer.resize(size);
            //file.read(&data[0], size);
        }

        // Public member function to write a char vector to a binary file on disk
        void write(const char *filename, vector<char> &buffer) {
            // Open the file
            ofstream file(filename, ios::binary);

            // TODO: Write metadata to the file

            // Write the file
            file.write(&buffer[0], buffer.size());
        }

        // TODO: Wrapper to convert to other sparse matrix types

};

int main() {
    // Construct a CSC matrix
    vector<unsigned short int> vals = {1, 9, 1, 3, 6, 2, 5, 3, 1, 4};
    vector<unsigned int> row = {1, 3, 0, 2, 0, 2, 0, 1, 3, 2};
    vector<unsigned int> cols = {0, 2, 4, 6, 9, 10};

    // Construct a DeBruinesComp object
    DeBruinesComp dbc = DeBruinesComp(vals, row, cols, {4, 5});


    return 0;
}