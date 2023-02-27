#include <iostream>
#include <Eigen/Sparse>
#include "misc/matrix_creator.cpp"

template <typename T2>
void test3(T2 *vals)
{
    // print vals

    std::cout << "test3" << std::endl;
    for (int i = 0; i < 10; i++)
    {
        std::cout << vals[i] << std::endl;
    }
}

template <typename vals_t>
void test1(vals_t **vals) {
    std::cout << "test1" << std::endl;

    // print vals
    for (int i = 0; i < 10; i++) {
        std::cout << (*vals)[i] << std::endl;
    }

    vals_t *vals2 = vals[0];

    // print vals2
    for (int i = 0; i < 10; i++) {
        std::cout << vals2[i] << std::endl;
    }

    test3(vals2);
}

template <typename T>
void test2(Eigen::SparseMatrix<T> &mat) {
    std::cout << "test2" << std::endl;

    T *vals = mat.valuePtr();

    // print vals
    for (int i = 0; i < 10; i++) {
        std::cout << vals[i] << std::endl;
    }
}



int main(int argc, char** argv) {

    int *vals = (int *) malloc(sizeof(int) * 10);

    // populate vals
    for (int i = 0; i < 10; i++) {
        vals[i] = i;
    }

    // call test1
    test1(&vals);

    // create a sparse matrix
    Eigen::SparseMatrix<int> mat(10, 10);

    // populate the matrix
    for (int i = 0; i < 10; i++) {
        mat.insert(i, i) = i;
    }

    // call test2
    test2(mat);

    int numRows = 50;
    int numCols = 50;
    int sparsity = 5;
    uint64_t seed = 5645646546;

    // generating a large random eigen sparse
    Eigen::SparseMatrix<int> myMatrix(numRows, numCols);
    myMatrix.reserve(Eigen::VectorXi::Constant(numRows, numCols));
    myMatrix = generateMatrix<int>(numRows, numCols, sparsity, seed);
    myMatrix.makeCompressed();

    // print myMatrix
    std::cout << myMatrix << std::endl;

    Eigen::SparseMatrix<int>::InnerIterator it(myMatrix, 0);
    while (it)
    {
        std::cout << it.row() << " " << it.col() << " " << it.value() << std::endl;
        ++it;
    }

    for (size_t i = 0; i < myMatrix.cols(); i++)
    {

        for (Eigen::SparseMatrix<int>::InnerIterator it(myMatrix, i); it; ++it)
        {
        }
    }

    int *values = myMatrix.valuePtr();
    int *indexes = myMatrix.innerIndexPtr();
    int *col_p = myMatrix.outerIndexPtr();

    std::cout << "values: " << std::endl;
    for (size_t i = 0; i < myMatrix.nonZeros(); i++)
    {
        std::cout << values[i] << " ";
    }

    std::cout << std::endl;

    Eigen::SparseMatrix<int, , short> myMatrix2(numRows, numCols);

    return 0;
}