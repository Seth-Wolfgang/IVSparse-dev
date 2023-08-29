#include "benchmarkFunctions.h"
#include "../../misc/matrix_creator.cpp"
#include <tuple>
#include <unordered_map>
#include <functional>
#include <string>
#include <fstream>
#include <iostream>

void benchmark(char* filepath, std::function<double(std::string, std::unordered_map<std::string, double>&)> func);
void loadMatrix(std::vector<std::tuple<uint, uint, double>>& data, std::function<double(std::string, std::unordered_map<std::string, double>&)> func, char* filepath);
double returnDouble(std::string val, std::unordered_map<std::string, double>& myMap);
double classifyDouble(std::string val, std::unordered_map<std::string, double>& myMap);
void load_mm_matrix(std::vector<std::tuple<uint, uint, double>>& data, char* filename);
void generateMatrix(std::vector<std::tuple<uint, uint, double>>& data, int numRows, int numCols, int sparsity, uint64_t seed, uint64_t maxValue);
template <typename T, typename indexType, int compressionLevel>
uint64_t buildMatrix(std::vector<std::tuple<uint, uint, double>>& data, uint rows, uint cols, uint nnz);

template <typename T, typename indexType, int compressionLevel>
void averageRedundancy(IVSparse::SparseMatrix<T, indexType, compressionLevel>& matrix);

#define ITERATIONS 10

int main() {

    // benchmark("../datasets/tags.csv", classifyDouble);
    std::cout << std::endl;
    std::cout << std::endl;
    // benchmark("../datasets/ratings.csv", returnDouble);
    benchmark("../datasets/PR02R.mtx", returnDouble);
    return 0;
}

// have a function that takes in a double and a map and returns a double
void loadMatrix(std::vector<std::tuple<uint, uint, double>>& data, std::function<double(std::string, std::unordered_map<std::string, double>&)> func, char* filename) {
    std::unordered_map<std::string, double> map;

    FILE* file;
    file = fopen(filename, "r");
    char line[1024];

    uint i = 0;
    while (fgets(line, 1024, file)) {
        // split the row into 3 seperate values
        char* val1 = strtok(line, ",");
        char* val2 = strtok(NULL, ",");
        char* val3 = strtok(NULL, ",");
        std::string val3String(val3);

        // add the values to the data vector
        data.push_back(std::make_tuple(atoi(val2), atoi(val1), func(val3String, map)));
    }

    // copy data to data vector
    fclose(file);
}

double returnDouble(std::string val, std::unordered_map<std::string, double>& myMap) {

    return atof(val.c_str());
}

double classifyDouble(std::string val, std::unordered_map<std::string, double>& myMap) {
    if (myMap.find(val) != myMap.end()) {
        return myMap[val];
    }
    else {
        myMap.insert(std::make_pair(val, myMap.size()));
        return static_cast<double>(myMap[val]);
    }
}

void benchmark(char* filepath, std::function<double(std::string, std::unordered_map<std::string, double>&)> func) {
    std::vector<std::tuple<uint, uint, double>> data;

    // loadMatrix(data, func, filepath);
    std::cout << "Loading matrix... " << filepath << std::endl;
    load_mm_matrix(data, filepath);
    // generateMatrix(data, 500000, 10000, 99, 1, 1);
    std::cout << "Done loading matrix" << std::endl;
    data.resize(data.size());

    // loop through the tuples and count the number of unique values

    // construct a dictionary of the unique values
    std::map<uint, uint> uniqueValues;

    for (uint i = 0; i < data.size(); i++) {
        uniqueValues.insert(std::pair<uint, uint>(std::get<2>(data.at(i)), 0));
    }

    // print the number of unique values
    std::cout << "Number of unique values: " << uniqueValues.size() << std::endl;

    uint cols = (uint)[&data] {
        int max = 0;
        for (uint i = 0; i < data.size(); i++) {
            if (std::get<1>(data.at(i)) > max) {
                max = std::get<1>(data.at(i));
            }
        }
        return max + 1;
        }
    ();

    int rows = (uint)[&data] {
        int max = 0;
        for (uint i = 0; i < data.size(); i++) {
            if (std::get<0>(data.at(i)) > max) {
                max = std::get<0>(data.at(i));
            }
        }
        return max;
        }
    ();

    uint size = data.size();
    double density = (double)(static_cast<double>(size) / (double)(static_cast<double>(rows) * static_cast<double>(cols)));
    std::cout << "Rows: " << rows << std::endl;
    std::cout << "Cols: " << cols << std::endl;
    std::cout << "Size: " << size << std::endl;
    std::cout << "Density: " << density << std::endl;
    std::cout << "gigabytes: " << (double)(static_cast<double>(size) * 16) / (double)(1024 * 1024 * 1024) << std::endl;
    // print all of data
    //  for (uint i = 0; i < data.size(); i++) {
    //      std::cout << std::get<0>(data.at(i)) << ", " << std::get<1>(data.at(i)) << ", " << std::get<2>(data.at(i)) << std::endl;
    //  }

    std::cout << "//////////////////////////////////////////////////////////// In: " << filepath << " ////////////////////////////////////////////////////////////" << std::endl;
    std::cout << "CSC: " << std::endl;
    uint64_t csf1Size = buildMatrix<double, uint, 1>(data, rows, cols, size);
    std::cout << "VCSC: " << std::endl;
    uint64_t csf2Size = buildMatrix<double, uint, 2>(data, rows, cols, size);
    std::cout << "IVCSC: " << std::endl;
    uint64_t csf3Size = buildMatrix<double, uint, 3>(data, rows, cols, size);

    std::cout << "CSC: " << csf1Size << std::endl;
    std::cout << "CSF2: " << csf2Size << std::endl;
    std::cout << "IVCSC: " << csf3Size << std::endl;

    std::cout << std::endl;
    std::cout << "Ratios:" << std::endl;

    std::cout << "CSC " << (double)csf1Size / (size * 16) << std::endl;
    std::cout << "VCSC: " << (double)csf2Size / (size * 16) << std::endl;
    std::cout << "IVCSC: " << (double)csf3Size / (size * 16) << std::endl;
}

