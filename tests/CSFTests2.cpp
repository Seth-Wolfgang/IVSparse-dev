#include "gtest/gtest.h"
#include "testHelperFunctions.hpp"



/*******************************************************************************************************
 *                                                                                                     *
 * GENERAL CASE TESTS                                                                                  *
 *                                                                                                     *
 ******************************************************************************************************/

TEST(CSFTest, GeneralCaseRandomMatrix) {
    Eigen::SparseMatrix<int> eigenMatrix = generateEigenMatrix<int>(10, 10, 1, 10);
    CSF::SparseMatrix a = getCSFMatrix<int>(eigenMatrix);

    uint64_t eigenTotal = getSum(eigenMatrix);
    if (eigenTotal != 0) {
        ASSERT_EQ(eigenTotal, getSum<int>(a));
    }
    else {

        ASSERT_DEATH(getSum<int>(a), ".*");
    }
}

TEST(CSFTest, UserEntersZeroRows) {
    ASSERT_DEATH(getCSFMatrix<int>(0, 10, 10, 10), ".*");
}

TEST(CSFTest, UserEntersZeroColumns) {
    ASSERT_DEATH(getCSFMatrix<int>(0, 10, 10, 10), ".*");
}

/*******************************************************************************************************
 *                                                                                                     *
 * INT TESTS                                                                                           *
 *                                                                                                     *
 ******************************************************************************************************/

 // TEST(CSFTest, ScalarMultplicationInt){
 //     CSF::SparseMatrix<int> a = getCSFMatrix<int>(10, 10, 1, 10);
 //     CSF::SparseMatrix<int> b = a * 2;
 //     ASSERT_EQ(getSum(b), 2 * getSum(a));
 // }

 // may not work for integers
 // TEST(CSFTest, ScalarDivisionInt){
 //     CSF::SparseMatrix<int> a = getCSFMatrix<int>(10, 10, 1, 10);
 //     CSF::SparseMatrix<int> b = a / 2;
 //     ASSERT_EQ(getSum(b) * 2, getSum(a));
 // }

 // TEST(CSFTest, ScalarMultiplicationByZeroInt){
 //     CSF::SparseMatrix<int> a = getCSFMatrix<int>(10, 10, 1, 10);
 //     CSF::SparseMatrix<int> b = a * 0;
 //     ASSERT_DEATH(getSum(b), ".*");
 // }

 // TEST(CSFTest, ScalarDivisionByZeroInt){
 //     CSF::SparseMatrix<int> a = getCSFMatrix<int>(10, 10, 1, 10);
 //     ASSERT_DEATH(a / 0, ".*");
 // }

 // TEST(CSFTest, MatrixAdditionWithInt){
 //     CSF::SparseMatrix<int> a = getCSFMatrix<int>(10, 10, 1, 10);
 //     CSF::SparseMatrix<int> b = getCSFMatrix<int>(10, 10, 1, 10);

 //     CSF::SparseMatrix<int> c = a + b;
 //     ASSERT_EQ(getSum(c), getSum(a) + getSum(b));
 // }

 // TEST(CSFTest, MatrixSubtractionWithInt){
 //     CSF::SparseMatrix<int> a = getCSFMatrix<int>(10, 10, 1, 10);
 //     CSF::SparseMatrix<int> b = getCSFMatrix<int>(10, 10, 1, 10);
 //     CSF::SparseMatrix<int> c = a - b;
 //     ASSERT_EQ(getSum(c), getSum(a) - getSum(b));
 // }

 // TEST(CSFTest, MatrixAdditionWithZeroInt){
 //     CSF::SparseMatrix<int> a = getCSFMatrix<int>(10, 10, 1, 10);
 //     CSF::SparseMatrix<int> b = a + 0;
 //     ASSERT_EQ(getSum(b), getSum(a));
 // }

 // TEST(CSFTest, MatrixSubtractionWithZeroInt){
 //     CSF::SparseMatrix<int> a = getCSFMatrix<int>(10, 10, 1, 10);
 //     CSF::SparseMatrix<int> b = a - 0;
 //     ASSERT_EQ(getSum(b), getSum(a));
 // }

 /*******************************************************************************************************
  *                                                                                                     *
  * FLOAT TESTS                                                                                         *
  *                                                                                                     *
  ******************************************************************************************************/

