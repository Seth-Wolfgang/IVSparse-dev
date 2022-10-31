#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <cstdint>
#include <typeinfo>
#include <bits/stdc++.h>

using namespace std;

class DeBruinesComp
{
private:
    // Metadata
    int magic = 0x361212; // File signiture bytes
    unsigned char row_t = 1;
    unsigned char col_t = 1;
    uint8_t val_t = 1;
    size_t num_vals;
    size_t num_rows; // Number of rows in the matrix
    size_t num_cols; // Number of columns in the matrix

    // Data
    vector<vector<unsigned char>> data; // Compressed data by column

public:
    // Constructor for CSC Matrix
    DeBruinesComp(const vector<unsigned int> &vals,
                  const vector<unsigned int> &row,
                  const vector<unsigned int> &col,
                  const vector<int> dim)
    {

        num_vals = vals.size(); // Number of non-zero values in the matrix
        num_rows = dim[0];      // Number of rows in the matrix
        num_cols = dim[1];      // Number of columns in the matrix

        // sort vals by column into a vector of vectors
        vector<vector<unsigned int>> vals_by_col; // Vector of vectors of vals sorted by column
        vector<vector<unsigned int>> row_by_col;  // Vector of vectors of rows indices sorted by column
        vector<unsigned int> temp;                // Temp vector to store vals in a column
        vector<unsigned int> temp_row;            // Temp vector to store row indices in a column
        for (int i = 0; i < dim[1]; i++)
        {
            int diff = col[i + 1] - col[i]; // Number of vals in a column
            for (int j = 0; j < diff; j++)
            {
                temp.push_back(vals[col[i] + j]);    // Add vals to temp vector
                temp_row.push_back(row[col[i] + j]); // Add row indices to temp vector
            }
            vals_by_col.push_back(temp);    // Add temp vector to vals_by_col
            row_by_col.push_back(temp_row); // Add temp vector to row_by_col
            temp.clear();                   // Clear temp vector
            temp_row.clear();               // Clear temp vector
        }

        // print vals_by_col
        for (int i = 0; i < vals_by_col.size(); i++)
        {
            for (int j = 0; j < vals_by_col[i].size(); j++)
            {
                cout << vals_by_col[i][j] << " ";
            }
            cout << endl;
        }

        // print row_by_col
        for (int i = 0; i < row_by_col.size(); i++)
        {
            for (int j = 0; j < row_by_col[i].size(); j++)
            {
                cout << row_by_col[i][j] << " ";
            }
            cout << endl;
        }

        // run length encode the vals_by_col vector
        for (int i = 0; i < vals_by_col.size(); i++)
        {
            sort(vals_by_col[i].begin(), vals_by_col[i].end()); // Sort the vals in a column
            vals_by_col[i] = run_length_encode(vals_by_col[i]); // Run length encode each column
            vals_by_col[i].shrink_to_fit();
        }

        // print vals_by_col
        cout << endl;
        for (int i = 0; i < vals_by_col.size(); i++)
        {
            for (int j = 0; j < vals_by_col[i].size(); j++)
            {
                cout << vals_by_col[i][j] << " ";
            }
            cout << endl;
        }

        // Compress each column
        vector<vector<unsigned char>> compressed_cols; // Vector of vectors of compressed cols
        for (int i = 0; i < vals_by_col.size(); i++)
        {

            // TODO: Fix seg fault below

            // unsigned char* p = compressed_cols[i].data(); // Pointer to the beginning of the vector

            // // Reserve space for the compressed column
            // size_t col_size = 0;
            // for (int j = 1; j < vals_by_col[i].size(); j+=2) {
            //     col_size += val_t * vals_by_col[i][j] + 3;
            // }
            // try {
            //     compressed_cols[i].reserve(col_size);
            // } catch (std::length_error) {
            //     cout << "Error: column too large" << endl;
            // }

            // memcopy the uncompressed data into compressed vector
            for (int j = 0; j < vals_by_col[i].size(); j += 2)
            {
                int val = vals_by_col[i][j];          // value for this run
                int num_runs = vals_by_col[i][j + 1]; // number of times value appears in column
                // find all indexes of val in row
                vector<int> indexes; // Vector of indexes of val in row
                for (int k = 0; k < row.size(); k++)
                {
                    if (row[k] == val)
                    {
                        indexes.push_back(k);
                    }
                } // indexes now contains all indexes of val in row

                // print indexes
                cout << endl;
                for (int k = 0; k < indexes.size(); k++)
                {
                    cout << indexes[k] << " ";
                }
                cout << endl;
            }
        }
    }

    // Run length encode a vector of values
    vector<unsigned int> run_length_encode(const vector<unsigned int> &vals)
    {
        vector<unsigned int> encoded;
        unsigned int run_length = 1;
        unsigned int prev_val = vals[0];
        for (int i = 1; i < vals.size(); i++)
        {
            if (vals[i] == prev_val)
            {
                run_length++;
            }
            else
            {
                encoded.push_back(prev_val);
                encoded.push_back(run_length);
                run_length = 1;
                prev_val = vals[i];
            }
        }
        encoded.push_back(prev_val);
        encoded.push_back(run_length);
        return encoded;
    }
};

int main()
{
    // generate a csc matrix
    vector<unsigned int> vals = {1, 2, 1, 3, 4, 3, 1, 4, 4, 1, 1, 1, 3, 2,
                                 2, 2, 1, 3, 1, 1, 3, 1, 2, 3, 4, 5, 6, 1, 1, 1,
                                 2, 3, 1, 1, 2, 2, 2, 3, 6, 1, 2, 3, 2};
    vector<unsigned int> rows = {1, 2, 5, 6, 8, 12, 14, 16, 17, 18, 19, 20, 21, 22,
                                 0, 1, 2, 3, 6, 7, 9, 11, 12, 14, 15, 16, 19, 21, 22, 23,
                                 1, 2, 3, 4, 5, 7, 9, 13, 14, 18, 19, 21, 23};
    vector<unsigned int> cols = {0, 14, 30, 43}; // 43 is the number of vals in the matrix
    vector<int> dim = {24, 3};

    DeBruinesComp dbc1 = DeBruinesComp(vals, rows, cols, dim);

    return 0;
}