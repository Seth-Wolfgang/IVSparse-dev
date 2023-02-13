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

    uint64_t eigenTotal = getEigenTotal(eigenMatrix);
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
 //     ASSERT_EQ(getSum(b), getSum(a));
 // }

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

    float eigenTotal = getEigenTotal(eigenMatrix);
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

// TEST(CSFTest, MatrixAdditionWithFloat){
//     CSF::SparseMatrix<float> a = getCSFMatrix<float>(10, 10, 1, 10);
//     CSF::SparseMatrix<float> b = getCSFMatrix<float>(10, 10, 1, 10);

//     CSF::SparseMatrix<float> c = a + b;
//     ASSERT_EQ(getSum(c), getSum(a) + getSum(b));
// }

// TEST(CSFTest, MatrixSubtractionWithFloat){
//     CSF::SparseMatrix<float> a = getCSFMatrix<float>(10, 10, 1, 10);
//     CSF::SparseMatrix<float> b = getCSFMatrix<float>(10, 10, 1, 10);
//     CSF::SparseMatrix<float> c = a - b;
//     ASSERT_EQ(getSum(c), getSum(a) - getSum(b));
// }

// TEST(CSFTest, MatrixAdditionWithZeroFloat){
//     CSF::SparseMatrix<float> a = getCSFMatrix<int>(10, 10, 1, 10);
//     CSF::SparseMatrix<float> b = a + 0;
//     ASSERT_EQ(getSum(b), getSum(a));
// }

// TEST(CSFTest, MatrixSubtractionWithZeroFloat){
//     CSF::SparseMatrix<float> a = getCSFMatrix<float>(10, 10, 1, 10);
//     CSF::SparseMatrix<float> b = a - 0;
//     ASSERT_EQ(getSum(b), getSum(a));
// }


