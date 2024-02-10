#include <chrono>
#include <iostream>

#include "../IVSparse/SparseMatrix"
// #include "misc/matrix_creator.cpp"


#define TYPE double
#define IVSparseMAJOR 1 // 1 = col major, 0 = row major
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
            Eigen::SparseMatrix<TYPE, EIGENMAJOR> eigen4);


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
            Eigen::SparseMatrix<TYPE, EIGENMAJOR> eigen4);

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
            Eigen::SparseMatrix<TYPE, EIGENMAJOR> eigen4);

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
            Eigen::SparseMatrix<TYPE, EIGENMAJOR> eigen4);

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
            Eigen::SparseMatrix<TYPE, EIGENMAJOR> eigen4);

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
            Eigen::SparseMatrix<TYPE, EIGENMAJOR> eigen4);

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
            Eigen::SparseMatrix<TYPE, EIGENMAJOR> eigen4);

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
            Eigen::SparseMatrix<TYPE, EIGENMAJOR> eigen4);