template <typename T, typename indexType, int compressionLevel>
void averageRedundancy(IVSparse::SparseMatrix<T, indexType, compressionLevel>& matrix) {
    const int numRows = matrix.rows();
    const int numCols = matrix.cols();
    std::cout << "Fetching redundancy" << std::endl;
    int colsWithValues = 0;
    double totalRedundancy = 0.0;
    std::unordered_map<double, double> uniqueValues_overall;


    for (int j = 0; j < numCols; ++j) {
        double totalValues = 0;
        double redundancy = 0;
        std::unordered_map<double, double> uniqueValues;

        for (typename IVSparse::SparseMatrix<T, indexType, compressionLevel>::InnerIterator it(matrix, j); it; ++it) {
            uniqueValues.insert(std::pair<double, int>(it.value(), 0));
            uniqueValues_overall.insert(std::pair<double, int>(it.value(), 0));
            totalValues++;
        }

        if (totalValues == 0 || uniqueValues.size() == 0)
            continue;
        else if (uniqueValues.size() == 1)
            redundancy = 1;
        else
            redundancy = 1 - (uniqueValues.size() / totalValues);
        totalRedundancy += redundancy;
        colsWithValues++;
    }
    std::cout << "Unique values in whole matrix: " << uniqueValues_overall.size() << std::endl;

    std::cout << "Avg Redundancy: " << totalRedundancy / static_cast<double>(colsWithValues) << std::endl;
}

void load_mm_matrix(std::vector<std::tuple<uint, uint, double>>& data, char* filename) {
    int retCode;
    MM_typecode matcode;
    FILE* f;
    int rows, cols, nonzeros;
    int i, * I, * J;
    double* val;

    // Check for correct number of arguments

    if ((f = fopen(filename, "r")) == NULL) {
        std::cout << "\033[31;1;4mError: Could not open matrix file!\033[0m" << std::endl;
        exit(1);
    }

    // Makes sure the banner can be read
    if (mm_read_banner(f, &matcode) != 0) {
        std::cout << "\033[31;1;4mError: Could not process Matrix Market banner.\033[0m" << std::endl;
        exit(1);
    }

    // Reads the dimensions and number of nonzeros
    if ((retCode = mm_read_mtx_crd_size(f, &rows, &cols, &nonzeros)) != 0) {
        std::cout << "\033[31;1;4mError: Could not read matrix dimensions.\033[0m" << std::endl;
        exit(1);
    }

    // Allocate memory for the matrix
    I = (int*)malloc(sizeof(uint));
    J = (int*)malloc(sizeof(uint));
    val = (double*)malloc(sizeof(double));
    data.reserve(nonzeros);
    // Read the matrix
    std::cout << "Done allocating memory" << std::endl;
    for (i = 0; i < nonzeros; i++) {
        fscanf(f, "%d %d %lg\n", &I[0], &J[0], &val[0]);
        data.push_back(std::make_tuple(I[0]--, J[0]--, val[0]));
    }

    // Close the file
    if (f != stdin)
        fclose(f);

    // Free the memory
    free(I);
    free(J);
    free(val);

    std::cout << "Loaded: " << filename << std::endl;

    return;
}

void generateMatrix(std::vector<std::tuple<uint, uint, double>>& data, int numRows, int numCols, int sparsity, uint64_t seed, uint64_t maxValue) {
    // generate a random sparse matrix
    rng randMatrixGen = rng(seed);
    data.reserve(numRows * 2);
    std::unordered_map<int, int> uniqueValues;


    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            if (randMatrixGen.draw<int>(i, j, sparsity)) {
                // int size = uniqueValues.size();
                // int newVal = rand();
                // uniqueValues.insert(std::pair<double, int>(newVal, 0));

                // while (uniqueValues.size() == size) {
                //     newVal = rand();
                //     uniqueValues.insert(std::pair<double, int>(newVal, 0));
                // }
                // data.push_back(std::make_tuple(i, j, newVal));
                data.push_back(std::make_tuple(i, j, 1));

            }
        }
    }
}

template <typename T, typename indexType, int compressionLevel>
uint64_t buildMatrix(std::vector<std::tuple<uint, uint, double>>& data, uint rows, uint cols, uint nnz) {

    IVSparse::SparseMatrix<T, indexType, compressionLevel> matrix(data, rows, cols, nnz);
    
    if constexpr (compressionLevel == 3) {
        averageRedundancy<double, uint, 3>(matrix);
    }

    uint64_t size = matrix.byteSize();
    return size;
}
