/*
Filename: CSF_SparseMatrix.hpp

Header file for the class defintion of the sparse matrix class
for compressed sparse fiber storage format (NON-NEGATIVE)

Authors: Skyler Ruiter, Seth Wolfgang
Version: 0.3.0
*/

#pragma once

// Namespace CSF start
namespace CSF {
    /* Compressed Sparse Fiber Sparse Matrix Class (NON-NEGATIVE)

    CSF::SparseMatrix<T, T_index, compression_level>
    CSF::SparseMatrix<T> (defaults to compression level 3 and value type = index type)

    Takes in data and compresses it into a propreitary sparse matrix
    format that specializes in compressing highly redundant non-negative
    data, partiaculary with a strong negative binomal distribution

    <typename T> (type of values stored in the sparse matrix)
    <typename T_index> (type of indices stored in sparse matrix)
        --defaulted to type T--
    <int compression_level> (the level of compression desired for the sparse matrix)
        --defaulted to 3--

    Compression Levels:
        1. Wrapped CSC Storage
        2. Compressed Sparse Fiber Base
        3. Compressed Sparse Fiber w/ Positive Delta Encoded & Byte Packed Indices

    */
    template <typename T, typename T_index=uint64_t, int compression_level=3>
    class SparseMatrix {
        // Private data members and functions
        private:
            //* ------------------- Class data -------------------

            // Compression delimiter
            uint8_t delim = 0;

            // dimensions and size of sparse matrix
            uint32_t num_rows;
            uint32_t num_cols;
            uint32_t num_nonzeros;

            // Data types for matrix values_t and indices
            uint32_t row_t;
            uint32_t col_t;
            uint32_t val_t;

            // compression size
            size_t compression_size;

            // void pointers to beginning and end
            void *comp_ptr; // end ptr
            void *begin_ptr; // begin ptr

            //* ----------------- Private member functions -----------------

            /* Allocate dynamic memory for sparse matrix

            Private member function that allocates roughly a CSC 
            amount of space for the sparse matrix to be compressed into

            --- if matrix is thowing errors atempt to allocate more space ---
            */
            void allocate_memory();


            /* Find min bytes to store size
            
            Returns the number of bytes required to store size,
            mainly used a helper function to byte pack

            */
            uint8_t byte_width(size_t size);

            //* ----------------- End Private member functions -----------------

        // Public data and member functions
        public:
            //* ----------------- Sparse Matrix Constructors -----------------

            /* Eigen Constructor Definiiton
            
            Takes in an Eigen::SparseMatrix<T> and compresses it 
            to compression_level and conditionally destroys values
            based on the destroy paramater
            
            */
            SparseMatrix(Eigen::SparseMatrix<T>& mat, bool destroy = false);


            /* Base CSC Array Constructor Definition
            
            Takes in 3 arrays correlating to CSC, values, indices, and col pointers
            as well as their respective sizes and the overall dimensions of the matrix
            and is then compresses the data into the class, with conditional destruction 

            */
            template <typename values_t, typename row_ind, typename col_ind>
            SparseMatrix(values_t **vals, row_ind **indexes, col_ind **col_p,
                        size_t non_zeros, size_t row_num, size_t col_num,
                        bool destroy = false);


            /* File Read Constructor Definition
            
            Takes a filename and reads the file and initializes the sparse matrix

            */
            SparseMatrix(const char *filename);


            /* Class Destructor Decleration
            
            frees begin_ptr
            */
            ~SparseMatrix();

            //* ----------------- Public Member Functions -----------------

            // Returns the total size of the sparse matrix in bytes
            size_t byte_size();

            // returns a pointer to the beginning of the compression
            // TODO: make a copy of the ptr, dont return the actual pointer
            void* beginPtr();

            void* endPtr();

            void write(const char *filename);

            //* ----------------- Sparse Matrix Iterator -----------------

            class Iterator;

            // class Col {
                
            //     template <typename index_t>
            //     Col (index_t col) {
            //         it = Iterator(matrix, col)
            //     }

            //     Eigen::Vector<T, 1, -1> operator*(Eigen::Vector<T, 1, -1>) {

            //     }

            //     private:
            //         Iterator& it;
            // }


            // Column(index_t col) {
            //     Col()
            //     // pass in data for column needed
            // }

    };


    // Compression Level 1 partial template specialization for Sparse Matrix class
    template <typename T, typename T_index>
    class SparseMatrix<T, T_index, 1> {
        private:
            //* ------------------- Class data -------------------

            // Compression delimiter
            uint8_t delim = 0;

            // dimensions and size of sparse matrix
            uint32_t num_rows;
            uint32_t num_cols;
            uint32_t num_nonzeros;

            // Data types for matrix values_t and indices
            uint32_t row_t;
            uint32_t col_t;
            uint32_t val_t;

            // compression size
            size_t compression_size;

            // void pointers to beginning and end
            void *comp_ptr;  // end ptr
            void *begin_ptr; // begin ptr

            
            T *values;
            T_index *indices;
            T_index *col_p;
        
        public:

        SparseMatrix(Eigen::SparseMatrix<T> &mat, bool destroy = false);

        class Iterator;
    };

    
}