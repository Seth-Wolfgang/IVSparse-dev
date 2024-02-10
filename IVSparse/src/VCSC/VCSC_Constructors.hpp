/**
 * @file VCSC_Constructors.hpp
 * @author Skyler Ruiter and Seth Wolfgang
 * @brief Constructors for VCSC Sparse Matrices
 * @version 0.1
 * @date 2023-07-03
 */

#pragma once

namespace IVSparse {

    // Destructor
    template <typename T, typename indexT, bool columnMajor>
    VCSC<T, indexT, columnMajor>::~VCSC() {

        // delete the meta data
        if (metadata != nullptr) {
            delete[] metadata;
        }

        // delete the values
        if (values != nullptr) {
            for (size_t i = 0; i < outerDim; i++) {
                if (values[i] != nullptr) {
                    free(values[i]);
                }
            }
            free(values);
        }
        if (counts != nullptr) {
            for (size_t i = 0; i < outerDim; i++) {
                if (counts[i] != nullptr) {
                    free(counts[i]);
                }
            }
            free(counts);
        }
        if (indices != nullptr) {
            for (size_t i = 0; i < outerDim; i++) {
                if (indices[i] != nullptr) {
                    free(indices[i]);
                }
            }
            free(indices);
        }

        if (valueSizes != nullptr) {
            free(valueSizes);
        }
        if (indexSizes != nullptr) {
            free(indexSizes);
        }
    }

    // Eigen Col Major Constructor
    template <typename T, typename indexT, bool columnMajor>
    VCSC<T, indexT, columnMajor>::VCSC(Eigen::SparseMatrix<T, 0>& mat) {

        // make sure the matrix is compressed
        mat.makeCompressed();

        // get the number of rows and columns
        numRows = mat.rows();
        numCols = mat.cols();

        outerDim = columnMajor ? numCols : numRows;
        innerDim = columnMajor ? numRows : numCols;

        // get the number of non-zero elements
        nnz = mat.nonZeros();

        // call the compression function
        compressCSC(mat.valuePtr(), mat.innerIndexPtr(), mat.outerIndexPtr());
    }

    // Eigen Row Major Constructor
    template <typename T, typename indexT, bool columnMajor>
    VCSC<T, indexT, columnMajor>::VCSC(Eigen::SparseMatrix<T, Eigen::RowMajor>& mat) {
        // make sure the matrix is compressed
        mat.makeCompressed();

        // get the number of rows and columns
        numRows = mat.rows();
        numCols = mat.cols();

        outerDim = numRows;
        innerDim = numCols;

        // get the number of non-zero elements
        nnz = mat.nonZeros();

        // call the compression function
        compressCSC(mat.valuePtr(), mat.innerIndexPtr(), mat.outerIndexPtr());
    }

    // Deep Copy Constructor
    template <typename T, typename indexT, bool columnMajor>
    VCSC<T, indexT, columnMajor>::VCSC(const IVSparse::VCSC<T, indexT, columnMajor>& other) {
        *this = other;
    }

    // Conversion Constructor
    template <typename T, typename indexT, bool columnMajor>
    VCSC<T, indexT, columnMajor>::VCSC(IVSparse::IVCSC<T, columnMajor>& other) {

        // other should be the same compression level as this now
        *this = other.template toVCSC<indexT>();

        // run the user checks and calculate the compression size
        calculateCompSize();

        #ifdef IVSPARSE_DEBUG
        userChecks();
        #endif
    }

    // Raw CSC Constructor
    template <typename T, typename indexT, bool columnMajor>
    template <typename T2, typename indexT2>
    VCSC<T, indexT, columnMajor>::VCSC(T2* vals, indexT2* innerIndices, indexT2* outerPtr, uint32_t num_rows, uint32_t num_cols, uint32_t nnz) {

        #ifdef IVSPARSE_DEBUG
        assert(num_rows > 0 && num_cols > 0 && nnz > 0 &&
               "Error: Matrix dimensions must be greater than 0");
        assert(innerIndices != nullptr && outerPtr != nullptr && vals != nullptr &&
               "Error: Pointers cannot be null");
        #endif


        // set the dimensions
        if (columnMajor) {
            innerDim = num_rows;
            outerDim = num_cols;
        }
        else {
            innerDim = num_cols;
            outerDim = num_rows;
        }
        numRows = num_rows;
        numCols = num_cols;
        this->nnz = nnz;

        // call the compression function
        compressCSC(vals, innerIndices, outerPtr);
    }

