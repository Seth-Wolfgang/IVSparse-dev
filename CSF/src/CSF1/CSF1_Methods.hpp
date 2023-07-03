#pragma once

namespace CSF {

    // Gets the element stored at the given row and column
    template <typename T, typename indexT, bool columnMajor>
    T SparseMatrix<T, indexT, 1, columnMajor>::coeff(uint32_t row, uint32_t col) { return (*this)(row, col); }

    // Check for Column Major
    template <typename T, typename indexT, bool columnMajor>
    bool SparseMatrix<T, indexT, 1, columnMajor>::isColumnMajor() const { return columnMajor; }

    // Get the values of the matrix
    template <typename T, typename indexT, bool columnMajor>
    T *SparseMatrix<T, indexT, 1, columnMajor>::getValues(uint32_t vec) const { return vals; }

    // Get the inner indices of the matrix
    template <typename T, typename indexT, bool columnMajor>
    indexT *SparseMatrix<T, indexT, 1, columnMajor>::getInnerIndices(uint32_t vec) const { return innerIdx; }

    // Get the outer pointers of the matrix
    template <typename T, typename indexT, bool columnMajor>
    indexT *SparseMatrix<T, indexT, 1, columnMajor>::getOuterPointers() const { return outerPtr; }

    // Get a csf vector from the matrix
    template <typename T, typename indexT, bool columnMajor>
    typename SparseMatrix<T, indexT, 1, columnMajor>::Vector SparseMatrix<T, indexT, 1, columnMajor>::getVector(uint32_t vec) {
        #ifdef CSF_DEBUG
        // check if the vector is out of bounds
        assert((vec < outerDim && vec >= 0) && "Vector index out of bounds");
        #endif

        // create a vector from the matrix
        typename SparseMatrix<T, indexT, 1, columnMajor>::Vector v(*this, vec);

        return v;
    }

    // write the matrix to file
    template <typename T, typename indexT, bool columnMajor>
    void SparseMatrix<T, indexT, 1, columnMajor>::write(const char *filename) {

        FILE* fp = fopen(filename, "wb");

        // write the metadata
        fwrite(metadata, sizeof(uint32_t), NUM_META_DATA, fp);

        // write the values
        fwrite(vals, sizeof(T), nnz, fp);

        // write the inner indices
        fwrite(innerIdx, sizeof(indexT), nnz, fp);

        // write the outer pointers
        fwrite(outerPtr, sizeof(indexT), outerDim + 1, fp);

        fclose(fp);
    }

    // print the matrix to stdout
    template <typename T, typename indexT, bool columnMajor>
    void SparseMatrix<T, indexT, 1, columnMajor>::print() {
        std::cout << std::endl;
        std::cout << "CSF Matrix" << std::endl;

        // if the matrix is less than 100 rows and columns print the whole thing
        if (numRows < 100 && numCols < 100) {
            // print the matrix
            for (uint32_t i = 0; i < numRows; i++) {
                for (uint32_t j = 0; j < numCols; j++) {
                    std::cout << coeff(i, j) << " ";
                }
                std::cout << std::endl;
            }
        } else if (numRows > 100 && numCols > 100) {
            // print the first 100 rows and columns
            for (uint32_t i = 0; i < 100; i++) {
                for (uint32_t j = 0; j < 100; j++) {
                    std::cout << coeff(i, j) << " ";
                }
                std::cout << std::endl;
            }
        }
    }

    template <typename T, typename indexT, bool columnMajor>
    CSF::SparseMatrix<T, indexT, 2, columnMajor> SparseMatrix<T, indexT, 1, columnMajor>::toCSF2() {
        // create a new CSF matrix
        CSF::SparseMatrix<T, indexT, 2, columnMajor> csfMat(vals, innerIdx, outerPtr, numRows, numCols, nnz);

        // return the matrix
        return csfMat;
    }

    template <typename T, typename indexT, bool columnMajor>
    CSF::SparseMatrix<T, indexT, 3, columnMajor> SparseMatrix<T, indexT, 1, columnMajor>::toCSF3() {
        // create a new CSF matrix
        CSF::SparseMatrix<T, indexT, 3, columnMajor> csfMat(vals, innerIdx, outerPtr, numRows, numCols, nnz);

        // return the matrix
        return csfMat;
    }

