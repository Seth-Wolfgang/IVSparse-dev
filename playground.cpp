
#include "CSF/SparseMatrix"
#include "misc/matrix_creator.cpp"
#include <iostream>

int main(int argc, char** argv) {

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


    // create a sparse matrix from the eigen sparse matrix
    CSF::SparseMatrix<int> myMatrix_csf(myMatrix_e);

    // get the begin and end pointers
    void * begin = myMatrix_csf.beginPtr();
    void * end = myMatrix_csf.endPtr();

    // print begin and end
    std::cout << "Begin: " << begin << std::endl;
    std::cout << "End: " << end << std::endl;

    // find the distance between the begin and end pointers
    std::cout << "Distance between begin and end: " << (int)((char*)end - (char*)begin) << std::endl;

    std::cout << "byte size: " << myMatrix_csf.byte_size() << std::endl;

    // // get the value at end minus 1
    // uint8_t * ending = (uint8_t*)end - 1;

    // // print out the value at the end minus 1
    // std::cout << "Value at end - 1: " << (int)*ending << std::endl;

    //myMatrix_csf.write("myMatrix_csf.csf");

    // create an iterator for the sparse matrix
    CSF::SparseMatrix<int>::Iterator iter(myMatrix_csf);
    // //CSF::Iterator<int, uint64_t, 3> iter = CSF::Iterator<int, uint64_t, 3>(myMatrix_csf);

    // // print out each value in the eigen matrix
    // //std::cout << myMatrix_e << std::endl;

    // get a count
    int eigen_count = 0;
    int eigen_count2 = 0;

    for (int i = 0; i < myMatrix_e.outerSize(); ++i) {
        for (Eigen::SparseMatrix<int>::InnerIterator it(myMatrix_e, i); it; ++it) {
            std::cout << it.value() << " ";
            eigen_count += it.value();
            eigen_count2++;
        }
    }

    std::cout << std::endl;

    // get a count
    int csf_count = 0;
    int csf_count2 = 0;


    // iterate over the matrix
    while (iter)
    {
        iter++;
        std::cout << *iter << " ";
        csf_count += *iter;
        csf_count2++;
    }


    std::cout << std::endl;

    std::cout << "Eigen count: " << eigen_count << std::endl;
    std::cout << "CSF count: " << csf_count << std::endl;

    std::cout << "Eigen count2: " << eigen_count2 << std::endl;
    std::cout << "CSF count2: " << csf_count2 << std::endl;

    std::cout << "Number of nonzeros in Eigen matrix: " << myMatrix_e.nonZeros() << std::endl;
    std::cout << "Number of nonzeros in CSF matrix: " << myMatrix_csf.nonzeros() << std::endl;

    std::cout << "Number of bytes for CSF: " << myMatrix_csf.byte_size() << std::endl;

    // construct a new matrix with the iterator
    CSF::SparseMatrix<int> myMatrix_csf2(iter);

    // print out the first value in the new matrix
    std::cout << "compression level: " << *(uint32_t *)(myMatrix_csf2.beginPtr()) << std::endl;

    // write it to file
    //myMatrix_csf2.write("myMatrix_csf2.csf");

    return 0;
}