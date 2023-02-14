#pragma once 

#define DEBUG 1

#include <type_traits>

namespace CSF {

    // General Constructors

    template <typename T, typename T_index, int compression_level>
    SparseMatrix<T, T_index, compression_level>::SparseMatrix()
    {
        row_t = 8;
        col_t = 8;
        val_t = sizeof(T);

        begin_ptr = malloc(28);
        comp_ptr = begin_ptr;

        create_metadata();
    }

    template <typename T, typename T_index, int compression_level>
    SparseMatrix<T, T_index, compression_level>::SparseMatrix(Eigen::SparseMatrix<T> &mat, bool destroy)
    {
        // check that the matrix is in column major order
        assert(mat.IsRowMajor == false);

        // check that the matrix is in compressed format
        if (mat.isCompressed() == false)
            mat.makeCompressed();

        // intialize the matrix
        num_rows = mat.rows();
        num_cols = mat.cols();
        num_nonzeros = mat.nonZeros();

        T *vals;
        T_index *indexes;
        T_index *col_p;

        if (destroy) {
            vals = mat.valuePtr();
            indexes = mat.innerIndexPtr();
            col_p = mat.outerIndexPtr();

        } else {
            indexes = mat.innerIndexPtr();
            col_p = mat.outerIndexPtr();

            // deep copy the values
            vals = (T *) malloc(num_nonzeros * sizeof(T));
            memcpy(vals, mat.valuePtr(), num_nonzeros * sizeof(T));
        }

        compress(vals, indexes, col_p);

        // free the memory if the matrix was destroyed
        if (!destroy) {
            free(vals);
        }
        
    }

    template <typename T, typename T_index, int compression_level>
    template <typename values_t, typename row_ind, typename col_ind>
    SparseMatrix<T, T_index, compression_level>::SparseMatrix(values_t **vals, row_ind **indexes, col_ind **col_p,
                                                              size_t non_zeros, size_t row_num, size_t col_num,
                                                              bool destroy)
    {
        // Check that templates T and values_t are the same
        static_assert(std::is_same<T, values_t>::value, "Your matrix must be of the same type as the constructor");

        // TODO: index type checking (T_index and row_ind / col_ind)

        // intialize the matrix
        num_rows = row_num;
        num_cols = col_num;
        num_nonzeros = non_zeros;

        if (!destroy) {
            // allocate space for a copy of vals
            values_t *vals_copy = (values_t *)malloc(num_nonzeros * sizeof(values_t));

            // copy vals into vals_copy
            memcpy(vals_copy, *vals, num_nonzeros * sizeof(values_t));

            // call compress with vals_copy
            compress(vals_copy, *indexes, *col_p);

            // free vals_copy
            free(vals_copy);
        } else {
            compress(*vals, *indexes, *col_p);
        }

    }

    template <typename T, typename T_index, int compression_level>
    SparseMatrix<T, T_index, compression_level>::SparseMatrix(const char *filename)
    {
        // Open the file
        FILE *fp = fopen(filename, "rb");

        // Check that the file exists
        if (fp == NULL) {
            printf("File %s does not exist\n", filename);
            exit(1);
        }

        // get size of file
        fseek(fp, 0, SEEK_END);
        compression_size = ftell(fp);
        fseek(fp, 0, SEEK_SET);

        // allocate memory for file
        begin_ptr = malloc(compression_size);

        // read in data
        fread(begin_ptr, 1, compression_size, fp);

        // close file
        fclose(fp);

        // set pointers
        comp_ptr = begin_ptr + compression_size;
        void *help_ptr = begin_ptr;

        // get metadata
        compression = *(uint32_t *)(help_ptr);
        help_ptr = (uint32_t *)(help_ptr) + 1;

        // assert that the compression level is the same and throw error
        if (compression != compression_level) {
            printf("Compression level of file does not match the compression level of the constructor\n");
            exit(1);
        }

        row_t = *(uint32_t *)(help_ptr);
        help_ptr = (uint32_t *)(help_ptr) + 1;

        col_t = *(uint32_t *)(help_ptr);
        help_ptr = (uint32_t *)(help_ptr) + 1;

        val_t = *(uint32_t *)(help_ptr);
        help_ptr = (uint32_t *)(help_ptr) + 1;

        // assert that the value type is the same and throw error
        if (val_t != sizeof(T)) {
            printf("Value type of file does not match the value type of the constructor\n");
            exit(1);
        }

        num_rows = *(uint32_t *)(help_ptr);
        help_ptr = (uint32_t *)(help_ptr) + 1;

        num_cols = *(uint32_t *)(help_ptr);
        help_ptr = (uint32_t *)(help_ptr) + 1;

        // make sure that rows and cols are not less than 1
        if (num_rows < 1 || num_cols < 1) {
            printf("Number of rows and columns must be greater than 0\n");
            exit(1);
        }

    }

