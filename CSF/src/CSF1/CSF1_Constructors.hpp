#pragma once

namespace CSF {

    // Destructor
    template <typename T, typename indexT, bool columnMajor>
    SparseMatrix<T, indexT, 1, columnMajor>::~SparseMatrix() {

        // free the old data
        if (vals != nullptr) {
            free(vals);
        }

        if (innerIdx != nullptr) {
            free(innerIdx);
        }

        if (outerPtr != nullptr) {
            free(outerPtr);
        }

        if (metadata != nullptr)
            delete[] metadata;
    }

    // Eigen Constructor
    template <typename T, typename indexT, bool columnMajor>
    SparseMatrix<T, indexT, 1, columnMajor>::SparseMatrix(Eigen::SparseMatrix<T> &mat) {

        mat.makeCompressed();

        innerDim = mat.innerSize();
        outerDim = mat.outerSize();

        numRows = mat.rows();
        numCols = mat.cols();

        nnz = mat.nonZeros();

        encodeValueType();
        index_t = sizeof(indexT);

        try {
            vals = (T*)malloc(nnz * sizeof(T));
            innerIdx = (indexT*)malloc(nnz * sizeof(indexT));
            outerPtr = (indexT*)malloc((outerDim + 1) * sizeof(indexT));
        } catch (std::bad_alloc &e) {
            std::cerr << "Allocation failed: " << e.what() << '\n';
        }

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

        calculateCompSize();

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

        try {
            vals = (T*)malloc(nnz * sizeof(T));
            innerIdx = (indexT*)malloc(nnz * sizeof(indexT));
            outerPtr = (indexT*)malloc((outerDim + 1) * sizeof(indexT));
        } catch (std::bad_alloc &e) {
            std::cerr << "Allocation failed: " << e.what() << '\n';
        }

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

        calculateCompSize();

        // run the user checks
        #ifdef CSF_DEBUG
        userChecks();
        #endif
    }

    // Deep Copy Constructor
    template <typename T, typename indexT, bool columnMajor>
    SparseMatrix<T, indexT, 1, columnMajor>::SparseMatrix(const CSF::SparseMatrix<T, indexT, 1, columnMajor> &other) { *this = other; }

