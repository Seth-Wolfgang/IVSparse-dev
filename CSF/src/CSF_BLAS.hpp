

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
