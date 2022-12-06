// [[Rcpp::depends(RcppEigen)]]
// [[Rcpp::depends(RcppClock)]]
// #include <RcppEigen.h>
#include <chrono>
#include <cstdint>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <cstring>
#include <bits/stdc++.h>
#include <map>
#include <vector>
// #include "const_array_iterator.cpp"
// #include "GenericCSCIterator.cpp"
// #include "matrixCreator.cpp"
// #include "DeBruine's_Compressed_Matrix_Name.cpp"
#include <Eigen/Sparse>
// #include <RcppClock.h>
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

class DeBruinesComp
{

private:
    // ! Magic is currently unused
    uint32_t magic = 1;
    uint8_t delim = 0;

    uint32_t num_rows;
    uint32_t num_cols;
    uint32_t num_vals;

    uint32_t row_t;
    uint32_t col_t;
    uint32_t val_t;

    void *ptr;
    void *data;
    size_t size;

    void allocate()
    {
        // ! Malloc currently allocates much more than needed
        data = malloc(num_vals * val_t * 1.3);
        if (!data)
        {
            cerr << "Malloc Failed" << endl;
        }
        ptr = data;
    }

    uint8_t byte_width(size_t size)
    {
        switch (size)
        {
        case 0 ... 255:
            return 1;
        case 256 ... 65535:
            return 2;
        case 65536 ... 4294967295:
            return 4;
        default:
            return 8;
        }
    }

public:

    /* COO Constructor
        @param *x: pointer to values of COO Matrix
        @param *i: pointer to indices of values in COO matrix
        @param *p: pointer to the column pointers of the COO matrix
        @param val_num: number of non-zero values
        @param row_num: number of rows in the matrix
        @param col_num: number of columns in the matrix
    */
    // ! Assumes column major format (Isn't this just CSC?)
    template <typename values, typename idx_type>
    DeBruinesComp(values *x_v, idx_type *i_v, idx_type *c_point, size_t val_num, size_t row_num, size_t col_num)
    {

        // ! Currently copies data first, should refactor to destroy COO matrix in place
        values x[val_num];
        idx_type i[val_num];
        idx_type p[col_num + 1];

        // create an array that is a copy of x_v and i_v
        for (int k = 0; k < val_num; k++)
        {
            x[k] = x_v[k];
            i[k] = i_v[k];
        }

        // create an array that is a copy of c_point
        for (int k = 0; k < col_num + 1; k++)
        {
            p[k] = c_point[k];
        }

        // Initialize the number of rows, cols, and vals, their types, and allocate space for them
        num_rows = row_num;
        num_cols = col_num;
        num_vals = val_num;

        row_t = byte_width(num_rows);
        col_t = byte_width(num_cols);
        val_t = sizeof(values);

        allocate();
        cout << "Allocated" << endl;
        // ! Create a copy of data here for debugging
        void *debug = data;

        // Construct Metadata
        // rowType       = params[0];
        // nRows         = params[1];
        // colType       = params[2];
        // nCols         = params[3];
        // valueWidth    = params[4];
        // * <row_t, col_t, val_t, num_rows, num_cols, [col_pointers], {...runs...}>
        *static_cast<uint32_t *>(ptr) = row_t;
        // ! better way of static casting 
        *(uint32_t*)(ptr) = row_t;
        ptr = static_cast<uint32_t *>(ptr) + 1;
        *static_cast<uint32_t *>(ptr) = num_rows;
        ptr = static_cast<uint32_t *>(ptr) + 1;
        *static_cast<uint32_t *>(ptr) = col_t;
        ptr = static_cast<uint32_t *>(ptr) + 1;
        *static_cast<uint32_t *>(ptr) = num_cols;
        ptr = static_cast<uint32_t *>(ptr) + 1;
        *static_cast<uint32_t *>(ptr) = val_t;
        ptr = static_cast<uint32_t *>(ptr) + 1;     



        // Create space for col_pointers
        // uint32_t *col_pointers = static_cast<uint32_t *>(ptr);
        // ptr = static_cast<uint32_t *>(ptr) + num_cols;

        // put a delimiter down at end of metadata
        *static_cast<uint32_t *>(ptr) = 0;
        ptr = static_cast<uint32_t *>(ptr) + 1;

        // * Loop through each column and constuct the runs
        for (int l = 0; l < num_cols; l++)
        {

            // for each element in the col
            for (int j = p[l]; j < p[l + 1]; j++)
            {
                if (x[j] != 0)
                {
                    // found value

                    // add value to run
                    *static_cast<values *>(ptr) = x[j];
                    ptr = static_cast<values *>(ptr) + 1;

                    // create an index pointer here
                    uint8_t *index_ptr = static_cast<uint8_t *>(ptr);
                    index_ptr[0] = (uint8_t)sizeof(idx_type);
                    ptr = static_cast<uint8_t *>(ptr) + 1;

                    // add index to run
                    *static_cast<idx_type *>(ptr) = i[j];
                    ptr = static_cast<idx_type *>(ptr) + 1;

                    // loop through rest of column and get indices
                    for (int k = j + 1; k < p[l + 1]; k++)
                    {
                        if (x[k] == x[j])
                        {
                            // found value again

                            // add index to run
                            *static_cast<idx_type *>(ptr) = i[k];
                            ptr = static_cast<idx_type *>(ptr) + 1;

                            // set value to 0
                            x[k] = 0;
                        }
                    }

                    // positive delta encode indices
                    size_t max = 0;
                    idx_type *index = reinterpret_cast<idx_type *>(index_ptr + 1);
                    int num_elements = (int)(static_cast<idx_type *>(ptr) - index);
                    for (int k = num_elements - 1; k > 0; k--)
                    {
                        index[k] = index[k] - index[k - 1];
                        if (index[k] > max)
                        {
                            max = index[k];
                        }
                    }
                    // set index pointer to correct size
                    index_ptr[0] = byte_width(max);
                    // move index pointer by one
                    index_ptr = index_ptr + 1;

                    // create a void pointer to index_ptr
                    void *reducer_ptr = static_cast<void *>(index_ptr);

                    // ! Get rid of switch statemnt with casting a void pointer to a uint8_t pointer
                    // Write over data with indices of new size
                    switch (byte_width(max))
                    {
                    case 1:
                        // cast reducer_ptr to uint8_t
                        reducer_ptr = static_cast<uint8_t *>(reducer_ptr);
                        for (int k = 0; k < num_elements; k++)
                        {
                            *static_cast<uint8_t *>(reducer_ptr) = index[k];
                            reducer_ptr = static_cast<uint8_t *>(reducer_ptr) + 1;
                        }
                        // add delimiter
                        *static_cast<uint8_t *>(reducer_ptr) = delim;
                        reducer_ptr = static_cast<uint8_t *>(reducer_ptr) + 1;
                        break;
                    case 2:
                        // cast reducer_ptr to uint16_t
                        reducer_ptr = static_cast<uint16_t *>(reducer_ptr);
                        for (int k = 0; k < num_elements; k++)
                        {
                            *static_cast<uint16_t *>(reducer_ptr) = index[k];
                            reducer_ptr = static_cast<uint16_t *>(reducer_ptr) + 1;
                        }
                        // add delimiter
                        *static_cast<uint16_t *>(reducer_ptr) = delim;
                        reducer_ptr = static_cast<uint16_t *>(reducer_ptr) + 1;
                        break;
                    case 4:
                        // cast reducer_ptr to uint32_t
                        reducer_ptr = static_cast<uint32_t *>(reducer_ptr);
                        for (int k = 0; k < num_elements; k++)
                        {
                            *static_cast<uint32_t *>(reducer_ptr) = index[k];
                            reducer_ptr = static_cast<uint32_t *>(reducer_ptr) + 1;
                        }
                        // add delimiter
                        *static_cast<uint32_t *>(reducer_ptr) = delim;
                        reducer_ptr = static_cast<uint32_t *>(reducer_ptr) + 1;
                        break;
                    case 8:
                        // cast reducer_ptr to uint64_t
                        reducer_ptr = static_cast<uint64_t *>(reducer_ptr);
                        for (int k = 0; k < num_elements; k++)
                        {
                            *static_cast<uint64_t *>(reducer_ptr) = index[k];
                            reducer_ptr = static_cast<uint64_t *>(reducer_ptr) + 1;
                        }
                        // add delimiter
                        *static_cast<uint64_t *>(reducer_ptr) = delim;
                        reducer_ptr = static_cast<uint64_t *>(reducer_ptr) + 1;
                        break;
                    } // end switch

                    // move ptr to reducer_ptr
                    ptr = reducer_ptr;

                } // end if
            }     // end for (unique value)

            // find distance to beginning of compression and set col_pointer
            // col_pointers[l] = static_cast<uint32_t *>(ptr) - static_cast<uint32_t *>(data);

        } // end for (cols)

        // remove ending zeros
        while (ptr != data && *static_cast<uint8_t *>(ptr) == 0)
        {
            ptr = static_cast<uint8_t *>(ptr) - 1;
        }

        // find size of data in bytes
        cout << "Sizing" << endl;
        cout << static_cast<uint8_t *>(ptr) - static_cast<uint8_t *>(data) << endl;
        // cout << static_cast<uint8_t *>(ptr) - static_cast<uint8_t *>(data) << endl;

        size_t size = static_cast<uint8_t *>(ptr) - static_cast<uint8_t *>(data);

        // resize data to fit
        data = realloc(data, size);

        //  ! crunch col pointers

        // print out data by byte
        // for (int i = 0; i < size; i++)
        // {
        //     printf("%02x ", *static_cast<uint8_t *>(data + i));
        // }

        // write data to file
        cout << "Writing to file..." << endl;
        //print all of data
        // for(int i = 0; i < size; i++){
        //     printf("%02x ", *static_cast<uint8_t *>(data + i));
        // }


        FILE *fp = fopen("test.bin", "wb");
        fwrite(data, size, 1, fp);
        fclose(fp);

    } // end constructor

