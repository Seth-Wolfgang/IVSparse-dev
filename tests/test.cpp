#include "test.hpp"


int main() {

    int cols1, cols2, cols3, cols4;
    int rows1, rows2, rows3, rows4;
    int a = (rand() % 100 + 1) % std::numeric_limits<INDEX_TYPE>::max() + 1;
    int b = (rand() % 100 + 1) % std::numeric_limits<INDEX_TYPE>::max() + 1;
    std::cout << "a: " << a << std::endl;
    std::cout << "b: " << b << std::endl;
    #ifdef IVSPARSE_HAS_OPENMP
    Eigen::initParallel();
    #endif
    if constexpr (IVSparseMAJOR) {
        cols1 = a;
        cols2 = a;
        cols3 = a;
        cols4 = a;

        rows1 = a;
        rows2 = b;
        rows3 = (a + b) % std::numeric_limits<INDEX_TYPE>::max() + 1;
        rows4 = 1;
    }
    else {
        cols1 = a;
        cols2 = b;
        cols3 = (a + b) % std::numeric_limits<INDEX_TYPE>::max() + 1;
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
    // test5(vcsc1, vcsc2, vcsc3, vcsc4, ivcsc1, ivcsc2, ivcsc3, ivcsc4);
    // test6(vcsc1, vcsc2, vcsc3, vcsc4, ivcsc1, ivcsc2, ivcsc3, ivcsc4);
    // test7(vcsc1, vcsc2, vcsc3, vcsc4, ivcsc1, ivcsc2, ivcsc3, ivcsc4, eigen_sparse1, eigen_sparse2, eigen_sparse3, eigen_sparse4);
    // test8(vcsc1, vcsc2, vcsc3, vcsc4, ivcsc1, ivcsc2, ivcsc3, ivcsc4, eigen_sparse1, eigen_sparse2, eigen_sparse3, eigen_sparse4);
    // test9(vcsc1, vcsc2, vcsc3, vcsc4, ivcsc1, ivcsc2, ivcsc3, ivcsc4, eigen_sparse1, eigen_sparse2, eigen_sparse3, eigen_sparse4);
    // test10(vcsc1, vcsc2, vcsc3, vcsc4, ivcsc1, ivcsc2, ivcsc3, ivcsc4, eigen_sparse1, eigen_sparse2, eigen_sparse3, eigen_sparse4);
    // test11(vcsc1, vcsc2, vcsc3, vcsc4, ivcsc1, ivcsc2, ivcsc3, ivcsc4, eigen_sparse1, eigen_sparse2, eigen_sparse3, eigen_sparse4);
    // test12(vcsc1, vcsc2, vcsc3, vcsc4, ivcsc1, ivcsc2, ivcsc3, ivcsc4, eigen_sparse1, eigen_sparse2, eigen_sparse3, eigen_sparse4);
    // test13(vcsc1, vcsc2, vcsc3, vcsc4, ivcsc1, ivcsc2, ivcsc3, ivcsc4, eigen_sparse1, eigen_sparse2, eigen_sparse3, eigen_sparse4);
    // test14(vcsc1, vcsc2, vcsc3, vcsc4, ivcsc1, ivcsc2, ivcsc3, ivcsc4, eigen_sparse1, eigen_sparse2, eigen_sparse3, eigen_sparse4);
    // test15(vcsc1, vcsc2, vcsc3, vcsc4, ivcsc1, ivcsc2, ivcsc3, ivcsc4, eigen_sparse1, eigen_sparse2, eigen_sparse3, eigen_sparse4);
    // test16(vcsc1, vcsc2, vcsc3, vcsc4, ivcsc1, ivcsc2, ivcsc3, ivcsc4, eigen_sparse1, eigen_sparse2, eigen_sparse3, eigen_sparse4);
    // test17(vcsc1, vcsc2, vcsc3, vcsc4, ivcsc1, ivcsc2, ivcsc3, ivcsc4, eigen_sparse1, eigen_sparse2, eigen_sparse3, eigen_sparse4);


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

    // vcsc5.print();
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
    IVSparse::IVCSC<TYPE, IVSparseMAJOR> ivcsc5("test.ivcsc");

    assert(ivcsc4.sum() == ivcsc5.sum());

    vcsc4.write("test2.vcsc");
    IVSparse::VCSC<TYPE, INDEX_TYPE, IVSparseMAJOR> vcsc5("test2.vcsc");

    assert(vcsc4.sum() == vcsc5.sum());

    // delete test and test2
    remove("test.ivcsc");
    remove("test2.vcsc");

    ivcsc4.append(ivcsc2);
    ivcsc4.append(ivcsc3);
    ivcsc4.write("test3");

    vcsc4.append(vcsc2);
    vcsc4.append(vcsc3);
    vcsc4.write("test4");

    IVSparse::IVCSC<TYPE, IVSparseMAJOR> ivcsc6("test3.ivcsc");
    IVSparse::VCSC<TYPE, INDEX_TYPE, IVSparseMAJOR> vcsc6("test4.vcsc");

    assert(ivcsc4.sum() == ivcsc6.sum());
    assert(vcsc4.sum() == vcsc6.sum());

    ivcsc6.read("test3.ivcsc");
    vcsc6.read("test4.vcsc");

    assert(ivcsc4.sum() == ivcsc6.sum());
    assert(vcsc4.sum() == vcsc6.sum());

    // std::cout << ivcsc4 << std::endl << "-------------------" << std::endl;
    // std::cout << ivcsc6 << std::endl;

    remove("test3.ivcsc");
    remove("test4.vcsc");
    
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

    IVSparse::VCSC<TYPE, INDEX_TYPE, IVSparseMAJOR> vcsc12 = ivcsc11;
    IVSparse::IVCSC<TYPE, IVSparseMAJOR> ivcsc12 = vcsc11;

    assert(vcsc12.sum() == ivcsc12.sum());
    assert(vcsc12.sum() == eigen5.sum());
}


void test10(IVSparse::VCSC<TYPE, INDEX_TYPE, IVSparseMAJOR> vcsc1,
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


    Eigen::Matrix<TYPE, -1, -1> denseMat1(eigen1);

    std::cout << "vcsc1.trace(): " << vcsc1.trace() << std::endl;
    std::cout << "ivcsc1.trace(): " << ivcsc1.trace() << std::endl;
    std::cout << "denseMat1.trace(): " << denseMat1.trace() << std::endl;

    assert(vcsc1.trace() == ivcsc1.trace());
    assert(vcsc1.trace() == denseMat1.trace());
    assert(ivcsc1.trace() == ivcsc1.transpose().trace());
    assert(vcsc1.trace() == vcsc1.transpose().trace());
}


void test11(IVSparse::VCSC<TYPE, INDEX_TYPE, IVSparseMAJOR> vcsc1,
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

    vcsc1.append(vcsc4);
    vcsc2.append(vcsc3);
    vcsc3.append(vcsc2);
    vcsc4.append(vcsc1);

    ivcsc1.append(ivcsc4);
    ivcsc2.append(ivcsc3);
    ivcsc3.append(ivcsc2);
    ivcsc4.append(ivcsc1);
    int rows;
    int cols;

    Eigen::Matrix<TYPE, -1, -1> denseMat1;
    Eigen::Matrix<TYPE, -1, -1> denseMat2;
    Eigen::Matrix<TYPE, -1, -1> denseMat3;
    Eigen::Matrix<TYPE, -1, -1> denseMat4;

    if constexpr (IVSparseMAJOR) {
        denseMat1 = Eigen::Matrix<TYPE, -1, -1>(eigen1.rows(), eigen1.cols() + eigen4.cols());
        denseMat2 = Eigen::Matrix<TYPE, -1, -1>(eigen2.rows(), eigen2.cols() + eigen3.cols());
        denseMat3 = Eigen::Matrix<TYPE, -1, -1>(eigen3.rows(), eigen3.cols() + eigen2.cols());
        denseMat4 = Eigen::Matrix<TYPE, -1, -1>(eigen4.rows(), eigen4.cols() + eigen1.cols());

    }
    else {
        denseMat1 = Eigen::Matrix<TYPE, -1, -1>(eigen1.rows() + eigen4.rows(), eigen1.cols());
        denseMat2 = Eigen::Matrix<TYPE, -1, -1>(eigen2.rows() + eigen3.rows(), eigen2.cols());
        denseMat3 = Eigen::Matrix<TYPE, -1, -1>(eigen3.rows() + eigen2.rows(), eigen3.cols());
        denseMat4 = Eigen::Matrix<TYPE, -1, -1>(eigen4.rows() + eigen1.rows(), eigen4.cols());
    }

    denseMat1 << Eigen::Matrix<TYPE, -1, -1>(eigen1), Eigen::Matrix<TYPE, -1, -1>(eigen4);
    denseMat2 << Eigen::Matrix<TYPE, -1, -1>(eigen2), Eigen::Matrix<TYPE, -1, -1>(eigen3);
    denseMat3 << Eigen::Matrix<TYPE, -1, -1>(eigen3), Eigen::Matrix<TYPE, -1, -1>(eigen2);
    denseMat4 << Eigen::Matrix<TYPE, -1, -1>(eigen4), Eigen::Matrix<TYPE, -1, -1>(eigen1);

    Eigen::SparseMatrix<TYPE, EIGENMAJOR> vcsc_to_eigen1 = vcsc1.toEigen();
    Eigen::SparseMatrix<TYPE, EIGENMAJOR> vcsc_to_eigen2 = vcsc2.toEigen();
    Eigen::SparseMatrix<TYPE, EIGENMAJOR> vcsc_to_eigen3 = vcsc3.toEigen();
    Eigen::SparseMatrix<TYPE, EIGENMAJOR> vcsc_to_eigen4 = vcsc4.toEigen();

    Eigen::SparseMatrix<TYPE, EIGENMAJOR> ivcsc_to_eigen1 = ivcsc1.toEigen();
    Eigen::SparseMatrix<TYPE, EIGENMAJOR> ivcsc_to_eigen2 = ivcsc2.toEigen();
    Eigen::SparseMatrix<TYPE, EIGENMAJOR> ivcsc_to_eigen3 = ivcsc3.toEigen();
    Eigen::SparseMatrix<TYPE, EIGENMAJOR> ivcsc_to_eigen4 = ivcsc4.toEigen();

    Eigen::SparseMatrix<TYPE, EIGENMAJOR> eigen_sparse1 = denseMat1.sparseView();
    Eigen::SparseMatrix<TYPE, EIGENMAJOR> eigen_sparse2 = denseMat2.sparseView();
    Eigen::SparseMatrix<TYPE, EIGENMAJOR> eigen_sparse3 = denseMat3.sparseView();
    Eigen::SparseMatrix<TYPE, EIGENMAJOR> eigen_sparse4 = denseMat4.sparseView();

    for (int i = 0; i < eigen_sparse1.outerSize(); ++i) {
        typename Eigen::SparseMatrix<TYPE, EIGENMAJOR>::InnerIterator it(eigen_sparse1, i);
        typename Eigen::SparseMatrix<TYPE, EIGENMAJOR>::InnerIterator it2(vcsc_to_eigen1, i);
        typename Eigen::SparseMatrix<TYPE, EIGENMAJOR>::InnerIterator it3(ivcsc_to_eigen1, i);


        while (it) {
            // std::cout << "1| eigen: " << it.value() << " vcsc: " << it2.value() << " ivcsc: " << it3.value() << std::endl;
            assert(it.value() == it2.value() && it.value() == it3.value());
            ++it;
            ++it2;
            ++it3;
        }
    }

    for (int i = 0; i < eigen_sparse2.outerSize(); ++i) {
        typename Eigen::SparseMatrix<TYPE, EIGENMAJOR>::InnerIterator it(eigen_sparse2, i);
        typename Eigen::SparseMatrix<TYPE, EIGENMAJOR>::InnerIterator it2(vcsc_to_eigen2, i);
        typename Eigen::SparseMatrix<TYPE, EIGENMAJOR>::InnerIterator it3(ivcsc_to_eigen2, i);

        while (it) {
            // std::cout << "2| eigen: " << it.value() << " vcsc: " << it2.value() << " ivcsc: " << it3.value() << std::endl;
            assert(it.value() == it2.value() && it.value() == it3.value());
            ++it;
            ++it2;
            ++it3;
        }
    }

    for (int i = 0; i < eigen_sparse3.outerSize(); ++i) {
        typename Eigen::SparseMatrix<TYPE, EIGENMAJOR>::InnerIterator it(eigen_sparse3, i);
        typename Eigen::SparseMatrix<TYPE, EIGENMAJOR>::InnerIterator it2(vcsc_to_eigen3, i);
        typename Eigen::SparseMatrix<TYPE, EIGENMAJOR>::InnerIterator it3(ivcsc_to_eigen3, i);

        while (it) {
            // std::cout << "3| eigen: " << it.value() << " vcsc: " << it2.value() << " ivcsc: " << it3.value() << std::endl;
            assert(it.value() == it2.value() && it.value() == it3.value());
            ++it;
            ++it2;
            ++it3;
        }
    }

    for (int i = 0; i < eigen_sparse4.outerSize(); ++i) {
        typename Eigen::SparseMatrix<TYPE, EIGENMAJOR>::InnerIterator it(eigen_sparse4, i);
        typename Eigen::SparseMatrix<TYPE, EIGENMAJOR>::InnerIterator it2(vcsc_to_eigen4, i);
        typename Eigen::SparseMatrix<TYPE, EIGENMAJOR>::InnerIterator it3(ivcsc_to_eigen4, i);

        while (it) {
            // std::cout << "4| eigen: " << it.value() << " vcsc: " << it2.value() << " ivcsc: " << it3.value() << std::endl;
            assert(it.value() == it2.value() && it.value() == it3.value());
            ++it;
            ++it2;
            ++it3;
        }
    }
}


void test12(IVSparse::VCSC<TYPE, INDEX_TYPE, IVSparseMAJOR> vcsc1,
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

    // std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
    vcsc1.append(eigen4.valuePtr(), eigen4.innerIndexPtr(), eigen4.outerIndexPtr(), eigen4.innerSize(), eigen4.outerSize(), eigen4.nonZeros());
    vcsc2.append(eigen3.valuePtr(), eigen3.innerIndexPtr(), eigen3.outerIndexPtr(), eigen3.innerSize(), eigen3.outerSize(), eigen3.nonZeros());
    vcsc3.append(eigen2.valuePtr(), eigen2.innerIndexPtr(), eigen2.outerIndexPtr(), eigen2.innerSize(), eigen2.outerSize(), eigen2.nonZeros());
    vcsc4.append(eigen1.valuePtr(), eigen1.innerIndexPtr(), eigen1.outerIndexPtr(), eigen1.innerSize(), eigen1.outerSize(), eigen1.nonZeros());
    // std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
    // std::cout << "vcsc append: " << std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() << std::endl;

    // t1 = std::chrono::high_resolution_clock::now();
    ivcsc1.append(eigen4.valuePtr(), eigen4.innerIndexPtr(), eigen4.outerIndexPtr(), eigen4.innerSize(), eigen4.outerSize(), eigen4.nonZeros());
    ivcsc2.append(eigen3.valuePtr(), eigen3.innerIndexPtr(), eigen3.outerIndexPtr(), eigen3.innerSize(), eigen3.outerSize(), eigen3.nonZeros());
    ivcsc3.append(eigen2.valuePtr(), eigen2.innerIndexPtr(), eigen2.outerIndexPtr(), eigen2.innerSize(), eigen2.outerSize(), eigen2.nonZeros());
    ivcsc4.append(eigen1.valuePtr(), eigen1.innerIndexPtr(), eigen1.outerIndexPtr(), eigen1.innerSize(), eigen1.outerSize(), eigen1.nonZeros());
    // t2 = std::chrono::high_resolution_clock::now();
    // std::cout << "ivcsc append: " << std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() << std::endl;

    Eigen::Matrix<TYPE, -1, -1> denseMat1;
    Eigen::Matrix<TYPE, -1, -1> denseMat2;
    Eigen::Matrix<TYPE, -1, -1> denseMat3;
    Eigen::Matrix<TYPE, -1, -1> denseMat4;

    // t1 = std::chrono::high_resolution_clock::now();
    if constexpr (IVSparseMAJOR) {
        denseMat1 = Eigen::Matrix<TYPE, -1, -1>(eigen1.rows(), eigen1.cols() + eigen4.cols());
        denseMat2 = Eigen::Matrix<TYPE, -1, -1>(eigen2.rows(), eigen2.cols() + eigen3.cols());
        denseMat3 = Eigen::Matrix<TYPE, -1, -1>(eigen3.rows(), eigen3.cols() + eigen2.cols());
        denseMat4 = Eigen::Matrix<TYPE, -1, -1>(eigen4.rows(), eigen4.cols() + eigen1.cols());

    }
    else {
        denseMat1 = Eigen::Matrix<TYPE, -1, -1>(eigen1.rows() + eigen4.rows(), eigen1.cols());
        denseMat2 = Eigen::Matrix<TYPE, -1, -1>(eigen2.rows() + eigen3.rows(), eigen2.cols());
        denseMat3 = Eigen::Matrix<TYPE, -1, -1>(eigen3.rows() + eigen2.rows(), eigen3.cols());
        denseMat4 = Eigen::Matrix<TYPE, -1, -1>(eigen4.rows() + eigen1.rows(), eigen4.cols());
    }
    // t2 = std::chrono::high_resolution_clock::now();
    // std::cout << "denseMat init: " << std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() << std::endl;

    // t1 = std::chrono::high_resolution_clock::now();
    denseMat1 << Eigen::Matrix<TYPE, -1, -1>(eigen1), Eigen::Matrix<TYPE, -1, -1>(eigen4);
    denseMat2 << Eigen::Matrix<TYPE, -1, -1>(eigen2), Eigen::Matrix<TYPE, -1, -1>(eigen3);
    denseMat3 << Eigen::Matrix<TYPE, -1, -1>(eigen3), Eigen::Matrix<TYPE, -1, -1>(eigen2);
    denseMat4 << Eigen::Matrix<TYPE, -1, -1>(eigen4), Eigen::Matrix<TYPE, -1, -1>(eigen1);
    // t2 = std::chrono::high_resolution_clock::now();
    // std::cout << "denseMat append: " << std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() << std::endl;

    // t1 = std::chrono::high_resolution_clock::now();
    Eigen::SparseMatrix<TYPE, EIGENMAJOR> vcsc_to_eigen1 = vcsc1.toEigen();
    Eigen::SparseMatrix<TYPE, EIGENMAJOR> vcsc_to_eigen2 = vcsc2.toEigen();
    Eigen::SparseMatrix<TYPE, EIGENMAJOR> vcsc_to_eigen3 = vcsc3.toEigen();
    Eigen::SparseMatrix<TYPE, EIGENMAJOR> vcsc_to_eigen4 = vcsc4.toEigen();
    // t2 = std::chrono::high_resolution_clock::now();
    // std::cout << "vcsc toEigen: " << std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() << std::endl;

    // t1 = std::chrono::high_resolution_clock::now();
    Eigen::SparseMatrix<TYPE, EIGENMAJOR> ivcsc_to_eigen1 = ivcsc1.toEigen();
    Eigen::SparseMatrix<TYPE, EIGENMAJOR> ivcsc_to_eigen2 = ivcsc2.toEigen();
    Eigen::SparseMatrix<TYPE, EIGENMAJOR> ivcsc_to_eigen3 = ivcsc3.toEigen();
    Eigen::SparseMatrix<TYPE, EIGENMAJOR> ivcsc_to_eigen4 = ivcsc4.toEigen();
    // t2 = std::chrono::high_resolution_clock::now();
    // std::cout << "ivcsc toEigen: " << std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() << std::endl;

    // t1 = std::chrono::high_resolution_clock::now();
    Eigen::SparseMatrix<TYPE, EIGENMAJOR> eigen_sparse1 = denseMat1.sparseView();
    Eigen::SparseMatrix<TYPE, EIGENMAJOR> eigen_sparse2 = denseMat2.sparseView();
    Eigen::SparseMatrix<TYPE, EIGENMAJOR> eigen_sparse3 = denseMat3.sparseView();
    Eigen::SparseMatrix<TYPE, EIGENMAJOR> eigen_sparse4 = denseMat4.sparseView();
    // t2 = std::chrono::high_resolution_clock::now();
    // std::cout << "denseMat toEigen: " << std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() << std::endl;

    for (int i = 0; i < eigen_sparse1.outerSize(); ++i) {
        typename Eigen::SparseMatrix<TYPE, EIGENMAJOR>::InnerIterator it(eigen_sparse1, i);
        typename Eigen::SparseMatrix<TYPE, EIGENMAJOR>::InnerIterator it2(vcsc_to_eigen1, i);
        typename Eigen::SparseMatrix<TYPE, EIGENMAJOR>::InnerIterator it3(ivcsc_to_eigen1, i);


        while (it) {
            // std::cout << "1| eigen: " << it.value() << " vcsc: " << it2.value() << " ivcsc: " << it3.value() << std::endl;
            assert(it.value() == it2.value() && it.value() == it3.value());
            ++it;
            ++it2;
            ++it3;
        }
    }

    for (int i = 0; i < eigen_sparse2.outerSize(); ++i) {
        typename Eigen::SparseMatrix<TYPE, EIGENMAJOR>::InnerIterator it(eigen_sparse2, i);
        typename Eigen::SparseMatrix<TYPE, EIGENMAJOR>::InnerIterator it2(vcsc_to_eigen2, i);
        typename Eigen::SparseMatrix<TYPE, EIGENMAJOR>::InnerIterator it3(ivcsc_to_eigen2, i);

        while (it) {
            // std::cout << "2| eigen: " << it.value() << " vcsc: " << it2.value() << " ivcsc: " << it3.value() << std::endl;
            assert(it.value() == it2.value() && it.value() == it3.value());
            ++it;
            ++it2;
            ++it3;
        }
    }

    for (int i = 0; i < eigen_sparse3.outerSize(); ++i) {
        typename Eigen::SparseMatrix<TYPE, EIGENMAJOR>::InnerIterator it(eigen_sparse3, i);
        typename Eigen::SparseMatrix<TYPE, EIGENMAJOR>::InnerIterator it2(vcsc_to_eigen3, i);
        typename Eigen::SparseMatrix<TYPE, EIGENMAJOR>::InnerIterator it3(ivcsc_to_eigen3, i);

        while (it) {
            // std::cout << "3| eigen: " << it.value() << " vcsc: " << it2.value() << " ivcsc: " << it3.value() << std::endl;
            assert(it.value() == it2.value() && it.value() == it3.value());
            ++it;
            ++it2;
            ++it3;
        }
    }

    for (int i = 0; i < eigen_sparse4.outerSize(); ++i) {
        typename Eigen::SparseMatrix<TYPE, EIGENMAJOR>::InnerIterator it(eigen_sparse4, i);
        typename Eigen::SparseMatrix<TYPE, EIGENMAJOR>::InnerIterator it2(vcsc_to_eigen4, i);
        typename Eigen::SparseMatrix<TYPE, EIGENMAJOR>::InnerIterator it3(ivcsc_to_eigen4, i);

        while (it) {
            // std::cout << "4| eigen: " << it.value() << " vcsc: " << it2.value() << " ivcsc: " << it3.value() << std::endl;
            assert(it.value() == it2.value() && it.value() == it3.value());
            ++it;
            ++it2;
            ++it3;
        }
    }
}


void test13(IVSparse::VCSC<TYPE, INDEX_TYPE, IVSparseMAJOR> vcsc1,
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

    Eigen::Matrix<TYPE, -1, -1> denseMat1(eigen1);
    Eigen::Matrix<TYPE, -1, -1> denseMat2(eigen2);
    Eigen::Matrix<TYPE, -1, -1> denseMat3(eigen3);
    Eigen::Matrix<TYPE, -1, -1> denseMat4(eigen4);

    Eigen::Matrix<TYPE, -1, -1> vcsc_sum1 = vcsc1.rowSum();
    Eigen::Matrix<TYPE, -1, -1> ivcsc_sum1 = ivcsc1.rowSum();
    Eigen::Matrix<TYPE, -1, -1> denseMat_sum1 = denseMat1.rowwise().sum();

    Eigen::Matrix<TYPE, -1, -1> vcsc_sum2 = vcsc2.rowSum();
    Eigen::Matrix<TYPE, -1, -1> ivcsc_sum2 = ivcsc2.rowSum();
    Eigen::Matrix<TYPE, -1, -1> denseMat_sum2 = denseMat2.rowwise().sum();


    Eigen::Matrix<TYPE, -1, -1> vcsc_sum3 = vcsc3.rowSum();
    Eigen::Matrix<TYPE, -1, -1> ivcsc_sum3 = ivcsc3.rowSum();
    Eigen::Matrix<TYPE, -1, -1> denseMat_sum3 = denseMat3.rowwise().sum();


    Eigen::Matrix<TYPE, -1, -1> vcsc_sum4 = vcsc4.rowSum();
    Eigen::Matrix<TYPE, -1, -1> ivcsc_sum4 = ivcsc4.rowSum();
    Eigen::Matrix<TYPE, -1, -1> denseMat_sum4 = denseMat4.rowwise().sum();

    for (int i = 0; i < vcsc_sum1.rows(); i++) {
        assert(vcsc_sum1(i, 0) == ivcsc_sum1(i, 0));
        assert(vcsc_sum1(i, 0) == denseMat_sum1(i, 0));
    }

    for (int i = 0; i < vcsc_sum2.rows(); i++) {
        assert(vcsc_sum2(i, 0) == ivcsc_sum2(i, 0));
        assert(vcsc_sum2(i, 0) == denseMat_sum2(i, 0));
    }
    for (int i = 0; i < vcsc_sum3.rows(); i++) {
        assert(vcsc_sum3(i, 0) == ivcsc_sum3(i, 0));
        assert(vcsc_sum3(i, 0) == denseMat_sum3(i, 0));
    }
    for (int i = 0; i < vcsc_sum4.rows(); i++) {
        assert(vcsc_sum4(i, 0) == ivcsc_sum4(i, 0));
        assert(vcsc_sum4(i, 0) == denseMat_sum4(i, 0));
    }


    vcsc_sum1 = vcsc1.colSum();
    ivcsc_sum1 = ivcsc1.colSum();
    denseMat_sum1 = denseMat1.colwise().sum();

    vcsc_sum2 = vcsc2.colSum();
    ivcsc_sum2 = ivcsc2.colSum();
    denseMat_sum2 = denseMat2.colwise().sum();


    vcsc_sum3 = vcsc3.colSum();
    ivcsc_sum3 = ivcsc3.colSum();
    denseMat_sum3 = denseMat3.colwise().sum();


    vcsc_sum4 = vcsc4.colSum();
    ivcsc_sum4 = ivcsc4.colSum();
    denseMat_sum4 = denseMat4.colwise().sum();

    for (int i = 0; i < vcsc_sum1.cols(); i++) {
        assert(vcsc_sum1(0, i) == ivcsc_sum1(0, i));
        assert(vcsc_sum1(0, i) == denseMat_sum1(0, i));
    }

    for (int i = 0; i < vcsc_sum2.cols(); i++) {
        assert(vcsc_sum2(0, i) == ivcsc_sum2(0, i));
        assert(vcsc_sum2(0, i) == denseMat_sum2(0, i));
    }

    for (int i = 0; i < vcsc_sum3.cols(); i++) {
        assert(vcsc_sum3(0, i) == ivcsc_sum3(0, i));
        assert(vcsc_sum3(0, i) == denseMat_sum3(0, i));
    }

    for (int i = 0; i < vcsc_sum4.cols(); i++) {
        assert(vcsc_sum4(0, i) == ivcsc_sum4(0, i));
        assert(vcsc_sum4(0, i) == denseMat_sum4(0, i));
    }

}


void test14(IVSparse::VCSC<TYPE, INDEX_TYPE, IVSparseMAJOR> vcsc1,
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


    Eigen::Matrix<TYPE, -1, -1> denseMat1(eigen1);
    Eigen::Matrix<TYPE, -1, -1> denseMat2(eigen2);
    Eigen::Matrix<TYPE, -1, -1> denseMat3(eigen3);
    Eigen::Matrix<TYPE, -1, -1> denseMat4(eigen4);

    Eigen::Matrix<TYPE, -1, -1> vcsc_sum1 = vcsc1.min(1);
    Eigen::Matrix<TYPE, -1, -1> ivcsc_sum1 = ivcsc1.min(1);
    Eigen::Matrix<TYPE, -1, -1> denseMat_sum1 = denseMat1.rowwise().minCoeff();

    Eigen::Matrix<TYPE, -1, -1> vcsc_sum2 = vcsc2.min(1);
    Eigen::Matrix<TYPE, -1, -1> ivcsc_sum2 = ivcsc2.min(1);
    Eigen::Matrix<TYPE, -1, -1> denseMat_sum2 = denseMat2.rowwise().minCoeff();


    Eigen::Matrix<TYPE, -1, -1> vcsc_sum3 = vcsc3.min(1);
    Eigen::Matrix<TYPE, -1, -1> ivcsc_sum3 = ivcsc3.min(1);
    Eigen::Matrix<TYPE, -1, -1> denseMat_sum3 = denseMat3.rowwise().minCoeff();


    Eigen::Matrix<TYPE, -1, -1> vcsc_sum4 = vcsc4.min(1);
    Eigen::Matrix<TYPE, -1, -1> ivcsc_sum4 = ivcsc4.min(1);
    Eigen::Matrix<TYPE, -1, -1> denseMat_sum4 = denseMat4.rowwise().minCoeff();

    for (int i = 0; i < vcsc_sum1.rows(); i++) {
        assert(vcsc_sum1(i, 0) == ivcsc_sum1(i, 0));
        assert(vcsc_sum1(i, 0) == denseMat_sum1(i, 0));
    }

    for (int i = 0; i < vcsc_sum2.rows(); i++) {
        assert(vcsc_sum2(i, 0) == ivcsc_sum2(i, 0));
        assert(vcsc_sum2(i, 0) == denseMat_sum2(i, 0));
    }
    for (int i = 0; i < vcsc_sum3.rows(); i++) {
        assert(vcsc_sum3(i, 0) == ivcsc_sum3(i, 0));
        assert(vcsc_sum3(i, 0) == denseMat_sum3(i, 0));
    }
    for (int i = 0; i < vcsc_sum4.rows(); i++) {
        assert(vcsc_sum4(i, 0) == ivcsc_sum4(i, 0));
        assert(vcsc_sum4(i, 0) == denseMat_sum4(i, 0));
    }


    vcsc_sum1 = vcsc1.max(1);
    ivcsc_sum1 = ivcsc1.max(1);
    denseMat_sum1 = denseMat1.rowwise().maxCoeff();

    vcsc_sum2 = vcsc2.max(1);
    ivcsc_sum2 = ivcsc2.max(1);
    denseMat_sum2 = denseMat2.rowwise().maxCoeff();


    vcsc_sum3 = vcsc3.max(1);
    ivcsc_sum3 = ivcsc3.max(1);
    denseMat_sum3 = denseMat3.rowwise().maxCoeff();


    vcsc_sum4 = vcsc4.max(1);
    ivcsc_sum4 = ivcsc4.max(1);
    denseMat_sum4 = denseMat4.rowwise().maxCoeff();

    for (int i = 0; i < vcsc_sum1.cols(); i++) {
        assert(vcsc_sum1(0, i) == ivcsc_sum1(0, i));
        assert(vcsc_sum1(0, i) == denseMat_sum1(0, i));
    }

    for (int i = 0; i < vcsc_sum2.cols(); i++) {
        assert(vcsc_sum2(0, i) == ivcsc_sum2(0, i));
        assert(vcsc_sum2(0, i) == denseMat_sum2(0, i));
    }

    for (int i = 0; i < vcsc_sum3.cols(); i++) {
        assert(vcsc_sum3(0, i) == ivcsc_sum3(0, i));
        assert(vcsc_sum3(0, i) == denseMat_sum3(0, i));
    }

    for (int i = 0; i < vcsc_sum4.cols(); i++) {
        assert(vcsc_sum4(0, i) == ivcsc_sum4(0, i));
        assert(vcsc_sum4(0, i) == denseMat_sum4(0, i));
    }
}

void test15(IVSparse::VCSC<TYPE, INDEX_TYPE, IVSparseMAJOR> vcsc1,
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


    Eigen::Matrix<TYPE, -1, -1> denseMat1(eigen1);
    Eigen::Matrix<TYPE, -1, -1> denseMat2(eigen2);
    Eigen::Matrix<TYPE, -1, -1> denseMat3(eigen3);
    Eigen::Matrix<TYPE, -1, -1> denseMat4(eigen4);

    Eigen::Matrix<TYPE, -1, -1> vcsc_sum1 = vcsc1.min(0);
    Eigen::Matrix<TYPE, -1, -1> ivcsc_sum1 = ivcsc1.min(0);
    Eigen::Matrix<TYPE, -1, -1> denseMat_sum1 = denseMat1.colwise().minCoeff();

    Eigen::Matrix<TYPE, -1, -1> vcsc_sum2 = vcsc2.min(0);
    Eigen::Matrix<TYPE, -1, -1> ivcsc_sum2 = ivcsc2.min(0);
    Eigen::Matrix<TYPE, -1, -1> denseMat_sum2 = denseMat2.colwise().minCoeff();


    Eigen::Matrix<TYPE, -1, -1> vcsc_sum3 = vcsc3.min(0);
    Eigen::Matrix<TYPE, -1, -1> ivcsc_sum3 = ivcsc3.min(0);
    Eigen::Matrix<TYPE, -1, -1> denseMat_sum3 = denseMat3.colwise().minCoeff();


    Eigen::Matrix<TYPE, -1, -1> vcsc_sum4 = vcsc4.min(0);
    Eigen::Matrix<TYPE, -1, -1> ivcsc_sum4 = ivcsc4.min(0);
    Eigen::Matrix<TYPE, -1, -1> denseMat_sum4 = denseMat4.colwise().minCoeff();

    for (int i = 0; i < vcsc_sum1.size(); i++) {
        assert(vcsc_sum1(i, 0) == ivcsc_sum1(i, 0));
        assert(vcsc_sum1(i, 0) == denseMat_sum1(i, 0));
    }

    for (int i = 0; i < vcsc_sum2.size(); i++) {
        assert(vcsc_sum2(i, 0) == ivcsc_sum2(i, 0));
        assert(vcsc_sum2(i, 0) == denseMat_sum2(i, 0));
    }
    for (int i = 0; i < vcsc_sum3.size(); i++) {
        assert(vcsc_sum3(i, 0) == ivcsc_sum3(i, 0));
        assert(vcsc_sum3(i, 0) == denseMat_sum3(i, 0));
    }
    for (int i = 0; i < vcsc_sum4.size(); i++) {
        assert(vcsc_sum4(i, 0) == ivcsc_sum4(i, 0));
        assert(vcsc_sum4(i, 0) == denseMat_sum4(i, 0));
    }


    vcsc_sum1 = vcsc1.max(0);
    ivcsc_sum1 = ivcsc1.max(0);
    denseMat_sum1 = denseMat1.colwise().maxCoeff();

    vcsc_sum2 = vcsc2.max(0);
    ivcsc_sum2 = ivcsc2.max(0);
    denseMat_sum2 = denseMat2.colwise().maxCoeff();


    vcsc_sum3 = vcsc3.max(0);
    ivcsc_sum3 = ivcsc3.max(0);
    denseMat_sum3 = denseMat3.colwise().maxCoeff();


    vcsc_sum4 = vcsc4.max(0);
    ivcsc_sum4 = ivcsc4.max(0);
    denseMat_sum4 = denseMat4.colwise().maxCoeff();

    for (int i = 0; i < vcsc_sum1.cols(); i++) {
        assert(vcsc_sum1(0, i) == ivcsc_sum1(0, i));
        assert(vcsc_sum1(0, i) == denseMat_sum1(0, i));
    }

    for (int i = 0; i < vcsc_sum2.cols(); i++) {
        assert(vcsc_sum2(0, i) == ivcsc_sum2(0, i));
        assert(vcsc_sum2(0, i) == denseMat_sum2(0, i));
    }

    for (int i = 0; i < vcsc_sum3.cols(); i++) {
        assert(vcsc_sum3(0, i) == ivcsc_sum3(0, i));
        assert(vcsc_sum3(0, i) == denseMat_sum3(0, i));
    }

    for (int i = 0; i < vcsc_sum4.cols(); i++) {
        assert(vcsc_sum4(0, i) == ivcsc_sum4(0, i));
        assert(vcsc_sum4(0, i) == denseMat_sum4(0, i));
    }
}

void test16(IVSparse::VCSC<TYPE, INDEX_TYPE, IVSparseMAJOR> vcsc1,
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


    Eigen::Matrix<TYPE, -1, -1> denseMat1(eigen1);
    Eigen::Matrix<TYPE, -1, -1> denseMat2(eigen2);
    Eigen::Matrix<TYPE, -1, -1> denseMat3(eigen3);
    Eigen::Matrix<TYPE, -1, -1> denseMat4(eigen4);

    TYPE vcsc_sum1 = vcsc1.min();
    TYPE ivcsc_sum1 = ivcsc1.min();
    TYPE denseMat_sum1 = denseMat1.minCoeff();

    TYPE vcsc_sum2 = vcsc2.min();
    TYPE ivcsc_sum2 = ivcsc2.min();
    TYPE denseMat_sum2 = denseMat2.minCoeff();


    TYPE vcsc_sum3 = vcsc3.min();
    TYPE ivcsc_sum3 = ivcsc3.min();
    TYPE denseMat_sum3 = denseMat3.minCoeff();


    TYPE vcsc_sum4 = vcsc4.min();
    TYPE ivcsc_sum4 = ivcsc4.min();
    TYPE denseMat_sum4 = denseMat4.minCoeff();

    assert(vcsc_sum1 == ivcsc_sum1);
    assert(vcsc_sum1 == denseMat_sum1);

    assert(vcsc_sum2 == ivcsc_sum2);
    assert(vcsc_sum2 == denseMat_sum2);

    assert(vcsc_sum3 == ivcsc_sum3);
    assert(vcsc_sum3 == denseMat_sum3);

    assert(vcsc_sum4 == ivcsc_sum4);
    assert(vcsc_sum4 == denseMat_sum4);

}

void test17(IVSparse::VCSC<TYPE, INDEX_TYPE, IVSparseMAJOR> vcsc1,
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


    Eigen::Matrix<TYPE, -1, -1> denseMat1(eigen1);
    Eigen::Matrix<TYPE, -1, -1> denseMat2(eigen2);
    Eigen::Matrix<TYPE, -1, -1> denseMat3(eigen3);
    Eigen::Matrix<TYPE, -1, -1> denseMat4(eigen4);

    TYPE vcsc_sum1 = vcsc1.max();
    TYPE ivcsc_sum1 = ivcsc1.max();
    TYPE denseMat_sum1 = denseMat1.maxCoeff();

    TYPE vcsc_sum2 = vcsc2.max();
    TYPE ivcsc_sum2 = ivcsc2.max();
    TYPE denseMat_sum2 = denseMat2.maxCoeff();

    TYPE vcsc_sum3 = vcsc3.max();
    TYPE ivcsc_sum3 = ivcsc3.max();
    TYPE denseMat_sum3 = denseMat3.maxCoeff();

    TYPE vcsc_sum4 = vcsc4.max();
    TYPE ivcsc_sum4 = ivcsc4.max();
    TYPE denseMat_sum4 = denseMat4.maxCoeff();

    assert(vcsc_sum1 == ivcsc_sum1);
    assert(vcsc_sum1 == denseMat_sum1);

    assert(vcsc_sum2 == ivcsc_sum2);
    assert(vcsc_sum2 == denseMat_sum2);

    assert(vcsc_sum3 == ivcsc_sum3);
    assert(vcsc_sum3 == denseMat_sum3);

    assert(vcsc_sum4 == ivcsc_sum4);
    assert(vcsc_sum4 == denseMat_sum4);

}