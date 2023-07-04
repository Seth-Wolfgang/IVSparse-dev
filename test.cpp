#include <iostream>
#include "CSF/SparseMatrix"
#include "misc/matrix_creator.cpp"
#include <chrono>
// #define EIGEN_DONT_PARALLELIZE
#define DATA_TYPE double

template<typename T, typename indexT>
void sizeTest(int iterations);

template <typename T, typename indexT, int compressionLevel> void iteratorTest();
void getMat(Eigen::SparseMatrix<int>& myMatrix_e);

// For my convenience
//  clear; rm a.out; g++ test.cpp; ./a.out

int main() {
    int rows = 100;
    int cols = 100;
    int sparsity = 99;
    uint64_t seed = 522;
    int maxVal = 10053425;

    // Eigen::SparseMatrix<DATA_TYPE> eigen(rows, cols);
    // eigen = generateMatrix<DATA_TYPE>(rows, cols, sparsity, seed, maxVal);
    // std::cout << eigen << std::endl;

    // Eigen::MatrixXi mat(6, 6);
    // mat << 0, 6, 4,  1, -1, 4,
    //        3, 9, 0,  0, -6, 4,
    //        0, 0,-5,-10,  0, 1,
    //        9, 8, 7,  6,  5, 4,
    //        0, 0, 0,  0,  0, 4,
    //        0, 0, 0,  0,  0,-1;

    // Eigen::Vector<DATA_TYPE, 6> eigenVec(6,1);
    // eigenVec << 0,
    //             3,
    //             0,
    //             9,
    //             0, 
    //             0;

    // int rowData[] = {0, 1, 2, 3, 4, 5};
    // int colData[] = {0, 1, 2, 2, 4, 5};
    // DATA_TYPE valData[] = {1, 2, 3, 4, 5, 6};

    // std::vector<std::tuple<int, int, DATA_TYPE>> data;

    // for(int i = 0; i < 6; i++) {
    //     data.push_back(std::make_tuple(rowData[i], colData[i], valData[i]));
    // }

    // CSF::SparseMatrix<DATA_TYPE, int, 1> csf(data, 6, 6, 6);

    // std::cout << csf << std::endl;

    // //create an eigen triplet from rowData, colData, and valData
    // Eigen::SparseMatrix<DATA_TYPE> mat(6, 6);
    // mat.reserve(Eigen::VectorXi::Constant(6, 6));
    // for (int i = 0; i < 6; i++) {
    //     mat.insert(rowData[i], colData[i]) = valData[i];
    // }
    // mat.makeCompressed();
    // std::cout << std::endl; 
    // std::cout << mat << std::endl;


    // Eigen::SparseMatrix<DATA_TYPE> eigen = mat.sparseView();
    // Eigen::SparseVector<DATA_TYPE> eigenVector = eigenVec.sparseView();

    // CSF::SparseMatrix<DATA_TYPE, uint32_t, 1> csf(eigen);
    // CSF::SparseMatrix<DATA_TYPE, uint32_t, 3> csf3(eigen);
    // CSF::SparseMatrix<DATA_TYPE, uint32_t, 2> csf2(eigen);
    // uint64_t eigenSize = eigen.nonZeros() * sizeof(double) + eigen.nonZeros() * sizeof(uint32_t) + (eigen.outerSize() + 1) * sizeof(uint32_t);

    // std::cout << "Eigen size: " << eigenSize << std::endl;
    // std::cout << "CSF2 size: " << csf2.byteSize() << std::endl;
    // std::cout << "CSF3 size: " << csf3.byteSize() << std::endl;

    // std::cout << "Ratios -> CSF2: " << (double)csf2.byteSize() / eigenSize << " \tCSF3: " << (double)csf3.byteSize() / eigenSize << std::endl;

    // std::cout << csf2 << std::endl;
    // std::cout << csf3 << std::endl;



    // std::cout << csf2 << std::endl;

    // for (int i = 0; i < csf2.cols(); i++) {
    //     for (typename CSF::SparseMatrix<DATA_TYPE, uint32_t, 2>::InnerIterator it(csf2, i); it; ++it) {
    //         std::cout << it.value() << " ";
    //     }
    //     std::cout << std::endl;
    // }
    //     std::cout << std::endl;
    //     std::cout << std::endl;

    // for (int i = 0; i < csf3.cols(); i++) {
    //     for (typename CSF::SparseMatrix<DATA_TYPE, uint32_t, 3>::InnerIterator it(csf3, i); it; ++it) {
    //         std::cout << it.value() << " ";
    //     }
    //     std::cout << std::endl;
    // }

    iteratorTest<int, int, 3>();
    iteratorTest<int, int, 2>();
    iteratorTest<int, int, 1>();

    return 1;
}

