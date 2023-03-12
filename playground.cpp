
#include "CSF/SparseMatrix"
#include "misc/matrix_creator.cpp"
#include <iostream>

int main(int argc, char** argv) {

    int numRows = 50;
    int numCols = 50;
    int sparsity = 4;
    uint64_t seed = 1956553944;
    // uint64_t seed = rand();

    // generating a large random eigen sparse
    Eigen::SparseMatrix<int> myMatrix_e(numRows, numCols);
    myMatrix_e.reserve(Eigen::VectorXi::Constant(numRows, numCols));
    myMatrix_e = generateMatrix<int>(numRows, numCols, sparsity, seed);
    myMatrix_e.prune(0);
    myMatrix_e.makeCompressed();

    // print out the matrix
    //std::cout << myMatrix_e << std::endl;


    // create a csf sparse matrix
    CSF::SparseMatrix<int, uint64_t, 3> myMatrix_csf3(myMatrix_e);
    CSF::SparseMatrix<int, uint64_t, 2> myMatrix_csf2(myMatrix_e);
    CSF::SparseMatrix<int, uint64_t, 1> myMatrix_csf1(myMatrix_e);

    // write the matrix to a file
    // myMatrix_csf3.write("test3.csf");
    // myMatrix_csf2.write("test2.csf");

    // create iterators for 2 and 3
    CSF::SparseMatrix<int, uint64_t, 3>::Iterator it3(myMatrix_csf3);
    CSF::SparseMatrix<int, uint64_t, 2>::Iterator it2(myMatrix_csf2);

    // check that all values are the same for 2 and 3 using the iterator
    while (it3) {
        it3++;
        it2++;
        if (*it3 != *it2) {
            std::cout << "ERROR: values are not the same" << std::endl;
            return 1;
        }
    }

    // print out a confirmation
    std::cout << "SUCCESS: values are the same" << std::endl;

    // loop through all values in the eigen matrix and add them together
    int eigensum = 0;
    for (int k = 0; k < myMatrix_e.outerSize(); ++k) {
        for (Eigen::SparseMatrix<int>::InnerIterator it(myMatrix_e, k); it; ++it) {
            eigensum += it.value();
        }
    }

    // reset the iterators
    it3.reset();
    it2.reset();

    // loop through all values in the csf matrix and add them together
    int csfsum3 = 0;
    int csfsum2 = 0;
    while (it3) {
        it3++;
        it2++;
        csfsum3 += *it3;
        csfsum2 += *it2;
    }

    // check that the sums are the same
    if (eigensum != csfsum3 || eigensum != csfsum2) {
        std::cout << "ERROR: sums are not the same" << std::endl;

        std::cout << "eigensum: " << eigensum << std::endl;
        std::cout << "csfsum3: " << csfsum3 << std::endl;
        std::cout << "csfsum2: " << csfsum2 << std::endl;

        return 1;
    }

    // print out a confirmation
    std::cout << "SUCCESS: sums are the same" << std::endl;

    // create a matrix from the iterator
    CSF::SparseMatrix<int, uint64_t, 3> myMatrix_csf3_2(it3);
    CSF::SparseMatrix<int, uint64_t, 2> myMatrix_csf2_2(it2);

    // write the matrix to a file
    // myMatrix_csf3_2.write("test3_2.csf");
    // myMayrix_csf_2_2.write("test2_2.csf");

    // check that the matrices are the same
    if (myMatrix_csf3 != myMatrix_csf3_2 || myMatrix_csf2 != myMatrix_csf2_2) {
        std::cout << "ERROR: matrices are not the same" << std::endl;
        return 1;
    }

    // print out a confirmation
    std::cout << "SUCCESS: matrices are the same" << std::endl;


    // convert the matricies to other matrices

    // csf 3 -> eigen
    Eigen::SparseMatrix<int> myMatrix_e_3 = myMatrix_csf3.to_eigen();

    // csf 2 -> eigen
    Eigen::SparseMatrix<int> myMatrix_e_2 = myMatrix_csf2.to_eigen();

    // make an iterator for the 2nd csf matrix
    CSF::SparseMatrix<int, uint64_t, 2>::Iterator it2_2(myMatrix_csf2);

    // csf 1 -> eigen
    Eigen::SparseMatrix<int> myMatrix_e_1 = myMatrix_csf1.to_eigen();

    // check that the matrices are the same so check if the output of << is the same

    // load the output of << into a string
    std::stringstream ss3;
    ss3 << myMatrix_e_3;
    std::string str3 = ss3.str();

    std::stringstream ss2;
    ss2 << myMatrix_e_2;
    std::string str2 = ss2.str();

    std::stringstream ss1;
    ss1 << myMatrix_e_1;
    std::string str1 = ss1.str();

    // check that the strings are the same
    if (str3 != str2 || str3 != str1) {
        std::cout << "ERROR: eigen matrices are not the same" << std::endl;

        std::cout << myMatrix_e << std::endl;
        std::cout << "str3: " << str3 << std::endl;
        std::cout << "str2: " << str2 << std::endl;
        std::cout << "str1: " << str1 << std::endl;

        return 1;
    }

    // print out a confirmation
    std::cout << "SUCCESS: eigen matrices are the same" << std::endl;


    // convert from csf1 to csf2

    CSF::SparseMatrix<int, uint64_t, 2> myMatrix_csf2_1 = myMatrix_csf1.to_csf2();

    // check that the matrices are the same
    if (myMatrix_csf2 != myMatrix_csf2_1) {
        std::cout << "ERROR: csf2 matrices are not the same" << std::endl;
        return 1;
    }

    // print out a confirmation
    std::cout << "SUCCESS: csf2 matrices are the same" << std::endl;

    
    // convert from csf2 to csf3

    CSF::SparseMatrix<int, uint64_t, 3> myMatrix_csf3_2_2 = myMatrix_csf2_2.to_csf1().to_csf3();

    // check that the matrices are the same 
    if (myMatrix_csf3 != myMatrix_csf3_2_2) {
        std::cout << "ERROR: csf3 matrices are not the same" << std::endl;
        return 1;
    }

    // print out a confirmation
    std::cout << "SUCCESS: csf3 matrices are the same" << std::endl;


    // convert from csf3 to csf2

    CSF::SparseMatrix<int, uint64_t, 2> myMatrix_csf2_3 = myMatrix_csf3.to_csf1().to_csf2();

    // check that the matrices are the same
    if (myMatrix_csf2 != myMatrix_csf2_3) {
        std::cout << "ERROR: csf2 matrices are not the same" << std::endl;
        return 1;
    }

    // print out a confirmation
    std::cout << "SUCCESS: csf2 matrices are the same" << std::endl;


    // compare two csf1 matricies that are the exact same

    // create 2 csf1 matrices from eigen with different names
    CSF::SparseMatrix<int, uint64_t, 1> mytest1(myMatrix_e);
    CSF::SparseMatrix<int, uint64_t, 1> mytest2(myMatrix_e);

    // check that the matrices are the same
    if (mytest1 != mytest2) {
        std::cout << "ERROR: csf1 matrices are not the same" << std::endl;
        return 1;
    }

    // print out a confirmation
    std::cout << "SUCCESS: csf1 matrices are the same" << std::endl;


    // change the value type of a CSF1 matrix using change_value_type()
    CSF::SparseMatrix<uint32_t, uint64_t, 1> myMatrix_csf1_2 = myMatrix_csf1.change_val_type<uint32_t>();

    // write the matrix to a file
    //myMatrix_csf1_2.write("test1_2.csf");

    // convert to CSF3
    CSF::SparseMatrix<uint32_t, uint64_t, 3> myMatrix_csf3_22 = myMatrix_csf1_2.to_csf3();

    // write the matrix to a file
    //myMatrix_csf3_22.write("test3_22.csf");

    // convert back to CSF1
    CSF::SparseMatrix<uint32_t, uint64_t, 1> myMatrix_csf1_22 = myMatrix_csf3_22.to_csf1();

    // change the value type back to int
    CSF::SparseMatrix<int, uint64_t, 1> myMatrix_csf1_222 = myMatrix_csf1_22.change_val_type<int>();

    // compress it to csf2
    CSF::SparseMatrix<int, uint64_t, 2> myMatrix_csf2_222 = myMatrix_csf1_222.to_csf2();

    // see if the matrices are the same
    if (myMatrix_csf2_222 != myMatrix_csf2) {
        std::cout << "ERROR: csf2 matrices are not the same" << std::endl;
        return 1;
    }

    // print out a confirmation
    std::cout << "SUCCESS: csf2 matrices are the same!!!!!!!!!!!!" << std::endl;


    // Test changing index type
    CSF::SparseMatrix<int, uint32_t, 1> myMatrix_csf1_3 = myMatrix_csf1.change_idx_type<uint32_t>();

    // convert to CSF3
    CSF::SparseMatrix<int, uint32_t, 3> myMatrix_csf3_3 = myMatrix_csf1_3.to_csf3();

    // convert back to CSF1
    CSF::SparseMatrix<int, uint32_t, 1> myMatrix_csf1_33 = myMatrix_csf3_3.to_csf1();

    // change the index type back to uint64_t
    CSF::SparseMatrix<int, uint64_t, 1> myMatrix_csf1_333 = myMatrix_csf1_33.change_idx_type<uint64_t>();

    // compress it to csf2
    CSF::SparseMatrix<int, uint64_t, 2> myMatrix_csf2_333 = myMatrix_csf1_333.to_csf2();

    // see if the matrices are the same
    if (myMatrix_csf2_333 != myMatrix_csf2) {
        std::cout << "ERROR: csf2 matrices are not the same" << std::endl;
        return 1;
    }

    // print out a confirmation
    std::cout << "SUCCESS: csf2 matrices are the same!!!!!!!!!!!! AGAIN" << std::endl;


    // test the new CSF1 constructor
    CSF::SparseMatrix<uint32_t, uint32_t, 1> testing(myMatrix_csf3);

    // write to file
    testing.write("testing.csf");

    // convert myMatrix_csf3 to CSF1
    CSF::SparseMatrix<int, uint64_t, 1> myMatrix_csf1_4 = myMatrix_csf3.to_csf1();

    // change the value type
    CSF::SparseMatrix<uint32_t, uint64_t, 1> myMatrix_csf1_5 = myMatrix_csf1_4.change_val_type<uint32_t>();

    // change the index type
    CSF::SparseMatrix<uint32_t, uint32_t, 1> myMatrix_csf1_6 = myMatrix_csf1_5.change_idx_type<uint32_t>();

    // compare the matrices
    if (myMatrix_csf1_6 != testing) {
        std::cout << "ERROR: csf1 matrices are not the same" << std::endl;
        return 1;
    }

    // print out a confirmation
    std::cout << "SUCCESS: csf1 matrices are the same!!!!!!!!!!!! AGAIN AGAIN" << std::endl;

    //myMatrix_csf3.print();

    return 0;
}