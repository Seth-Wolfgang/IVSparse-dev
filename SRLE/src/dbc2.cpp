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
        data.reserve(num_vals / 4);
    }

    // Function to return number of bytes to store a given number
    // SWITCH STATEMENT (OR LOGORITHIM) 
    uint8_t shrink_to(size_t num) {
        if (num < 256) {
            return 1;
        } else if (num < 65536) {
            return 2;
        } else if (num < 16777216) {
            return 3;
        } else if (num < 4294967296) {
            return 4;
        } else if (num < 1099511627776) {
            return 5;
        } else if (num < 281474976710656) {
            return 6;
        } else if (num < 72057594037927936) {
            return 7;
        } else {
            return 8;
        }
    }

    // ---- End Private Methods ---- //

    public:
    // Constructor for COO Matrix
    // * ASSUMING in column major??
    DeBruinesComp(const vector<unsigned int> &vals) {

        // * Assuming first tuple is num_rows, num_cols, num_vals
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
        // ? put all of these into 1 btye usually only 1-8 so if row and col_t are equal can store in 1 byte 4 bits for val_t and 4 for row/col_t?
        data.push_back(val_t);
        data.push_back(row_t);
        data.push_back(col_t);
        // Memcopy num_rows and num_cols into data
        memcpy(con_ptr + 3, &num_rows, row_t);
        memcpy(con_ptr + 3 + row_t, &num_cols, col_t);

        // Create a buffer for col_ptrs so size of col_ptrs stays constant (iterate con_ptr)
        con_ptr += 3 + row_t + col_t;

        // Create Pointer to start of col_ptr to update during compression
        uint8_t* col_ptr = con_ptr;

        // Iterate con_ptr num_cols times col_t bytes
        con_ptr += num_cols * col_t;

        // LOOP1: Construct each Column
        for (int i = 0; i < num_cols; i++) {

            // use a set to store unique values as it imposes uniqueness and automatically sorts by ascending order
            set<unsigned int> unique_vals_set;

            // insert all unique values into set
            for (int j = 3; j < vals.size(); j += 3) {
                if (vals[j + 1] == i) {
                    unique_vals_set.insert(vals[j+2]);
                }
            }

            // create vector to store unique values
            vector<unsigned int> unique_vals(unique_vals_set.begin(), unique_vals_set.end());

            // TODO: Update col_ptr to match beginning of column
            // ? Store the number of runs until the next column? would be shorter then the number of values in between
            int num_runs = 0;

            // LOOP2: Construct each Run
            for (unsigned int k = 0; k < unique_vals.size(); k++) {

                // memcopy unique value into data and iterate con_ptr
                // !! how to grab item from set without [] operator
                memcpy(con_ptr, &unique_vals[k], val_t);
                con_ptr += val_t;

                // create pointer to index type
                uint8_t* index_ptr = con_ptr;

                // memcpy the index type of the run
                uint8_t index_t = 1; // ? change to row type by default?
                memcpy(con_ptr, &index_t, 1);
                con_ptr += 1;

                // Find each indicie of the unique value and push to data
                // ? more efficient to do find all unique value indicies at once?
                size_t max = 0;
                size_t num_indicies = 0;

                for (int j = 3; j < vals.size(); j += 3) {
                    // !! how to grab item from set without [] operator
                    if (vals[j + 1] == i && vals[j + 2] == unique_vals[k]) {
                        
                        // if the con_ptr is right after the index_ptr then don't positive delta encode that value
                        if (con_ptr == index_ptr + 1) {
                            memcpy(con_ptr, &vals[j], row_t);
                            con_ptr += row_t;
                            max = vals[j];
                            num_indicies++;
                        } else { // else positive delta encode the value
                            size_t delta = vals[j] - vals[j - 3];
                            memcpy(con_ptr, &delta, row_t);
                            con_ptr += row_t;
                            if (delta > max) {
                                max = delta;
                            }
                            num_indicies++;
                        }
                        
                    }
                }

                // Determine min byte width of indicies using max
                uint8_t old_index_t = index_t;
                index_t = shrink_to(max);

                // write indexes to temp vector
                vector<uint8_t> temp;
                temp.reserve(num_indicies * index_t);
                for (int j = 0; j < num_indicies; j++) {
                    uint8_t* temp_ptr = temp.data();
                    memcpy(temp_ptr + (j * index_t), // Where
                           con_ptr - (num_indicies * row_t) + (j * row_t), // What (end of indicies -> beginning of indicies -> current index)
                           index_t); // How much
                }

                // Overwrite old indexes with new indexes
                con_ptr -= num_indicies * row_t;
                memcpy(con_ptr, temp.data(), num_indicies * index_t);
                con_ptr += num_indicies * index_t;


                // Update index_t
                memcpy(index_ptr, &index_t, 1);
                

                // Add delimter to data
                uint8_t delim = 0;
                memcpy(con_ptr, &delim, 1);

                // Update num_runs
                num_runs++;
            }

        // Update col_ptr
        memcpy(col_ptr, &num_runs, col_t);
        col_ptr += col_t;
        
        // Continue until no unique values left in column, then loop to next column
        }
        
        // ---- End Compression ---- //

        // resize vector to actual size
        data.resize(con_ptr - data.data());
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