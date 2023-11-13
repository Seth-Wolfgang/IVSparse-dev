#include <chrono>
#include <iostream>

#include "IVSparse/SparseMatrix"
#include "misc/matrix_creator.cpp"



int main() {

    Eigen::Matrix<int, -1, -1> eigen = Eigen::Matrix<int, -1, -1>::Random(10, 10);
    Eigen::SparseMatrix<int> eigen_sparse = eigen.sparseView();

    IVSparse::SparseMatrix<int, int, 3> ivcsc(eigen_sparse);
    IVSparse::SparseMatrix<int, int, 2> vcsc(eigen_sparse);

    ivcsc.print();
    vcsc.print();

    // ivcsc.append(ivcsc);
    vcsc.append(vcsc);  
     
    assert(ivcsc.sum() == vcsc.sum());
    assert(ivcsc.sum() == eigen_sparse.sum());

    IVSparse::SparseMatrix<int, int, 2> vcsc2 = vcsc.slice(0, 10);
    IVSparse::SparseMatrix<int, int, 3> ivcsc2 = ivcsc.slice(0, 10);

    assert(vcsc2.sum() == ivcsc2.sum());
    assert(vcsc2.sum() == eigen_sparse.sum());

    return 0;
}