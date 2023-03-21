#include <iostream>
#include "CSF/SparseMatrix"
#include "misc/matrix_creator.cpp"

int main() {

    int numRows = 500;
    int numCols = 500;
    int sparsity = 20;
    uint64_t seed = 1952575394;

    Eigen::SparseMatrix<int> myMatrix_e(numRows, numCols);
    myMatrix_e.reserve(Eigen::VectorXi::Constant(numRows, numCols));
    myMatrix_e = generateMatrix<int>(numRows, numCols, sparsity, seed);
    myMatrix_e.prune(0);
    myMatrix_e.makeCompressed();

    // std::cout << myMatrix_e << std::endl;

    CSF::SparseMatrix<int> myMatrix_csf(myMatrix_e);
    

    // print out the byte size of the matrix
    std::cout << "size: " << myMatrix_csf.compressionSize() << std::endl;


    // writing the CSF sparse to a file
    myMatrix_csf.write("test.csf");

    // get the column size of column 8
    std::cout << "col size: " << myMatrix_csf.getColSize(8) << std::endl;


    // sum all values in the eigen matrix
    int sum_e = 0;
    for (int k=0; k<myMatrix_e.outerSize(); ++k)
        for (Eigen::SparseMatrix<int>::InnerIterator it(myMatrix_e,k); it; ++it)
            sum_e += it.value();

    // sum all values in the CSF matrix
    int sum_csf = 0;
    for (uint32_t k=0; k<myMatrix_csf.innerSize(); ++k)
        for (CSF::SparseMatrix<int>::InnerIterator it(myMatrix_csf,k); it; ++it)
            sum_csf += it.value();

    // compare the sums
    std::cout << "sum_e: " << sum_e << std::endl;
    std::cout << "sum_csf: " << sum_csf << std::endl;



    return 0;
}


