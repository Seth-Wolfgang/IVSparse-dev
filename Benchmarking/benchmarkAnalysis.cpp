/**
 * @brief A simple class to store and record basic statistical data of benchmarking results
 * @author Seth Wolfgang
 * @date 2023-03-22
 */

#include <stdio.h>
#include <vector>
#include <unistd.h>
#include <stdlib.h>
#include <inttypes.h>

class BenchAnalysis {
private:

    typedef struct matrixInfo {
        uint32_t matrixNum;
        uint32_t matrixRows;
        uint32_t matrixCols;
        uint64_t matrixNonzeros;
        double matrixRedundancy;
        double matrixDensity;
    } matrix;

    matrix* myMatrix;

    // CSF 1 Data
    std::vector<uint64_t> CSFConstructorTimes = {};
    std::vector<uint64_t> CSFInnerIteratorTimes;
    std::vector<uint64_t> CSFScalarMultiplicationTimes;
    std::vector<uint64_t> CSFVectorMultiplicationTimes;
    std::vector<uint64_t> CSFMatrixMultiplicationTimes;

    // CSF 2 Data
    std::vector<uint64_t> CSF2ConstructorTimes;
    std::vector<uint64_t> CSF2InnerIteratorTimes;
    std::vector<uint64_t> CSF2ScalarMultiplicationTimes;
    std::vector<uint64_t> CSF2VectorMultiplicationTimes;
    std::vector<uint64_t> CSF2MatrixMultiplicationTimes;

    // CSF 3 Data
    std::vector<uint64_t> CSF3ConstructorTimes;
    std::vector<uint64_t> CSF3InnerIteratorTimes;
    std::vector<uint64_t> CSF3ScalarMultiplicationTimes;
    std::vector<uint64_t> CSF3VectorMultiplicationTimes;
    std::vector<uint64_t> CSF3MatrixMultiplicationTimes;

    // Eigen data
    std::vector<uint64_t> EigenConstructorTimes;
    std::vector<uint64_t> EigenInnerIteratorTimes;
    std::vector<uint64_t> EigenScalarMultiplicationTimes;
    std::vector<uint64_t> EigenVectorMultiplicationTimes;
    std::vector<uint64_t> EigenMatrixMultiplicationTimes;


    //memory usage (in bytes)
    std::vector<uint64_t> CSFMemoryUsage;
    std::vector<uint64_t> CSF2MemoryUsage;
    std::vector<uint64_t> CSF3MemoryUsage;
    std::vector<uint64_t> EigenMemoryUsage;


public:

    // Constructor
    BenchAnalysis(std::vector<uint32_t> matrixData, double matrixRedundancy, double matrixDensity) {
        myMatrix = (matrix*)malloc(sizeof(matrix));

        //TODO: Look back over rb file format
        // myMatrix->matrixNum = matrixNum;
        // myMatrix->matrixRows = matrixRows;
        // myMatrix->matrixCols = matrixCols;
        // myMatrix->matrixNonzeros = matrixNonzeros;
        myMatrix->matrixRedundancy = matrixRedundancy;
        myMatrix->matrixDensity = matrixDensity;


        //Checking to see if the files we're writing to exist in the directory
        //if not, we write the headers at the top of the file.
        FILE* file;
        if (access("timeData", F_OK) != 0) {
            file = fopen("matrixAttributes.csv", "a");
            fprintf(file, "Matrix Number, Matrix Rows, Matrix Cols, Matrix Nonzeros, Matrix Redundancy, Matrix Density");
            fclose(file);
        }

        if (access("timeData", F_OK) != 0) {
            file = fopen("timeData.csv", "a");
            fprintf(file, "CSF 1 Constructor Time, CSF 1 Inner Iterator Time, CSF 1 Scalar Multiplication Time, CSF 1 Vector Multiplication Time, CSF 1 Matrix Multiplication Time, CSF 2 Constructor Time, CSF 2 Inner Iterator Time, CSF 2 Scalar Multiplication Time, CSF 2 Vector Multiplication Time, CSF 2 Matrix Multiplication Time, CSF 3 Constructor Time, CSF 3 Inner Iterator Time, CSF 3 Scalar Multiplication Time, CSF 3 Vector Multiplication Time, CSF 3 Matrix Multiplication Time, Eigen Constructor Time, Eigen Inner Iterator Time, Eigen Scalar Multiplication Time, Eigen Vector Multiplication Time, Eigen Matrix Multiplication Time, Max CSF 1 Constructor Time, Max CSF 1 Inner Iterator Time, Max CSF 1 Scalar Multiplication Time, Max CSF 1 Vector Multiplication Time, Max CSF 1 Matrix Multiplication Time, Max CSF 2 Constructor Time, Max CSF 2 Inner Iterator Time, Max CSF 2 Scalar Multiplication Time, Max CSF 2 Vector Multiplication Time, Max CSF 2 Matrix Multiplication Time, Max CSF 3 Constructor Time, Max CSF 3 Inner Iterator Time, Max CSF 3 Scalar Multiplication Time, Max CSF 3 Vector Multiplication Time, Max CSF 3 Matrix Multiplication Time, Max Eigen Constructor Time, Max Eigen Inner Iterator Time, Max Eigen Scalar Multiplication Time, Max Eigen Vector Multiplication Time, Max Eigen Matrix Multiplication Time\n");
        }

    }

    // Destructor
    ~BenchAnalysis() {
        if (myMatrix != NULL)
            free(myMatrix);
    }

