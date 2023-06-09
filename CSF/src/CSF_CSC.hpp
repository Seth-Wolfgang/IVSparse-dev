#pragma once

// for CSF1 details

namespace CSF {

    //* Constructors & Destructor *//

    // default empty constructor
    template <typename T, typename indexT, bool columnMajor>
    SparseMatrix<T, indexT, 1, columnMajor>::SparseMatrix() {
        // set everything to zero or the nullptr

        metadata = nullptr;
        vals = nullptr;
        innerIdx = nullptr;
        outerPtr = nullptr;

        outerDim = 0;
        innerDim = 0;
        numRows = 0;
        numCols = 0;
        nnz = 0;
        compSize = 0;

        val_t = 0;
        index_t = 0;
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

        // run the user checks
        #ifdef CSF_DEBUG
        userChecks();
        #endif
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

        // run the user checks
        #ifdef CSF_DEBUG
        userChecks();
        #endif
    }

    // generalized constructor
    template <typename T, typename indexT, bool columnMajor>
    template <uint8_t compressionLevel2>
    SparseMatrix<T, indexT, 1, columnMajor>::SparseMatrix(CSF::SparseMatrix<T, indexT, compressionLevel2, columnMajor>& mat) {

        // check if the matrix is empty
        if (mat.nnz == 0) {
            // set everything to zero or the nullptr

            metadata = nullptr;
            vals = nullptr;
            innerIdx = nullptr;
            outerPtr = nullptr;

            outerDim = 0;
            innerDim = 0;
            numRows = 0;
            numCols = 0;
            nnz = 0;
            compSize = 0;

            val_t = 0;
            index_t = 0;

            return;
        }

        // make a temporary CSF1 matrix
        CSF::SparseMatrix<T, indexT, 1, columnMajor> temp;

        // if the incoming matrix is csf 2, convert it to csf1
        if constexpr (compressionLevel2 == 2) {
            temp = mat.toCSF1();
        } else if constexpr (compressionLevel2 == 3) {
            temp = mat.toCSF1();
        } else {
            temp = mat;
        }


        innerDim = temp.innerDim;
        outerDim = temp.outerDim;

        numRows = temp.numRows;
        numCols = temp.numCols;

        nnz = temp.nnz;

        val_t = temp.val_t;
        index_t = temp.index_t;

        compSize = temp.compSize;

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

        memcpy(vals, temp.vals, sizeof(T) * nnz);
        memcpy(innerIdx, temp.innerIdx, sizeof(indexT) * nnz);
        memcpy(outerPtr, temp.outerPtr, sizeof(indexT) * (outerDim + 1));

        val_t = encodeVal();

        // run the user checks
        #ifdef CSF_DEBUG
            userChecks();
        #endif
    }

    // vector constructor
    template <typename T, typename indexT, bool columnMajor>
    SparseMatrix<T, indexT, 1, columnMajor>::SparseMatrix(typename CSF::SparseMatrix<T, indexT, 1, columnMajor>::Vector& vec) {

        if (columnMajor) {
            innerDim = vec.length();
            outerDim = 1;
            numRows = vec.length();
            numCols = 1;
        } else {
            innerDim = 1;
            outerDim = vec.length();
            numRows = 1;
            numCols = vec.length();
        }

        // see if the vector is empty
        if (vec.nonZeros() == 0) {
            // set everything to zero or the nullptr
            vals = nullptr;
            innerIdx = nullptr;
            outerPtr = nullptr;

            nnz = 0;
            compSize = META_DATA_SIZE;

            val_t = encodeVal();
            index_t = sizeof(indexT);

            metadata = new uint32_t[NUM_META_DATA];

            metadata[0] = 1;
            metadata[1] = innerDim;
            metadata[2] = outerDim;
            metadata[3] = nnz;
            metadata[4] = val_t;
            metadata[5] = index_t;

            return;
        }

        nnz = vec.nonZeros();
        compSize = vec.byteSize() + META_DATA_SIZE;

        val_t = encodeVal();
        index_t = sizeof(indexT);

        metadata = new uint32_t[NUM_META_DATA];

        metadata[0] = 1;
        metadata[1] = innerDim;
        metadata[2] = outerDim;
        metadata[3] = nnz;
        metadata[4] = val_t;
        metadata[5] = index_t;

        vals = new T[nnz];
        innerIdx = new indexT[nnz];
        outerPtr = new indexT[outerDim + 1];

        memcpy(vals, vec.values(), sizeof(T) * nnz);
        memcpy(innerIdx, vec.indexPtr(), sizeof(indexT) * nnz);

        // run the user checks
        #ifdef CSF_DEBUG
        userChecks();
        #endif

    }

