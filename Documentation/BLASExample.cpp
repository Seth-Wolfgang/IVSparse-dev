#include "../CSF/SparseMatrix"
#include "../misc/matrix_creator.cpp"

int main() {

    //For ease of use, create an Eigen::SparseMatrix
    Eigen::SparseMatrix<int> eigenSparseMatrix(20, 4);
    eigenSparseMatrix = generateMatrix<int>(20, 4, 1, 0, 10);
    eigenSparseMatrix.makeCompressed();

    //Create a CSF::SparseMatrix from the Eigen::SparseMatrix
    CSF::SparseMatrix<int> csfSparseMatrix(eigenSparseMatrix);

    //Print the CSF::SparseMatrix
    std::cout << csfSparseMatrix.toEigen() << std::endl;

    /**
     * Scalar multiplication
     * 
     * Scalar multiplication iterates through the whole matrix and scalese each value by the scalar.
     * This method is O(n^2) for CSF 3, but for CSF 2 it will only iterate through the unique values stored in 
     * performance arrays if the setting is active.
     * 
     * In place operations are also supported.
     * 
     */
    csfSparseMatrix *= 2;
    csfSparseMatrix = csfSparseMatrix * 2;

    //Print the CSF::SparseMatrix
    std::cout << csfSparseMatrix.toEigen() << std::endl;

    /**
     * Vector multiplication
     * 
     * Vector multiplication iterates through the whole matrix and multiplies each value by the corresponding value in the vector.
     * This is done in O(n^2) and is slower than the Eigen::SparseMatrix implementation.
     * 
     * The product does produce an Eigen::Vector as opposed to a CSF::SparseMatrix.
     * 
     */
    Eigen::VectorXi eigenVector = Eigen::VectorXi::Random(4);
    Eigen::VectorXi eigenResult = csfSparseMatrix * eigenVector;

    //Print the Eigen::VectorXd
    std::cout << eigenResult << std::endl;

    /**
     * Matrix multiplication
     * 
     * Our matrix mutliplication method produces an Eigen::Matrix as the product of a CSF::SparseMatrix and an Eigen::Matrix.
     * As of right now, this only works for Sparse * Dense operations, so it is not currently possible to multiply by an Eigen::SparseMatrix.
     * 
     * This algorithm is O(n^3). 
     * 
     */
    Eigen::MatrixXi eigenMatrix = Eigen::MatrixXi::Random(4, 4);        //Create a random matrix
    Eigen::MatrixXi eigenMatrixResult = csfSparseMatrix * eigenMatrix;  //Multiply the CSF::SparseMatrix by the Eigen::Matrix

    /**
     * Matrix Transpose
     * 
     * The matrix transpose method produces a transposed version of the CSF::SparseMatrix. Note: This operation can be quite costly 
     * due to how CSF::SparseMatrix is stored. 
     * 
     * This algorithm is in O(n^2)
    */
    CSF::SparseMatrix<int> csfSparseMatrixT = csfSparseMatrix.transpose(); 


    //Print the Eigen::MatrixXd
    std::cout << eigenMatrixResult << std::endl;

    /**
     * Outer Sums
     * 
     * The column sum method adds up each elemnt in each outer index and returns an array containing the sums.
     * This method benefits greatly from the CSF 2 performance arrays and is recommnded to use them for this method
     * 
     * This algorithm is in O(n^2)
    */

    int* columnSums = csfSparseMatrix.outerSum();

    //Print the column sums
    for (int i = 0; i < csfSparseMatrix.cols(); i++) {
        std::cout << columnSums[i] << std::endl;
    }

    /**
     * Row Sums
     * 
     * The row sum method adds up each elemnt in each inner index and returns an array containing the sums.
     * This method does NOT benefit from CSF 2 performance arrays, but they won't hinder it either.
     * This method must iterate through all data stored in the CSF::SparseMatrix.
     * 
     * This algorithm is in O(n^2)
    */

    int* rowSums = csfSparseMatrix.innerSum();

    //Print the row sums
    for (int i = 0; i < csfSparseMatrix.rows(); i++) {
        std::cout << rowSums[i] << std::endl;
    }

    /**
     * Max outer coefficients
     * 
     * The max outer coefficients method finds the maximum value in each outer index and returns an array containing the maximums.
     * This method benefits greatly from the CSF 2 performance arrays and is recommnded to use them for this method
     * 
     * This algorithm is in O(n^2)
    */

    int* maxOuterCoefficients = csfSparseMatrix.maxColCoeff();

    //Print the max outer coefficients
    for (int i = 0; i < csfSparseMatrix.cols(); i++) {
        std::cout << maxOuterCoefficients[i] << std::endl;
    }

    /**
     * Max inner coefficients
     * 
     * The max inner coefficients method finds the maximum value in each inner index and returns an array containing the maximums.
     * This method does NOT benefit from CSF 2 performance arrays, but they won't hinder it either.
     * This method must iterate through all data stored in the CSF::SparseMatrix.
     * 
     * This algorithm is in O(n^2)
    */

    int* maxInnerCoefficients = csfSparseMatrix.maxRowCoeff();

    //Print the max inner coefficients
    for (int i = 0; i < csfSparseMatrix.rows(); i++) {
        std::cout << maxInnerCoefficients[i] << std::endl;
    }

    /**
     * Min outer coefficients
     * 
     * The min outer coefficients method finds the minimum value in each outer index and returns an array containing the minimums.
     * This method benefits greatly from the CSF 2 performance arrays and is recommnded to use them for this method
     * 
     * This algorithm is in O(n^2)
    */

    int* minOuterCoefficients = csfSparseMatrix.minColCoeff();

    //Print the min outer coefficients
    for (int i = 0; i < csfSparseMatrix.cols(); i++) {
        std::cout << minOuterCoefficients[i] << std::endl;
    }

    /**
     * Min inner coefficients
     * 
     * The min inner coefficients method finds the minimum value in each inner index and returns an array containing the minimums.
     * This method does NOT benefit from CSF 2 performance arrays, but they won't hinder it either.
     * This method must iterate through all data stored in the CSF::SparseMatrix.
     * 
     * This algorithm is in O(n^2)
    */

    int* minInnerCoefficients = csfSparseMatrix.minRowCoeff();

    //Print the min inner coefficients
    for (int i = 0; i < csfSparseMatrix.rows(); i++) {
        std::cout << minInnerCoefficients[i] << std::endl;
    }

    /**
     * Trace of a matrix
     * 
     * The trace of a matrix is the sum of the diagonal elements of the matrix.
     * This method does NOT benefit from CSF 2 performance arrays, but they won't hinder it either.
     * 
     * This algorithm is in O(n^2)
    */

    int trace = csfSparseMatrix.trace();

    //Print the trace
    std::cout << trace << std::endl;


    /**
     * Sum of Matrix Coefficients
     * 
     * The sum of matrix coefficients is the sum of all elements in the matrix.
     * This method benefits greatly from CSF 2 performance arrays and is highly 
     * recommnded to use them for this method
     * 
     * This algorithm is in O(n^2)
    */

    int sum = csfSparseMatrix.sum();

    //Print the sum
    std::cout << sum << std::endl;

    /**
     * Frobenius Norm
     * 
     * The Frobenius norm is the square root of the sum of the squares of the matrix coefficients.
     * This method benefits greatly from CSF 2 performance arrays and is highly 
     * recommnded to use them for this method
     * 
     * This algorithm is in O(n^2)
    */

    double frobeniusNorm = csfSparseMatrix.norm();

    //Print the Frobenius norm
    std::cout << frobeniusNorm << std::endl;

    /**
     * Vector Length
     * 
     * The vector length is the square root of the sum of the squares of the vector coefficients.
     * This method benefits greatly from CSF 2 performance arrays and is highly 
     * recommnded to use them for this method
     * 
     * This algorithm is in O(n)
    */

    double vectorLength = csfSparseMatrix.vectorLength(0); // This is the length of the first vector

    //Print the vector length
    std::cout << vectorLength << std::endl;


    return 1;
}