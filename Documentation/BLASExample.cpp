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
     * This is done in O(n^2) but future implementations will use a new data structure to store the values
     * So we can reduce the time complexity to O(n).
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
     * As of right now, this operation is only single threaded.
     * 
     */
    Eigen::VectorXi eigenVector = Eigen::VectorXi::Random(4);
    Eigen::VectorXi eigenResult = csfSparseMatrix * eigenVector;

    //Print the Eigen::VectorXd
    std::cout << eigenResult << std::endl;

    /**
     * Matrix multiplication
     * 
     * 
     * This algorithm is O(n^2).
     * 
     */
    Eigen::MatrixXi eigenMatrix = Eigen::MatrixXi::Random(4, 4);
    Eigen::MatrixXi eigenMatrixResult = csfSparseMatrix * eigenMatrix;

    //Print the Eigen::MatrixXd
    std::cout << eigenMatrixResult << std::endl;

    return 1;
}