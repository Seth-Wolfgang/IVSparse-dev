#pragma once

// for CSF1 details

namespace CSF {

    //* Constructors & Destructor *//

    // default empty constructor
    template <typename T, typename indexT, bool columnMajor>
    SparseMatrix<T, indexT, 1, columnMajor>::SparseMatrix() {
        
    }

    // eigen sparse matrix constructor
    template <typename T, typename indexT, bool columnMajor>
    SparseMatrix<T, indexT, 1, columnMajor>::SparseMatrix(Eigen::SparseMatrix<T> &mat) {
        
        mat.makeCompressed();

        innerDim = mat.innerSize();
        outerDim = mat.outerSize();

        numRows = mat.rows();
        numCols = mat.cols();

        nnz = mat.nonZeros();

        val_t = encodeVal();
        index_t = sizeof(indexT);

        compSize = sizeof(T) * nnz + sizeof(indexT) * (nnz + outerDim + 1) + META_DATA_SIZE;

        vals = new T[nnz];
        innerIdx = new indexT[nnz];
        outerPtr = new indexT[outerDim + 1];

        metadata = new uint32_t[NUM_META_DATA];

        metadata[0] = 1;
        metadata[1] = innerDim;
        metadata[2] = outerDim;
        metadata[3] = nnz;
        metadata[4] = val_t;
        metadata[5] = index_t;

        memcpy(vals, mat.valuePtr(), sizeof(T) * nnz);
        memcpy(innerIdx, mat.innerIndexPtr(), sizeof(indexT) * nnz);
        memcpy(outerPtr, mat.outerIndexPtr(), sizeof(indexT) * (outerDim + 1));

        // run user checks
        if (DEBUG) { userChecks(); }
    }

    // eigen sparse matrix constructor (row major)
    template <typename T, typename indexT, bool columnMajor>
    SparseMatrix<T, indexT, 1, columnMajor>::SparseMatrix(Eigen::SparseMatrix<T, Eigen::RowMajor> &mat)
    {
        mat.makeCompressed();

        innerDim = mat.innerSize();
        outerDim = mat.outerSize();

        numRows = mat.rows();
        numCols = mat.cols();

        nnz = mat.nonZeros();

        val_t = encodeVal();
        index_t = sizeof(indexT);

        compSize = sizeof(T) * nnz + sizeof(indexT) * (nnz + outerDim + 1) + META_DATA_SIZE;

        vals = new T[nnz];
        innerIdx = new indexT[nnz];
        outerPtr = new indexT[outerDim + 1];

        metadata = new uint32_t[NUM_META_DATA];

        metadata[0] = 1;
        metadata[1] = innerDim;
        metadata[2] = outerDim;
        metadata[3] = nnz;
        metadata[4] = val_t;
        metadata[5] = index_t;

        memcpy(vals, mat.valuePtr(), sizeof(T) * nnz);
        memcpy(innerIdx, mat.innerIndexPtr(), sizeof(indexT) * nnz);
        memcpy(outerPtr, mat.outerIndexPtr(), sizeof(indexT) * (outerDim + 1));

        // run user checks
        if (DEBUG) { userChecks(); }
    }

    // deep copy constructor
    template <typename T, typename indexT, bool columnMajor>
    SparseMatrix<T, indexT, 1, columnMajor>::SparseMatrix(CSF::SparseMatrix<T, indexT, 1, columnMajor> &mat)
    {
        innerDim = mat.innerDim;
        outerDim = mat.outerDim;

        numRows = mat.numRows;
        numCols = mat.numCols;

        nnz = mat.nnz;

        val_t = mat.val_t;
        index_t = mat.index_t;

        compSize = mat.compSize;

        vals = new T[nnz];
        innerIdx = new indexT[nnz];
        outerPtr = new indexT[outerDim + 1];

        metadata = new uint32_t[NUM_META_DATA];

        metadata[0] = 1;
        metadata[1] = innerDim;
        metadata[2] = outerDim;
        metadata[3] = nnz;
        metadata[4] = val_t;
        metadata[5] = index_t;

        memcpy(vals, mat.vals, sizeof(T) * nnz);
        memcpy(innerIdx, mat.innerIdx, sizeof(indexT) * nnz);
        memcpy(outerPtr, mat.outerPtr, sizeof(indexT) * (outerDim + 1));

        // run user checks
        if (DEBUG) { userChecks(); }
    }