    // COO Constructor
    template <typename T, typename indexT, bool columnMajor>
    template <typename T2, typename indexT2>
    VCSC<T, indexT, columnMajor>::VCSC(std::vector<std::tuple<indexT2, indexT2, T2>>& entries, uint64_t num_rows, uint32_t num_cols, uint32_t nnz) {

        #ifdef IVSPARSE_DEBUG
        assert(num_rows > 0 && num_cols > 0 && nnz > 0 &&
               "Error: Matrix dimensions must be greater than 0");
        #endif

        // see if the matrix is empty
        if (nnz == 0) {
            *this = VCSC<T, indexT, columnMajor>();
        }

        // set the dimensions
        if (columnMajor) {
            innerDim = num_rows;
            outerDim = num_cols;
        }
        else {
            innerDim = num_cols;
            outerDim = num_rows;
        }

        numRows = num_rows;
        numCols = num_cols;
        this->nnz = nnz;
        encodeValueType();
        index_t = sizeof(indexT);

        metadata = new uint32_t[NUM_META_DATA];
        metadata[0] = 2;
        metadata[1] = innerDim;
        metadata[2] = outerDim;
        metadata[3] = nnz;
        metadata[4] = val_t;
        metadata[5] = index_t;

        // allocate the vectors
        try {
            values = (T**)malloc(sizeof(T*) * outerDim);
            counts = (indexT**)malloc(sizeof(indexT*) * outerDim);
            indices = (indexT**)malloc(sizeof(indexT*) * outerDim);
            valueSizes = (indexT*)malloc(sizeof(indexT) * outerDim);
            indexSizes = (indexT*)malloc(sizeof(indexT) * outerDim);
        }
        catch (std::bad_alloc& ba) {
            std::cerr << "bad_alloc caught: " << ba.what() << '\n';
            throw std::runtime_error("Error: Could not allocate memory");
        }

        // sort the tuples by first by column then by row
        std::sort(entries.begin(), entries.end(),
                  [](const std::tuple<indexT2, indexT2, T2>& a,
                     const std::tuple<indexT2, indexT2, T2>& b) {
                         if (std::get<1>(a) == std::get<1>(b)) {
                             return std::get<0>(a) < std::get<0>(b);
                         }
                         else {
                             return std::get<1>(a) < std::get<1>(b);
                         }
                  });

        std::map<T2, std::vector<indexT2>> maps[outerDim];

        // loop through the tuples
        for (size_t i = 0; i < nnz; i++) {
            // get the column
            indexT2 row = std::get<0>(entries[i]);
            indexT2 col = std::get<1>(entries[i]);
            T2 val = std::get<2>(entries[i]);

            // check if the value is already in the map
            if (maps[col].find(val) != maps[col].end()) {
                // value found positive delta encode it
                maps[col][val].push_back(row);
            }
            else {
                // value not found
                maps[col][val] = std::vector<indexT2>{ row };
            }

        }  // end of loop through tuples

        // loop through the array
        #ifdef IVSPARSE_HAS_OPENMP
        #pragma omp parallel for
        #endif
        for (size_t i = 0; i < outerDim; i++) {
            // check if the column is empty
            if (maps[i].empty()) {
                values[i] = nullptr;
                counts[i] = nullptr;
                indices[i] = nullptr;
                valueSizes[i] = 0;
                indexSizes[i] = 0;
                continue;
            }

            size_t performanceVecSize = 0;
            size_t numInidces = 0;

            // loop through the vectors of the map
            for (auto& val : maps[i]) {
                performanceVecSize++;
                numInidces += val.second.size();
            }

            try {
                values[i] = (T*)malloc(sizeof(T) * maps[i].size());
                counts[i] = (indexT*)malloc(sizeof(indexT) * maps[i].size());
                indices[i] = (indexT*)malloc(sizeof(indexT) * numInidces);
            }
            catch (std::bad_alloc& ba) {
                std::cerr << "bad_alloc caught: " << ba.what() << '\n';
                throw std::runtime_error("Error: Could not allocate memory");
            }

            valueSizes[i] = maps[i].size();
            indexSizes[i] = numInidces;

            size_t index = 0;
            size_t valIndex = 0;

            for (auto& val : maps[i]) {
                values[i][valIndex] = val.first;
                counts[i][valIndex] = val.second.size();

                for (auto& indexVal : val.second) {
                    indices[i][index] = indexVal;
                    index++;
                }

                valIndex++;
            }

        }  // end of loop through the array

        // run the user checks and calculate the compression size
        calculateCompSize();

        #ifdef IVSPARSE_DEBUG
        userChecks();
        #endif
    }

