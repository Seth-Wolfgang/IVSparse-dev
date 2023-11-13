#include <chrono>
#include <iostream>

#include "IVSparse/SparseMatrix"
#include "misc/matrix_creator.cpp"

#define TYPE int

void test1(IVSparse::SparseMatrix<TYPE, int, 2> vcsc1,
           IVSparse::SparseMatrix<TYPE, int, 2> vcsc2,
           IVSparse::SparseMatrix<TYPE, int, 2> vcsc3,
           IVSparse::SparseMatrix<TYPE, int, 2> vcsc4,
           IVSparse::SparseMatrix<TYPE, int, 3> ivcsc1,
           IVSparse::SparseMatrix<TYPE, int, 3> ivcsc2,
           IVSparse::SparseMatrix<TYPE, int, 3> ivcsc3,
           IVSparse::SparseMatrix<TYPE, int, 3> ivcsc4,
           Eigen::Matrix<TYPE, -1, -1> eigen1,
           Eigen::Matrix<TYPE, -1, -1> eigen2,
           Eigen::Matrix<TYPE, -1, -1> eigen3,
           Eigen::Matrix<TYPE, -1, -1> eigen4);

void test2(IVSparse::SparseMatrix<TYPE, int, 2> vcsc1,
           IVSparse::SparseMatrix<TYPE, int, 2> vcsc2,
           IVSparse::SparseMatrix<TYPE, int, 2> vcsc3,
           IVSparse::SparseMatrix<TYPE, int, 2> vcsc4,
           IVSparse::SparseMatrix<TYPE, int, 3> ivcsc1,
           IVSparse::SparseMatrix<TYPE, int, 3> ivcsc2,
           IVSparse::SparseMatrix<TYPE, int, 3> ivcsc3,
           IVSparse::SparseMatrix<TYPE, int, 3> ivcsc4);


int main() {

    Eigen::Matrix<TYPE, -1, -1> eigen1 = Eigen::Matrix<TYPE, -1, -1>::Random(10, 10);
    Eigen::Matrix<TYPE, -1, -1> eigen2 = Eigen::Matrix<TYPE, -1, -1>::Random(10, 5);
    Eigen::Matrix<TYPE, -1, -1> eigen3 = Eigen::Matrix<TYPE, -1, -1>::Random(10, 15);
    Eigen::Matrix<TYPE, -1, -1> eigen4 = Eigen::Matrix<TYPE, -1, -1>::Random(10, 1);

    for (int i = 0; i < eigen1.cols(); i++) {
        for (int j = 0; j < eigen1.rows(); j++) {
            eigen1(j, i) = rand() % 10 + 1;
        }
    }
    for (int i = 0; i < eigen2.cols(); i++) {
        for (int j = 0; j < eigen2.rows(); j++) {
            eigen2(j, i) = rand() % 10 + 1;
        }
    }
    for (int i = 0; i < eigen3.cols(); i++) {
        for (int j = 0; j < eigen3.rows(); j++) {
            eigen3(j, i) = rand() % 10 + 1;
        }
    }
    for (int i = 0; i < eigen4.cols(); i++) {
        for (int j = 0; j < eigen4.rows(); j++) {
            eigen4(j, i) = rand() % 10 + 1;
        }
    }

    Eigen::SparseMatrix<TYPE> eigen_sparse1 = eigen1.sparseView();
    Eigen::SparseMatrix<TYPE> eigen_sparse2 = eigen2.sparseView();
    Eigen::SparseMatrix<TYPE> eigen_sparse3 = eigen3.sparseView();
    Eigen::SparseMatrix<TYPE> eigen_sparse4 = eigen4.sparseView();

    IVSparse::SparseMatrix<TYPE, int, 2> vcsc1(eigen_sparse1);
    IVSparse::SparseMatrix<TYPE, int, 3> ivcsc1(eigen_sparse1);

    IVSparse::SparseMatrix<TYPE, int, 2> vcsc2(eigen_sparse2);
    IVSparse::SparseMatrix<TYPE, int, 3> ivcsc2(eigen_sparse2);

    IVSparse::SparseMatrix<TYPE, int, 2> vcsc3(eigen_sparse3);
    IVSparse::SparseMatrix<TYPE, int, 3> ivcsc3(eigen_sparse3);

    IVSparse::SparseMatrix<TYPE, int, 2> vcsc4(eigen_sparse4);
    IVSparse::SparseMatrix<TYPE, int, 3> ivcsc4(eigen_sparse4);

    test1(vcsc1, vcsc2, vcsc3, vcsc4, ivcsc1, ivcsc2, ivcsc3, ivcsc4, eigen1, eigen2, eigen3, eigen4);
    test2(vcsc1, vcsc2, vcsc3, vcsc4, ivcsc1, ivcsc2, ivcsc3, ivcsc4);
    // test3(vcsc1, vcsc2, vcsc3, vcsc4, ivcsc1, ivcsc2, ivcsc3, ivcsc4);
    // test4(vcsc1, vcsc2, vcsc3, vcsc4, ivcsc1, ivcsc2, ivcsc3, ivcsc4);




    return 0;
}


