#include <Eigen/Sparse>
#include <iostream>

#include "misc/matrix_creator.cpp"

int main(int argc, char** argv) {
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
    while (it) {
        std::cout << it.row() << " " << it.col() << " " << it.value() << std::endl;
        ++it;
    }


    for (size_t i = 0; i < myMatrix.cols(); i++) {

        for (Eigen::SparseMatrix<int>::InnerIterator it(myMatrix, i); it; ++it) {

        }
    }

    int *values = myMatrix.valuePtr();
    int *indexes = myMatrix.innerIndexPtr();
    int *col_p = myMatrix.outerIndexPtr();

    std::cout << "values: " << std::endl;
    for (size_t i = 0; i < myMatrix.nonZeros(); i++) {
        std::cout << values[i] << " ";
    }

    std::cout << std::endl;

    Eigen::SparseMatrix<int, Eigen::ColMajor ,short> myMatrix2(numRows, numCols);


    return 0;

}

// template <typename T, int compression_level>
// SparseMatrix<T, compression_level>::SparseMatrix(Eigen::SparseMatrix<T> &mat)
// {
//     mat.makeCompressed();

//     size_t nnz = mat.nonZeros();
//     T *vals_arr = new T[nnz];
//     T *indexes_arr = new T[nnz];
//     T *col_p_arr = new T[mat.outerSize() + 1];

//     // Copy data from Eigen
//     std::memcpy(vals_arr, mat.valuePtr(), nnz * sizeof(T));
//     std::memcpy(indexes_arr, mat.innerIndexPtr(), nnz * sizeof(T));
//     std::memcpy(col_p_arr, mat.outerIndexPtr(), (mat.outerSize() + 1) * sizeof(T));

//     T **vals = &vals_arr;
//     T **indexes = &indexes_arr;
//     T **col_p = &col_p_arr;

//     // Construct CSF
//     CSF::SparseMatrix<T, compression_level> tempMatrix = CSF::SparseMatrix<T, compression_level>(vals, indexes, col_p, nnz, mat.rows(), mat.cols(), compression_level);

//     num_rows = tempMatrix.num_rows;
//     num_cols = tempMatrix.num_cols;
//     num_nonzeros = tempMatrix.num_nonzeros;

//     // Data types for matrix values_t and indices
//     row_t = tempMatrix.row_t;
//     col_t = tempMatrix.col_t;
//     val_t = tempMatrix.val_t;

//     // compression size
//     compression_size = tempMatrix.compression_size;

//     // void pointers for compression
//     comp_ptr = tempMatrix.comp_ptr;
//     begin_ptr = tempMatrix.begin_ptr;

//     // Free memory
//     delete[] vals_arr;
//     delete[] indexes_arr;
//     delete[] col_p_arr;
// }

// // dedicated eigen constructor
// template <typename T, int compression_level>
// SparseMatrix<T, compression_level>::SparseMatrix(Eigen::SparseMatrix<T> &mat, bool destroy = false)
// {
//     // compress the matrix if not already
//     mat.makeCompressed();

//     // initialize data
//     num_rows = mat.rows();
//     num_cols = mat.cols();
//     num_nonzeros = mat.nonZeros();

//     row_t = byte_width(num_rows);
//     col_t = byte_width(num_cols);
//     val_t = sizeof(T);

//     // allocate memory for compression
//     allocate_memory();

//     // !! Debug ptr
//     void *debug = begin_ptr;

//     // Construct metadata --------------------
//     // * <row_t, col_t, val_t, num_rows, num_cols, [col_pointers], {...runs...}>

//     // row, col, and val sizes onto compression
//     *(uint32_t *)(comp_ptr) = row_t;
//     comp_ptr = (uint32_t *)(comp_ptr) + 1;

//     *(uint32_t *)(comp_ptr) = col_t;
//     comp_ptr = (uint32_t *)(comp_ptr) + 1;