    // General Conversion Constructor
    template <typename T, typename indexT, bool columnMajor>
    template <uint8_t compressionLevel2>
    SparseMatrix<T, indexT, 1, columnMajor>::SparseMatrix(CSF::SparseMatrix<T, indexT, compressionLevel2, columnMajor> &other) {

        // if already csf1 then just copy
        if constexpr (compressionLevel2 == 1) {
            *this = other;
            return;
        }

        CSF::SparseMatrix<T, indexT, 1, columnMajor> temp;

        if constexpr(compressionLevel2 == 2) {
            temp = other.toCSF1();
        } else if constexpr (compressionLevel2 == 3) {
            temp = other.toCSF1();
        }
        else if constexpr (compressionLevel2 == 3)
        {
            temp = mat.toCSF1();
        }

        numRows = num_rows;
        numCols = num_cols;
        this->nnz = nnz;

        encodeValueType();
        index_t = sizeof(indexT);

        try {
            this->vals = (T*)malloc(nnz * sizeof(T));
            innerIdx = (indexT*)malloc(nnz * sizeof(indexT));
            this->outerPtr = (indexT*)malloc((outerDim + 1) * sizeof(indexT));
        } catch (std::bad_alloc &e) {
            std::cerr << "Allocation failed: " << e.what() << '\n';
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

        memcpy(this->vals, vals, sizeof(T) * nnz);
        memcpy(innerIdx, innerIndices, sizeof(indexT) * nnz);
        memcpy(this->outerPtr, outerPtr, sizeof(indexT) * (outerDim + 1));

        val_t = encodeValueType();

        // run the user checks
        #ifdef CSF_DEBUG
        userChecks();
        #endif
    }

    // Vector Constructor
    template <typename T, typename indexT, bool columnMajor>
    SparseMatrix<T, indexT, 1, columnMajor>::SparseMatrix(typename CSF::SparseMatrix<T, indexT, 1, columnMajor>::Vector &vec){

        if constexpr (columnMajor) {
            innerDim = vec.getLength();
            outerDim = 1;
            numRows = vec.getLength();
            numCols = 1;
        } else {
            innerDim = 1;
            outerDim = vec.getLength();
            numRows = 1;
            numCols = vec.getLength();
        }

        nnz = vec.nonZeros();

        encodeValueType();
        index_t = sizeof(indexT);
        
        metadata = new uint32_t[NUM_META_DATA];

        metadata[0] = 1;
        metadata[1] = innerDim;
        metadata[2] = outerDim;
        metadata[3] = nnz;
        metadata[4] = val_t;
        metadata[5] = index_t;

        // if the vector is empty, return
        if (vec.byteSize() == 0)
        {
            vals = nullptr;
            innerIdx = nullptr;
            
            // allocate outerPtr
            try {
                outerPtr = (indexT*)malloc((outerDim + 1) * sizeof(indexT));
            } catch (std::bad_alloc &e) {
                std::cerr << "Allocation failed: " << e.what() << '\n';
            }

            outerPtr[0] = 0;

            return;
        }

        try {
            vals = (T*)malloc(nnz * sizeof(T));
            innerIdx = (indexT*)malloc(nnz * sizeof(indexT));
            outerPtr = (indexT*)malloc((outerDim + 1) * sizeof(indexT));
        } catch (std::bad_alloc &e) {
            std::cerr << "Allocation failed: " << e.what() << '\n';
        }

        memcpy(vals, vec.getValues(), sizeof(T) * nnz);
        memcpy(innerIdx, vec.getInnerIndices(), sizeof(indexT) * nnz);
        outerPtr[0] = 0;
        outerPtr[1] = nnz;

        calculateCompSize();
    }

    // Array of Vectors Constructor
    template <typename T, typename indexT, bool columnMajor>
    SparseMatrix<T, indexT, 1, columnMajor>::SparseMatrix(std::vector<typename CSF::SparseMatrix<T, indexT, 1, columnMajor>::Vector> &vecs) {

        CSF::SparseMatrix<T, indexT, 1, columnMajor> temp(vecs[0]);

        for (size_t i = 1; i < vecs.size(); i++) {
            temp.append(vecs[i]);
        }

        *this = temp;

        // run the user checks
        #ifdef CSF_DEBUG
        userChecks();
        #endif

        calculateCompSize();
    }

    // File Constructor
    template <typename T, typename indexT, bool columnMajor>
    SparseMatrix<T, indexT, 1, columnMajor>::SparseMatrix(const char *filename) {

        FILE *fp = fopen(filename, "rb");

        if (fp == NULL) {
            std::cerr << "Error: Could not open file " << filename << std::endl;
            exit(1);
        }

        metadata = new uint32_t[NUM_META_DATA];

        // read the metadata
        fread(metadata, sizeof(uint32_t), NUM_META_DATA, fp);

        // set the dimensions
        innerDim = metadata[1];
        outerDim = metadata[2];
        nnz = metadata[3];
        val_t = metadata[4];
        index_t = metadata[5];

        if constexpr (columnMajor) {
            numRows = innerDim;
            numCols = outerDim;
        } else {
            numRows = outerDim;
            numCols = innerDim;
        }

        // allocate the memory
        try {
            vals = (T*)malloc(nnz * sizeof(T));
            innerIdx = (indexT*)malloc(nnz * sizeof(indexT));
            outerPtr = (indexT*)malloc((outerDim + 1) * sizeof(indexT));
        } catch (std::bad_alloc &e) {
            std::cerr << "Error: Could not allocate memory for CSF matrix" << std::endl;
            exit(1);
        }

        // read the data
        fread(vals, sizeof(T), nnz, fp);
        fread(innerIdx, sizeof(indexT), nnz, fp);
        fread(outerPtr, sizeof(indexT), outerDim + 1, fp);

        fclose(fp);

        // run the user checks
        #ifdef CSF_DEBUG
        userChecks();
        #endif

        calculateCompSize();
    }
}