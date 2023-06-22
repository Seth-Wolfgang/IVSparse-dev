#pragma once

namespace CSF {

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    bool SparseMatrix<T, indexT, compressionLevel, columnMajor>::performanceVectorsInitialized()
    {
        return performanceVectors;
    }

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    void SparseMatrix<T, indexT, compressionLevel, columnMajor>::setPerformanceVectors(bool on)
    {
        if (on)
        {
            initPerformanceVectors();
        }
        else
        {
            deletePerformanceVectors();
        }
    }

    //* Getters *//

    // Check for Column Major
    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    bool SparseMatrix<T, indexT, compressionLevel, columnMajor>::isColumnMajor() const { return columnMajor; }

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    void *SparseMatrix<T, indexT, compressionLevel, columnMajor>::vectorPointer(uint32_t vec) { return data[vec]; }

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    size_t SparseMatrix<T, indexT, compressionLevel, columnMajor>::getVectorSize(uint32_t vec) const { return (char *)endPointers[vec] - (char *)data[vec]; }

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    uint32_t SparseMatrix<T, indexT, compressionLevel, columnMajor>::innerSize() const { return innerDim; }

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    uint32_t SparseMatrix<T, indexT, compressionLevel, columnMajor>::outerSize() const { return outerDim; }

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    uint32_t SparseMatrix<T, indexT, compressionLevel, columnMajor>::rows() const { return numRows; }

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    uint32_t SparseMatrix<T, indexT, compressionLevel, columnMajor>::cols() const { return numCols; }

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    uint32_t SparseMatrix<T, indexT, compressionLevel, columnMajor>::nonZeros() const { return nnz; }

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    size_t SparseMatrix<T, indexT, compressionLevel, columnMajor>::byteSize() const { return compSize; }

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    typename SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector SparseMatrix<T, indexT, compressionLevel, columnMajor>::getVector(uint32_t vec) { return (*this)[vec]; }

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    T SparseMatrix<T, indexT, compressionLevel, columnMajor>::coeff(uint32_t row, uint32_t col)
    {
        return (*this)(row, col);
    }

    //* Utility Methods *//

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    void SparseMatrix<T, indexT, compressionLevel, columnMajor>::write(const char *filename)
    {
        // Open the file
        FILE *fp = fopen(filename, "wb");

        // Write the metadata
        fwrite(metadata, 1, NUM_META_DATA * sizeof(uint32_t), fp);

        // check if the performance vectors are on
        if (performanceVectors)
        {
            // write the performance vectors

            // first write the size of each vector
            for (uint32_t i = 0; i < outerDim; i++)
            {
                fwrite(&valueArraySize[i], 1, sizeof(uint32_t), fp);
            }

            // write each vector
            for (uint32_t i = 0; i < outerDim; i++)
            {
                fwrite(valueArray[i], 1, valueArraySize[i] * sizeof(T), fp);
            }

            // write the countsArray vector
            for (uint32_t i = 0; i < outerDim; i++)
            {
                fwrite(countsArray[i], 1, valueArraySize[i] * sizeof(uint32_t), fp);
            }

            // write the data
            for (uint32_t i = 0; i < outerDim; i++)
            {
                fwrite(data[i], 1, (char *)endPointers[i] - (char *)data[i], fp);
            }

            // close the file
            fclose(fp);

            // return
            return;
        }

        // write the size of each vector
        for (uint32_t i = 0; i < outerDim; i++)
        {
            uint64_t size = (uint8_t *)endPointers[i] - (uint8_t *)data[i];
            fwrite(&size, 1, sizeof(uint64_t), fp);
        }

        // write each vector
        for (uint32_t i = 0; i < outerDim; i++)
        {
            fwrite(data[i], 1, (char *)endPointers[i] - (char *)data[i], fp);
        }

        // close the file
        fclose(fp);
    }

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    void SparseMatrix<T, indexT, compressionLevel, columnMajor>::print()
    {
        bool flippedVectors = false;

        // check if the performance vectors are on
        if (performanceVectors)
        {
            // turn them off
            setPerformanceVectors(false);
            flippedVectors = true;
        }

        std::cout << std::endl;
        std::cout << "CSF Matrix" << std::endl;

        // if the matrix is less than 100 rows and columns print the whole thing
        if (numRows < 100 && numCols < 100)
        {
            // print the matrix
            for (uint32_t i = 0; i < numRows; i++)
            {
                for (uint32_t j = 0; j < numCols; j++)
                {
                    std::cout << coeff(i, j) << " ";
                }
                std::cout << std::endl;
            }
        }
        else if (numRows > 100 && numCols > 100)
        {
            // print the first 100 rows and columns
            for (uint32_t i = 0; i < 100; i++)
            {
                for (uint32_t j = 0; j < 100; j++)
                {
                    std::cout << coeff(i, j) << " ";
                }
                std::cout << std::endl;
            }
        }

        std::cout << std::endl;

        // if the performance vectors were on turn them back on
        if (flippedVectors)
        {
            setPerformanceVectors(true);
        }
    }

