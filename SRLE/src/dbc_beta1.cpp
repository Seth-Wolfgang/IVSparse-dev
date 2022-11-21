// Needed Includes
#include <cstdint>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <cstring>
#include <bits/stdc++.h>

// Iterator Includes
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iterator>
#include <fstream>
#include <algorithm>

// Includes needed for constucting compression
#include <map>
#include <vector>

// Wrapper includes
#include <Eigen/Sparse>

using namespace std;

class DeBruinesComp
{
private:
    // ! Magic is currently unused
    int magic = 0x36121236;
    uint8_t delim = 0;

    size_t num_rows;
    size_t num_cols;
    size_t num_vals;

    uint8_t row_t;
    uint8_t col_t;
    uint8_t val_t;

    uint8_t *ptr;
    uint8_t *data;
    size_t size;

    void allocate()
    {
        // ! Malloc currently allocates much more than needed
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
    // Constructor to take in an eigen sparse matrix
    // ! Is temporary, still gross, just a proof of concept
    template <typename T>
    DeBruinesComp(Eigen::SparseMatrix<T> &mat)
    {
        // Find number of non-zero elements
        num_vals = mat.nonZeros();

        T non_zero[num_vals];
        T rows_indices[num_vals];
        T col_indices[num_vals];

        for (size_t k = 0; k < mat.outerSize(); ++k) {
            for (typename Eigen::SparseMatrix<T>::InnerIterator it(mat, k); it; ++it) {
                non_zero[k] = it.value();
                rows_indices[k] = it.row();
                col_indices[k] = it.col();
            }
        }

        // print out non_zero, rows_indices, and col_indices
        cout << "non_zero: " << endl;
        for (size_t k = 0; k < num_vals; ++k) {
            cout << non_zero[k] << " ";
        }

        cout << endl << "rows_indices: " << endl;
        for (size_t k = 0; k < num_vals; ++k) {
            cout << rows_indices[k] << " ";
        }

        cout << endl << "col_indices: " << endl;
        for (size_t k = 0; k < num_vals; ++k) {
            cout << col_indices[k] << " ";
        }

        // Create new debruines compression
        DeBruinesComp(non_zero, rows_indices, col_indices, mat.rows(), mat.cols(), num_vals);
    }

    /*  Takes in a COO Matrix and converts it to a DeBruinesComp Matrix
        @param *vals: Pointer to the values of the COO Matrix
        @param *rows: Pointer to the rows of the COO Matrix
        @param *cols: Pointer to the cols of the COO Matrix
        @param val_num: Number of vals in the COO Matrix
        @param row_num: Number of rows in the COO Matrix
        @param col_num: Number of cols in the COO Matrix */
    template <typename values, typename rowcols>
    DeBruinesComp(const values *vals, const rowcols *rows, const rowcols *cols, size_t val_num, size_t row_num, size_t col_num)
    {

        // Initialize the number of rows, cols, and vals
        num_rows = row_num;
        num_cols = col_num;
        num_vals = val_num;

        size_t max_val = 0;

        // Finds max value in vals to be compressed to val_type
        // ? Could refactor to be in first loop and construct metadata between making dictionary and building runs
        for (size_t i = 0; i < num_vals; i++)
        {
            if (vals[i] > max_val)
            {
                max_val = vals[i];
            }
        }

        // Finds the smallest type that can hold the max value
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

        // Leave pointer to update col pointers later
        uint64_t *col_ptr = (uint64_t *)ptr;
        col_ptr[0] = 0;
        col_ptr++;

        ptr += num_cols * 8;

        uint8_t previous_idx = 0;

        // Column Loop
        for (size_t i = 0; i < num_cols; i++)
        {
            // Create dictionary with all metadata
            map<values, vector<rowcols>> unique_vals;

            // move through data (FOR THE COLUMN) and if value is unique, add it to dictionary, if value is not unique, add index to that value in dictionary
            // First val in vector is the previous index (used for positive delta encoding)
            // TODO Refactor to only run through the column being encoded
            for (size_t j = 0; j < num_vals; j++)
            {
                if (unique_vals.count(vals[j]) == 1 && cols[j] == i)
                {
                    // Val Exists in Dict

                    size_t delta = rows[j] - unique_vals[vals[j]][0];

                    unique_vals[vals[j]].push_back(delta);

                    unique_vals[vals[j]][0] = rows[j];
                }
                else if (cols[j] == i)
                {
                    // Val does not Exist in dict

                    vector<rowcols> temp = {rows[j], rows[j]};
                    unique_vals[vals[j]] = temp;
                }
            }

            // Loop through dictionary and construct compression
            for (auto i : unique_vals)
            {
                memcpy(ptr, &i.first, val_t);
                ptr += val_t;

                uint8_t *idx = ptr;
                uint8_t idx_t = byte_width(*max_element(i.second.begin(), i.second.end()));
                memcpy(ptr, &idx_t, 1);
                ptr++;

                // Construct Run
                for (auto j : i.second)
                {
                    if (j != i.second[0])
                    {
                        memcpy(ptr, &j, idx_t);
                        ptr += idx_t;
                    }
                }

                for (size_t j = 0; j < idx_t; j++)
                {
                    memcpy(ptr, &delim, 1);
                    ptr++;
                }

                previous_idx = idx_t;
            }

            // update col_ptr
            if (i != num_cols - 1)
            {
                size_t col_location = ptr - data;
                memcpy(col_ptr, &col_location, 8);
                col_ptr++;
            }
        }

        // Chop off end delimiters
        ptr -= previous_idx;

        // Resize data to fit actual size
        size = ptr - data;
        data = (uint8_t*) realloc(data, ptr - data);
    }

    ~DeBruinesComp()
    {
        free(data);
    }

    void print()
    {
        cout << "Printing DeBruinesComp Matrix" << endl;
        cout << "Row Type: " << (int)row_t << endl;
        cout << "Col Type: " << (int)col_t << endl;
        cout << "Val Type: " << (int)val_t << endl;
        cout << "Num Rows: " << num_rows << endl;
        cout << "Num Cols: " << num_cols << endl;
        cout << "Num Vals: " << num_vals << endl;
        cout << "Data: " << endl;
        for (size_t i = 0; i < size; i++)
        {
            cout << (int)data[i] << " ";
        }
        cout << endl;
        cout << endl;
    }

    // Write to file
    void write(string filename)
    {
        ofstream file(filename, ios::out | ios::binary);
        file.write((char *)data, ptr - data);
        file.close();
    }

    // Read from file
    // ! HAS A MEMORY LEAK SOMEWHERE >:(
    void read(string filename)
    {
        // Open file
        ifstream file(filename, ios::in | ios::binary);

        // Get file size
        file.seekg(0, ios::end);
        size_t size = file.tellg();
        file.seekg(0, ios::beg);

        // Allocate memory
        data = (uint8_t *)malloc(size);

        // Read data
        file.read((char *)data, size);
        file.close();

        // Set pointer and itialize variables
        ptr = data;
        row_t = *ptr;
        ptr++;
        col_t = *ptr;
        ptr++;
        val_t = *ptr;
        ptr++;
        memcpy(&num_rows, ptr, row_t);
        memcpy(&num_cols, ptr + row_t, col_t);
        ptr += row_t + col_t;

        // Put pointer at end of data
        ptr += size - (ptr - data);

        size = ptr - data;
    }

    template <typename T>
    class const_array_iterator
    {
        // todo: clean the vocabulary
    private:
        uint32_t magicByteSize; //= params[0];
        uint32_t rowType;       //= params[1];
        uint32_t nRows;         //= params[2];
        uint32_t colType;       //= params[3];
        uint32_t nCols;         //= params[4];
        uint32_t valueWidth;    //= params[5];
        uint32_t oldIndexType;  //= params[6];
        int newIndexWidth;      // basically how many bytes we read, NOT ACTUALLY THE TYPE
        char *end;
        char *fileData;
        char *arrayPointer;
        uint64_t index = 0;
        // int (*functionPointer)();
        T value;
        uint64_t sum = 0;

    public:
        const_array_iterator(const char *filePath)
        {

            // set up the iterator
            readFile(filePath);

            // read first 28 bytes of fileData put it into params -> metadata
            uint32_t params[7];

            memcpy(&params, arrayPointer, 28); // 28 is subject to change depending on magic bytes
            arrayPointer += 32;                // first delimitor is 4 bytes

            magicByteSize = params[0];
            rowType = params[1];
            nRows = params[2];
            colType = params[3];
            nCols = params[4];
            valueWidth = params[5];
            oldIndexType = params[6];

            memcpy(&value, arrayPointer, valueWidth);
            arrayPointer += valueWidth;
            memcpy(&newIndexWidth, arrayPointer, 1);
            arrayPointer++; // this should make it point to first index


        } // end of constructor

        // todo make this return type T
        T &operator*() { return value; };

        uint64_t getSum() { return sum; };

        // template<typename indexType>
        const uint64_t operator++()
        {
            // TODO template metaprogramming
            // todo through an exception if we request something smaller than the size of the index

            uint64_t newIndex = 0; // get rid of in future versions

            memcpy(&newIndex, arrayPointer, newIndexWidth);
            arrayPointer += newIndexWidth;
            sum += value;

            if (newIndex == 0 && index != 0)
            { // change that

                memcpy(&value, arrayPointer, valueWidth);
                arrayPointer += valueWidth;

                memcpy(&newIndexWidth, arrayPointer, 1);
                arrayPointer++;

                memset(&index, 0, 8);
                memcpy(&index, arrayPointer, newIndexWidth);
            }
            return index += newIndex;
        }

        // equality operator
        operator bool()
        {
            return end >= arrayPointer;
        }

        // marginally faster
        inline void readFile(const char *filePath)
        {
            // read a file using the C fopen function and store to fileData
            FILE *file = fopen(filePath, "rb");
            fseek(file, 0, SEEK_END);
            int sizeOfFile = ftell(file);
            fileData = (char *)malloc(sizeof(char *) * sizeOfFile);
            fseek(file, 0, SEEK_SET);
            fread(fileData, sizeOfFile, 1, file);
            fclose(file);
            cout << "Size of file: " << sizeOfFile << endl;
            arrayPointer = fileData;
            end = fileData + sizeOfFile;
        }
    };
};

int main()
{

    int cols[58] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2};
    int rows[58] = {1, 2, 3, 5, 7, 9, 10, 11, 12, 14, 15, 19, 20, 23, 24, 25, 26, 29, 30, 32, 34, 0, 9, 13, 14, 15, 16, 20, 21, 23, 24, 25, 26, 27, 29, 31, 32, 35, 0, 1, 3, 4, 6, 7, 9, 10, 12, 13, 14, 16, 17, 19, 23, 24, 28, 30, 31, 35};
    int vals[58] = {1, 1, 2, 3, 1, 2, 2, 1, 1, 2, 3, 1, 3, 1, 3, 1, 2, 3, 300, 1, 1, 1, 1, 2, 1, 1, 1, 2, 1, 1, 2, 2, 1, 3, 3, 1, 1, 1, 2, 3, 1, 3, 1, 3, 4, 8, 2, 1, 1, 2, 3, 3, 3, 3, 1, 1, 1, 8};

    size_t val_num = 58;
    size_t row_num = 36;
    size_t col_num = 3;

    DeBruinesComp temp_comp(vals, rows, cols, val_num, row_num, col_num);
    temp_comp.print();

    temp_comp.write("test2.bin");

    // Create an iterator for temp_comp
    

    //temp_comp.read("test.bin");

    // Create an eigen sparse matrix
    cout << "Testing Eigen" << endl;

    

    return 0;
};