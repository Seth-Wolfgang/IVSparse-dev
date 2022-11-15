// Needed Includes
#include <cstdint>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <cstring>

// Potentially Undeeded Includes
#include <set>

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

    size_t num_runs = 0;
    uint8_t* ptr;
    uint8_t* data;

    void allocate() {
        data = (uint8_t*) malloc(num_vals * 4 * val_t);
        if (!data) {
            cerr << "Malloc Failed" << endl;
        }
        ptr = data;
    }

    uint8_t byte_width(size_t size) {
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

    //template <typename T>
    DeBruinesComp(const unsigned int *mat, size_t rows, size_t cols, size_t vals) {

        num_rows = rows;
        num_cols = cols;
        num_vals = vals;

        size_t max_row = 0;
        size_t max_col = 0;
        size_t max_val = 0;

        for (size_t i = 0; i < vals * 3; i += 3) {
            if (mat[i] > max_row) {
                max_row = mat[i];
            }
            if (mat[i + 1] > max_col) {
                max_col = mat[i + 1];
            }
            if (mat[i + 2] > max_val) {
                max_val = mat[i + 2];
            }
        }

        row_t = byte_width(max_row);
        col_t = byte_width(max_col);
        val_t = byte_width(max_val);

        allocate();

        uint8_t types[3] = {row_t, col_t, val_t};

        memcpy(ptr, &types, 3);
        ptr += 3;

        memcpy(ptr, &num_rows, row_t);
        memcpy(ptr + row_t, &num_cols, col_t);
        ptr += row_t + col_t;

        uint8_t* col_ptr = ptr;
        col_ptr += col_t;

        ptr += num_cols * col_t;

        // Loop 1:
        for (size_t i = 0; i < num_cols; i++) {
            set<unsigned int> unique_vals_set;

            for (size_t j = 0; j < num_vals * 3; j += 3) {
                if (mat[j + 1] == i) {
                    unique_vals_set.insert(mat[j+2]);
                }
            }

            unsigned int* uniques = (unsigned int*) malloc(unique_vals_set.size() * sizeof(unsigned int));

            size_t it = 0;
            set<unsigned int>::iterator itr;
            for (itr = unique_vals_set.begin(); itr != unique_vals_set.end(); itr++) {
                uniques[it] = *itr;
                it++;
            }

            // Loop 2:
            for (size_t k = 0; k < unique_vals_set.size(); k++) {
                memcpy(ptr, &uniques[k], val_t);
                ptr += val_t;

                uint8_t* idx = ptr;

                uint8_t idx_t = row_t;
                memcpy(ptr, &idx_t, 1);
                ptr++;

                size_t max = 0;
                size_t num_indicies = 0;
                size_t previous;

                for (size_t j = 0; j < num_vals * 3; j += 3) {
                    if (mat[j + 1] == i && mat[j + 2] == uniques[k]) {

                        if (ptr == idx + 1) {
                            memcpy(ptr, &mat[j], row_t);

                            previous = mat[j];
                            ptr += row_t;
                            max = mat[j];
                            num_indicies++;
                        } else {
                            size_t delta = mat[j] - previous;

                            memcpy(ptr, &delta, row_t);
                            ptr += row_t;

                            if (delta > max) {
                                max = delta;
                            }

                            num_indicies++;
                            previous = mat[j];
                        }

                    }
                }

                ptr -= num_indicies * row_t;

                uint8_t old_idx_t = idx_t;
                idx_t = byte_width(max);

                uint8_t temp[num_indicies * idx_t];

                for (size_t j = 0; j < num_indicies; j++) {

                    memcpy(temp + (j * idx_t), ptr + (j * row_t), idx_t);

                }

                memcpy(ptr, temp, num_indicies * idx_t);
                ptr += num_indicies * idx_t;

                memcpy(ptr, &delim, 1);
                ptr++;

                num_runs++;
            }


            if (i != num_cols - 1) {
                memcpy(col_ptr, &num_runs, col_t);
                col_ptr += col_t;
            }

            free(uniques);
        }

        ptr--;

        data = (uint8_t*) realloc(data, ptr - data);

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
    // Create a test vector
    unsigned int test[58*3] = {1, 0, 1,
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
    DeBruinesComp test_comp(test, 36, 3, 58);
    return 0;
};