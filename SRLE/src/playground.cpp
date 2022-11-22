//[[Rcpp::depends(RcppEigen)]]
#include <RcppEigen.h>
#include <chrono>
// #include "const_array_iterator.cpp"
// #include "GenericCSCIterator.cpp"
// #include "matrixCreator.cpp"
// #include "DeBruine's_Compressed_Matrix_Name.cpp"
// #include <Eigen/Sparse>
// #include <Rcpp//clock.h>
// #include <Rcpp.h>

using namespace std;
//using namespace //Rcpp;
// void calcTime(chrono::steady_//clock::time_point begin, chrono::steady_//clock::time_point end);
template<typename T> class const_array_iterator;
template<typename T> class GenericCSCIterator;
template<typename T> class matrixCreator;
class rng;

// template<typename T>
// Eigen::SparseMatrix<T> generateMatrix(int numRows, int numCols, double sparsity);
void iteratorBenchmark(int numRows, int numCols, double sparsity);


// int main() {
//     int numRows = 1000;
//     int numCols = 1000;
//     double sparsity = 20;
//     iteratorBenchmark(numRows, numCols, sparsity);

//     return 0;
// }


// void calcTime(chrono::steady_//clock::time_point begin, chrono::steady_//clock::time_point end){
//     std::Rcout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[µs]" << std::endl;
//     std::Rcout << "Time difference = " << std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count() << "[ns]" << std::endl;
//     std::Rcout << "Time difference = " << std::chrono::duration_cast<std::chrono::milliseconds> (end - begin).count() << "[ms]" << std::endl;

// }




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

class rng {
   private:
    uint64_t state;

   public:
    rng(uint64_t state) : state(state) {}

    void advance_state() {
        state ^= state << 19;
        state ^= state >> 7;
        state ^= state << 36;
    }

    uint64_t operator*() const {
        return state;
    }

    uint64_t rand() {
        uint64_t x = state ^ (state << 38);
        x ^= x >> 13;
        x ^= x << 23;
        
        return x;
    }

    uint64_t rand(uint64_t i) {
        // advance i
        i ^= i << 19;
        i ^= i >> 7;
        i ^= i << 36;

        // add i to state
        uint64_t x = state + i;

        // advance state
        x ^= x << 38;
        x ^= x >> 13;
        x ^= x << 23;

        return x;
    }

    uint64_t rand(uint64_t i, uint64_t j) {
        uint64_t x = rand(i);

        // advance j
        j ^= j >> 7;
        j ^= j << 23;
        j ^= j >> 8;

        // add j to state
        x += j;

        // advance state
        x ^= x >> 7;
        x ^= x << 53;
        x ^= x >> 4;

        return x;
    }

    template <typename T>
    T sample(T max_value) {
        return rand() % max_value;
    }

    template <typename T>
    T sample(uint64_t i, T max_value) {
        return rand(i) % max_value;
    }

    template <typename T>
    T sample(uint64_t i, uint64_t j, T max_value) {
        return rand(i, j) % max_value;
    }

    template <typename T>
    bool draw(T probability) {
        return sample(probability) == 0;
    }

    template <typename T>
    bool draw(uint64_t i, T probability) {
        return sample(i, probability) == 0;
    }

    template <typename T>
    bool draw(uint64_t i, uint64_t j, T probability) {
        sample(i, j, probability);
        return sample(i, j, probability) == 0;
    }

    template <typename T>
    double uniform() {
        T x = (T)rand() / UINT64_MAX;
        return x - std::floor(x);
    }

    template <typename T>
    double uniform(uint64_t i) {
        T x = (T)rand(i) / UINT64_MAX;
        return x - std::floor(x);
    }

    template <typename T>
    double uniform(uint64_t i, uint64_t j) {
        T x = (T)rand(i, j) / UINT64_MAX;
        return x - std::floor(x);
    }
};

