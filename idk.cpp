#include "CSF/SparseMatrix"
#include "misc/matrix_creator.cpp"
#include <iostream>

int main(int argc, char **argv)
{

    int numRows = 50;
    int numCols = 50;
    int sparsity = 4;
    uint64_t seed = 1956553944;

    // generating a large random eigen sparse
    Eigen::SparseMatrix<int> myMatrix_e(numRows, numCols);
    myMatrix_e.reserve(Eigen::VectorXi::Constant(numRows, numCols));
    myMatrix_e = generateMatrix<int>(numRows, numCols, sparsity, seed);
    myMatrix_e.prune(0);
    myMatrix_e.makeCompressed();

    // create a csf sparse matrix
    CSF::SparseMatrix<int, uint64_t, 3> myMatrix_csf3(myMatrix_e);

    // make an iterator
    CSF::SparseMatrix<int, uint64_t, 3>::Iterator it3(myMatrix_csf3);

    // create an eigen matrix from the csf matrix
    Eigen::SparseMatrix<int> myMatrix_e2 = myMatrix_csf3.to_eigen();

    // create a csf 1 matrix from the eigen matrix
    CSF::SparseMatrix<int, uint64_t, 1> myMatrix_csf1(myMatrix_e2);

    // create a csf1 matrix from the original eigen matrix
    CSF::SparseMatrix<int, uint64_t, 1> myMatrix_csf1_2(myMatrix_e);

    // create a csf2 matrix from the csf 1 matrix
    CSF::SparseMatrix<int, uint64_t, 2> myMatrix_csf2 = myMatrix_csf1.to_csf2();

    std::cout << "Value at (2, 1): " << myMatrix_csf2.coeff(2, 1) << std::endl;
    std::cout << "Value at (2, 1): " << myMatrix_e.coeff(2, 1) << std::endl;

    //std::cout << myMatrix_e << std::endl;


    return 0;
}