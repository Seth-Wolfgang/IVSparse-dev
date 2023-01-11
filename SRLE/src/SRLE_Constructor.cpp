/*
Version 2.1
By: Skyler Ruiter

Content: This is a file to build the constructor for a new data structure and compression algorithm called SRLE. 

*/

// Constuctor and General Includes


// Eigen Include
#include <Eigen/Sparse>

// Namespace
using namespace std;

class SRLE {
    private:

    // Constructor data

    // Compression delimiter
    uint8_t delim = 0;

    // dimensions and size of sparse matrix
    uint32_t num_rows;
    uint32_t num_cols;
    uint32_t num_nonzeros;

    // Data types for matrix values and indices
    uint32_t row_t;
    uint32_t col_t;
    uint32_t val_t;

    // compression size
    size_t size;

    // void pointers for compression
    void* ptr;
    void* data;

    // Function to allocate memory for compression
    void allocate_memory() {
        
        // Malloc memory for the data, never worse then CSC so allocate CSC amount
        // space for the value and row, col indicies, and a buffer zone
        data = malloc(num_nonzeros * val_t +
                      num_nonzeros * row_t +
                      num_cols * col_t +
                      num_rows);

        // Check if memory was allocated
        if (!data) {
            throw bad_alloc();
        }

        // Set the pointer to the start of the data
        ptr = data;
    }

    uint8_t byte_width(size_t size) {
        switch (size)
        {
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

    /* CSC Constructor
    
    */
   template <typename values, typename row_ind, typename col_ind>
   SRLE(values **vals, row_ind **indexes, col_ind **col_p,
        size_t non_zeros, size_t row_num, size_t col_num) {
        
        // Destructive Method

        // Initialize data
        num_rows = row_num;
        num_cols = col_num;
        num_nonzeros = non_zeros;

        row_t = byte_width(num_rows);
        col_t = byte_width(num_cols);
        val_t = sizeof(values);

        // Allocate memory for compression
        allocate_memory();

        // Construct Metadata
        // * <row_t, col_t, val_t, num_rows, num_cols, [col_pointers], {...runs...}>

        // Row, Col, and Val sizes onto compression
        *(uint32_t *)(ptr) = row_t;
        ptr = (uint32_t *)(ptr) + 1;

        *(uint32_t *)(ptr) = col_t;
        ptr = (uint32_t *)(ptr) + 1;

        *(uint32_t *)(ptr) = val_t;
        ptr = (uint32_t *)(ptr) + 1;

        // Number of Rows and Cols onto compression
        *(uint32_t *)(ptr) = num_rows;
        ptr = (uint32_t *)(ptr) + 1;

        *(uint32_t *)(ptr) = num_cols;
        ptr = (uint32_t *)(ptr) + 1;

        // Create a space for col pointers
        // ! Need to be size T

   }
};

int main() {
    return 0;
}