#include "gtest/gtest.h"
#include "testHelperFunctions.hpp"
#include <tuple>
#include <type_traits>

/**
 * @brief Test fixture for the CSF::SparseMatrix class and its associated functions
 *
 */

 // test for high and low sparsity on matrix/vector multiplication -DONE
 // test the deep copy constructor -> check sizes, sums, etc
 // check scalar multiplication across types, check * 0, * -1, * 1, * 2, * 0.5, * 10000
 // check vector multiplication across types, check * 0, * -1, * 1, * 2, * 0.5, * 10000 and random vectors compared to eigen
 // check each constructor
 // check that I can grab each column of a matrix as well as invalid columns. negatives should start from the back -> like python
 // check that I can access a random element of a matrix -> negatives should start from back like python
 // check that I can convert a matrix
 // check splicig matrices -> like python... arr[1:3] 
 // Test a matrix in which all values are unique

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
    > Implementations;


    TYPED_TEST_SUITE(CSFTest, Implementations);

    /*******************************************************************************************************
     *                                                                                                     *
     * CSF COMPRESSION LEVEL 3 TESTS                                                                       *
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

        //Compression level 1
        CSF::SparseMatrix<
            typename std::tuple_element<0, decltype(TypeParam())>::type,
            typename std::tuple_element<1, decltype(TypeParam())>::type,
            1
        > csf1(eigen);

        //Compression level 2
        CSF::SparseMatrix<
            typename std::tuple_element<0, decltype(TypeParam())>::type,
            typename std::tuple_element<1, decltype(TypeParam())>::type,
            2
        > csf2(eigen);

        //Compression level 3
        CSF::SparseMatrix<
            typename std::tuple_element<0, decltype(TypeParam())>::type,
            typename std::tuple_element<1, decltype(TypeParam())>::type,
            3
        > csf3(eigen);

        ASSERT_EQ(csf1.rows(), eigen.rows());
        ASSERT_EQ(csf1.cols(), eigen.cols());
        ASSERT_EQ(csf1.nonzeros(), eigen.nonZeros());

        ASSERT_EQ(csf2.rows(), eigen.rows());
        ASSERT_EQ(csf2.cols(), eigen.cols());
        ASSERT_EQ(csf2.nonzeros(), eigen.nonZeros());

        ASSERT_EQ(csf3.rows(), eigen.rows());
        ASSERT_EQ(csf3.cols(), eigen.cols());
        ASSERT_EQ(csf3.nonzeros(), eigen.nonZeros());
    }

    TYPED_TEST(CSFTest, GeneralCaseRandomDenseMatrixSum) {
        // Solution from
        // https://stackoverflow.com/questions/29382157/how-to-test-c-template-class-with-multiple-template-parameters-using-gtest
        uint64_t seed = rand() % 10000 + 1;
        typename std::tuple_element<0, decltype(TypeParam())>::type csfTotal1;
        typename std::tuple_element<0, decltype(TypeParam())>::type csfTotal2;
        typename std::tuple_element<0, decltype(TypeParam())>::type csfTotal3;
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

            // Compression level 1
            CSF::SparseMatrix<
                typename std::tuple_element<0, decltype(TypeParam())>::type,
                typename std::tuple_element<1, decltype(TypeParam())>::type,
                1
            > csf1(eigen);

            //Compression level 2
            CSF::SparseMatrix<
                typename std::tuple_element<0, decltype(TypeParam())>::type,
                typename std::tuple_element<1, decltype(TypeParam())>::type,
                2
            > csf2(eigen);

            //Compression level 3
            CSF::SparseMatrix<
                typename std::tuple_element<0, decltype(TypeParam())>::type,
                typename std::tuple_element<1, decltype(TypeParam())>::type,
                3
            > csf3(eigen);

            //Get the totals
            // csfTotal1 = getSum<typename std::tuple_element<0, decltype(TypeParam())>::type, typename std::tuple_element<1, decltype(TypeParam())>::type, 1>(csf1);
            csfTotal2 = getSum<typename std::tuple_element<0, decltype(TypeParam())>::type, typename std::tuple_element<1, decltype(TypeParam())>::type, 2>(csf2);
            csfTotal3 = getSum<typename std::tuple_element<0, decltype(TypeParam())>::type, typename std::tuple_element<1, decltype(TypeParam())>::type, 3>(csf3);
            eigenTotal = getSum<typename std::tuple_element<0, decltype(TypeParam())>::type>(eigen);

            // If a singular total is off, the test will fail
            // ASSERT_EQ(csfTotal1, eigenTotal);
            ASSERT_EQ(csfTotal2, eigenTotal);
            ASSERT_EQ(csfTotal3, eigenTotal);
        }
    }


    TYPED_TEST(CSFTest, GeneralCaseRandomSparseMatrixSum) {
        // Solution from
        // https://stackoverflow.com/questions/29382157/how-to-test-c-template-class-with-multiple-template-parameters-using-gtest
        uint64_t seed = rand() % 10000 + 1;
        // typename std::tuple_element<0, decltype(TypeParam())>::type csfTotal1;
        // typename std::tuple_element<0, decltype(TypeParam())>::type csfTotal2;
        typename std::tuple_element<0, decltype(TypeParam())>::type csfTotal3;
        typename std::tuple_element<0, decltype(TypeParam())>::type eigenTotal;
        Eigen::SparseMatrix<typename std::tuple_element<0, decltype(TypeParam())>::type> eigen = generateEigenMatrix<typename std::tuple_element<0, decltype(TypeParam())>::type>(100, 100, 50, seed);

        //For a thorough test, we will use 1000 random matrices
        for (int i = 0; i < 1000; i++) {
            seed = rand() % 10000 + 1;

            //For the case of a zero matrix, we will skip this and look at one in a future test
            while (getSum<typename std::tuple_element<0, decltype(TypeParam())>::type>(eigen) == 0) {
                seed = rand() % 10000 + 1;
                eigen = generateEigenMatrix<typename std::tuple_element<0, decltype(TypeParam())>::type>(100, 100, 20, seed);
            }

            // // Compression level 1
            // CSF::SparseMatrix<
            //     typename std::tuple_element<0, decltype(TypeParam())>::type,
            //     typename std::tuple_element<1, decltype(TypeParam())>::type,
            //     1
            // > csf1(eigen);

            // //Compression level 2
            // CSF::SparseMatrix<
            //     typename std::tuple_element<0, decltype(TypeParam())>::type,
            //     typename std::tuple_element<1, decltype(TypeParam())>::type,
            //     2
            // > csf2(eigen);

            //Compression level 3
            CSF::SparseMatrix<
                typename std::tuple_element<0, decltype(TypeParam())>::type,
                typename std::tuple_element<1, decltype(TypeParam())>::type,
                3
            > csf3(eigen);

            //Get the totals
            // csfTotal1 = getSum<typename std::tuple_element<0, decltype(TypeParam())>::type, typename std::tuple_element<1, decltype(TypeParam())>::type, 1>(csf1);
            // csfTotal2 = getSum<typename std::tuple_element<0, decltype(TypeParam())>::type, typename std::tuple_element<1, decltype(TypeParam())>::type, 2>(csf2);
            csfTotal3 = getSum<typename std::tuple_element<0, decltype(TypeParam())>::type, typename std::tuple_element<1, decltype(TypeParam())>::type, 3>(csf3);

            eigenTotal = getSum<typename std::tuple_element<0, decltype(TypeParam())>::type>(eigen);

            // If a singular total is off, the test will fail
            ASSERT_EQ(csfTotal3, eigenTotal);
        }
    }

    TYPED_TEST(CSFTest, DeepCopyIsSameAsOriginal) {
        // Solution from
        // https://stackoverflow.com/questions/29382157/how-to-test-c-template-class-with-multiple-template-parameters-using-gtest
        Eigen::SparseMatrix<typename std::tuple_element<0, decltype(TypeParam())>::type> eigen = generateEigenMatrix<typename std::tuple_element<0, decltype(TypeParam())>::type>(100, 100, 20, 10);

        // Compression level 1
        // CSF::SparseMatrix<
        //     typename std::tuple_element<0, decltype(TypeParam())>::type,
        //     typename std::tuple_element<1, decltype(TypeParam())>::type,
        //     1> csf1(eigen);

        // //Compression level 2
        // CSF::SparseMatrix<
        //     typename std::tuple_element<0, decltype(TypeParam())>::type,
        //     typename std::tuple_element<1, decltype(TypeParam())>::type,
        //     2> csf2(eigen);

        //Compression level 3
        CSF::SparseMatrix<
            typename std::tuple_element<0, decltype(TypeParam())>::type,
            typename std::tuple_element<1, decltype(TypeParam())>::type,
            3> csf3(eigen);

        //Copy of compression level 1
        // CSF::SparseMatrix<
        //     typename std::tuple_element<0, decltype(TypeParam())>::type,
        //     typename std::tuple_element<1, decltype(TypeParam())>::type,
        //     1> csfCopy1(csf1);

        // //Copy of compression level 2
        // CSF::SparseMatrix<
        //     typename std::tuple_element<0, decltype(TypeParam())>::type,
        //     typename std::tuple_element<1, decltype(TypeParam())>::type,
        //     2> csfCopy2(csf2);

        //Copy of compression level 3
        CSF::SparseMatrix<
            typename std::tuple_element<0, decltype(TypeParam())>::type,
            typename std::tuple_element<1, decltype(TypeParam())>::type,
            3> csfCopy3(csf3);

        //Check that the copies are the same dimensions
        // ASSERT_EQ(csf1.rows(), csfCopy1.rows());
        // ASSERT_EQ(csf1.cols(), csfCopy1.cols());
        // ASSERT_EQ(csf1.nonzeros(), csfCopy1.nonzeros());

        // ASSERT_EQ(csf2.rows(), csfCopy2.rows());
        // ASSERT_EQ(csf2.cols(), csfCopy2.cols());
        // ASSERT_EQ(csf2.nonzeros(), csfCopy2.nonzeros());

        ASSERT_EQ(csf3.rows(), csfCopy3.rows());
        ASSERT_EQ(csf3.cols(), csfCopy3.cols());
        ASSERT_EQ(csf3.nonzeros(), csfCopy3.nonzeros());

        // typename std::tuple_element<0, decltype(TypeParam())>::type CSFSum1 = getSum<typename std::tuple_element<0, decltype(TypeParam())>::type, typename std::tuple_element<1, decltype(TypeParam())>::type, 1>(csf1);
        // typename std::tuple_element<0, decltype(TypeParam())>::type CSFCopySum1 = getSum<typename std::tuple_element<0, decltype(TypeParam())>::type, typename std::tuple_element<1, decltype(TypeParam())>::type, 1>(csfCopy1);

        // typename std::tuple_element<0, decltype(TypeParam())>::type CSFSum2 = getSum<typename std::tuple_element<0, decltype(TypeParam())>::type, typename std::tuple_element<1, decltype(TypeParam())>::type, 2>(csf2);
        // typename std::tuple_element<0, decltype(TypeParam())>::type CSFCopySum2 = getSum<typename std::tuple_element<0, decltype(TypeParam())>::type, typename std::tuple_element<1, decltype(TypeParam())>::type, 2>(csfCopy2);

        typename std::tuple_element<0, decltype(TypeParam())>::type CSFSum3 = getSum<typename std::tuple_element<0, decltype(TypeParam())>::type, typename std::tuple_element<1, decltype(TypeParam())>::type, 3>(csf3);
        typename std::tuple_element<0, decltype(TypeParam())>::type CSFCopySum3 = getSum<typename std::tuple_element<0, decltype(TypeParam())>::type, typename std::tuple_element<1, decltype(TypeParam())>::type, 3>(csfCopy3);

        // ASSERT_EQ(CSFSum1, CSFCopySum1);
        // ASSERT_EQ(CSFSum2, CSFCopySum2);
        ASSERT_EQ(CSFSum3, CSFCopySum3);
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

    /******************************************************************************************************
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
    //     ASSERT_EQ(getSum<T>(b), 0);
    // }

    // TYPED_TEST(CSFTest, ScalarDivisionByZero) {
    //     CSF::SparseMatrix a = getCSFMatrix<T>(10, 10, 1, 10);
    //     ASSERT_DEATH(a / 0, ".*");
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