//     *(uint32_t *)(comp_ptr) = val_t;
//     comp_ptr = (uint32_t *)(comp_ptr) + 1;

//     // Number of Rows and Cols onto compression
//     *(uint32_t *)(comp_ptr) = num_rows;
//     comp_ptr = (uint32_t *)(comp_ptr) + 1;

//     *(uint32_t *)(comp_ptr) = num_cols;
//     comp_ptr = (uint32_t *)(comp_ptr) + 1;

//     // Create a space for col pointers
//     uint64_t *col_pointers = (uint64_t *)(comp_ptr);
//     comp_ptr = (uint64_t *)(comp_ptr) + (uint64_t)(num_cols);

//     // Put a delim at the end of the metadata
//     *(uint32_t *)(comp_ptr) = delim;
//     comp_ptr = (uint32_t *)(comp_ptr) + 1;
//     // End of Metadata --------------------

//     // Loop through each column
//     for (size_t i = 0; i < num_cols; i++)
//     {
//         // update the col pointer
//         col_pointers[i] = (uint64_t)(comp_ptr) - (uint64_t)(begin_ptr);

//         // loop through each row in the column
//         for (Eigen::SparseMatrix<T>::InnerIterator it(mat, i); it; ++it)
//         {
//             if (it.val() != 0)
//             {
//                 // new value found

//                 // add the found value to run
//                 *(T *)(comp_ptr) = it.val();
//                 comp_ptr = (T *)(comp_ptr) + 1;

//                 // create an index pointer to update index type later
//                 void *help_ptr = comp_ptr;

//                 // default index size is value type
//                 *(T *)(comp_ptr) = (uint8_t)sizeof(T);
//                 comp_ptr = (uint8_t *)(comp_ptr) + 1;

//                 // add the found index to run
//                 *(T *)(comp_ptr) = it.row();
//                 comp_ptr = (T *)(comp_ptr) + 1;

//                 // loop through the rest of the column
//                 for (Eigen::SparseMatrix<T>::InnerIterator it2(mat, i); it2; ++it2)
//                 {
//                     if (it2.val() == it.val() && it2.row() > it.row())
//                     {
//                         // new value found

//                         // add the found index to run
//                         *(T *)(comp_ptr) = it2.row();
//                         comp_ptr = (T *)(comp_ptr) + 1;

//                         // set current index to zero
//                         it2.valueRef() = 0;
//                     }
//                 }

//                 // set origianl index to zero
//                 it.valueRef() = 0;

//                 // positive delta encode the indexes

//                 if (compression_level == 3)
//                 {

//                     // set variable for max element
//                     size_t max_index = 0;

//                     // find the number of elements found for unique value
//                     size_t num_elements = (T *)(comp_ptr) - ((T *)(help_ptr));

//                     // bring comp_ptr back to being pointed at last found index
//                     comp_ptr = (row_ind *)(comp_ptr)-1;

//                     // loop moves comp_ptr backwards through indices and positive delta encodes them
//                     for (size_t k = 0; k < num_elements - 1; k++)
//                     {

//                         // subtract element from one before it
//                         *(T *)(comp_ptr) = *(T *)(comp_ptr) - *((T *)(comp_ptr)-1);

//                         // if bigger then prev max make curr max idx
//                         if (*(T *)(comp_ptr) > max_index)
//                         {
//                             max_index = *(T *)(comp_ptr);
//                         }

//                         comp_ptr = (T *)(comp_ptr)-1; // loop control
//                     }

//                     // set index pointer to correct size for run
//                     *(uint8_t *)(help_ptr) = byte_width(max_index);
//                     help_ptr = (uint8_t *)(help_ptr) + 1;
//                 }
//                 else if (compression_level = 2)
//                 {
//                     // add delim to end of run
//                     *(T *)(comp_ptr) = delim;
//                     comp_ptr = (T *)(comp_ptr) + 1;

//                     // bring up help ptr to comp ptr
//                     help_ptr = comp_ptr;
//                 }
//             }
//         }
//     }
// }