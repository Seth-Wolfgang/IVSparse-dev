

namespace CSF {
    // testing ground for simple linear algebra operations
    // will be replaced by operators when they are all operational

    /**
     * @brief Scalar multiplication function for CSF matrices
     *
     *
     * @tparam T
     * @param scalar
     * @param column
     * @return
     */

     // template <typename T>
     // CSF::SparseMatrix scalarMultiply(CSF::SparseMatrix matrix, int scalar) {
     //     CSF::SparseMatrix result = CSF::SparseMatrix(matrix);
     //     CSF::Iterator<T> originalIter = CSF::Iterator<T>(matrix);
     //     CSF::Iterator<T> resultIter = CSF::Iterator<T>(result);

     //     //Inital run
     //     resultIter.setNewValue(scalar * *originalIter);

     //     //Iterate through the matrix and multiply each value by the scalar
     //     while (originalIter) {
     //         originalIter++;

     //         if (*originalIter != *resultIter) {
     //             resultIter++;
     //             // cout << "EQ: " << scalar << " * " << *originalIter << " = " << scalar * *originalIter << endl;
     //             resultIter.setNewValue(scalar * *originalIter);

     //             continue;
     //         }
     //         resultIter++;
     //     }

     //     return result;
     // }

     /**
      * @brief Scalar multiplication function without return (WIP)
      *
      * @tparam T
      * @param matrix
      * @param scalar
      * @return CSF::SparseMatrix
      */

    template <typename T, typename indexType, int compressionLevel>
    void scalarMultiply(CSF::SparseMatrix<T, indexType, compressionLevel> matrix, int scalar) {
    CSF::Iterator<T, T, compressionLevel> iter = CSF::Iterator<T, T, compressionLevel>(matrix);

        //Iterate through the matrix and multiply each value by the scalar
        while (iter) {
            if (iter.atBeginningOfRun()) {
                iter.setRunValue(scalar * *iter);
            }
            iter++;
        }
    }

    /**
    * @brief Vector multiplication function for CSF Vectors
    *
    *
    * @tparam T
    * @param scalar
    * @param column
    * @return
    */

    // template <typename T, typename, indexType, int compressionLevel>
    // void vectorMultiply(CSF::SparseMatrix<T, indexType, compressionLevel> matrix, CSF::SparseMatrix<T, indexType, compressionLevel> vector) {
    //     if (matrix.getNumCols() == vector.getNumRows()) {
    //         std::cerr << "Matrix and vector dimensions do not match" << endl;
    //     }

    //     CSF::Iterator<T> matIter = CSF::Iterator<T>(matrix);
    //     CSF::Iterator<T> vecIter = CSF::Iterator<T>(vector);
    //     void* addressOfNextColumn = matIter.getColumnAddress(vecIter.getIndex() + 1);

    //     //Iterate through the matrix and multiply each value by the scalar
    //     while (vecIter) {
    //         matIter.goToColumn(vecIter.getIndex());

    //         //TODO: check to see if we're at address of next column
    //         while (matIter.compareAddress(addressOfNextColumn)) {
    //             if (matIter.atBeginningOfRun())
    //                 iter.setRunValue(*iter * *vecIter)
    //                 matIter++;
    //         }
    //         vecIter++;
    //         addressOfNextColumn = matIter.getColumnAddress(vecIter.getIndex() + 1);
    //     }

    // }


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
     //     CSF::Iterator<T> iter1 = CSF::Iterator<T>(vec1);
     //     CSF::Iterator<T> iter2 = CSF::Iterator<T>(vec2);

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
