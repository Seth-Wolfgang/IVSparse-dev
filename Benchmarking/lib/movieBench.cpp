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

template <typename T, typename indexType, int compressionLevel>
void averageRedundancy(CSF::SparseMatrix<T, indexType, compressionLevel>& matrix);

#define ITERATIONS 10

int main() {

    // benchmark("../datasets/tags.csv", classifyDouble);
    std::cout << std::endl;
    std::cout << std::endl;
    // benchmark("../datasets/ratings.csv", returnDouble);
    benchmark("../datasets/filtered_feature_bc_matrix.mtx", returnDouble);
    return 0;

}

//have a function that takes in a double and a map and returns a double
void loadMatrix(std::vector<std::tuple<uint, uint, double>>& data, std::function<double(std::string, std::unordered_map<std::string, double>&)> func, char* filename) {
    std::unordered_map<std::string, double> map;

    FILE* file;
    file = fopen(filename, "r");
    char line[1024];


    uint i = 0;
    while (fgets(line, 1024, file)) {
        //split the row into 3 seperate values
        char* val1 = strtok(line, ",");
        char* val2 = strtok(NULL, ",");
        char* val3 = strtok(NULL, ",");
        std::string val3String(val3);

        //add the values to the data vector
        data.push_back(std::make_tuple(atoi(val2), atoi(val1), func(val3String, map)));

    }

    //copy data to data vector
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

    load_mm_matrix(data, filepath);

    uint cols = (uint)[&data] {
        int max = 0;
        for (uint i = 0; i < data.size(); i++) {
            if (std::get<1>(data.at(i)) > max) {
                max = std::get<1>(data.at(i));
            }
        }
        return max + 1;
        }();

        int rows = (uint)[&data] {
            int max = 0;
            for (uint i = 0; i < data.size(); i++) {
                if (std::get<0>(data.at(i)) > max) {
                    max = std::get<0>(data.at(i));
                }
            }
            return max;
            }();

            uint size = data.size();
            std::cout << "Rows: " << rows << std::endl;
            std::cout << "Cols: " << cols << std::endl;
            std::cout << "Size: " << size << std::endl;
            std::cout << "Density: " << (double)((double)size / (rows * cols)) << std::endl;
            //print all of data
            // for (uint i = 0; i < data.size(); i++) {
            //     std::cout << std::get<0>(data.at(i)) << ", " << std::get<1>(data.at(i)) << ", " << std::get<2>(data.at(i)) << std::endl;
            // }

            std::cout << "//////////////////////////////////////////////////////////// In: " << filepath << " ////////////////////////////////////////////////////////////" << std::endl;
            uint64_t csf1Size = CSF::SparseMatrix<double, uint, 1>(data, rows, cols, size).byteSize();
            std::cout << "CSF1 Size: " << csf1Size << std::endl;
            uint64_t csf2Size = CSF::SparseMatrix<double, uint, 2>(data, rows, cols, size).byteSize();
            std::cout << "CSF2 Size: " << csf2Size << std::endl;
            CSF::SparseMatrix<double, uint, 3> csf3(data, rows, cols, size);
            std::cout << "CSF3 Size: " << csf3.byteSize() << std::endl;

            averageRedundancy<double, uint, 3>(csf3);
            std::cout << "\nRatios: " << std::endl;
            std::cout << "CSF2: " << (double)((double)csf2Size / csf1Size) << std::endl;
            std::cout << "CSF3: " << (double)((double)csf3.byteSize() / csf1Size) << std::endl;
}

template <typename T, typename indexType, int compressionLevel>
void averageRedundancy(CSF::SparseMatrix<T, indexType, compressionLevel>& matrix) {
    const int numRows = matrix.rows();
    const int numCols = matrix.cols();
    int colsWithValues = 0;
    double totalRedundancy = 0.0;

    for (int j = 0; j < numCols; ++j) {
        double totalValues = 0;
        std::unordered_map<double, double> uniqueValues;

        for (typename CSF::SparseMatrix<T, indexType, compressionLevel>::InnerIterator it(matrix, j); it; ++it) {
            uniqueValues.insert(std::pair<double, int>(it.value(), 0));
            totalValues++;
        }
        if (totalValues == 0 || uniqueValues.size() == 0) {
            continue;
        }
        colsWithValues++;
        double redundancy = (uniqueValues.size() / totalValues);
        totalRedundancy += redundancy;
    }

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
    if (f != stdin) fclose(f);

    // Free the memory
    free(I);
    free(J);
    free(val);

    std::cout << "Loaded: " << filename << std::endl;
}