void test1(IVSparse::SparseMatrix<TYPE, int, 2> vcsc1,
           IVSparse::SparseMatrix<TYPE, int, 2> vcsc2,
           IVSparse::SparseMatrix<TYPE, int, 2> vcsc3,
           IVSparse::SparseMatrix<TYPE, int, 2> vcsc4,
           IVSparse::SparseMatrix<TYPE, int, 3> ivcsc1,
           IVSparse::SparseMatrix<TYPE, int, 3> ivcsc2,
           IVSparse::SparseMatrix<TYPE, int, 3> ivcsc3,
           IVSparse::SparseMatrix<TYPE, int, 3> ivcsc4,
           Eigen::Matrix<TYPE, -1, -1> eigen1,
           Eigen::Matrix<TYPE, -1, -1> eigen2,
           Eigen::Matrix<TYPE, -1, -1> eigen3,
           Eigen::Matrix<TYPE, -1, -1> eigen4) {

    assert(vcsc1.sum() == ivcsc1.sum());
    assert(vcsc2.sum() == ivcsc2.sum());
    assert(vcsc3.sum() == ivcsc3.sum());
    assert(vcsc4.sum() == ivcsc4.sum());
    assert(vcsc1.sum() == eigen1.sum());
    assert(vcsc2.sum() == eigen2.sum());
    assert(vcsc3.sum() == eigen3.sum());
    assert(vcsc4.sum() == eigen4.sum());


    ivcsc1.append(ivcsc1);
    vcsc1.append(vcsc1);

    assert(vcsc1.sum() == ivcsc1.sum());
    assert(vcsc1.sum() == eigen1.sum() * 2);


    ivcsc2.append(ivcsc2);
    vcsc2.append(vcsc2);

    assert(vcsc2.sum() == ivcsc2.sum());
    assert(vcsc2.sum() == eigen2.sum() * 2);

    ivcsc3.append(ivcsc3);
    vcsc3.append(vcsc3);

    assert(vcsc3.sum() == ivcsc3.sum());
    assert(vcsc3.sum() == eigen3.sum() * 2);

    ivcsc4.append(ivcsc4);
    vcsc4.append(vcsc4);

    assert(vcsc4.sum() == ivcsc4.sum());
    assert(vcsc4.sum() == eigen4.sum() * 2);

}

void test2(IVSparse::SparseMatrix<TYPE, int, 2> vcsc1,
           IVSparse::SparseMatrix<TYPE, int, 2> vcsc2,
           IVSparse::SparseMatrix<TYPE, int, 2> vcsc3,
           IVSparse::SparseMatrix<TYPE, int, 2> vcsc4,
           IVSparse::SparseMatrix<TYPE, int, 3> ivcsc1,
           IVSparse::SparseMatrix<TYPE, int, 3> ivcsc2,
           IVSparse::SparseMatrix<TYPE, int, 3> ivcsc3,
           IVSparse::SparseMatrix<TYPE, int, 3> ivcsc4) {

    IVSparse::SparseMatrix<TYPE, int, 2> vcsc5 = vcsc1;
    IVSparse::SparseMatrix<TYPE, int, 3> ivcsc5 = ivcsc1;

    vcsc5.append(vcsc2);
    ivcsc5.append(ivcsc2);

    assert(vcsc5.sum() == ivcsc5.sum());

    vcsc5.append(vcsc3);
    ivcsc5.append(ivcsc3);

    assert(vcsc5.sum() == ivcsc5.sum());

    vcsc5.append(vcsc4);
    ivcsc5.append(ivcsc4);

    assert(vcsc5.sum() == ivcsc5.sum());

    vcsc5.append(vcsc5);
    ivcsc5.append(ivcsc5);

    assert(vcsc5.sum() == ivcsc5.sum());

    vcsc5.print();
    ivcsc5.print();

    int combinedSum = vcsc1.sum() + vcsc2.sum();
    vcsc1.append(vcsc2);
    ivcsc1.append(ivcsc2);

    assert(vcsc1.sum() == ivcsc1.sum());
    assert(vcsc1.sum() == combinedSum);

    combinedSum = vcsc1.sum() + vcsc3.sum();
    vcsc1.append(vcsc3);
    ivcsc1.append(ivcsc3);
    assert(vcsc1.sum() == ivcsc1.sum());
    assert(vcsc1.sum() == combinedSum);

    combinedSum = vcsc1.sum() + vcsc4.sum();
    vcsc1.append(vcsc4);
    ivcsc1.append(ivcsc4);
    assert(vcsc1.sum() == ivcsc1.sum());
    assert(vcsc1.sum() == combinedSum);

    combinedSum = vcsc2.sum() + vcsc3.sum();
    vcsc2.append(vcsc3);
    ivcsc2.append(ivcsc3);
    assert(vcsc2.sum() == ivcsc2.sum());
    assert(vcsc2.sum() == combinedSum);

    combinedSum = vcsc2.sum() + vcsc4.sum();
    vcsc2.append(vcsc4);
    ivcsc2.append(ivcsc4);
    assert(vcsc2.sum() == ivcsc2.sum());
    assert(vcsc2.sum() == combinedSum);

    combinedSum = vcsc3.sum() + vcsc4.sum();
    vcsc3.append(vcsc4);
    ivcsc3.append(ivcsc4);
    assert(vcsc3.sum() == ivcsc3.sum());
    assert(vcsc3.sum() == combinedSum);

    combinedSum = vcsc4.sum() + vcsc1.sum();
    vcsc4.append(vcsc1);
    ivcsc4.append(ivcsc1);
    assert(vcsc4.sum() == ivcsc4.sum());
    assert(vcsc4.sum() == combinedSum);

}
