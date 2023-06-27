#pragma once

namespace CSF
{

    //* Constructors & Destructor *//

    // default empty constructor
    template <typename T, typename indexT, bool columnMajor>
    SparseMatrix<T, indexT, 1, columnMajor>::SparseMatrix()
    {
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
    SparseMatrix<T, indexT, 1, columnMajor>::SparseMatrix(Eigen::SparseMatrix<T> &mat)
    {

        mat.makeCompressed();

        innerDim = mat.innerSize();
        outerDim = mat.outerSize();

        numRows = mat.rows();
        numCols = mat.cols();

        nnz = mat.nonZeros();

        encodeValueType();
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
    SparseMatrix<T, indexT, 1, columnMajor>::SparseMatrix(Eigen::SparseMatrix<T, Eigen::RowMajor> &other)
    {
        other.makeCompressed();

        innerDim = other.innerSize();
        outerDim = other.outerSize();

        numRows = other.rows();
        numCols = other.cols();

        nnz = other.nonZeros();

        val_t = encodeValueType();
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

        memcpy(vals, other.valuePtr(), sizeof(T) * nnz);
        memcpy(innerIdx, other.innerIndexPtr(), sizeof(indexT) * nnz);
        memcpy(outerPtr, other.outerIndexPtr(), sizeof(indexT) * (outerDim + 1));

        // run the user checks
#ifdef CSF_DEBUG
        userChecks();
#endif
    }

    // generalized constructor
    template <typename T, typename indexT, bool columnMajor>
    template <uint8_t compressionLevel2>
    SparseMatrix<T, indexT, 1, columnMajor>::SparseMatrix(CSF::SparseMatrix<T, indexT, compressionLevel2, columnMajor> &mat)
    {

        // check if the matrix is empty
        if (mat.nonZeros() == 0)
        {
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
        if constexpr (compressionLevel2 == 2)
        {
            temp = mat.toCSF1();
        }
        else if constexpr (compressionLevel2 == 3)
        {
            temp = mat.toCSF1();
        }
        else
        {
            temp = mat;
        }

        innerDim = temp.innerDim;
        outerDim = temp.outerDim;

        numRows = temp.numRows;
        numCols = temp.numCols;

        nnz = temp.nnz;

        encodeValueType();
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


        // run the user checks
        #ifdef CSF_DEBUG
        userChecks();
        #endif
    }

    // vector constructor
    template <typename T, typename indexT, bool columnMajor>
    SparseMatrix<T, indexT, 1, columnMajor>::SparseMatrix(typename CSF::SparseMatrix<T, indexT, 1, columnMajor>::Vector &vec)
    {

        if (columnMajor)
        {
            innerDim = vec.length();
            outerDim = 1;
            numRows = vec.length();
            numCols = 1;
        }
        else
        {
            innerDim = 1;
            outerDim = vec.length();
            numRows = 1;
            numCols = vec.length();
        }

        // see if the vector is empty
        if (vec.nonZeros() == 0)
        {
            // set everything to zero or the nullptr
            vals = nullptr;
            innerIdx = nullptr;
            outerPtr = nullptr;

            nnz = 0;
            compSize = META_DATA_SIZE;

            val_t = encodeValueType();
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

        val_t = encodeValueType();
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
    SparseMatrix<T, indexT, 1, columnMajor>::SparseMatrix(T2 *vals, indexT2 *innerIndices, indexT2 *outerPtr, uint32_t num_rows, uint32_t num_cols, uint32_t nnz)
    {

        // set the meta data
        if constexpr (columnMajor)
        {
            innerDim = num_rows;
            outerDim = num_cols;
        }
        else
        {
            innerDim = num_cols;
            outerDim = num_rows;
        }

        numRows = num_rows;
        numCols = num_cols;
        nnz = nnz;

        val_t = encodeValueType();
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
        if (metadata != nullptr)
        {
            delete[] metadata;
        }
    }
}