    /* Eigen Wrapper Constructor
        @param &mat: Eigen Sparse Matrix to compress
    */
    template <typename T>
    DeBruinesComp(Eigen::SparseMatrix<T> &mat){

        //convert mat to CSC
        int* i = new int[mat.nonZeros()]; // rows
        int* p = new int[mat.outerSize()]; // cols
        T* x = new T[mat.nonZeros()]; // values
        
        for(size_t col = 0; col < mat.outerSize(); ++col){
            p[col] = mat.outerIndexPtr()[col];
            for(typename Eigen::SparseMatrix<T>::InnerIterator it(mat, col); it; ++it){
                i[it.index()] = it.row();
                x[it.index()] = it.value();
            }
        }



        //print number of values in p

    /* COO Constructor
        @param *x: pointer to values of COO Matrix
        @param *i: pointer to indices of values in COO matrix
        @param *p: pointer to the column pointers of the COO matrix
        @param val_num: number of non-zero values
        @param row_num: number of rows in the matrixouterSi
        @param col_num: number of columns in the matrix
    */
 
        for(int j = 0; j < mat.nonZeros(); j++){
            cout << "value: "  << x[j] << " row: " << i[j] << " col: " << p[j] << endl;
        }
        cout << endl << endl;


        DeBruinesComp(x, i, p, mat.nonZeros(), mat.rows(), mat.cols());
    }

    ~DeBruinesComp()
    {
        free(data);
    }