template<typename T>
class const_array_iterator {
    //todo:
    //clean the vocabulary
    private:
        uint32_t magicByteSize; //= params[0];
        uint32_t rowType;       //= params[1];
        uint32_t nRows;         //= params[2];
        uint32_t colType;       //= params[3];
        uint32_t nCols;         //= params[4];
        uint32_t valueWidth;    //= params[5];
        uint32_t oldIndexType;  //= params[6];        
        int newIndexWidth; //basically how many bytes we read, NOT ACTUALLY THE TYPE
        char* end;
        char* fileData;
        char* arrayPointer;
        uint64_t index = 0;
        T value;
        uint64_t sum = 0;

    public:
      
    //constructor that takes in a file path containing the data we're going over
    const_array_iterator(string filePath) {

        //set up the iterator
        readFile(filePath);

        // read first 28 bytes of fileData put it into params -> metadata
        uint32_t params[7];
        // vector<uint32_t> metaDataForMyIter(8);

        memcpy(&params, arrayPointer, 28); //28 is subject to change depending on magic bytes
        arrayPointer+=32; //first delimitor is 4 bytes
        magicByteSize = params[0];
        rowType       = params[1];
        nRows         = params[2];
        colType       = params[3];
        nCols         = params[4];
        valueWidth    = params[5];
        oldIndexType  = params[6];

        memcpy(&value, arrayPointer, valueWidth);
        arrayPointer += valueWidth;
        memcpy(&newIndexWidth, arrayPointer, 1);
        arrayPointer++; //this should make it point to first index

        // cout << "value: " << value << endl;
        // cout << "newIndexWidth: " << newIndexWidth << endl;

        // //for debugging
        //  for(int i = 0; i < 7; i++) {
        //      cout << i << " " << params[i] << endl;
        // }


    }//end of constructor


    //constructor that takes in the data rather than reading the file
    // const_array_iterator(char* data){
    //     arrayPointer = data;
    //     uint32_t params[7];
    //     memcpy(&params, arrayPointer, 28); //28 is subject to change depending on magic bytes
    //     arrayPointer+=32; //first delimitor is 4 bytes

    //     magicByteSize = params[0];
    //     rowType       = params[1];
    //     nRows         = params[2];
    //     colType       = params[3];
    //     nCols         = params[4];
    //     valueWidth    = params[5];
    //     oldIndexType  = params[6];

    //     memcpy(&value, arrayPointer, valueWidth);
    //     arrayPointer += valueWidth;
    //     memcpy(&newIndexWidth, arrayPointer, 1);
    //     arrayPointer++; //this should make it point to first index

    // }


    //todo make this return type T 
    T& operator * () {return value;}; 
    
    uint64_t getSum() {return sum;};

    //template<typename indexType> 
    const uint64_t operator++() { 
        //todo through an exception if we request something smaller than the size of the index
        uint64_t newIndex = 0; 
        memcpy(&newIndex, arrayPointer, newIndexWidth);

        arrayPointer += newIndexWidth;
        sum += value;

        if(newIndex == 0 && index != 0){ //change that
            
            memcpy(&value, arrayPointer, valueWidth);
            arrayPointer += valueWidth; 
            
            memcpy(&newIndexWidth, arrayPointer, 1);
            arrayPointer++;
            
            // cout << endl << "value: " << value << endl;
            // cout << "newIndexWidth: " << newIndexWidth << endl;
            
            memset(&index, 0, 8);
            memcpy(&index, arrayPointer, newIndexWidth);

        }
        return index += newIndex;

    }


    // equality operator
    operator bool() {
        //cout << "end " << &end << endl;
        //cout << "arr " << &arrayPointer << endl;
        return end >= arrayPointer;} //change to not equal at the end


    // reads in the file and stores it in a char* 
    inline void readFile(string filePath){ 
        ifstream fileStream;
        fileStream.open(filePath, ios::binary | ios::out);
        
        fileStream.seekg(0, ios::end);
        int sizeOfFile = fileStream.tellg();
        fileData = (char*)malloc(sizeof(char*)*sizeOfFile);

        fileStream.seekg(0, ios::beg);
        fileStream.read(fileData, sizeOfFile);
        
        fileStream.close();

        arrayPointer = fileData;
        end = fileData + sizeOfFile;
        Rcpp::Rcout << "Size: " << sizeOfFile << endl;
        
        }

