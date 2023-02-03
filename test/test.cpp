#include "../CSF/SparseMatrix"

int main(int argc, char ** argv) {

    Eigen::SparseMatrix<int> mat1(11, 10);

    // populate mat1
    mat1.insert(2, 0) = 1;
    mat1.insert(5, 0) = 2;
    mat1.insert(3, 1) = 1;
    mat1.insert(4, 1) = 2;
    mat1.insert(9, 1) = 1;
    mat1.insert(9, 2) = 1;
    mat1.insert(1, 3) = 1;
    mat1.insert(2, 3) = 1;
    mat1.insert(6, 3) = 2;
    mat1.insert(2, 4) = 2;
    mat1.insert(4, 4) = 1;
    mat1.insert(9, 4) = 1;
    mat1.insert(3, 6) = 1;
    mat1.insert(4, 6) = 1;

    mat1.makeCompressed();

    // print out mat1
    std::cout << mat1 << std::endl;

    // iterate through mat1 using value pointer
    // for (int k=0; k<mat1.outerSize(); ++k) {
    //     for (Eigen::SparseMatrix<int>::InnerIterator it(mat1,k); it; ++it) {
    //         std::cout << it.value() << std::endl;
    //     }
    // }

    for (Eigen::SparseMatrix<int>::InnerIterator it(mat1, 0); it; ++it) {
        std::cout << it.value() << std::endl;
    }

    std::cout << mat1.outerSize() << std::endl;
    std::cout << mat1.innerSize() << std::endl;


    return 0;
}