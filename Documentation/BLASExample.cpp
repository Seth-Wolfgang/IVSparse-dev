#include "../CSF/SparseMatrix"
#include "../misc/matrix_creator.cpp"

int main() {

    //For ease of use, create an Eigen::SparseMatrix
    Eigen::SparseMatrix<int> eigenSparseMatrix(20, 4);
    eigenSparseMatrix = generateMatrix<int>(20, 4, 1, 0);
    eigenSparseMatrix.makeCompressed();

    //Create a CSF::SparseMatrix from the Eigen::SparseMatrix
    CSF::SparseMatrix<int> csfSparseMatrix(eigenSparseMatrix);

    //Print the CSF::SparseMatrix
    std::cout << csfSparseMatrix.toEigen() << std::endl;

    /**
     * Scalar multiplication
     * 
     * Scalar multiplication iterates through the whole matrix and scalese each value by the scalar.
     * This is done in O(n^2) but future implementations for CSF level 2 will use a new data structure to store the values
     * So we can reduce the time complexity to O(n).
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

    return 1;
}