/**
 * @file VCSC_Methods.hpp
 * @author Skyler Ruiter and Seth Wolfgang
 * @brief Methods for VCSC Sparse Matrices
 * @version 0.1
 * @date 2023-07-03
 */

#pragma once

namespace IVSparse {

    //* Getters *//

    // Gets the element stored at the given row and column
    template <typename T, typename indexT, bool columnMajor>
    T VCSC<T, indexT, columnMajor>::coeff(uint32_t row, uint32_t col) {
        return (*this)(row, col);
    }

    // Check for Column Major
    template <typename T, typename indexT, bool columnMajor>
    bool VCSC<T, indexT, columnMajor>::isColumnMajor() const {
        return columnMajor;
    }

    // get the values vector
    template <typename T, typename indexT, bool columnMajor>
    T* VCSC<T, indexT, columnMajor>::getValues(uint32_t vec) const {
        return values[vec];
    }

    // get the counts vector
    template <typename T, typename indexT, bool columnMajor>
    indexT* VCSC<T, indexT, columnMajor>::getCounts(uint32_t vec) const {
        return counts[vec];
    }

    // get the indices vector
    template <typename T, typename indexT, bool columnMajor>
    indexT* VCSC<T, indexT, columnMajor>::getIndices(
        uint32_t vec) const {
        return indices[vec];
    }

    // get the number of unique values in a vector
    template <typename T, typename indexT, bool columnMajor>
    indexT VCSC<T, indexT, columnMajor>::getNumUniqueVals(
        uint32_t vec) const {
        if (valueSizes == nullptr) {
            return 0;
        }
        return valueSizes[vec];
    }

    // get the number of indices in a vector
    template <typename T, typename indexT, bool columnMajor>
    indexT VCSC<T, indexT, columnMajor>::getNumIndices(
        uint32_t vec) const {
        if (indexSizes == nullptr) {
            return 0;
        }
        return indexSizes[vec];
    }

    //* Utility Methods *//

    // Writes the matrix to file
    template <typename T, typename indexT, bool columnMajor>
    void VCSC<T, indexT, columnMajor>::write(char* filename) {

        std::string file = std::string(filename);
        if (strcasestr(filename, ".vcsc") == NULL) {
            file += std::string(".vcsc");
            // strcat(filename, ".vcsc");
        }

        // Open the file
        FILE* fp = fopen(file.c_str(), "wb+");

        // Write the metadata
        fwrite(metadata, 1, NUM_META_DATA * sizeof(uint32_t), fp);

        // write the lengths of the vectors
        for (uint32_t i = 0; i < outerDim; ++i) {
            fwrite(&valueSizes[i], 1, sizeof(indexT), fp);
        }
        for (uint32_t i = 0; i < outerDim; ++i) {
            fwrite(&indexSizes[i], 1, sizeof(indexT), fp);
        }

        // write the values
        for (uint32_t i = 0; i < outerDim; ++i) {
            fwrite(values[i], 1, valueSizes[i] * sizeof(T), fp);
        }

        // write the counts
        for (uint32_t i = 0; i < outerDim; ++i) {
            fwrite(counts[i], 1, valueSizes[i] * sizeof(indexT), fp);
        }

        // write the indices
        for (uint32_t i = 0; i < outerDim; ++i) {
            fwrite(indices[i], 1, indexSizes[i] * sizeof(indexT), fp);
        }

        // close the file
        fclose(fp);
    }

    template <typename T, typename indexT, bool columnMajor>
    void VCSC<T, indexT, columnMajor>::read(char* filename) {

        *this = VCSC<T, indexT, columnMajor>(filename);

    }


