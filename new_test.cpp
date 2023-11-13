#include <chrono>
#include <iostream>

#include "IVSparse/SparseMatrix"
#include "misc/matrix_creator.cpp"

#define TYPE int16_t

int main() {

    Eigen::Matrix<TYPE, -1, -1> eigen = Eigen::Matrix<TYPE, -1, -1>::Random(10, 10);
    Eigen::SparseMatrix<TYPE> eigen_sparse = eigen.sparseView();

    //IVSparse::SparseMatrix<TYPE, int, 3> ivcsc(eigen_sparse);
    IVSparse::SparseMatrix<TYPE, int, 2> vcsc(eigen_sparse);

    //ivcsc.print();
    vcsc.print();

    IVSparse::SparseMatrix<TYPE, int, 2> vcsc2 = vcsc.transpose();

    vcsc2.print();

    vcsc2 = vcsc2 * 0;

    vcsc2.append(vcsc);

    vcsc2.print();

    // slice the first 3 cols of ivcsc
    IVSparse::SparseMatrix<TYPE, int, 2> vcsc3 = vcsc2.slice(0, 3);

    vcsc3.print();

    return 0;
}