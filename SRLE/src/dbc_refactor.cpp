#include <cstdint>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <cstring>

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

    size_t num_runs;
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
    DeBruinesComp(const int *data, size_t rows, size_t cols, size_t vals) {

        num_rows = rows;
        num_cols = cols;
        num_vals = vals;

        size_t max_row = 0;
        size_t max_col = 0;
        size_t max_val = 0;

        for (size_t i = 0; i < vals * 3; i += 3) {
            if (data[i] > max_row) {
                max_row = data[i];
            }
            if (data[i + 1] > max_col) {
                max_col = data[i + 1];
            }
            if (data[i + 2] > max_val) {
                max_val = data[i + 2];
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

        

    }

    ~DeBruinesComp() {
        free(data);
        cout << "Dead" << endl;
    }

};

int main() {
    return 0;
};