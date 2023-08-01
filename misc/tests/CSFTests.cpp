#include "gtest/gtest.h"
#include "testHelperFunctions.hpp"
#include <tuple>
#include <type_traits>

#define NUM_OF_ITERATIONS 100

/**
 * @brief Test fixture for the IVSparse::SparseMatrix class and its associated functions
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

namespace
{

    template <typename T>
    class CSFTest : public testing::Test
    {
    };

    typedef ::testing::Types<
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
        std::tuple<double, uint64_t, int>>
        Implementations;

    TYPED_TEST_SUITE(CSFTest, Implementations);

    /*******************************************************************************************************
     *                                                                                                     *
     * IVSparse COMPRESSION TESTS                                                                               *
     *                                                                                                     *
     ******************************************************************************************************/

    TYPED_TEST(CSFTest, SameDimensions)
    {

        //     // These do not work when put into the template params
        //     // typename std::tuple_element<0, decltype(TypeParam())>::type A;
        //     // typename std::tuple_element<1, decltype(TypeParam())>::type B;
        //     // typename std::tuple_element<2, decltype(TypeParam())>::type C;

        //     // typename std::tuple_element<0, TypeParam>::type A;
        //     // using type = typename std::get<0>(TypeParam)::type;
        //     // typename TypeParam::type B;

        //     // Solution from
        //     // https://stackoverflow.com/questions/29382157/how-to-test-c-template-class-with-multiple-template-parameters-using-gtest
        Eigen::SparseMatrix<typename std::tuple_element<0, decltype(TypeParam())>::type> eigen = generateEigenMatrix<typename std::tuple_element<0, decltype(TypeParam())>::type>(100, 100, 1, 10);

        // Compression level 2
        IVSparse::SparseMatrix<
            typename std::tuple_element<0, decltype(TypeParam())>::type,
            typename std::tuple_element<1, decltype(TypeParam())>::type,
            2>
            csf2(eigen);

        // Compression level 3
        IVSparse::SparseMatrix<
            typename std::tuple_element<0, decltype(TypeParam())>::type,
            typename std::tuple_element<1, decltype(TypeParam())>::type,
            3>
            csf3(eigen);

        ASSERT_EQ(csf2.rows(), eigen.rows());
        ASSERT_EQ(csf2.cols(), eigen.cols());
        ASSERT_EQ(csf2.nonZeros(), eigen.nonZeros());

        ASSERT_EQ(csf3.rows(), eigen.rows());
        ASSERT_EQ(csf3.cols(), eigen.cols());
        ASSERT_EQ(csf3.nonZeros(), eigen.nonZeros());
    }

    TYPED_TEST(CSFTest, GeneralCaseRandomDenseMatrixSum)
    {
        // Solution from
        // https://stackoverflow.com/questions/29382157/how-to-test-c-template-class-with-multiple-template-parameters-using-gtest
        uint64_t seed = rand() % 10000 + 1;
        typename std::tuple_element<0, decltype(TypeParam())>::type csfTotal2;
        typename std::tuple_element<0, decltype(TypeParam())>::type csfTotal3;
        typename std::tuple_element<0, decltype(TypeParam())>::type eigenTotal;
        Eigen::SparseMatrix<typename std::tuple_element<0, decltype(TypeParam())>::type> eigen = generateEigenMatrix<typename std::tuple_element<0, decltype(TypeParam())>::type>(100, 100, 1, seed);

        // For a thorough test, we will use 1000 random matrices
        for (int i = 0; i < NUM_OF_ITERATIONS; i++)
        {
            seed = rand() % 10000 + 1;

            // For the case of a zero matrix, we will skip this and look at one in a future test
            while (getSum<typename std::tuple_element<0, decltype(TypeParam())>::type>(eigen) == 0)
            {
                seed = rand() % 10000 + 1;
                eigen = generateEigenMatrix<typename std::tuple_element<0, decltype(TypeParam())>::type>(100, 100, 1, seed);
            }

            // Compression level 2
            IVSparse::SparseMatrix<
                typename std::tuple_element<0, decltype(TypeParam())>::type,
                typename std::tuple_element<1, decltype(TypeParam())>::type,
                2>
                csf2(eigen);

            // Compression level 3
            IVSparse::SparseMatrix<
                typename std::tuple_element<0, decltype(TypeParam())>::type,
                typename std::tuple_element<1, decltype(TypeParam())>::type,
                3>
                csf3(eigen);

            // Get the totals
            csfTotal2 = csf2.sum();
            csfTotal3 = csf3.sum();
            eigenTotal = getSum<typename std::tuple_element<0, decltype(TypeParam())>::type>(eigen);

            // If a singular total is off, the test will fail
            ASSERT_EQ(csfTotal2, eigenTotal);
            ASSERT_EQ(csfTotal3, eigenTotal);
        }
    }

    TYPED_TEST(CSFTest, GeneralCaseRandomSparseMatrixSum)
    {
        // Solution from
        // https://stackoverflow.com/questions/29382157/how-to-test-c-template-class-with-multiple-template-parameters-using-gtest
        uint64_t seed = rand() % 100 + 1;
        typename std::tuple_element<0, decltype(TypeParam())>::type csfTotal2;
        typename std::tuple_element<0, decltype(TypeParam())>::type csfTotal3;
        typename std::tuple_element<0, decltype(TypeParam())>::type eigenTotal;
        Eigen::SparseMatrix<typename std::tuple_element<0, decltype(TypeParam())>::type> eigen = generateEigenMatrix<typename std::tuple_element<0, decltype(TypeParam())>::type>(100, 100, 20, seed);
        eigen.makeCompressed();
        // For a thorough test, we will use 1000 random matrices
        for (int i = 0; i < NUM_OF_ITERATIONS; i++)
        {
            seed = rand();

            // For the case of a zero matrix, we will skip this and look at one in a future test
            eigen = generateEigenMatrix<typename std::tuple_element<0, decltype(TypeParam())>::type>(100, 100, 20, seed);
            eigen.makeCompressed();

            // //Compression level 2
            IVSparse::SparseMatrix<
                typename std::tuple_element<0, decltype(TypeParam())>::type,
                typename std::tuple_element<1, decltype(TypeParam())>::type,
                2>
                csf2(eigen);

            // Compression level 3
            IVSparse::SparseMatrix<
                typename std::tuple_element<0, decltype(TypeParam())>::type,
                typename std::tuple_element<1, decltype(TypeParam())>::type,
                3>
                csf3(eigen);
            // Get the totals
            csfTotal2 = csf2.sum();
            csfTotal3 = getSumCSF<typename std::tuple_element<0, decltype(TypeParam())>::type, typename std::tuple_element<1, decltype(TypeParam())>::type, 3>(csf3);
            eigenTotal = getSum<typename std::tuple_element<0, decltype(TypeParam())>::type>(eigen);

            // If a singular total is off, the test will fail
            ASSERT_EQ(csfTotal3, eigenTotal);
            ASSERT_EQ(csfTotal2, eigenTotal);
        }
    }

    TYPED_TEST(CSFTest, DeepCopyIsSameAsOriginal)
    {
        // Solution from
        // https://stackoverflow.com/questions/29382157/how-to-test-c-template-class-with-multiple-template-parameters-using-gtest
        Eigen::SparseMatrix<typename std::tuple_element<0, decltype(TypeParam())>::type> eigen = generateEigenMatrix<typename std::tuple_element<0, decltype(TypeParam())>::type>(100, 100, 20, 10);

        // Compression level 2
        IVSparse::SparseMatrix<
            typename std::tuple_element<0, decltype(TypeParam())>::type,
            typename std::tuple_element<1, decltype(TypeParam())>::type,
            2>
            csf2(eigen);

        // Compression level 3
        IVSparse::SparseMatrix<
            typename std::tuple_element<0, decltype(TypeParam())>::type,
            typename std::tuple_element<1, decltype(TypeParam())>::type,
            3>
            csf3(eigen);

        // Copy of compression level 2
        IVSparse::SparseMatrix<
            typename std::tuple_element<0, decltype(TypeParam())>::type,
            typename std::tuple_element<1, decltype(TypeParam())>::type,
            2>
            csfCopy2(csf2);

        // Copy of compression level 3
        IVSparse::SparseMatrix<
            typename std::tuple_element<0, decltype(TypeParam())>::type,
            typename std::tuple_element<1, decltype(TypeParam())>::type,
            3>
            csfCopy3(csf3);

        ASSERT_EQ(csf2.rows(), csfCopy2.rows());
        ASSERT_EQ(csf2.cols(), csfCopy2.cols());
        ASSERT_EQ(csf2.nonZeros(), csfCopy2.nonZeros());

        ASSERT_EQ(csf3.rows(), csfCopy3.rows());
        ASSERT_EQ(csf3.cols(), csfCopy3.cols());
        ASSERT_EQ(csf3.nonZeros(), csfCopy3.nonZeros());

        typename std::tuple_element<0, decltype(TypeParam())>::type CSFSum2 = csf2.sum();
        typename std::tuple_element<0, decltype(TypeParam())>::type CSFCopySum2 = csfCopy2.sum();

        typename std::tuple_element<0, decltype(TypeParam())>::type CSFSum3 = csf3.sum();
        typename std::tuple_element<0, decltype(TypeParam())>::type CSFCopySum3 = csfCopy3.sum();

        ASSERT_EQ(CSFSum2, CSFCopySum2);
        ASSERT_EQ(CSFSum3, CSFCopySum3);
    }

    TYPED_TEST(CSFTest, LargeMatrixColumnSum)
    {
        // Solution from
        // https://stackoverflow.com/questions/29382157/how-to-test-c-template-class-with-multiple-template-parameters-using-gtest
        uint64_t seed = rand() % 10000 + 1;
        typename std::tuple_element<0, decltype(TypeParam())>::type csfTotal2;
        typename std::tuple_element<0, decltype(TypeParam())>::type csfTotal3;
        typename std::tuple_element<0, decltype(TypeParam())>::type eigenTotal = 0;
        Eigen::SparseMatrix<typename std::tuple_element<0, decltype(TypeParam())>::type> eigen = generateEigenMatrix<typename std::tuple_element<0, decltype(TypeParam())>::type>(getLargeNumber<typename std::tuple_element<1, decltype(TypeParam())>::type>(),
                                                                                                                                                                                  getLargeNumber<typename std::tuple_element<1, decltype(TypeParam())>::type>(), 1, seed);
        // For a thorough test, we will use 1000 random matrices
        for (int i = 0; i < 1; i++)
        {
            seed = rand() % 10000 + 1;

            // For the case of a zero matrix, we will skip this and look at one in a future test
            while (eigen.sum() == eigenTotal)
            {
                seed = rand() % 10000 + 1;
                std::cout << "Zero matrix generated, regenerating" << std::endl;
                eigen = generateEigenMatrix<typename std::tuple_element<0, decltype(TypeParam())>::type>(getLargeNumber<typename std::tuple_element<1, decltype(TypeParam())>::type>(),
                                                                                                         getLargeNumber<typename std::tuple_element<1, decltype(TypeParam())>::type>(), 1, seed);
            }

            IVSparse::SparseMatrix<
                typename std::tuple_element<0, decltype(TypeParam())>::type,
                typename std::tuple_element<1, decltype(TypeParam())>::type,
                2>
                csf2(eigen);

            // Compression level 3
            IVSparse::SparseMatrix<
                typename std::tuple_element<0, decltype(TypeParam())>::type,
                typename std::tuple_element<1, decltype(TypeParam())>::type,
                3>
                csf3(eigen);
            // Get the totals
            csfTotal2 = csf2.sum();
            csfTotal3 = csf3.sum();
            eigenTotal = eigen.sum();

            // If a singular total is off, the test will fail
            ASSERT_EQ(csfTotal2, eigenTotal);
            ASSERT_EQ(csfTotal3, eigenTotal);
        }
    }

    TYPED_TEST(CSFTest, 1RowColumnSum)
    {
        // Solution from
        // https://stackoverflow.com/questions/29382157/how-to-test-c-template-class-with-multiple-template-parameters-using-gtest
        uint64_t seed = rand() % 10000 + 1;
        typename std::tuple_element<0, decltype(TypeParam())>::type csfTotal2;
        typename std::tuple_element<0, decltype(TypeParam())>::type csfTotal3;
        typename std::tuple_element<0, decltype(TypeParam())>::type eigenTotal;
        Eigen::SparseMatrix<typename std::tuple_element<0, decltype(TypeParam())>::type> eigen = generateEigenMatrix<typename std::tuple_element<0, decltype(TypeParam())>::type>(1, 100, 1, seed);

        // For a thorough test, we will use 1000 random matrices
        for (int i = 0; i < NUM_OF_ITERATIONS; i++)
        {
            seed = rand() % 10000 + 1;

            // For the case of a zero matrix, we will skip this and look at one in a future test
            while (eigen.sum() == 0)
            {
                seed = rand() % 10000 + 1;
                eigen = generateEigenMatrix<typename std::tuple_element<0, decltype(TypeParam())>::type>(1, 100, 1, seed);
            }

            // Compression level 2
            IVSparse::SparseMatrix<
                typename std::tuple_element<0, decltype(TypeParam())>::type,
                typename std::tuple_element<1, decltype(TypeParam())>::type,
                2>
                csf2(eigen);

            // Compression level 3
            IVSparse::SparseMatrix<
                typename std::tuple_element<0, decltype(TypeParam())>::type,
                typename std::tuple_element<1, decltype(TypeParam())>::type,
                3>
                csf3(eigen);

            // Get the totals
            csfTotal2 = csf2.sum();
            csfTotal3 = csf3.sum();
            eigenTotal = eigen.sum();

            // If a singular total is off, the test will fail
            ASSERT_EQ(csfTotal2, eigenTotal);
            ASSERT_EQ(csfTotal3, eigenTotal);
        }
    }

    TYPED_TEST(CSFTest, 1ColumnSum)
    {
        // Solution from
        // https://stackoverflow.com/questions/29382157/how-to-test-c-template-class-with-multiple-template-parameters-using-gtest
        uint64_t seed = rand() % 10000 + 1;
        typename std::tuple_element<0, decltype(TypeParam())>::type csfTotal1;
        typename std::tuple_element<0, decltype(TypeParam())>::type csfTotal2;
        typename std::tuple_element<0, decltype(TypeParam())>::type csfTotal3;
        typename std::tuple_element<0, decltype(TypeParam())>::type eigenTotal;
        Eigen::SparseMatrix<typename std::tuple_element<0, decltype(TypeParam())>::type> eigen = generateEigenMatrix<typename std::tuple_element<0, decltype(TypeParam())>::type>(100, 1, 1, seed);

        // For a thorough test, we will use 1000 random matrices
        for (int i = 0; i < NUM_OF_ITERATIONS; i++)
        {
            seed = rand() % 10000 + 1;

            // For the case of a zero matrix, we will skip this and look at one in a future test
            while (eigen.sum() == 0)
            {
                seed = rand() % 10000 + 1;
                eigen = generateEigenMatrix<typename std::tuple_element<0, decltype(TypeParam())>::type>(100, 1, 1, seed);
            }

            // Compression level 2
            IVSparse::SparseMatrix<
                typename std::tuple_element<0, decltype(TypeParam())>::type,
                typename std::tuple_element<1, decltype(TypeParam())>::type,
                2>
                csf2(eigen);

            // Compression level 3
            IVSparse::SparseMatrix<
                typename std::tuple_element<0, decltype(TypeParam())>::type,
                typename std::tuple_element<1, decltype(TypeParam())>::type,
                3>
                csf3(eigen);

            // Get the totals
            csfTotal2 = csf2.sum();
            csfTotal3 = csf3.sum();
            eigenTotal = eigen.sum();

            // If a singular total is off, the test will fail
            ASSERT_EQ(csfTotal2, eigenTotal);
            ASSERT_EQ(csfTotal3, eigenTotal);
        }
    }

    /*******************************************************************************************************
     *                                                                                                     *
     * GARBAGE INPUT TESTS                                                                                 *
     *                                                                                                     *
     ******************************************************************************************************/

    //  TYPED_TEST(CSFTest, UserEntersZeroRows) {
    //  ASSERT_DEATH(IVSparse::SparseMatrix a = getCSFMatrix(0, 10, 10, 10), ".*");
    //  }

    // TYPED_TEST(CSFTest, UserEntersZeroColumns) {
    //     IVSparse::SparseMatrix a = getCSFMatrix(10, 0, 10, 10);
    //     ASSERT_DEATH(a, ".*");
    // }

    /******************************************************************************************************
     *                                                                                                     *
     * ARITHMETIC TESTS                                                                                    *
     *                                                                                                     *
     ******************************************************************************************************/

    TYPED_TEST(CSFTest, ScalarMultplication)
    {
        typename std::tuple_element<0, decltype(TypeParam())>::type csfTotal2;
        typename std::tuple_element<0, decltype(TypeParam())>::type csfTotal3;
        typename std::tuple_element<0, decltype(TypeParam())>::type originalTotal2;
        typename std::tuple_element<0, decltype(TypeParam())>::type originalTotal3;

        int seed = rand();

        Eigen::SparseMatrix<typename std::tuple_element<0, decltype(TypeParam())>::type> eigen = generateEigenMatrix<typename std::tuple_element<0, decltype(TypeParam())>::type>(100, 100, 1, seed);

        // For the case of a zero matrix, we will skip this and look at one in a future test
        while (getSum<typename std::tuple_element<0, decltype(TypeParam())>::type>(eigen) == 0)
        {
            seed = rand();
            eigen = generateEigenMatrix<typename std::tuple_element<0, decltype(TypeParam())>::type>(100, 100, 1, seed);
        }

        // Compression level 2
        IVSparse::SparseMatrix<
            typename std::tuple_element<0, decltype(TypeParam())>::type,
            typename std::tuple_element<1, decltype(TypeParam())>::type,
            2>
            csf2(eigen);

        // Compression level 3
        IVSparse::SparseMatrix<
            typename std::tuple_element<0, decltype(TypeParam())>::type,
            typename std::tuple_element<1, decltype(TypeParam())>::type,
            3>
            csf3(eigen);

        originalTotal2 = (csf2);
        originalTotal3 = csf3.sum();

        csf2 * 2.0;
        csf3 * 2.0;

        csfTotal2 = (csf2);
        csfTotal3 = csf3.sum();

        ASSERT_EQ(originalTotal2 * 2, csfTotal2) << "Seed: " << seed;
        ASSERT_EQ(originalTotal3 * 2, csfTotal3) << "Seed: " << seed;
    }

    // TYPED_TEST(CSFTest, ScalarDivision) {
    //     IVSparse::SparseMatrix a = getCSFMatrix<T>(10, 10, 1, 10);
    //     IVSparse::SparseMatrix b = a / 2.0;
    //     ASSERT_EQ(getSum<T>(b) * 2, getSum<T>(a));
    // }

    // TYPED_TEST(CSFTest, ScalarMultiplicationByZero) {
    //     IVSparse::SparseMatrix a = getCSFMatrix<T>(10, 10, 1, 10);
    //     IVSparse::SparseMatrix b = a * 0;
    //     ASSERT_EQ(getSum<T>(b), 0);
    // }

    // TYPED_TEST(CSFTest, ScalarDivisionByZero) {
    //     IVSparse::SparseMatrix a = getCSFMatrix<T>(10, 10, 1, 10);
    //     ASSERT_DEATH(a / 0, ".*");
    // }

    /*******************************************************************************************************
     *                                                                                                     *
     * COMPRESSION CONVERSION TESTS                                                                        *
     *                                                                                                     *
     ******************************************************************************************************/

    // TYPED_TEST(CSFTest, CSCtoCSF2) {
    //     IVSparse::SparseMatrix a = getCSFMatrix<T>(10, 10, 1, 10);
    //     IVSparse::SparseMatrix b = a.toCSF<2>();
    //     ASSERT_EQ(getSum<T>(a), getSum<T>(b));
    // }

    // TYPED_TEST(CSFTest, CSCtoCSF3) {
    //     IVSparse::SparseMatrix a = getCSFMatrix<T>(10, 10, 1, 10);
    //     IVSparse::SparseMatrix b = a.toCSF<3>();
    //     ASSERT_EQ(getSum<T>(a), getSum<T>(b));
    // }

    // TYPED_TEST(CSFTest, CSF2toCSC) {
    //     IVSparse::SparseMatrix a = getCSFMatrix<T>(10, 10, 1, 10);
    //     IVSparse::SparseMatrix b = a.toCSF<1>();
    //     ASSERT_EQ(getSum<T>(a), getSum<T>(b));
    // }

    // TYPED_TEST(CSFTest, CSF2toCSF3) {
    //     IVSparse::SparseMatrix a = getCSFMatrix<T>(10, 10, 1, 10);
    //     IVSparse::SparseMatrix b = a.toCSF<3>();
    //     ASSERT_EQ(getSum<T>(a), getSum<T>(b));
    // }

    // TYPED_TEST(CSFTest, CSF3toCSC) {
    //     IVSparse::SparseMatrix a = getCSFMatrix<T>(10, 10, 1, 10);
    //     IVSparse::SparseMatrix b = a.toCSF<1>();
    //     ASSERT_EQ(getSum<T>(a), getSum<T>(b));
    // }

    // TYPED_TEST(CSFTest, CSF3toCSF2) {
    //     IVSparse::SparseMatrix a = getCSFMatrix<T>(10, 10, 1, 10);
    //     IVSparse::SparseMatrix b = a.toCSF<2>();
    //     ASSERT_EQ(getSum<T>(a), getSum<T>(b));
    // }
}