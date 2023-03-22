/**
 * @brief A simple class to store and record basic statistical data of benchmarking results
 * @author Seth Wolfgang
 * @date 2023-03-22
 */

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

    // CSF 1 Data
    std::vector<T> CSFConstructorTimes;
    std::vector<T> CSFInnerIteratorTimes;
    std::vector<T> CSFScalarMultiplicationTimes;
    std::vector<T> CSFVectorMultiplicationTimes;
    std::vector<T> CSFMatrixMultiplicationTimes;

    // CSF 2 Data
    std::vector<T> CSF2ConstructorTimes;
    std::vector<T> CSF2InnerIteratorTimes;
    std::vector<T> CSF2ScalarMultiplicationTimes;
    std::vector<T> CSF2VectorMultiplicationTimes;
    std::vector<T> CSF2MatrixMultiplicationTimes;

    // CSF 3 Data
    std::vector<T> CSF3ConstructorTimes;
    std::vector<T> CSF3InnerIteratorTimes;
    std::vector<T> CSF3ScalarMultiplicationTimes;
    std::vector<T> CSF3VectorMultiplicationTimes;
    std::vector<T> CSF3MatrixMultiplicationTimes;

    // Eigen data
    std::vector<T> EigenConstructorTimes;
    std::vector<T> EigenInnerIteratorTimes;
    std::vector<T> EigenScalarMultiplicationTimes;
    std::vector<T> EigenVectorMultiplicationTimes;
    std::vector<T> EigenMatrixMultiplicationTimes;
    

    //memory usage (in bytes)
    std::vector<T> CSFMemoryUsage;
    std::vector<T> CSF2MemoryUsage;
    std::vector<T> CSF3MemoryUsage;
    std::vector<T> EigenMemoryUsage;


public:

    // Constructor
    benchAnalysis(uint32_t matrixNum, uint32_t matrixRows, uint32_t matrixCols, uint64_t matrixNonzeros, double matrixRedundancy, double matrixDensity) {
        matrix myMatrix = (matrix)malloc(sizeof(matrix));
        myMatrix.matrixNum = matrixNum;
        myMatrix.matrixRows = matrixRows;
        myMatrix.matrixCols = matrixCols;
        myMatrix.matrixNonzeros = matrixNonzeros;
        myMatrix.matrixRedundancy = matrixRedundancy;
        myMatrix.matrixDensity = matrixDensity;
    }

    // Destructor
    ~benchAnalysis() {
        if (myMatrix != NULL)
            free(myMatrix);
    }

    template <typename T>
    void pushData(std::vector<T> data) {

        // CSF 1 Data
        CSFConstructorTimes.push_back(data.at(0));
        CSFInnerIteratorTimes.push_back(data.at(1));
        CSFScalarMultiplicationTimes.push_back(data.at(2));
        CSFVectorMultiplicationTimes.push_back(data.at(3));
        CSFMatrixMultiplicationTimes.push_back(data.at(4));

        // CSF 2 Data
        CSF2ConstructorTimes.push_back(data.at(5));
        CSF2InnerIteratorTimes.push_back(data.at(6));
        CSF2ScalarMultiplicationTimes.push_back(data.at(7));
        CSF2VectorMultiplicationTimes.push_back(data.at(8));
        CSF2MatrixMultiplicationTimes.push_back(data.at(9));

        // CSF 3 Data
        CSF3ConstructorTimes.push_back(data.at(10));
        CSF3InnerIteratorTimes.push_back(data.at(11));
        CSF3ScalarMultiplicationTimes.push_back(data.at(12));
        CSF3VectorMultiplicationTimes.push_back(data.at(13));
        CSF3MatrixMultiplicationTimes.push_back(data.at(14));

        // Eigen data
        EigenConstructorTimes.push_back(data.at(15));
        EigenInnerIteratorTimes.push_back(data.at(16));
        EigenScalarMultiplicationTimes.push_back(data.at(17));
        EigenVectorMultiplicationTimes.push_back(data.at(18));
        EigenMatrixMultiplicationTimes.push_back(data.at(19));

        // Memory usage
        CSFMemoryUsage.push_back(data.at(20));
        CSF2MemoryUsage.push_back(data.at(21));
        CSF3MemoryUsage.push_back(data.at(22));
        EigenMemoryUsage.push_back(data.at(23));
    }

    /**
     * @brief Finds the average time in a vector
     *
     * @tparam T
     * @param times
     */

    template <typename T>
    void average(vector<T> times) {
        T sum = 0;
        for (int i = 0; i < times.size(); i++) {
            sum += times.at(i);
        }
        return sum / times.size();

    }

    /**
     * @brief Finds the maximum value in a vector
     *
     * @tparam T
     * @param times
     */

    template <typename T>
    void max(vector<T> times) {
        T max = times.at(0);
        for (int i = 1; i < times.size(); i++) {
            if (times.at(i) > max) {
                max = times.at(i);
            }
        }
        return max;
    }

    void printTimesToCSV() {
        File file = null;
        if (!fileExists("timeData.csv")) {
            file = fopen("timeData.csv", "a");
            fprintf(file, "CSF 1 Constructor Time, CSF 1 Inner Iterator Time, CSF 1 Scalar Multiplication Time, CSF 1 Vector Multiplication Time, CSF 1 Matrix Multiplication Time, CSF 2 Constructor Time, CSF 2 Inner Iterator Time, CSF 2 Scalar Multiplication Time, CSF 2 Vector Multiplication Time, CSF 2 Matrix Multiplication Time, CSF 3 Constructor Time, CSF 3 Inner Iterator Time, CSF 3 Scalar Multiplication Time, CSF 3 Vector Multiplication Time, CSF 3 Matrix Multiplication Time, Eigen Constructor Time, Eigen Inner Iterator Time, Eigen Scalar Multiplication Time, Eigen Vector Multiplication Time, Eigen Matrix Multiplication Time, Max CSF 1 Constructor Time, Max CSF 1 Inner Iterator Time, Max CSF 1 Scalar Multiplication Time, Max CSF 1 Vector Multiplication Time, Max CSF 1 Matrix Multiplication Time, Max CSF 2 Constructor Time, Max CSF 2 Inner Iterator Time, Max CSF 2 Scalar Multiplication Time, Max CSF 2 Vector Multiplication Time, Max CSF 2 Matrix Multiplication Time, Max CSF 3 Constructor Time, Max CSF 3 Inner Iterator Time, Max CSF 3 Scalar Multiplication Time, Max CSF 3 Vector Multiplication Time, Max CSF 3 Matrix Multiplication Time, Max Eigen Constructor Time, Max Eigen Inner Iterator Time, Max Eigen Scalar Multiplication Time, Max Eigen Vector Multiplication Time, Max Eigen Matrix Multiplication Time\n");
        }
        else {
            file = fopen("timeData.csv", "a");
            vector<T> data;

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
                fprintf(file, "%f, ", data.at(i));
            }
            fprintf(file, "\n");
        }

    }

    void printMatrixAttributesToCSV() {
        file = fopen("matrixAttributes.csv", "a");
        fprintf(file, "Matrix Number, Matrix Rows, Matrix Cols, Matrix Nonzeros, Matrix Redundancy, Matrix Density");

        for (int i = 0; i < matrixInfo.size(); i++) {
            fprintf(file, "%d, %d, %d, %d, %f, %f\n", matrixInfo.matrixNum,
                    matrixInfo.matrixRows,
                    matrixInfo.matrixCols,
                    matrixInfo.matrixNonzeros,
                    matrixInfo.matrixRedundancy,
                    matrixInfo.matrixDensity);
        }
    }

}