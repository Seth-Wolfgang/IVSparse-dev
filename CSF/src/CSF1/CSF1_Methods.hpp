#pragma once

// for CSF1 details

namespace CSF
{

    //* Private Class Methods *//

    template <typename T, typename indexT, bool columnMajor>
    uint8_t SparseMatrix<T, indexT, 1, columnMajor>::byteWidth(size_t size)
    {
        if (size <= ONE_BYTE_MAX)
        {
            return 1;
        }
        else if (size <= TWO_BYTE_MAX)
        {
            return 2;
        }
        else if (size <= FOUR_BYTE_MAX)
        {
            return 4;
        }
        else
        {
            return 8;
        }
    }

    template <typename T, typename indexT, bool columnMajor>
    void SparseMatrix<T, indexT, 1, columnMajor>::encodeValueType()
    {
        uint8_t byte0 = sizeof(T);
        uint8_t byte1 = std::is_floating_point<T>::value ? 1 : 0;
        uint8_t byte2 = std::is_signed_v<T> ? 1 : 0;
        uint8_t byte3 = columnMajor ? 1 : 0;

        val_t = (byte3 << 24) | (byte2 << 16) | (byte1 << 8) | byte0;
    }

    template <typename T, typename indexT, bool columnMajor>
    void SparseMatrix<T, indexT, 1, columnMajor>::checkValueType()
    {
        uint8_t byte0 = val_t & 0xFF;
        uint8_t byte1 = (val_t >> 8) & 0xFF;
        uint8_t byte2 = (val_t >> 16) & 0xFF;
        uint8_t byte3 = (val_t >> 24) & 0xFF;

        if (byte0 != sizeof(T))
        {
            std::cout << "Error: Value type size does not match" << std::endl;
            throw std::runtime_error("Value type size does not match, correct size is " + std::to_string(sizeof(T)) + "");
        }

        if (byte1 != std::is_floating_point_v<T>)
        {
            std::cout << "Error: Value type is not floating point" << std::endl;
            throw std::runtime_error("Value type is not floating point when it should be");
        }

        if (byte2 != std::is_signed_v<T>)
        {
            std::cout << "Error: Value type is not signed" << std::endl;
            throw std::runtime_error("Value type is not signed when it should be");
        }

        if (byte3 != columnMajor)
        {
            std::cout << "Error: Wrong Major Direction" << std::endl;
            throw std::runtime_error("Wrong Major Direction");
        }
    }

    template <typename T, typename indexT, bool columnMajor>
    void SparseMatrix<T, indexT, 1, columnMajor>::userChecks()
    {
        // throw an error if the matrix has less than one rows or columns or nonzero values
        if (innerDim < 1 || outerDim < 1 || nnz < 1)
            throw std::invalid_argument("The matrix must have at least one row, column, and nonzero value");

        // check that indexT is not floating point
        if (std::is_floating_point<indexT>::value)
            throw std::invalid_argument("The index type must be a non-floating point type");

        // check that T and indexT are numeric types
        if (!std::is_arithmetic<T>::value || !std::is_arithmetic<indexT>::value)
            throw std::invalid_argument("The value and index types must be numeric types");

        // check that the index type is not a bool
        if (std::is_same<indexT, bool>::value)
            throw std::invalid_argument("The value and index types must not be bool");

        // check that the row and col types can hold the number of rows and columns
        if (innerDim > std::numeric_limits<indexT>::max() || outerDim > std::numeric_limits<indexT>::max())
            throw std::invalid_argument("The number of rows and columns must be less than the maximum value of the index type");

        checkValueType();
    }

    //* Utility Methods *//

    template <typename T, typename indexT, bool columnMajor>
    void SparseMatrix<T, indexT, 1, columnMajor>::print()
    {
        // if larger than 100 rows or cols don't print
        if (numRows > 100 || numCols > 100)
        {
            std::cout << "Matrix is too large to print" << std::endl;
            return;
        }

        std::cout << std::endl;
        std::cout << "Matrix: " << numRows << "x" << numCols << std::endl;

        // print the matrix
        for (indexT i = 0; i < numRows; i++)
        {
            for (indexT j = 0; j < numCols; j++)
            {
                std::cout << (*this)(i, j) << " ";
            }
            std::cout << std::endl;
        }

        std::cout << std::endl;
    }

