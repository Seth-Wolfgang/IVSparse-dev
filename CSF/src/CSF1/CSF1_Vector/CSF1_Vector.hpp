#pragma once

namespace CSF
{

    template <typename T, typename indexT, bool columnMajor>
    class SparseMatrix<T, indexT, 1, columnMajor>::Vector
    {
    private:
        //* Private Class Variables *//

        size_t size = 0;

        T *vals = nullptr;
        indexT *indices = nullptr;

        uint32_t nnz = 0;
        uint32_t vecSize = 0;
        uint32_t length = 0;

        //* Private Class Methods *//

        void userChecks();

    public:
        //* Constructors & Destructor *//

        Vector();

        Vector(CSF::SparseMatrix<T, indexT, 1, columnMajor> &mat, uint32_t vec);

        Vector(CSF::SparseMatrix<T, indexT, 1, columnMajor>::Vector &vec);

        ~Vector();

        //* Operator Overloads *//

        T operator[](uint32_t index);

        uint32_t elementLength();

        uint32_t nonZeros();

        T *values();

        indexT *indexPtr();

        size_t byteSize();

        //* Utility Methods *//

        void write(const char *filename);

        void print();
    };

    template <typename T, typename indexT, bool columnMajor>
    SparseMatrix<T, indexT, 1, columnMajor>::Vector::Vector()
    {
        length = 0;
        nnz = 0;
        vals = nullptr;
        indices = nullptr;
        size = 0;
    }

    template <typename T, typename indexT, bool columnMajor>
    SparseMatrix<T, indexT, 1, columnMajor>::Vector::Vector(CSF::SparseMatrix<T, indexT, 1, columnMajor> &mat, uint32_t vec)
    {
        // get the length of the vector
        if (columnMajor)
        {
            length = mat.rows();
        }
        else
        {
            length = mat.cols();
        }

        // check for an empty vector
        if (mat.outerPtr[vec] == mat.outerPtr[vec + 1])
        {
            nnz = 0;
            vals = nullptr;
            indices = nullptr;
            size = 0;
            return;
        }

        // get the number of non-zeros in the vector
        nnz = mat.outerPtr[vec + 1] - mat.outerPtr[vec];

        // allocate memory for the values and inner index
        vals = new T[nnz];
        indices = new indexT[nnz];

        // update the values and inner index using memcpy
        memcpy(vals, &mat.vals[mat.outerPtr[vec]], nnz * sizeof(T));
        memcpy(indices, &mat.innerIdx[mat.outerPtr[vec]], nnz * sizeof(indexT));

        size = nnz * sizeof(T) + nnz * sizeof(indexT);
    }

    template <typename T, typename indexT, bool columnMajor>
    SparseMatrix<T, indexT, 1, columnMajor>::Vector::Vector(CSF::SparseMatrix<T, indexT, 1, columnMajor>::Vector &vec)
    {
        // get the length of the vector
        length = vec.length();

        // get the number of non-zeros in the vector
        nnz = vec.nonZeros();

        // allocate memory for the values and inner index
        vals = new T[nnz];
        indices = new indexT[nnz];

        // update the values and inner index
        for (indexT i = 0; i < nnz; i++)
        {
            vals[i] = vec.values()[i];
            indices[i] = vec.indices()[i];
        }

        size = nnz * sizeof(T) + nnz * sizeof(indexT);
    }

    template <typename T, typename indexT, bool columnMajor>
    SparseMatrix<T, indexT, 1, columnMajor>::Vector::~Vector()
    {
        if (vals != nullptr)
        {
            delete[] vals;
        }
        if (indices != nullptr)
        {
            delete[] indices;
        }
    }

    //* Getters *//

    template <typename T, typename indexT, bool columnMajor>
    uint32_t SparseMatrix<T, indexT, 1, columnMajor>::Vector::elementLength() { return length; }

    template <typename T, typename indexT, bool columnMajor>
    uint32_t SparseMatrix<T, indexT, 1, columnMajor>::Vector::nonZeros() { return nnz; }

    template <typename T, typename indexT, bool columnMajor>
    T *SparseMatrix<T, indexT, 1, columnMajor>::Vector::values() { return vals; }

    template <typename T, typename indexT, bool columnMajor>
    indexT *SparseMatrix<T, indexT, 1, columnMajor>::Vector::indexPtr() { return indices; }

    template <typename T, typename indexT, bool columnMajor>
    size_t SparseMatrix<T, indexT, 1, columnMajor>::Vector::byteSize() { return size; }

    //* Overloaded Operators *//

    template <typename T, typename indexT, bool columnMajor>
    T SparseMatrix<T, indexT, 1, columnMajor>::Vector::operator[](uint32_t index)
    {
        // check if the index is within the vector dimensions
        if (index >= length)
        {
            throw std::out_of_range("Index out of range");
        }

        // check if the vector is empty
        if (nnz == 0)
        {
            return 0;
        }

        // check if the vector is not empty
        else
        {
            // loop through the vector
            for (indexT i = 0; i < nnz; i++)
            {
                // check if the index is found
                if (indices[i] == index)
                {
                    return vals[i];
                }
            }

            // return 0 if the index is not found
            return 0;
        }
    }

    //* Utility Methods *//

    template <typename T, typename indexT, bool columnMajor>
    void SparseMatrix<T, indexT, 1, columnMajor>::Vector::write(const char *filename)
    {
        // turn into a CSF matrix
        CSF::SparseMatrix<T, indexT, 1, columnMajor> csfMat(*this);

        // write the matrix
        csfMat.write(filename);
    }

    template <typename T, typename indexT, bool columnMajor>
    void SparseMatrix<T, indexT, 1, columnMajor>::Vector::print()
    {

        // if length larger than 100 dont print
        if (length > 100)
        {
            std::cout << "Vector is too large to print" << std::endl;
            return;
        }

        std::cout << std::endl;
        std::cout << "Vector: " << std::endl;

        // print the vector
        for (indexT i = 0; i < length; i++)
        {
            std::cout << (*this)[i] << " ";
        }

        std::cout << std::endl;
    }
}