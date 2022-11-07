#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <cstdint>
#include <typeinfo>
#include <bits/stdc++.h>
#include <set>


using namespace std;

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
    size_t num_vals;

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
        data.reserve(num_vals * 4);
    }

    // ---- End Private Methods ---- //

    public:
    // Constructor for COO Matrix
    // ---ASSUMING in column major (sorted by column)--- //
    DeBruinesComp(const vector<unsigned int> &vals) {

        // Assuming first tuple is num_rows, num_cols, num_vals
        num_rows = vals[0];
        num_cols = vals[1];
        num_vals = vals[2];

        // Allocate space for the vector based on estimate
        allocate();

        // Set pointer to beginning of data
        con_ptr = data.data();

        // ---- Begin Compression ---- //

        // Construct Vector up to col_ptr
        // <val_t, row_t, col_t, num_rows, num_cols, [HERE]>
            // put all of these into 1 btye usually only 1-8 so if row and col_t are equal can store in 1 byte 4 bits for val_t and 4 for row/col_t?
        data.push_back(val_t);
        data.push_back(row_t);
        data.push_back(col_t);
        // Memcopy num_rows and num_cols into data
        memcpy(con_ptr + 3, &num_rows, row_t);
        memcpy(con_ptr + 3 + row_t, &num_cols, col_t);

        // Create a buffer for col_ptrs so size of col_ptrs stays constant (iterate con_ptr )
        con_ptr += 3 + row_t + col_t;

        // Create Pointer to start of col_ptr to update during compression
        uint8_t* col_ptr = con_ptr;

        // Iterate con_ptr num_cols times col_t bytes
        con_ptr += num_cols * col_t;

        // LOOP1: Construct each Column
        for (int i = 0; i < num_cols; i++) {
            // use a set to store unique values as it imposes uniqueness and automatically sorts by ascending order
            set<unsigned int> unique_vals;

            // insert all unique values into set
            for (int j = 3; j < vals.size(); j += 3) {
                if (vals[j + 1] == i) {
                    unique_vals.insert(vals[j+2]);
                }
            }

            // Update col_ptr to match beginning of column
            

            // LOOP2: Construct each Run
            for (int k = 0; k < unique_vals.size(); k++) {

                // memcopy unique value into data and iterate con_ptr
                memcpy(con_ptr, &unique_vals[k], val_t);
                con_ptr += val_t;

                // create pointer to index type
                uint8_t* index_ptr = con_ptr;

                // memcpy the index type of the run
                uint8_t index_t = 1;
                memcpy(con_ptr, &index_t, 1);
                con_ptr += 1;

                // Find each indicie of the unique value and push to data
                // -----------more efficient to do find all unique value indicies at once?
                unsigned int max = 0;
                for (int j = 3; j < vals.size(); j += 3) {
                    if (vals[j + 1] == i && vals[j + 2] == unique_vals[k]) {
                        // Positive delta encode values and insert them into data
                        memcpy(con_ptr, &vals[j], row_t);
                        con_ptr += row_t;
                    }
                }

                // Determine min byte width of indicies

                // Overwrite indicies with new byte width indicies

                // Update index type in data

                // Add delimter to data
            }
        
        // Continue until no unique values left in column, then loop to next column
        }
        
        // ---- End Compression ---- //

        // Shrink Data to Optimal Size
        // TODO: probably can't use this after all that memcpys soooo have fun skyler
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