    // // //marginally faster 
    // inline void readFile(string filePath){
    //     //read a file using the C fopen function and store to fileData
    //     FILE* file = fopen(filePath.c_str(), "rb");
    //     if (file == nullptr){Rcpp::stop("Cannot open file");}
    //     fseek(file, 0, SEEK_END);
    //     int sizeOfFile = ftell(file);
    //     fileData = (char*)malloc(sizeof(char*)*sizeOfFile);
    //     fseek(file, 0, SEEK_SET);
    //     fread(fileData, sizeOfFile, 1, file);
    //     fclose(file);
    //     // cout << "Size of file: " << sizeOfFile << endl;
    //     arrayPointer = fileData;
    //     end = fileData + sizeOfFile;
    //     if(arrayPointer == nullptr){Rcpp::stop("arrayPointer is null");}
    //     Rcpp::Rcout << "ArrayPointer: " << *(char*)&arrayPointer[0] << endl;
    //     Rcpp::Rcout << "File size: " << sizeof(fileData) << endl;
    // }
};

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

// Eigen::SparseMatrix<int> generateMatrix(int numRows, int numCols, double sparsity){
//     //generate a random sparse matrix
//     uint64_t favoriteNumber = 11515616;
//     rng randMatrixGen = rng(favoriteNumber);

//     Eigen::SparseMatrix<int> myMatrix(numRows, numCols);
//     myMatrix.reserve(Eigen::VectorXi::Constant(numRows, numCols));

//     for(int i = 0; i < numRows; i++){
//         for(int j = 0; j < numCols; j++){
//             if(randMatrixGen.draw<int>(i,j, sparsity)){
//                 myMatrix.insert(i, j) = 100 * randMatrixGen.uniform<double>(j);
//             }
//         }
//     }
//     return myMatrix;
// }

//[[Rcpp::export]]
void iteratorBenchmark(int numRows, int numCols, double sparsity) {
    Rcpp::Rcout << "test" << endl;
    //Rcpp:://clock //clock;
    //My Iterator test
    //TO ENSURE EVERYTHING WORKS, THE TOTAL SUM OF ALL VALUES IS CALUCLATED AND SHOULD PRINT THE SAME NUMBER FOR EACH ITERATOR
    uint64_t total = 0;
    int value = 0;
    string fileName = "input.bin";


    Eigen::SparseMatrix<int> myMatrix(numRows, numCols);
    myMatrix.reserve(Eigen::VectorXi::Constant(numRows, numCols));
    myMatrix = generateMatrix<int>(numRows, numCols, sparsity);
    myMatrix.makeCompressed(); 

    // DeBruinesComp myCompression(myMatrix);
    // Rcpp::Rcout << "test1" << endl;


    const_array_iterator<int>* iter = new const_array_iterator<int>(fileName);
    
    ////clock.tick("SRLE");
    while(iter->operator bool()) {
        iter->operator++();
        if(iter->operator *() != value){
            // Rcout << iter->operator *() << endl;
            total =  iter->operator *();
        }
    }
    // clock.tock("SRLE");
    Rcpp::Rcout << "SRLE Total: " << total << endl;

    //////////////////////////////CSC innerIterator////////////////////////////////
    //generating a large random eigen sparse
    // Rcout << "Testing Eigen" << endl;
    total = 0;
    Rcpp::Rcout << "test2" << endl;



    //begin timing
    //clock.tick("Eigen");
    Eigen::SparseMatrix<int>::InnerIterator it(myMatrix, 0);
    for (int i=0; i<numRows; ++i){
        for (Eigen::SparseMatrix<int>::InnerIterator it(myMatrix, i); it; ++it){
            total += it.value();
        }
    }
    // //clock.tock("Eigen");
    Rcpp::Rcout << "InnerIterator Total: " << total << endl;


    //////////////////////////////GENERIC CSC Iterator////////////////////////////////
    Rcpp::Rcout << "Testing CSC Iterator" << endl;
    total = 0;
    //clock.tick("CSC");
    GenericCSCIterator<int> iter2 = GenericCSCIterator<int>(myMatrix);
    while(iter2.operator bool()){
        total += iter2.operator *();
        iter2.operator++();
    }
    //clock.tock("CSC");
    Rcpp::Rcout << "CSC Total: " << total << endl;

    //clock.stop("Iterators");
}