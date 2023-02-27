#pragma once 

#define DEBUG 1

#include <type_traits>
#include <iostream>
#include <iomanip>

namespace CSF {

    // General Constructors

    template <typename T, typename T_index, int compression_level>
    SparseMatrix<T, T_index, compression_level>::SparseMatrix()
    {
    }

    template <typename T, typename T_index, int compression_level>
    SparseMatrix<T, T_index, compression_level>::SparseMatrix(Eigen::SparseMatrix<T> &mat, bool destroy)
    {
        // check that the matrix is in column major order
        if (mat.IsRowMajor)
            throw std::invalid_argument("The matrix must be in column major order");

        // check that the matrix is in compressed format
        if (mat.isCompressed() == false)
            mat.makeCompressed();

        // intialize the matrix
        num_rows = mat.rows();
        num_cols = mat.cols();
        num_nonzeros = mat.nonZeros();

        T *vals;
        int *indexes;
        int *col_p;

        if (destroy) {
            vals = mat.valuePtr();
            indexes = mat.innerIndexPtr();
            col_p = mat.outerIndexPtr();

        } else {
            indexes = mat.innerIndexPtr();
            col_p = mat.outerIndexPtr();

            // deep copy the values
            try {
                vals = (T *)malloc(num_nonzeros * sizeof(T));
                memcpy(vals, mat.valuePtr(), num_nonzeros * sizeof(T));
            } catch (std::bad_alloc &e) {
                std::cerr << "Error: " << e.what() << std::endl;
                exit(1);
            }
        }

        compress(vals, indexes, col_p);

        // free the memory if the matrix was destroyed
        if (!destroy && vals != nullptr) {
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

        // intialize the matrix
        num_rows = row_num;
        num_cols = col_num;
        num_nonzeros = non_zeros;

        if (!destroy) {
            
            // allocate space for a copy of vals
            values_t *vals_copy;
            try {
                vals_copy = (values_t *)malloc(num_nonzeros * sizeof(values_t));
            } catch (std::bad_alloc &e) {
                std::cerr << "Error: " << e.what() << std::endl;
                exit(1);
            }

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
        if (fp == nullptr)
            throw std::invalid_argument("The file could not be opened");

        // get size of file
        fseek(fp, 0, SEEK_END);
        compression_size = ftell(fp);
        fseek(fp, 0, SEEK_SET);

        // allocate memory for file
        try {
            begin_ptr = malloc(compression_size);
        } catch (std::bad_alloc &e) {
            std::cerr << "Error: " << e.what() << std::endl;
            exit(1);
        }

        // read in data
        fread(begin_ptr, 1, compression_size, fp);

        // close file
        fclose(fp);

        // set pointers
        comp_ptr = (void *)((uint8_t *)(begin_ptr) + compression_size);
        void *help_ptr = begin_ptr;

        // get metadata
        compression = *(uint32_t *)(help_ptr);
        help_ptr = (uint32_t *)(help_ptr) + 1;

        // assert that the compression level is the same and throw error
        if (compression != compression_level) {
            printf("Compression level of file does not match the compression level of the constructor\n");
            printf("The compression level of the file is %d and the compression level of the constructor is %d", compression, compression_level);
            exit(1);
        }

        row_t = *(uint32_t *)(help_ptr);
        help_ptr = (uint32_t *)(help_ptr) + 1;

        col_t = *(uint32_t *)(help_ptr);
        help_ptr = (uint32_t *)(help_ptr) + 1;

        val_t = *(uint32_t *)(help_ptr);
        help_ptr = (uint32_t *)(help_ptr) + 1;

        num_rows = *(uint32_t *)(help_ptr);
        help_ptr = (uint32_t *)(help_ptr) + 1;

        num_cols = *(uint32_t *)(help_ptr);
        help_ptr = (uint32_t *)(help_ptr) + 1;

        num_nonzeros = *(uint32_t *)(help_ptr);
        help_ptr = (uint32_t *)(help_ptr) + 1;

        sanity_checks();

    }

    template <typename T, typename T_index, int compression_level>
    SparseMatrix<T, T_index, compression_level>::SparseMatrix(CSF::SparseMatrix<T, T_index, compression_level> &mat) 
    {
        // create a deep copy of the matrix
        num_rows = mat.rows();
        num_cols = mat.cols();
        num_nonzeros = mat.nonzeros();

        compression_size = mat.byte_size();

        try {
            begin_ptr = malloc(mat.byte_size());
        } catch (std::bad_alloc &e) {
            std::cerr << "Error: " << e.what() << std::endl;
            exit(1);
        }
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

        sanity_checks();
    }

    template <typename T, typename T_index, int compression_level>
    SparseMatrix<T, T_index, compression_level>::~SparseMatrix()
    {
        if (begin_ptr != NULL)
            free(begin_ptr);
    }


    // Constructor Helper Functions ---------------------------------------------------------------------------

    template <typename T, typename T_index, int compression_level>
    uint64_t* SparseMatrix<T, T_index, compression_level>::create_metadata()
    {
        // Construct Metadata --------------------
        // * <compression, row_t, col_t, val_t, num_rows, num_cols, num_nonzeros, [col_pointers], {...runs...}>

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

        // Number of Rows and Cols onto compression and num nonzeros
        *(uint32_t *)(comp_ptr) = num_rows;
        comp_ptr = (uint32_t *)(comp_ptr) + 1;

        *(uint32_t *)(comp_ptr) = num_cols;
        comp_ptr = (uint32_t *)(comp_ptr) + 1;

        *(uint32_t *)(comp_ptr) = num_nonzeros;
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

        // check that row or col type isn't float or double
        if (std::is_floating_point<rows_type>::value || std::is_floating_point<cols_type>::value)
            throw std::invalid_argument("The row and column types must be non-floating point types");

        // determine the type of each value
        if (compression_level == 2) {
            row_t = sizeof(T_index);
            col_t = sizeof(T_index);
        } else {
            row_t = byte_width(num_rows);
            col_t = byte_width(num_cols);
        }

        val_t = encode_valt();

        sanity_checks();

        // allocate memory for the matrix
        allocate_memory();

        // create pointer to update col pointers
        uint64_t *col_pointers = create_metadata();

        uint8_t last_col_index = sizeof(T_index);

        for (size_t i = 0; i < num_cols; i++) {

            // Update the col pointer
            col_pointers[i] = (uint64_t)(comp_ptr) - (uint64_t)(begin_ptr);

            for (size_t j = col_p[i]; j < col_p[i + 1]; j++) {

                if ((vals)[j] != 0)
                {
                    // New unique value found

                    // Add the found value to run
                    *(T *)(comp_ptr) = (vals)[j];
                    comp_ptr = (T *)(comp_ptr) + 1;

                    // Create an index pointer to update index type later
                    void *help_ptr = comp_ptr;

                    // default index type to row index type and iterate pointer
                    *(uint8_t *)help_ptr = (uint8_t)sizeof(T_index);
                    comp_ptr = (uint8_t *)(comp_ptr) + 1;

                    // Add the found index to run
                    *(T_index *)(comp_ptr) = (indexes)[j];
                    comp_ptr = (T_index *)(comp_ptr) + 1;

                    // Loop through rest of column to get rest of indices
                    for (size_t k = j + 1; k < (col_p)[i + 1]; k++)
                    {

                        if ((vals)[k] == (vals)[j])
                        {

                            // Found value again

                            // add index of value to run
                            *(T_index *)(comp_ptr) = (indexes)[k];
                            comp_ptr = (T_index *)(comp_ptr) + 1;

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
                        size_t num_elements = (T_index *)(comp_ptr) - ((T_index *)(help_ptr));

                        // bring comp_ptr back to being pointed at last found index
                        comp_ptr = (T_index *)(comp_ptr)-1;

                        // loop moves comp_ptr backwards through indices and positive delta encodes them
                        for (size_t k = 0; k < num_elements - 1; k++)
                        {

                            // subtract element from one before it
                            *(T_index *)(comp_ptr) = *(T_index *)(comp_ptr) - *((T_index *)(comp_ptr)-1);

                            // if bigger then prev max make curr max idx
                            if (*(T_index *)(comp_ptr) > max_index)
                            {
                                max_index = *(T_index *)(comp_ptr);
                            }

                            comp_ptr = (T_index *)(comp_ptr)-1; // loop control
                        }

                        // set index pointer to correct size for run
                        *(uint8_t *)(help_ptr) = byte_width(max_index);
                        help_ptr = (uint8_t *)(help_ptr) + 1;

                        last_col_index = byte_width(max_index);

                        // write over data with indices of new size, index compression
                        switch (byte_width(max_index))
                        {
                        case 1:

                            // walk the two iterators, compressing down to optimal byte width
                            for (size_t k = 0; k < num_elements; k++)
                            {

                                // set index to uint8_t size
                                *(uint8_t *)(comp_ptr) = (uint8_t) * (T_index *)(help_ptr);

                                // Iterate pointers
                                comp_ptr = (uint8_t *)(comp_ptr) + 1;
                                help_ptr = (T_index *)(help_ptr) + 1;
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
                                *(uint16_t *)(comp_ptr) = (uint16_t) * (T_index *)(help_ptr);

                                // Iterate pointers
                                comp_ptr = (uint16_t *)(comp_ptr) + 1;
                                help_ptr = (T_index *)(help_ptr) + 1;
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
                                *(uint32_t *)(comp_ptr) = (uint32_t) * (T_index *)(help_ptr);

                                // Iterate pointers
                                comp_ptr = (uint32_t *)(comp_ptr) + 1;
                                help_ptr = (T_index *)(help_ptr) + 1;
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
                        *(T_index *)(comp_ptr) = delim;
                        comp_ptr = (T_index *)(comp_ptr) + 1;

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
        try {
            begin_ptr = realloc(begin_ptr, compression_size);
        } catch (std::bad_alloc &e) {
            std::cout << "Error: " << e.what() << std::endl;
            exit(1);
        }
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

        // set types
        row_t = sizeof(T_index);
        col_t = sizeof(T_index);
        val_t = encode_valt();

        sanity_checks();

        // if destroy is false copy the data
        if (!destroy) {
            try {
                vals = (T *)malloc(num_nonzeros * sizeof(T));
                indexes = (T_index *)malloc(num_nonzeros * sizeof(T_index));
                col_p = (T_index *)malloc((num_cols + 1) * sizeof(T_index));
            } catch (std::bad_alloc &e) {
                std::cout << "Error: " << e.what() << std::endl;
                exit(1);
            }
            
            // copy data
            memcpy(vals, mat.valuePtr(), num_nonzeros * sizeof(T));
            

            // ! check back here to see if this works
            // copy indexes and col_p and cast them to T_index
            for (size_t i = 0; i < num_nonzeros; i++)
                indexes[i] = (T_index)mat.innerIndexPtr()[i];
            
            for (size_t i = 0; i < num_cols + 1; i++)
                col_p[i] = (T_index)mat.outerIndexPtr()[i];

        } else {
            vals = mat.valuePtr();

            // ! check back here to see if this works
            indexes = (T_index *)mat.innerIndexPtr();
            col_p = (T_index *)mat.outerIndexPtr();
        }

        // set compression size
        compression_size = num_nonzeros * sizeof(T) + num_nonzeros * sizeof(T_index) + (num_cols + 1) * sizeof(T_index);

    }

    template <typename T, typename T_index>
    template <typename values_t, typename row_ind, typename col_ind>
    SparseMatrix<T, T_index, 1>::SparseMatrix(values_t **vals, row_ind **indexes, col_ind **col_p,
                                                size_t non_zeros, size_t row_num, size_t col_num,
                                                bool destroy)
    {
        // assert that values_t is the same as T
        static_assert(std::is_same<values_t, T>::value, "type of value array must be the same as value template parameter");

        // assert that row_ind is the same size as T_index
        static_assert(sizeof(row_ind) == sizeof(T_index), "type of row index array must be the same size as row index template parameter");

        // assert that col_ind is the same size as T_index
        static_assert(sizeof(col_ind) == sizeof(T_index), "type of column index array must be the same size as column index template parameter");

        // set variables
        num_rows = row_num;
        num_cols = col_num;
        num_nonzeros = non_zeros;

        // set types
        row_t = sizeof(T_index);
        col_t = sizeof(T_index);
        val_t = encode_valt();

        sanity_checks();

        // if destroy is false copy the data
        if (!destroy) {
            try {
                this->vals = (T *)malloc(num_nonzeros * sizeof(T));
                this->indexes = (T_index *)malloc(num_nonzeros * sizeof(T_index));
                this->col_p = (T_index *)malloc((num_cols + 1) * sizeof(T_index));
            } catch (std::bad_alloc &e) {
                std::cout << "Error: " << e.what() << std::endl;
                exit(1);
            }

            // copy data
            memcpy(this->vals, *vals, num_nonzeros * sizeof(T));
            memcpy(this->indexes, *indexes, num_nonzeros * sizeof(T_index));
            memcpy(this->col_p, *col_p, (num_cols + 1) * sizeof(T_index));

        } else {
            this->vals = *vals;
            this->indexes = *indexes;
            this->col_p = *col_p;
        }

        compression_size = num_nonzeros * sizeof(T) + num_nonzeros * sizeof(T_index) + (num_cols + 1) * sizeof(T_index);
    }

    template <typename T, typename T_index>
    SparseMatrix<T, T_index, 1>::SparseMatrix(const char *filename)
    {
        // open file
        FILE *file = fopen(filename, "rb");

        // check if file is null
        if (file == nullptr)
            throw std::invalid_argument("The file could not be opened");

        // read in metadata which is 7 uint32_t values
        uint32_t metadata[7];
        fread(metadata, sizeof(uint32_t), 7, file);

        // set variables
        if (metadata[0] != 1)
            throw std::invalid_argument("The file is not in compression level 1");

        row_t = metadata[1];
        col_t = metadata[2];
        val_t = metadata[3];
        num_rows = metadata[4];
        num_cols = metadata[5];
        num_nonzeros = metadata[6];

        // read in data
        try {
            vals = (T *)malloc(num_nonzeros * sizeof(T));
            indexes = (T_index *)malloc(num_nonzeros * sizeof(T_index));
            col_p = (T_index *)malloc((num_cols + 1) * sizeof(T_index));
        } catch (std::bad_alloc &e) {
            std::cout << "Error: " << e.what() << std::endl;
            exit(1);
        }

        // -- read in data -- //

        // read in column pointers
        fread(col_p, sizeof(T_index), num_cols + 1, file);

        // read in the values
        fread(vals, sizeof(T), num_nonzeros, file);

        // read in the indexes
        fread(indexes, sizeof(T_index), num_nonzeros, file);

        // close file
        fclose(file);

        compression_size = num_nonzeros * sizeof(T) + num_nonzeros * sizeof(T_index) + (num_cols + 1) * sizeof(T_index);

        sanity_checks();
    }

    template <typename T, typename T_index>
    SparseMatrix<T, T_index, 1>::SparseMatrix(CSF::SparseMatrix<T, T_index, 1> &mat)
    {

        // set variables
        num_rows = mat.rows();
        num_cols = mat.cols();
        num_nonzeros = mat.nonzeros();
        compression_size = num_nonzeros * sizeof(T) + num_nonzeros * sizeof(T_index) + (num_cols + 1) * sizeof(T_index);

        // set types
        row_t = sizeof(T_index);
        col_t = sizeof(T_index);
        val_t = encode_valt();

        sanity_checks();

        // copy data
        try {
            vals = (T *)malloc(num_nonzeros * sizeof(T));
            indexes = (T_index *)malloc(num_nonzeros * sizeof(T_index));
            col_p = (T_index *)malloc((num_cols + 1) * sizeof(T_index));
        } catch (std::bad_alloc &e) {
            std::cout << "Error: " << e.what() << std::endl;
            exit(1);
        }

        memcpy(vals, mat.vals, num_nonzeros * sizeof(T));
        memcpy(indexes, mat.indexes, num_nonzeros * sizeof(T_index));
        memcpy(col_p, mat.col_p, (num_cols + 1) * sizeof(T_index));
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