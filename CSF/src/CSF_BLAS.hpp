#pragma once
#include <algorithm>
#include <vector>
#include <iostream>

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

template <typename T>
CSF::SparseMatrix scalarMultiply(CSF::SparseMatrix matrix, int scalar)
{
    CSF::SparseMatrix result = matrix;
    CSF::Iterator<T> matIter = CSF::Iterator<T>(matrix);
    CSF::Iterator<T> resIter = CSF::Iterator<T>(result);

    while (matIter)
    {
        matIter++;

        if (*matIter != *resIter)
        {
            resIter++;
            *resIter = scalar * *matIter;

            continue;
        }
        resIter++;
    }

    return result;
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
// TODO Will work for any CSC matrix.
// TODO IDEA: Form a dictionary of the two vectors and
//  template <typename T>
//  T dotProduct(CSF::SparseMatrix<T> vec1, CSF::SparseMatrix<T> vec2) {
//      T result = 0;
//      CSF::Iterator<T> iter1 = CSF::Iterator<T>(vec1);
//      CSF::Iterator<T> iter2 = CSF::Iterator<T>(vec2);

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
