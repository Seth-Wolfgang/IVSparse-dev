#include <iostream>
#include <fstream>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

int main() {
    
    vector<uint8_t> data;

    int num  = 258;

    data.reserve(4);

    memcpy(&data[0], &num, 1);

    //print data
    for (int i = 0; i < 4; i++)
        std::cout << (uint16_t) data[i] << " ";

}