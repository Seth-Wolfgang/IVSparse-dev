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

    // writing the CSF sparse to a file
    // myMatrix_csf.write("test.csf");

    // std::cout << myMatrix_e << std::endl;

    // get an iterator 
    // CSF::SparseMatrix<int>::InnerIterator it(myMatrix_csf, 0);

    // // iterate over the non-zero elements of the first row
    // while (it) {
    //     std::cout << it.index() << " " << it.col() << " " << it.value() << std::endl;
    //     it++;
    // }

    // add all the elements in the matrix
    int sum = 0;
    for (int k = 0; k < myMatrix_csf.outerSize(); ++k) {
        for (CSF::SparseMatrix<int>::InnerIterator it(myMatrix_csf, k); it; it++) {
            sum += it.value();
        }
    }

    // add all the elements in the eigen matrix
    int sum_e = 0;
    for (int k = 0; k < myMatrix_e.outerSize(); ++k) {
        for (Eigen::SparseMatrix<int>::InnerIterator it(myMatrix_e, k); it; ++it) {
            sum_e += it.value();
        }
    }
    
    std::cout << "sum: " << sum << std::endl;
    std::cout << "sum_e: " << sum_e << std::endl;

    return 0;
}