    template <typename T, typename T_index, int compression_level>
    SparseMatrix<T, T_index, compression_level>::SparseMatrix(CSF::SparseMatrix<T, T_index, compression_level> &mat) 
    {
        // create a deep copy of the matrix
        num_rows = mat.rows();
        num_cols = mat.cols();
        num_nonzeros = mat.nonzeros();

        begin_ptr = malloc(mat.byte_size());
        comp_ptr = (uint8_t *)begin_ptr + mat.byte_size();

        // copy the data
        memcpy(begin_ptr, mat.beginPtr(), mat.byte_size());

        // set the pointers
        void *help_ptr = begin_ptr;

        // get metadata
        compression = *(uint32_t *)(help_ptr);
        help_ptr = (uint32_t *)(help_ptr) + 1;

        row_t = *(uint32_t *)(help_ptr);
        help_ptr = (uint32_t *)(help_ptr) + 1;

        col_t = *(uint32_t *)(help_ptr);
        help_ptr = (uint32_t *)(help_ptr) + 1;

        val_t = *(uint32_t *)(help_ptr);
        help_ptr = (uint32_t *)(help_ptr) + 1;
    }

    template <typename T, typename T_index, int compression_level>
    SparseMatrix<T, T_index, compression_level>::~SparseMatrix()
    {
        free(begin_ptr);
    }


    // Constructor Helper Functions ---------------------------------------------------------------------------

    template <typename T, typename T_index, int compression_level>
    uint64_t* SparseMatrix<T, T_index, compression_level>::create_metadata()
    {
        // Construct Metadata --------------------
        // * <compression, row_t, col_t, val_t, num_rows, num_cols, [col_pointers], {...runs...}>

        // Compression Level onto compression
        *(uint32_t *)(comp_ptr) = compression;
        comp_ptr = (uint32_t *)(comp_ptr) + 1;

        // Row, Col, and Val sizes onto compression
        *(uint32_t *)(comp_ptr) = row_t;
        comp_ptr = (uint32_t *)(comp_ptr) + 1;

        *(uint32_t *)(comp_ptr) = col_t;
        comp_ptr = (uint32_t *)(comp_ptr) + 1;

        *(uint32_t *)(comp_ptr) = val_t;
        comp_ptr = (uint32_t *)(comp_ptr) + 1;

        // Number of Rows and Cols onto compression
        *(uint32_t *)(comp_ptr) = num_rows;
        comp_ptr = (uint32_t *)(comp_ptr) + 1;

        *(uint32_t *)(comp_ptr) = num_cols;
        comp_ptr = (uint32_t *)(comp_ptr) + 1;

        // Create a space for col pointers
        uint64_t *col_pointers = (uint64_t *)(comp_ptr);
        comp_ptr = (uint64_t *)(comp_ptr) + (uint64_t)(num_cols);

        // Put a delim at the end of the metadata
        *(uint32_t *)(comp_ptr) = delim;
        comp_ptr = (uint32_t *)(comp_ptr) + 1;
        // End of Metadata --------------------

        return col_pointers;
    }

