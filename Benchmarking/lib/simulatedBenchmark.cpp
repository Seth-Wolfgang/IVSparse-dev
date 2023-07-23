#include "benchmarkFunctions.h"
#include "../../misc/matrix_creator.cpp"

template <typename T>
void sizeTest(int rows, int cols, std::vector<std::vector<double>>& data, double sparsity, double redundancy);
void printDataToFile(std::vector<std::vector<double>>& data);
template <typename T> void generateMatrix(std::vector<std::tuple<uint, uint, double>>& data, int numRows, int numCols, double sparsity, uint64_t seed, T maxValue);

int main(int argc, char** argv) {
    std::vector<std::vector<double>> data(100000);

    std::cout << "Running with " << argv[1] << " rows and " << argv[2] << " columns" << std::endl;
    if (argc != 3) {
        argv    = (char**)malloc(3 * sizeof(char*));
        argv[1] = (char*)malloc(5 * sizeof(char));
        argv[2] = (char*)malloc(5 * sizeof(char));
        argv[1] = "1000";
        argv[2] = "1000";
    }

    #pragma omp parallel for schedule(dynamic)
    for (int redundancy = 1; redundancy <= 1000; redundancy++) {
        sizeTest<double>(atoi(argv[1]), atoi(argv[2]), data, (0.1 * sparsity), 0.1 * redundancy);
    }

    printDataToFile(data);

    return 1;
}

void printDataToFile(std::vector<std::vector<double>>& data) {
    FILE* file;
    file = fopen("../sizeData.csv", "a");

    fprintf(file, "%s\n", "Matrix Number, Sparsity, Redundancy, CSF1 Size, CSF2 Size, CSF3 Size");
    for (int i = 0; i < data.size(); i++) {
        fprintf(file, "%lu, %f, %f, %lu, %lu, %lu\n", data.at(i).at(0), data.at(i).at(1), data.at(i).at(2), data.at(i).at(3), data.at(i).at(4), data.at(i).at(5));
    }

}

template <typename T>
void sizeTest(int rows, int cols, std::vector<std::vector<double>>& data, double sparsity, double redundancy) {
    int spot = 100 * ((10 * sparsity) - 1) + (10 * redundancy) - 1;
    std::vector<std::tuple<uint, uint, double>> matrixData;
    generateMatrix<double>(matrixData, rows, cols, sparsity, 1, redundancy);

    eigen = generateMatrix<int>(rows, cols, sparsity, redundancy, redundancy);
    IVSparse::SparseMatrix<T, INDEX_TYPE, 1> csf1(eigen);
    IVSparse::SparseMatrix<T, INDEX_TYPE, 2> csf2(eigen);
    IVSparse::SparseMatrix<T, INDEX_TYPE, 3> csf3(eigen);

    data.at(spot).push_back((double)spot);
    data.at(spot).push_back(rows);
    data.at(spot).push_back(cols);
    data.at(spot).push_back(sparsity);
    data.at(spot).push_back(redundancy);
    data.at(spot).push_back((double)csf1.byteSize());
    data.at(spot).push_back((double)csf2.byteSize());
    data.at(spot).push_back((double)csf3.byteSize());
    printf("%6.0lf %8.2lf %8.2lf %10.1lf %10.1lf %10.1lf\n", data.at(spot).at(0), data.at(spot).at(1), data.at(spot).at(2), data.at(spot).at(3), data.at(spot).at(4), data.at(spot).at(5));

}

template <typename T>
void generateMatrix(std::vector<std::tuple<uint, uint, double>>& data, int numRows, int numCols, double sparsity, uint64_t seed, T maxValue) {
    rng randMatrixGen = rng(seed);
    data.reserve(numRows * 2);

    // #pragma openmp parallel for threadNum(4)
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            if (randMatrixGen.draw<double>(i, j, sparsity)) {
                if constexpr (std::is_floating_point<T>::value)
                    data.push_back(std::make_tuple(i, j, fmod((double)rand(), maxValue) + 0.1));
                else
                    data.push_back(std::make_tuple(i, j, rand() % maxValue + 1));
            }
        }
    }
}
