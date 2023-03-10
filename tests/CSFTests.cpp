#include "gtest/gtest.h"
#include "testHelperFunctions.hpp"
#include <tuple>
#include <type_traits>

/**
 * @brief Test fixture for the CSF::SparseMatrix class and its associated functions
 *
 */

namespace {

    template <typename T>
    class CSFTest: public testing::Test {};

    typedef ::testing::Types <
        std::tuple<int, int, int>,
        std::tuple<uint8_t, uint8_t, int>,
        std::tuple<uint16_t, uint16_t, int>,
        std::tuple<uint32_t, uint32_t, int>,
        std::tuple<uint64_t, uint64_t, int>,
        std::tuple<float, uint8_t, int>,
        std::tuple<float, uint16_t, int>,
        std::tuple<float, uint32_t, int>,
        std::tuple<float, uint64_t, int>,
        std::tuple<double, uint8_t, int>,
        std::tuple<double, uint16_t, int>,
        std::tuple<double, uint32_t, int>,
        std::tuple<double, uint64_t, int>
    > ImplementationsINT;


    TYPED_TEST_SUITE(CSFTest, ImplementationsINT);

    /*******************************************************************************************************
     *                                                                                                     *
     * CONSTRUCTOR TESTS                                                                                   *
     *                                                                                                     *
     ******************************************************************************************************/

    TYPED_TEST(CSFTest, SameDimensions) {

        // These do not work when put into the template params
        // typename std::tuple_element<0, decltype(TypeParam())>::type A;
        // typename std::tuple_element<1, decltype(TypeParam())>::type B;
        // typename std::tuple_element<2, decltype(TypeParam())>::type C;

        // typename std::tuple_element<0, TypeParam>::type A;
        // using type = typename std::get<0>(TypeParam)::type;
        // typename TypeParam::type B;

        // Solution from
        // https://stackoverflow.com/questions/29382157/how-to-test-c-template-class-with-multiple-template-parameters-using-gtest
        Eigen::SparseMatrix<typename std::tuple_element<0, decltype(TypeParam())>::type> eigen = generateEigenMatrix<typename std::tuple_element<0, decltype(TypeParam())>::type>(100, 100, 1, 10);


        CSF::SparseMatrix<
            typename std::tuple_element<0, decltype(TypeParam())>::type,
            typename std::tuple_element<1, decltype(TypeParam())>::type,
            3
        > csf(eigen);

        ASSERT_EQ(csf.rows(), eigen.rows());
        ASSERT_EQ(csf.cols(), eigen.cols());
        ASSERT_EQ(csf.nonzeros(), eigen.nonZeros());
    }

    TYPED_TEST(CSFTest, GeneralCaseRandomDenseMatrixSum) {
        // Solution from
        // https://stackoverflow.com/questions/29382157/how-to-test-c-template-class-with-multiple-template-parameters-using-gtest
        uint64_t seed = rand() % 10000 + 1;
        int failCounter = 0;
        typename std::tuple_element<0, decltype(TypeParam())>::type csfTotal;
        typename std::tuple_element<0, decltype(TypeParam())>::type eigenTotal;

        Eigen::SparseMatrix<typename std::tuple_element<0, decltype(TypeParam())>::type> eigen = generateEigenMatrix<typename std::tuple_element<0, decltype(TypeParam())>::type>(100, 100, 1, seed);

        //For a thorough test, we will use 1000 random matrices
        for (int i = 0; i < 1000; i++) {
            seed = rand() % 10000 + 1;

            //For the case of a zero matrix, we will skip this and look at one in a future test
            while (getSum<typename std::tuple_element<0, decltype(TypeParam())>::type>(eigen) == 0) {
                seed = rand() % 10000 + 1;
                eigen = generateEigenMatrix<typename std::tuple_element<0, decltype(TypeParam())>::type>(100, 100, 20, seed);
            }

            //Construct the CSF matrix
            CSF::SparseMatrix<
                typename std::tuple_element<0, decltype(TypeParam())>::type,
                typename std::tuple_element<1, decltype(TypeParam())>::type,
                3> csf(eigen);

            //Get the totals
            csfTotal = getSum<typename std::tuple_element<0, decltype(TypeParam())>::type, typename std::tuple_element<1, decltype(TypeParam())>::type, 3>(csf);
            eigenTotal = getSum<typename std::tuple_element<0, decltype(TypeParam())>::type>(eigen);

            // If a singular total is off, the test will fail
            if (csfTotal != eigenTotal) {
                failCounter++;
            }
        }
        ASSERT_EQ(failCounter, 0);
    }


