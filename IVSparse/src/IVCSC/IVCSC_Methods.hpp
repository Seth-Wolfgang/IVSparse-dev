/**
 * @file IVCSCC_Methods.hpp
 * @author Skyler Ruiter and Seth Wolfgang
 * @brief Methods for IVCSC Sparse Matrices
 * @version 0.1
 * @date 2023-07-03
 */

#pragma once

namespace IVSparse {

    //* Getters *//

    // Gets the element stored at the given row and column
    template<typename T, bool columnMajor>
    T IVCSC<T, columnMajor>::coeff(uint32_t row, uint32_t col) {

        #ifdef IVSPARSE_DEBUG
        // check that the row and column are valid
        assert(row < numRows && col < numCols && "Invalid row and column!");
        assert(row >= 0 && col >= 0 && "Invalid row and column!");
        #endif

        return (*this)(row, col);
    }

    // Check for Column Major
    template<typename T, bool columnMajor>
    bool IVCSC<T, columnMajor>::isColumnMajor() const {
        return columnMajor;
    }

    // Returns a pointer to the given vector
    template<typename T, bool columnMajor>
    void* IVCSC<T, columnMajor>::vectorPointer(uint32_t vec) {

        #ifdef IVSPARSE_DEBUG
        assert(vec < outerDim && vec >= 0 && "Invalid vector!");
        #endif

        return data[vec];
    }

    // Gets the byte size of a given vector
    template<typename T, bool columnMajor>
    size_t IVCSC<T, columnMajor>::getVectorByteSize(uint32_t vec) const {
        #ifdef IVSPARSE_DEBUG
        assert(vec < outerDim && vec >= 0 && "Invalid vector!");
        #endif

        if (data[vec] == endPointers[vec]) {
            return 0;
        }
        return (char*)endPointers[vec] - (char*)data[vec];
    }

    //* Utility Methods *//

    // Writes the matrix to file
    template<typename T, bool columnMajor>
    void IVCSC<T, columnMajor>::write(char* filename) {

        std::string file = std::string(filename);
        if (strcasestr(filename, ".ivcsc") == NULL) {
            file += std::string(".ivcsc");
            // strcat(filename, ".vcsc");
        }

        // Open the file
        FILE* fp = fopen(file.c_str(), "wb+");

        // Write the metadata
        fwrite(metadata, 1, NUM_META_DATA * sizeof(uint32_t), fp);

        // write the size of each vector
        for (uint32_t i = 0; i < outerDim; i++) {
            uint64_t size = (uint8_t*)endPointers[i] - (uint8_t*)data[i];
            fwrite(&size, 1, sizeof(uint64_t), fp);
        }

        // write each vector
        for (uint32_t i = 0; i < outerDim; i++) {
            fwrite(data[i], 1, (char*)endPointers[i] - (char*)data[i], fp);
        }

        // close the file
        fclose(fp);
    }

    template <typename T, bool columnMajor>
    void IVCSC<T, columnMajor>::read(char* filename) {

        *this = IVCSC<T, columnMajor>(filename);

    }