    void pushData(std::vector<uint64_t> data) {

        // Constructor times
        EigenConstructorTimes.push_back(data.at(0));
        CSFConstructorTimes.push_back(data.at(1));
        CSF2ConstructorTimes.push_back(data.at(2));
        CSF3ConstructorTimes.push_back(data.at(3));

        // Inner iterator times
        EigenInnerIteratorTimes.push_back(data.at(4));
        CSFInnerIteratorTimes.push_back(data.at(5));
        CSF2InnerIteratorTimes.push_back(data.at(6));
        CSF3InnerIteratorTimes.push_back(data.at(7));

        // Scalar multiplication times
        EigenScalarMultiplicationTimes.push_back(data.at(8));
        CSFScalarMultiplicationTimes.push_back(data.at(9));
        CSF2ScalarMultiplicationTimes.push_back(data.at(10));
        CSF3ScalarMultiplicationTimes.push_back(data.at(11));

        // Vector multiplication times
        EigenVectorMultiplicationTimes.push_back(data.at(12));
        CSFVectorMultiplicationTimes.push_back(data.at(13));
        CSF2VectorMultiplicationTimes.push_back(data.at(14));
        CSF3VectorMultiplicationTimes.push_back(data.at(15));

        // Matrix multiplication times
        EigenMatrixMultiplicationTimes.push_back(data.at(16));
        CSFMatrixMultiplicationTimes.push_back(data.at(17));
        CSF2MatrixMultiplicationTimes.push_back(data.at(18));
        CSF3MatrixMultiplicationTimes.push_back(data.at(19));

        // Memory usage
        EigenMemoryUsage.push_back(data.at(20));
        CSFMemoryUsage.push_back(data.at(21));
        CSF2MemoryUsage.push_back(data.at(22));
        CSF3MemoryUsage.push_back(data.at(23));
    }

    /**
     * @brief Finds the average time in a vector
     *
     * @param times
     */

    uint64_t average(std::vector<uint64_t>& times) {
        uint64_t sum = 0;
        for (int i = 0; i < times.size(); i++) {
            sum += times.at(i);
        }
        return sum / times.size();

    }

    /**
     * @brief Finds the maximum value in a vector
     *
     * @tparam uint64_t
     * @param times
     */

    uint64_t max(std::vector<uint64_t> times) {
        uint64_t max = times.at(0);
        for (int i = 1; i < times.size(); i++) {
            if (times.at(i) > max) {
                max = times.at(i);
            }
        }
        return max;
    }

    void printTimesToCSV() {
        FILE* file = fopen("timeData.csv", "a");
        std::vector<uint64_t> data;

        // record average times
        data.push_back(average(CSFConstructorTimes));
        data.push_back(average(CSFInnerIteratorTimes));
        data.push_back(average(CSFScalarMultiplicationTimes));
        data.push_back(average(CSFVectorMultiplicationTimes));
        data.push_back(average(CSFMatrixMultiplicationTimes));
        data.push_back(average(CSF2ConstructorTimes));
        data.push_back(average(CSF2InnerIteratorTimes));
        data.push_back(average(CSF2ScalarMultiplicationTimes));
        data.push_back(average(CSF2VectorMultiplicationTimes));
        data.push_back(average(CSF2MatrixMultiplicationTimes));
        data.push_back(average(CSF3ConstructorTimes));
        data.push_back(average(CSF3InnerIteratorTimes));
        data.push_back(average(CSF3ScalarMultiplicationTimes));
        data.push_back(average(CSF3VectorMultiplicationTimes));
        data.push_back(average(CSF3MatrixMultiplicationTimes));
        data.push_back(average(EigenConstructorTimes));
        data.push_back(average(EigenInnerIteratorTimes));
        data.push_back(average(EigenScalarMultiplicationTimes));
        data.push_back(average(EigenVectorMultiplicationTimes));
        data.push_back(average(EigenMatrixMultiplicationTimes));

        // record max times
        data.push_back(max(CSFConstructorTimes));
        data.push_back(max(CSFInnerIteratorTimes));
        data.push_back(max(CSFScalarMultiplicationTimes));
        data.push_back(max(CSFVectorMultiplicationTimes));
        data.push_back(max(CSFMatrixMultiplicationTimes));
        data.push_back(max(CSF2ConstructorTimes));
        data.push_back(max(CSF2InnerIteratorTimes));
        data.push_back(max(CSF2ScalarMultiplicationTimes));
        data.push_back(max(CSF2VectorMultiplicationTimes));
        data.push_back(max(CSF2MatrixMultiplicationTimes));
        data.push_back(max(CSF3ConstructorTimes));
        data.push_back(max(CSF3InnerIteratorTimes));
        data.push_back(max(CSF3ScalarMultiplicationTimes));
        data.push_back(max(CSF3VectorMultiplicationTimes));
        data.push_back(max(CSF3MatrixMultiplicationTimes));
        data.push_back(max(EigenConstructorTimes));
        data.push_back(max(EigenInnerIteratorTimes));
        data.push_back(max(EigenScalarMultiplicationTimes));
        data.push_back(max(EigenVectorMultiplicationTimes));
        data.push_back(max(EigenMatrixMultiplicationTimes));

        // Finally, print the data to the file
        for (int i = 0; i < data.size(); i++) {
            fprintf(file, "%" PRIu64, data.at(i));
        }
        fprintf(file, "\n");
        fclose(file);
    }

    void printMatrixAttributesToCSV() {
        FILE* file = fopen("matrixAttributes.csv", "a");

        fprintf(file, "%" PRIu32",%" PRIu32",%" PRIu32",%" PRIu64", %f, %f\n", myMatrix->matrixNum,
                myMatrix->matrixRows,
                myMatrix->matrixCols,
                myMatrix->matrixNonzeros,
                myMatrix->matrixRedundancy,
                myMatrix->matrixDensity);

        fclose(file);
    }


};