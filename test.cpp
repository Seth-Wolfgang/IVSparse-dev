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
    #pragma omp parallel for num_threads(15)
    for (int i = 0; i < 1000000; i++) {
        iteratorTest<double, uint64_t, 3>();
        std::cout << "Test " << i << " passed" << std::endl;
    }


    return 0;
}

template <typename T, typename indexT, int compressionLevel>
void iteratorTest() {

    int numRows = 1000;//rand() % 1000 + 10;
    int numCols = 1000;//rand() % 1000 + 10;
    int sparsity = 1;//rand() % 50 + 1;
    uint64_t seed = 1;//rand();

    Eigen::SparseMatrix<T> eigen(numRows, numCols);
    eigen.reserve(Eigen::VectorXi::Constant(numCols, numRows));
    eigen = generateMatrix<T>(numRows, numCols, sparsity, seed);
    eigen.makeCompressed();

    Eigen::MatrixXd randMatrix = Eigen::MatrixXd::Random(numCols, numRows);
    Eigen::VectorXd randVector = Eigen::VectorXd::Random(numCols);

    //Create CSF matrix and an eigen dense matrix
    CSF::SparseMatrix<T, indexT, compressionLevel> csfMatrix(eigen);

    std::chrono::time_point<std::chrono::system_clock> start, end;

    start = std::chrono::system_clock::now();
    Eigen::MatrixXd denseMatrix = csfMatrix * randMatrix;
    end = std::chrono::system_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>( end - start ).count();

    start = std::chrono::system_clock::now();
    Eigen::MatrixXd denseMatrix2 = csfMatrix.matrixMultiply2(randMatrix);
    end = std::chrono::system_clock::now();   
    auto duration2 = std::chrono::duration_cast<std::chrono::microseconds>( end - start ).count();

    std::cout << "Version 1 (new): " << duration << " version 2 (old): " << duration2 << std::endl;


    // Eigen::MatrixXd controlMatrix = eigen * randMatrix;

    T sum_e = denseMatrix.sum();
    T sum_csf = denseMatrix2.sum();

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

