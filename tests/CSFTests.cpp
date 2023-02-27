#include "gtest/gtest.h"
#include "testHelperFunctions.hpp"


namespace {

    template <class T>
    CSF::SparseMatrix CreateCSFSparseMatrix();

    template<>
    CSF::SparseMatrix CreateCSFSparseMatrix<int>() {
        return CSF::SparseMatrix<int>();
    }

    template<>
    CSF::SparseMatrix CreateCSFSparseMatrix<uint64_t>() {
        return CSF::SparseMatrix<uint64_t>();
    }

    template<>
    CSF::SparseMatrix CreateCSFSparseMatrix<double>() {
        return CSF::SparseMatrix<double>();
    }



    template <class T>
    class CSFTestGeneral : public ::testing::Test {
    protected:
        CSFTestGeneral(int numRows, int numCols, int sparsity, int seed) {
            csf = generateEigenMatrix<T>(100, 100, 20, 10);
            eigen = getCSFMatrix(b);
        }

        ~CSFTestGeneral() override {
            delete csf;
            delete eigen;
        }
        // Class members declared here can be used by all tests in the test suite
        // for Foo.
        CSF::SparseMatrix csf;
        Eigen::SparseMatrix<T> eigen;
    };


    using testing::Types;
    template<typename T>
    class CSFTest : public ::testing::Test {};

    typedef Types<int, uint64_t, double> myTypes;
    TYPED_TEST_CASE(CSFTestGeneral, myTypes);

    /*******************************************************************************************************
     *                                                                                                     *
     * CONSTRUCTOR TESTS                                                                                   *
     *                                                                                                     *
     ******************************************************************************************************/

    //If this does not work, then all test fail
    TYPED_TEST(CSFTestGeneral, GeneralCaseRandomMatrix) {
        uint64_t eigenTotal = getEigenTotal(this->eigen);
        if (eigenTotal != 0) {
            uint64_t csfTotal = getSum(this->a);
            ASSERT_EQ(eigenTotal, csfTotal);
        }
        else {
            ASSERT_DEATH(getSum(this->a), ".*");
        }
    }


    // TYPED_TEST(CSFTestGeneral, GeneralCaseWithHighSparsity) {
    //     Eigen::SparseMatrix<T> eigenMatrix = generateEigenMatrix<T>(100, 100, 50, 100);
    //     CSF::SparseMatrix a = getCSFMatrix(eigenMatrix);

    //     uint64_t eigenTotal = getEigenTotal(eigenMatrix);
    //     if (eigenTotal != 0) {
    //         uint64_t csfTotal = getSum(a);
    //         ASSERT_EQ(eigenTotal, csfTotal);
    //     }
    //     else {
    //         ASSERT_DEATH(getSumNoReturn(a), ".*");
    //     }
    // }

    // TYPED_TEST(CSFTestGeneral, GeneralCaseWithDenseMatrix) {
    //     Eigen::SparseMatrix<T> eigenMatrix = generateEigenMatrix(100, 100, 2, 100);
    //     CSF::SparseMatrix<T> a = getCSFMatrix(eigenMatrix);

    //     uint64_t eigenTotal = getEigenTotal(eigenMatrix);
    //     if (eigenTotal != 0) {
    //         uint64_t csfTotal = getSum(a);
    //         ASSERT_EQ(eigenTotal, csfTotal);
    //     }
    //     else {
    //         ASSERT_DEATH(getSumNoReturn(a), ".*");
    //     }
    // }

    /*******************************************************************************************************
     *                                                                                                     *
     * GARBAGE INPUT TESTS                                                                                 *
     *                                                                                                     *
     ******************************************************************************************************/


    // TYPED_TEST(CSFTest, UserEntersZeroRows) {
    //     ASSERT_DEATH(CSF::SparseMatrix a = getCSFMatrix(0, 10, 10, 10), ".*");
    // }


    // TYPED_TEST(CSFTest, UserEntersZeroColumns) {
    //     CSF::SparseMatrix a = getCSFMatrix(10, 0, 10, 10);
    //     ASSERT_DEATH(a, ".*");
    // }

    /*******************************************************************************************************
     *                                                                                                     *
     * ARITHMETIC TESTS                                                                                    *
     *                                                                                                     *
     ******************************************************************************************************/

    // TYPED_TEST(CSFTest, ScalarMultplication) {
    //     CSF::SparseMatrix a = getCSFMatrix<T>(10, 10, 1, 10);
    //     CSF::SparseMatrix b = a * 2.0;
    //     ASSERT_EQ(getSum<T>(b), getSum<T>(a));
    // }

    // TYPED_TEST(CSFTest, ScalarDivision) {
    //     CSF::SparseMatrix a = getCSFMatrix<T>(10, 10, 1, 10);
    //     CSF::SparseMatrix b = a / 2.0;
    //     ASSERT_EQ(getSum<T>(b) * 2, getSum<T>(a));
    // }

