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
        double matrixNum;
        double matrixRows;
        double matrixCols;
        double matrixNonzeros;
        double matrixRedundancy;
        double matrixDensity;
    } matrix;

    matrix* myMatrix;

    // CSF1 1 Data
    std::vector<uint64_t> CSFConstructorTimes;
    std::vector<uint64_t> CSFInnerIteratorTimes;
    std::vector<uint64_t> CSFScalarMultiplicationTimes;
    std::vector<uint64_t> CSFVectorMultiplicationTimes;
    std::vector<uint64_t> CSFMatrixMultiplicationTimes;

    // CSF1 2 Data
    std::vector<uint64_t> CSF2ConstructorTimes;
    std::vector<uint64_t> CSF2InnerIteratorTimes;
    std::vector<uint64_t> CSF2ScalarMultiplicationTimes;
    std::vector<uint64_t> CSF2VectorMultiplicationTimes;
    std::vector<uint64_t> CSF2MatrixMultiplicationTimes;

    // CSF1 3 Data
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
    BenchAnalysis(std::vector<double> matrixData) {
        myMatrix = (matrix*)malloc(sizeof(matrix));
        //matrixData -> ID, rows, cols, nonzeos, redundancy, matrix density
        // Assigning the matrix data to the struct
        myMatrix->matrixNum = matrixData[0];
        myMatrix->matrixRows = matrixData[1];
        myMatrix->matrixCols = matrixData[2];
        myMatrix->matrixNonzeros = matrixData[3];
        myMatrix->matrixRedundancy = matrixData[4];
        myMatrix->matrixDensity = matrixData[5];

        //Checking to see if the files we're writing to exist in the directory
        //if not, we write the headers at the top of the file.
        FILE* file;
        if (access("timeData.csv", F_OK) != 0) {
            std::cout << "Creating timeData.csv" << std::endl;
            file = fopen("timeData.csv", "a");
            fprintf(file, "%s\n", "Matrix Number, Matrix Rows, Matrix Cols, Matrix Nonzeros, Matrix Redundancy, Matrix Density, Eigen Constructor Time, CSF1 Constructor Time, CSF2 Constructor Time, CSF3 Constructor Time, Eigen Inner Iterator Time, CSF1 Inner Iterator Time, CSF2 Inner Iterator Time, CSF3 Inner Iterator Time, Eigen Scalar Multiplication Time, CSF1 Scalar Multiplication Time, CSF2 Scalar Multiplication Time, CSF3 Scalar Multiplication Time, Eigen Vector Multiplication Time, CSF1 Vector Multiplication Time, CSF2 Vector Multiplication Time, CSF3 Vector Multiplication Time, Eigen Matrix Multiplication Time, CSF1 Matrix Multiplication Time, CSF2 Matrix Multiplication Time, CSF3 Matrix Multiplication Time, Max Eigen Constructor Time, Max CSF1 Constructor Time, Max CSF2 Constructor Time, Max CSF3 Constructor Time, Max Eigen Inner Iterator Time, Max CSF1 Inner Iterator Time, Max CSF2 Inner Iterator Time, Max CSF3 Inner Iterator Time, Max Eigen Scalar Multiplication Time, Max CSF1 Scalar Multiplication Time, Max CSF2 Scalar Multiplication Time, Max CSF3 Scalar Multiplication Time, Max Eigen Vector Multiplication Time, Max CSF1 Vector Multiplication Time, Max CSF2 Vector Multiplication Time, Max CSF3 Vector Multiplication Time, Max Eigen Matrix Multiplication Time, Max CSF1 Matrix Multiplication Time, Max CSF2 Matrix Multiplication Time, Max CSF3 Matrix Multiplication Time, Eigen Memory Usage, CSF1 Memory Usage, CSF2 Memory Usage, CSF3 Memory Usag");
            fclose(file);
        }
        //check if first line of file is

    }

    // Destructor
    ~BenchAnalysis() {
        if (myMatrix != NULL)
            free(myMatrix);
    }

    void pushData(std::vector<uint64_t> data) {

        // Constructor times
        EigenConstructorTimes.push_back(data.at(0));
        CSFConstructorTimes.push_back(data.at(1)); // Currently 0
        CSF2ConstructorTimes.push_back(data.at(2));
        CSF3ConstructorTimes.push_back(data.at(3));

        // Inner iterator times
        EigenInnerIteratorTimes.push_back(data.at(4));
        CSFInnerIteratorTimes.push_back(data.at(5));
        CSF2InnerIteratorTimes.push_back(data.at(6));
        CSF3InnerIteratorTimes.push_back(data.at(7));

        // Scalar multiplication times
        EigenScalarMultiplicationTimes.push_back(data.at(8));
        CSFScalarMultiplicationTimes.push_back(data.at(9)); // Currently 0
        CSF2ScalarMultiplicationTimes.push_back(data.at(10));
        CSF3ScalarMultiplicationTimes.push_back(data.at(11));

        // Vector multiplication times
        EigenVectorMultiplicationTimes.push_back(data.at(12));
        CSFVectorMultiplicationTimes.push_back(data.at(13));
        CSF2VectorMultiplicationTimes.push_back(data.at(14));
        CSF3VectorMultiplicationTimes.push_back(data.at(15));

        // Matrix multiplication times
        EigenMatrixMultiplicationTimes.push_back(data.at(16));
        CSFMatrixMultiplicationTimes.push_back(data.at(17));  // Currently 0
        CSF2MatrixMultiplicationTimes.push_back(data.at(18));
        CSF3MatrixMultiplicationTimes.push_back(data.at(19));

        // Memory usage
        EigenMemoryUsage.push_back(data.at(20)); // Currently 0
        CSFMemoryUsage.push_back(data.at(21)); // Currently 0
        CSF2MemoryUsage.push_back(data.at(22)); // Currently 0
        CSF3MemoryUsage.push_back(data.at(23)); // Currently 0
    }

    /**
     * @brief Finds the average time in a vector
     *
     * @param times
     */

    uint64_t average(std::vector<uint64_t>& times) {
        uint64_t sum = 0;
        for (uint32_t i = 0; i < times.size(); i++) {
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
        for (uint32_t i = 1; i < times.size(); i++) {
            if (times.at(i) > max) {
                max = times.at(i);
            }
        }
        return max;
    }

    void printTimesToCSV() {
        std::vector<uint64_t> data;

        //Average times
        //Constructors
        //print all elements of EigenConstructorTimes

        data.push_back(average(EigenConstructorTimes));
        data.push_back(average(CSFConstructorTimes));
        data.push_back(average(CSF2ConstructorTimes));
        data.push_back(average(CSF3ConstructorTimes));

        //Inner iterators
        data.push_back(average(EigenInnerIteratorTimes));
        data.push_back(average(CSFInnerIteratorTimes));
        data.push_back(average(CSF2InnerIteratorTimes));
        data.push_back(average(CSF3InnerIteratorTimes));

        //Scalar Multiplication
        data.push_back(average(EigenScalarMultiplicationTimes));
        data.push_back(average(CSFScalarMultiplicationTimes));
        data.push_back(average(CSF2ScalarMultiplicationTimes));
        data.push_back(average(CSF3ScalarMultiplicationTimes));

        //Vector Multiplication
        data.push_back(average(EigenVectorMultiplicationTimes));
        data.push_back(average(CSFVectorMultiplicationTimes));
        data.push_back(average(CSF2VectorMultiplicationTimes));
        data.push_back(average(CSF3VectorMultiplicationTimes));

        //Matrix Multiplication
        data.push_back(average(EigenMatrixMultiplicationTimes));
        data.push_back(average(CSFMatrixMultiplicationTimes));
        data.push_back(average(CSF2MatrixMultiplicationTimes));
        data.push_back(average(CSF3MatrixMultiplicationTimes));

        // Memory usage
        // data.push_back(average(EigenMemoryUsage));
        // data.push_back(average(CSFMemoryUsage));
        // data.push_back(average(CSF2MemoryUsage));
        // data.push_back(average(CSF3MemoryUsage));
        data.push_back(0);
        data.push_back(0);
        data.push_back(0);
        data.push_back(0);

        // Max times
        //Constructors
        data.push_back(max(EigenConstructorTimes));
        data.push_back(max(CSFConstructorTimes));
        data.push_back(max(CSF2ConstructorTimes));
        data.push_back(max(CSF3ConstructorTimes));

        //Inner iterators
        data.push_back(max(EigenInnerIteratorTimes));
        data.push_back(max(CSFInnerIteratorTimes));
        data.push_back(max(CSF2InnerIteratorTimes));
        data.push_back(max(CSF3InnerIteratorTimes));

        //Scalar Multiplication
        data.push_back(max(EigenScalarMultiplicationTimes));
        data.push_back(max(CSFScalarMultiplicationTimes));
        data.push_back(max(CSF2ScalarMultiplicationTimes));
        data.push_back(max(CSF3ScalarMultiplicationTimes));

        //Vector Multiplication
        data.push_back(max(EigenVectorMultiplicationTimes));
        data.push_back(max(CSFVectorMultiplicationTimes));
        data.push_back(max(CSF2VectorMultiplicationTimes));
        data.push_back(max(CSF3VectorMultiplicationTimes));

        //Matrix Multiplication
        data.push_back(max(EigenMatrixMultiplicationTimes));
        data.push_back(max(CSFMatrixMultiplicationTimes));
        data.push_back(max(CSF2MatrixMultiplicationTimes));
        data.push_back(max(CSF3MatrixMultiplicationTimes));

        // Memory usage
        // data.push_back(max(EigenMemoryUsage));
        // data.push_back(max(CSFMemoryUsage));
        // data.push_back(max(CSF2MemoryUsage));
        // data.push_back(max(CSF3MemoryUsage));
        data.push_back(0);
        data.push_back(0);
        data.push_back(0);
        data.push_back(0);

        /*
                                                                 ORDER: CSC, CSF1, CSF2, CSF3
            ||
                              ATTRIBUTES                      ||                                          AVERAGE                                              ||                                             MAX                                                |
            ID | Rows | Cols | Nonzeros | Redundancy, Density || Constructor | Iterator | scalar multiplcation | vector multiplication | matrix multiplication ||  Constructor | Iterator | scalar multiplcation | vector multiplication | matrix multiplication |
        */
        
        FILE* file = fopen("timeData.csv", "a");
        fprintf(file, "%f, %f, %f, %f, %f, %f,", 
                myMatrix->matrixNum,
                myMatrix->matrixRows,
                myMatrix->matrixCols,
                myMatrix->matrixNonzeros,
                myMatrix->matrixRedundancy,
                myMatrix->matrixDensity);
        // Finally, print the data to the file
        for (uint32_t i = 0; i < data.size(); ++i) {
            fprintf(file, "%" PRIu64 ",", data.at(i));
        }
        fprintf(file, "\n");
        fclose(file);
    }



};