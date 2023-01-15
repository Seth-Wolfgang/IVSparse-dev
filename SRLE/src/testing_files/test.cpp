#include <iostream>
#include <fstream>
#include <vector>
#include <bits/stdc++.h>
#include <Eigen/Sparse>

using namespace std;


void test(int **vals) {
    // access the 5 array values and print them out
    for (int i = 0; i < 5; i++) {
        cout << (*vals)[i] << endl;
    }
}

int main() {

    // malloc space for 5 integers
    int *arr = (int *)malloc(5 * sizeof(int));
    
    // assign values to the array
    for (int i = 0; i < 5; i++) {
        arr[i] = i;
    }

    // create a pointer pointer to pass to test()
    int **vals = &arr;

    // call test()
    test(vals);

    return 0;
}