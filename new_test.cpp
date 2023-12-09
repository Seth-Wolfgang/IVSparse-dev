#include <chrono>
#include <iostream>

#include "IVSparse/SparseMatrix"
#include "misc/matrix_creator.cpp"

#define TYPE int
#define IVSparseMAJOR 0 // IVSparse -> col major, Eigen -> row major
#define EIGENMAJOR !IVSparseMAJOR    // IVSparse -> col major, Eigen -> row major
#define INDEX_TYPE int
#define IVSPARSE_DEBUG

void test1(IVSparse::VCSC<TYPE, INDEX_TYPE, IVSparseMAJOR> vcsc1,
           IVSparse::VCSC<TYPE, INDEX_TYPE, IVSparseMAJOR> vcsc2,
           IVSparse::VCSC<TYPE, INDEX_TYPE, IVSparseMAJOR> vcsc3,
           IVSparse::VCSC<TYPE, INDEX_TYPE, IVSparseMAJOR> vcsc4,
           IVSparse::IVCSC<TYPE, IVSparseMAJOR> ivcsc1,
           IVSparse::IVCSC<TYPE, IVSparseMAJOR> ivcsc2,
           IVSparse::IVCSC<TYPE, IVSparseMAJOR> ivcsc3,
           IVSparse::IVCSC<TYPE, IVSparseMAJOR> ivcsc4,
           Eigen::Matrix<TYPE, -1, -1, EIGENMAJOR> eigen1,
           Eigen::Matrix<TYPE, -1, -1, EIGENMAJOR> eigen2,
           Eigen::Matrix<TYPE, -1, -1, EIGENMAJOR> eigen3,
           Eigen::Matrix<TYPE, -1, -1, EIGENMAJOR> eigen4);

void test2(IVSparse::VCSC<TYPE, INDEX_TYPE, IVSparseMAJOR> vcsc1,
           IVSparse::VCSC<TYPE, INDEX_TYPE, IVSparseMAJOR> vcsc2,
           IVSparse::VCSC<TYPE, INDEX_TYPE, IVSparseMAJOR> vcsc3,
           IVSparse::VCSC<TYPE, INDEX_TYPE, IVSparseMAJOR> vcsc4,
           IVSparse::IVCSC<TYPE, IVSparseMAJOR> ivcsc1,
           IVSparse::IVCSC<TYPE, IVSparseMAJOR> ivcsc2,
           IVSparse::IVCSC<TYPE, IVSparseMAJOR> ivcsc3,
           IVSparse::IVCSC<TYPE, IVSparseMAJOR> ivcsc4);

void test3(IVSparse::VCSC<TYPE, INDEX_TYPE, IVSparseMAJOR> vcsc1,
           IVSparse::VCSC<TYPE, INDEX_TYPE, IVSparseMAJOR> vcsc2,
           IVSparse::VCSC<TYPE, INDEX_TYPE, IVSparseMAJOR> vcsc3,
           IVSparse::VCSC<TYPE, INDEX_TYPE, IVSparseMAJOR> vcsc4,
           IVSparse::IVCSC<TYPE, IVSparseMAJOR> ivcsc1,
           IVSparse::IVCSC<TYPE, IVSparseMAJOR> ivcsc2,
           IVSparse::IVCSC<TYPE, IVSparseMAJOR> ivcsc3,
           IVSparse::IVCSC<TYPE, IVSparseMAJOR> ivcsc4,
           Eigen::SparseMatrix<TYPE, EIGENMAJOR> eigen1,
           Eigen::SparseMatrix<TYPE, EIGENMAJOR> eigen2,
           Eigen::SparseMatrix<TYPE, EIGENMAJOR> eigen3,
           Eigen::SparseMatrix<TYPE, EIGENMAJOR> eigen4);

void test4(IVSparse::VCSC<TYPE, INDEX_TYPE, IVSparseMAJOR> vcsc1,
           IVSparse::VCSC<TYPE, INDEX_TYPE, IVSparseMAJOR> vcsc2,
           IVSparse::VCSC<TYPE, INDEX_TYPE, IVSparseMAJOR> vcsc3,
           IVSparse::VCSC<TYPE, INDEX_TYPE, IVSparseMAJOR> vcsc4,
           IVSparse::IVCSC<TYPE, IVSparseMAJOR> ivcsc1,
           IVSparse::IVCSC<TYPE, IVSparseMAJOR> ivcsc2,
           IVSparse::IVCSC<TYPE, IVSparseMAJOR> ivcsc3,
           IVSparse::IVCSC<TYPE, IVSparseMAJOR> ivcsc4);

void test5(IVSparse::VCSC<TYPE, INDEX_TYPE, IVSparseMAJOR> vcsc1,
           IVSparse::VCSC<TYPE, INDEX_TYPE, IVSparseMAJOR> vcsc2,
           IVSparse::VCSC<TYPE, INDEX_TYPE, IVSparseMAJOR> vcsc3,
           IVSparse::VCSC<TYPE, INDEX_TYPE, IVSparseMAJOR> vcsc4,
           IVSparse::IVCSC<TYPE, IVSparseMAJOR> ivcsc1,
           IVSparse::IVCSC<TYPE, IVSparseMAJOR> ivcsc2,
           IVSparse::IVCSC<TYPE, IVSparseMAJOR> ivcsc3,
           IVSparse::IVCSC<TYPE, IVSparseMAJOR> ivcsc4);