    // File Constructor
    template <typename T, typename indexT, bool columnMajor>
    VCSC<T, indexT, columnMajor>::VCSC(char* filename) {

        assert(strcasestr(filename, ".vcsc") != NULL && "Error: File must be a .vcsc file");

        // open the file
        FILE* fp = fopen(filename, "rb");

        #ifdef IVSPARSE_DEBUG
        // check if the file was opened
        if (fp == nullptr) {
            throw std::runtime_error("Error: Could not open file");
        }
        #endif

        // read the metadata
        metadata = new uint32_t[NUM_META_DATA];
        fread(metadata, sizeof(uint32_t), NUM_META_DATA, fp);

            // set the matrix info
        innerDim = metadata[1];
        outerDim = metadata[2];
        nnz = metadata[3];
        val_t = metadata[4];
        index_t = metadata[5];
        numRows = columnMajor ? innerDim : outerDim;
        numCols = columnMajor ? outerDim : innerDim;

        #ifdef IVSPARSE_DEBUG
        // if the compression level of the file is different than the compression
        // level of the class
        if (metadata[0] != 2) {
            // throw an error
            throw std::runtime_error(
                "Error: Compression level of file does not match compression level of "
                "class");
        }
        #endif

        // allocate the vectors
        try {
            values = (T**)malloc(sizeof(T*) * outerDim);
            counts = (indexT**)malloc(sizeof(indexT*) * outerDim);
            indices = (indexT**)malloc(sizeof(indexT*) * outerDim);
            valueSizes = (indexT*)malloc(sizeof(indexT) * outerDim);
            indexSizes = (indexT*)malloc(sizeof(indexT) * outerDim);
        }
        catch (std::bad_alloc& ba) {
            std::cerr << "bad_alloc caught: " << ba.what() << '\n';
            throw std::runtime_error("Error: Could not allocate memory");
        }

        // read in the value sizes
        for (size_t i = 0; i < outerDim; i++) {
            fread(&valueSizes[i], sizeof(indexT), 1, fp);
        }

        // read in the index sizes
        for (size_t i = 0; i < outerDim; i++) {
            fread(&indexSizes[i], sizeof(indexT), 1, fp);
        }

        // read in the values
        for (size_t i = 0; i < outerDim; i++) {
            try {
                values[i] = (T*)malloc(sizeof(T) * valueSizes[i]);
            }
            catch (std::bad_alloc& ba) {
                std::cerr << "bad_alloc caught: " << ba.what() << '\n';
                throw std::runtime_error("Error: Could not allocate memory");
            }
            fread(values[i], sizeof(T), valueSizes[i], fp);
        }

        // read in the counts
        for (size_t i = 0; i < outerDim; i++) {
            try {
                counts[i] = (indexT*)malloc(sizeof(indexT) * valueSizes[i]);
            }
            catch (std::bad_alloc& ba) {
                std::cerr << "bad_alloc caught: " << ba.what() << '\n';
                throw std::runtime_error("Error: Could not allocate memory");
            }
            fread(counts[i], sizeof(indexT), valueSizes[i], fp);
        }

        // read in the indices
        for (size_t i = 0; i < outerDim; i++) {
            try {
                indices[i] = (indexT*)malloc(sizeof(indexT) * indexSizes[i]);
            }
            catch (std::bad_alloc& ba) {
                std::cerr << "bad_alloc caught: " << ba.what() << '\n';
                throw std::runtime_error("Error: Could not allocate memory");
            }
            fread(indices[i], sizeof(indexT), indexSizes[i], fp);
        }

        // close the file
        fclose(fp);

        // calculate the compresssion size
        calculateCompSize();

        // run the user checks
        #ifdef IVSPARSE_DEBUG
        userChecks();
        #endif
    }  // end of File Constructor

