#include <iostream>
#include <fstream>
#include <vector>
#include <bits/stdc++.h>
#include <Eigen/Sparse>

using namespace std;


int main() {

    cout << "Testing Eigen" << endl;
    // Create a 30x30 sparse matrix
    Eigen::SparseMatrix<double> A(30, 30);
    for (int k = 0; k < 30; ++k) {
        A.insert(k, k) = k*k;
    }
    cout << "A: " << endl << A << endl;

    // make a list of all the non-zero elements
    vector<double> non_zero;
    for (int k = 0; k < 30; ++k) {
        non_zero.push_back(A.coeff(k, k));
    }

    // print the list of non-zero elements
    cout << "non_zero: " << endl;
    for (int k = 0; k < non_zero.size(); ++k) {
        cout << non_zero[k] << " ";
    }

    // get a list of the indices of the non-zero elements
    vector<int> indices;
    for (int k = 0; k < 30; ++k) {
        indices.push_back(A.outerIndexPtr()[k]);
    }

    // print the list of indices
    cout << endl << "indices: " << endl;
    for (int k = 0; k < indices.size(); ++k) {
        cout << indices[k] << " ";
    }

    // get a list of the column indices of the non-zero elements
    vector<int> col_indices;
    for (int k = 0; k < 30; ++k) {
        col_indices.push_back(A.innerIndexPtr()[k]);
    }

    // print the list of column indices
    cout << endl << "col_indices: " << endl;
    for (int k = 0; k < col_indices.size(); ++k) {
        cout << col_indices[k] << " ";
    }

    return 0;
}