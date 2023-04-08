#include <iostream>
#include "CSF/SparseMatrix"
#include "misc/matrix_creator.cpp"
#include <chrono>


template <typename T, typename indexT, int compressionLevel> void iteratorTest();
void getMat(Eigen::SparseMatrix<int>& myMatrix_e);

int main() {

    // create an eigen sparse matrix
    Eigen::SparseMatrix<int> skyMat(10, 10);
    getMat(skyMat);

    std::cout << skyMat << std::endl;

    // create a CSF sparse matrix
    CSF::SparseMatrix<int, int, 3> skyMat_csf(skyMat);
    CSF::SparseMatrix<int, int, 2> skyMat_csf2(skyMat);

    // transpose the CSF matrix
    CSF::SparseMatrix<int, int, 3> skyMat_csfT = skyMat_csf.transpose();

    // turn the CSF matrix into an eigen matrix
    Eigen::SparseMatrix<int> skyMat_e = skyMat_csfT.toEigen();

    // print the eigen matrix
    std::cout << skyMat_e << std::endl;

    std::cout << skyMat.transpose() << std::endl;

    // make a vector of the CSF matrix
    CSF::SparseMatrix<int, int, 3>::Vector skyVec(skyMat_csf, 0);

    // multiply the CSF by 3
    skyMat_csf *= 3;

    


    // * CSF Iterator Testing * //
    // #pragma omp parallel for num_threads(15)
    // for (int i = 0; i < 1000000; i++) {
    //     iteratorTest<int, uint64_t, 3>();
    //     std::cout << "Test " << i << " passed" << std::endl;
    // }


    return 0;
}

template <typename T, typename indexT, int compressionLevel>
void iteratorTest() {

    int numRows = rand() % 1000 + 10;
    int numCols = rand() % 1000 + 10;
    int sparsity = rand() % 50 + 1;
    uint64_t seed = rand();

    Eigen::SparseMatrix<T> myMatrix_e(numRows, numCols);
    myMatrix_e.reserve(Eigen::VectorXi::Constant(numCols, numRows));
    myMatrix_e = generateMatrix<T>(numRows, numCols, sparsity, seed);
    myMatrix_e.makeCompressed();

    //Create CSF matrix and an eigen dense matrix
    CSF::SparseMatrix<T, indexT, compressionLevel> myMatrix_csf(myMatrix_e);
    Eigen::MatrixXd eigenMatrix = Eigen::MatrixXd(myMatrix_e);

    //make an eigen vectorXd and fill it with twos
    Eigen::VectorXd eigenVector2(numCols);
    eigenVector2.setRandom();

    //make an eigen::sparsematrix and fill it with twos
    Eigen::SparseMatrix<T> eigenVector(numCols, 1);
    eigenVector.reserve(Eigen::VectorXi::Constant(numCols, numCols));
    eigenVector.setZero();

    // Fill the vector with 2
    for (int i = 0; i < numCols; i++) {
        eigenVector.insert(i, 0) = 2;
    }

    //get sum of both myMatrix_e and myMatrix_csf
    T tempSumCSF = 0;
    for (int k = 0; k < myMatrix_csf.outerSize(); ++k) {
        for (typename CSF::SparseMatrix<T, indexT, compressionLevel>::InnerIterator it(myMatrix_csf, k); it; ++it) {
            tempSumCSF += it.value();
        }
    }
    assert(myMatrix_e.sum() == tempSumCSF);

    //Compress vector
    eigenVector.makeCompressed();
    CSF::SparseMatrix<T, indexT, compressionLevel> myMatrix_csf2(eigenVector);
    typename CSF::SparseMatrix<T, indexT, compressionLevel>::Vector CSFVector(myMatrix_csf2, 0);

    Eigen::VectorXd myVector_e2 = myMatrix_csf * eigenVector2;
    Eigen::VectorXd myVector_e = eigenMatrix * eigenVector2;
    // T sum_e = myMatrix_e.sum() * 2;

    // myMatrix_csf *= 2;
    // T sum_csf = 0;
    // for(int k = 0; k < myMatrix_csf.outerSize(); ++k){
    //     for(typename CSF::SparseMatrix<T, indexT, compressionLevel>::InnerIterator it(myMatrix_csf, k); it; ++it) {
    //         sum_csf += it.value();
    //     }
    // }

    // for(int i = 0; i < myVector_e2.size(); i++) {
    //     std::cout << myVector_e2(i) << " ";
    // }
    // std::cout << std::endl;

    T sum_e = myVector_e.sum();
    T sum_csf = myVector_e2.sum();

    if (sum_csf - sum_e > 10 || sum_csf == 0) {
        std::cout << "Rows: " << numRows << " Cols: " << numCols << " Sparsity: " << sparsity << " Seed: " << seed << std::endl;
        std::cout << "sum_csf: " << sum_csf << " sum_e: " << sum_e << std::endl;
        assert(sum_csf == sum_e);
    }
}