    //* Private Constructors *//

    // Private Tranpose Constructor
    template <typename T, typename indexT, bool columnMajor>
    VCSC<T, indexT, columnMajor>::VCSC(std::unordered_map<T, std::vector<indexT>>* maps, uint32_t num_rows, uint32_t num_cols) {

        // set class variables
        if constexpr (columnMajor) {
            innerDim = num_cols;
            outerDim = num_rows;
        }
        else {
            innerDim = num_rows;
            outerDim = num_cols;
        }

        numRows = num_cols;
        numCols = num_rows;
        encodeValueType();
        index_t = sizeof(indexT);

        // allocate the vectors
        try {
            values = (T**)malloc(sizeof(T*) * outerDim);
            counts = (indexT**)malloc(sizeof(indexT*) * outerDim);
            indices = (indexT**)malloc(sizeof(indexT*) * outerDim);
            valueSizes = (indexT*)malloc(sizeof(indexT) * outerDim);
            indexSizes = (indexT*)malloc(sizeof(indexT) * outerDim);
        }
        catch (std::bad_alloc& ba) {
            std::cerr << "bad_alloc caught: " << ba.what() << '\n';
            throw std::runtime_error("Error: Could not allocate memory");
        }

        // loop through the array
        #ifdef IVSPARSE_HAS_OPENMP
        #pragma omp parallel for
        #endif
        for (size_t i = 0; i < outerDim; i++) {
            // check if the column is empty
            if (maps[i].empty()) [[unlikely]] {
                values[i] = nullptr;
                counts[i] = nullptr;
                indices[i] = nullptr;
                valueSizes[i] = 0;
                indexSizes[i] = 0;
                continue;
                }
            size_t byteSize = 0;
            size_t numInidces = 0;

            // loop through the vectors of the map
            for (auto& val : maps[i]) {
                // add the size of the vector to the byteSize
                byteSize += (sizeof(indexT) * val.second.size());

                // add the size of the vector to the numIndices
                numInidces += val.second.size();
            }

            try {
                values[i] = (T*)malloc(sizeof(T) * maps[i].size());
                counts[i] = (indexT*)malloc(sizeof(indexT) * maps[i].size());
                indices[i] = (indexT*)malloc(sizeof(indexT) * numInidces);
            }
            catch (std::bad_alloc& ba) {
                std::cerr << "bad_alloc caught: " << ba.what() << '\n';
                throw std::runtime_error("Error: Could not allocate memory");
            }

            valueSizes[i] = maps[i].size();
            indexSizes[i] = numInidces;
            nnz += numInidces;

            size_t index = 0;
            size_t valIndex = 0;

            for (auto& val : maps[i]) {
                values[i][valIndex] = val.first;
                counts[i][valIndex] = val.second.size();

                memcpy(&indices[i][index], val.second.data(), sizeof(indexT) * val.second.size());
                index += val.second.size();

                valIndex++;
            }

        }  // end of loop through the array

        // set the metadata
        metadata = new uint32_t[NUM_META_DATA];
        metadata[0] = 2;
        metadata[1] = innerDim;
        metadata[2] = outerDim;
        metadata[3] = nnz;
        metadata[4] = val_t;
        metadata[5] = index_t;

        // run the user checks and calculate the compression size
        calculateCompSize();

        #ifdef IVSPARSE_DEBUG
        userChecks();
        #endif
    }  // end of Private Tranpose Constructor

}  // namespace IVSparse