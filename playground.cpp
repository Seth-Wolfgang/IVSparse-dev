#include <iostream>
#include "IVSparse/SparseMatrix"
#include "misc/matrix_creator.cpp"
#include <chrono>

#define DATA_TYPE int64_t
#define INDEX_TYPE int

template <typename T>
bool compareMatrices(Eigen::Matrix<T, -1, -1> mat1, Eigen::Matrix<T, -1, -1> mat2, Eigen::Matrix<T, -1, -1> mat3);

//  For my convenience
//  clear; rm a.out; g++ test.cpp; ./a.out

int main() {

    int rows = 1000;
    int cols = 1000;
    int sparsity = 5;
    uint64_t seed = 522;
    int maxVal = 10;
    int numIterations = 10;
    const bool isColMajor = true;

    Eigen::initParallel();

    Eigen::Matrix<DATA_TYPE, -1, -1> testDense1 = Eigen::Matrix<DATA_TYPE, -1, -1>::Random(rows, cols);
    Eigen::Matrix<DATA_TYPE, -1, -1> testDense2 = Eigen::Matrix<DATA_TYPE, -1, -1>::Random(rows, cols + 1);
    Eigen::Matrix<DATA_TYPE, -1, -1> testDense3 = Eigen::Matrix<DATA_TYPE, -1, -1>::Random(rows + 1, cols);

    for( int i = 0; i < rows; i++) {
        for( int j = 0; j < cols; j++) {
            testDense1(i, j) = testDense1(i, j) % maxVal;
            testDense2(i, j) = testDense2(i, j) % maxVal;
            testDense3(i, j) = testDense3(i, j) % maxVal;
        }
    }

    Eigen::SparseMatrix<DATA_TYPE> testEigenDense1 = testDense1.sparseView();
    Eigen::SparseMatrix<DATA_TYPE> testEigenDense2 = testDense2.sparseView();
    Eigen::SparseMatrix<DATA_TYPE> testEigenDense3 = testDense3.sparseView();

    Eigen::Matrix<DATA_TYPE, -1, -1> testEigenDense1Transpose = testDense1.transpose();
    Eigen::Matrix<DATA_TYPE, -1, -1> testEigenDense2Transpose = testDense2.transpose();
    Eigen::Matrix<DATA_TYPE, -1, -1> testEigenDense3Transpose = testDense3.transpose();

    IVSparse::VCSC<DATA_TYPE, int> vcsc1(testEigenDense1);
    IVSparse::VCSC<DATA_TYPE, int> vcsc2(testEigenDense2);
    IVSparse::VCSC<DATA_TYPE, int> vcsc3(testEigenDense3);

    IVSparse::IVCSC<DATA_TYPE> ivcsc1(testEigenDense1);
    IVSparse::IVCSC<DATA_TYPE> ivcsc2(testEigenDense2);
    IVSparse::IVCSC<DATA_TYPE> ivcsc3(testEigenDense3);

    std::vector<uint64_t> timeEigen;
    std::vector<uint64_t> timeVCSC;
    std::vector<uint64_t> timeIVCSC;

    timeEigen.reserve(numIterations);
    timeVCSC.reserve(numIterations);
    timeIVCSC.reserve(numIterations);

    for (int i = 0; i < numIterations; i++) {

        std::chrono::time_point<std::chrono::system_clock> start, end;

        start = std::chrono::system_clock::now();
        Eigen::Matrix<DATA_TYPE, -1, -1> resultEigen = testEigenDense1 * testEigenDense1Transpose;
        end = std::chrono::system_clock::now();
        std::cout << "Eigen: " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << std::endl;
        timeEigen.push_back(std::chrono::duration_cast<std::chrono::microseconds>(end - start).count());

        start = std::chrono::system_clock::now();
        Eigen::Matrix<DATA_TYPE, -1, -1> resultVCSC = vcsc1 * testEigenDense1Transpose;
        end = std::chrono::system_clock::now();
        std::cout << "VCSC: " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << std::endl;
        timeVCSC.push_back(std::chrono::duration_cast<std::chrono::microseconds>(end - start).count());

        start = std::chrono::system_clock::now();
        Eigen::Matrix<DATA_TYPE, -1, -1> resultIVCSC = ivcsc1 * testEigenDense1Transpose;
        end = std::chrono::system_clock::now();

        std::cout << "IVCSC: " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << std::endl << std::endl;
        timeIVCSC.push_back(std::chrono::duration_cast<std::chrono::microseconds>(end - start).count());
        assert(compareMatrices<DATA_TYPE>(resultEigen, resultVCSC, resultIVCSC));

    }

    uint64_t sumEigen = 0;
    uint64_t sumVCSC = 0;
    uint64_t sumIVCSC = 0;

    for(int i = 0; i < timeEigen.size(); i++) {
        sumEigen += timeEigen[i];
        sumVCSC += timeVCSC[i];
        sumIVCSC += timeIVCSC[i];
    }

    sumEigen /= numIterations;
    sumVCSC /= numIterations;
    sumIVCSC /= numIterations;

    std::cout << "Summary: " << std::endl;
    std::cout << "Eigen: " << sumEigen << std::endl;
    std::cout << "VCSC: " << sumVCSC << std::endl;
    std::cout << "IVCSC: " << sumIVCSC << std::endl;





    return 0;
}

template <typename T>
bool compareMatrices(Eigen::Matrix<T, -1, -1> mat1, Eigen::Matrix<T, -1, -1> mat2, Eigen::Matrix<T, -1, -1> mat3) {

    if (mat1.cols() != mat2.cols() || mat2.cols() != mat3.cols()) {
        std::cout << "mat1: " << mat1.cols() << " mat2: " << mat2.cols() << " mat3: " << mat3.cols() << std::endl;
        return false;
    }
    if (mat1.rows() != mat2.rows() || mat2.rows() != mat3.rows()) {
        std::cout << "mat1: " << mat1.rows() << " mat2: " << mat2.rows() << " mat3: " << mat3.rows() << std::endl;
        return false;
    }
    if (mat1.sum() != mat2.sum() || mat2.sum() != mat3.sum()) {
        std::cout << "mat1: " << mat1.sum() << " mat2: " << mat2.sum() << " mat3: " << mat3.sum() << std::endl;
        return false;
    }

    for (int i = 0; i < mat3.rows(); i++) {
        for (int j = 0; j < mat3.cols(); j++) {
            if (mat1(i, j) != mat2(i, j) || mat2(i, j) != mat3(i, j)) {
                std::cout << "mat1: " << mat1(i, j) << " mat2: " << mat2(i, j) << " mat3: " << mat3(i, j) << std::endl;
                return false;
            }
        }
    }
    return true;

}
