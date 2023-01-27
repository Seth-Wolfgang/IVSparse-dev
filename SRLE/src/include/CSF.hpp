
/*
Version 2.1
By: Skyler Ruiter
Content: This is a file to build the constructor for a new data structure and compression algorithm called CSF.
*/

#include "CSF_Lib.hpp"

using std::cout;
using std::endl;

#define DEBUG 0

namespace CSF {

    // Class for the CSF matrix

    template <int compression_level>
    class SparseMatrix {
    private:
        //* Constructor data

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

        // compression size and level
        size_t compression_size;

        bool is_allocated = false;

        // void pointers for compression
        void* comp_ptr;
        void* begin_ptr;

        // Function to allocate memory for compression
        void allocate_memory() {

            // Malloc memory for the data, never worse then CSC so allocate CSC amount
            // space for the value and row, col indicies, and a buffer zone

            size_t csc_size = num_nonzeros * val_t + num_nonzeros * row_t + num_cols * col_t + 300;

            begin_ptr = malloc(csc_size);

            // Check if memory was allocated
            if (!begin_ptr) {
                throw std::bad_alloc();
            }

            is_allocated = true;

            // Set the pointer to the start of the data
            comp_ptr = begin_ptr;
        }

        // Finds the amount of bytes needed to store the given value
        uint8_t byte_width(size_t size) {
            switch (size) {
            case 0 ... 255:
                return 1;
            case 256 ... 65535:
                return 2;
            case 65536 ... 4294967295:
                return 4;
            default:
                return 8;
            }
        }

    public:
        // Eigen Wrapper Constructor
        // TODO make an optimized dedicated eigen constuctor
        template <typename T>
        SparseMatrix(Eigen::SparseMatrix<T>& mat, int compression_l = 3) {

            mat.makeCompressed();

            size_t nnz = mat.nonZeros();
            T* vals_arr = new T[nnz];
            T* indexes_arr = new T[nnz];
            T* col_p_arr = new T[mat.outerSize() + 1];

            // Copy data from Eigen
            std::memcpy(vals_arr, mat.valuePtr(), nnz * sizeof(T));
            std::memcpy(indexes_arr, mat.innerIndexPtr(), nnz * sizeof(T));
            std::memcpy(col_p_arr, mat.outerIndexPtr(), (mat.outerSize() + 1) * sizeof(T));

            T** vals = &vals_arr;
            T** indexes = &indexes_arr;
            T** col_p = &col_p_arr;


            compression_level = compression_l;

            // Construct CSF
            CSF::SparseMatrix<compression_level> tempMatrix = CSF::SparseMatrix<compression_level>(vals, indexes, col_p, nnz, mat.rows(), mat.cols(), compression_level);


            num_rows = tempMatrix.num_rows;
            num_cols = tempMatrix.num_cols;
            num_nonzeros = tempMatrix.num_nonzeros;

            // Data types for matrix values_t and indices
            row_t = tempMatrix.row_t;
            col_t = tempMatrix.col_t;
            val_t = tempMatrix.val_t;

            // compression size
            compression_size = tempMatrix.compression_size;

            // void pointers for compression
            comp_ptr = tempMatrix.comp_ptr;
            begin_ptr = tempMatrix.begin_ptr;

            // Free memory
            delete[] vals_arr;
            delete[] indexes_arr;
            delete[] col_p_arr;
        }