    // file constructor
    template <typename T, typename indexT, bool columnMajor>
    SparseMatrix<T, indexT, 1, columnMajor>::SparseMatrix(const char *filename)
    {
        FILE *fp = fopen(filename, "rb");
        
        if (fp == nullptr)
        {
            throw std::runtime_error("File not found");
        }

        // read the meta data
        metadata = new uint32_t[NUM_META_DATA];

        fread(metadata, sizeof(uint32_t), NUM_META_DATA, fp);

        // set the meta data
        innerDim = metadata[1];
        outerDim = metadata[2];
        nnz = metadata[3];
        val_t = metadata[4];
        index_t = metadata[5];

        if (columnMajor)
        {
            numRows = innerDim;
            numCols = outerDim;
        }
        else
        {
            numRows = outerDim;
            numCols = innerDim;
        }

        // allocate memory for the values, inner index, and outer pointers
        vals = new T[nnz];
        innerIdx = new indexT[nnz];
        outerPtr = new indexT[outerDim + 1];

        // read the values, inner index, and outer pointers
        fread(vals, sizeof(T), nnz, fp);
        fread(innerIdx, sizeof(indexT), nnz, fp);
        fread(outerPtr, sizeof(indexT), outerDim + 1, fp);

        // close the file
        fclose(fp);

        // update the compression size
        compSize = nnz * sizeof(T) + nnz * sizeof(indexT) + (outerDim + 1) * sizeof(indexT);

        // run the user checks
        #ifdef CSF_DEBUG
        userChecks();
        #endif
    }

    template <typename T, typename indexT, bool columnMajor>
    template <typename T2, typename indexT2>
    SparseMatrix<T, indexT, 1, columnMajor>::SparseMatrix(T2* vals, indexT2* innerIndices, indexT2* outerPtr, uint32_t num_rows, uint32_t num_cols, uint32_t nnz) {

        // set the meta data
        if constexpr (columnMajor) {
            innerDim = num_rows;
            outerDim = num_cols;
        } else {
            innerDim = num_cols;
            outerDim = num_rows;
        }

        numRows = num_rows;
        numCols = num_cols;
        nnz = nnz;

        val_t = encodeVal();
        index_t = sizeof(indexT);

        compSize = sizeof(T) * nnz + sizeof(indexT) * nnz + sizeof(indexT) * (outerDim + 1) + META_DATA_SIZE;

        // allocate memory for the values, inner index, and outer pointers
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

        memcpy(vals, vals, sizeof(T) * nnz);
        memcpy(innerIdx, innerIndices, sizeof(indexT) * nnz);
        memcpy(outerPtr, outerPtr, sizeof(indexT) * (outerDim + 1));

        // run the user checks
        #ifdef CSF_DEBUG
        userChecks();
        #endif
    }

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

    template <typename T, typename indexT, bool columnMajor>
    T SparseMatrix<T, indexT, 1, columnMajor>::coeff(uint32_t row, uint32_t col) {
        return (*this)(row, col);
    }

    template <typename T, typename indexT, bool columnMajor>
    typename CSF::SparseMatrix<T, indexT, 1, columnMajor>::Vector SparseMatrix<T, indexT, 1, columnMajor>::getVector(uint32_t vec) {
        return Vector(*this, vec);
    }

