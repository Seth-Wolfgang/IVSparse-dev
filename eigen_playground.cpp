#include <Eigen/Sparse>
#include <iostream>

#include "misc/matrix_creator.cpp"

int main(int argc, char** argv) {
    int numRows = 50;
    int numCols = 50;
    int sparsity = 5;
    uint64_t seed = 5645646546;

    // generating a large random eigen sparse
    Eigen::SparseMatrix<int> myMatrix(numRows, numCols);
    myMatrix.reserve(Eigen::VectorXi::Constant(numRows, numCols));
    myMatrix = generateMatrix<int>(numRows, numCols, sparsity, seed);
    myMatrix.makeCompressed();

    // print myMatrix
    std::cout << myMatrix << std::endl;

    Eigen::SparseMatrix<int>::InnerIterator it(myMatrix, 0);
    while (it) {
        std::cout << it.row() << " " << it.col() << " " << it.value() << std::endl;
        ++it;
    }


    for (size_t i = 0; i < myMatrix.cols(); i++) {

        for (Eigen::SparseMatrix<int>::InnerIterator it(myMatrix, i); it; ++it) {

        }
    }

    int *values = myMatrix.valuePtr();
    int *indexes = myMatrix.innerIndexPtr();
    int *col_p = myMatrix.outerIndexPtr();

    std::cout << "values: " << std::endl;
    for (size_t i = 0; i < myMatrix.nonZeros(); i++) {
        std::cout << values[i] << " ";
    }

    std::cout << std::endl;

    Eigen::SparseMatrix<int,, short> myMatrix2(numRows, numCols);

    return 0;

}