    TYPED_TEST(CSFTest, GeneralCaseRandomSparseMatrixSum) {
        // Solution from
        // https://stackoverflow.com/questions/29382157/how-to-test-c-template-class-with-multiple-template-parameters-using-gtest
        uint64_t seed = rand() % 10000 + 1;
        int failCounter = 0;
        typename std::tuple_element<0, decltype(TypeParam())>::type csfTotal;
        typename std::tuple_element<0, decltype(TypeParam())>::type eigenTotal;

        Eigen::SparseMatrix<typename std::tuple_element<0, decltype(TypeParam())>::type> eigen = generateEigenMatrix<typename std::tuple_element<0, decltype(TypeParam())>::type>(100, 100, 50, seed);


        for (int i = 0; i < 1000; i++) {
            seed = rand() % 10000 + 1;
            while (getSum<typename std::tuple_element<0, decltype(TypeParam())>::type>(eigen) == 0) {
                seed = rand() % 10000 + 1;
                eigen = generateEigenMatrix<typename std::tuple_element<0, decltype(TypeParam())>::type>(100, 100, 20, seed);
            }
            CSF::SparseMatrix<
                typename std::tuple_element<0, decltype(TypeParam())>::type,
                typename std::tuple_element<1, decltype(TypeParam())>::type,
                3> csf(eigen);
            csfTotal = getSum<typename std::tuple_element<0, decltype(TypeParam())>::type, typename std::tuple_element<1, decltype(TypeParam())>::type, 3>(csf);
            eigenTotal = getSum<typename std::tuple_element<0, decltype(TypeParam())>::type>(eigen);
            if (csfTotal != eigenTotal) {
                failCounter++;
            }
        }
        ASSERT_EQ(failCounter, 0);
    }

    TYPED_TEST(CSFTest, DeepCopyIsSameAsOriginal) {
        // Solution from
        // https://stackoverflow.com/questions/29382157/how-to-test-c-template-class-with-multiple-template-parameters-using-gtest
        Eigen::SparseMatrix<typename std::tuple_element<0, decltype(TypeParam())>::type> eigen = generateEigenMatrix<typename std::tuple_element<0, decltype(TypeParam())>::type>(100, 100, 20, 10);

        CSF::SparseMatrix<
            typename std::tuple_element<0, decltype(TypeParam())>::type,
            typename std::tuple_element<1, decltype(TypeParam())>::type,
            3> csf(eigen);

        CSF::SparseMatrix<
            typename std::tuple_element<0, decltype(TypeParam())>::type,
            typename std::tuple_element<1, decltype(TypeParam())>::type,
            3> csfCopy(csf);

        ASSERT_EQ(csf.rows(), csfCopy.rows());
        ASSERT_EQ(csf.cols(), csfCopy.cols());
        ASSERT_EQ(csf.nonzeros(), csfCopy.nonzeros());

        typename std::tuple_element<0, decltype(TypeParam())>::type CSFSum = getSum<typename std::tuple_element<0, decltype(TypeParam())>::type, typename std::tuple_element<1, decltype(TypeParam())>::type, 3>(csf);
        typename std::tuple_element<0, decltype(TypeParam())>::type CSFCopySum = getSum<typename std::tuple_element<0, decltype(TypeParam())>::type, typename std::tuple_element<1, decltype(TypeParam())>::type, 3>(csfCopy);

        ASSERT_EQ(CSFSum, CSFCopySum);
    }

    /*******************************************************************************************************
     *                                                                                                     *
     * GARBAGE INPUT TESTS                                                                                 *
     *                                                                                                     *
     ******************************************************************************************************/


     //  TYPED_TEST(CSFTest, UserEntersZeroRows) {
         //  ASSERT_DEATH(CSF::SparseMatrix a = getCSFMatrix(0, 10, 10, 10), ".*");
     //  }


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
}


