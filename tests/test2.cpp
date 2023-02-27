#include "../CSF/SparseMatrix"
#include "../misc/matrix_creator.cpp"
#include <iostream>

int main(int argc, char **argv)
{
    // Create a random matrix
    int numRows = 100000;
    int numCols = 100000;
    int sparsity = 2;
    uint64_t seed = 1956553944;

    // generating a large random eigen sparse
    Eigen::SparseMatrix<int> myMatrix(numRows, numCols);
    myMatrix.reserve(Eigen::VectorXi::Constant(numRows, numCols));
    myMatrix = generateMatrix<int>(numRows, numCols, sparsity, seed);
    myMatrix.makeCompressed();

    // Create a CSF matrix

    CSF::SparseMatrix<int, int, 3> myCSFMatrix(myMatrix);

    // print out the dimensions
    std::cout << myCSFMatrix.rows() << std::endl;
    std::cout << myCSFMatrix.cols() << std::endl;

    // print out the compression size
    std::cout << myCSFMatrix.byte_size() << std::endl;

    // print out the number of nonzeros
    std::cout << myCSFMatrix.nonzeros() << std::endl;
}