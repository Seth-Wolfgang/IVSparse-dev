#include "../CSF/SparseMatrix"
#include "../misc/matrix_creator.cpp"
#include <iostream>

/*
TODO - 
1. Fix index typing, cast to uint64 when needed stop being lazy
2. Get the decompressor working (using iterator most likely)
3. Merging branches and testing
4. Writing a ton of comments
5. Start writing BLAS routines
6. Finish up the Constructors for CSF
7. Write up the redundancy testing helper function
8. Go through and do all user checks, attempt to break 
    CSF as much as possible to make sure user can't break it easily
9. Write up offical example code and documentation
*/

int main (int argc, char** argv) {

    // Show the different functionalites of the CSF format

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


    // Create a CSF matrix from the Eigen matrix

    // Default initialization (compression lvl 3 and T_index = uint64_t but is ignored because bytepacking)
    // ! Not working rn
    //CSF::SparseMatrix<int> mat1(myMatrix);

    // Explicit initialization of comp_lvl 3 and int indexing
    CSF::SparseMatrix<int, int, 3> mat2(myMatrix);


    // compression level 2 using int indexing
    CSF::SparseMatrix<int, int, 2> mat3(myMatrix);

    // compression level 2 using other indexing
    // ! Not working rn
    //CSF::SparseMatrix<int, uint64_t, 2> mat4(myMatrix);

    // compression level 1 using int indexing
    CSF::SparseMatrix<int, int, 1> mat5(myMatrix);

    // compression level 1 using other indexing
    // ! Not working rn
    //CSF::SparseMatrix<int, uint64_t, 1> mat6(myMatrix);

    
    // create a new eigen matrix of type short
    Eigen::SparseMatrix<short> myMatrix2(numRows, numCols);

    // populate the matrix
    for (int k=0; k<myMatrix.outerSize(); ++k)
        for (Eigen::SparseMatrix<int>::InnerIterator it(myMatrix,k); it; ++it)
            myMatrix2.insert(it.row(), it.col()) = it.value();


    // create a new CSF matrix from the eigen matrix of type short
    CSF::SparseMatrix<short, int, 3> mat7(myMatrix2);

    // create a comp_lvl 2 CSF matrix from the eigen matrix of type short
    CSF::SparseMatrix<short, int, 2> mat8(myMatrix2);

    // create a comp_lvl 1 CSF matrix from the eigen matrix of type short
    CSF::SparseMatrix<short, int, 1> mat9(myMatrix2);

    // create a comp_lvl 3 CSF matrix from the eigen matrix of type short
    // ! Not working rn
    //CSF::SparseMatrix<short> mat10(myMatrix2);


    // turn the CSF1 matrix into a CSF3 matrix
    CSF::SparseMatrix<int, int, 3> mat11 = mat5.to_csf3();

    // print the rows and cols of mat11
    std::cout << "mat11 has " << mat11.rows() << " rows and " << mat11.cols() << " cols" << std::endl;

    // print out number of nonzeros and compression size
    std::cout << "mat11 has " << mat11.nonzeros() << " nonzeros and " << mat11.byte_size() << " bytes" << std::endl;

    // write mat11 to file
    mat11.write("mat11.csf");


    // read mat11 from file
    CSF::SparseMatrix<int, int, 3> mat12("mat11.csf");
    
    // print out number of nonzeros and compression size
    // ! cant find non-zeros w/o counting them explicitly
    std::cout << "mat12 has " << mat12.nonzeros() << " nonzeros and " << mat12.byte_size() << " bytes" << std::endl;
    
    return 0;
}