template<typename T, typename indexT>
void sizeTest(int iterations) {
    int rows = 100;
    int cols = 100;
    int sparsity = 9;
    uint64_t seed = 1;
    int maxVal = 1000;

    std::cout << "Rows: " << rows << " \nCols: " << cols << " \nSparsity: " << sparsity << " \nSeed: " << seed << " \nMaxVal " << maxVal << std::endl;

    std::vector < uint64_t > csf2Sizes;
    std::vector < uint64_t > csfSizes;

    #pragma omp parallel for num_threads(15)
    for (int i = 0; i < iterations; i++) {
        // create an eigen sparse matrix
        Eigen::SparseMatrix<T> eigen(rows, cols);
        // getMat(eigen);
        eigen = generateMatrix<T>(rows, cols, sparsity, rand(), maxVal);
        // std::cout << eigen << std::endl;

        // create a CSF sparse matrix
        CSF::SparseMatrix<T, indexT, 3> csf(eigen);
        CSF::SparseMatrix<T, indexT, 2> csf2(eigen);

        csfSizes.push_back(csf.compressionSize());
        csf2Sizes.push_back(csf2.compressionSize());
    }

    uint64_t avgCSF2Size = 0;
    uint64_t avgCSFSize = 0;
    for (int i = 0; i < csf2Sizes.size(); i++) {
        avgCSF2Size += csf2Sizes[i];
        avgCSFSize += csfSizes[i];
    }
    avgCSF2Size /= csf2Sizes.size();
    avgCSFSize /= csfSizes.size();


    std::cout << "CSF: " << avgCSFSize << std::endl;
    std::cout << "CSF2: " << avgCSF2Size << std::endl;
    // uint64_t eigenSize = eigen.nonZeros() * sizeof(double) + eigen.nonZeros() * sizeof(uint32_t) + (eigen.outerSize() + 1) * sizeof(uint32_t);
    // std::cout << "eigen size: " << eigenSize << std::endl;
}

template <typename T, typename indexT, int compressionLevel>
void iteratorTest() {

    int numRows = 1000;//rand() % 1000 + 10;
    int numCols = 1000;//rand() % 1000 + 10;
    int sparsity = 10;//rand() % 50 + 1;
    uint64_t seed = 1;//rand();

    // Initialize the random matrix
    Eigen::SparseMatrix<T> eigen(numRows, numCols);
    eigen.reserve(Eigen::VectorXi::Constant(numCols, numRows));
    eigen = generateMatrix<T>(numRows, numCols, sparsity, rand(), 10);
    eigen.makeCompressed();

    //Create random matrix and vector to multiply with
    // Eigen::Matrix<T, -1, -1> randMatrix = Eigen::Matrix<T, -1, -1>::Random(numCols, numRows);
    // Eigen::Matrix<T, -1, 1> randVector = Eigen::Matrix<T, -1, 1>::Random(numCols);

    // Eigen::VectorXd randVector = Eigen::VectorXd::Random(numCols);

    //Create CSF matrix and an eigen dense matrix
    CSF::SparseMatrix<T, indexT, compressionLevel> csfMatrix(eigen);

    //Create a dense matrix to store the result of the multiplication
    std::chrono::time_point<std::chrono::system_clock> start, end;
    // Eigen::Matrix<T, -1, -1>  csfDenseMatrix;
    // Eigen::Matrix<T, -1, -1> eigenDenseMatrix;

    //Vectors to store times for averages
    std::vector<uint64_t> timesForNew;
    std::vector<uint64_t> timesForOld;
    uint64_t ours = 0;
    uint64_t old = 0;
    for (int i = 0; i < 1; i++) {

        //Measure time for CSF matrix
        T sum = 0;
        start = std::chrono::system_clock::now();

        for (int i = 0; i < csfMatrix.outerSize(); ++i) {
            for (typename CSF::SparseMatrix<T, indexT, compressionLevel>::InnerIterator it(csfMatrix, i); it; ++it) {
                sum += it.value();
            }
        }

        end = std::chrono::system_clock::now();
        timesForNew.push_back(std::chrono::duration_cast<std::chrono::microseconds>(end - start).count());
        ours = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

        // std::cout << "CSF:\n " << csfDenseMatrix << std::endl;

        //Measure time for Eigen matrix
        T sum2 = 0;
        start = std::chrono::system_clock::now();
        for (int i = 0; i < eigen.outerSize(); ++i) {
            for (typename Eigen::SparseMatrix<T>::InnerIterator it(eigen, i); it; ++it) {
                sum2 += it.value();
            }
        }
        end = std::chrono::system_clock::now();
        timesForOld.push_back(std::chrono::duration_cast<std::chrono::microseconds>(end - start).count());
        old = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        assert(sum2 == sum);
        // std::cout << "(CSF): " << ours << "(Eigen): " << old << std::endl;

        // std::cout << "Eigen:\n " << eigenDenseMatrix << std::endl;
    }
    //take average of timesforNew and timesForOld
    uint64_t duration = 0;
    uint64_t duration2 = 0;
    for (int i = 0; i < timesForNew.size(); i++) {
        duration += timesForNew[i];
        duration2 += timesForOld[i];
    }
    duration /= timesForNew.size();
    duration2 /= timesForOld.size();

    std::cout << "Version 1 (CSF): " << duration << " version 2 (Eigen): " << duration2 << std::endl;


    // Eigen::MatrixXd controlMatrix = eigen * randMatrix;

    // T sum_e = denseMatrix.sum();
    // T sumCSF = csfDenseMatrix.sum();
    // T sumEigen = eigenDenseMatrix.sum();

    // std::cout << "Eigen: " << sumEigen << " CSF: " << sumCSF << std::endl;

    // if (sumCSF == 0 || sumEigen == 0 || sumCSF != sumEigen) {
    //     std::cout << "Rows: " << numRows << " Cols: " << numCols << " Sparsity: " << sparsity << " Seed: " << seed << std::endl;
    //     std::cout << "sum_csf: " << sumCSF << " Eigen: " << sumEigen << std::endl;
    //     assert(sumCSF == sumEigen);
    // }
}