    //* Conversion/Transformation Methods *//

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    void SparseMatrix<T, indexT, compressionLevel, columnMajor>::append(typename CSF::SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector &vec)
    {
        // check if the matrix is empty
        if (nnz == 0) [[unlikely]]
        {
            *this = CSF::SparseMatrix<T, indexT, compressionLevel, columnMajor>(vec);
        } else {
            // check if the vector is empty, if so change the implementation details
            if (vec.begin() == vec.end()) [[unlikely]]
            {

                if (columnMajor)
                {
                    numCols++;
                }
                else
                {
                    numRows++;
                }
                outerDim++;

                // realloc the data to be one larger
                try
                {
                    data = (void **)realloc(data, outerDim * sizeof(void *));
                    endPointers = (void **)realloc(endPointers, outerDim * sizeof(void *));
                }
                catch (std::bad_alloc &e)
                {
                    throw std::bad_alloc();
                }

                // set the new vector to nullptr
                data[outerDim - 1] = nullptr;
                endPointers[outerDim - 1] = nullptr;

                compSize += sizeof(void *) * 2;

                // if perforamnce vectors are on
                if (performanceVectors)
                {
                    // realloc the valueArray to be one larger
                    try
                    {
                        valueArray = (T **)realloc(valueArray, outerDim * sizeof(T *));
                        countsArray = (uint32_t **)realloc(countsArray, outerDim * sizeof(uint32_t *));
                    }
                    catch (std::bad_alloc &e)
                    {
                        throw std::bad_alloc();
                    }

                    // set the new vector to nullptr
                    valueArray[outerDim - 1] = nullptr;
                    countsArray[outerDim - 1] = nullptr;

                    // realloc the valueArraySize to be one larger
                    try
                    {
                        valueArraySize = (uint32_t *)realloc(valueArraySize, outerDim * sizeof(uint32_t));
                    }
                    catch (std::bad_alloc &e)
                    {
                        throw std::bad_alloc();
                    }

                    // set the new valueArraySize to 0
                    valueArraySize[outerDim - 1] = 0;

                    compSize += sizeof(T *) * 2;
                    compSize += sizeof(uint32_t);
                }

                return;
            }
            else
            {

                // check that the vector is the correct size
                if ((vec.getLength() != innerDim))
                    throw std::invalid_argument("The vector must be the same size as the outer dimension of the matrix!");

                outerDim++;
                nnz += vec.nonZeros();
                if (columnMajor)
                {
                    numCols++;
                }
                else
                {
                    numRows++;
                }

                // realloc the data to be one larger
                try
                {
                    data = (void **)realloc(data, outerDim * sizeof(void *));
                    endPointers = (void **)realloc(endPointers, outerDim * sizeof(void *));
                }
                catch (std::bad_alloc &e)
                {
                    throw std::bad_alloc();
                }

                // malloc the new vector
                try
                {
                    data[outerDim - 1] = malloc(vec.byteSize());
                    endPointers[outerDim - 1] = (char *)data[outerDim - 1] + vec.byteSize();
                }
                catch (std::bad_alloc &e)
                {
                    throw std::bad_alloc();
                }

                // copy the vector into the new space
                memcpy(data[outerDim - 1], vec.begin(), vec.byteSize());

                // update the compression size
                compSize += vec.byteSize();
                compSize += sizeof(void *) * 2;

                // if perforamnce vectors are on
                if (performanceVectors) {

                    // realloc the valueArray to be one larger
                    try
                    {
                        valueArray = (T **)realloc(valueArray, outerDim * sizeof(T *));
                        countsArray = (uint32_t **)realloc(countsArray, outerDim * sizeof(uint32_t *));
                    }
                    catch (std::bad_alloc &e)
                    {
                        throw std::bad_alloc();
                    }

                    // malloc the new vector
                    try
                    {
                        valueArray[outerDim - 1] = (T *)malloc(vec.getValueArraySize() * sizeof(T));
                        countsArray[outerDim - 1] = (uint32_t *)malloc(vec.getValueArraySize() * sizeof(uint32_t));
                    }
                    catch (std::bad_alloc &e)
                    {
                        throw std::bad_alloc();
                    }

                    // copy the valueArray into the new space
                    memcpy(valueArray[outerDim - 1], vec.getValues(), vec.getValueArraySize() * sizeof(T));
                    memcpy(countsArray[outerDim - 1], vec.getCounts(), vec.getValueArraySize() * sizeof(uint32_t));

                    // realloc the valueArraySize to be one larger
                    try
                    {
                        valueArraySize = (uint32_t *)realloc(valueArraySize, outerDim * sizeof(uint32_t));
                    }
                    catch (std::bad_alloc &e)
                    {
                        throw std::bad_alloc();
                    }

                    // copy the valueArraySize into the new space
                    valueArraySize[outerDim - 1] = vec.getValueArraySize();

                    // update the compression size
                    compSize += sizeof(T *) * 2;
                    compSize += sizeof(uint32_t);

                }
            }
        }
    }

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    CSF::SparseMatrix<T, indexT, compressionLevel, columnMajor> SparseMatrix<T, indexT, compressionLevel, columnMajor>::transpose()
    {
        // make a data structure to store the tranpose
        std::unordered_map<T, std::vector<indexT>> mapsT[innerDim];

        // populate the transpose data structure
        for (uint32_t i = 0; i < outerDim; ++i)
        {
            for (typename SparseMatrix<T, indexT, compressionLevel>::InnerIterator it(*this, i); it; ++it)
            {
                // add the value to the map
                if constexpr (columnMajor)
                {
                    mapsT[it.row()][it.value()].push_back(it.col());
                }
                else
                {
                    mapsT[it.col()][it.value()].push_back(it.row());
                }
            }
        }

        // if compression level 3 the indices need to be encoded and packed
        if constexpr (compressionLevel == 3)
        {
            for (auto &row : mapsT)
            {
                for (auto &col : row)
                {

                    // find the max value in the vector
                    size_t max = col.second[0];

                    // delta encode the vector
                    for (uint32_t i = col.second.size() - 1; i > 0; --i)
                    {
                        col.second[i] -= col.second[i - 1];
                        if ((size_t)col.second[i] > max)
                            max = col.second[i];
                    }

                    max = byteWidth(max);
                    // append max to the vector
                    col.second.push_back(max);
                }
            }
        }

        // create a new matrix passing in transposedMap
        CSF::SparseMatrix<T, indexT, compressionLevel, columnMajor> temp(mapsT, numRows, numCols);

        if constexpr (compressionLevel == 2)
        {
            // initialize the performance vectors
            temp.setPerformanceVectors(true);
        }

        // return the new matrix
        return temp;
    }