    template <typename T, typename indexT, bool columnMajor>
    void SparseMatrix<T, indexT, 1, columnMajor>::write(const char *filename)
    {
        FILE *fp = fopen(filename, "wb");

        // write the metadata
        fwrite(metadata, sizeof(uint32_t), NUM_META_DATA, fp);

        // write the values, inner index, and outer pointers
        fwrite(vals, sizeof(T), nnz, fp);
        fwrite(innerIdx, sizeof(indexT), nnz, fp);
        fwrite(outerPtr, sizeof(indexT), outerDim + 1, fp);

        // close the file
        fclose(fp);
    }

    //* Getters & Setters *//

    template <typename T, typename indexT, bool columnMajor>
    uint32_t SparseMatrix<T, indexT, 1, columnMajor>::innerSize() const { return innerDim; }

    template <typename T, typename indexT, bool columnMajor>
    uint32_t SparseMatrix<T, indexT, 1, columnMajor>::outerSize() const { return outerDim; }

    template <typename T, typename indexT, bool columnMajor>
    uint32_t SparseMatrix<T, indexT, 1, columnMajor>::rows() const { return numRows; }

    template <typename T, typename indexT, bool columnMajor>
    uint32_t SparseMatrix<T, indexT, 1, columnMajor>::cols() const { return numCols; }

    template <typename T, typename indexT, bool columnMajor>
    uint32_t SparseMatrix<T, indexT, 1, columnMajor>::nonZeros() const { return nnz; }

    template <typename T, typename indexT, bool columnMajor>
    size_t SparseMatrix<T, indexT, 1, columnMajor>::byteSize() const { return compSize; }

    template <typename T, typename indexT, bool columnMajor>
    T *SparseMatrix<T, indexT, 1, columnMajor>::values() { return vals; }

    template <typename T, typename indexT, bool columnMajor>
    indexT *SparseMatrix<T, indexT, 1, columnMajor>::innerIdxPtr() { return innerIdx; }

    template <typename T, typename indexT, bool columnMajor>
    indexT *SparseMatrix<T, indexT, 1, columnMajor>::outerPtrs() { return outerPtr; }

    template <typename T, typename indexT, bool columnMajor>
    T SparseMatrix<T, indexT, 1, columnMajor>::coeff(uint32_t row, uint32_t col)
    {
        return (*this)(row, col);
    }

    template <typename T, typename indexT, bool columnMajor>
    typename CSF::SparseMatrix<T, indexT, 1, columnMajor>::Vector SparseMatrix<T, indexT, 1, columnMajor>::getVector(uint32_t vec)
    {
        return Vector(*this, vec);
    }

    template <typename T, typename indexT, bool columnMajor>
    size_t SparseMatrix<T, indexT, 1, columnMajor>::getVectorSize(uint32_t vec) const
    {
        return outerPtr[vec + 1] - outerPtr[vec];
    }

    //* Conversion Methods *//

    template <typename T, typename indexT, bool columnMajor>
    Eigen::SparseMatrix<T> SparseMatrix<T, indexT, 1, columnMajor>::toEigen()
    {
        // create a new sparse matrix with the correct dimensions
        Eigen::SparseMatrix<T> eigenMat(numRows, numCols);

        // add the values to the matrix
        for (indexT i = 0; i < outerDim; i++)
        {
            for (indexT j = outerPtr[i]; j < outerPtr[i + 1]; j++)
            {
                eigenMat.insert(innerIdx[j], i) = vals[j];
            }
        }

        // return the matrix
        return eigenMat;
    }

    template <typename T, typename indexT, bool columnMajor>
    CSF::SparseMatrix<T, indexT, 2, columnMajor> SparseMatrix<T, indexT, 1, columnMajor>::toCSF2()
    {
        // create a new CSF matrix
        CSF::SparseMatrix<T, indexT, 2, columnMajor> csfMat(vals, innerIdx, outerPtr, numRows, numCols, nnz);

        // return the matrix
        return csfMat;
    }