    // TYPED_TEST(CSFTest, ScalarMultiplicationByZero) {
    //     CSF::SparseMatrix a = getCSFMatrix<T>(10, 10, 1, 10);
    //     CSF::SparseMatrix b = a * 0;
    //     ASSERT_DEATH(getSum<T>(b), ".*");
    // }

    // TYPED_TEST(CSFTest, ScalarDivisionByZero) {
    //     CSF::SparseMatrix a = getCSFMatrix<T>(10, 10, 1, 10);
    //     ASSERT_DEATH(a / 0, ".*");
    // }

    // TYPED_TEST(CSFTest, MatrixAddition) {
    //     CSF::SparseMatrix a = getCSFMatrix<T>(10, 10, 1, 10);
    //     CSF::SparseMatrix b = getCSFMatrix<T>(10, 10, 1, 10);

    //     CSF::SparseMatrix c = a + b;
    //     ASSERT_EQ(getSum<T>(c), getSum<T>(a) + getSum<T>(b));
    // }

    // TYPED_TEST(CSFTest, MatrixSubtraction) {
    //     CSF::SparseMatrix a = getCSFMatrix<T>(10, 10, 1, 10);
    //     CSF::SparseMatrix b = getCSFMatrix<T>(10, 10, 1, 10);
    //     CSF::SparseMatrix c = a - b;
    //     ASSERT_EQ(getSum<T>(c), getSum<T>(a) - getSum<T>(b));
    // }

    // TYPED_TEST(CSFTest, MatrixAdditionWithZero) {
    //     CSF::SparseMatrix a = getCSFMatrix<T>(10, 10, 1, 10);
    //     CSF::SparseMatrix b = a + 0;
    //     ASSERT_EQ(getSum<T>(b), getSum<T>(a));
    // }

    // TYPED_TEST(CSFTest, MatrixSubtractionWithZero) {
    //     CSF::SparseMatrix a = getCSFMatrix<T>(10, 10, 1, 10);
    //     CSF::SparseMatrix b = a - 0;
    //     ASSERT_EQ(getSum<T>(b), getSum<T>(a));
    // }

    /*******************************************************************************************************
     *                                                                                                     *
     * COMPRESSION CONVERSION TESTS                                                                        *
     *                                                                                                     *
     ******************************************************************************************************/

    // TYPED_TEST(CSFTest, CSF1toCSF2) {
    //     CSF::SparseMatrix a = getCSFMatrix<T>(10, 10, 1, 10);
    //     CSF::SparseMatrix b = a.toCSF<2>();
    //     ASSERT_EQ(getSum<T>(a), getSum<T>(b));
    // }

    // TYPED_TEST(CSFTest, CSF1toCSF3) {
    //     CSF::SparseMatrix a = getCSFMatrix<T>(10, 10, 1, 10);
    //     CSF::SparseMatrix b = a.toCSF<3>();
    //     ASSERT_EQ(getSum<T>(a), getSum<T>(b));
    // }

    // TYPED_TEST(CSFTest, CSF2toCSF1) {
    //     CSF::SparseMatrix a = getCSFMatrix<T>(10, 10, 1, 10);
    //     CSF::SparseMatrix b = a.toCSF<1>();
    //     ASSERT_EQ(getSum<T>(a), getSum<T>(b));
    // }

    // TYPED_TEST(CSFTest, CSF2toCSF3) {
    //     CSF::SparseMatrix a = getCSFMatrix<T>(10, 10, 1, 10);
    //     CSF::SparseMatrix b = a.toCSF<3>();
    //     ASSERT_EQ(getSum<T>(a), getSum<T>(b));
    // }

    // TYPED_TEST(CSFTest, CSF3toCSF1) {
    //     CSF::SparseMatrix a = getCSFMatrix<T>(10, 10, 1, 10);
    //     CSF::SparseMatrix b = a.toCSF<1>();
    //     ASSERT_EQ(getSum<T>(a), getSum<T>(b));
    // }

    // TYPED_TEST(CSFTest, CSF3toCSF2) {
    //     CSF::SparseMatrix a = getCSFMatrix<T>(10, 10, 1, 10);
    //     CSF::SparseMatrix b = a.toCSF<2>();
    //     ASSERT_EQ(getSum<T>(a), getSum<T>(b));
    // }

    REGISTER_TYPED_TEST_SUITE_P(CSFTestGeneral, 
                                // UserEntersZeroRows, 
                                // UserEntersZeroColumns, 
                                // ScalarMultplication,
                                // ScalarDivision, 
                                // ScalarMultiplicationByZero, 
                                // ScalarDivisionByZero,
                                // MatrixAddition, 
                                // MatrixSubtraction, 
                                // MatrixAdditionWithZero,
                                // MatrixSubtractionWithZero
                                // , 
                                // CSF1toCSF2, CSF1toCSF3, CSF2toCSF1,
                                // CSF2toCSF3, CSF3toCSF1, CSF3toCSF2
                                );

    INSTANTIATE_TYPED_TEST_SUITE_P(My, CSFTestGeneral, MyTypes);

}
