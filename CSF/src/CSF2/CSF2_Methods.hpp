/**
 * @file CSF2_Methods.hpp
 * @author Skyler Ruiter and Seth Wolfgang
 * @brief Methods for CSF2 Sparse Matrices
 * @version 0.1
 * @date 2023-07-03
 */

#pragma once

namespace CSF {

    //* Getters *//

    // Gets the element stored at the given row and column
    template <typename T, typename indexT, bool columnMajor>
    T SparseMatrix<T, indexT, 2, columnMajor>::coeff(uint32_t row, uint32_t col) { return (*this)(row, col); }

    // Check for Column Major
    template <typename T, typename indexT, bool columnMajor>
    bool SparseMatrix<T, indexT, 2, columnMajor>::isColumnMajor() const { return columnMajor; }

    // get the values vector
    template <typename T, typename indexT, bool columnMajor>
    T* SparseMatrix<T, indexT, 2, columnMajor>::getValues(uint32_t vec) const { return values[vec]; }

    // get the counts vector
    template <typename T, typename indexT, bool columnMajor>
    indexT* SparseMatrix<T, indexT, 2, columnMajor>::getCounts(uint32_t vec) const { return counts[vec]; }

    // get the indices vector
    template <typename T, typename indexT, bool columnMajor>
    indexT* SparseMatrix<T, indexT, 2, columnMajor>::getIndices(uint32_t vec) const { return indices[vec]; }

    // get the number of unique values in a vector
    template <typename T, typename indexT, bool columnMajor>
    indexT SparseMatrix<T, indexT, 2, columnMajor>::getNumUniqueVals(uint32_t vec) const { 
        if (valueSizes == nullptr) { return 0;}
        return valueSizes[vec]; 
    }

    // get the number of indices in a vector
    template <typename T, typename indexT, bool columnMajor>
    indexT SparseMatrix<T, indexT, 2, columnMajor>::getNumIndices(uint32_t vec) const { 
        if (indexSizes == nullptr) { return 0;}
        return indexSizes[vec]; 
    }

    // get the vector at the given index
    template <typename T, typename indexT, bool columnMajor>
    typename CSF::SparseMatrix<T, indexT, 2, columnMajor>::Vector SparseMatrix<T, indexT, 2, columnMajor>::getVector(uint32_t vec) { return (*this)[vec]; }

    //* Utility Methods *//

    // Writes the matrix to file
    template <typename T, typename indexT, bool columnMajor>
    void SparseMatrix<T, indexT, 2, columnMajor>::write(const char* filename) {
        // Open the file
        FILE* fp = fopen(filename, "wb");

        // Write the metadata
        fwrite(metadata, 1, NUM_META_DATA * sizeof(uint32_t), fp);

        // write the lengths of the vectors
        for (uint32_t i = 0; i < outerDim; ++i) { fwrite(&valueSizes[i], 1, sizeof(indexT), fp); }

        for (uint32_t i = 0; i < outerDim; ++i) { fwrite(&indexSizes[i], 1, sizeof(indexT), fp); }

        // write the values
        for (uint32_t i = 0; i < outerDim; ++i) { fwrite(values[i], 1, valueSizes[i] * sizeof(T), fp); }

        // write the counts
        for (uint32_t i = 0; i < outerDim; ++i) { fwrite(counts[i], 1, valueSizes[i] * sizeof(indexT), fp); }

        // write the indices
        for (uint32_t i = 0; i < outerDim; ++i) { fwrite(indices[i], 1, indexSizes[i] * sizeof(indexT), fp); }

        // close the file
        fclose(fp);
    }

    // Prints the matrix dense to console
    template <typename T, typename indexT, bool columnMajor>
    void SparseMatrix<T, indexT, 2, columnMajor>::print() {
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
        }
        else if (numRows > 100 && numCols > 100) {
            // print the first 100 rows and columns
            for (uint32_t i = 0; i < 100; i++) {
                for (uint32_t j = 0; j < 100; j++) {
                    std::cout << coeff(i, j) << " ";
                }
                std::cout << std::endl;
            }
        }