    // file constructor
    template <typename T, typename indexT, bool columnMajor>
    SparseMatrix<T, indexT, 1, columnMajor>::SparseMatrix(const char *filename)
    {

    }

    // COO constructor
    // TODO: add support for this constructor

    // destructor
    template <typename T, typename indexT, bool columnMajor>
    SparseMatrix<T, indexT, 1, columnMajor>::~SparseMatrix()
    {
        if (vals != nullptr) { delete[] vals; }
        if (innerIdx != nullptr) { delete[] innerIdx; }
        if (outerPtr != nullptr) { delete[] outerPtr; }
        if (metadata != nullptr) { delete[] metadata; }
    }

    //* Private Class Methods *//

    template <typename T, typename indexT, bool columnMajor>
    uint8_t SparseMatrix<T, indexT, 1, columnMajor>::byteWidth(size_t size) {
        if (size <= ONE_BYTE_MAX) {
            return 1;
        } else if (size <= TWO_BYTE_MAX) {
            return 2;
        } else if (size <= FOUR_BYTE_MAX) {
            return 4;
        } else {
            return 8;
        }
    }

    template <typename T, typename indexT, bool columnMajor>
    uint32_t SparseMatrix<T, indexT, 1, columnMajor>::encodeVal() {
        uint8_t byte0 = sizeof(T);
        uint8_t byte1 = std::is_floating_point<T>::value ? 1 : 0;
        uint8_t byte2 = std::is_signed_v<T> ? 1 : 0;
        uint8_t byte3 = columnMajor ? 1 : 0;

        return (byte3 << 24) | (byte2 << 16) | (byte1 << 8) | byte0;
    }