    // Write to file
};


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
    //turn into a sub class of skyler's constructor
    private:
        uint32_t rowType;       //= params[1];
        uint32_t nRows;         //= params[2];
        uint32_t colType;       //= params[3];
        uint32_t nCols;         //= params[4];
        uint32_t valueWidth;    //= params[5];
        uint8_t newIndexWidth; //basically how many bytes we read, NOT ACTUALLY THE TYPE
        char* end;
        char* fileData;
        void* arrayPointer;
        uint64_t index = 0;
        T value;
        uint64_t sum = 0;

    public:
      

   const_array_iterator(const char* filePath) {

        //set up the iterator
        readFile(filePath);
        //read first 28 bytes of fileData put it into params -> metadata
        uint32_t params[7];
        
        memcpy(&params, arrayPointer, 24); //28 is subject to change depending on magic bytes
        arrayPointer+=24; //first delimitor is 4 bytes

        rowType       = params[0];
        nRows         = params[1];
        colType       = params[2];
        nCols         = params[3];
        valueWidth    = params[4];
        cout << "valueWidth: " << valueWidth << endl;

        memcpy(&value, arrayPointer, valueWidth);
        arrayPointer += valueWidth;
        newIndexWidth =  static_cast<int>(*static_cast<uint8_t*>(arrayPointer));
        arrayPointer++; //this should make it point to first index

        cout << "value: " << value << endl;
        cout << "newIndexWidth: " << newIndexWidth << endl;

        // for debugging
         for(int i = 0; i < 5; i++) {
             cout << i << " " << params[i] << endl;
        }


    }//end of constructor


    //todo make this return type T 
    T& operator * () {return value;}; 
    
    //EXPERIMENTAL INCREMENT OPERATOR -> NOT DECREMENT
    const uint64_t operator --() {
        uint64_t newIndex = 0; 
        printf("newIndexWidth: %d\n", newIndexWidth);

        switch (newIndexWidth){
            case 1:
                newIndex = static_cast<uint64_t>(*static_cast<uint8_t*>(arrayPointer));
                break;
            case 2:
                newIndex =  static_cast<uint64_t>(*static_cast<uint8_t*>(arrayPointer));
                break;
            case 4:
                newIndex =  static_cast<uint64_t>(*static_cast<uint8_t*>(arrayPointer));
                break;
            case 8:
                newIndex =  static_cast<uint64_t>(*static_cast<uint8_t*>(arrayPointer));
                break;
            default:
                cout << static_cast<int>(*static_cast<uint8_t*>(arrayPointer)) << endl;
                cerr << "Invalid width" << endl;
                exit(-1);
                break;
        }
        cout << "arrayPointer position: " <<  ((char*)arrayPointer - fileData) << endl; 
        cout << "arrayPointer value: " << *(uint8_t*)arrayPointer << endl;
        cout << "valueWidth " << valueWidth << endl;


        arrayPointer += newIndexWidth;

        if(newIndex == 0 && index != 0){ //todo change that
            
            memcpy(&value, arrayPointer, valueWidth);
            arrayPointer += valueWidth; 
            
            memcpy(&newIndexWidth, arrayPointer, 1);
            arrayPointer++;
            
            cout << endl << "value: " << value << endl;
            cout << "newIndexWidth: " << newIndexWidth << endl;
            
            memset(&index, 0, 8);
            memcpy(&index, arrayPointer, newIndexWidth);

        }
        return index += newIndex;
    }

    // template<typename indexType> 
    const uint64_t operator++() { 
        //TODO template metaprogramming
        //todo through an exception if we request something smaller than the size of the index

        uint64_t newIndex = 0; //get rid of in future versions

        memcpy(&newIndex, arrayPointer, newIndexWidth);
        arrayPointer += newIndexWidth;
        sum += value;

        if(newIndex == 0 && index != 0){ //change that
            
            memcpy(&value, arrayPointer, valueWidth);
            arrayPointer += valueWidth; 
            
            memcpy(&newIndexWidth, arrayPointer, 1);
            arrayPointer++;
            
            cout << endl << "value: " << value << endl;
            cout << "newIndexWidth: " << *(uint8_t*)newIndexWidth << endl;
            
            memset(&index, 0, 8);
            memcpy(&index, arrayPointer, newIndexWidth);

        }
        return index += newIndex;

    }


    // equality operator
    operator bool() { return end >= arrayPointer;} //change to not equal at the end


    // reads in the file and stores it in a char* 
    // inline void readFile(string filePath){ 
    //     ifstream fileStream;
    //     fileStream.open(filePath, ios::binary | ios::out);
        
    //     fileStream.seekg(0, ios::end);
    //     int sizeOfFile = fileStream.tellg();
    //     fileData = (char*)malloc(sizeof(char*)*sizeOfFile);

    //     fileStream.seekg(0, ios::beg);
    //     fileStream.read(fileData, sizeOfFile);
        
    //     fileStream.close();

    //     arrayPointer = fileData;
    //     end = fileData + sizeOfFile;
    //     }

    //marginally faster 
    inline void readFile(const char* filePath){
        //read a file using the C fopen function and store to fileData
        FILE* file = fopen(filePath, "rb");
        
        fseek(file, 0, SEEK_END);
        int sizeOfFile = ftell(file);
        fileData = (char*)malloc(sizeof(char*)*sizeOfFile);

        fseek(file, 0, SEEK_SET);

        fread(fileData, sizeOfFile, 1, file);
        fclose(file);
        // cout << "Size of file: " << sizeOfFile << endl;
        arrayPointer = fileData;
        end = fileData + sizeOfFile;
    }
};

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
    // myCompression.print();
    // myCompression.write("test.bin");

    // cout << "Testing SRLE" << endl;
    // const_array_iterator<int>* iter = new const_array_iterator<int>(fileName.c_str());
    // clock.tick("SRLE w/ memcpy");
    // while(iter->operator bool()) {
    //     iter->operator++();
    //     total += iter->operator*();
    //     if(iter->operator *() != value){
    //         value =  iter->operator *();
    //     }
    // }
    // clock.tock("SRLE w/ memcpy");
    // cout << "SRLE (N) Total: " << total << endl;
    // cout << "SRLE Total: " << total << endl;

    //////////////////////////////Experimental Iterator//////////////////////////////
    total = 0;
    cout << "Testing Experimental Iterator" << endl;
    const_array_iterator<int>* newIter = new const_array_iterator<int>(fileName.c_str());
    // clock.tick("SRLE w/ void*");
    while(newIter->operator bool()) {
        newIter->operator--();
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