void test6(IVSparse::VCSC<TYPE, INDEX_TYPE, IVSparseMAJOR> vcsc1,
           IVSparse::VCSC<TYPE, INDEX_TYPE, IVSparseMAJOR> vcsc2,
           IVSparse::VCSC<TYPE, INDEX_TYPE, IVSparseMAJOR> vcsc3,
           IVSparse::VCSC<TYPE, INDEX_TYPE, IVSparseMAJOR> vcsc4,
           IVSparse::IVCSC<TYPE, IVSparseMAJOR> ivcsc1,
           IVSparse::IVCSC<TYPE, IVSparseMAJOR> ivcsc2,
           IVSparse::IVCSC<TYPE, IVSparseMAJOR> ivcsc3,
           IVSparse::IVCSC<TYPE, IVSparseMAJOR> ivcsc4);

void test7(IVSparse::VCSC<TYPE, INDEX_TYPE, IVSparseMAJOR> vcsc1,
           IVSparse::VCSC<TYPE, INDEX_TYPE, IVSparseMAJOR> vcsc2,
           IVSparse::VCSC<TYPE, INDEX_TYPE, IVSparseMAJOR> vcsc3,
           IVSparse::VCSC<TYPE, INDEX_TYPE, IVSparseMAJOR> vcsc4,
           IVSparse::IVCSC<TYPE, IVSparseMAJOR> ivcsc1,
           IVSparse::IVCSC<TYPE, IVSparseMAJOR> ivcsc2,
           IVSparse::IVCSC<TYPE, IVSparseMAJOR> ivcsc3,
           IVSparse::IVCSC<TYPE, IVSparseMAJOR> ivcsc4,
           Eigen::SparseMatrix<TYPE, EIGENMAJOR> eigen1,
           Eigen::SparseMatrix<TYPE, EIGENMAJOR> eigen2,
           Eigen::SparseMatrix<TYPE, EIGENMAJOR> eigen3,
           Eigen::SparseMatrix<TYPE, EIGENMAJOR> eigen4);

void test8(IVSparse::VCSC<TYPE, INDEX_TYPE, IVSparseMAJOR> vcsc1,
           IVSparse::VCSC<TYPE, INDEX_TYPE, IVSparseMAJOR> vcsc2,
           IVSparse::VCSC<TYPE, INDEX_TYPE, IVSparseMAJOR> vcsc3,
           IVSparse::VCSC<TYPE, INDEX_TYPE, IVSparseMAJOR> vcsc4,
           IVSparse::IVCSC<TYPE, IVSparseMAJOR> ivcsc1,
           IVSparse::IVCSC<TYPE, IVSparseMAJOR> ivcsc2,
           IVSparse::IVCSC<TYPE, IVSparseMAJOR> ivcsc3,
           IVSparse::IVCSC<TYPE, IVSparseMAJOR> ivcsc4,
           Eigen::SparseMatrix<TYPE, EIGENMAJOR> eigen1,
           Eigen::SparseMatrix<TYPE, EIGENMAJOR> eigen2,
           Eigen::SparseMatrix<TYPE, EIGENMAJOR> eigen3,
           Eigen::SparseMatrix<TYPE, EIGENMAJOR> eigen4);

void test8(IVSparse::VCSC<TYPE, INDEX_TYPE, IVSparseMAJOR> vcsc1,
           IVSparse::VCSC<TYPE, INDEX_TYPE, IVSparseMAJOR> vcsc2,
           IVSparse::VCSC<TYPE, INDEX_TYPE, IVSparseMAJOR> vcsc3,
           IVSparse::VCSC<TYPE, INDEX_TYPE, IVSparseMAJOR> vcsc4,
           IVSparse::IVCSC<TYPE, IVSparseMAJOR> ivcsc1,
           IVSparse::IVCSC<TYPE, IVSparseMAJOR> ivcsc2,
           IVSparse::IVCSC<TYPE, IVSparseMAJOR> ivcsc3,
           IVSparse::IVCSC<TYPE, IVSparseMAJOR> ivcsc4,
           Eigen::SparseMatrix<TYPE, EIGENMAJOR> eigen1,
           Eigen::SparseMatrix<TYPE, EIGENMAJOR> eigen2,
           Eigen::SparseMatrix<TYPE, EIGENMAJOR> eigen3,
           Eigen::SparseMatrix<TYPE, EIGENMAJOR> eigen4);

