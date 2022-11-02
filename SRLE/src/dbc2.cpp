#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <cstdint>
#include <typeinfo>
#include <bits/stdc++.h>


using namespace std;

/* Data Structures Questions (11/2):
    1. What is COO sparse format?
    2. How aer we estimating the size of data?
    3. Can we see your 'hacky' way of type casting?
*/

// Take in a COO Matrix and Constructor will compress it
// and store it as a DBC Compressed matrix

// Allocate space for the data so that it fits into a CSC Matrix
// Then do all compression in place (in that one vector)

class DeBruinesComp {
    private:
    // ---- Metadata ---- //
    
    // TODO: define file signiture bytes
    int magic = 0x36121236; // File signiture bytes
    
    size_t num_cols;
    size_t num_rows;

    // Define number of bytes needed for each type
    uint8_t row_t = 1;
    uint8_t col_t = 1;
    uint8_t val_t = 1;

    // ---- End Metadata ---- //

    // Storage container for all data
    // Eventual home for final compressed data
    vector<uint8_t> data;
    uint8_t* con_ptr;

    // ---- Private Methods ---- //

    // Function to allocate space for the incoming matrix
    void allocate() {
        data.reserve(
            // TODO: Space Estimate Here
        );
    }

    // ---- End Private Methods ---- //

    public:
    // Constructor for COO Matrix
    DeBruinesComp(
        const vector<unsigned int> &vals,
        const vector<unsigned int> &row,
        const vector<unsigned int> &col_p,
        const vector<int> dim) {


        // Allocate space for the vector based on estimate
        allocate();

        // Set pointer to beginning of data
        con_ptr = data.data();

        // ---- Begin Compression ---- //

        // Construct Vector up to col_ptr
        // <val_t, row_t, col_t, num_rows, num_cols, [HERE]>

        // Create a buffer for col_ptrs so size of col_ptrs stays constant

        // Create Pointer to start of col_ptr to update during compression

        // LOOP1: Construct each Column
            // TODO: Define Data Structure for storing unieuq values sorted

            // Find first unique value in column (store unique values sorted)

            // Update col_ptr to match beginning of column
            

            // LOOP2: Construct each Run
                // Find each indicie of the unique value and push to data

                // Positive Delta Encode indicies in place

                // Determine min byte width of indicies

                // Overwrite indicies with new byte width indicies

                // Update index type in data

                // Add delimter to data
        
        // Continue until no unique values left in column, then loop to next column
        
        // ---- End Compression ---- //

        // Shrink Data to Optimal Size
        data.shrink_to_fit();
    }

    // Read compressed matrix from file
    DeBruinesComp(const string &filename) {
        // Go past magic and throw rest into data
    }


    // Write compressed matrix to file
    void write(const string &filename) {
        // push magic to file and then throw all of data onto file?
    }

};

int main() {
    cout << "Hello, World!" << endl;
    return 0;
}