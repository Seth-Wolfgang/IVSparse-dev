// Needed Includes
#include <cstdint>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <cstring>
#include <bits/stdc++.h>

#include <map>
#include <vector>

using namespace std;

class DeBruinesComp {
    private:

    int magic = 0x36121236;
    uint8_t delim = 0;

    size_t num_rows;
    size_t num_cols;
    size_t num_vals;

    uint8_t row_t;
    uint8_t col_t;
    uint8_t val_t;

    uint8_t* ptr;
    uint8_t* data;

    void allocate() {
        data = (uint8_t *)malloc(num_vals * 4 * val_t);
        if (!data)
        {
            cerr << "Malloc Failed" << endl;
        }
        ptr = data;
    }

    uint8_t byte_width(size_t size)
    {
        switch (size)
        {
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

    public:

    template <typename values, typename rowcols>
    DeBruinesComp(const values *vals, const rowcols *rows, const rowcols *cols, size_t val_num, size_t row_num, size_t col_num) {

        cout << "DeBruinesComp Beta V.1" << endl;

        num_rows = row_num;
        num_cols = col_num;
        num_vals = val_num;

        size_t max_val = 0;

        // Could refactor to be in first loop and construct metadata between making dictionary and building runs
        for (size_t i = 0; i < num_vals; i++) {
            if (vals[i] > max_val) {
                max_val = vals[i];
            }
        }

        row_t = byte_width(num_rows);
        col_t = byte_width(num_cols);
        val_t = byte_width(max_val);

        allocate();

        // Construct Metadata
        memcpy(ptr, &row_t, 1);
        ptr++;

        memcpy(ptr, &col_t, 1);
        ptr++;

        memcpy(ptr, &val_t, 1);
        ptr++;

        memcpy(ptr, &num_rows, row_t);
        memcpy(ptr + row_t, &num_cols, col_t);
        ptr += row_t + col_t;

        uint64_t *col_ptr = (uint64_t*) ptr;
        col_ptr[0] = 0;
        col_ptr += 8;

        ptr += num_cols * 8;

        uint8_t previous_idx = 0;

        // Column Loop
        for (size_t i = 0; i < num_cols; i++) {
            // Create dictionary with all metadata
            map<values, vector<rowcols>> unique_vals;

            // move through data (FOR THE COLUMN) and if value is unique, add it to dictionary, if value is not unique, add index to that value in dictionary

            // Refactor to only run through the column being encoded
            for (size_t j = 0; j < num_vals; j++) {
                if (unique_vals.count(vals[j]) == 1 && cols[j] == i) {
                    // Val Exists in Dict

                    // print out found value and its index
                    //cout << "Found Value Again: " << vals[j] << " at index: " << rows[j] << endl;

                    rowcols previous = unique_vals[vals[j]].front();
                    // calculate delta
                    for (size_t k = 1; k < unique_vals[vals[j]].size(); k++) {
                        previous += unique_vals[vals[j]][k];
                    }

                    rowcols delta = rows[j] - previous;

                    // print delta
                    //cout << "Delta: " << delta << endl;

                    unique_vals[vals[j]].push_back(delta);

                } else if (cols[j] == i) {
                    // Val does not Exist in dict

                    // print out found value and its index
                    //cout << "Found Value: " << vals[j] << " at index: " << rows[j] << endl;

                    vector<rowcols> temp = {rows[j]};
                    unique_vals[vals[j]] = temp;

                }
            }

            // Print out dictionary
            for (auto const& x : unique_vals) {
                cout << x.first << ": ";
                for (auto const& y : x.second) {
                    cout << y << " ";
                }
                cout << endl;
            }

            // Loop through dictionary and construct compression
            for (auto i : unique_vals) {
                memcpy(ptr, &i.first, val_t);
                ptr += val_t;

                uint8_t* idx = ptr;
                uint8_t idx_t = byte_width(*max_element(i.second.begin(), i.second.end()));
                memcpy(ptr, &idx_t, 1);
                ptr++;

                // Construct Run
                for (auto j : i.second) {
                    memcpy(ptr, &j, idx_t);
                    ptr += idx_t;
                }

                for (size_t j = 0; j < idx_t; j++) {
                    memcpy(ptr, &delim, 1);
                    ptr++;
                }

                previous_idx = idx_t;
            }

            // update col_ptr
            if (i != num_cols - 1) {
                size_t col_location = ptr - data;
                memcpy(col_ptr, &col_location, 8);
                col_ptr += 8;
            }

        }

        ptr -= previous_idx;

        data = (uint8_t*) realloc(data, ptr-data);

        cout << "Final Vector: " << endl;
        for (size_t i = 0; i < ptr - data; i++)
        {
            cout << (int)data[i] << " ";
        }
        cout << endl;
        cout << endl;

    }

    ~DeBruinesComp() {
        free(data);
        cout << "Dead" << endl;
    }
};

int main() {

    int cols[58] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, 2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2};
    int rows[58] = {1, 2, 3, 5, 7, 9, 10, 11, 12, 14, 15, 19, 20, 23, 24, 25, 26, 29, 30, 32, 34, 0, 9, 13, 14, 15, 16, 20, 21, 23, 24, 25, 26, 27, 29, 31, 32, 35, 0, 1, 3, 4, 6, 7, 9, 10, 12, 13, 14, 16, 17, 19, 23, 24, 28, 30, 31, 35};
    int vals[58] = {1, 1, 2, 3, 1, 2, 2, 1, 1, 2, 3, 1, 3, 1, 3, 1, 2, 3, 2, 1, 1, 1, 1, 2, 1, 1, 1, 2, 1, 1, 2, 2, 1, 3, 3, 1, 1, 1, 2, 3, 1, 3, 1, 3, 4, 8, 2, 1, 1, 2, 3, 3, 3, 3, 1, 1, 1, 8};

    size_t val_num = 58;
    size_t row_num = 36;
    size_t col_num = 3;

    DeBruinesComp temp_comp(vals, rows, cols, val_num, row_num, col_num);

    return 0;
};