TEST(CSFTest, GeneralCaseRandomMatrixFloat) {
    Eigen::SparseMatrix<float> eigenMatrix = generateEigenMatrix<float>(10, 10, 1, 10);
    CSF::SparseMatrix a = getCSFMatrix<float>(eigenMatrix);

    float eigenTotal = getSum(eigenMatrix);
    if (eigenTotal != 0) {
        ASSERT_EQ(eigenTotal, getSum<float>(a));
    }
    else {

        ASSERT_DEATH(getSum<float>(a), ".*");
    }
}

TEST(CSFTest, UserEntersZeroRowsFloat) {
    ASSERT_DEATH(getCSFMatrix<float>(0, 10, 10, 10), ".*");
}

TEST(CSFTest, UserEntersZeroColumnsFloat) {
    ASSERT_DEATH(getCSFMatrix<float>(0, 10, 10, 10), ".*");
}

// TEST(CSFTest, ScalarMultplicationFloat){
//     CSF::SparseMatrix<float> a = getCSFMatrix<float>(10, 10, 1, 10);
//     CSF::SparseMatrix<float> b = a * 2.0;
//     ASSERT_EQ(getSum(b), getSum(a));
// }

// TEST(CSFTest, ScalarDivisionFloat){
//     CSF::SparseMatrix<float> a = getCSFMatrix<float>(10, 10, 1, 10);
//     CSF::SparseMatrix<float> b = a / 2.0;
//     ASSERT_EQ(getSum(b) * 2, getSum(a));
// }

// TEST(CSFTest, ScalarMultiplicationByZeroFloat){
//     CSF::SparseMatrix<float> a = getCSFMatrix<float>(10, 10, 1, 10);
//     CSF::SparseMatrix<float> b = a * 0;
//     ASSERT_DEATH(getSum(b), ".*");
// }

// TEST(CSFTest, ScalarDivisionByZeroFloat){
//     CSF::SparseMatrix<float> a = getCSFMatrix<float>(10, 10, 1, 10);
//     ASSERT_DEATH(a / 0, ".*");
// }



 /*******************************************************************************************************
  *                                                                                                     *
  * CONVERSION TESTS                                                                                    *
  *                                                                                                     *
  ******************************************************************************************************/

    // TEST(CSFTest, CSF1toCSF2) {
    //     CSF::SparseMatrix a = getCSFMatrix<T>(10, 10, 1, 10);
    //     CSF::SparseMatrix b = a.toCSF<2>();
    //     ASSERT_EQ(getSum<T>(a), getSum<T>(b));
    // }

    // TEST(CSFTest, CSF1toCSF3) {
    //     CSF::SparseMatrix a = getCSFMatrix<T>(10, 10, 1, 10);
    //     CSF::SparseMatrix b = a.toCSF<3>();
    //     ASSERT_EQ(getSum<T>(a), getSum<T>(b));
    // }

    // TEST(CSFTest, CSF2toCSF1) {
    //     CSF::SparseMatrix a = getCSFMatrix<T>(10, 10, 1, 10);
    //     CSF::SparseMatrix b = a.toCSF<1>();
    //     ASSERT_EQ(getSum<T>(a), getSum<T>(b));
    // }

    // TEST(CSFTest, CSF2toCSF3) {
    //     CSF::SparseMatrix a = getCSFMatrix<T>(10, 10, 1, 10);
    //     CSF::SparseMatrix b = a.toCSF<3>();
    //     ASSERT_EQ(getSum<T>(a), getSum<T>(b));
    // }

    // TEST(CSFTest, CSF3toCSF1) {
    //     CSF::SparseMatrix a = getCSFMatrix<T>(10, 10, 1, 10);
    //     CSF::SparseMatrix b = a.toCSF<1>();
    //     ASSERT_EQ(getSum<T>(a), getSum<T>(b));
    // }

    // TEST(CSFTest, CSF3toCSF2) {
    //     CSF::SparseMatrix a = getCSFMatrix<T>(10, 10, 1, 10);
    //     CSF::SparseMatrix b = a.toCSF<2>();
    //     ASSERT_EQ(getSum<T>(a), getSum<T>(b));
    // }


 /*******************************************************************************************************
  *                                                                                                     *
  * CONVERSION TESTS                                                                                    *
  *                                                                                                     *
  ******************************************************************************************************/