        // ? could potentially move some logic outside the constructor for performance gains ?
        /* CSC Constructor
        Takes in 3 arrays of a CSC sparse matrix as well as the dimensions and destructively compresses the sparse data to SRLE
        - Can ask constructor to non-destructively compress the data
        */
        template <typename values_t, typename row_ind, typename col_ind>
        SparseMatrix(values_t** vals, row_ind** indexes, col_ind** col_p,
                     size_t non_zeros, size_t row_num, size_t col_num,
                     int compression_l = 3, bool destroy = true) {

            // TODO: implement non-destructive method

            // ! Destructive Method

            // Initialize data
            num_rows = row_num;
            num_cols = col_num;
            num_nonzeros = non_zeros;

            compression_level = compression_l;

            row_t = byte_width(num_rows);
            col_t = byte_width(num_cols);
            val_t = sizeof(values_t);

            // Allocate memory for compression
            allocate_memory();

            // !! Debug ptr
            void* debug = begin_ptr;

            // Construct Metadata --------------------
            // * <row_t, col_t, val_t, num_rows, num_cols, [col_pointers], {...runs...}>

            // Row, Col, and Val sizes onto compression
            *(uint32_t*)(comp_ptr) = row_t;
            comp_ptr = (uint32_t*)(comp_ptr)+1;

            *(uint32_t*)(comp_ptr) = col_t;
            comp_ptr = (uint32_t*)(comp_ptr)+1;

            *(uint32_t*)(comp_ptr) = val_t;
            comp_ptr = (uint32_t*)(comp_ptr)+1;

            // Number of Rows and Cols onto compression
            *(uint32_t*)(comp_ptr) = num_rows;
            comp_ptr = (uint32_t*)(comp_ptr)+1;

            *(uint32_t*)(comp_ptr) = num_cols;
            comp_ptr = (uint32_t*)(comp_ptr)+1;

            // Create a space for col pointers
            // ! currently size uint64_t and positive delta encoded
            uint64_t* col_pointers = (uint64_t*)(comp_ptr);
            comp_ptr = (uint64_t*)(comp_ptr)+(uint64_t)(num_cols);

            // Put a delim at the end of the metadata
            *(uint32_t*)(comp_ptr) = delim;
            comp_ptr = (uint32_t*)(comp_ptr)+1;
            // End of Metadata --------------------

            // Loop through each column and construct the compression runs
            for (size_t i = 0; i < num_cols; i++) {

                // Update the col pointer
                col_pointers[i] = (uint64_t)(comp_ptr)-(uint64_t)(begin_ptr);
                // std::cout << std::distance((uint8_t *)(begin_ptr), (uint8_t *)(comp_ptr)) << std::endl;

                // For each element in the column check if it's a new value
                for (size_t j = (*col_p)[i]; j < (*col_p)[i + 1]; j++) {

                    // New unique value check
                    if ((*vals)[j] != 0) {
                        // New unique value found

                        // Add the found value to run
                        *(values_t*)(comp_ptr) = (*vals)[j];
                        comp_ptr = (uint32_t*)(comp_ptr)+1;

                        // Create an index pointer to update index type later
                        void* help_ptr = comp_ptr;

                        // default index type to row index type and iterate pointer
                        *(uint8_t*)help_ptr = (uint8_t)sizeof(row_ind);
                        comp_ptr = (uint8_t*)(comp_ptr)+1;

                        // Add the found index to run
                        *(row_ind*)(comp_ptr) = (*indexes)[j];
                        comp_ptr = (uint32_t*)(comp_ptr)+1;

                        // Loop through rest of column to get rest of indices
                        for (size_t k = j + 1; k < (*col_p)[i + 1]; k++) {

                            if ((*vals)[k] == (*vals)[j]) {

                                // Found value again

                                // add index of value to run
                                *(row_ind*)(comp_ptr) = (*indexes)[k];
                                comp_ptr = (row_ind*)(comp_ptr)+1;

                                // set value to zero
                                (*vals)[k] = 0;
                            }
                        }

                        // Set first index found to 0
                        (*vals)[j] = 0;

                        //* Positive delta encode the indices -----------

                        // constexpr if (compression_level == 3) {
                        constexpr if (compression_level == 3) {

                            // set variable for max element
                            size_t max_index = 0;

                            // find number of elements found for unique value
                            size_t num_elements = (row_ind*)(comp_ptr)-((row_ind*)(help_ptr));

                            // bring comp_ptr back to being pointed at last found index
                            comp_ptr = (row_ind*)(comp_ptr)-1;

                            // loop moves comp_ptr backwards through indices and positive delta encodes them
                            for (size_t k = 0; k < num_elements - 1; k++) {

                                // subtract element from one before it
                                *(row_ind*)(comp_ptr) = *(row_ind*)(comp_ptr)-*((row_ind*)(comp_ptr)-1);

                                // if bigger then prev max make curr max idx
                                if (*(row_ind*)(comp_ptr) > max_index) {
                                    max_index = *(row_ind*)(comp_ptr);
                                }

                                comp_ptr = (row_ind*)(comp_ptr)-1; // loop control
                            }

                            // set index pointer to correct size for run
                            *(uint8_t*)(help_ptr) = byte_width(max_index);
                            help_ptr = (uint8_t*)(help_ptr)+1;

                            // write over data with indices of new size, index compression
                            switch (byte_width(max_index)) {
                            case 1:

                                // walk the two iterators, compressing down to optimal byte width
                                for (size_t k = 0; k < num_elements; k++) {

                                    // set index to uint8_t size
                                    *(uint8_t*)(comp_ptr) = (uint8_t) * (row_ind*)(help_ptr);

                                    // Iterate pointers
                                    comp_ptr = (uint8_t*)(comp_ptr)+1;
                                    help_ptr = (row_ind*)(help_ptr)+1;
                                }

                                // Add delim
                                *(uint8_t*)(comp_ptr) = delim;
                                comp_ptr = (uint8_t*)(comp_ptr)+1;

                                break;

                            case 2:
                                // walk the two iterators, compressing down to optimal byte width
                                for (size_t k = 0; k < num_elements; k++) {

                                    // set index to uint16_t size
                                    *(uint16_t*)(comp_ptr) = (uint16_t) * (row_ind*)(help_ptr);

                                    // Iterate pointers
                                    comp_ptr = (uint16_t*)(comp_ptr)+1;
                                    help_ptr = (row_ind*)(help_ptr)+1;
                                }

                                // Add delim
                                *(uint16_t*)(comp_ptr) = delim;
                                comp_ptr = (uint16_t*)(comp_ptr)+1;

                                break;

                            case 4:
                                // walk the two iterators, compressing down to optimal byte width
                                for (size_t k = 0; k < num_elements; k++) {

                                    // set index to uint8_t size
                                    *(uint32_t*)(comp_ptr) = (uint32_t) * (row_ind*)(help_ptr);

                                    // Iterate pointers
                                    comp_ptr = (uint32_t*)(comp_ptr)+1;
                                    help_ptr = (row_ind*)(help_ptr)+1;
                                }

                                // Add delim
                                *(uint32_t*)(comp_ptr) = delim;
                                comp_ptr = (uint32_t*)(comp_ptr)+1;

                                break;

                            } // end switch

                            help_ptr = comp_ptr;

                        }
                        else if (compression_level == 2) { // end compression level 3
                            // add delim to end of run
                            *(row_ind*)(comp_ptr) = delim;
                            comp_ptr = (row_ind*)(comp_ptr)+1;

                            // bring up help ptr to comp ptr
                            help_ptr = comp_ptr;
                        }
                    } // end if

                } // end for loop of uniques in col

            } // end of col for loop

            // remove ending zeros
            while (comp_ptr != begin_ptr && *(uint8_t*)(comp_ptr) == 0) {
                comp_ptr = (uint8_t*)(comp_ptr)-1;
            }

            // positive delta encode the column pointers
            for (size_t i = num_cols - 1; i > 0; i--) {
                col_pointers[i] = col_pointers[i] - col_pointers[i - 1];
            }

            // find size of file in bytes
            compression_size = (uint8_t*)(comp_ptr)-((uint8_t*)(begin_ptr)-1);

            // resize data to fit actual size
            begin_ptr = realloc(begin_ptr, compression_size);

            // ! write data to file
            FILE* fp = fopen("data.bin", "wb");
            fwrite(begin_ptr, 1, compression_size, fp);
            fclose(fp);

        } // end of constructor

        ~SparseMatrix() {
            if (is_allocated)
                free(begin_ptr);
            is_allocated = false;
        }

        size_t byteSize() const {
            return compression_size;
        }

        void* getData() {
            return begin_ptr;
        }

        void* getEnd() {
            return comp_ptr;
        }

    }; // end of SparseMatrix class

    // --------------- Iterator class ------------------
    template <typename T>
    class iterator {



    };

}; // end of namespace