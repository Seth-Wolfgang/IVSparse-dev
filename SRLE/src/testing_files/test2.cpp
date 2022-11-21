#include <Eigen/Sparse>
#include <iostream>
#include "../matrixCreator.cpp"

using namespace Eigen;
using std::cout;
using std::endl;

typedef Triplet<int> Trip;

template <typename T>
Eigen::SparseMatrix<T> generateMatrix(int numRows, int numCols, double sparsity)
{
    // generate a random sparse matrix
    uint64_t favoriteNumber = 11515616;
    rng randMatrixGen = rng(favoriteNumber);

    Eigen::SparseMatrix<T> myMatrix(numRows, numCols);
    myMatrix.reserve(Eigen::VectorXi::Constant(numRows, numCols));

    for (int i = 0; i < numRows; i++)
    {
        for (int j = 0; j < numCols; j++)
        {
            if (randMatrixGen.draw<int>(i, j, sparsity))
            {
                myMatrix.insert(i, j) = 100 * randMatrixGen.uniform<double>(j);
            }
        }
    }
    return myMatrix;
}

int main(int argc, char *argv[])
{

    std::vector<Trip> trp, tmp;

    // I subtracted 1 from the indices so that the output matches your question
    trp.push_back(Trip(1 - 1, 1 - 1, 3));
    trp.push_back(Trip(1 - 1, 3 - 1, 4));
    trp.push_back(Trip(2 - 1, 3 - 1, 1));
    trp.push_back(Trip(3 - 1, 2 - 1, 2));
    trp.push_back(Trip(3 - 1, 4 - 1, 5));
    trp.push_back(Trip(4 - 1, 1 - 1, 4));

    int rows, cols;
    rows = cols = 4;
    SparseMatrix<int> A(rows, cols);

    A.setFromTriplets(trp.begin(), trp.end());
    cout << "Matrix from triplets:" << endl;
    cout << A << endl;

    cout << endl
         << "Triplets:" << endl;
    cout << "Row\tCol\tVal" << endl;
    for (int k = 0; k < A.outerSize(); ++k)
    {
        for (SparseMatrix<int>::InnerIterator it(A, k); it; ++it)
        {
            cout << 1 + it.row() << "\t"; // row index
            cout << 1 + it.col() << "\t"; // col index (here it is equal to k)
            cout << it.value() << endl;
        }
    }

    // generate a random sparse matrix

    int numRows = 100;
    int numCols = 100;
    double sparsity = 0.1;

    Eigen::SparseMatrix<int> myMatrix(numRows, numCols);
    myMatrix.reserve(Eigen::VectorXi::Constant(numRows, numCols));
    myMatrix = generateMatrix<int>(numRows, numCols, sparsity);
    myMatrix.makeCompressed();

     return 0;
}