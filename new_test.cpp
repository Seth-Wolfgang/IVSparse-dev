#include <chrono>
#include <iostream>

#include "IVSparse/SparseMatrix"
#include "misc/matrix_creator.cpp"



int main() {

    Eigen::Matrix<int8_t, -1, -1> eigen = Eigen::Matrix<int8_t, -1, -1>::Zero(1000, 1000);

    for(int i = 0; i < eigen.cols(); i++) {
        for (int j = 0; j < eigen.rows(); j++) {
            eigen(i, j) = 1;
        }
    }

    std::cout << eigen << std::endl;

    Eigen::SparseMatrix<int8_t> sparse = eigen.sparseView();

    IVSparse::SparseMatrix<int8_t, int32_t, 2> ivsparse(sparse);

    std::cout << (int)ivsparse.sum() << std::endl;
    std::cout << (int)eigen.sum() << std::endl;


    return 0;
}