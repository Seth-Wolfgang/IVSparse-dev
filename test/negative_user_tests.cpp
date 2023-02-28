#include "../CSF/SparseMatrix"
#include "../misc/matrix_creator.cpp"
#include <iostream>
#include <cstdlib>


int main (int argc, char** argv) {

    // Create a random matrix
    int numRows = 50;
    int numCols = 50;
    int sparsity = 4;
    uint64_t seed = 1956553944;
    //uint64_t seed = rand();

    // generating a large random eigen sparse
    Eigen::SparseMatrix<int> myMatrix_e(numRows, numCols);
    myMatrix_e.reserve(Eigen::VectorXi::Constant(numRows, numCols));
    myMatrix_e = generateMatrix<int>(numRows, numCols, sparsity, seed);
    myMatrix_e.makeCompressed();

    // create a random eigen matrix of type double
    Eigen::SparseMatrix<double> myMatrix2_e(numRows, numCols);
    myMatrix2_e.reserve(Eigen::VectorXi::Constant(numRows, numCols));
    myMatrix2_e = generateMatrix<double>(numRows, numCols, sparsity, seed);
    myMatrix2_e.makeCompressed();

    // create a random eigen matrix of type float
    Eigen::SparseMatrix<float> myMatrix3_e(numRows, numCols);
    myMatrix3_e.reserve(Eigen::VectorXi::Constant(numRows, numCols));
    myMatrix3_e = generateMatrix<float>(numRows, numCols, sparsity, seed);
    myMatrix3_e.makeCompressed();

    // create a random eigen matrix of type uint64_t
    Eigen::SparseMatrix<uint64_t> myMatrix4_e(numRows, numCols);
    myMatrix4_e.reserve(Eigen::VectorXi::Constant(numRows, numCols));
    myMatrix4_e = generateMatrix<uint64_t>(numRows, numCols, sparsity, seed);
    myMatrix4_e.makeCompressed();


    //! Time to break stuff yayyy

    //! things that are broken but need checks still
        //* What if index type isn't big enough to store the number of rows or cols??
    
    
    // Break the matrix by giving wrong types and compression levels

    // CSF::SparseMatrix<int, uint64_t, 4> myMatrix1(myMatrix_e);
    // CSF::SparseMatrix<double, uint64_t, 4> myMatrix2(myMatrix2_e);
    // CSF::SparseMatrix<float, uint64_t, 4> myMatrix3(myMatrix3_e);
    // CSF::SparseMatrix<uint64_t, uint64_t, 4> myMatrix4(myMatrix4_e);

    // CSF::SparseMatrix<char> myMatrix5(myMatrix_e);
    // CSF::SparseMatrix<bool> myMatrix6(myMatrix_e);

    CSF::SparseMatrix<int, double, 2> myMatrix7(myMatrix_e);
    CSF::SparseMatrix<int, float, 2> myMatrix8(myMatrix_e);
    CSF::SparseMatrix<int, char, 2> myMatrix9(myMatrix_e);
    CSF::SparseMatrix<int, bool, 2> myMatrix10(myMatrix_e);
    myMatrix10.write("test.txt");

    CSF::SparseMatrix<int, double, 3> myMatrix11(myMatrix_e);

    return 0;
}