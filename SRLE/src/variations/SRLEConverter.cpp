#include "../include/CPP_Lib.hpp"

class DeBruinesComp
{

private:
    // ! Magic is currently unused
    uint32_t magic = 1;
    uint8_t delim = 0;

    uint32_t num_rows;
    uint32_t num_cols;
    uint32_t num_vals;

    uint32_t row_t;
    uint32_t col_t;
    uint32_t val_t;

    void *ptr;
    void *data;
    size_t size;

    void allocate()
    {
        // ! Malloc currently allocates much more than needed
        data = malloc(num_vals * val_t * 1.3);
        if (!data)
        {
            cerr << "Malloc Failed" << endl;
        }
        ptr = data;
    }

    uint8_t byte_width(size_t size)
    {
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

    /* COO Constructor
        @param *x: pointer to values of COO Matrix
        @param *i: pointer to indices of values in COO matrix
        @param *p: pointer to the column pointers of the COO matrix
        @param val_num: number of non-zero values
        @param row_num: number of rows in the matrix
        @param col_num: number of columns in the matrix
    */
    // ! Assumes column major format (Isn't this just CSC?)
    template <typename values, typename idx_type>
    DeBruinesComp(values *x_v, idx_type *i_v, idx_type *c_point, size_t val_num, size_t row_num, size_t col_num)
    {

        // ! Currently copies data first, should refactor to destroy COO matrix in place
        values x[val_num];
        idx_type i[val_num];
        idx_type p[col_num + 1];

        // create an array that is a copy of x_v and i_v
        for (int k = 0; k < val_num; k++)
        {
            x[k] = x_v[k];
            i[k] = i_v[k];
        }

        // create an array that is a copy of c_point
        for (int k = 0; k < col_num + 1; k++)
        {
            p[k] = c_point[k];
        }

        // Initialize the number of rows, cols, and vals, their types, and allocate space for them
        num_rows = row_num;
        num_cols = col_num;
        num_vals = val_num;

        row_t = byte_width(num_rows);
        col_t = byte_width(num_cols);
        val_t = sizeof(values);

        allocate();
        cout << "Allocated" << endl;
        // ! Create a copy of data here for debugging
        void *debug = data;

        // Construct Metadata
        // rowType       = params[0];
        // nRows         = params[1];
        // colType       = params[2];
        // nCols         = params[3];
        // valueWidth    = params[4];
        // * <row_t, col_t, val_t, num_rows, num_cols, [col_pointers], {...runs...}>
        *static_cast<uint32_t *>(ptr) = row_t;
        // ! better way of static casting 
        *(uint32_t*)(ptr) = row_t;
        ptr = static_cast<uint32_t *>(ptr) + 1;
        *static_cast<uint32_t *>(ptr) = num_rows;
        ptr = static_cast<uint32_t *>(ptr) + 1;
        *static_cast<uint32_t *>(ptr) = col_t;
        ptr = static_cast<uint32_t *>(ptr) + 1;
        *static_cast<uint32_t *>(ptr) = num_cols;
        ptr = static_cast<uint32_t *>(ptr) + 1;
        *static_cast<uint32_t *>(ptr) = val_t;
        ptr = static_cast<uint32_t *>(ptr) + 1;     



        // Create space for col_pointers
        // uint32_t *col_pointers = static_cast<uint32_t *>(ptr);
        // ptr = static_cast<uint32_t *>(ptr) + num_cols;

        // put a delimiter down at end of metadata
        *static_cast<uint32_t *>(ptr) = 0;
        ptr = static_cast<uint32_t *>(ptr) + 1;

        // * Loop through each column and constuct the runs
        for (int l = 0; l < num_cols; l++)
        {

            // for each element in the col
            for (int j = p[l]; j < p[l + 1]; j++)
            {
                if (x[j] != 0)
                {
                    // found value

                    // add value to run
                    *static_cast<values *>(ptr) = x[j];
                    ptr = static_cast<values *>(ptr) + 1;

                    // create an index pointer here
                    uint8_t *index_ptr = static_cast<uint8_t *>(ptr);
                    index_ptr[0] = (uint8_t)sizeof(idx_type);
                    ptr = static_cast<uint8_t *>(ptr) + 1;

                    // add index to run
                    *static_cast<idx_type *>(ptr) = i[j];
                    ptr = static_cast<idx_type *>(ptr) + 1;

                    // loop through rest of column and get indices
                    for (int k = j + 1; k < p[l + 1]; k++)
                    {
                        if (x[k] == x[j])
                        {
                            // found value again

                            // add index to run
                            *static_cast<idx_type *>(ptr) = i[k];
                            ptr = static_cast<idx_type *>(ptr) + 1;

                            // set value to 0
                            x[k] = 0;
                        }
                    }

                    // positive delta encode indices
                    size_t max = 0;
                    idx_type *index = reinterpret_cast<idx_type *>(index_ptr + 1);
                    int num_elements = (int)(static_cast<idx_type *>(ptr) - index);
                    for (int k = num_elements - 1; k > 0; k--)
                    {
                        index[k] = index[k] - index[k - 1];
                        if (index[k] > max)
                        {
                            max = index[k];
                        }
                    }
                    // set index pointer to correct size
                    index_ptr[0] = byte_width(max);
                    // move index pointer by one
                    index_ptr = index_ptr + 1;

                    // create a void pointer to index_ptr
                    void *reducer_ptr = static_cast<void *>(index_ptr);

                    // ! Get rid of switch statemnt with casting a void pointer to a uint8_t pointer
                    // Write over data with indices of new size
                    switch (byte_width(max))
                    {
                    case 1:
                        // cast reducer_ptr to uint8_t
                        reducer_ptr = static_cast<uint8_t *>(reducer_ptr);
                        for (int k = 0; k < num_elements; k++)
                        {
                            *static_cast<uint8_t *>(reducer_ptr) = index[k];
                            reducer_ptr = static_cast<uint8_t *>(reducer_ptr) + 1;
                        }
                        // add delimiter
                        *static_cast<uint8_t *>(reducer_ptr) = delim;
                        reducer_ptr = static_cast<uint8_t *>(reducer_ptr) + 1;
                        break;
                    case 2:
                        // cast reducer_ptr to uint16_t
                        reducer_ptr = static_cast<uint16_t *>(reducer_ptr);
                        for (int k = 0; k < num_elements; k++)
                        {
                            *static_cast<uint16_t *>(reducer_ptr) = index[k];
                            reducer_ptr = static_cast<uint16_t *>(reducer_ptr) + 1;
                        }
                        // add delimiter
                        *static_cast<uint16_t *>(reducer_ptr) = delim;
                        reducer_ptr = static_cast<uint16_t *>(reducer_ptr) + 1;
                        break;
                    case 4:
                        // cast reducer_ptr to uint32_t
                        reducer_ptr = static_cast<uint32_t *>(reducer_ptr);
                        for (int k = 0; k < num_elements; k++)
                        {
                            *static_cast<uint32_t *>(reducer_ptr) = index[k];
                            reducer_ptr = static_cast<uint32_t *>(reducer_ptr) + 1;
                        }
                        // add delimiter
                        *static_cast<uint32_t *>(reducer_ptr) = delim;
                        reducer_ptr = static_cast<uint32_t *>(reducer_ptr) + 1;
                        break;
                    case 8:
                        // cast reducer_ptr to uint64_t
                        reducer_ptr = static_cast<uint64_t *>(reducer_ptr);
                        for (int k = 0; k < num_elements; k++)
                        {
                            *static_cast<uint64_t *>(reducer_ptr) = index[k];
                            reducer_ptr = static_cast<uint64_t *>(reducer_ptr) + 1;
                        }
                        // add delimiter
                        *static_cast<uint64_t *>(reducer_ptr) = delim;
                        reducer_ptr = static_cast<uint64_t *>(reducer_ptr) + 1;
                        break;
                    } // end switch

                    // move ptr to reducer_ptr
                    ptr = reducer_ptr;

                } // end if
            }     // end for (unique value)

            // find distance to beginning of compression and set col_pointer
            // col_pointers[l] = static_cast<uint32_t *>(ptr) - static_cast<uint32_t *>(data);

        } // end for (cols)

        // remove ending zeros
        while (ptr != data && *static_cast<uint8_t *>(ptr) == 0)
        {
            ptr = static_cast<uint8_t *>(ptr) - 1;
        }

        // find size of data in bytes
        cout << "Sizing" << endl;
        cout << static_cast<uint8_t *>(ptr) - static_cast<uint8_t *>(data) << endl;
        // cout << static_cast<uint8_t *>(ptr) - static_cast<uint8_t *>(data) << endl;

        size_t size = static_cast<uint8_t *>(ptr) - static_cast<uint8_t *>(data);

        // resize data to fit
        data = realloc(data, size);

        //  ! crunch col pointers

        // print out data by byte
        // for (int i = 0; i < size; i++)
        // {
        //     printf("%02x ", *static_cast<uint8_t *>(data + i));
        // }

        // write data to file
        cout << "Writing to file..." << endl;
        //print all of data
        // for(int i = 0; i < size; i++){
        //     printf("%02x ", *static_cast<uint8_t *>(data + i));
        // }


        FILE *fp = fopen("test.bin", "wb");
        fwrite(data, size, 1, fp);
        fclose(fp);

    } // end constructor

    /* Eigen Wrapper Constructor
        @param &mat: Eigen Sparse Matrix to compress
    */
    template <typename T>
    DeBruinesComp(Eigen::SparseMatrix<T> &mat){

        //convert mat to CSC
        int* i = new int[mat.nonZeros()]; // rows
        int* p = new int[mat.outerSize()]; // cols
        T* x = new T[mat.nonZeros()]; // values
        
        for(size_t col = 0; col < mat.outerSize(); ++col){
            p[col] = mat.outerIndexPtr()[col];
            for(typename Eigen::SparseMatrix<T>::InnerIterator it(mat, col); it; ++it){
                i[it.index()] = it.row();
                x[it.index()] = it.value();
            }
        }



        //print number of values in p

    /* COO Constructor
        @param *x: pointer to values of COO Matrix
        @param *i: pointer to indices of values in COO matrix
        @param *p: pointer to the column pointers of the COO matrix
        @param val_num: number of non-zero values
        @param row_num: number of rows in the matrixouterSi
        @param col_num: number of columns in the matrix
    */
 
        for(int j = 0; j < mat.nonZeros(); j++){
            cout << "value: "  << x[j] << " row: " << i[j] << " col: " << p[j] << endl;
        }
        cout << endl << endl;


        DeBruinesComp(x, i, p, mat.nonZeros(), mat.rows(), mat.cols());
    }

    ~DeBruinesComp()
    {
        free(data);
    }

    // Write to file
};