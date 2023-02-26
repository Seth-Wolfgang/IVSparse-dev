#include "../CSF/SparseMatrix"
#include "../misc/matrix_creator.cpp"
#include <iostream>

/*
Things to test/get working:
1. Decompressor
2. Floats and doubles
3. negative numbers
4. CSF vectors
5. CSF -> Eigen
6. << operator
7. index types
8. redundancy checker
9. CSF1 write and read from file
*/

int main (int argc, char** argv) {

    // Create a random matrix
    int numRows = 50;
    int numCols = 50;
    int sparsity = 4;
    uint64_t seed = 1956553944;

    // generating a large random eigen sparse
    Eigen::SparseMatrix<int> myMatrix(numRows, numCols);
    myMatrix.reserve(Eigen::VectorXi::Constant(numRows, numCols));
    myMatrix = generateMatrix<int>(numRows, numCols, sparsity, seed);
    myMatrix.makeCompressed();


    // --- Eigen + CSF Testing --- //

    //* Integer and default Index and Value Type

    // Create a CSF matrix from an Eigen matrix (defualt)
    CSF::SparseMatrix<int> mat1(myMatrix);
    mat1.write("mat1.csf");

    // Create a CSF matrix from an Eigen matrix (CSF2)
    CSF::SparseMatrix<int, int, 2> mat2(myMatrix);
    //mat2.write("mat2.csf");

    // Create a CSF matrix from an Eigen matrix (CSF1)
    CSF::SparseMatrix<int, int, 1> mat3(myMatrix);
    //! (Not implemented yet) mat3.write("mat3.csf");


    //* Non Integer index types
    CSF::SparseMatrix<int, uint16_t, 3> mat4(myMatrix);
    //mat4.write("mat4.csf");

    CSF::SparseMatrix<int, uint32_t, 3> mat5(myMatrix);
    //mat5.write("mat5.csf");
    
    CSF::SparseMatrix<int, uint64_t, 3> mat6(myMatrix);
    //mat6.write("mat6.csf");

    CSF::SparseMatrix<int, uint64_t, 2> mat7(myMatrix);
    //mat7.write("mat7.csf");

    CSF::SparseMatrix<int, uint64_t, 1> mat8(myMatrix);
    mat8.write("mat8.csf");

    // create an eigen matrix from mat8
    Eigen::SparseMatrix<int> mat8_eigen = mat8.to_eigen();

    // create a random eigen matrix of type double
    Eigen::SparseMatrix<double> myMatrix2(numRows, numCols);
    myMatrix2.reserve(Eigen::VectorXi::Constant(numRows, numCols));
    myMatrix2 = generateMatrix<double>(numRows, numCols, sparsity, seed);
    myMatrix2.makeCompressed();

    // Create a CSF matrix from an Eigen matrix (defualt)
    CSF::SparseMatrix<double, uint16_t, 2> mat9(myMatrix2);
    mat9.write("mat9.csf");

    // create a random eigen matrix of type float
    Eigen::SparseMatrix<float> myMatrix3(numRows, numCols);
    myMatrix3.reserve(Eigen::VectorXi::Constant(numRows, numCols));
    myMatrix3 = generateMatrix<float>(numRows, numCols, sparsity, seed);
    myMatrix3.makeCompressed();

    // Create a CSF matrix from an Eigen matrix (defualt)
    CSF::SparseMatrix<float, uint16_t, 2> mat10(myMatrix3);
    //mat10.write("mat10.csf");


    return 0;
}