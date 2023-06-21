#include <iostream>
#include "CSF/SparseMatrix"
#include "misc/matrix_creator.cpp"
#include <chrono>
#include "Benchmarking/lib/armadillo"
// #define EIGEN_DONT_PARALLELIZE
#define DATA_TYPE int

template<typename T, typename indexT>
void sizeTest(int iterations);

template <typename T, typename indexT, int compressionLevel> void iteratorTest();
void getMat(Eigen::SparseMatrix<int>& myMatrix_e);

int main() {
    int rows = 1000;
    int cols = 1000;
    int sparsity = 10;
    uint64_t seed = 1;
    int maxVal = 1;

    // create an eigen sparse matrix
    // Eigen::SparseMatrix<DATA_TYPE> eigen(rows, cols);
    // getMat(eigen);
    // eigen = generateMatrix<DATA_TYPE>(rows, cols, 1, 1, 9);
    // std::cout << eigen << std::endl;

    Eigen::MatrixXi mat(6, 6);
    mat << 0, 3, 4, 1,-1, 4,
           3, 9, 0, 0,-6, 0,
           0, 0,-5,-10, 0, 1,
           9, 8, 7, 6, 5, 4,
           0, 0, 0, 0, 0, 0,
           0, 0, 0, 0, 0,-1;

    Eigen::SparseMatrix<DATA_TYPE> eigen = mat.sparseView();

    //put all of eigen into an eigenTriplet
    std::vector<Eigen::Triplet<DATA_TYPE>> eigenTriplet;
    for (int i = 0; i < eigen.outerSize(); ++i) {
        for (typename Eigen::SparseMatrix<DATA_TYPE>::InnerIterator it(eigen, i); it; ++it) {
            eigenTriplet.push_back(Eigen::Triplet<DATA_TYPE>(it.row(), it.col(), it.value()));
        }
    }

    arma::mat* aMat = new arma::mat(6, 6);
    for (auto& triplet : eigenTriplet) {
        aMat->at(triplet.row(), triplet.col()) = triplet.value();
    }
    arma::sp_mat armaMat(*aMat);
    delete aMat;

    arma::vec result = armaMat * arma::ones<arma::vec>(6);

    for(int i = 0; i < result.size(); i++) {
        std::cout << result[i] << std::endl;
    }
    
    std::cout << std::endl;

    // create a CSF sparse matrix
    CSF::SparseMatrix<DATA_TYPE, int, 3> csf(eigen);
    CSF::SparseMatrix<DATA_TYPE, int, 2> csf2(eigen);

    std::vector csf2Result = csf2.innerSum();

    for(int i = 0; i < csf2Result.size(); i++) {
        std::cout << csf2Result[i] << std::endl;
    }

    // csf2.setPerformanceVecs(true);
    // std::cout << "Sum: " << csf2.sum() << std::endl;


    // make a vector of the CSF matrix
    // CSF::SparseMatrix<int, int, 3>::Vector skyVec(csf, 0);

    // multiply the CSF by 3
    // csf *= 3;

    // std::cout << "CSF: " << csf.compressionSize() << std::endl;
    // std::cout << "CSF2: " << csf2.compressionSize() << std::endl;
    // uint64_t eigenSize = eigen.nonZeros() * sizeof(double) + eigen.nonZeros() * sizeof(uint32_t) + (eigen.outerSize() + 1) * sizeof(uint32_t);
    // std::cout << "eigen size: " << eigenSize << std::endl;

    // Eigen::IOFormat clean(Eigen::StreamPrecision, Eigen::DontAlignCols, " ", "\n", "", "", "", "");

    // std::cout << Eigen::MatrixXd(eigen).format(clean) << std::endl << std::endl;

    // std::cout << csf << std::endl;



    //rows * columns * (end pointers + start pointers) + values * data type + metadata 

    //rows * columns (2 * pointers) * outersize + (sizeof(valueType) + sizeof(delimitor)) * outersize 


    // std::cout << csf << std::endl;
    // std::cout << eigen << std::endl;


    // * CSF Iterator Testing * //
    // #pragma omp parallel for num_threads(15)
    // for (int i = 0; i < 1; i++) {
    //     iteratorTest<double, uint64_t, 3>();
    //     std::cout << "Test " << i << " passed" << std::endl;
    // }

    // for(int i = 0; i < 1; i++) {
    //     std::cout << "i: " << i << std::endl;
    //     sizeTest<int, uint64_t>(10);
    // }


    return 1;
}

template<typename T, typename indexT>
void sizeTest(int iterations) {
    int rows = 10000;
    int cols = 10000;
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
    int sparsity = 20;//rand() % 50 + 1;
    uint64_t seed = 1;//rand();

    // Initialize the random matrix
    Eigen::SparseMatrix<T> eigen(numRows, numCols);
    eigen.reserve(Eigen::VectorXi::Constant(numCols, numRows));
    eigen = generateMatrix<T>(numRows, numCols, sparsity, rand(), 10);
    eigen.makeCompressed();

    //Create random matrix and vector to multiply with
    Eigen::Matrix<T, -1, -1> randMatrix = Eigen::Matrix<T, -1, -1>::Random(numCols, numRows);
    // Eigen::Matrix<T, -1, 1> randVector = Eigen::Matrix<T, -1, 1>::Random(numCols);

    Eigen::VectorXd randVector = Eigen::VectorXd::Random(numCols);

    //Create CSF matrix and an eigen dense matrix
    CSF::SparseMatrix<T, indexT, compressionLevel> csfMatrix(eigen);

    //Create a dense matrix to store the result of the multiplication
    std::chrono::time_point<std::chrono::system_clock> start, end;
    Eigen::Matrix<T, -1, -1>  csfDenseMatrix;
    Eigen::Matrix<T, -1, -1> eigenDenseMatrix;

    //Vectors to store times for averages
    std::vector<uint64_t> timesForNew;
    std::vector<uint64_t> timesForOld;
    uint64_t ours = 0;
    uint64_t old = 0;
    for (int i = 0; i < 10000; i++) {

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
        std::cout << "(CSF): " << ours << "(Eigen): " << old << std::endl;

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
    T sumCSF = csfDenseMatrix.sum();
    T sumEigen = eigenDenseMatrix.sum();

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

