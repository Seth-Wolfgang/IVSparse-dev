#include "benchmarkFunctions.h"
#include "../../misc/matrix_creator.cpp"

template <typename T>
void sizeTest(int rows, int cols, std::vector<std::vector<uint64_t>>& data, int sparsity, int redundancy);
void printDataToFile(std::vector<std::vector<uint64_t>>& data);

int main(int argc, char** argv) {
    std::vector<std::vector<uint64_t>> data(10000);

    // if (argc != 2) {
    //     sizeTest<int>(1000, 1000, data);
    // }
    // else if (argc == 3) {
    std::cout << "Running with " << argv[1] << " rows and " << argv[2] << " columns" << std::endl;

#pragma omp parallel for schedule(dynamic)
    for (int sparsity = 1; sparsity <= 100; sparsity++) {
        for (int redundancy = 1; redundancy <= 100; redundancy++) {
            sizeTest<int>(atoi(argv[1]), atoi(argv[2]), data, sparsity, redundancy);
        }
    }

    // }
    printDataToFile(data);

    return 1;
}

void printDataToFile(std::vector<std::vector<uint64_t>>& data) {
    FILE* file;
    if (access("../sizeData.csv", F_OK) != 0) {
        std::cout << "Creating sizeData.csv" << std::endl;
        file = fopen("../sizeData.csv", "a");
        fprintf(file, "%s\n", "Matrix Number, Sparsity, Redundancy, CSF1 Size, CSF2 Size, CSF3 Size");
        fclose(file);
    }

    file = fopen("../sizeData.csv", "a");
    for (int i = 0; i < data.size(); i++) {
        fprintf(file, "%lu, %lu, %lu, %lu, %lu, %lu\n", data.at(i).at(0), data.at(i).at(1), data.at(i).at(2), data.at(i).at(3), data.at(i).at(4), data.at(i).at(5));
    }
}


template <typename T>
void sizeTest(int rows, int cols, std::vector<std::vector<uint64_t>>& data, int sparsity, int redundancy) {
    Eigen::SparseMatrix<T> eigen;
    int spot = 100 * (sparsity - 1) + redundancy - 1;

    eigen = generateMatrix<int>(rows, cols, sparsity, redundancy, redundancy);
    CSF::SparseMatrix<T, INDEX_TYPE, 1> csf1(eigen);
    CSF::SparseMatrix<T, INDEX_TYPE, 2> csf2(eigen);
    CSF::SparseMatrix<T, INDEX_TYPE, 3> csf3(eigen);

    data.at(spot).push_back(spot);
    data.at(spot).push_back(sparsity);
    data.at(spot).push_back(redundancy);
    data.at(spot).push_back(static_cast<uint64_t>(csf1.byteSize()));
    data.at(spot).push_back(static_cast<uint64_t>(csf2.byteSize()));
    data.at(spot).push_back(static_cast<uint64_t>(csf3.byteSize()));
    std::cout << "Completed matrix: " << spot << " of 10000" << std::endl;
}


