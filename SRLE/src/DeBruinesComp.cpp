#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <string>
#include <Eigen>

using namespace std;

// Class for our compressed sparse matrix
class DeBruinesComp {
    public:
        // Iterator for the compressed sparse matrix
        struct ByteIterator {
            
        };

        // Public member function to read in a binary file from disk to a char vector
        void readBinaryFile(const char *filename, vector<char> &buffer) {
            // Open the file
            ifstream file(filename, ios::binary);

            // Get the starting point of the file
            streampos begin, end;
            begin = file.tellg();

            // Get the ending point of the file
            file.seekg(0, ios::end);
            end = file.tellg();

            // Get the size of the file
            int size = end - begin;

            // Go back to the starting point
            file.seekg(0, ios::beg);

            // Read the file
            buffer.resize(size);
            file.read(&data[0], size);
        }

        // Function to take an Eigen sparse matrix and compress it
        void compress(Eigen::SparseMatrix<double> &matrix) {
            // Get the number of rows and columns
            int rows = matrix.rows();
            int cols = matrix.cols();

            // Get the number of non-zero elements
            int nnz = matrix.nonZeros();

            // Get the number of non-zero elements per row
            vector<int> nnzPerRow(rows);
            for (int i = 0; i < rows; i++) {
                nnzPerRow[i] = matrix.row(i).nonZeros();
            }

            // Get the number of non-zero elements per column
            vector<int> nnzPerCol(cols);
            for (int i = 0; i < cols; i++) {
                nnzPerCol[i] = matrix.col(i).nonZeros();
            }

            // Get the row indices of the non-zero elements
            vector<int> rowIndices(nnz);
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < nnzPerRow[i]; j++) {
                    rowIndices.push_back(i);
                }
            }

            // Get the column indices of the non-zero elements
            vector<int> colIndices(nnz);
            for (int i = 0; i < cols; i++) {
                for (int j = 0; j < nnzPerCol[i]; j++) {
                    colIndices.push_back(i);
                }
            }

            // Get the values of the non-zero elements
            vector<double> values(nnz);
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < nnzPerRow[i]; j++) {
                    values.push_back(matrix.coeff(i, j));
                }
            }

        }

    private:
        vector<char> data;
};