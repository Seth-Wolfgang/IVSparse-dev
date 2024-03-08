/**
 * @file VCSC_Parallel_Methods.hpp
 * @author Skyler Ruiter and Seth Wolfgang
 * @brief Parallel Methods for VCSC Sparse Matrices
 *        Note: These files are for algorithms that required changes to the algorithm to be parallelized.
 *        Trivially parallelizable algorithms are in the original file.
 * @version 0.1
 * @date 2024-03-08
 */

namespace IVSparse {
    
    template <typename T, typename indexT, bool columnMajor>
    IVSparse::VCSC<T, indexT, columnMajor> VCSC<T, indexT, columnMajor>::transpose() {
        // make a data structure to store the tranpose
        // std::unordered_map<T, std::vector<indexT>> mapsT[innerDim];
        std::vector<std::unordered_map<T, std::vector<indexT>>> mapsT(innerDim);
        mapsT.resize(innerDim);
        std::vector<std::mutex> mutexList(innerDim);

        // populate the transpose data structure
        #ifdef IVSPARSE_HAS_OPENMP
        #pragma omp parallel for
        #endif        
        for (uint32_t i = 0; i < outerDim; ++i) {

            for (typename VCSC<T, indexT, columnMajor>::InnerIterator it(*this, i); it; ++it) {
                std::lock_guard lock(mutexList[it.getIndex()]);
                mapsT[it.getIndex()][it.value()].push_back(i);
            }
        }

        // create a new matrix passing in transposedMap
        IVSparse::VCSC<T, indexT, columnMajor> temp(mapsT.data(), numRows, numCols);

        // return the new matrix
        return temp;
    }

        template <typename T, typename indexT, bool columnMajor>
    void VCSC<T, indexT, columnMajor>::write(char* filename) {

        std::string file = std::string(filename);
        if (strcasestr(filename, ".vcsc") == NULL) {
            file += std::string(".vcsc");
        }

        // Open the file
        FILE* fp = fopen(file.c_str(), "wb+");
        if (fp == NULL) [[unlikely]] {
            throw std::runtime_error("Error opening " + file);
        }

            // This is the size of what is going to be written
            // and the size of valueSizes and indexSizes
        uint64_t offset = outerDim * sizeof(indexT);

        // write the metadata and lengths of the vectors
        #pragma omp parallel sections
        {
            #pragma omp section
            {
                if (pwrite(fileno(fp), metadata, META_DATA_SIZE, 0) == -1) [[unlikely]] {
                    throw std::runtime_error("Error writing to " + file);
                }
            }
            #pragma omp section
            {
                if (pwrite(fileno(fp), valueSizes, offset, META_DATA_SIZE) == -1) [[unlikely]] {
                    throw std::runtime_error("Error writing to " + file);
                }
            }
            #pragma omp section
            {
                if (pwrite(fileno(fp), indexSizes, offset, META_DATA_SIZE + offset) == -1) [[unlikely]] {
                    throw std::runtime_error("Error writing to " + file);
                }
            }
        }

        offset = (offset * 2) + META_DATA_SIZE;
        uint64_t countsStart = offset;
        uint64_t indicesStart = 0; // zero becaue offset is added after loop

        #pragma omp parallel for reduction(+: countsStart, indicesStart)
        for (int i = 0; i < outerDim; ++i) {
            countsStart += valueSizes[i] * sizeof(T);
            indicesStart += valueSizes[i] * sizeof(indexT);
        }
        indicesStart += countsStart;

        #pragma omp parallel for 
        for (uint32_t i = 0; i < outerDim; ++i) {

            uint64_t tempOffset = offset;
            uint64_t tempCountsStart = countsStart;
            uint64_t tempIndicesStart = indicesStart;

            #pragma omp simd
            for (int j = 1; j <= i; ++j) {
                // std::cout << "j: " << j << std::endl;
                tempOffset += valueSizes[j - 1] * sizeof(T);
                tempCountsStart += valueSizes[j - 1] * sizeof(indexT);
                tempIndicesStart += indexSizes[j - 1] * sizeof(indexT);
            }

            if (pwrite(fileno(fp), values[i], valueSizes[i] * sizeof(T), tempOffset) == -1 ||
                pwrite(fileno(fp), counts[i], valueSizes[i] * sizeof(indexT), tempCountsStart) == -1 ||
                pwrite(fileno(fp), indices[i], indexSizes[i] * sizeof(indexT), tempIndicesStart) == -1) [[unlikely]] {
                throw std::runtime_error("Error writing to " + file);
            }

        }

        // close the file
        fclose(fp);
    }

}