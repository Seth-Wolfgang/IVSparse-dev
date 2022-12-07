// [[Rcpp::depends(RcppEigen)]]
// [[Rcpp::depends(RcppClock)]]
// #include <RcppEigen.h>
#include "include/SRLE_Lib.hpp"
using namespace std;


//Functions
void iteratorBenchmark(int numRows, int numCols, double sparsity);
template <typename T> Eigen::SparseMatrix<T> generateMatrix(int numRows, int numCols, double sparsity);


int main() {
    int numRows = 100;
    int numCols = 100;
    double sparsity = 50;
    iteratorBenchmark(numRows, numCols, sparsity);

    // const_array_iterator<int>* iter = new const_array_iterator<int>("input.bin");
    // int value = 0;
    // ////clock.tick("SRLE");
    // while(iter->operator bool()) {
    //     iter->operator++();
    //     if(iter->operator *() != value){
    //         cout << iter->operator *() << endl;
    //         value =  iter->operator *();
    //     }
    // }

    return 0;
}

//[[Rcpp::export]]
void iteratorBenchmark(int numRows, int numCols, double sparsity) {
    // Rcpp::Clock clock;
    //TO ENSURE EVERYTHING WORKS, THE TOTAL SUM OF ALL VALUES IS CALUCLATED AND SHOULD PRINT THE SAME NUMBER FOR EACH ITERATOR
    uint64_t total = 0;
    int value = 0;
    string fileName = "test.bin";


    Eigen::SparseMatrix<int> myMatrix(numRows, numCols);
    myMatrix.reserve(Eigen::VectorXi::Constant(numRows, numCols));
    myMatrix = generateMatrix<int>(numRows, numCols, sparsity);
    myMatrix.makeCompressed(); 

    DeBruinesComp myCompression(myMatrix);

    //////////////////////////////Experimental Iterator//////////////////////////////
    total = 0;
    cout << "Testing Iterator" << endl;
    const_array_iterator<int>* newIter = new const_array_iterator<int>(fileName.c_str());
    // clock.tick("SRLE w/ void*");

    while(newIter->operator bool()) {
        newIter->operator++();
        total += newIter->operator*();
        if(newIter->operator *() != value){
            value =  newIter->operator *();
        }
    }

    cout << "SRLE (E) Total: " << total << endl;
    // clock.tock("SRLE w/ void*");

    //////////////////////////////CSC innerIterator////////////////////////////////
    //generating a large random eigen sparse
    cout << "Testing Eigen" << endl;
    total = 0;



    //begin timing
    // clock.tick("Eigen");
    Eigen::SparseMatrix<int>::InnerIterator it(myMatrix, 0);
    for (int i=0; i<numRows; ++i){
        for (Eigen::SparseMatrix<int>::InnerIterator it(myMatrix, i); it; ++it){
            total += it.value();
        }
    }
    // clock.tock("Eigen");
    cout << "InnerIterator Total: " << total << endl;


    //////////////////////////////GENERIC CSC Iterator////////////////////////////////
    cout << "Testing CSC Iterator" << endl;
    total = 0;
    // clock.tick("CSC");
    GenericCSCIterator<int> iter2 = GenericCSCIterator<int>(myMatrix);
    while(iter2.operator bool()){
        total += iter2.operator *();
        iter2.operator++();
    }
    // clock.tock("CSC");
    cout << "CSC Total: " << total << endl;

    // clock.stop("Iterators");
}


template <typename T>
Eigen::SparseMatrix<T> generateMatrix(int numRows, int numCols, double sparsity){
    //generate a random sparse matrix
    uint64_t favoriteNumber = 515;
    rng randMatrixGen = rng(favoriteNumber);

    Eigen::SparseMatrix<T> myMatrix(numRows, numCols);
    myMatrix.reserve(Eigen::VectorXi::Constant(numRows, numCols));

    for(int i = 0; i < numRows; i++){
        for(int j = 0; j < numCols; j++){
            if(randMatrixGen.draw<int>(i,j, sparsity)){
                myMatrix.insert(i, j) = 10 * randMatrixGen.uniform<double>(j);
            }
        }
    }
    return myMatrix;
}