    template <typename T, typename indexT, bool columnMajor>
    CSF::SparseMatrix<T, indexT, 3, columnMajor> SparseMatrix<T, indexT, 1, columnMajor>::toCSF3()
    {
        // create a new CSF matrix
        CSF::SparseMatrix<T, indexT, 3, columnMajor> csfMat(vals, innerIdx, outerPtr, numRows, numCols, nnz);

        // return the matrix
        return csfMat;
    }

    //! TODO: Implement this method w/o eigen
    template <typename T, typename indexT, bool columnMajor>
    CSF::SparseMatrix<T, indexT, 1, columnMajor> SparseMatrix<T, indexT, 1, columnMajor>::transpose()
    {
        // create an eigen matrix
        Eigen::SparseMatrix<T> eigenMat = *this.toEigen();

        // transpose the matrix
        eigenMat.transposeInPlace();

        // create a new CSF matrix
        CSF::SparseMatrix<T, indexT, 1, columnMajor> csfMat(eigenMat);

        // return the matrix
        return csfMat;
    }

    template <typename T, typename indexT, bool columnMajor>
    void SparseMatrix<T, indexT, 1, columnMajor>::append(SparseMatrix<T, indexT, 1, columnMajor>::Vector &vec)
    {
        // update the matrix dimensions
        if (columnMajor)
        {
            numCols++;
        }
        else
        {
            numRows++;
        }

        // update the number of non-zeros
        nnz += vec.nonZeros();

        // allocate new memory for the values, inner index, and outer pointers
        T *newVals = new T[nnz];
        indexT *newInnerIdx = new indexT[nnz];
        indexT *newOuterPtr = new indexT[outerDim + 2];

        // copy the old values, inner index, and outer pointers into the new arrays
        memcpy(newVals, vals, nnz * sizeof(T));
        memcpy(newInnerIdx, innerIdx, nnz * sizeof(indexT));
        memcpy(newOuterPtr, outerPtr, (outerDim + 1) * sizeof(indexT));

        // delete the old arrays
        delete[] vals;
        delete[] innerIdx;
        delete[] outerPtr;

        // update the values, inner index, and outer pointers
        vals = newVals;
        innerIdx = newInnerIdx;
        outerPtr = newOuterPtr;

        // update the outer pointers
        if (columnMajor)
        {
            outerPtr[outerDim + 1] = outerPtr[outerDim] + vec.nonZeros();
        }
        else
        {
            outerPtr[outerDim + 1] = outerPtr[outerDim] + vec.nonZeros();
        }

        // update the values and inner index
        for (indexT i = 0; i < vec.nonZeros(); i++)
        {
            vals[outerPtr[outerDim] + i] = vec.valuePtr()[i];
            innerIdx[outerPtr[outerDim] + i] = vec.innerIdxPtr()[i];
        }

        // update the outer dimension
        outerDim++;

        // update the compression size
        compSize = nnz * sizeof(T) + nnz * sizeof(indexT) + (outerDim + 1) * sizeof(indexT);
    }

    //* Overloaded Operators *//

    template <typename T, typename indexT, bool columnMajor>
    bool SparseMatrix<T, indexT, 1, columnMajor>::operator==(const SparseMatrix<T, indexT, 1, columnMajor> &other)
    {
        // check if the dimensions are the same
        if (numRows != other.numRows || numCols != other.numCols)
        {
            return false;
        }

        // check if the number of non-zeros are the same
        if (nnz != other.nnz)
        {
            return false;
        }

        // check if the value arrays are the same
        for (indexT i = 0; i < nnz; i++)
        {
            if (vals[i] != other.vals[i])
            {
                return false;
            }
        }

        // check if the inner index arrays are the same
        for (indexT i = 0; i < nnz; i++)
        {
            if (innerIdx[i] != other.innerIdx[i])
            {
                return false;
            }
        }

        // check if the outer pointer arrays are the same
        for (indexT i = 0; i < outerDim + 1; i++)
        {
            if (outerPtr[i] != other.outerPtr[i])
            {
                return false;
            }
        }

        // return true if all the checks pass
        return true;
    }

