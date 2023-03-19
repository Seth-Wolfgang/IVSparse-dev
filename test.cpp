#include <iostream>
#include "CSF/SparseMatrix"
#include "misc/matrix_creator.cpp"

int main() {

    int numRows = 50;
    int numCols = 50;
    int sparsity = 4;
    uint64_t seed = 1956553944;
    // uint64_t seed = rand();

    // generating a large random eigen sparse
    Eigen::SparseMatrix<int> myMatrix_e(numRows, numCols);
    myMatrix_e.reserve(Eigen::VectorXi::Constant(numRows, numCols));
    myMatrix_e = generateMatrix<int>(numRows, numCols, sparsity, seed);
    myMatrix_e.prune(0);
    myMatrix_e.makeCompressed();

    // generating a large random CSF sparse
    CSF::SparseMatrix<int> myMatrix_csf(myMatrix_e);

    return 0;
}