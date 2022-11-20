//[[Rcpp::depends(RcppClock)]]
//[[Rcpp::depends(RcppEigen)]]
//[[Rcpp::depends(Rcpp)]]
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <iterator>
#include <cstddef>
#include <fstream>
#include<algorithm> 
#include <Eigen/Sparse>

using namespace std;

//template<typename T> <- return what user wants https://en.cppreference.com/w/cpp/language/partial_specialization
template<typename T>
class GenericCSCIterator {
    //todo:
    //clean the vocabulary
    private:
        vector<int> row = vector<int>();
        vector<int> col = vector<int>();
        vector<T> values = vector<T>();
        int* rowPtr;
        int* colPtr;
        T* valuePtr;
        int* end;



    public:

    GenericCSCIterator(Eigen::SparseMatrix<T> myMatrix) {
        for (int i=0; i < myMatrix.outerSize(); ++i)
            for(typename Eigen::SparseMatrix<T>::InnerIterator it(myMatrix, i); it; ++it){               
                row.push_back(it.row());
                col.push_back(it.col());
                values.push_back(it.value());
            }
        rowPtr = &row[0];
        colPtr = &col[0];
        valuePtr = &values[0];
        end = rowPtr + row.size();
    }


    //todo make this return type T 
    T& operator * () {return *valuePtr;}
    
    int getRow () {return *rowPtr;}

    int getCol () {return *colPtr;}

    const int operator++() { 
        //Iterate over myMatrix
        rowPtr++;
        valuePtr++;
        return *rowPtr;
    }

    // equality operator
    operator bool() {return rowPtr != end;}

};