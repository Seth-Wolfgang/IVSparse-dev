    #include <gtest/gtest.h>
    #include "CSFTests.cpp"
    

    GTEST_API_ int main(int argc, char** argv) {
        ::testing::InitGoogleTest(&argc, argv);
        return RUN_ALL_TESTS();
    }