    template <typename T, typename indexT, bool columnMajor>
    Eigen::SparseMatrix<T, columnMajor ? Eigen::ColMajor : Eigen::RowMajor> SparseMatrix<T, indexT, 1, columnMajor>::toEigen() {
        // create a new sparse matrix with the correct dimensions
        Eigen::SparseMatrix<T, columnMajor ? Eigen::ColMajor : Eigen::RowMajor> eigenMat(numRows, numCols);

        // check if the matrix is empty
        if (nnz == 0) {
            return eigenMat;
        }

        // add the values to the matrix
        for (uint32_t i = 0; i < outerDim; i++) {

            for (indexT j = outerPtr[i]; j < outerPtr[i + 1]; j++) {
                eigenMat.insert(innerIdx[j], i) = vals[j];
            }
        }

        // return the matrix
        return eigenMat;
    }

    template <typename T, typename indexT, bool columnMajor>
    CSF::SparseMatrix<T, indexT, 1, columnMajor> SparseMatrix<T, indexT, 1, columnMajor>::transpose() {
        // create an eigen matrix
        Eigen::SparseMatrix<T> eigenMat = (*this).toEigen();

        // transpose the matrix
        eigenMat = eigenMat.transpose();

        // create a new CSF matrix
        CSF::SparseMatrix<T, indexT, 1, columnMajor> csfMat(eigenMat);

        // return the matrix
        return csfMat;
    }

    // in place transpose
    template <typename T, typename indexT, bool columnMajor>
    void SparseMatrix<T, indexT, 1, columnMajor>::inPlaceTranspose() {
        // create an eigen matrix
        Eigen::SparseMatrix<T> eigenMat = (*this).toEigen();

        // transpose the matrix
        eigenMat = eigenMat.transpose();

        *this = CSF::SparseMatrix<T, indexT, 1, columnMajor>(eigenMat);
    }

    template <typename T, typename indexT, bool columnMajor>
    void SparseMatrix<T, indexT, 1, columnMajor>::append(SparseMatrix<T, indexT, 1, columnMajor>::Vector& vec) {

        // update the dimensions
        if (columnMajor) {
            numCols++;
        } else {
            numRows++;
        }
        outerDim++;
        metadata[2] = outerDim;

        nnz += vec.nonZeros();
        metadata[3] = nnz;

        // realloc the arrays
        try {
            vals = (T*)realloc(vals, sizeof(T) * nnz);
            innerIdx = (indexT*)realloc(innerIdx, sizeof(indexT) * nnz);
            outerPtr = (indexT*)realloc(outerPtr, sizeof(indexT) * (outerDim + 1));
        } catch (std::bad_alloc& ba) {
            std::cerr << "Error: " << ba.what() << std::endl;
            exit(1);
        }

        // copy the values
        memcpy(vals + (nnz - vec.nonZeros()), vec.getValues(), sizeof(T) * vec.nonZeros());
        memcpy(innerIdx + (nnz - vec.nonZeros()), vec.getInnerIndices(), sizeof(indexT) * vec.nonZeros());

        // update the last outer pointer
        outerPtr[outerDim] = nnz;

        calculateCompSize();
    }

    // slice method that returns a vector of CSF vectors
    template <typename T, typename indexT, bool columnMajor>
    std::vector<typename CSF::SparseMatrix<T, indexT, 1, columnMajor>::Vector> SparseMatrix<T, indexT, 1, columnMajor>::slice(uint32_t start, uint32_t end)
    {
        #ifdef CSF_DEBUG
        assert(start < outerDim && end <= outerDim && start < end && "Invalid start and end values!");
        #endif


        // make a vector of CSF vectors
        std::vector<typename CSF::SparseMatrix<T, indexT, 1, columnMajor>::Vector> vecs(end - start);

        // grab the vectors and add them to vecs
        for (uint32_t i = start; i < end; ++i)
        {
            // make a temp vector
            CSF::SparseMatrix<T, indexT, 1, columnMajor>::Vector temp(*this, i);

            // add the vector to vecs
            vecs[i - start] = temp;
        }

        // return the vector
        return vecs;
    }
}