void test9(IVSparse::VCSC<TYPE, INDEX_TYPE, IVSparseMAJOR> vcsc1,
           IVSparse::VCSC<TYPE, INDEX_TYPE, IVSparseMAJOR> vcsc2,
           IVSparse::VCSC<TYPE, INDEX_TYPE, IVSparseMAJOR> vcsc3,
           IVSparse::VCSC<TYPE, INDEX_TYPE, IVSparseMAJOR> vcsc4,
           IVSparse::IVCSC<TYPE, IVSparseMAJOR> ivcsc1,
           IVSparse::IVCSC<TYPE, IVSparseMAJOR> ivcsc2,
           IVSparse::IVCSC<TYPE, IVSparseMAJOR> ivcsc3,
           IVSparse::IVCSC<TYPE, IVSparseMAJOR> ivcsc4,
           Eigen::SparseMatrix<TYPE, EIGENMAJOR> eigen1,
           Eigen::SparseMatrix<TYPE, EIGENMAJOR> eigen2,
           Eigen::SparseMatrix<TYPE, EIGENMAJOR> eigen3,
           Eigen::SparseMatrix<TYPE, EIGENMAJOR> eigen4);



int main() {

    int cols1, cols2, cols3, cols4;
    int rows1, rows2, rows3, rows4;
    int a = rand() % 1000 + 1;
    int b = rand() % 1000 + 1;
    
    if constexpr (IVSparseMAJOR) {
        cols1 = a;
        cols2 = a;
        cols3 = a;
        cols4 = a;

        rows1 = a;
        rows2 = b;
        rows3 = a + b;
        rows4 = 1;
    }
    else {
        cols1 = a;
        cols2 = b;
        cols3 = a + b;
        cols4 = 1;

        rows1 = a;
        rows2 = a;
        rows3 = a;
        rows4 = a;
    }


    Eigen::Matrix<TYPE, -1, -1, EIGENMAJOR> eigen1 = Eigen::Matrix<TYPE, -1, -1, EIGENMAJOR>::Random(cols1, rows1);
    Eigen::Matrix<TYPE, -1, -1, EIGENMAJOR> eigen2 = Eigen::Matrix<TYPE, -1, -1, EIGENMAJOR>::Random(cols2, rows2);
    Eigen::Matrix<TYPE, -1, -1, EIGENMAJOR> eigen3 = Eigen::Matrix<TYPE, -1, -1, EIGENMAJOR>::Random(cols3, rows3);
    Eigen::Matrix<TYPE, -1, -1, EIGENMAJOR> eigen4 = Eigen::Matrix<TYPE, -1, -1, EIGENMAJOR>::Random(cols4, rows4);

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

    Eigen::SparseMatrix<TYPE, EIGENMAJOR> eigen_sparse1 = eigen1.sparseView();
    Eigen::SparseMatrix<TYPE, EIGENMAJOR> eigen_sparse2 = eigen2.sparseView();
    Eigen::SparseMatrix<TYPE, EIGENMAJOR> eigen_sparse3 = eigen3.sparseView();
    Eigen::SparseMatrix<TYPE, EIGENMAJOR> eigen_sparse4 = eigen4.sparseView();

    IVSparse::VCSC<TYPE, INDEX_TYPE, IVSparseMAJOR> vcsc1(eigen_sparse1);
    IVSparse::IVCSC<TYPE, IVSparseMAJOR> ivcsc1(eigen_sparse1);

    IVSparse::VCSC<TYPE, INDEX_TYPE, IVSparseMAJOR> vcsc2(eigen_sparse2);
    IVSparse::IVCSC<TYPE, IVSparseMAJOR> ivcsc2(eigen_sparse2);

    IVSparse::VCSC<TYPE, INDEX_TYPE, IVSparseMAJOR> vcsc3(eigen_sparse3);
    IVSparse::IVCSC<TYPE, IVSparseMAJOR> ivcsc3(eigen_sparse3);

    IVSparse::VCSC<TYPE, INDEX_TYPE, IVSparseMAJOR> vcsc4(eigen_sparse4);
    IVSparse::IVCSC<TYPE, IVSparseMAJOR> ivcsc4(eigen_sparse4);

    test1(vcsc1, vcsc2, vcsc3, vcsc4, ivcsc1, ivcsc2, ivcsc3, ivcsc4, eigen1, eigen2, eigen3, eigen4);
    test2(vcsc1, vcsc2, vcsc3, vcsc4, ivcsc1, ivcsc2, ivcsc3, ivcsc4);
    test3(vcsc1, vcsc2, vcsc3, vcsc4, ivcsc1, ivcsc2, ivcsc3, ivcsc4, eigen_sparse1, eigen_sparse2, eigen_sparse3, eigen_sparse4);
    test4(vcsc1, vcsc2, vcsc3, vcsc4, ivcsc1, ivcsc2, ivcsc3, ivcsc4);
    test5(vcsc1, vcsc2, vcsc3, vcsc4, ivcsc1, ivcsc2, ivcsc3, ivcsc4);
    test6(vcsc1, vcsc2, vcsc3, vcsc4, ivcsc1, ivcsc2, ivcsc3, ivcsc4);
    test7(vcsc1, vcsc2, vcsc3, vcsc4, ivcsc1, ivcsc2, ivcsc3, ivcsc4, eigen_sparse1, eigen_sparse2, eigen_sparse3, eigen_sparse4);
    test8(vcsc1, vcsc2, vcsc3, vcsc4, ivcsc1, ivcsc2, ivcsc3, ivcsc4, eigen_sparse1, eigen_sparse2, eigen_sparse3, eigen_sparse4);
    test9(vcsc1, vcsc2, vcsc3, vcsc4, ivcsc1, ivcsc2, ivcsc3, ivcsc4, eigen_sparse1, eigen_sparse2, eigen_sparse3, eigen_sparse4);


    return 0;
}