    // Transpose In Place Method
    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    void SparseMatrix<T, indexT, compressionLevel, columnMajor>::inPlaceTranspose()
    {

        // make a data structure to store the tranpose
        std::unordered_map<T, std::vector<indexT>> mapsT[innerDim];

        // populate the transpose data structure
        for (uint32_t i = 0; i < outerDim; ++i)
        {
            for (typename SparseMatrix<T, indexT, compressionLevel>::InnerIterator it(*this, i); it; ++it)
            {
                // add the value to the map
                if constexpr (columnMajor)
                {
                    mapsT[it.row()][it.value()].push_back(it.col());
                }
                else
                {
                    mapsT[it.col()][it.value()].push_back(it.row());
                }
            }
        }

        // if compression level 3 the indices need to be encoded and packed
        if constexpr (compressionLevel == 3)
        {
            for (auto &row : mapsT)
            {
                for (auto &col : row)
                {

                    // find the max value in the vector
                    size_t max = col.second[0];

                    // delta encode the vector
                    for (uint32_t i = col.second.size() - 1; i > 0; --i)
                    {
                        col.second[i] -= col.second[i - 1];
                        if ((size_t)col.second[i] > max)
                            max = col.second[i];
                    }

                    max = byteWidth(max);
                    // append max to the vector
                    col.second.push_back(max);
                }
            }
        }

        *this = CSF::SparseMatrix<T, indexT, compressionLevel, columnMajor>(mapsT, numRows, numCols);

        if constexpr (compressionLevel == 2)
        {
            // initialize the performance vectors
            initPerformanceVectors();
        }
    }

    // slice method that returns an array of vectors
    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    typename CSF::SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector *SparseMatrix<T, indexT, compressionLevel, columnMajor>::slice(uint32_t start, uint32_t end)
    {
        #ifdef CSF_DEBUG
        // check that the start and end are valid
        assert(start < outerDim && end <= outerDim && start < end && "Invalid start and end values!");
        #endif

        // create a new array of vectors
        CSF::SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector *vectors = new CSF::SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector[end - start];

        // iterate over the matrix
        #ifdef CSF_PARALLEL
        #pragma omp parallel for
        #endif
        for (uint32_t i = start; i < end; ++i)
        {
            // create a new vector
            CSF::SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector vec(*this, i);

            // add the vector to the array
            vectors[i - start] = vec;
        }

        return vectors;
    }

    // to eigen method
    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    Eigen::SparseMatrix<T, columnMajor ? Eigen::ColMajor : Eigen::RowMajor> SparseMatrix<T, indexT, compressionLevel, columnMajor>::toEigen()
    {

        #ifdef CSF_DEBUG
        // assert that the matrix is not empty
        assert(outerDim > 0 && "Cannot convert an empty matrix to an Eigen matrix!");
        #endif

        // create a new sparse matrix
        Eigen::SparseMatrix<T, columnMajor ? Eigen::ColMajor : Eigen::RowMajor> eigenMatrix(numRows, numCols);

        // iterate over the matrix
        for (uint32_t i = 0; i < outerDim; ++i)
        {
            for (typename SparseMatrix<T, indexT, compressionLevel>::InnerIterator it(*this, i); it; ++it)
            {
                // add the value to the matrix
                eigenMatrix.insert(it.row(), it.col()) = it.value();
            }
        }

        // finalize the matrix
        eigenMatrix.makeCompressed();

        // return the matrix
        return eigenMatrix;
    }

} // end namespace CSF