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
    uint8_t delim = 0;

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
        // * Print Stuff
        cout << "Allocating space for matrix" << endl;
        data.reserve(num_vals * 4);
        cout << num_vals*4 << endl;
    }

    // Function to return number of bytes to store a given number
    uint8_t shrink_to(size_t num) {
        switch (num) {
            case 0 ... 255:
                return 1;
            case 256 ... 65535:
                return 2;
            case 65536 ... 16777215:
                return 3;
            case 16777216 ... 4294967295:
                return 4;
            default:
                return 8;
        }
    }

    // ---- End Private Methods ---- //

    public:
    // Constructor for COO Matrix
    // ASSUMING in column major
    DeBruinesComp(const vector<unsigned int> &vals) {

        // Assuming first tuple is num_rows, num_cols, num_vals
        num_rows = vals[0];
        num_cols = vals[1];
        num_vals = vals[2];

        // * Print out metadata
        cout << "Number of rows: " << num_rows << endl;
        cout << "Number of cols: " << num_cols << endl;
        cout << "Number of vals: " << num_vals << endl;

        // Allocate space for the vector based on estimate
        allocate();

        // Set pointer to beginning of data
        con_ptr = data.data();

        // ---- Begin Compression ---- //

        // Construct Vector up to col_ptr

        // Need to determine types for row, col, val

        // Find the largest row, col, val
        size_t max_row = 0;
        size_t max_col = 0;
        size_t max_val = 0;

        for (size_t i = 3; i < vals.size(); i += 3) {
            if (vals[i] > max_row) {
                max_row = vals[i];
            }
            if (vals[i + 1] > max_col) {
                max_col = vals[i + 1];
            }
            if (vals[i + 2] > max_val) {
                max_val = vals[i + 2];
            }
        }

        row_t = shrink_to(max_row);
        col_t = shrink_to(max_col);
        val_t = shrink_to(max_val);

        // * Print Stuff
        cout << "Row type: " << (int) row_t << endl;
        cout << "Col type: " << (int) col_t << endl;
        cout << "Val type: " << (int) val_t << endl;


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

        // * Print Vector up until this point using con_ptr
        cout << "Vector up until col_ptr" << endl;
        for (size_t i = 0; i < con_ptr - data.data(); i++) {
            cout << (int) data[i] << " ";
        }
        cout << endl;

        // LOOP1: Construct each Column
        for (int i = 0; i < num_cols; i++) {

            // use a set to store unique values as it imposes uniqueness and automatically sorts by ascending order
            set<unsigned int> unique_vals_set;

            // insert all unique values into set
            for (size_t j = 3; j < vals.size(); j += 3) {
                if (vals[j + 1] == i) {
                    unique_vals_set.insert(vals[j+2]);
                }
            }

            // create vector to store unique values
            vector<unsigned int> unique_vals(unique_vals_set.begin(), unique_vals_set.end());

            // * print out unique values
            cout << "Unique values for column " << i << ": ";
            for (size_t j = 0; j < unique_vals.size(); j++) {
                cout << unique_vals[j] << " ";
            }
            cout << endl;

            // TODO: Update col_ptr to match beginning of column
            // ? Store the number of runs until the next column? would be shorter then the number of values in between
            int num_runs = 0;

            // LOOP2: Construct each Run
            for (unsigned int k = 0; k < unique_vals.size(); k++) {

                // memcopy unique value into data and iterate con_ptr
                memcpy(con_ptr, &unique_vals[k], val_t);
                con_ptr += val_t;

                // create pointer to index type
                uint8_t* index_ptr = con_ptr;

                // memcpy the index type of the run
                uint8_t index_t = row_t;
                memcpy(con_ptr, &index_t, 1);
                con_ptr += 1;

                // * Print out the vector up to this point using con_ptr
                // cout << "Vector up to index type: " << endl;
                // for (size_t i = 0; i < con_ptr - data.data(); i++) {
                //     cout << (int) data[i] << " ";
                // }
                // cout << endl;


                // Find each indicie of the unique value and push to data
                // ? more efficient to do find all unique value indicies at once?
                size_t max = 0;
                size_t num_indicies = 0;

                for (int j = 3; j < vals.size(); j += 3) {
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
                temp.reserve(num_indicies * index_t + 1);

                for (int j = 0; j < num_indicies; j++) {
                    
                    uint8_t* temp_ptr = temp.data();

                    memcpy(temp_ptr + (j * index_t), // Where
                           con_ptr - (num_indicies * row_t) + (j * row_t), // What (end of indicies -> beginning of indicies -> current index)
                           index_t); // How much
                    
                    // memcpy a zero to the end of the temp vector
                    memcpy(temp_ptr + (num_indicies * index_t), &delim, 1);
                }

                // Overwrite old indexes with new indexes
                con_ptr -= num_indicies * row_t;
                memcpy(con_ptr, temp.data(), num_indicies * index_t + 1);
                con_ptr += num_indicies * index_t;


                // Update index_t
                memcpy(index_ptr, &index_t, 1);

                // Update num_runs
                num_runs++;


                // * Print Vector up until this point using con_ptr
                cout << "Vector up to run " << k << ": " << endl;
                for (size_t i = 0; i < con_ptr - data.data(); i++) {
                    cout << (int) data[i] << " ";
                }
                cout << endl;
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

    // Create a test vector
    vector<unsigned int> test = {36, 3, 58,
        
                                 1, 0, 1,
                                 2, 0, 1, 
                                 3, 0, 2,
                                 5, 0, 3,
                                 7, 0, 1,
                                 9, 0, 2,
                                 10, 0, 2,
                                 11, 0, 1,
                                 12, 0, 1,
                                 14, 0, 2,
                                 15, 0, 3,
                                 19, 0, 1,
                                 20, 0, 3,
                                 23, 0, 1, 
                                 24, 0, 3,
                                 25, 0, 1,
                                 26, 0, 2,
                                 29, 0, 3,
                                 30, 0, 2,
                                 32, 0, 1,
                                 34, 0, 1,
                                 
                                 0, 1, 1,
                                 9, 1, 1,
                                 13, 1, 2,
                                 14, 1, 1,
                                 15, 1, 1,
                                 16, 1, 1,
                                 20, 1, 2,
                                 21, 1, 1,
                                 23, 1, 1,
                                 24, 1, 2,
                                 25, 1, 2,
                                 26, 1, 1,
                                 27, 1, 3,
                                 29, 1, 3,
                                 31, 1, 1,
                                 32, 1, 1,
                                 35, 1, 1,
                                 
                                 0, 2, 2,
                                 1, 2, 3,
                                 3, 2, 1,
                                 4, 2, 3,
                                 6, 2, 1,
                                 7, 2, 3,
                                 9, 2, 4,
                                 10, 2, 8,
                                 12, 2, 2,
                                 13, 2, 1,
                                 14, 2, 1,
                                 16, 2, 2,
                                 17, 2, 3,
                                 19, 2, 3,
                                 23, 2, 3,
                                 24, 2, 3,
                                 28, 2, 1,
                                 30, 2, 1,
                                 31, 2, 1,
                                 35, 2, 8};

    // Create a DeBruinesComp object
    DeBruinesComp test_comp(test);

    
    cout << "Hello, World!" << endl;
    return 0;
}