void test1(IVSparse::VCSC<TYPE, INDEX_TYPE, IVSparseMAJOR> vcsc1,
           IVSparse::VCSC<TYPE, INDEX_TYPE, IVSparseMAJOR> vcsc2,
           IVSparse::VCSC<TYPE, INDEX_TYPE, IVSparseMAJOR> vcsc3,
           IVSparse::VCSC<TYPE, INDEX_TYPE, IVSparseMAJOR> vcsc4,
           IVSparse::IVCSC<TYPE, IVSparseMAJOR> ivcsc1,
           IVSparse::IVCSC<TYPE, IVSparseMAJOR> ivcsc2,
           IVSparse::IVCSC<TYPE, IVSparseMAJOR> ivcsc3,
           IVSparse::IVCSC<TYPE, IVSparseMAJOR> ivcsc4,
           Eigen::Matrix<TYPE, -1, -1, EIGENMAJOR> eigen1,
           Eigen::Matrix<TYPE, -1, -1, EIGENMAJOR> eigen2,
           Eigen::Matrix<TYPE, -1, -1, EIGENMAJOR> eigen3,
           Eigen::Matrix<TYPE, -1, -1, EIGENMAJOR> eigen4) {

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

void test2(IVSparse::VCSC<TYPE, INDEX_TYPE, IVSparseMAJOR> vcsc1,
           IVSparse::VCSC<TYPE, INDEX_TYPE, IVSparseMAJOR> vcsc2,
           IVSparse::VCSC<TYPE, INDEX_TYPE, IVSparseMAJOR> vcsc3,
           IVSparse::VCSC<TYPE, INDEX_TYPE, IVSparseMAJOR> vcsc4,
           IVSparse::IVCSC<TYPE, IVSparseMAJOR> ivcsc1,
           IVSparse::IVCSC<TYPE, IVSparseMAJOR> ivcsc2,
           IVSparse::IVCSC<TYPE, IVSparseMAJOR> ivcsc3,
           IVSparse::IVCSC<TYPE, IVSparseMAJOR> ivcsc4) {

    IVSparse::VCSC<TYPE, INDEX_TYPE, IVSparseMAJOR> vcsc5 = vcsc1;
    IVSparse::IVCSC<TYPE, IVSparseMAJOR> ivcsc5 = ivcsc1;

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
    // std::cout << vcsc5 << std::endl;
    // std::cout << ivcsc5 << std::endl;

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


void test3(IVSparse::VCSC<TYPE, INDEX_TYPE, IVSparseMAJOR> vcsc1,
           IVSparse::VCSC<TYPE, INDEX_TYPE, IVSparseMAJOR> vcsc2,
           IVSparse::VCSC<TYPE, INDEX_TYPE, IVSparseMAJOR> vcsc3,
           IVSparse::VCSC<TYPE, INDEX_TYPE, IVSparseMAJOR> vcsc4,
           IVSparse::IVCSC<TYPE, IVSparseMAJOR> ivcsc1,
           IVSparse::IVCSC<TYPE, IVSparseMAJOR> ivcsc2,
           IVSparse::IVCSC<TYPE, IVSparseMAJOR> ivcsc3,
           IVSparse::IVCSC<TYPE, IVSparseMAJOR> ivcsc4,
           Eigen::SparseMatrix<TYPE, EIGENMAJOR> eigen1,
           Eigen::SparseMatrix<TYPE, EIGENMAJOR> eigen2,
           Eigen::SparseMatrix<TYPE, EIGENMAJOR> eigen3,
           Eigen::SparseMatrix<TYPE, EIGENMAJOR> eigen4) {

    IVSparse::VCSC<TYPE, INDEX_TYPE, IVSparseMAJOR> vcsc5 = vcsc1;
    IVSparse::IVCSC<TYPE, IVSparseMAJOR> ivcsc5 = ivcsc1;

    vcsc5.append(eigen2);
    ivcsc5.append(eigen2);

    assert(vcsc5.sum() == ivcsc5.sum());

    vcsc5.append(eigen3);
    ivcsc5.append(eigen3);

    assert(vcsc5.sum() == ivcsc5.sum());

    vcsc5.append(eigen4);
    ivcsc5.append(eigen4);

    assert(vcsc5.sum() == ivcsc5.sum());

    vcsc5.append(vcsc5);
    ivcsc5.append(ivcsc5);

    assert(vcsc5.sum() == ivcsc5.sum());

    // std::cout << vcsc5 << std::endl;
    // std::cout << ivcsc5 << std::endl;

    int combinedSum = vcsc1.sum() + vcsc2.sum();
    vcsc1.append(eigen2);
    ivcsc1.append(eigen2);

    assert(vcsc1.sum() == ivcsc1.sum());
    assert(vcsc1.sum() == combinedSum);

    combinedSum = vcsc1.sum() + vcsc3.sum();
    vcsc1.append(vcsc3);
    ivcsc1.append(eigen3);
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
    vcsc3.append(eigen4);
    ivcsc3.append(ivcsc4);
    assert(vcsc3.sum() == ivcsc3.sum());
    assert(vcsc3.sum() == combinedSum);

    combinedSum = vcsc4.sum() + vcsc1.sum();
    vcsc4.append(vcsc1);
    ivcsc4.append(ivcsc1);
    assert(vcsc4.sum() == ivcsc4.sum());
    assert(vcsc4.sum() == combinedSum);

    IVSparse::VCSC<TYPE, INDEX_TYPE, IVSparseMAJOR> vcsc6 = vcsc4.transpose();
    IVSparse::IVCSC<TYPE, IVSparseMAJOR> ivcsc6 = ivcsc4.transpose();

    assert(vcsc6.sum() == vcsc4.sum());
    assert(ivcsc6.sum() == ivcsc4.sum());

    // std::cout << vcsc6 << std::endl;
    // std::cout << ivcsc6 << std::endl;

    vcsc6.append(vcsc6);
    ivcsc6.append(ivcsc6);

    assert(vcsc6.sum() == vcsc4.sum() * 2);
    assert(ivcsc6.sum() == ivcsc4.sum() * 2);

    vcsc4 = vcsc6.transpose();
    ivcsc4 = ivcsc6.transpose();

    assert(vcsc4.sum() == vcsc6.sum());
    assert(ivcsc4.sum() == ivcsc6.sum());

}


void test4(IVSparse::VCSC<TYPE, INDEX_TYPE, IVSparseMAJOR> vcsc1,
           IVSparse::VCSC<TYPE, INDEX_TYPE, IVSparseMAJOR> vcsc2,
           IVSparse::VCSC<TYPE, INDEX_TYPE, IVSparseMAJOR> vcsc3,
           IVSparse::VCSC<TYPE, INDEX_TYPE, IVSparseMAJOR> vcsc4,
           IVSparse::IVCSC<TYPE, IVSparseMAJOR> ivcsc1,
           IVSparse::IVCSC<TYPE, IVSparseMAJOR> ivcsc2,
           IVSparse::IVCSC<TYPE, IVSparseMAJOR> ivcsc3,
           IVSparse::IVCSC<TYPE, IVSparseMAJOR> ivcsc4) {


    ivcsc4.write("test");
    IVSparse::IVCSC<TYPE, IVSparseMAJOR> ivcsc5("test");

    assert(ivcsc4.sum() == ivcsc5.sum());

    vcsc4.write("test2");
    IVSparse::VCSC<TYPE, INDEX_TYPE, IVSparseMAJOR> vcsc5("test2");

    assert(vcsc4.sum() == vcsc5.sum());

    // delete test and test2
    remove("test");
    remove("test2");

    ivcsc4.append(ivcsc2);
    ivcsc4.append(ivcsc3);
    ivcsc4.write("test3");

    vcsc4.append(vcsc2);
    vcsc4.append(vcsc3);
    vcsc4.write("test4");

    IVSparse::IVCSC<TYPE, IVSparseMAJOR> ivcsc6("test3");
    IVSparse::VCSC<TYPE, INDEX_TYPE, IVSparseMAJOR> vcsc6("test4");

    assert(ivcsc4.sum() == ivcsc6.sum());
    assert(vcsc4.sum() == vcsc6.sum());

    // std::cout << ivcsc4 << std::endl << "-------------------" << std::endl;
    // std::cout << ivcsc6 << std::endl;

    remove("test3");
    remove("test4");
}


void test5(IVSparse::VCSC<TYPE, INDEX_TYPE, IVSparseMAJOR> vcsc1,
           IVSparse::VCSC<TYPE, INDEX_TYPE, IVSparseMAJOR> vcsc2,
           IVSparse::VCSC<TYPE, INDEX_TYPE, IVSparseMAJOR> vcsc3,
           IVSparse::VCSC<TYPE, INDEX_TYPE, IVSparseMAJOR> vcsc4,
           IVSparse::IVCSC<TYPE, IVSparseMAJOR> ivcsc1,
           IVSparse::IVCSC<TYPE, IVSparseMAJOR> ivcsc2,
           IVSparse::IVCSC<TYPE, IVSparseMAJOR> ivcsc3,
           IVSparse::IVCSC<TYPE, IVSparseMAJOR> ivcsc4) {


    IVSparse::IVCSC<TYPE, IVSparseMAJOR> ivcsc5 = ivcsc1.transpose();

    // std::cout << ivcsc5 << std::endl << "-------------------" << std::endl;
    // std::cout << ivcsc1 << std::endl;

    assert(ivcsc5.sum() == ivcsc1.sum());


    IVSparse::IVCSC<TYPE, IVSparseMAJOR> ivcsc6 = ivcsc2.transpose();

    // std::cout << ivcsc6 << std::endl << "-------------------" << std::endl;
    // std::cout << ivcsc2 << std::endl;

    assert(ivcsc6.sum() == ivcsc2.sum());

    IVSparse::VCSC<TYPE, INDEX_TYPE, IVSparseMAJOR> vcsc5 = vcsc1.transpose();

    // std::cout << vcsc5 << std::endl << "-------------------" << std::endl;
    // std::cout << vcsc1 << std::endl;

    assert(vcsc5.sum() == vcsc1.sum());


    IVSparse::VCSC<TYPE, INDEX_TYPE, IVSparseMAJOR> vcsc6 = vcsc2.transpose();

    // std::cout << vcsc6 << std::endl << "-------------------" << std::endl;
    // std::cout << vcsc2 << std::endl;

    assert(vcsc6.sum() == vcsc2.sum());

    // Eigen::Matrix<TYPE, -1, -1> mockEigen1 = Eigen::Matrix<TYPE, -1, -1>::Random(1000, 10);
    // Eigen::SparseMatrix<TYPE> mockEigenSparse1 = mockEigen1.sparseView();

//     IVSparse::VCSC<TYPE, INDEX_TYPE, IVSparseMAJOR> vcsc7(mockEigenSparse1);

//     std::cout << vcsc7 << std::endl;

//     std::cout << "-------------------" << std::endl;

//     IVSparse::VCSC<TYPE, INDEX_TYPE, IVSparseMAJOR> vcsc8 = vcsc7.transpose();

//     std::cout << vcsc8 << std::endl;
}


void test6(IVSparse::VCSC<TYPE, INDEX_TYPE, IVSparseMAJOR> vcsc1,
           IVSparse::VCSC<TYPE, INDEX_TYPE, IVSparseMAJOR> vcsc2,
           IVSparse::VCSC<TYPE, INDEX_TYPE, IVSparseMAJOR> vcsc3,
           IVSparse::VCSC<TYPE, INDEX_TYPE, IVSparseMAJOR> vcsc4,
           IVSparse::IVCSC<TYPE, IVSparseMAJOR> ivcsc1,
           IVSparse::IVCSC<TYPE, IVSparseMAJOR> ivcsc2,
           IVSparse::IVCSC<TYPE, IVSparseMAJOR> ivcsc3,
           IVSparse::IVCSC<TYPE, IVSparseMAJOR> ivcsc4) {

    vcsc2.append(vcsc4);
    ivcsc2.append(ivcsc4);

    IVSparse::VCSC<TYPE, INDEX_TYPE, IVSparseMAJOR> vcsc6 = vcsc2.transpose();
    IVSparse::IVCSC<TYPE, IVSparseMAJOR> ivcsc6 = ivcsc2.transpose();

    assert(ivcsc2.sum() == ivcsc6.sum());
    assert(vcsc2.sum() == vcsc6.sum());

    IVSparse::VCSC<TYPE, INDEX_TYPE, IVSparseMAJOR> vcsc7 = vcsc6.transpose();
    IVSparse::IVCSC<TYPE, IVSparseMAJOR> ivcsc7 = ivcsc6.transpose();

    assert(ivcsc7.sum() == ivcsc2.sum());
    assert(vcsc7.sum() == vcsc2.sum());

    IVSparse::IVCSC<TYPE, IVSparseMAJOR> ivcsc5 = ivcsc1.slice(0, 5);
    IVSparse::VCSC<TYPE, INDEX_TYPE, IVSparseMAJOR> vcsc5 = vcsc1.slice(0, 5);

    assert(ivcsc5.sum() == vcsc5.sum());

    // for (int i = 0; i < ivcsc5.rows(); i++) {
    //     for (int j = 0; j < ivcsc5.cols(); j++) {
    //         assert(ivcsc5(i, j) == vcsc5(i, j));
    //         assert(ivcsc5(i, j) == ivcsc1(i, j));
    //         assert(vcsc5(i, j) == vcsc1(i, j));
    //     }
    // }
    // ivcsc5 = ivcsc1.slice(1, 3);
    // vcsc5 = vcsc1.slice(1, 3);

    // assert(ivcsc5.sum() == vcsc5.sum());

    // for (int i = 0; i < ivcsc5.rows(); i++) {
    //     for (int j = 0; j < ivcsc5.cols(); j++) {
    //         assert(ivcsc5(i, j) == vcsc5(i, j));
    //         assert(ivcsc5(i, j) == ivcsc1(i, j + 1));
    //         assert(vcsc5(i, j) == vcsc1(i, j + 1));
    //     }
    // }

    // ivcsc5 = ivcsc1.slice(1, 2);
    // vcsc5 = vcsc1.slice(1, 2);

    // assert(ivcsc5.sum() == vcsc5.sum());

    // for (int i = 0; i < ivcsc5.rows(); i++) {
    //     for (int j = 0; j < ivcsc5.cols(); j++) {
    //         assert(ivcsc5(i, j) == vcsc5(i, j));
    //         assert(ivcsc5(i, j) == ivcsc1(i, j + 1));
    //         assert(vcsc5(i, j) == vcsc1(i, j + 1));
    //     }
    // }

    // ivcsc5 = ivcsc1.slice(3, 7);
    // vcsc5 = vcsc1.slice(3, 7);

    // assert(ivcsc5.sum() == vcsc5.sum());

    // for (int i = 0; i < ivcsc5.rows(); i++) {
    //     for (int j = 0; j < ivcsc5.cols(); j++) {
    //         assert(ivcsc5(i, j) == vcsc5(i, j));
    //         assert(ivcsc5(i, j) == ivcsc1(i, j + 3));
    //         assert(vcsc5(i, j) == vcsc1(i, j + 3));
    //     }
    // }

    ivcsc5 = ivcsc1.slice(0, ivcsc1.cols());
    vcsc5 = vcsc1.slice(0, vcsc1.cols());

    assert(ivcsc5.sum() == vcsc5.sum());

    for (int i = 0; i < ivcsc5.rows(); i++) {
        for (int j = 0; j < ivcsc5.cols(); j++) {
            assert(ivcsc5(i, j) == vcsc5(i, j));
            assert(ivcsc5(i, j) == ivcsc1(i, j));
            assert(vcsc5(i, j) == vcsc1(i, j));
        }
    }

}

void test7(IVSparse::VCSC<TYPE, INDEX_TYPE, IVSparseMAJOR> vcsc1,
           IVSparse::VCSC<TYPE, INDEX_TYPE, IVSparseMAJOR> vcsc2,
           IVSparse::VCSC<TYPE, INDEX_TYPE, IVSparseMAJOR> vcsc3,
           IVSparse::VCSC<TYPE, INDEX_TYPE, IVSparseMAJOR> vcsc4,
           IVSparse::IVCSC<TYPE, IVSparseMAJOR> ivcsc1,
           IVSparse::IVCSC<TYPE, IVSparseMAJOR> ivcsc2,
           IVSparse::IVCSC<TYPE, IVSparseMAJOR> ivcsc3,
           IVSparse::IVCSC<TYPE, IVSparseMAJOR> ivcsc4,
           Eigen::SparseMatrix<TYPE, EIGENMAJOR> eigen1,
           Eigen::SparseMatrix<TYPE, EIGENMAJOR> eigen2,
           Eigen::SparseMatrix<TYPE, EIGENMAJOR> eigen3,
           Eigen::SparseMatrix<TYPE, EIGENMAJOR> eigen4) {


    Eigen::SparseMatrix<TYPE, EIGENMAJOR> eigen_sparse1 = vcsc1.toEigen();
    Eigen::SparseMatrix<TYPE, EIGENMAJOR> eigen_sparse2 = vcsc2.toEigen();
    Eigen::SparseMatrix<TYPE, EIGENMAJOR> eigen_sparse3 = vcsc3.toEigen();
    Eigen::SparseMatrix<TYPE, EIGENMAJOR> eigen_sparse4 = vcsc4.toEigen();

    for (int i = 0; i < eigen_sparse1.outerSize(); ++i) {
        typename Eigen::SparseMatrix<TYPE, EIGENMAJOR>::InnerIterator it(eigen_sparse1, i);
        typename Eigen::SparseMatrix<TYPE, EIGENMAJOR>::InnerIterator it2(eigen1, i);

        while (it) {
            assert(it.value() == it2.value());
            ++it;
            ++it2;
        }
    }

    for (int i = 0; i < eigen_sparse2.outerSize(); ++i) {
        typename Eigen::SparseMatrix<TYPE, EIGENMAJOR>::InnerIterator it(eigen_sparse2, i);
        typename Eigen::SparseMatrix<TYPE, EIGENMAJOR>::InnerIterator it2(eigen2, i);

        while (it) {
            assert(it.value() == it2.value());
            ++it;
            ++it2;
        }
    }

    for (int i = 0; i < eigen_sparse3.outerSize(); ++i) {
        typename Eigen::SparseMatrix<TYPE, EIGENMAJOR>::InnerIterator it(eigen_sparse3, i);
        typename Eigen::SparseMatrix<TYPE, EIGENMAJOR>::InnerIterator it2(eigen3, i);

        while (it) {
            assert(it.value() == it2.value());
            ++it;
            ++it2;
        }
    }

    for (int i = 0; i < eigen_sparse4.outerSize(); ++i) {
        typename Eigen::SparseMatrix<TYPE, EIGENMAJOR>::InnerIterator it(eigen_sparse4, i);
        typename Eigen::SparseMatrix<TYPE, EIGENMAJOR>::InnerIterator it2(eigen4, i);

        while (it) {
            assert(it.value() == it2.value());
            ++it;
            ++it2;
        }
    }
}


void test8(IVSparse::VCSC<TYPE, INDEX_TYPE, IVSparseMAJOR> vcsc1,
           IVSparse::VCSC<TYPE, INDEX_TYPE, IVSparseMAJOR> vcsc2,
           IVSparse::VCSC<TYPE, INDEX_TYPE, IVSparseMAJOR> vcsc3,
           IVSparse::VCSC<TYPE, INDEX_TYPE, IVSparseMAJOR> vcsc4,
           IVSparse::IVCSC<TYPE, IVSparseMAJOR> ivcsc1,
           IVSparse::IVCSC<TYPE, IVSparseMAJOR> ivcsc2,
           IVSparse::IVCSC<TYPE, IVSparseMAJOR> ivcsc3,
           IVSparse::IVCSC<TYPE, IVSparseMAJOR> ivcsc4,
           Eigen::SparseMatrix<TYPE, EIGENMAJOR> eigen1,
           Eigen::SparseMatrix<TYPE, EIGENMAJOR> eigen2,
           Eigen::SparseMatrix<TYPE, EIGENMAJOR> eigen3,
           Eigen::SparseMatrix<TYPE, EIGENMAJOR> eigen4) {



    vcsc1 *= 7;
    ivcsc1 *= 7;
    assert(eigen1.sum() * 7 == vcsc1.sum());
    assert(eigen1.sum() * 7 == ivcsc1.sum());

    vcsc2 *= 7;
    ivcsc2 *= 7;
    assert(eigen2.sum() * 7 == vcsc2.sum());
    assert(eigen2.sum() * 7 == ivcsc2.sum());

    vcsc3 *= 7;
    ivcsc3 *= 7;

    assert(eigen3.sum() * 7 == vcsc3.sum());
    assert(eigen3.sum() * 7 == ivcsc3.sum());

    vcsc4 *= 7;
    ivcsc4 *= 7;
    assert(eigen4.sum() * 7 == vcsc4.sum());
    assert(eigen4.sum() * 7 == ivcsc4.sum());

}


void test9(IVSparse::VCSC<TYPE, INDEX_TYPE, IVSparseMAJOR> vcsc1,
           IVSparse::VCSC<TYPE, INDEX_TYPE, IVSparseMAJOR> vcsc2,
           IVSparse::VCSC<TYPE, INDEX_TYPE, IVSparseMAJOR> vcsc3,
           IVSparse::VCSC<TYPE, INDEX_TYPE, IVSparseMAJOR> vcsc4,
           IVSparse::IVCSC<TYPE, IVSparseMAJOR> ivcsc1,
           IVSparse::IVCSC<TYPE, IVSparseMAJOR> ivcsc2,
           IVSparse::IVCSC<TYPE, IVSparseMAJOR> ivcsc3,
           IVSparse::IVCSC<TYPE, IVSparseMAJOR> ivcsc4,
           Eigen::SparseMatrix<TYPE, EIGENMAJOR> eigen1,
           Eigen::SparseMatrix<TYPE, EIGENMAJOR> eigen2,
           Eigen::SparseMatrix<TYPE, EIGENMAJOR> eigen3,
           Eigen::SparseMatrix<TYPE, EIGENMAJOR> eigen4) {


    IVSparse::VCSC<TYPE, INDEX_TYPE, IVSparseMAJOR> vcsc5 = ivcsc1;
    IVSparse::IVCSC<TYPE, IVSparseMAJOR> ivcsc5 = vcsc1;

    assert(vcsc5.sum() == ivcsc5.sum());
    assert(vcsc5.sum() == eigen1.sum());

    IVSparse::VCSC<TYPE, INDEX_TYPE, IVSparseMAJOR> vcsc6 = ivcsc2;
    IVSparse::IVCSC<TYPE, IVSparseMAJOR> ivcsc6 = vcsc2;

    assert(vcsc6.sum() == ivcsc6.sum());
    assert(vcsc6.sum() == eigen2.sum());

    IVSparse::VCSC<TYPE, INDEX_TYPE, IVSparseMAJOR> vcsc7 = ivcsc3;
    IVSparse::IVCSC<TYPE, IVSparseMAJOR> ivcsc7 = vcsc3;

    assert(vcsc7.sum() == ivcsc7.sum());
    assert(vcsc7.sum() == eigen3.sum());

    IVSparse::VCSC<TYPE, INDEX_TYPE, IVSparseMAJOR> vcsc8 = ivcsc4;
    IVSparse::IVCSC<TYPE, IVSparseMAJOR> ivcsc8 = vcsc4;

    assert(vcsc8.sum() == ivcsc8.sum());
    assert(vcsc8.sum() == eigen4.sum());

    IVSparse::VCSC<TYPE, INDEX_TYPE, IVSparseMAJOR> vcsc9 = ivcsc5;
    IVSparse::IVCSC<TYPE, IVSparseMAJOR> ivcsc9 = vcsc5;

    assert(vcsc9.sum() == ivcsc9.sum());
    assert(vcsc9.sum() == eigen1.sum());

    IVSparse::VCSC<TYPE, INDEX_TYPE, IVSparseMAJOR> vcsc10;
    IVSparse::IVCSC<TYPE, IVSparseMAJOR> ivcsc10;
    Eigen::SparseMatrix<TYPE> eigen5;
    Eigen::SparseMatrix<TYPE> eigen6;


    vcsc10 = ivcsc5;
    ivcsc10 = vcsc5;
    eigen5 = vcsc5.toEigen();
    eigen6 = ivcsc5.toEigen();

    assert(vcsc10.sum() == ivcsc10.sum());
    assert(vcsc10.sum() == eigen5.sum());
    assert(eigen5.sum() == eigen1.sum());
    assert(eigen6.sum() == eigen1.sum());

    IVSparse::VCSC<TYPE, INDEX_TYPE, IVSparseMAJOR> vcsc11(ivcsc10);
    IVSparse::IVCSC<TYPE, IVSparseMAJOR> ivcsc11(vcsc10);

    assert(vcsc11.sum() == ivcsc11.sum());
    assert(vcsc11.sum() == eigen5.sum());

}