#include <iostream>
#include "CSF/SparseMatrix"
#include <fstream>

using namespace std;

int main() {

    int rows = 46985;
    int cols = 124836;
    int nnz = 5410236;

    uint32_t *vals = new uint32_t[nnz];
    uint32_t *indices = new uint32_t[nnz];
    uint32_t *colPointers = new uint32_t[cols + 1];

    // read in data from file and store in vals, indices, colPointers

    fstream file("data/X_data.txt");

    int count = 0;

    for (string line; getline(file, line);) {

        int value = stoi(line);
        vals[count] = value;
        count++;
    }

    file.close();

    file.open("data/X_indices.txt");

    count = 0;

    for (string line; getline(file, line);) {

        int value = stoi(line);
        indices[count] = value;
        count++;
    }

    file.close();

    file.open("data/X_indptr.txt");

    count = 0;

    for (string line; getline(file, line);) {

        int value = stoi(line);
        colPointers[count] = value;
        count++;
    }

    file.close();

    // create sparse matrix
    CSF::SparseMatrix<uint32_t, uint32_t, 1> X1(vals, indices, colPointers, rows, cols, nnz);
    CSF::SparseMatrix<uint32_t, uint32_t, 2> X2(vals, indices, colPointers, rows, cols, nnz);
    CSF::SparseMatrix<uint32_t, uint32_t, 3> X3(vals, indices, colPointers, rows, cols, nnz);

    // print the sparse matrix byte size
    cout << "CSF1 Size: " << X1.byteSize() << endl;
    cout << "CSF2 Size: " << X2.byteSize() << endl;
    cout << "CSF3 Size: " << X3.byteSize() << endl;


    // free
    delete[] vals;
    delete[] indices;
    delete[] colPointers;

    return 0;

}