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

    // CSF1 2 Data
    std::vector<uint64_t> CSF2ConstructorTimes;
    std::vector<uint64_t> CSF2InnerIteratorTimes;
    std::vector<uint64_t> CSF2ScalarMultiplicationTimes;
    std::vector<uint64_t> CSF2VectorMultiplicationTimes;

    // CSF1 3 Data
    std::vector<uint64_t> CSF3ConstructorTimes;
    std::vector<uint64_t> CSF3InnerIteratorTimes;
    std::vector<uint64_t> CSF3ScalarMultiplicationTimes;
    std::vector<uint64_t> CSF3VectorMultiplicationTimes;

    // Eigen data
    std::vector<uint64_t> EigenConstructorTimes;
    std::vector<uint64_t> EigenInnerIteratorTimes;
    std::vector<uint64_t> EigenScalarMultiplicationTimes;
    std::vector<uint64_t> EigenVectorMultiplicationTimes;

    //memory usage (in bytes)
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
            fprintf(file, "%s\n", "Matrix Number,Matrix Rows,Matrix Cols,Matrix Nonzeros,Matrix Redundancy,Matrix Density,Avg Eigen Constructor Time,Avg CSF2 Constructor Time,Avg CSF3 Constructor Time,Avg Eigen InnerIterator Time,Avg CSF2 InnerIterator Time,Avg CSF3 InnerIterator Time,Avg Eigen Scalar Multiplication Time,Avg CSF2 Scalar Multiplication Time,Avg CSF3 Scalar Multiplication Time,Avg Eigen Vector Multiplication Time,Avg CSF2 Vector Multiplication Time,Avg CSF3 Vector Multiplication Time,Avg Eigen Memory Usage, Avg CSF2 Memory Usage,Avg CSF3 Memory Usage,min Eigen Constructor Time,min CSF2 Constructor Time,min CSF3 Constructor Time,min Eigen InnerIterator Time,min CSF2 InnerIterator Time,min CSF3 InnerIterator Time,min Eigen Scalar Multiplication Time,min CSF2 Scalar Multiplication Time,min CSF3 Scalar Multiplication Time,min Eigen Vector Multiplication Time,min CSF2 Vector Multiplication Time,min CSF3 Vector Multiplication Time,min Eigen Memory Usage, min CSF2 Memory Usage,min CSF3 Memory Usage,Q1 Eigen Constructor Time,Q1 CSF2 Constructor Time,Q1 CSF3 Constructor Time,Q1 Eigen InnerIterator Time,Q1 CSF2 InnerIterator Time,Q1 CSF3 InnerIterator Time,Q1 Eigen Scalar Multiplication Time,Q1 CSF2 Scalar Multiplication Time,Q1 CSF3 Scalar Multiplication Time,Q1 Eigen Vector Multiplication Time,Q1 CSF2 Vector Multiplication Time,Q1 CSF3 Vector Multiplication Time,Q1 Eigen Memory Usage, Q1 CSF2 Memory Usage,Q1 CSF3 Memory Usage,Median Eigen Constructor Time,Median CSF2 Constructor Time,Median CSF3 Constructor Time,Median Eigen InnerIterator Time,Median CSF2 InnerIterator Time,Median CSF3 InnerIterator Time,Median Eigen Scalar Multiplication Time,Median CSF2 Scalar Multiplication Time,Median CSF3 Scalar Multiplication Time,Median Eigen Vector Multiplication Time,Median CSF2 Vector Multiplication Time,Median CSF3 Vector Multiplication Time,Median Eigen Memory Usage, Median CSF2 Memory Usage,Median CSF3 Memory Usage,Q3 Eigen Constructor Time,Q3 CSF2 Constructor Time,Q3 CSF3 Constructor Time,Q3 Eigen InnerIterator Time,Q3 CSF2 InnerIterator Time,Q3 CSF3 InnerIterator Time,Q3 Eigen Scalar Multiplication,Q3 CSF2 Scalar Multiplication Time,Q3 CSF3 Scalar Multiplication Time,Q3 Eigen Vector Multiplication Time,Q3 CSF2 Vector Multiplication Time,Q3 CSF3 Vector Multiplication Time,Q3 Eigen Memory Usage, Q3 CSF2 Memory Usage,Q3 CSF3 Memory Usage,Max Eigen Constructor Time,Max CSF2 Constructor Time,Max CSF3 Constructor Time,Max Eigen InnerIterator Time,Max CSF2 InnerIterator Time,Max CSF3 InnerIterator Time,Max Eigen Scalar Multiplication Time,Max CSF2 Scalar Multiplication Time,Max CSF3 Scalar Multiplication Time,Max Eigen Vector Multiplication Time,Max CSF2 Vector Multiplication Time,Max CSF3 Vector Multiplication Time,Max Eigen Memory Usage, Max CSF2 Memory Usage,Max CSF3 Memory Usage");
            fclose(file);
        }

        if (access("rawTimeData.csv", F_OK) != 0) {
            std::cout << "Creating memoryData.csv" << std::endl;
            file = fopen("rawTimeData.csv", "a");
            fprintf(file, "%s\n", "Matrix Number,Matrix Rows,Matrix Cols,Matrix Nonzeros,Matrix Redundancy,Matrix Density,Eigen Constructor Time,CSF2 Constructor Time,CSF3 Constructor Time,Eigen InnerIterator Time,CSF2 InnerIterator Time,CSF3 InnerIterator Time,Eigen Scalar Multiplication Time,CSF2 Scalar Multiplication Time,CSF3 Scalar Multiplication Time,Eigen Vector Multiplication Time,CSF2 Vector Multiplication Time,CSF3 Vector Multiplication Time,Eigen Memory Usage,CSF2 Memory Usage,CSF3 Memory Usage");
            fclose(file);
        }
    }

    // Destructor
    ~BenchAnalysis() {
        if (myMatrix != NULL)
            free(myMatrix);
    }

    void pushData(std::vector<uint64_t>& data) {

        // Constructor times
        EigenConstructorTimes.push_back(data.at(0));
        CSF2ConstructorTimes.push_back(data.at(1));
        CSF3ConstructorTimes.push_back(data.at(2));

        // Inner iterator times
        EigenInnerIteratorTimes.push_back(data.at(3));
        CSF2InnerIteratorTimes.push_back(data.at(4));
        CSF3InnerIteratorTimes.push_back(data.at(5));

        // Scalar multiplication times
        EigenScalarMultiplicationTimes.push_back(data.at(6));
        CSF2ScalarMultiplicationTimes.push_back(data.at(7));
        CSF3ScalarMultiplicationTimes.push_back(data.at(8));

        // Vector multiplication times
        EigenVectorMultiplicationTimes.push_back(data.at(9));
        CSF2VectorMultiplicationTimes.push_back(data.at(10));
        CSF3VectorMultiplicationTimes.push_back(data.at(11));

        // Memory usage
        EigenMemoryUsage.push_back(data.at(12));
        CSF2MemoryUsage.push_back(data.at(13));
        CSF3MemoryUsage.push_back(data.at(14));

        FILE* file = fopen("rawTimeData.csv", "a");
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

    uint64_t min(std::vector<uint64_t> times) {
        uint64_t min = times.at(0);
        for (uint32_t i = 1; i < times.size(); i++) {
            if (times.at(i) < min) {
                min = times.at(i);
            }
        }
        return min;
    }

    uint64_t median(std::vector<uint64_t> times) {
        std::sort(times.begin(), times.end());
        if (times.size() % 2 == 0) {
            return (times.at(times.size() / 2 - 1) + times.at(times.size() / 2)) / 2;
        }
        else {
            return times.at(times.size() / 2);
        }
    }

    uint64_t quarter1Percentile(std::vector<uint64_t> times) {
        std::sort(times.begin(), times.end());
        return times.at(times.size() / 4);
    }

    uint64_t quarter3Percentile(std::vector<uint64_t> times) {
        std::sort(times.begin(), times.end());
        return times.at(times.size() * 3 / 4);
    }

    void printTimesToCSV() {
        std::vector<uint64_t> data;

        //Average times
        //Constructors
        //print all elements of EigenConstructorTimes

        data.push_back(average(EigenConstructorTimes));
        data.push_back(average(CSF2ConstructorTimes));
        data.push_back(average(CSF3ConstructorTimes));

        //Inner iterators
        data.push_back(average(EigenInnerIteratorTimes));
        data.push_back(average(CSF2InnerIteratorTimes));
        data.push_back(average(CSF3InnerIteratorTimes));

        //Scalar Multiplication
        data.push_back(average(EigenScalarMultiplicationTimes));
        data.push_back(average(CSF2ScalarMultiplicationTimes));
        data.push_back(average(CSF3ScalarMultiplicationTimes));

        //Vector Multiplication
        data.push_back(average(EigenVectorMultiplicationTimes));
        data.push_back(average(CSF2VectorMultiplicationTimes));
        data.push_back(average(CSF3VectorMultiplicationTimes));

        // Memory usage
        data.push_back(average(EigenMemoryUsage));
        data.push_back(average(CSF2MemoryUsage));
        data.push_back(average(CSF3MemoryUsage));

        //Mins
        //Constructors
        data.push_back(min(EigenConstructorTimes));
        data.push_back(min(CSF2ConstructorTimes));
        data.push_back(min(CSF3ConstructorTimes));

        //Inner iterators
        data.push_back(min(EigenInnerIteratorTimes));
        data.push_back(min(CSF2InnerIteratorTimes));
        data.push_back(min(CSF3InnerIteratorTimes));

        //Scalar Multiplication
        data.push_back(min(EigenScalarMultiplicationTimes));
        data.push_back(min(CSF2ScalarMultiplicationTimes));
        data.push_back(min(CSF3ScalarMultiplicationTimes));

        //Vector Multiplication
        data.push_back(min(EigenVectorMultiplicationTimes));
        data.push_back(min(CSF2VectorMultiplicationTimes));
        data.push_back(min(CSF3VectorMultiplicationTimes));

        // Memory usage
        data.push_back(min(EigenMemoryUsage));
        data.push_back(min(CSF2MemoryUsage));
        data.push_back(min(CSF3MemoryUsage));

        //Quartile 1

        //Constructors
        data.push_back(quarter1Percentile(EigenConstructorTimes));
        data.push_back(quarter1Percentile(CSF2ConstructorTimes));
        data.push_back(quarter1Percentile(CSF3ConstructorTimes));

        //Inner iterators
        data.push_back(quarter1Percentile(EigenInnerIteratorTimes));
        data.push_back(quarter1Percentile(CSF2InnerIteratorTimes));
        data.push_back(quarter1Percentile(CSF3InnerIteratorTimes));

        //Scalar Multiplication
        data.push_back(quarter1Percentile(EigenScalarMultiplicationTimes));
        data.push_back(quarter1Percentile(CSF2ScalarMultiplicationTimes));
        data.push_back(quarter1Percentile(CSF3ScalarMultiplicationTimes));

        //Vector Multiplication
        data.push_back(quarter1Percentile(EigenVectorMultiplicationTimes));
        data.push_back(quarter1Percentile(CSF2VectorMultiplicationTimes));
        data.push_back(quarter1Percentile(CSF3VectorMultiplicationTimes));

        // Memory usage
        data.push_back(quarter1Percentile(EigenMemoryUsage));
        data.push_back(quarter1Percentile(CSF2MemoryUsage));
        data.push_back(quarter1Percentile(CSF3MemoryUsage));

        //Medians
        //Constructors
        data.push_back(median(EigenConstructorTimes));
        data.push_back(median(CSF2ConstructorTimes));
        data.push_back(median(CSF3ConstructorTimes));

        //Inner iterators
        data.push_back(median(EigenInnerIteratorTimes));
        data.push_back(median(CSF2InnerIteratorTimes));
        data.push_back(median(CSF3InnerIteratorTimes));

        //Scalar Multiplication
        data.push_back(median(EigenScalarMultiplicationTimes));
        data.push_back(median(CSF2ScalarMultiplicationTimes));
        data.push_back(median(CSF3ScalarMultiplicationTimes));

        //Vector Multiplication
        data.push_back(median(EigenVectorMultiplicationTimes));
        data.push_back(median(CSF2VectorMultiplicationTimes));
        data.push_back(median(CSF3VectorMultiplicationTimes));

        // Memory usage
        data.push_back(median(EigenMemoryUsage));
        data.push_back(median(CSF2MemoryUsage));
        data.push_back(median(CSF3MemoryUsage));

        //Quartile 3
        //Constructors
        data.push_back(quarter3Percentile(EigenConstructorTimes));
        data.push_back(quarter3Percentile(CSF2ConstructorTimes));
        data.push_back(quarter3Percentile(CSF3ConstructorTimes));

        //Inner iterators
        data.push_back(quarter3Percentile(EigenInnerIteratorTimes));
        data.push_back(quarter3Percentile(CSF2InnerIteratorTimes));
        data.push_back(quarter3Percentile(CSF3InnerIteratorTimes));

        //Scalar Multiplication
        data.push_back(quarter3Percentile(EigenScalarMultiplicationTimes));
        data.push_back(quarter3Percentile(CSF2ScalarMultiplicationTimes));
        data.push_back(quarter3Percentile(CSF3ScalarMultiplicationTimes));

        //Vector Multiplication
        data.push_back(quarter3Percentile(EigenVectorMultiplicationTimes));
        data.push_back(quarter3Percentile(CSF2VectorMultiplicationTimes));
        data.push_back(quarter3Percentile(CSF3VectorMultiplicationTimes));

        // Memory usage
        data.push_back(quarter3Percentile(EigenMemoryUsage));
        data.push_back(quarter3Percentile(CSF2MemoryUsage));
        data.push_back(quarter3Percentile(CSF3MemoryUsage));

        // Max times
        //Constructors
        data.push_back(max(EigenConstructorTimes));
        data.push_back(max(CSF2ConstructorTimes));
        data.push_back(max(CSF3ConstructorTimes));

        //Inner iterators
        data.push_back(max(EigenInnerIteratorTimes));
        data.push_back(max(CSF2InnerIteratorTimes));
        data.push_back(max(CSF3InnerIteratorTimes));

        //Scalar Multiplication
        data.push_back(max(EigenScalarMultiplicationTimes));
        data.push_back(max(CSF2ScalarMultiplicationTimes));
        data.push_back(max(CSF3ScalarMultiplicationTimes));

        //Vector Multiplication
        data.push_back(max(EigenVectorMultiplicationTimes));
        data.push_back(max(CSF2VectorMultiplicationTimes));
        data.push_back(max(CSF3VectorMultiplicationTimes));

        // Memory usage
        data.push_back(max(EigenMemoryUsage));
        data.push_back(max(CSF2MemoryUsage));
        data.push_back(max(CSF3MemoryUsage));


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