    template <typename T, typename indexT, bool columnMajor>
    void SparseMatrix<T, indexT, 1, columnMajor>::checkVal() {
        uint8_t byte0 = val_t & 0xFF;
        uint8_t byte1 = (val_t >> 8) & 0xFF;
        uint8_t byte2 = (val_t >> 16) & 0xFF;
        uint8_t byte3 = (val_t >> 24) & 0xFF;


        if (byte0 != sizeof(T)) {
            std::cout << "Error: Value type size does not match" << std::endl;
            throw std::runtime_error("Value type size does not match, correct size is " + std::to_string(sizeof(T)) + "");
        }

        if (byte1 != std::is_floating_point_v<T>) {
            std::cout << "Error: Value type is not floating point" << std::endl;
            throw std::runtime_error("Value type is not floating point when it should be");
        }

        if (byte2 != std::is_signed_v<T>) {
            std::cout << "Error: Value type is not signed" << std::endl;
            throw std::runtime_error("Value type is not signed when it should be");
        }

        if (byte3 != columnMajor) {
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

        checkVal();
    }

    //* Utility Methods *//

    template <typename T, typename indexT, bool columnMajor>
    void SparseMatrix<T, indexT, 1, columnMajor>::print()
    {

    }

    template <typename T, typename indexT, bool columnMajor>
    void SparseMatrix<T, indexT, 1, columnMajor>::write(const char *filename)
    {

    }

    //* Getters & Setters *//

    template <typename T, typename indexT, bool columnMajor>
    uint32_t SparseMatrix<T, indexT, 1, columnMajor>::innerSize() { return innerDim; }

    template <typename T, typename indexT, bool columnMajor>
    uint32_t SparseMatrix<T, indexT, 1, columnMajor>::outerSize() { return outerDim; }

    template <typename T, typename indexT, bool columnMajor>
    uint32_t SparseMatrix<T, indexT, 1, columnMajor>::rows() { return numRows; }

    template <typename T, typename indexT, bool columnMajor>
    uint32_t SparseMatrix<T, indexT, 1, columnMajor>::cols() { return numCols; }

    template <typename T, typename indexT, bool columnMajor>
    uint32_t SparseMatrix<T, indexT, 1, columnMajor>::nonZeros() { return nnz; }

    template <typename T, typename indexT, bool columnMajor>
    size_t SparseMatrix<T, indexT, 1, columnMajor>::compressionSize() { return compSize; }

    template <typename T, typename indexT, bool columnMajor>
    T *SparseMatrix<T, indexT, 1, columnMajor>::values() { return vals; }

    template <typename T, typename indexT, bool columnMajor>
    indexT *SparseMatrix<T, indexT, 1, columnMajor>::innerIdxPtr() { return innerIdx; }

    template <typename T, typename indexT, bool columnMajor>
    indexT *SparseMatrix<T, indexT, 1, columnMajor>::outerPtrs() { return outerPtr; }

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
    CSF::SparseMatrix<T, indexT, 2, columnMajor > SparseMatrix<T, indexT, 1, columnMajor>::toCSF2()
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
        if (columnMajor) {
            numCols++;
        } else {
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
        if (columnMajor) {
            outerPtr[outerDim + 1] = outerPtr[outerDim] + vec.nonZeros();
        } else {
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

    //* CSF1 InnerIterator Class *//


        //* Private Methods *//


        //* Constructors & Destructor *//


        //* Overloaded Operators *//


        //* Getters & Setters *//


        //* Utility Methods *//



    //* End of CSF1 InnerIterator Class *//

    //* CSF1 Vector Class *//

        //* Constructors & Destructor *//

        template <typename T, typename indexT, bool columnMajor>
        SparseMatrix<T, indexT, 1, columnMajor>::Vector::Vector() 
        {

        }

        template <typename T, typename indexT, bool columnMajor>
        SparseMatrix<T, indexT, 1, columnMajor>::Vector::Vector(CSF::SparseMatrix<T, indexT, 1, columnMajor> &mat, uint32_t vec) 
        {
            // get the length of the vector
            if (columnMajor) {
                vecLength = mat.rows();
            } else {
                vecLength = mat.cols();
            }

            // get the number of non-zeros in the vector
            for (indexT i = mat.outerPtr[vec]; i < mat.outerPtr[vec + 1]; i++) { nnz++; }

            // allocate memory for the values and inner index
            vals = new T[nnz];
            indices = new indexT[nnz];

            // update the values and inner index
            for (indexT i = 0; i < nnz; i++)
            {
                vals[i] = mat.vals[mat.outerPtr[vec] + i];
                indices[i] = mat.innerIdx[mat.outerPtr[vec] + i];
            }

            size = nnz * sizeof(T) + nnz * sizeof(indexT);
        }

        template <typename T, typename indexT, bool columnMajor>
        SparseMatrix<T, indexT, 1, columnMajor>::Vector::Vector(CSF::SparseMatrix<T, indexT, 1, columnMajor>::Vector &vec) 
        {
            // get the length of the vector
            vecLength = vec.length();

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
            if (vals != nullptr) { delete[] vals; }
            if (indices != nullptr) { delete[] indices; }
        }

        //* Getters *//

        template <typename T, typename indexT, bool columnMajor>
        uint32_t SparseMatrix<T, indexT, 1, columnMajor>::Vector::length() { return vecLength; }

        template <typename T, typename indexT, bool columnMajor>
        uint32_t SparseMatrix<T, indexT, 1, columnMajor>::Vector::nonZeros()  { return nnz; }

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
            if (index >= vecLength)
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

        }

    //* End CSF1 Vector Class *//

    //* Misc. Methods *//
}