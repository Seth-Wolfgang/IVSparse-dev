// [[Rcpp::depends(RcppEigen)]]
// [[Rcpp::depends(RcppClock)]]
// #include <RcppEigen.h>
#include "include/SRLE_Lib.hpp"
using namespace std;


//Functions
void iteratorBenchmark(int numRows, int numCols, int sparsity, uint64_t seed);
template <typename T> Eigen::SparseMatrix<T> generateMatrix(int numRows, int numCols, int sparsity, uint64_t seed);


int main() {
    int numRows = 100;
    int numCols = 100;
    int sparsity = 20;
    uint64_t seed = 51;
    iteratorBenchmark(numRows, numCols, sparsity, seed);

    return 1;
}

//[[Rcpp::export]]
void iteratorBenchmark(int numRows, int numCols, int sparsity, uint64_t seed) {
    // Rcpp::Clock clock;
    //TO ENSURE EVERYTHING WORKS, THE TOTAL SUM OF ALL VALUES IS CALUCLATED AND SHOULD PRINT THE SAME NUMBER FOR EACH ITERATOR
    uint64_t total = 0;
    int value = 0;
    string fileName = "test.bin";


    Eigen::SparseMatrix<int> myMatrix(numRows, numCols);
    myMatrix.reserve(Eigen::VectorXi::Constant(numRows, numCols));
    myMatrix = generateMatrix<int>(numRows, numCols, sparsity, seed);
    myMatrix.makeCompressed(); 

    DeBruinesComp myCompression(myMatrix);

    //////////////////////////////Experimental Iterator//////////////////////////////
    total = 0;
    cout << "Testing Iterator" << endl;
    const_array_iterator<int>* newIter = new const_array_iterator<int>(fileName.c_str());
    // clock.tick("SRLE w/ void*");
    vector<int> SRLEVector;
    while(newIter->operator bool()) {
        newIter->operator++();
        total += newIter->operator*();
        SRLEVector.push_back(newIter->operator*());
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
    vector<int> eigenVector;
    // Eigen::SparseMatrix<int>::InnerIterator it(myMatrix, 0);
    for (int i=0; i<numCols; ++i){
        for (Eigen::SparseMatrix<int>::InnerIterator it(myMatrix, i); it; ++it){
            total += it.value();
            eigenVector.push_back(it.value());
        }
    }
        
    sort(SRLEVector.begin(), SRLEVector.end());
    sort(eigenVector.begin(), eigenVector.end());

    cout << "SRLE Vector" << endl;
    for(auto j : SRLEVector){
        cout << j << " ";
    }
    cout << endl << endl;
    cout << "Eigen Vector" << endl;
    for(auto j : eigenVector){
        cout << j << " ";
    }
    cout << endl;

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
Eigen::SparseMatrix<T> generateMatrix(int numRows, int numCols, int sparsity, uint64_t seed){
    //generate a random sparse matrix
    rng randMatrixGen = rng(seed);

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