        std::cout << std::endl;
    }

    // Convert a CSF3 matrix to CSF1
    template <typename T, typename indexT, bool columnMajor>
    CSF::SparseMatrix<T, indexT, 1, columnMajor> SparseMatrix<T, indexT, 2, columnMajor>::toCSF1() {
        // create a new sparse matrix
        Eigen::SparseMatrix<T, columnMajor ? Eigen::ColMajor : Eigen::RowMajor> eigenMatrix(numRows, numCols);

        // iterate over the matrix
        for (uint32_t i = 0; i < outerDim; ++i) {
            for (typename SparseMatrix<T, indexT, 2>::InnerIterator it(*this, i); it; ++it) {
                // add the value to the matrix
                eigenMatrix.insert(it.row(), it.col()) = it.value();
            }
        }

        // finalize the matrix
        eigenMatrix.makeCompressed();

        // make a csf1 matrix
        CSF::SparseMatrix<T, indexT, 1, columnMajor> csf1Matrix(eigenMatrix);

        // return the matrix
        return csf1Matrix;
    }

    // Convert a CSF3 matrix to a CSF2 matrix
    template <typename T, typename indexT, bool columnMajor>
    CSF::SparseMatrix<T, indexT, 3, columnMajor> SparseMatrix<T, indexT, 2, columnMajor>::toCSF3() {

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

            for (typename SparseMatrix<T, indexT, 2>::InnerIterator it(*this, i); it; ++it) {
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

        // return a CSF3 matrix from the CSC vectors
        CSF::SparseMatrix<T, indexT, 3, columnMajor> mat(values, indices, colPtrs, numRows, numCols, nnz);

        // free the CSC vectors
        free(values);
        free(indices);
        free(colPtrs);

        return mat;
    }

    // converts the csf matrix to an eigen one and returns it
    template <typename T, typename indexT, bool columnMajor>
    Eigen::SparseMatrix<T, columnMajor ? Eigen::ColMajor : Eigen::RowMajor> SparseMatrix<T, indexT, 2, columnMajor>::toEigen() {

        #ifdef CSF_DEBUG
        // assert that the matrix is not empty
        assert(outerDim > 0 && "Cannot convert an empty matrix to an Eigen matrix!");
        #endif

        // create a new sparse matrix
        Eigen::SparseMatrix<T, columnMajor ? Eigen::ColMajor : Eigen::RowMajor> eigenMatrix(numRows, numCols);

        // iterate over the matrix
        for (uint32_t i = 0; i < outerDim; ++i) {
            for (typename SparseMatrix<T, indexT, 2>::InnerIterator it(*this, i); it; ++it) {
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
    void SparseMatrix<T, indexT, 2, columnMajor>::append(typename CSF::SparseMatrix<T, indexT, 2, columnMajor>::Vector& vec) {
        // check if the matrix is empty
        if (numRows < 1 && numCols < 1) [[unlikely]] {
            *this = CSF::SparseMatrix<T, indexT, 2, columnMajor>(vec);
        }
        else {
            // check if the vector is empty, if so change the implementation details
            if (vec.nonZeros() == 0) {

                if (columnMajor) { numCols++; }
                else { numRows++; }
                outerDim++;

                // update metadata
                metadata[2] = outerDim;

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

                // set the last vector to be empty
                values[outerDim - 1] = nullptr;
                counts[outerDim - 1] = nullptr;
                indices[outerDim - 1] = nullptr;
                valueSizes[outerDim - 1] = 0;
                indexSizes[outerDim - 1] = 0;

                calculateCompSize();
                return;
            
            } else {

                // check that the vector is the correct size
                if ((vec.getLength() != innerDim))
                    throw std::invalid_argument("The vector must be the same size as the outer dimension of the matrix!");

                outerDim++;
                nnz += vec.nonZeros();

                if (columnMajor) { numCols++; }
                else { numRows++; }

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

                // set the sizes of the new vector
                valueSizes[outerDim - 1] = vec.uniqueVals();
                indexSizes[outerDim - 1] = vec.nonZeros();

                // allocate the new vectors
                try {
                    values[outerDim - 1] = (T*)malloc(valueSizes[outerDim - 1] * sizeof(T));
                    counts[outerDim - 1] = (indexT*)malloc(sizeof(indexT) * valueSizes[outerDim - 1]);
                    indices[outerDim - 1] = (indexT*)malloc(indexSizes[outerDim - 1] * sizeof(indexT));
                }
                catch (std::bad_alloc& e) {
                    std::cerr << "Error: " << e.what() << std::endl;
                    exit(1);
                }

                // copy the data from the vector to the new vectors
                memcpy(values[outerDim - 1], vec.getValues(), valueSizes[outerDim - 1] * sizeof(T));
                memcpy(counts[outerDim - 1], vec.getCounts(), valueSizes[outerDim - 1] * sizeof(indexT));
                memcpy(indices[outerDim - 1], vec.getIndices(), indexSizes[outerDim - 1] * sizeof(indexT));

                // update the compressed size
                calculateCompSize();
            }
        }

    } // end append

    // tranposes the csf matrix
    template <typename T, typename indexT, bool columnMajor>
    CSF::SparseMatrix<T, indexT, 2, columnMajor> SparseMatrix<T, indexT, 2, columnMajor>::transpose() {
        // make a data structure to store the tranpose
        std::unordered_map<T, std::vector<indexT>> mapsT[innerDim];

        // populate the transpose data structure
        for (uint32_t i = 0; i < outerDim; ++i) {
            for (typename SparseMatrix<T, indexT, 2>::InnerIterator it(*this, i); it; ++it) {
                // add the value to the map
                if constexpr (columnMajor) {
                    mapsT[it.row()][it.value()].push_back(it.col());
                }
                else {
                    mapsT[it.col()][it.value()].push_back(it.row());
                }
            }
        }

        // create a new matrix passing in transposedMap
        CSF::SparseMatrix<T, indexT, 2, columnMajor> temp(mapsT, numRows, numCols);

        // return the new matrix
        return temp;
    }

    // Transpose In Place Method
    template <typename T, typename indexT, bool columnMajor>
    void SparseMatrix<T, indexT, 2, columnMajor>::inPlaceTranspose() {

        // make a data structure to store the tranpose
        std::unordered_map<T, std::vector<indexT>> mapsT[innerDim];

        // populate the transpose data structure
        for (uint32_t i = 0; i < outerDim; ++i) {
            for (typename SparseMatrix<T, indexT, 2>::InnerIterator it(*this, i); it; ++it) {
                // add the value to the map
                if constexpr (columnMajor) {
                    mapsT[it.row()][it.value()].push_back(it.col());
                }
                else {
                    mapsT[it.col()][it.value()].push_back(it.row());
                }
            }
        }

        // set this to the transposed matrix
        *this = CSF::SparseMatrix<T, indexT, 2, columnMajor>(mapsT, numRows, numCols);
    }

    // slice method that returns a vector of CSF vectors
    template <typename T, typename indexT, bool columnMajor>
    std::vector<typename CSF::SparseMatrix<T, indexT, 2, columnMajor>::Vector> SparseMatrix<T, indexT, 2, columnMajor>::slice(uint32_t start, uint32_t end) {
        #ifdef CSF_DEBUG
        assert(start < outerDim && end <= outerDim && start < end && "Invalid start and end values!");
        #endif

        // make a vector of CSF vectors
        std::vector<typename CSF::SparseMatrix<T, indexT, 2, columnMajor>::Vector> vecs(end - start);

        // grab the vectors and add them to vecs
        for (uint32_t i = start; i < end; ++i) {
            // make a temp vector
            CSF::SparseMatrix<T, indexT, 2, columnMajor>::Vector temp(*this, i);

            // add the vector to vecs
            vecs[i - start] = temp;
        }

        // return the vector
        return vecs;
    }

} // end namespace CSF