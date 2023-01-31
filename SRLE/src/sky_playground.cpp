#include <iostream>
#include <Eigen/Sparse>

#include "CSFmatrix.h"

int main()
{

    // malloc space for data
    int *values_arr = (int *)malloc(58 * sizeof(int));
    int *indexes_arr = (int *)malloc(58 * sizeof(int));
    int *col_p_arr = (int *)malloc(4 * sizeof(int));
    int x[58] = {
        1, 1, 2, 3, 1, 2, 2, 1, 1, 2, 3, 1, 3, 1, 3, 1, 2, 3, 2, 1, 1,

        1, 1, 2, 1, 1, 1, 2, 1, 1, 2, 2, 1, 3, 3, 1, 1, 1,

        2, 3, 1, 3, 1, 3, 4000000, 8, 2, 1, 1, 2, 3, 3, 3, 3, 1, 1, 1, 8};

    int i[58] = {

        1, 2, 3, 5, 7, 9, 10, 11, 12, 14, 15, 19, 20, 23, 24, 25, 26, 29, 30, 32, 34,

        0, 9, 13, 14, 15, 16, 20, 21, 23, 24, 25, 26, 27, 29, 31, 32, 35,

        0, 1, 3, 4, 6, 7, 9, 10, 12, 13, 14, 16, 17, 19, 23, 24, 28, 30, 31, 35};

    int p[58] = {0, 21, 38, 58};

    // put values into allocated space
    for (size_t j = 0; j < 58; j++)
    {
        values_arr[j] = x[j];
        indexes_arr[j] = i[j];
    }

    for (size_t j = 0; j < 4; j++)
    {
        col_p_arr[j] = p[j];
    }

    size_t val_num = 58;
    size_t row_num = 36;
    size_t col_num = 3;

    // call constructor

    int **vals = &values_arr;
    int **indexes = &indexes_arr;
    int **col_p = &col_p_arr;

    CSF::SparseMatrix test(vals, indexes, col_p, val_num, row_num, col_num, false);

    // print out vals, indexs, col_p
    for (size_t j = 0; j < 58; j++)
    {
        printf("%d ", values_arr[j]);
    }

    printf("\n");

    for (size_t j = 0; j < 58; j++)
    {
        printf("%d ", indexes_arr[j]);
    }

    printf("\n");

    for (size_t j = 0; j < 4; j++)
    {
        printf("%d ", col_p_arr[j]);
    }

    printf("\n");

    // free stuff
    free(values_arr);
    free(indexes_arr);
    free(col_p_arr);

    int rows = 10;
    int cols = 10;

    Eigen::SparseMatrix<int> mat(rows, cols);

    // populate the matrix
    mat.insert(2, 0) = 1;
    mat.insert(5, 0) = 2;
    mat.insert(3, 1) = 1;
    mat.insert(4, 1) = 2;
    mat.insert(9, 1) = 1;
    mat.insert(9, 2) = 1;
    mat.insert(1, 3) = 1;
    mat.insert(2, 3) = 1;
    mat.insert(6, 3) = 2;
    mat.insert(2, 4) = 2;
    mat.insert(4, 4) = 1;
    mat.insert(9, 4) = 1;
    mat.insert(3, 6) = 1;
    mat.insert(4, 6) = 1;
    mat.insert(5, 6) = 2;
    mat.insert(4, 7) = 1;
    mat.insert(5, 7) = 1;
    mat.insert(6, 7) = 2;
    mat.insert(7, 7) = 1;
    mat.insert(8, 7) = 1;
    mat.insert(4, 8) = 1;
    mat.insert(9, 8) = 2;
    mat.insert(4, 9) = 1;

    // call constructor
    CSF::SparseMatrix test2(mat);

    return 0;
}