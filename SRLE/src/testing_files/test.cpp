#include <iostream>
#include <fstream>
#include <vector>
#include <bits/stdc++.h>
#include <Eigen/Sparse>

using namespace std;

void test() {
    
}

int main() {

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

    for (int k = 0; k < mat.outerSize(); ++k)
        for (Eigen::SparseMatrix<int>::InnerIterator it(mat, k); it; ++it)
        {
            cout << it.value() << " " << it.row() << " " << it.col() << endl;
        }

    cout << mat.outerSize() << endl;
    cout << mat.innerSize() << endl;

    return 0;
}