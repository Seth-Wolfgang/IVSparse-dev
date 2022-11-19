#include <iostream>
#include <iterator>
#include <chrono>
#include "const_array_iterator.cpp"
#include <Eigen/Sparse>

using namespace std;

void calcTime(chrono::steady_clock::time_point begin, chrono::steady_clock::time_point end);

int main(){

    //My Iterator test
    const_array_iterator<int>* iter = new const_array_iterator<int>("input.bin");
    // iter->operator++();
    double value = 0;

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    while(iter->operator bool()) {
        iter->operator++();
        if(iter->operator *() != value){
            // cout << iter->operator *() << endl;
            value =  iter->operator *();
        }
    }
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    calcTime(begin, end);

    //CSC innerIterator
    //generating a large random eigen sparse
    cout << "Testing Eigen" << endl;
    uint64_t total = 0;
    vector<char> v(10000);
    for(int i = 0; i < v.size(); i++){
        v.push_back(i);
    }

    Eigen::SparseMatrix<int> myMatrix(10000, 10000);
    myMatrix.reserve(Eigen::VectorXi::Constant(10000, 10000));
    for (int k=0; k<10000; ++k)
        myMatrix.insert(k, k) = 8;
    myMatrix.makeCompressed();
    cout << "Size of myMatrix after compression: " << sizeof(myMatrix) << endl;
    
    //begin timing
    begin = std::chrono::steady_clock::now();
    Eigen::SparseMatrix<int>::InnerIterator it(myMatrix, 0);
    for (int k=0; k<10000; ++k){
        for (Eigen::SparseMatrix<int>::InnerIterator it(myMatrix,k); it; ++it){
            total += it.value();
        }
    }
    end = std::chrono::steady_clock::now();
    cout << total << endl;
    calcTime(begin, end);


    Eigen::SparseVector<int> vec(10000);
    vec.reserve(10000);
    for (int k=0; k<10000; ++k)
        vec.insert(k) = 8;
    vec.makeCompressed();

    cout << "Vector" << endl;
    //begin timing
    begin = std::chrono::steady_clock::now();
    for (SparseVector<int>::InnerIterator it(vec); it; ++it){
        total += it.value();
    }
    end = std::chrono::steady_clock::now();
    calcTime(begin, end);


    return 0;
}


void calcTime(chrono::steady_clock::time_point begin, chrono::steady_clock::time_point end){
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[µs]" << std::endl;
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count() << "[ns]" << std::endl;
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::milliseconds> (end - begin).count() << "[ms]" << std::endl;

}