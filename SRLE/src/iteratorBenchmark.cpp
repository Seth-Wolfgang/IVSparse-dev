#include "include/CSF.hpp"
#include "include/CSF_Lib.hpp"


int main() {
    int matrixSeed = rand();
    int matrixSeed2 = rand();
    int numRows = rand() % 1000 + 1;
    int numCols = rand() % 1000 + 1;

    int sparsity = 20;
    uint64_t seed = matrixSeed * matrixSeed2;

    // cout << iteratorBenchmark(544, 130, 20, 1563481712) << endl;

    for (int i = 0; i < 10000; i++) {
        matrixSeed = rand();
        matrixSeed2 = rand();
        numRows = rand() % 100 + 10;
        numCols = rand() % 100 + 10;
        // sparsity = rand() % 50 + 1;
        cout << "numRows: " << numRows << endl;
        cout << "numCols: " << numCols << endl;
        seed = matrixSeed * matrixSeed2;
        cout << "i: " << i << endl;
        if (!iteratorBenchmark(numRows, numCols, sparsity, seed - matrixSeed2)) {

            cout << "Something went wrong" << endl;
            cout << "numRows: " << numRows << endl;
            cout << "numCols: " << numCols << endl;
            cout << "sparsity: " << sparsity << endl;
            cout << "Matrix seed: " << matrixSeed << " * " << matrixSeed2 << endl;
            cout << "i: " << i << endl;
            return 0;
        }
    }
    cout << " \u001b[32mEverything worked!!\u001b[0m" << endl;
    return 1;
}

bool iteratorBenchmark(int numRows, int numCols, int sparsity, uint64_t seed) {
    // TO ENSURE EVERYTHING WORKS, THE TOTAL SUM OF ALL VALUES IS CALUCLATED AND SHOULD PRINT THE SAME NUMBER FOR EACH ITERATOR
    int value = 0;
    int CSFTotal = 0;
    int eigenTotal = 0;
    int genericTotal = 0;

    string fileName = "test.bin"; // Input.bin is a working form of CSF. The Constructor makes test.bin, but it is not working

    // generating a large random eigen sparse
    Eigen::SparseMatrix<int> myMatrix(numRows, numCols);
    myMatrix = generateMatrix<int>(numRows, numCols, sparsity, seed);
    myMatrix.makeCompressed();

    // Converting to CSF
    CSF::SparseMatrix CSFMatrix = CSF::SparseMatrix(myMatrix);

    //////////////////////////////CSF Iterator//////////////////////////////

    // This block of code reads through the whole matrix and adds the sum of all values to total
    // It currently does not work, but it is a good starting point for CSF

    // cout << "Testing Iterator" << endl;

    CSF::iterator<int> newIter = CSF::iterator<int>(CSFMatrix);
    // CSF::CSFIterator<int>* newIter = new CSF::CSFIterator<int>(fileName.c_str());

    vector<int> SRLEVector;

    while (newIter.operator bool()) {
        newIter++;
        CSFTotal += newIter.getValue();
        SRLEVector.push_back(newIter.getValue());
        if (newIter.getValue() != value) {
            value = newIter.getValue();
        }
    }

    // cout << "CSF Total: " << CSFTotal << endl;

    //////////////////////////////CSC innerIterator////////////////////////////////
    // generating a large random eigen sparse

    // The next two blocks do essentially the same as the first but only go through the CSC matrix

    // cout << "Testing Eigen" << endl;

    // begin timing
    vector<int> eigenVector;
    for (int i = 0; i < numCols; ++i) {
        for (Eigen::SparseMatrix<int>::InnerIterator it(myMatrix, i); it; ++it) {
            eigenTotal += it.value();
            eigenVector.push_back(it.value());
        }
    }

    //print eigen matrix




    // cout << "InnerIterator Total: " << eigenTotal << endl;

    //////////////////////////////GENERIC CSC Iterator////////////////////////////////
    // cout << "Testing CSC Iterator" << endl;
    GenericCSCIterator<int> iter2 = GenericCSCIterator<int>(myMatrix);
    while (iter2.operator bool()) {
        genericTotal += iter2.operator*();
        iter2.operator++();
    }
    // cout << "CSC Total: " << genericTotal << endl;

    if (genericTotal == eigenTotal && eigenTotal == CSFTotal) {
        return true;
    }
    else {
        cout << "CSF Total: " << CSFTotal << endl;
        cout << "Eigen Total: " << eigenTotal << endl;
        cout << "Generic Total: " << genericTotal << endl;
        cout << "off by: " << CSFTotal - eigenTotal << endl;
        /**
 * Testing to see if the vectors match
 */

 // sort(SRLEVector.begin(), SRLEVector.end());
 // sort(eigenVector.begin(), eigenVector.end());

 // cout << "SRLE Vector" << endl;
 // for (auto j : SRLEVector) {
 //     cout << j << " ";
 // }
 // cout << endl
 //     << endl;
 // cout << "Eigen Vector" << endl;
 // for (auto j : eigenVector) {
 //     cout << j << " ";
 // }
 // cout << endl;

        return false;

    }
}

template <typename T>
Eigen::SparseMatrix<T> generateMatrix(int numRows, int numCols, int sparsity, uint64_t seed) {
    // generate a random sparse matrix
    rng randMatrixGen = rng(seed);

    Eigen::SparseMatrix<T> myMatrix(numRows, numCols);
    myMatrix.reserve(Eigen::VectorXi::Constant(numRows * 10, numCols * 20));
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            if (randMatrixGen.draw<int>(i, j, sparsity)) {
                myMatrix.insert(i, j) = 100 * randMatrixGen.uniform<double>(j);
            }
        }
    }
    return myMatrix;
}