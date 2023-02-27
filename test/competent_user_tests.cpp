#include "../CSF/SparseMatrix"
#include "../misc/matrix_creator.cpp"
#include <iostream>
#include <cstdlib>

/*
Things to test/get working:
1. Decompressor
4. CSF vectors
6. << operator
8. redundancy checker
*/

int main (int argc, char** argv) {

    // ---- Generate Random Eigen Matrices ---- //

    // Create a random matrix
    int numRows = 50;
    int numCols = 50;
    int sparsity = 4;
    uint64_t seed = 1956553944;
    //uint64_t seed = rand();

    // generating a large random eigen sparse
    Eigen::SparseMatrix<int> myMatrix_e(numRows, numCols);
    myMatrix_e.reserve(Eigen::VectorXi::Constant(numRows, numCols));
    myMatrix_e = generateMatrix<int>(numRows, numCols, sparsity, seed);
    myMatrix_e.makeCompressed();

    // create a random eigen matrix of type double
    Eigen::SparseMatrix<double> myMatrix2_e(numRows, numCols);
    myMatrix2_e.reserve(Eigen::VectorXi::Constant(numRows, numCols));
    myMatrix2_e = generateMatrix<double>(numRows, numCols, sparsity, seed);
    myMatrix2_e.makeCompressed();

    // create a random eigen matrix of type float
    Eigen::SparseMatrix<float> myMatrix3_e(numRows, numCols);
    myMatrix3_e.reserve(Eigen::VectorXi::Constant(numRows, numCols));
    myMatrix3_e = generateMatrix<float>(numRows, numCols, sparsity, seed);
    myMatrix3_e.makeCompressed();

    // create a random eigen matrix of type uint64_t
    Eigen::SparseMatrix<uint64_t> myMatrix4_e(numRows, numCols);
    myMatrix4_e.reserve(Eigen::VectorXi::Constant(numRows, numCols));
    myMatrix4_e = generateMatrix<uint64_t>(numRows, numCols, sparsity, seed);
    myMatrix4_e.makeCompressed();

    // ---- Create CSF Matrices from above Eigen Matrices ---- // 

    // Create integer CSF matrices of compression levels 1, 2, and 3 (competent user)
    CSF::SparseMatrix<int, int, 1> myMatrix1(myMatrix_e);
    CSF::SparseMatrix<int, int, 2> myMatrix2(myMatrix_e);
    CSF::SparseMatrix<int, int, 3> myMatrix3(myMatrix_e);
    CSF::SparseMatrix<int, uint64_t, 1> myMatrix4(myMatrix_e);
    CSF::SparseMatrix<int, uint64_t, 2> myMatrix5(myMatrix_e);
    CSF::SparseMatrix<int, uint64_t, 3> myMatrix6(myMatrix_e);
    CSF::SparseMatrix<int> myMatrix7(myMatrix_e);
    CSF::SparseMatrix<int, short, 2> myMatrix8(myMatrix_e);
    CSF::SparseMatrix<int, long, 3> myMatrix9(myMatrix_e);
    //!CSF::SparseMatrix<int, uint8_t, 3> myMatrix10(myMatrix2);

    // Create double CSF matrices of compression levels 1, 2, and 3 (competent user)
    CSF::SparseMatrix<double, int, 1> myMatrix11(myMatrix2_e);
    CSF::SparseMatrix<double, int, 2> myMatrix12(myMatrix2_e);
    CSF::SparseMatrix<double, int, 3> myMatrix13(myMatrix2_e);
    CSF::SparseMatrix<double, uint64_t, 1> myMatrix14(myMatrix2_e);
    CSF::SparseMatrix<double, uint64_t, 2> myMatrix15(myMatrix2_e);
    CSF::SparseMatrix<double> myMatrix16(myMatrix2_e);
    CSF::SparseMatrix<double, short, 2> myMatrix17(myMatrix2_e);
    CSF::SparseMatrix<double, long, 3> myMatrix18(myMatrix2_e);
    //!CSF::SparseMatrix<double, uint8_t, 3> myMatrix19(myMatrix2);

    // Create float CSF matrices of compression levels 1, 2, and 3 (competent user)
    CSF::SparseMatrix<float, int, 1> myMatrix20(myMatrix3_e);
    CSF::SparseMatrix<float, int, 2> myMatrix21(myMatrix3_e);
    CSF::SparseMatrix<float, int, 3> myMatrix22(myMatrix3_e);
    CSF::SparseMatrix<float, uint64_t, 1> myMatrix23(myMatrix3_e);
    CSF::SparseMatrix<float, uint64_t, 2> myMatrix24(myMatrix3_e);
    CSF::SparseMatrix<float, uint64_t, 3> myMatrix25(myMatrix3_e);
    CSF::SparseMatrix<float> myMatrix26(myMatrix3_e);
    CSF::SparseMatrix<float, short, 2> myMatrix27(myMatrix3_e);
    CSF::SparseMatrix<float, long, 3> myMatrix28(myMatrix3_e);
    //!CSF::SparseMatrix<float, uint8_t, 3> myMatrix29(myMatrix2);

    // Create uint64_t CSF matrices of compression levels 1, 2, and 3 (competent user)
    CSF::SparseMatrix<uint64_t, int, 1> myMatrix30(myMatrix4_e);
    CSF::SparseMatrix<uint64_t, int, 2> myMatrix31(myMatrix4_e);
    CSF::SparseMatrix<uint64_t, int, 3> myMatrix32(myMatrix4_e);
    CSF::SparseMatrix<uint64_t, uint64_t, 1> myMatrix33(myMatrix4_e);
    CSF::SparseMatrix<uint64_t, uint64_t, 2> myMatrix34(myMatrix4_e);
    CSF::SparseMatrix<uint64_t, uint64_t, 3> myMatrix35(myMatrix4_e);
    CSF::SparseMatrix<uint64_t> myMatrix36(myMatrix4_e);
    CSF::SparseMatrix<uint64_t, short, 2> myMatrix37(myMatrix4_e);
    CSF::SparseMatrix<uint64_t, long, 3> myMatrix38(myMatrix4_e);
    //!CSF::SparseMatrix<uint64_t, uint8_t, 3> myMatrix39(myMatrix2);



    // ---- Test deep copy constructor ---- //

    // Create a deep copy of the above CSF matrices
    CSF::SparseMatrix<int, int, 1> myMatrix40(myMatrix1);
    CSF::SparseMatrix<int, int, 2> myMatrix41(myMatrix2);
    CSF::SparseMatrix<int, int, 3> myMatrix42(myMatrix3);
    // print out the rows and columns of matrix42
    std::cout << "myMatrix42 has " << myMatrix42.rows() << " rows and " << myMatrix42.cols() << " columns." << std::endl;
    // print the compression level
    std::cout << "myMatrix42 has compression level " << myMatrix42.compLvl() << std::endl;
    myMatrix42.write("tmp/myMatrix42.csf");
    CSF::SparseMatrix<int, uint64_t, 1> myMatrix43(myMatrix4);
    CSF::SparseMatrix<int, uint64_t, 2> myMatrix44(myMatrix5);
    CSF::SparseMatrix<int, uint64_t, 3> myMatrix45(myMatrix6);
    CSF::SparseMatrix<int> myMatrix46(myMatrix7);
    CSF::SparseMatrix<int, short, 2> myMatrix47(myMatrix8);
    CSF::SparseMatrix<int, long, 3> myMatrix48(myMatrix9);
    //!CSF::SparseMatrix<int, uint8_t, 3> myMatrix49(myMatrix10);

    CSF::SparseMatrix<double, int, 1> myMatrix50(myMatrix11);
    CSF::SparseMatrix<double, int, 2> myMatrix51(myMatrix12);
    CSF::SparseMatrix<double, int, 3> myMatrix52(myMatrix13);
    CSF::SparseMatrix<double, uint64_t, 1> myMatrix53(myMatrix14);
    CSF::SparseMatrix<double, uint64_t, 2> myMatrix54(myMatrix15);
    CSF::SparseMatrix<double> myMatrix55(myMatrix16);
    CSF::SparseMatrix<double, short, 2> myMatrix56(myMatrix17);
    CSF::SparseMatrix<double, long, 3> myMatrix57(myMatrix18);
    //!CSF::SparseMatrix<double, uint8_t, 3> myMatrix58(myMatrix19);

    CSF::SparseMatrix<float, int, 1> myMatrix59(myMatrix20);
    CSF::SparseMatrix<float, int, 2> myMatrix60(myMatrix21);
    CSF::SparseMatrix<float, int, 3> myMatrix61(myMatrix22);
    CSF::SparseMatrix<float, uint64_t, 1> myMatrix62(myMatrix23);
    CSF::SparseMatrix<float, uint64_t, 2> myMatrix63(myMatrix24);
    CSF::SparseMatrix<float, uint64_t, 3> myMatrix64(myMatrix25);
    CSF::SparseMatrix<float> myMatrix65(myMatrix26);
    CSF::SparseMatrix<float, short, 2> myMatrix66(myMatrix27);
    CSF::SparseMatrix<float, long, 3> myMatrix67(myMatrix28);
    //!CSF::SparseMatrix<float, uint8_t, 3> myMatrix68(myMatrix29);

    CSF::SparseMatrix<uint64_t, int, 1> myMatrix69(myMatrix30);
    CSF::SparseMatrix<uint64_t, int, 2> myMatrix70(myMatrix31);
    CSF::SparseMatrix<uint64_t, int, 3> myMatrix71(myMatrix32);
    CSF::SparseMatrix<uint64_t, uint64_t, 1> myMatrix72(myMatrix33);
    CSF::SparseMatrix<uint64_t, uint64_t, 2> myMatrix73(myMatrix34);
    CSF::SparseMatrix<uint64_t, uint64_t, 3> myMatrix74(myMatrix35);
    CSF::SparseMatrix<uint64_t> myMatrix75(myMatrix36);
    CSF::SparseMatrix<uint64_t, short, 2> myMatrix76(myMatrix37);
    CSF::SparseMatrix<uint64_t, long, 3> myMatrix77(myMatrix38);
    //!CSF::SparseMatrix<uint64_t, uint8_t, 3> myMatrix78(myMatrix39);

    // ---- Test raw pointer constructors ---- //


    // ---- Test File IO on CSF Matrices ---- //

    // write CSF matrices to file
    myMatrix1.write("tmp/myMatrix1.csf");
    myMatrix2.write("tmp/myMatrix2.csf");
    myMatrix3.write("tmp/myMatrix3.csf");
    myMatrix4.write("tmp/myMatrix4.csf");
    myMatrix5.write("tmp/myMatrix5.csf");
    myMatrix6.write("tmp/myMatrix6.csf");
    myMatrix7.write("tmp/myMatrix7.csf");
    myMatrix8.write("tmp/myMatrix8.csf");
    myMatrix9.write("tmp/myMatrix9.csf");
    //!myMatrix10.write("/tmp/myMatrix10.csf");
    
    myMatrix11.write("tmp/myMatrix11.csf");
    myMatrix12.write("tmp/myMatrix12.csf");
    myMatrix13.write("tmp/myMatrix13.csf");
    myMatrix14.write("tmp/myMatrix14.csf");
    myMatrix15.write("tmp/myMatrix15.csf");
    myMatrix16.write("tmp/myMatrix16.csf");
    myMatrix17.write("tmp/myMatrix17.csf");
    myMatrix18.write("tmp/myMatrix18.csf");
    //!myMatrix19.write("/tmp/myMatrix19.csf");

    myMatrix20.write("tmp/myMatrix20.csf");
    myMatrix21.write("tmp/myMatrix21.csf");
    myMatrix22.write("tmp/myMatrix22.csf");
    myMatrix23.write("tmp/myMatrix23.csf");
    myMatrix24.write("tmp/myMatrix24.csf");
    myMatrix25.write("tmp/myMatrix25.csf");
    myMatrix26.write("tmp/myMatrix26.csf");
    myMatrix27.write("tmp/myMatrix27.csf");
    myMatrix28.write("tmp/myMatrix28.csf");
    //!myMatrix29.write("/tmp/myMatrix29.csf");

    myMatrix30.write("tmp/myMatrix30.csf");
    myMatrix31.write("tmp/myMatrix31.csf");
    myMatrix32.write("tmp/myMatrix32.csf");
    myMatrix33.write("tmp/myMatrix33.csf");
    myMatrix34.write("tmp/myMatrix34.csf");
    myMatrix35.write("tmp/myMatrix35.csf");
    myMatrix36.write("tmp/myMatrix36.csf");
    myMatrix37.write("tmp/myMatrix37.csf");
    myMatrix38.write("tmp/myMatrix38.csf");
    //!myMatrix39.write("/tmp/myMatrix39.csf");

    // read CSF matrices from file
    CSF::SparseMatrix<int, int, 1> myMatrix1_read("tmp/myMatrix1.csf");
    CSF::SparseMatrix<int, int, 2> myMatrix2_read("tmp/myMatrix2.csf");
    CSF::SparseMatrix<int, int, 3> myMatrix3_read("tmp/myMatrix3.csf");
    CSF::SparseMatrix<int, uint64_t, 1> myMatrix4_read("tmp/myMatrix4.csf");
    CSF::SparseMatrix<int, uint64_t, 2> myMatrix5_read("tmp/myMatrix5.csf");
    CSF::SparseMatrix<int, uint64_t, 3> myMatrix6_read("tmp/myMatrix6.csf");
    CSF::SparseMatrix<int> myMatrix7_read("tmp/myMatrix7.csf");
    CSF::SparseMatrix<int, short, 2> myMatrix8_read("tmp/myMatrix8.csf");
    CSF::SparseMatrix<int, long, 3> myMatrix9_read("tmp/myMatrix9.csf");
    //!CSF::SparseMatrix<int, uint8_t, 3> myMatrix10_read("/tmp/myMatrix10.csf");

    CSF::SparseMatrix<double, int, 1> myMatrix11_read("tmp/myMatrix11.csf");
    CSF::SparseMatrix<double, int, 2> myMatrix12_read("tmp/myMatrix12.csf");
    CSF::SparseMatrix<double, int, 3> myMatrix13_read("tmp/myMatrix13.csf");
    CSF::SparseMatrix<double, uint64_t, 1> myMatrix14_read("tmp/myMatrix14.csf");
    CSF::SparseMatrix<double, uint64_t, 2> myMatrix15_read("tmp/myMatrix15.csf");
    CSF::SparseMatrix<double> myMatrix16_read("tmp/myMatrix16.csf");
    CSF::SparseMatrix<double, short, 2> myMatrix17_read("tmp/myMatrix17.csf");
    CSF::SparseMatrix<double, long, 3> myMatrix18_read("tmp/myMatrix18.csf");
    //!CSF::SparseMatrix<double, uint8_t, 3> myMatrix19_read("/tmp/myMatrix19.csf");

    CSF::SparseMatrix<float, int, 1> myMatrix20_read("tmp/myMatrix20.csf");
    CSF::SparseMatrix<float, int, 2> myMatrix21_read("tmp/myMatrix21.csf");
    CSF::SparseMatrix<float, int, 3> myMatrix22_read("tmp/myMatrix22.csf");
    CSF::SparseMatrix<float, uint64_t, 1> myMatrix23_read("tmp/myMatrix23.csf");
    CSF::SparseMatrix<float, uint64_t, 2> myMatrix24_read("tmp/myMatrix24.csf");
    CSF::SparseMatrix<float, uint64_t, 3> myMatrix25_read("tmp/myMatrix25.csf");
    CSF::SparseMatrix<float> myMatrix26_read("tmp/myMatrix26.csf");
    CSF::SparseMatrix<float, short, 2> myMatrix27_read("tmp/myMatrix27.csf");
    CSF::SparseMatrix<float, long, 3> myMatrix28_read("tmp/myMatrix28.csf");
    //!CSF::SparseMatrix<float, uint8_t, 3> myMatrix29_read("/tmp/myMatrix29.csf");

    CSF::SparseMatrix<uint64_t, int, 1> myMatrix30_read("tmp/myMatrix30.csf");
    CSF::SparseMatrix<uint64_t, int, 2> myMatrix31_read("tmp/myMatrix31.csf");
    CSF::SparseMatrix<uint64_t, int, 3> myMatrix32_read("tmp/myMatrix32.csf");
    CSF::SparseMatrix<uint64_t, uint64_t, 1> myMatrix33_read("tmp/myMatrix33.csf");
    CSF::SparseMatrix<uint64_t, uint64_t, 2> myMatrix34_read("tmp/myMatrix34.csf");
    CSF::SparseMatrix<uint64_t, uint64_t, 3> myMatrix35_read("tmp/myMatrix35.csf");
    CSF::SparseMatrix<uint64_t> myMatrix36_read("tmp/myMatrix36.csf");
    CSF::SparseMatrix<uint64_t, short, 2> myMatrix37_read("tmp/myMatrix37.csf");
    CSF::SparseMatrix<uint64_t, long, 3> myMatrix38_read("tmp/myMatrix38.csf");
    //!CSF::SparseMatrix<uint64_t, uint8_t, 3> myMatrix39_read("/tmp/myMatrix39.csf");


    // write a few of the read matrices again
    myMatrix1_read.write("tmp/myMatrix1_read.csf");
    myMatrix12_read.write("tmp/myMatrix12_read.csf");
    myMatrix23_read.write("tmp/myMatrix23_read.csf");
    myMatrix34_read.write("tmp/myMatrix34_read.csf");
    

    // ---- Test moving between compression levels ---- //

    // move from level 1 to level 2
    CSF::SparseMatrix<int, int, 2> myMatrix1_level2 = myMatrix1.to_csf2();
    myMatrix1_level2.write("tmp/myMatrix1_level2.csf");

    CSF::SparseMatrix<int, uint64_t, 2> myMatrix4_level2 = myMatrix4.to_csf2();
    myMatrix4_level2.write("tmp/myMatrix4_level2.csf");

    CSF::SparseMatrix<double, int, 2> myMatrix11_level2 = myMatrix11.to_csf2();
    myMatrix11_level2.write("tmp/myMatrix11_level2.csf");

    CSF::SparseMatrix<double, uint64_t, 2> myMatrix14_level2 = myMatrix14.to_csf2();
    myMatrix14_level2.write("tmp/myMatrix14_level2.csf");

    CSF::SparseMatrix<float, int, 2> myMatrix20_level2 = myMatrix20.to_csf2();
    myMatrix20_level2.write("tmp/myMatrix20_level2.csf");

    CSF::SparseMatrix<float, uint64_t, 2> myMatrix23_level2 = myMatrix23.to_csf2();
    myMatrix23_level2.write("tmp/myMatrix23_level2.csf");

    CSF::SparseMatrix<uint64_t, int, 2> myMatrix30_level2 = myMatrix30.to_csf2();
    myMatrix30_level2.write("tmp/myMatrix30_level2.csf");

    CSF::SparseMatrix<uint64_t, uint64_t, 2> myMatrix33_level2 = myMatrix33.to_csf2();
    myMatrix33_level2.write("tmp/myMatrix33_level2.csf");

    // move from level 1 to level 3

    CSF::SparseMatrix<int, int, 3> myMatrix1_level3 = myMatrix1.to_csf3();
    myMatrix1_level3.write("tmp/myMatrix1_level3.csf");

    CSF::SparseMatrix<int, uint64_t, 3> myMatrix4_level3 = myMatrix4.to_csf3();
    myMatrix4_level3.write("tmp/myMatrix4_level3.csf");

    CSF::SparseMatrix<double, int, 3> myMatrix11_level3 = myMatrix11.to_csf3();
    myMatrix11_level3.write("tmp/myMatrix11_level3.csf");

    CSF::SparseMatrix<double, uint64_t, 3> myMatrix14_level3 = myMatrix14.to_csf3();
    myMatrix14_level3.write("tmp/myMatrix14_level3.csf");

    CSF::SparseMatrix<float, int, 3> myMatrix20_level3 = myMatrix20.to_csf3();
    myMatrix20_level3.write("tmp/myMatrix20_level3.csf");

    CSF::SparseMatrix<float, uint64_t, 3> myMatrix23_level3 = myMatrix23.to_csf3();
    myMatrix23_level3.write("/tmp/myMatrix23_level3.csf");

    CSF::SparseMatrix<uint64_t, int, 3> myMatrix30_level3 = myMatrix30.to_csf3();
    myMatrix30_level3.write("tmp/myMatrix30_level3.csf");

    CSF::SparseMatrix<uint64_t, uint64_t, 3> myMatrix33_level3 = myMatrix33.to_csf3();
    myMatrix33_level3.write("tmp/myMatrix33_level3.csf");

    // move from 1 to eigen
    Eigen::SparseMatrix<int> myMatrix1_eigen = myMatrix1.to_eigen();

    Eigen::SparseMatrix<int> myMatrix4_eigen = myMatrix4.to_eigen();

    Eigen::SparseMatrix<double> myMatrix11_eigen = myMatrix11.to_eigen();

    Eigen::SparseMatrix<double> myMatrix14_eigen = myMatrix14.to_eigen();

    Eigen::SparseMatrix<float> myMatrix20_eigen = myMatrix20.to_eigen();

    Eigen::SparseMatrix<float> myMatrix23_eigen = myMatrix23.to_eigen();

    Eigen::SparseMatrix<uint64_t> myMatrix30_eigen = myMatrix30.to_eigen();

    Eigen::SparseMatrix<uint64_t> myMatrix33_eigen = myMatrix33.to_eigen();

    // ---- Test helper methods ---- //

    // test rows, cols, and nonzero methods

    // matrix1
    std::cout << "myMatrix1 has " << myMatrix1.rows() << " rows, " << myMatrix1.cols() << " cols, and " << myMatrix1.nonzeros() << " nonzero elements" << std::endl;

    // matrix8
    std::cout << "myMatrix8 has " << myMatrix8.rows() << " rows, " << myMatrix8.cols() << " cols, and " << myMatrix8.nonzeros() << " nonzero elements" << std::endl;

    // matrix17
    std::cout << "myMatrix17 has " << myMatrix17.rows() << " rows, " << myMatrix17.cols() << " cols, and " << myMatrix17.nonzeros() << " nonzero elements" << std::endl;

    // matrix26
    std::cout << "myMatrix26 has " << myMatrix26.rows() << " rows, " << myMatrix26.cols() << " cols, and " << myMatrix26.nonzeros() << " nonzero elements" << std::endl;

    // matrix35
    std::cout << "myMatrix35 has " << myMatrix35.rows() << " rows, " << myMatrix35.cols() << " cols, and " << myMatrix35.nonzeros() << " nonzero elements" << std::endl;

    

    // for each matrix print out the byte_size()
    std::cout << "myMatrix1 comp_lvl and byte size: " << myMatrix1.compLvl() << " " << myMatrix1.byte_size() << std::endl;
    std::cout << "myMatrix2 comp_lvl and byte size: " << myMatrix2.compLvl() << " " << myMatrix2.byte_size() << std::endl;
    std::cout << "myMatrix3 comp_lvl and byte size: " << myMatrix3.compLvl() << " " << myMatrix3.byte_size() << std::endl;
    std::cout << "myMatrix4 comp_lvl and byte size: " << myMatrix4.compLvl() << " " << myMatrix4.byte_size() << std::endl;
    std::cout << "myMatrix5 comp_lvl and byte size: " << myMatrix5.compLvl() << " " << myMatrix5.byte_size() << std::endl;
    std::cout << "myMatrix6 comp_lvl and byte size: " << myMatrix6.compLvl() << " " << myMatrix6.byte_size() << std::endl;
    std::cout << "myMatrix7 comp_lvl and byte size: " << myMatrix7.compLvl() << " " << myMatrix7.byte_size() << std::endl;
    std::cout << "myMatrix8 comp_lvl and byte size: " << myMatrix8.compLvl() << " " << myMatrix8.byte_size() << std::endl;
    std::cout << "myMatrix9 comp_lvl and byte size: " << myMatrix9.compLvl() << " " << myMatrix9.byte_size() << std::endl;
    //std::cout << "myMatrix10 comp_lvl and byte size: " << myMatrix10.compLvl() << " " << myMatrix10.byte_size() << std::endl;
    std::cout << "myMatrix11 comp_lvl and byte size: " << myMatrix11.compLvl() << " " << myMatrix11.byte_size() << std::endl;
    std::cout << "myMatrix12 comp_lvl and byte size: " << myMatrix12.compLvl() << " " << myMatrix12.byte_size() << std::endl;
    std::cout << "myMatrix13 comp_lvl and byte size: " << myMatrix13.compLvl() << " " << myMatrix13.byte_size() << std::endl;
    std::cout << "myMatrix14 comp_lvl and byte size: " << myMatrix14.compLvl() << " " << myMatrix14.byte_size() << std::endl;
    std::cout << "myMatrix15 comp_lvl and byte size: " << myMatrix15.compLvl() << " " << myMatrix15.byte_size() << std::endl;
    std::cout << "myMatrix16 comp_lvl and byte size: " << myMatrix16.compLvl() << " " << myMatrix16.byte_size() << std::endl;
    std::cout << "myMatrix17 comp_lvl and byte size: " << myMatrix17.compLvl() << " " << myMatrix17.byte_size() << std::endl;
    std::cout << "myMatrix18 comp_lvl and byte size: " << myMatrix18.compLvl() << " " << myMatrix18.byte_size() << std::endl;
    //std::cout << "myMatrix19 comp_lvl and byte size: " << myMatrix19.compLvl() << " " << myMatrix19.byte_size() << std::endl;
    std::cout << "myMatrix20 comp_lvl and byte size: " << myMatrix20.compLvl() << " " << myMatrix20.byte_size() << std::endl;
    std::cout << "myMatrix21 comp_lvl and byte size: " << myMatrix21.compLvl() << " " << myMatrix21.byte_size() << std::endl;
    std::cout << "myMatrix22 comp_lvl and byte size: " << myMatrix22.compLvl() << " " << myMatrix22.byte_size() << std::endl;
    std::cout << "myMatrix23 comp_lvl and byte size: " << myMatrix23.compLvl() << " " << myMatrix23.byte_size() << std::endl;
    std::cout << "myMatrix24 comp_lvl and byte size: " << myMatrix24.compLvl() << " " << myMatrix24.byte_size() << std::endl;
    std::cout << "myMatrix25 comp_lvl and byte size: " << myMatrix25.compLvl() << " " << myMatrix25.byte_size() << std::endl;
    std::cout << "myMatrix26 comp_lvl and byte size: " << myMatrix26.compLvl() << " " << myMatrix26.byte_size() << std::endl;
    std::cout << "myMatrix27 comp_lvl and byte size: " << myMatrix27.compLvl() << " " << myMatrix27.byte_size() << std::endl;
    std::cout << "myMatrix28 comp_lvl and byte size: " << myMatrix28.compLvl() << " " << myMatrix28.byte_size() << std::endl;
    //std::cout << "myMatrix29 comp_lvl and byte size: " << myMatrix29.compLvl() << " " << myMatrix29.byte_size() << std::endl;
    std::cout << "myMatrix30 comp_lvl and byte size: " << myMatrix30.compLvl() << " " << myMatrix30.byte_size() << std::endl;
    std::cout << "myMatrix31 comp_lvl and byte size: " << myMatrix31.compLvl() << " " << myMatrix31.byte_size() << std::endl;
    std::cout << "myMatrix32 comp_lvl and byte size: " << myMatrix32.compLvl() << " " << myMatrix32.byte_size() << std::endl;
    std::cout << "myMatrix33 comp_lvl and byte size: " << myMatrix33.compLvl() << " " << myMatrix33.byte_size() << std::endl;
    std::cout << "myMatrix34 comp_lvl and byte size: " << myMatrix34.compLvl() << " " << myMatrix34.byte_size() << std::endl;
    std::cout << "myMatrix35 comp_lvl and byte size: " << myMatrix35.compLvl() << " " << myMatrix35.byte_size() << std::endl;
    std::cout << "myMatrix36 comp_lvl and byte size: " << myMatrix36.compLvl() << " " << myMatrix36.byte_size() << std::endl;
    std::cout << "myMatrix37 comp_lvl and byte size: " << myMatrix37.compLvl() << " " << myMatrix37.byte_size() << std::endl;
    std::cout << "myMatrix38 comp_lvl and byte size: " << myMatrix38.compLvl() << " " << myMatrix38.byte_size() << std::endl;


    // for matrix23 print out the vals, indexes, and col_p
    std::cout << "myMatrix23 vals: " << std::endl;
    for (int i = 0; i < myMatrix23.nonzeros(); i++) {
        std::cout << ((float *)myMatrix23.valuePtr())[i] << " ";
    }

    std::cout << std::endl << "myMatrix23 indexes: " << std::endl;
    for (int i = 0; i < myMatrix23.nonzeros(); i++) {
        std::cout << ((uint64_t *)myMatrix23.indexPtr())[i] << " ";
    }

    std::cout << std::endl << "myMatrix23 col_p: " << std::endl;
    for (int i = 0; i < myMatrix23.cols() + 1; i++) {
        std::cout << ((uint64_t *)myMatrix23.colPtr())[i] << " ";
    }

    std::cout << std::endl;

    // for matrix4 print out the vals, indexes, and col_p
    std::cout << "myMatrix4 vals: " << std::endl;
    for (int i = 0; i < myMatrix4.nonzeros(); i++) {
        std::cout << ((int *)myMatrix4.valuePtr())[i] << " ";
    }

    std::cout << std::endl << "myMatrix4 indexes: " << std::endl;
    for (int i = 0; i < myMatrix4.nonzeros(); i++) {
        std::cout << ((uint64_t *)myMatrix4.indexPtr())[i] << " ";
    }

    std::cout << std::endl << "myMatrix4 col_p: " << std::endl;
    for (int i = 0; i < myMatrix4.cols() + 1; i++) {
        std::cout << ((uint64_t *)myMatrix4.colPtr())[i] << " ";
    }

    std::cout << std::endl;

    return 0;
}