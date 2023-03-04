

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

    template <typename T, typename indexType, int compressionLevel>
    void scalarMultiply(CSF::SparseMatrix<T, indexType, compressionLevel>& matrix, int scalar) {
        CSF::Iterator<T, T, compressionLevel> iter = CSF::Iterator<T, T, compressionLevel>(matrix);

        //Iterate through the matrix and multiply each value by the scalar
        while (iter) {
            if (iter.atBeginningOfRun()) {
                iter.setRunValue(scalar * *iter);
            }
            iter++;
        }

        // return CSF::SparseMatrix<T, indexType, compressionLevel>(iter);
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

    template <typename T, typename indexType, int compressionLevel>
    void vectorMultiply(CSF::SparseMatrix<T, indexType, compressionLevel>& matrix, CSF::SparseMatrix<T, indexType, compressionLevel>& vector) {
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
        CSF::Iterator<T, indexType, compressionLevel> matIter = CSF::Iterator<T, indexType, compressionLevel>(matrix);
        CSF::Iterator<T, indexType, compressionLevel> vecIter = CSF::Iterator<T, indexType, compressionLevel>(vector);

        //We need to keep track of the address of the next column
        void* addressOfNextColumn = matIter.getColumnAddress(vecIter.getIndex() + 1);

        //Iterate through the matrix and multiply each value by the scalar
        while (vecIter && matIter) {
            matIter.goToColumn(vecIter.getIndex());

            while (matIter.compareAddress(addressOfNextColumn) == -1 && matIter) {
                if (matIter.atBeginningOfRun()) {

                    std::cout << "multiplying " << *matIter << " by " << *vecIter << " = " << *matIter * *vecIter << std::endl;
                    matIter.setRunValue(*matIter * *vecIter);

                }
                matIter++;
            }
            vecIter++;
            addressOfNextColumn = matIter.getColumnAddress(vecIter.getIndex() + 1);
        }
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
