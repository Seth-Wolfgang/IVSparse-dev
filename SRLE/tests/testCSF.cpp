#include "gtest/gtest.h"
#include "SRLE/tests/testHelperFunctions.hpp"
#include "SRLE/include/CSF.hpp"
#include "SRLE/include/CSF_Lib.hpp"


/*******************************************************************************************************
 *                                                                                                     *
 * GENERAL CASE TESTS                                                                                  *
 *                                                                                                     *
 ******************************************************************************************************/

TEST(CSFTest, GeneralCaseRandomMatrix) {
    eigenMatrix<int> = getEigenMatrix<int>();
    CSF::SparseMatrix<int> a = getCSFMatrix<int>(eigenMatrix);

    eigenTotal = getEigenTotal(eigenMatrix);
    if(eigenTotal != 0) {
        ASSERT_EQ(eigenTotal, CSFTotal);
    }
    else {
        ASSERT_DEATH(CSFTotal, ".*");
    }   
}

TEST(CSFTest, UserEntersZeroRows){
    CSF::SparseMatrix a = getCSFMatrix<int>(0, 10, 10, 10);
    ASSERT_DEATH(a, ".*");
}

TEST(CSFTest, UserEntersZeroColumns){
    CSF::SparseMatrix<int> a = getCSFMatrix<int>(10, 0, 10, 10);
    ASSERT_DEATH(a, ".*");
}

/*******************************************************************************************************
 *                                                                                                     *
 * INT TESTS                                                                                           *
 *                                                                                                     *
 ******************************************************************************************************/

TEST(CSFTest, ScalarMultplicationInt){
    CSF::SparseMatrix<int> a = getCSFMatrix<int>(10, 10, 1, 10);
    CSF::SparseMatrix<int> b = a * 2;
    ASSERT_EQ(getSum(b), getSum(a));
}

TEST(CSFTest, ScalarDivisionInt){
    CSF::SparseMatrix<int> a = getCSFMatrix<int>(10, 10, 1, 10);
    CSF::SparseMatrix<int> b = a / 2;
    ASSERT_EQ(getSum(b) * 2, getSum(a));
}

TEST(CSFTest, ScalarMultiplicationByZeroInt){
    CSF::SparseMatrix<int> a = getCSFMatrix<int>(10, 10, 1, 10);
    CSF::SparseMatrix<int> b = a * 0;
    ASSERT_DEATH(getSum(b), ".*");
}

TEST(CSFTest, ScalarDivisionByZeroInt){
    CSF::SparseMatrix<int> a = getCSFMatrix<int>(10, 10, 1, 10);
    ASSERT_DEATH(a / 0, ".*");
}

TEST(CSFTest, MatrixAdditionWithInt){
    CSF::SparseMatrix<int> a = getCSFMatrix<int>(10, 10, 1, 10);
    CSF::SparseMatrix<int> b = getCSFMatrix<int>(10, 10, 1, 10);

    CSF::SparseMatrix<int> c = a + b;
    ASSERT_EQ(getSum(c), getSum(a) + getSum(b));
}

TEST(CSFTest, MatrixSubtractionWithInt){
    CSF::SparseMatrix<int> a = getCSFMatrix<int>(10, 10, 1, 10);
    CSF::SparseMatrix<int> b = getCSFMatrix<int>(10, 10, 1, 10);
    CSF::SparseMatrix<int> c = a - b;
    ASSERT_EQ(getSum(c), getSum(a) - getSum(b));
}

TEST(CSFTest, MatrixAdditionWithZeroInt){
    CSF::SparseMatrix<int> a = getCSFMatrix<int>(10, 10, 1, 10);
    CSF::SparseMatrix<int> b = a + 0;
    ASSERT_EQ(getSum(b), getSum(a));
}

TEST(CSFTest, MatrixSubtractionWithZeroInt){
    CSF::SparseMatrix<int> a = getCSFMatrix<int>(10, 10, 1, 10);
    CSF::SparseMatrix<int> b = a - 0;
    ASSERT_EQ(getSum(b), getSum(a));
}

/*******************************************************************************************************
 *                                                                                                     *
 * FLOAT TESTS                                                                                         *
 *                                                                                                     *
 ******************************************************************************************************/

TEST(CSFTest, ScalarMultplicationFloat){
    CSF::SparseMatrix<float> a = getCSFMatrix<float>(10, 10, 1, 10);
    CSF::SparseMatrix<float> b = a * 2.0;
    ASSERT_EQ(getSum(b), getSum(a));
}

TEST(CSFTest, ScalarDivisionFloat){
    CSF::SparseMatrix<float> a = getCSFMatrix<float>(10, 10, 1, 10);
    CSF::SparseMatrix<float> b = a / 2.0;
    ASSERT_EQ(getSum(b) * 2, getSum(a));
}

TEST(CSFTest, ScalarMultiplicationByZeroFloat){
    CSF::SparseMatrix<float> a = getCSFMatrix<float>(10, 10, 1, 10);
    CSF::SparseMatrix<float> b = a * 0;
    ASSERT_DEATH(getSum(b), ".*");
}

TEST(CSFTest, ScalarDivisionByZeroFloat){
    CSF::SparseMatrix<float> a = getCSFMatrix<float>(10, 10, 1, 10);
    ASSERT_DEATH(a / 0, ".*");
}

TEST(CSFTest, MatrixAdditionWithFloat){
    CSF::SparseMatrix<float> a = getCSFMatrix<float>(10, 10, 1, 10);
    CSF::SparseMatrix<float> b = getCSFMatrix<float>(10, 10, 1, 10);

    CSF::SparseMatrix<float> c = a + b;
    ASSERT_EQ(getSum(c), getSum(a) + getSum(b));
}

TEST(CSFTest, MatrixSubtractionWithFloat){
    CSF::SparseMatrix<float> a = getCSFMatrix<float>(10, 10, 1, 10);
    CSF::SparseMatrix<float> b = getCSFMatrix<float>(10, 10, 1, 10);
    CSF::SparseMatrix<float> c = a - b;
    ASSERT_EQ(getSum(c), getSum(a) - getSum(b));
}

TEST(CSFTest, MatrixAdditionWithZeroFloat){
    CSF::SparseMatrix<float> a = getCSFMatrix<int>(10, 10, 1, 10);
    CSF::SparseMatrix<float> b = a + 0;
    ASSERT_EQ(getSum(b), getSum(a));
}

TEST(CSFTest, MatrixSubtractionWithZeroFloat){
    CSF::SparseMatrix<float> a = getCSFMatrix<float>(10, 10, 1, 10);
    CSF::SparseMatrix<float> b = a - 0;
    ASSERT_EQ(getSum(b), getSum(a));
}