    template <typename T, typename T_index, int compression_level>
    template <typename values_type, typename rows_type, typename cols_type>
    void SparseMatrix<T, T_index, compression_level>::compress(values_type *vals, rows_type *indexes, cols_type *col_p)
    {

        // throw an error if the matrix has less than one rows or columns or nonzero values
        if (num_rows < 1 || num_cols < 1 || num_nonzeros < 1)
            throw std::invalid_argument("The matrix must have at least one row, column, and nonzero value");


        // determine the type of each value
        if (compression_level == 2) {
            row_t = sizeof(T_index);
            col_t = sizeof(T_index);
        } else {
            row_t = byte_width(num_rows);
            col_t = byte_width(num_cols);
        }

        val_t = sizeof(values_type);

        // allocate memory for the matrix
        allocate_memory();

        // create pointer to update col pointers
        uint64_t *col_pointers = create_metadata();

        uint8_t last_col_index = 1;

        for (size_t i = 0; i < num_cols; i++) {

            // Update the col pointer
            col_pointers[i] = (uint64_t)(comp_ptr) - (uint64_t)(begin_ptr);

            for (size_t j = col_p[i]; j < col_p[i + 1]; j++) {

                if ((vals)[j] != 0)
                {
                    // New unique value found

                    // Add the found value to run
                    *(values_type *)(comp_ptr) = (vals)[j];
                    comp_ptr = (values_type *)(comp_ptr) + 1;

                    // Create an index pointer to update index type later
                    void *help_ptr = comp_ptr;

                    // default index type to row index type and iterate pointer
                    *(uint8_t *)help_ptr = (uint8_t)sizeof(rows_type);
                    comp_ptr = (uint8_t *)(comp_ptr) + 1;

                    // Add the found index to run
                    *(rows_type *)(comp_ptr) = (indexes)[j];
                    comp_ptr = (rows_type *)(comp_ptr) + 1;

                    // Loop through rest of column to get rest of indices
                    for (size_t k = j + 1; k < (col_p)[i + 1]; k++)
                    {

                        if ((vals)[k] == (vals)[j])
                        {

                            // Found value again

                            // add index of value to run
                            *(rows_type *)(comp_ptr) = (indexes)[k];
                            comp_ptr = (rows_type *)(comp_ptr) + 1;

                            // set value to zero
                            (vals)[k] = 0;
                        }
                    }

                    // Set first index found to 0
                    (vals)[j] = 0;

                    //* Positive delta encode the indices -----------

                    if (compression_level == 3)
                    {

                        // set variable for max element
                        size_t max_index = 0;

                        // find number of elements found for unique value
                        size_t num_elements = (rows_type *)(comp_ptr) - ((rows_type *)(help_ptr));

                        // bring comp_ptr back to being pointed at last found index
                        comp_ptr = (rows_type *)(comp_ptr)-1;

                        // loop moves comp_ptr backwards through indices and positive delta encodes them
                        for (size_t k = 0; k < num_elements - 1; k++)
                        {

                            // subtract element from one before it
                            *(rows_type *)(comp_ptr) = *(rows_type *)(comp_ptr) - *((rows_type *)(comp_ptr)-1);

                            // if bigger then prev max make curr max idx
                            if (*(rows_type *)(comp_ptr) > max_index)
                            {
                                max_index = *(rows_type *)(comp_ptr);
                            }

                            comp_ptr = (rows_type *)(comp_ptr)-1; // loop control
                        }

                        // set index pointer to correct size for run
                        *(uint8_t *)(help_ptr) = byte_width(max_index);
                        help_ptr = (uint8_t *)(help_ptr) + 1;

                        // ! temp solution, def a more optimal solution to be found
                        last_col_index = byte_width(max_index);

                        // write over data with indices of new size, index compression
                        switch (byte_width(max_index))
                        {
                        case 1:

                            // walk the two iterators, compressing down to optimal byte width
                            for (size_t k = 0; k < num_elements; k++)
                            {

                                // set index to uint8_t size
                                *(uint8_t *)(comp_ptr) = (uint8_t) * (rows_type *)(help_ptr);

                                // Iterate pointers
                                comp_ptr = (uint8_t *)(comp_ptr) + 1;
                                help_ptr = (rows_type *)(help_ptr) + 1;
                            }

                            // Add delim
                            *(uint8_t *)(comp_ptr) = delim;
                            comp_ptr = (uint8_t *)(comp_ptr) + 1;

                            break;

                        case 2:
                            // walk the two iterators, compressing down to optimal byte width
                            for (size_t k = 0; k < num_elements; k++)
                            {

                                // set index to uint16_t size
                                *(uint16_t *)(comp_ptr) = (uint16_t) * (rows_type *)(help_ptr);

                                // Iterate pointers
                                comp_ptr = (uint16_t *)(comp_ptr) + 1;
                                help_ptr = (rows_type *)(help_ptr) + 1;
                            }

                            // Add delim
                            *(uint16_t *)(comp_ptr) = delim;
                            comp_ptr = (uint16_t *)(comp_ptr) + 1;

                            break;

                        case 4:
                            // walk the two iterators, compressing down to optimal byte width
                            for (size_t k = 0; k < num_elements; k++)
                            {

                                // set index to uint8_t size
                                *(uint32_t *)(comp_ptr) = (uint32_t) * (rows_type *)(help_ptr);

                                // Iterate pointers
                                comp_ptr = (uint32_t *)(comp_ptr) + 1;
                                help_ptr = (rows_type *)(help_ptr) + 1;
                            }

                            // Add delim
                            *(uint32_t *)(comp_ptr) = delim;
                            comp_ptr = (uint32_t *)(comp_ptr) + 1;

                            break;

                        } // end switch

                        help_ptr = comp_ptr;
                    }
                    else if (compression_level == 2)
                    { // end compression level 3
                        // add delim to end of run
                        *(rows_type *)(comp_ptr) = delim;
                        comp_ptr = (rows_type *)(comp_ptr) + 1;

                        // bring up help ptr to comp ptr
                        help_ptr = comp_ptr;
                    }
                } // end if
            } // end value loop

        } // end column loop

        // remove ending zeros
        for (uint8_t i = 0; i < last_col_index + 1; i++)
        {
            comp_ptr = (uint8_t *)(comp_ptr)-1;
        }

        // find size of file in bytes
        compression_size = (uint8_t *)(comp_ptr) - ((uint8_t *)(begin_ptr)-1);

        // resize data to fit actual size
        begin_ptr = realloc(begin_ptr, compression_size);
    }