    template <typename T, typename indexT, bool columnMajor>
    bool SparseMatrix<T, indexT, 1, columnMajor>::operator!=(const SparseMatrix<T, indexT, 1, columnMajor> &other)
    {
        return !(*this == other);
    }

    template <typename T, typename indexT, bool columnMajor>
    T SparseMatrix<T, indexT, 1, columnMajor>::operator()(uint32_t row, uint32_t col)
    {
        // check if the row and column are within the matrix dimensions
        if (row >= numRows || col >= numCols)
        {
            throw std::out_of_range("Row or column index out of range");
        }

        // check if the matrix is column major
        if (columnMajor)
        {
            // check if the column is empty
            if (outerPtr[col] == outerPtr[col + 1])
            {
                return 0;
            }

            // check if the column is not empty
            else
            {
                // loop through the column
                for (indexT i = outerPtr[col]; i < outerPtr[col + 1]; i++)
                {
                    // check if the row is found
                    if (innerIdx[i] == row)
                    {
                        return vals[i];
                    }
                }

                // return 0 if the row is not found
                return 0;
            }
        }

        // check if the matrix is row major
        else
        {
            // check if the row is empty
            if (outerPtr[row] == outerPtr[row + 1])
            {
                return 0;
            }

            // check if the row is not empty
            else
            {
                // loop through the row
                for (indexT i = outerPtr[row]; i < outerPtr[row + 1]; i++)
                {
                    // check if the column is found
                    if (innerIdx[i] == col)
                    {
                        return vals[i];
                    }
                }

                // return 0 if the column is not found
                return 0;
            }
        }
    }

    template <typename T, typename indexT, bool columnMajor>
    CSF::SparseMatrix<T, indexT, 1, columnMajor> &SparseMatrix<T, indexT, 1, columnMajor>::operator=(const CSF::SparseMatrix<T, indexT, 1, columnMajor> &other)
    {

        // check for an empty matrix
        if (other.nnz == 0)
        {

            // delete the old arrays
            if (vals != nullptr)
            {
                delete[] vals;
            }
            if (innerIdx != nullptr)
            {
                delete[] innerIdx;
            }
            if (outerPtr != nullptr)
            {
                delete[] outerPtr;
            }

            delete[] metadata;

            metadata = nullptr;

            outerDim = 0;
            innerDim = 0;
            numRows = 0;
            numCols = 0;
            nnz = 0;
            compSize = 0;

            return *this;
        }

        // check for self assignment
        if (this == &other)
        {
            return *this;
        }

        // delete the old arrays
        if (vals != nullptr)
        {
            delete[] vals;
        }
        if (innerIdx != nullptr)
        {
            delete[] innerIdx;
        }
        if (outerPtr != nullptr)
        {
            delete[] outerPtr;
        }

        delete[] metadata;

        // allocate metadata
        metadata = new uint32_t[NUM_META_DATA];

        // copy the metadata
        memcpy(metadata, other.metadata, NUM_META_DATA * sizeof(uint32_t));

        // copy the pointers
        innerDim = other.innerDim;
        outerDim = other.outerDim;
        numRows = other.numRows;
        numCols = other.numCols;
        nnz = other.nnz;
        compSize = other.compSize;

        index_t = other.index_t;
        val_t = encodeValueType();

        // allocate memory for the values, inner index, and outer pointers
        vals = new T[nnz];
        innerIdx = new indexT[nnz];
        outerPtr = new indexT[outerDim + 1];

        // copy the values, inner index, and outer pointers
        memcpy(vals, other.vals, nnz * sizeof(T));
        memcpy(innerIdx, other.innerIdx, nnz * sizeof(indexT));
        memcpy(outerPtr, other.outerPtr, (outerDim + 1) * sizeof(indexT));

        // return the matrix
        return *this;
    }
}