    // Prints the matrix dense to console
    template<typename T, bool columnMajor>
    void IVCSC<T, columnMajor>::print() {
        std::cout << std::endl;
        std::cout << "IVCSC Matrix" << std::endl;

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
    template <typename T, bool columnMajor>
    template <typename indexT>
    IVSparse::VCSC<T, indexT, columnMajor> IVCSC<T, columnMajor>::toVCSC() {

        //* compress the data

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

            for (typename IVCSC<T, columnMajor>::InnerIterator it(*this, i); it; ++it) {
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

        // return a VCSC matrix from the CSC vectors
        typename IVSparse::VCSC<T, indexT, columnMajor> mat(values, indices, colPtrs, numRows, numCols, nnz);

        // free the CSC vectors
        free(values);
        free(indices);
        free(colPtrs);

        return mat;
    }

    // converts the ivsparse matrix to an eigen one and returns it
    template<typename T, bool columnMajor>
    Eigen::SparseMatrix<T, columnMajor ? Eigen::ColMajor : Eigen::RowMajor> IVCSC<T, columnMajor>::toEigen() {
        #ifdef IVSPARSE_DEBUG
        // assert that the matrix is not empty
        assert(outerDim > 0 && "Cannot convert an empty matrix to an Eigen matrix!");
        #endif

        // iterate over the matrix
        // #ifndef IVSPARSE_HAS_OPENMP
        Eigen::SparseMatrix<T, columnMajor ? Eigen::ColMajor : Eigen::RowMajor> eigenMatrix(numRows, numCols);
        // eigenMatrix.reserve(Eigen::VectorXi::Constant(numCols, nnz / numCols));

        for (uint32_t i = 0; i < outerDim; ++i) {
            // check if the vector is empty
            if (data[i] == nullptr) {
                continue;
            }

            for (typename IVCSC<T, columnMajor>::InnerIterator it(*this, i);it; ++it) {
                // add the value to the matrix
                eigenMatrix.insert(it.row(), it.col()) = it.value();
            }
        }
        // eigenMatrix.makeCompressed();
        // return eigenMatrix;
        // #endif
        eigenMatrix.makeCompressed();
        return eigenMatrix;
        // #ifdef IVSPARSE_HAS_OPENMP
        // #pragma omp declare reduction (merge : std::vector<Eigen::Triplet<T>> : omp_out.insert(omp_out.end(), omp_in.begin(), omp_in.end()))

        // Eigen::SparseMatrix<T, columnMajor ? Eigen::ColMajor : Eigen::RowMajor> eigenMatrix;
        // std::vector<Eigen::Triplet<T>> triplets(nnz);

        // #pragma omp parallel for reduction(merge: triplets)
        // for (uint32_t i = 0; i < outerDim; ++i) {
        //     // check if the vector is empty
        //     if (data[i] == nullptr) {
        //         continue;
        //     }

        //     for (typename IVCSC<T, columnMajor>::InnerIterator it(*this, i);it; ++it) {
        //         // add the value to the matrix
        //         triplets.push_back(Eigen::Triplet<T>(it.row(), it.col(), it.value()));
        //     }
        // }
        // eigenMatrix.setFromTriplets(triplets.begin(), triplets.end());

        // // finalize the matrix
        // eigenMatrix.makeCompressed();

        // // return the matrix
        // return eigenMatrix;
        // #endif
    }

    //* Conversion/Transformation Methods *//

    // appends a vector to the back of the storage order of the matrix
    template <typename T, bool columnMajor>
    void IVCSC<T, columnMajor>::append(IVSparse::IVCSC<T, columnMajor>& mat) {

        #ifdef IVSPARSE_DEBUG
        assert(mat.innerDim == innerDim && "Vector must be the same size as the inner dimension!");
        #endif

        uint32_t oldOuterDim = outerDim;

        // update the outer dimension
        outerDim += mat.outerDim;
        if (columnMajor) {
            numCols = outerDim;
        }
        else {
            numRows = outerDim;
        }

        // update the number of nonzeros
        nnz += mat.nnz;

        // update the metadata
        metadata[2] = outerDim;
        metadata[3] = nnz;

        // reallocate the data
        try {
            data = (void**)realloc(data, outerDim * sizeof(void*));
            endPointers = (void**)realloc(endPointers, outerDim * sizeof(void*));
        }
        catch (std::bad_alloc& e) {
            throw std::bad_alloc();
        }

        // deep copy the data
        for (uint32_t i = 0; i < outerDim - oldOuterDim; ++i) {
            try {
                data[oldOuterDim + i] = malloc(mat.getVectorByteSize(i));
                endPointers[oldOuterDim + i] = (char*)data[oldOuterDim + i] + mat.getVectorByteSize(i);
            }
            catch (std::bad_alloc& e) {
                throw std::bad_alloc();
            }

            // copy the vector
            memcpy(data[oldOuterDim + i], mat.data[i], mat.getVectorByteSize(i));
        }


        calculateCompSize();
    }

    // Eigen -> IVSparse append
    template<typename T, bool columnMajor>
    inline void IVSparse::IVCSC<T, columnMajor>::append(Eigen::SparseMatrix<T, columnMajor ? Eigen::ColMajor : Eigen::RowMajor>& mat) {
        IVCSC<T, columnMajor> temp(mat);
        append(temp);
    }

    // Raw CSC -> IVSparse append
    template<typename T, bool columnMajor>
    template <typename T2, typename indexT>
    inline void IVSparse::IVCSC<T, columnMajor>::append(T2* vals, indexT* innerIndices, indexT* outerPtr, uint32_t num_rows, uint32_t num_cols, uint32_t nnz) {
        IVCSC<T, columnMajor> temp(vals, innerIndices, outerPtr, num_rows, num_cols, nnz);
        append(temp);
    }


    // tranposes the ivsparse matrix
    template<typename T, bool columnMajor>
    IVSparse::IVCSC<T, columnMajor> IVCSC<T, columnMajor>::transpose() {

        std::vector<std::unordered_map<T, std::vector<size_t>>> mapsT;
        // mapsT.reserve(innerDim);
        mapsT.resize(innerDim);
        // populate the transpose data structure

        #ifdef IVSPARSE_HAS_OPENMP
        #pragma omp parallel for
        #endif
        for (uint32_t i = 0; i < outerDim; ++i) {
            for (typename IVCSC<T, columnMajor>::InnerIterator it(*this, i); it; ++it) {
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

        #pragma omp parallel for
        for (int i = 0; i < innerDim; ++i) {
            for (auto& col : mapsT[i]) {
                // find the max value in the vector
                size_t max = col.second[0];

                // delta encode the vector
                for (uint32_t i = col.second.size() - 1; i > 0; --i) {
                    col.second[i] -= col.second[i - 1];
                    if ((size_t)col.second[i] > max) max = col.second[i];
                }

                max = byteWidth(max);
                // append max to the vector
                col.second.push_back(max);
            }
        }

        // create a new matrix passing in transposedMap
        IVSparse::IVCSC<T, columnMajor> temp(mapsT.data(), numRows, numCols);

        // return the new matrix
        return temp;
    }

    // Transpose In Place Method
    template<typename T, bool columnMajor>
    void IVCSC<T, columnMajor>::inPlaceTranspose() {
        // make a data structure to store the tranpose
        // std::unordered_map<T, std::vector<indexT>> mapsT[innerDim];
        std::vector<std::unordered_map<T, std::vector<size_t>>> mapsT;
        // mapsT.reserve(innerDim);
        mapsT.resize(innerDim);


        // populate the transpose data structure
        #ifdef IVSPARSE_HAS_OPENMP
        #pragma omp parallel for
        #endif
        for (uint32_t i = 0; i < outerDim; ++i) {
            for (typename IVCSC<T, columnMajor>::InnerIterator it(*this, i); it; ++it) {
                // add the value to the map
                if constexpr (columnMajor) {
                    mapsT[it.row()][it.value()].push_back(it.col());
                }
                else {
                    mapsT[it.col()][it.value()].push_back(it.row());
                }
            }
        }

        #ifdef IVSPARSE_HAS_OPENMP
        #pragma omp parallel for
        #endif
        for (int i = 0; i < innerDim; ++i) {
            for (auto& col : mapsT[i]) {
                // find the max value in the vector
                size_t max = col.second[0];

                // delta encode the vector
                for (uint32_t i = col.second.size() - 1; i > 0; --i) {
                    col.second[i] -= col.second[i - 1];
                    if ((size_t)col.second[i] > max) max = col.second[i];
                }

                max = byteWidth(max);
                // append max to the vector
                col.second.push_back(max);
            }
        }

        *this = IVSparse::IVCSC<T, columnMajor>(mapsT.data(), numRows, numCols);
    }

    // slice method that returns an IVCSC matrix
    template<typename T, bool columnMajor>
    IVSparse::IVCSC<T, columnMajor> IVCSC<T, columnMajor>::slice(uint32_t const start, uint32_t end) {

        #ifdef IVSPARSE_DEBUG
        assert(start < outerDim && end <= outerDim && start < end &&
               "Invalid start and end values!");
        #endif

        // create a new matrix
        IVSparse::IVCSC<T, columnMajor> temp;

        temp.outerDim = end - start;
        temp.innerDim = innerDim;

        if constexpr (columnMajor) {
            temp.numRows = innerDim;
            temp.numCols = temp.outerDim;
        }
        else {
            temp.numRows = temp.outerDim;
            temp.numCols = innerDim;
        }

        // allocate the vectors
        try {
            temp.data = (void**)malloc((end - start) * sizeof(void*));
            temp.endPointers = (void**)malloc((end - start) * sizeof(void*));
        }
        catch (std::bad_alloc& e) {
            throw std::bad_alloc();
        }

        // copy the vectors
        for (uint32_t i = start; i < end; ++i) {

            try {
                temp.data[i - start] = malloc(getVectorByteSize(i));
                temp.endPointers[i - start] = (char*)temp.data[i - start] + getVectorByteSize(i);
            }
            catch (std::bad_alloc& e) {
                throw std::bad_alloc();
            }

            // copy the vector
            memcpy(temp.data[i - start], data[i], getVectorByteSize(i));
        }

        // get nnz
        temp.nnz = 0;
        for (int i = 0; i < temp.outerDim; ++i) {
            if (temp.getVectorByteSize(i) == 0) continue;
            for (typename IVCSC<T, columnMajor>::InnerIterator it(temp, i); it; ++it) {
                temp.nnz++;
            }
        }

        temp.metadata = new uint32_t[NUM_META_DATA];
        temp.metadata[0] = 3;
        temp.metadata[1] = temp.innerDim;
        temp.metadata[2] = temp.outerDim;
        temp.metadata[3] = temp.nnz;
        temp.metadata[4] = val_t;
        temp.metadata[5] = index_t;


        // update metadata
        temp.calculateCompSize();
        return temp;
    }


}  // end namespace IVSparse