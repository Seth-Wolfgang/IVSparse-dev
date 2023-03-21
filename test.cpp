#include <iostream>
#include "CSF/SparseMatrix"
#include "misc/matrix_creator.cpp"

int main() {

    int numRows = 1000;
    int numCols = 1000;
    int sparsity = 20;
    uint64_t seed = 1952575394;

    Eigen::SparseMatrix<int> myMatrix_e(numRows, numCols);
    myMatrix_e.reserve(Eigen::VectorXi::Constant(numRows, numCols));
    myMatrix_e = generateMatrix<int>(numRows, numCols, sparsity, seed);
    myMatrix_e.prune(0);
    myMatrix_e.makeCompressed();


    // std::cout << "CSC sparse size: " << currentSize2 - currentSize1 << std::endl;

    // generating a large random CSF sparse
    

    CSF::SparseMatrix<int> myMatrix_csf(myMatrix_e);

    // writing the CSF sparse to a file
    // myMatrix_csf.write("test.csf");

    // std::cout << myMatrix_e << std::endl;

    // add all the elements in the matrix
    uint64_t sum = 0;
    for (uint32_t k = 0; k < myMatrix_csf.outerSize(); ++k) {
        for (CSF::SparseMatrix<int>::InnerIterator it(myMatrix_csf, k); it; it++) {
            sum += it.value();
        }
    }

    // add all the elements in the eigen matrix
    uint64_t sum_e = 0;
    for (int k = 0; k < myMatrix_e.outerSize(); ++k) {
        for (Eigen::SparseMatrix<int>::InnerIterator it(myMatrix_e, k); it; ++it) {
            sum_e += it.value();
        }
    }


    // std::cout << "sum: " << sum << std::endl;
    // std::cout << "sum_e: " << sum_e << std::endl;

    // get a csf::vector of the third column
    // CSF::SparseMatrix<int>::Vector vec(myMatrix_csf, 2);

    // get an iterator
    // CSF::SparseMatrix<int>::InnerIterator vectorIt(vec);

    // iterate over the non-zero elements of the third column
    // while (vectorIt) {
    //     std::cout << vectorIt.index() << " " << vectorIt.col() << " " << vectorIt.value() << std::endl;
    //     vectorIt++;
    // }

    // create an iterator for the third col
    // CSF::SparseMatrix<int>::InnerIterator it2(myMatrix_csf, 2);

    // iterate over the non-zero elements of the third column
    // while (it2) {
    //     std::cout << it2.index() << " " << it2.col() << " " << it2.value() << std::endl;
    //     it2++;
    // }

// generating a large random eigen sparse


    return 0;
}


