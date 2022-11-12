#include <iostream>
#include <fstream>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

void testing(const int *data, size_t size) {
    for (size_t i = 0; i < size; i++) {
        cout << (int)data[i] << " ";
    }
}

int main() {
    
    vector<uint8_t> data;

    int num  = 258;

    data.reserve(4);

    memcpy(&data[0], &num, 1);

    //print data
    for (int i = 0; i < 4; i++)
        std::cout << (uint16_t) data[i] << " ";
    
    cout << endl;


    int* test_data = (int*) malloc(4 * sizeof(int));

    for (int i = 0; i < 4; i++) {
        test_data[i] = i;
    }

    testing(test_data, 4);

    cout << endl;

    free(test_data);

}