    template <typename T, typename indexT, bool columnMajor>
    size_t SparseMatrix<T, indexT, 1, columnMajor>::getVecSize(uint32_t vec) const {
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

    template <typename T, typename indexT, bool columnMajor>
    CSF::SparseMatrix<T, indexT, 1, columnMajor>& SparseMatrix<T, indexT, 1, columnMajor>::operator=(const CSF::SparseMatrix<T, indexT, 1, columnMajor>& other) {

        // check for an empty matrix
        if (other.nnz == 0) {
            
            // delete the old arrays
            if (vals != nullptr) { delete[] vals; }
            if (innerIdx != nullptr) { delete[] innerIdx; }
            if (outerPtr != nullptr) { delete[] outerPtr; }

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
        if (this == &other) {
            return *this;
        }

        // delete the old arrays
        if (vals != nullptr) { delete[] vals; }
        if (innerIdx != nullptr) { delete[] innerIdx; }
        if (outerPtr != nullptr) { delete[] outerPtr; }

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
        val_t = encodeVal();

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

    //* CSF1 InnerIterator Class *//

        //* Constructors & Destructor *//

        template <typename T, typename indexT, bool columnMajor>
        SparseMatrix<T, indexT, 1, columnMajor>::InnerIterator::InnerIterator(SparseMatrix<T, indexT, 1, columnMajor> &mat, uint32_t vec)
        {
            this->outer = vec;

            vals = &mat.vals[mat.outerPtr[vec]];
            indices = &mat.innerIdx[mat.outerPtr[vec]];
            endPtr = &mat.innerIdx[mat.outerPtr[vec + 1]];

            val = vals;
            index = indices[0];

        }

        template <typename T, typename indexT, bool columnMajor>
        SparseMatrix<T, indexT, 1, columnMajor>::InnerIterator::InnerIterator(SparseMatrix<T, indexT, 1, columnMajor>::Vector &vec)
        {
            this->outer = 0;

            vals = vec.values();
            indices = vec.indexPtr();
            endPtr = vec.indexPtr() + vec.nonZeros();

            val = vals;
            index = indices[0];
        }

        // //* Overloaded Operators *//

        template <typename T, typename indexT, bool columnMajor>
        void SparseMatrix<T, indexT, 1, columnMajor>::InnerIterator::operator++()
        {
            vals++;
            indices++;

            val = vals;
            index = *indices;
        }

        template <typename T, typename indexT, bool columnMajor>
        bool SparseMatrix<T, indexT, 1, columnMajor>::InnerIterator::operator==(const InnerIterator &other) { return (vals == other.vals && indices == other.index); }

        template <typename T, typename indexT, bool columnMajor>
        bool SparseMatrix<T, indexT, 1, columnMajor>::InnerIterator::operator!=(const InnerIterator &other) { return (vals != other.vals || indices != other.index); }

        template <typename T, typename indexT, bool columnMajor>
        bool SparseMatrix<T, indexT, 1, columnMajor>::InnerIterator::operator<(const InnerIterator &other) { return (vals < other.vals && indices < other.index); }

        template <typename T, typename indexT, bool columnMajor>
        bool SparseMatrix<T, indexT, 1, columnMajor>::InnerIterator::operator>(const InnerIterator &other) { return (vals > other.vals && indices > other.index); }

        template <typename T, typename indexT, bool columnMajor>
        T& SparseMatrix<T, indexT, 1, columnMajor>::InnerIterator::operator*() { return val; }

        // //* Getters & Setters *//

        template <typename T, typename indexT, bool columnMajor>
        indexT SparseMatrix<T, indexT, 1, columnMajor>::InnerIterator::getIndex() { return index; }

        template <typename T, typename indexT, bool columnMajor>
        indexT SparseMatrix<T, indexT, 1, columnMajor>::InnerIterator::outerDim() { return outer; }

        template <typename T, typename indexT, bool columnMajor>
        indexT SparseMatrix<T, indexT, 1, columnMajor>::InnerIterator::row()
        {
            if (columnMajor) {
                return index;
            } else {
                return outer;
            }
        }

        template <typename T, typename indexT, bool columnMajor>
        indexT SparseMatrix<T, indexT, 1, columnMajor>::InnerIterator::col() {
            if (columnMajor) {
                return outer;
            } else {
                return index;
            }
        }

        template <typename T, typename indexT, bool columnMajor>
        T SparseMatrix<T, indexT, 1, columnMajor>::InnerIterator::value() { return *val; }


    //* End of CSF1 InnerIterator Class *//

    //* CSF1 Vector Class *//

        //* Constructors & Destructor *//

        template <typename T, typename indexT, bool columnMajor>
        SparseMatrix<T, indexT, 1, columnMajor>::Vector::Vector() 
        {
            vecLength = 0;
            nnz = 0;
            vals = nullptr;
            indices = nullptr;
            size = 0;
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
            // turn into a CSF matrix
            CSF::SparseMatrix<T, indexT, 1, columnMajor> csfMat(*this);

            // write the matrix
            csfMat.write(filename);
        }

        template <typename T, typename indexT, bool columnMajor>
        void SparseMatrix<T, indexT, 1, columnMajor>::Vector::print() {

            // if vecLength larger than 100 dont print
            if (vecLength > 100)
            {
                std::cout << "Vector is too large to print" << std::endl;
                return;
            }

            std::cout << std::endl;
            std::cout << "Vector: " << std::endl;

            // print the vector
            for (indexT i = 0; i < vecLength; i++)
            {
                std::cout << (*this)[i] << " ";
            }

            std::cout << std::endl;

        }

    //* End CSF1 Vector Class *//

    //* Misc. Methods *//
}