void getMat(Eigen::SparseMatrix<int>& myMatrix_e) {
    // declare an eigen sparse matrix of both types

    // col 0
    myMatrix_e.insert(0, 0) = 1;
    myMatrix_e.insert(2, 0) = 2;
    myMatrix_e.insert(3, 0) = 3;
    myMatrix_e.insert(5, 0) = 1;
    myMatrix_e.insert(6, 0) = 3;
    myMatrix_e.insert(7, 0) = 8;

    // col 1
    myMatrix_e.insert(3, 1) = 1;
    myMatrix_e.insert(4, 1) = 3;
    myMatrix_e.insert(5, 1) = 8;
    myMatrix_e.insert(6, 1) = 7;
    myMatrix_e.insert(8, 1) = 1;
    myMatrix_e.insert(9, 1) = 2;

    // col 2
    myMatrix_e.insert(0, 2) = 2;
    myMatrix_e.insert(2, 2) = 2;
    myMatrix_e.insert(5, 2) = 1;
    myMatrix_e.insert(7, 2) = 3;
    myMatrix_e.insert(9, 2) = 1;

    // col 3

    // col 4
    myMatrix_e.insert(0, 4) = 1;
    myMatrix_e.insert(3, 4) = 1;
    myMatrix_e.insert(4, 4) = 3;
    myMatrix_e.insert(6, 4) = 2;
    myMatrix_e.insert(7, 4) = 1;

    // col 5
    myMatrix_e.insert(0, 5) = 8;
    myMatrix_e.insert(2, 5) = 1;
    myMatrix_e.insert(3, 5) = 4;
    myMatrix_e.insert(5, 5) = 3;
    myMatrix_e.insert(7, 5) = 1;
    myMatrix_e.insert(8, 5) = 2;

    // col 6
    myMatrix_e.insert(3, 6) = 6;
    myMatrix_e.insert(5, 6) = 1;
    myMatrix_e.insert(7, 6) = 3;

    // col 7
    myMatrix_e.insert(2, 7) = 3;
    myMatrix_e.insert(4, 7) = 4;
    myMatrix_e.insert(5, 7) = 1;
    myMatrix_e.insert(8, 7) = 2;
    myMatrix_e.insert(9, 7) = 3;

    // col 8
    myMatrix_e.insert(0, 8) = 2;
    myMatrix_e.insert(2, 8) = 1;
    myMatrix_e.insert(3, 8) = 2;
    myMatrix_e.insert(5, 8) = 3;
    myMatrix_e.insert(7, 8) = 3;
    myMatrix_e.insert(9, 8) = 1;

    // col 9
    myMatrix_e.insert(3, 9) = 2;
    myMatrix_e.insert(4, 9) = 4;
    myMatrix_e.insert(7, 9) = 1;
    myMatrix_e.insert(8, 9) = 1;

    myMatrix_e.makeCompressed();

}

