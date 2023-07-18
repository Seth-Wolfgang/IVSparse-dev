#include <Eigen/Sparse>
#include <IVSparse/SparseMatrix>
#include <iostream>

int main()
{

    int rows = 4;
    int cols = 4;
    int nnz = 4;

    int values[4] = {1, 2, 3, 4};
    int rowIndices[4] = {0, 1, 2, 3};
    int outerPointers[5] = {0, 1, 2, 3, 4};

    IVSparseSparseMatrix<int> matrix(values, rowIndices, outerPointers, rows, cols, nnz);

    matrix.print();
}