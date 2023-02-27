
#include "CSF/SparseMatrix"
#include "misc/matrix_creator.cpp"
#include <iostream>

int main(int argc, char** argv) {

    // int rows = 10;
    // int cols = 10;

    // Eigen::SparseMatrix<int> mat(rows, cols);

    // // populate the matrix
    // mat.insert(2, 0) = 1;
    // mat.insert(5, 0) = 2;
    // mat.insert(3, 1) = 1;
    // mat.insert(4, 1) = 2;
    // mat.insert(9, 1) = 1;
    // mat.insert(9, 2) = 1;
    // mat.insert(1, 3) = 1;
    // mat.insert(2, 3) = 1;
    // mat.insert(6, 3) = 2;
    // mat.insert(2, 4) = 2;
    // mat.insert(4, 4) = 1;
    // mat.insert(9, 4) = 1;
    // mat.insert(3, 6) = 1;
    // mat.insert(4, 6) = 1;
    // mat.insert(5, 6) = 2;
    // mat.insert(4, 7) = 1;
    // mat.insert(5, 7) = 1;
    // mat.insert(6, 7) = 2;
    // mat.insert(7, 7) = 1;
    // mat.insert(8, 7) = 1;
    // mat.insert(4, 8) = 1;
    // mat.insert(9, 8) = 2;
    // mat.insert(4, 9) = 1;

    // // call constructor
    // CSF::SparseMatrix<int, int, 3> matrix(mat);

    // // print out num rows and cols
    // std::cout << matrix.rows() << std::endl;
    // std::cout << matrix.cols() << std::endl;

    // CSF::SparseMatrix<int, int, 1> mymat(mat);

    // // print out num rows and cols
    // std::cout << mymat.rows() << std::endl;
    // std::cout << mymat.cols() << std::endl;

    // // create new matrix using to_csf3
    // CSF::SparseMatrix<int, int, 3> matrix6 = mymat.to_csf3();

    // // print matrix
    // std::cout << matrix6.rows()  << std::endl;


    int numRows = 50;
    int numCols = 50;
    int sparsity = 4;
    uint64_t seed = 1956553944;

    // generating a large random eigen sparse
    Eigen::SparseMatrix<int> myMatrix(numRows, numCols);
    myMatrix.reserve(Eigen::VectorXi::Constant(numRows, numCols));
    myMatrix = generateMatrix<int>(numRows, numCols, sparsity, seed);
    myMatrix.makeCompressed();

    // call constructor
    CSF::SparseMatrix<int, int, 2> matrix2(myMatrix);

    // print out myMatrix
    std::cout << myMatrix << std::endl;

    // create a csf 1 matrix
    CSF::SparseMatrix<int, int, 1> matrix3(myMatrix);

    // compress matrix 3 to csf 3
    CSF::SparseMatrix<int, int, 3> matrix4 = matrix3.to_csf3();

    // print out rows and cols for matrix 4
    std::cout << matrix4.rows() << std::endl;
    std::cout << matrix4.cols() << std::endl;

    // write matrix to file
    matrix2.write("test.csfr");


    // create an eigen sparse matrix of type short
    Eigen::SparseMatrix<short> myMatrix2(numRows, numCols);

    // populate the matrix
    myMatrix2.insert(2, 0) = 1;
    myMatrix2.insert(5, 0) = 2;
    myMatrix2.insert(3, 1) = 1;
    myMatrix2.insert(4, 1) = 2;

    // call constructor
    //CSF::SparseMatrix<short> matrix5(myMatrix2);

    // // print matrix
    // //std::cout << myMatrix << std::endl;

    // // write matrix to file
    // matrix2.write("test.csfr");

    // int *values_arr = (int *)malloc(58 * sizeof(int));
    // int *indexes_arr = (int *)malloc(58 * sizeof(int));
    // int *col_p_arr = (int *)malloc(4 * sizeof(int));
    // int x[58] = {
    //     1, 1, 2, 3, 1, 2, 2, 1, 1, 2, 3, 1, 3, 1, 3, 1, 2, 3, 2, 1, 1,

    //     1, 1, 2, 1, 1, 1, 2, 1, 1, 2, 2, 1, 3, 3, 1, 1, 1,

    //     2, 3, 1, 3, 1, 3, 4000000, 8, 2, 1, 1, 2, 3, 3, 3, 3, 1, 1, 1, 8};

    // int i[58] = {

    //     1, 2, 3, 5, 7, 9, 10, 11, 12, 14, 15, 19, 20, 23, 24, 25, 26, 29, 30, 32, 34,

    //     0, 9, 13, 14, 15, 16, 20, 21, 23, 24, 25, 26, 27, 29, 31, 32, 35,

    //     0, 1, 3, 4, 6, 7, 9, 10, 12, 13, 14, 16, 17, 19, 23, 24, 28, 30, 31, 35};

    // int p[58] = {0, 21, 38, 58};

    // // put values into allocated space
    // for (size_t j = 0; j < 58; j++)
    // {
    //     values_arr[j] = x[j];
    //     indexes_arr[j] = i[j];
    // }

    // for (size_t j = 0; j < 4; j++)
    // {
    //     col_p_arr[j] = p[j];
    // }

    // size_t val_num = 58;
    // size_t row_num = 36;
    // size_t col_num = 3;

    // // call constructor
    // CSF::SparseMatrix<int> test(&values_arr, &indexes_arr, &col_p_arr, val_num, row_num, col_num);

    // // print out values_arr
    // for (size_t j = 0; j < 58; j++)
    // {
    //     std::cout << values_arr[j] << " ";
    // }

    // std::cout << std::endl;

    // test.write("test.csfr");

    // // print compression size
    // std::cout << "Compression size: " << test.byte_size() << std::endl;

    // // free allocated space
    // free(values_arr);
    // free(indexes_arr);
    // free(col_p_arr);


    return 0;
}