    // Prints the matrix dense to console
    template <typename T, typename indexT, bool columnMajor>
    void VCSC<T, indexT, columnMajor>::print() {
        std::cout << std::endl;
        std::cout << "VCSC Matrix" << std::endl;

        // print the first 100 rows and columns
        for (uint32_t i = 0; i < 100 && i < numRows; i++) {
            for (uint32_t j = 0; j < 100 && j < numCols; j++) {
                std::cout << static_cast<int>(coeff(i, j)) << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

    // Convert a IVCSC matrix to a VCSC matrix
    template <typename T, typename indexT, bool columnMajor>
    IVSparse::IVCSC<T, columnMajor> VCSC<T, indexT, columnMajor>::toIVCSC() {
        // make a pointer for the CSC pointers
        T* values = (T*)malloc(nnz * sizeof(T));
        indexT* indices = (indexT*)malloc(nnz * sizeof(indexT));
        indexT* colPtrs = (indexT*)malloc((outerDim + 1) * sizeof(indexT));

        colPtrs[0] = 0;

        // make an array of ordered maps to hold the data
        std::map<indexT, T> dict[outerDim];

        // iterate through the data using the iterator
        for (uint32_t i = 0; i < outerDim; ++i) {
            size_t count = 0;

            for (typename VCSC<T, indexT, columnMajor>::InnerIterator it(*this, i); it; ++it) {
                dict[i][it.getIndex()] = it.value();
                count++;
            }
            colPtrs[i + 1] = colPtrs[i] + count;
        }
        size_t count = 0;

        // loop through the dictionary and populate values and indices
        for (uint32_t i = 0; i < outerDim; ++i) {
            for (auto& pair : dict[i]) {
                values[count] = pair.second;
                indices[count] = pair.first;
                count++;
            }
        }

        // return a IVCSC matrix from the CSC vectors
        IVSparse::IVCSC<T, columnMajor> mat(values, indices, colPtrs, numRows, numCols, nnz);

        // free the CSC vectors
        free(values);
        free(indices);
        free(colPtrs);

        return mat;
    }

    // converts the ivsparse matrix to an eigen one and returns it
    template <typename T, typename indexT, bool columnMajor>
    Eigen::SparseMatrix<T, columnMajor ? Eigen::ColMajor : Eigen::RowMajor> VCSC<T, indexT, columnMajor>::toEigen() {

        #ifdef IVSPARSE_DEBUG
        // assert that the matrix is not empty
        assert(outerDim > 0 && "Cannot convert an empty matrix to an Eigen matrix!");
        #endif

        // create a new sparse matrix
        Eigen::SparseMatrix<T, columnMajor ? Eigen::ColMajor : Eigen::RowMajor> eigenMatrix(numRows, numCols);

        // eigenMatrix.reserve(Eigen::VectorXi::Constant(nnz));

        // iterate over the matrix
        // #ifdef IVSPARSE_HAS_OPENMP
        // #pragma omp parallel for
        // #endif
        for (uint32_t i = 0; i < outerDim; ++i) {
            for (typename VCSC<T, indexT, columnMajor>::InnerIterator it(*this, i); it; ++it) {
                // add the value to the matrix
                eigenMatrix.insert(it.row(), it.col()) = it.value();
            }
        }

        // finalize the matrix
        eigenMatrix.makeCompressed();

        // return the matrix
        return eigenMatrix;
    }

    //* Conversion/Transformation Methods *//

    // appends a vector to the back of the storage order of the matrix
    template <typename T, typename indexT, bool columnMajor>
    void VCSC<T, indexT, columnMajor>::append(IVSparse::VCSC<T, indexT, columnMajor>& mat) {

        #ifdef IVSPARSE_DEBUG
        // check that the vector is the correct size
        assert((mat.innerDim == innerDim) &&
               "The vector must be the same size as the outer dimension of the "
               "matrix!");
        #endif

        uint32_t oldOuterDim = outerDim;

        outerDim += mat.outerSize();
        nnz += mat.nonZeros();

        if constexpr (columnMajor) {
            numCols = outerDim;
        }
        else {
            numRows = outerDim;
        }

        // update metadata
        metadata[2] = outerDim;
        metadata[3] = nnz;

        // realloc the vectors
        try {
            values = (T**)realloc(values, outerDim * sizeof(T*));
            counts = (indexT**)realloc(counts, outerDim * sizeof(indexT*));
            indices = (indexT**)realloc(indices, outerDim * sizeof(indexT*));
            valueSizes = (indexT*)realloc(valueSizes, outerDim * sizeof(indexT));
            indexSizes = (indexT*)realloc(indexSizes, outerDim * sizeof(indexT));
        }
        catch (std::bad_alloc& e) {
            std::cerr << "Error: " << e.what() << std::endl;
            exit(1);
        }

        // copy the data from the vector to the new vectors
        #ifdef IVSPARSE_HAS_OPENMP
        #pragma omp parallel for
        #endif
        for (uint32_t i = 0; i < outerDim - oldOuterDim; ++i) {
            valueSizes[oldOuterDim + i] = mat.getNumUniqueVals(i);
            indexSizes[oldOuterDim + i] = mat.getNumIndices(i);

            // allocate the new vectors
            try {
                values[oldOuterDim + i] = (T*)malloc(valueSizes[oldOuterDim + i] * sizeof(T));
                counts[oldOuterDim + i] = (indexT*)malloc(valueSizes[oldOuterDim + i] * sizeof(indexT));
                indices[oldOuterDim + i] = (indexT*)malloc(indexSizes[oldOuterDim + i] * sizeof(indexT));
            }
            catch (std::bad_alloc& e) {
                std::cerr << "Error: " << e.what() << std::endl;
                exit(1);
            }

            // copy the data from the vector to the new vectors
            memcpy(values[oldOuterDim + i], mat.getValues(i), mat.valueSizes[i] * sizeof(T));
            memcpy(counts[oldOuterDim + i], mat.getCounts(i), mat.valueSizes[i] * sizeof(indexT));
            memcpy(indices[oldOuterDim + i], mat.getIndices(i), mat.indexSizes[i] * sizeof(indexT));
        }

        // update the compressed size
        calculateCompSize();
    }  // end append

    // Eigen -> IVSparse append
    template<typename T, typename indexT, bool columnMajor>
    inline void IVSparse::VCSC<T, indexT, columnMajor>::append(Eigen::SparseMatrix<T, columnMajor ? Eigen::ColMajor : Eigen::RowMajor>& mat) {
        VCSC<T, indexT, columnMajor> temp(mat);
        append(temp);
    }

    // Raw CSC -> IVSparse append
    template<typename T, typename indexT, bool columnMajor>
    template<typename T2, typename indexT2>
    inline void IVSparse::VCSC<T, indexT, columnMajor>::append(T2* vals, indexT2* innerIndices, indexT2* outerPtr, uint32_t num_rows, uint32_t num_cols, uint32_t nnz) {
        VCSC<T, indexT, columnMajor> temp(vals, innerIndices, outerPtr, num_rows, num_cols, nnz);
        append(temp);
    }

    // tranposes the ivsparse matrix
    template <typename T, typename indexT, bool columnMajor>
    IVSparse::VCSC<T, indexT, columnMajor> VCSC<T, indexT, columnMajor>::transpose() {
        // make a data structure to store the tranpose
        // std::unordered_map<T, std::vector<indexT>> mapsT[innerDim];
        std::vector<std::unordered_map<T, std::vector<indexT>>> mapsT(innerDim);
        mapsT.resize(innerDim);

        // populate the transpose data structure
        #ifdef IVSPARSE_HAS_OPENMP
        #pragma omp parallel for
        #endif        
        for (uint32_t i = 0; i < outerDim; ++i) {
            for (typename VCSC<T, indexT, columnMajor>::InnerIterator it(*this, i); it; ++it) {
                // add the value to the map
                if constexpr (columnMajor) {
                    #pragma omp critical
                    mapsT[it.row()][it.value()].push_back(it.col());
                }
                else {
                    #pragma omp critical
                    mapsT[it.col()][it.value()].push_back(it.row());
                }
            }
        }

        // create a new matrix passing in transposedMap
        IVSparse::VCSC<T, indexT, columnMajor> temp(mapsT.data(), numRows, numCols);

        // return the new matrix
        return temp;
    }

    // Transpose In Place Method
    template <typename T, typename indexT, bool columnMajor>
    void VCSC<T, indexT, columnMajor>::inPlaceTranspose() {
        // make a data structure to store the tranpose
        // std::unordered_map<T, std::vector<indexT>> mapsT[innerDim];
        std::vector<std::unordered_map<T, std::vector<indexT>>> mapsT(innerDim);
        mapsT.resize(innerDim);


        // populate the transpose data structure
        #ifdef IVSPARSE_HAS_OPENMP
        #pragma omp parallel for
        #endif
        for (uint32_t i = 0; i < outerDim; ++i) {
            for (typename VCSC<T, indexT, columnMajor>::InnerIterator it(*this, i); it; ++it) {
                // add the value to the map
                if constexpr (columnMajor) {
                    #pragma omp critical
                    mapsT[it.row()][it.value()].push_back(it.col());
                }
                else {
                    #pragma omp critical
                    mapsT[it.col()][it.value()].push_back(it.row());
                }
            }
        }

        // set this to the transposed matrix
        *this = IVSparse::VCSC<T, indexT, columnMajor>(mapsT.data(), numRows, numCols);
    }

    // slice method that returns a vector of IVSparse vectors
    template <typename T, typename indexT, bool columnMajor>
    IVSparse::VCSC<T, indexT, columnMajor> VCSC<T, indexT, columnMajor>::slice(uint32_t start, uint32_t end) {

        #ifdef IVSPARSE_DEBUG
        assert(start < outerDim && end <= outerDim && start < end &&
               "Invalid start and end values!");
        #endif

        // create a new matrix
        IVSparse::VCSC<T, indexT, columnMajor> temp;

        temp.innerDim = innerDim;
        temp.outerDim = end - start;

        if constexpr (columnMajor) {
            temp.numRows = innerDim;
            temp.numCols = temp.outerDim;
        }
        else {
            temp.numRows = temp.outerDim;
            temp.numCols = innerDim;
        }

        // malloc the vectors
        try {
            temp.values = (T**)malloc((end - start) * sizeof(T*));
            temp.counts = (indexT**)malloc((end - start) * sizeof(indexT*));
            temp.indices = (indexT**)malloc((end - start) * sizeof(indexT*));
            temp.valueSizes = (indexT*)malloc((end - start) * sizeof(indexT));
            temp.indexSizes = (indexT*)malloc((end - start) * sizeof(indexT));
        }
        catch (std::bad_alloc& e) {
            std::cerr << "Error: " << e.what() << std::endl;
            exit(1);
        }

        // copy the data from the vector to the new vectors
        for (int i = 0; i < end - start; i++) {

            temp.valueSizes[i] = valueSizes[i + start];
            temp.indexSizes[i] = indexSizes[i + start];

            // allocate the new vectors
            try {
                temp.values[i] = (T*)malloc(valueSizes[i + start] * sizeof(T));
                temp.counts[i] = (indexT*)malloc(sizeof(indexT) * valueSizes[i + start]);
                temp.indices[i] = (indexT*)malloc(indexSizes[i + start] * sizeof(indexT));
            }
            catch (std::bad_alloc& e) {
                std::cerr << "Error: " << e.what() << std::endl;
                exit(1);
            }

            // copy the data from the vector to the new vectors
            memcpy(temp.values[i], values[i + start], valueSizes[i + start] * sizeof(T));
            memcpy(temp.counts[i], counts[i + start], valueSizes[i + start] * sizeof(indexT));
            memcpy(temp.indices[i], indices[i + start], indexSizes[i + start] * sizeof(indexT));

            temp.nnz += temp.valueSizes[i] * temp.indexSizes[i];

        }

        temp.metadata = new uint32_t[NUM_META_DATA];
        temp.metadata[0] = 2;
        temp.metadata[1] = temp.innerDim;
        temp.metadata[2] = temp.outerDim;
        temp.metadata[3] = temp.nnz;
        temp.metadata[4] = val_t;
        temp.metadata[5] = index_t;


        // update the compressed size
        temp.calculateCompSize();
        return temp;
    }

}  // end namespace IVSparse