    // CSF::SparseMatrix<T, T_index, 1> Constructors ----------------------------------------------------------
    template <typename T, typename T_index>
    SparseMatrix<T, T_index, 1>::SparseMatrix()
    {
    }
    
    template <typename T, typename T_index>
    SparseMatrix<T, T_index, 1>::SparseMatrix(Eigen::SparseMatrix<T> &mat, bool destroy)
    {
        // check that the matrix is in column major order
        assert(mat.IsRowMajor == false);

        // check that the matrix is in compressed format
        if (mat.isCompressed() == false)
            mat.makeCompressed();

        // set size variables
        num_rows = mat.rows();
        num_cols = mat.cols();
        num_nonzeros = mat.nonZeros();

        // throw an error if the matrix has less than one rows or columns or nonzero values
        if (num_rows < 1 || num_cols < 1 || num_nonzeros < 1)
            throw std::invalid_argument("The matrix must have at least one row, column, and nonzero value");

        // assert that T_index is of type int if using this constructor
        static_assert(std::is_same<T_index, int>::value, "T_index must be of type int for eigen matrix constructor");

        // set types
        row_t = sizeof(T_index);
        col_t = sizeof(T_index);
        val_t = sizeof(T);

        // if destroy is false copy the data
        if (!destroy) {
            vals = (T *)malloc(num_nonzeros * sizeof(T));
            indexes = (int *)malloc(num_nonzeros * sizeof(T));
            col_p = (int *)malloc((num_cols + 1) * sizeof(T));

            // copy data
            memcpy(vals, mat.valuePtr(), num_nonzeros * sizeof(T));
            memcpy(indexes, mat.innerIndexPtr(), num_nonzeros * sizeof(T));
            memcpy(col_p, mat.outerIndexPtr(), (num_cols + 1) * sizeof(T));
        } else {
            vals = mat.valuePtr();
            indexes = mat.innerIndexPtr();
            col_p = mat.outerIndexPtr();
        }

        // set compression size
        // TODO: take another look here
        compression_size = num_nonzeros * sizeof(T) + num_nonzeros * sizeof(T) + (num_cols + 1) * sizeof(T);

    }

    template <typename T, typename T_index>
    template <typename values_t, typename row_ind, typename col_ind>
    SparseMatrix<T, T_index, 1>::SparseMatrix(values_t **vals, row_ind **indexes, col_ind **col_p,
                                                size_t non_zeros, size_t row_num, size_t col_num,
                                                bool destroy)
    {
    }

    template <typename T, typename T_index>
    SparseMatrix<T, T_index, 1>::SparseMatrix(const char *filename)
    {

    }

    template <typename T, typename T_index>
    SparseMatrix<T, T_index, 1>::SparseMatrix(CSF::SparseMatrix<T, T_index, 1> &mat)
    {

    }

    template <typename T, typename T_index>
    SparseMatrix<T, T_index, 1>::~SparseMatrix()
    {
        if (vals != nullptr)
            free(vals);
        if (indexes != nullptr)
            free(indexes);
        if (col_p != nullptr)
            free(col_p);
    }
}