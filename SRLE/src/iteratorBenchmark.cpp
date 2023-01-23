#include "include/CSF.hpp"
#include "include/CSF_Lib.hpp"

int main() {

    int numRows = 100;
    int numCols = 100;
    int sparsity = 20;
    uint64_t seed = 5645646546;
    iteratorBenchmark(numRows, numCols, sparsity, seed);

    return 1;
}

void iteratorBenchmark(int numRows, int numCols, int sparsity, uint64_t seed) {
    // TO ENSURE EVERYTHING WORKS, THE TOTAL SUM OF ALL VALUES IS CALUCLATED AND SHOULD PRINT THE SAME NUMBER FOR EACH ITERATOR
    int value = 0;
    int CSFTotal = 0;
    int eigenTotal = 0;
    int genericTotal = 0;

    string fileName = "test.bin"; // Input.bin is a working form of CSF. The Constructor makes test.bin, but it is not working

    // generating a large random eigen sparse
    Eigen::SparseMatrix<int> myMatrix(numRows, numCols);
    myMatrix.reserve(Eigen::VectorXi::Constant(numRows, numCols));
    myMatrix = generateMatrix<int>(numRows, numCols, sparsity, seed);
    myMatrix.makeCompressed();

    // Converting to CSF
    CSF::SparseMatrix* CSFMatrix = new CSF::SparseMatrix(myMatrix);

    //////////////////////////////CSF Iterator//////////////////////////////

    // This block of code reads through the whole matrix and adds the sum of all values to total
    // It currently does not work, but it is a good starting point for CSF

    cout << "Testing Iterator" << endl;

    CSF::iterator<int>* newIter = new CSF::iterator<int>(*CSFMatrix);
    // CSF::CSFIterator<int>* newIter = new CSF::CSFIterator<int>(fileName.c_str());

    vector<int> SRLEVector;

    while (newIter) {
        newIter++;
        CSFTotal += newIter->operator*();
        SRLEVector.push_back(newIter->operator*());
        if (newIter->operator*() != value) {
            value = newIter->operator*();
        }
    }

    cout << "CSF Total: " << CSFTotal << endl;

    //////////////////////////////CSC innerIterator////////////////////////////////
    // generating a large random eigen sparse

    // The next two blocks do essentially the same as the first but only go through the CSC matrix

    cout << "Testing Eigen" << endl;

    // begin timing
    vector<int> eigenVector;
    for (int i = 0; i < numCols; ++i) {
        for (Eigen::SparseMatrix<int>::InnerIterator it(myMatrix, i); it; ++it) {
            eigenTotal += it.value();
            eigenVector.push_back(it.value());
        }
    }

    /**
     * Testing to see if the vectors match
     */

    sort(SRLEVector.begin(), SRLEVector.end());
    sort(eigenVector.begin(), eigenVector.end());

    cout << "SRLE Vector" << endl;
    for (auto j : SRLEVector) {
        cout << j << " ";
    }
    cout << endl
        << endl;
    cout << "Eigen Vector" << endl;
    for (auto j : eigenVector) {
        cout << j << " ";
    }
    cout << endl;

    cout << "InnerIterator Total: " << eigenTotal << endl;

    //////////////////////////////GENERIC CSC Iterator////////////////////////////////
    cout << "Testing CSC Iterator" << endl;
    GenericCSCIterator<int> iter2 = GenericCSCIterator<int>(myMatrix);
    while (iter2.operator bool()) {
        genericTotal += iter2.operator*();
        iter2.operator++();
    }
    cout << "CSC Total: " << genericTotal << endl;

    if (genericTotal == eigenTotal && eigenTotal == CSFTotal) {
        cout << "All iterators are working" << endl;
    }
    else {
        cout << "Something is wrong" << endl;
    }
}

template <typename T>
Eigen::SparseMatrix<T> generateMatrix(int numRows, int numCols, int sparsity, uint64_t seed) {
    // generate a random sparse matrix
    rng randMatrixGen = rng(seed);

    Eigen::SparseMatrix<T> myMatrix(numRows, numCols);
    myMatrix.reserve(Eigen::VectorXi::Constant(numRows, numCols));

    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            if (randMatrixGen.draw<int>(i, j, sparsity)) {
                myMatrix.insert(i, j) = 10 * randMatrixGen.uniform<double>(j);
            }
        }
    }
    return myMatrix;
}