#include "gtest/gtest.h"
#include "testHelperFunctions.hpp"
#include <tuple>
#include <type_traits>

namespace {



    template <typename T>
    class CSFTest: public testing::Test {};
    // protected:

    //     CSFTest() {
    //         eigen = generateEigenMatrix<std::get<0>(TypeParam)>(100, 100, 20, 10);
    //         csf = CSF::SparseMatrix<std::get<0>(TypeParam), std::get<1>(TypeParam), std::get<2>(TypeParam)>(eigen);
    //     }

    //     virtual ~CSFTest() override {
    //         delete &csf;
    //         delete &eigen;
    //     }
    //     CSF::SparseMatrix<T, T, 3> csf;
    //     Eigen::SparseMatrix<T> eigen;
    // };

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

     //If this does not work, then all test fail
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

    TYPED_TEST(CSFTest, GeneralCaseRandomMatrixSum) {
        // Solution from
        // https://stackoverflow.com/questions/29382157/how-to-test-c-template-class-with-multiple-template-parameters-using-gtest
        Eigen::SparseMatrix<typename std::tuple_element<0, decltype(TypeParam())>::type> eigen = generateEigenMatrix<typename std::tuple_element<0, decltype(TypeParam())>::type>(100, 100, 20, 10);

        CSF::SparseMatrix<
            typename std::tuple_element<0, decltype(TypeParam())>::type,
            typename std::tuple_element<1, decltype(TypeParam())>::type,
            3> csf(eigen);


        uint64_t eigenTotal = getSum<typename std::tuple_element<0, decltype(TypeParam())>::type>(eigen);
        if (eigenTotal != 0) {
            uint64_t csfTotal = getSum<typename std::tuple_element<0, decltype(TypeParam())>::type, typename std::tuple_element<1, decltype(TypeParam())>::type, 3>(csf);
            ASSERT_EQ(eigenTotal, csfTotal);
        }
        else {
            ASSERT_TRUE(true);
            //Assert death in all cases except for a seg fault
        //     ASSERT_DEATH({
        //         uint64_t = getSum<typename std::tuple_element<0, decltype(TypeParam())>::type, typename std::tuple_element<1, decltype(TypeParam())>::type, 3>(csf);
        //         }, ".*");
        // }
        }
    }

    TYPED_TEST(CSFTest, GeneralCaseSparseMatrixSum) {
        // Solution from
        // https://stackoverflow.com/questions/29382157/how-to-test-c-template-class-with-multiple-template-parameters-using-gtest
        Eigen::SparseMatrix<typename std::tuple_element<0, decltype(TypeParam())>::type> eigen = generateEigenMatrix<typename std::tuple_element<0, decltype(TypeParam())>::type>(100, 100, 20, 10);

        CSF::SparseMatrix<
            typename std::tuple_element<0, decltype(TypeParam())>::type,
            typename std::tuple_element<1, decltype(TypeParam())>::type,
            3> csf(eigen);


        uint64_t eigenTotal = getSum<typename std::tuple_element<0, decltype(TypeParam())>::type>(eigen);
        if (eigenTotal != 0) {
            uint64_t csfTotal = getSum<typename std::tuple_element<0, decltype(TypeParam())>::type, typename std::tuple_element<1, decltype(TypeParam())>::type, 3>(csf);
            ASSERT_EQ(eigenTotal, csfTotal);
        }
        else {
            ASSERT_TRUE(true);
            //Assert death in all cases except for a seg fault
        //     ASSERT_DEATH({
        //         uint64_t = getSum<typename std::tuple_element<0, decltype(TypeParam())>::type, typename std::tuple_element<1, decltype(TypeParam())>::type, 3>(csf);
        //         }, ".*");
        // }
        }
    }

    TYPED_TEST(CSFTest, GeneralCaseDenseMatrixSum) {
        // Solution from
        // https://stackoverflow.com/questions/29382157/how-to-test-c-template-class-with-multiple-template-parameters-using-gtest
        Eigen::SparseMatrix<typename std::tuple_element<0, decltype(TypeParam())>::type> eigen = generateEigenMatrix<typename std::tuple_element<0, decltype(TypeParam())>::type>(100, 100, 1, 10);

        CSF::SparseMatrix<
            typename std::tuple_element<0, decltype(TypeParam())>::type,
            typename std::tuple_element<1, decltype(TypeParam())>::type,
            3> csf(eigen);


        uint64_t eigenTotal = getSum<typename std::tuple_element<0, decltype(TypeParam())>::type>(eigen);
        if (eigenTotal != 0) {
            uint64_t csfTotal = getSum<typename std::tuple_element<0, decltype(TypeParam())>::type, typename std::tuple_element<1, decltype(TypeParam())>::type, 3>(csf);
            ASSERT_EQ(eigenTotal, csfTotal);
        }
        else {
            ASSERT_TRUE(true);
            //Assert death in all cases except for a seg fault
        //     ASSERT_DEATH({
        //         uint64_t = getSum<typename std::tuple_element<0, decltype(TypeParam())>::type, typename std::tuple_element<1, decltype(TypeParam())>::type, 3>(csf);
        //         }, ".*");
        // }
        }
    }

    TYPED_TEST(CSFTest, DeepCopyIsSameAsOriginal){
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

//     REGISTER_TYPED_TEST_SUITE_P(CSFTest,
//         SameDimensions,
//         GeneralCaseRandomMatrixSum
//         // UserEntersZeroRows,
//         // UserEntersZeroColumns,
//         // ScalarMultplication,
//         // ScalarDivision,
//         // ScalarMultiplicationByZero,
//         // ScalarDivisionByZero,
//         // CSF1toCSF2,
//         // CSF1toCSF3,
//         // CSF2toCSF1,
//         // CSF2toCSF3,
//         // CSF3toCSF1,
//         // CSF3toCSF2
//     );
}