void getMat(Eigen::SparseMatrix<int>& myMatrix_e) {
    // declare an eigen sparse matrix of both types

    // col 0
    myMatrix_e.insert(0, 0) = 1;
    myMatrix_e.insert(2, 0) = 2;
    myMatrix_e.insert(3, 0) = 3;
    myMatrix_e.insert(5, 0) = 1;
    myMatrix_e.insert(6, 0) = 3;
    myMatrix_e.insert(7, 0) = 8;

    // col 1
    myMatrix_e.insert(3, 1) = 1;
    myMatrix_e.insert(4, 1) = 3;
    myMatrix_e.insert(5, 1) = 8;
    myMatrix_e.insert(6, 1) = 7;
    myMatrix_e.insert(8, 1) = 1;
    myMatrix_e.insert(9, 1) = 2;

    // col 2
    myMatrix_e.insert(0, 2) = 2;
    myMatrix_e.insert(2, 2) = 2;
    myMatrix_e.insert(5, 2) = 1;
    myMatrix_e.insert(7, 2) = 3;
    myMatrix_e.insert(9, 2) = 1;

    // col 3

    // col 4
    myMatrix_e.insert(0, 4) = 1;
    myMatrix_e.insert(3, 4) = 1;
    myMatrix_e.insert(4, 4) = 3;
    myMatrix_e.insert(6, 4) = 2;
    myMatrix_e.insert(7, 4) = 1;

    // col 5
    myMatrix_e.insert(0, 5) = 8;
    myMatrix_e.insert(2, 5) = 1;
    myMatrix_e.insert(3, 5) = 4;
    myMatrix_e.insert(5, 5) = 3;
    myMatrix_e.insert(7, 5) = 1;
    myMatrix_e.insert(8, 5) = 2;

    // col 6
    myMatrix_e.insert(3, 6) = 6;
    myMatrix_e.insert(5, 6) = 1;
    myMatrix_e.insert(7, 6) = 3;

    // col 7
    myMatrix_e.insert(2, 7) = 3;
    myMatrix_e.insert(4, 7) = 4;
    myMatrix_e.insert(5, 7) = 1;
    myMatrix_e.insert(8, 7) = 2;
    myMatrix_e.insert(9, 7) = 3;

    // col 8
    myMatrix_e.insert(0, 8) = 2;
    myMatrix_e.insert(2, 8) = 1;
    myMatrix_e.insert(3, 8) = 2;
    myMatrix_e.insert(5, 8) = 3;
    myMatrix_e.insert(7, 8) = 3;
    myMatrix_e.insert(9, 8) = 1;

    // col 9
    myMatrix_e.insert(3, 9) = 2;
    myMatrix_e.insert(4, 9) = 4;
    myMatrix_e.insert(7, 9) = 1;
    myMatrix_e.insert(8, 9) = 1;

    myMatrix_e.makeCompressed();

}

