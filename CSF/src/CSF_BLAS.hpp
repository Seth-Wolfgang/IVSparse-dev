

namespace CSF {

    // testing ground for simple linear algebra operations
    // will be replaced by operators when they are all operational


     /**
      * @brief Scalar multiplication function without return (WIP)
      *
      * @tparam T
      * @param matrix
      * @param scalar
      * @return CSF::SparseMatrix
      */

/*************************************************************************************************************************
 *                                                                                                                       *
 *                                                                                                                       *
 *                  DO NOT EDIT SCALAR MULTIPLY - IT IS NOW THE SparseMatrix::Operator * (T scalar)                      *
 *                                                                                                                       *                                                                                                                                    
 *                                                                                                                       *
 ************************************************************************************************************************/



    // template <typename T, typename indexType, int compressionLevel>
    // CSF::SparseMatrix<T, indexType, compressionLevel> scalarMultiply(CSF::SparseMatrix<T, indexType, compressionLevel>& matrix, int scalar) {
    //     // void scalarMultiply(CSF::SparseMatrix<T, indexType, compressionLevel>& matrix, int scalar) {
    //     typename CSF::SparseMatrix<T, indexType, compressionLevel>::Iterator iter(matrix);

    //     //Iterate through the matrix and multiply each value by the scalar
    //     while (iter) {
    //         if (iter.atBeginningOfRun()) {
    //             iter.setRunValue(scalar * *iter);
    //         }
    //         iter++;
    //     }

    //     return CSF::SparseMatrix<T, indexType, compressionLevel>(iter);
    // }

    /**
    * @brief Vector multiplication function for CSF Vectors
    *
    *
    * @tparam T
    * @param scalar
    * @param column
    * @return
    */

    template <typename T, typename indexType, int compressionLevel>
    CSF::SparseMatrix<T, indexType, compressionLevel> vectorMultiply(CSF::SparseMatrix<T, indexType, compressionLevel>& matrix, CSF::SparseMatrix<T, indexType, compressionLevel> vector) {

        //Check that the matrix and vector dimensions match or if the vector is actually a vector
        if (matrix.cols() != vector.rows() || vector.cols() != 1) {
            std::cerr << "Matrix and vector dimensions do not match" << std::endl;

            if (matrix.cols() != vector.rows()) {
                std::cerr << "Matrix and vector dimensions do not match" << std::endl;
                std::cerr << "Matrix has " << matrix.cols() << " columns and vector has " << vector.rows() << " rows" << std::endl;
            }
            else {
                std::cerr << "Given vector parameter is not a column vector" << std::endl;
                std::cerr << "Vector has " << vector.cols() << " columns" << std::endl;
            }
            exit(-1);
        }

        //We need two iterators to iterate through the matrix and vector
        typename CSF::SparseMatrix<T, indexType, compressionLevel>::Iterator matIter(matrix);
        typename CSF::SparseMatrix<T, indexType, compressionLevel>::Iterator vecIter(vector);

        //We need to keep track of the address of the next column
        void* addressOfNextColumn = matIter.getColumnAddress(vecIter.getIndex() + 1);

        //Iterate through the matrix and multiply each value by the scalar at the index of the vector
        while (vecIter && matIter) {
            vecIter++;
            // std::cout << "vecIter index: " << vecIter.getIndex() << std::endl;
            matIter.goToColumn(vecIter.getIndex());
            addressOfNextColumn = matIter.getColumnAddress(vecIter.getIndex() + 1);

            // While mateIter is less than the address of the next column
            while (matIter.compareAddress(addressOfNextColumn) == -1) {
                if (matIter.atBeginningOfRun()) {

                    // std::cout << "multiplying " << *matIter << " by " << *vecIter << " = " << *matIter * *vecIter << std::endl;
                    matIter.setRunValue(*matIter * *vecIter);

                    // if the last of the binary data is an index, the function might continue
                    // So we have a safeguard here. If this statement is in the while loop, it will not
                    // be successful in multiplying the last value. 
                    // Ex. A run where -> (3) [0] *end* where 0 is where the end pointer points to. 3 is a value, and 0 is the final index of the CSF matrix.
                    if (matIter)
                        break;
                }
                matIter++;
            }

        }
        
        return CSF::SparseMatrix<T, indexType, compressionLevel>(matIter);
    }


    /**
     * @brief Dot product function for CSF Vectors
     *
     *
     * @tparam T
     * @param vec1
     * @param vec2
     * @return
     */
     //TODO Will work for any CSC matrix. 
     //TODO IDEA: Form a dictionary of the two vectors and 
     // template <typename T>
     // T dotProduct(CSF::SparseMatrix<T> vec1, CSF::SparseMatrix<T> vec2) {
     //     T result = 0;
        // typename CSF::SparseMatrix<T, indexType, compressionLevel>::Iterator iter1(vector);
        // typename CSF::SparseMatrix<T, indexType, compressionLevel>::Iterator iter2(matrix);

     //     while (iter1 && iter2) {

     //         if(iter1 == iter2) {
     //             result += *iter1 * *iter2;
     //             iter1++;
     //             iter2++;
     //             continue;
     //         }
     //         else if (iter1 < iter2) {
     //             iter1++;
     //             continue;
     //         }
     //         else {
     //             iter2++;
     //         }

     //         //Faster but not portable
     //         // switch (iter1 - iter2){
     //         //     case 1 ... INT_MAX:
     //         //         iter2++;
     //         //         break;
     //         //     case -1 ... INT_MIN:
     //         //         iter1++;
     //         //         break;
     //         //     default:
     //         //         result += *iter1 * *iter2;
     //         //         iter1++;
     //         //         iter2++;
     //         //         break;
     //         // }
     //     }

     //     return result;
     // }
}
