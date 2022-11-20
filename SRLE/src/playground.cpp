//[[Rcpp::depends(RcppClock)]]
#include <iostream>
#include <iterator>
#include <chrono>
#include "const_array_iterator.cpp"
#include "GenericCSCIterator.cpp"
#include "matrixCreator.cpp"
#include <RcppClock.h>
#include <Rcpp.h>
#include <RcppEigen.h>

using namespace std;

void calcTime(chrono::steady_clock::time_point begin, chrono::steady_clock::time_point end);


template<typename T>
Eigen::SparseMatrix<T> generateMatrix(int numRows, int numCols, double sparsity);

int main(){
    Rcpp::Clock clock;

    clock.tick("SRLE");
    //My Iterator test
    const_array_iterator<int>* iter = new const_array_iterator<int>("input.bin");
    // iter->operator++();
    double value = 0;

    while(iter->operator bool()) {
        iter->operator++();
        if(iter->operator *() != value){
            // cout << iter->operator *() << endl;
            value =  iter->operator *();
        }
    }
    clock.tock("SRLE");


    ////////////////////////////////CSC innerIterator////////////////////////////////
    //generating a large random eigen sparse
    cout << "Testing Eigen" << endl;
    uint64_t total = 0;
    // vector<char> v(10000);
    // for(int i = 0; i < v.size(); i++){
    //     v.push_back(i);
    // }

    Eigen::SparseMatrix<int> myMatrix(100, 100);
    myMatrix.reserve(Eigen::VectorXi::Constant(100, 100));
    myMatrix = generateMatrix<int>(100, 100, 100);
    myMatrix.makeCompressed();

    // for (int k=0; k<10000; ++k)
    //     myMatrix.insert(k, k) = 8;
    // myMatrix.makeCompressed();
    // cout << "Size of myMatrix after compression: " << sizeof(myMatrix) << endl;

    //begin timing
    clock.tick("Eigen");
    Eigen::SparseMatrix<int>::InnerIterator it(myMatrix, 0);
    for (int k=0; k<100; ++k){
        for (Eigen::SparseMatrix<int>::InnerIterator it(myMatrix, k); it; ++it){
            total += it.value();
        }
    }
    clock.tock("Eigen");
    cout << "Total: " << total << endl;


    ////////////////////////////////GENERIC CSC Iterator////////////////////////////////
    cout << "Testing CSC Iterator" << endl;
    total = 0;
    clock.tick("CSC");
    GenericCSCIterator<int> iter2 = GenericCSCIterator<int>(myMatrix);
    while(iter2.operator bool()){
        total += iter2.operator *();
        iter2.operator++();
    }
    clock.tock("CSC");
    cout << "Total: " << total << endl;

    clock.stop("Iterators");


    return 0;
}


void calcTime(chrono::steady_clock::time_point begin, chrono::steady_clock::time_point end){
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[µs]" << std::endl;
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count() << "[ns]" << std::endl;
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::milliseconds> (end - begin).count() << "[ms]" << std::endl;

}


template <typename T>
Eigen::SparseMatrix<T> generateMatrix(int numRows, int numCols, double sparsity){
    //generate a random sparse matrix
    uint64_t favoriteNumber = 11515616;
    rng randMatrixGen = rng(favoriteNumber);

    Eigen::SparseMatrix<T> myMatrix(numRows, numCols);
    myMatrix.reserve(Eigen::VectorXi::Constant(numRows, numCols));

    for(int i = 0; i < numRows; i++){
        for(int j = 0; j < numCols; j++){
            if(randMatrixGen.draw<int>(i,j, sparsity)){
                myMatrix.insert(i, j) = 100 * randMatrixGen.uniform<double>(j);
            }
        }
    }
    return myMatrix;
}