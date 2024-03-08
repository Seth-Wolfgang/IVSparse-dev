




namespace IVSparse {

    template<typename T, bool columnMajor>
    IVSparse::IVCSC<T, columnMajor> IVCSC<T, columnMajor>::transpose() {

        std::vector<std::unordered_map<T, std::vector<size_t>>> mapsT;
        // mapsT.reserve(innerDim);
        mapsT.resize(innerDim);
        std::vector<std::mutex> mutexList(innerDim);
        // mutexList.resize(innerDim);

        #ifdef IVSPARSE_HAS_OPENMP
        #pragma omp parallel for
        #endif
        for (uint32_t i = 0; i < outerDim; ++i) {
            for (typename IVCSC<T, columnMajor>::InnerIterator it(*this, i); it; ++it) {
                std::lock_guard lock(mutexList[it.getIndex()]);
                mapsT[it.getIndex()][it.value()].push_back(i);
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


    template<typename T, bool columnMajor>
    void IVCSC<T, columnMajor>::write(char* filename) {

        std::string file = std::string(filename);
        if (strcasestr(filename, ".ivcsc") == NULL) {
            file += std::string(".ivcsc");
            // strcat(filename, ".vcsc");
        }
        FILE* fp = fopen(file.c_str(), "wb+");

        // Write the metadata
        if (pwrite(fileno(fp), metadata, META_DATA_SIZE, 0) == -1) {
            throw std::runtime_error("Error writing to " + file);
        }


        uint64_t* sizes = (uint64_t*)malloc((outerDim + 1) * sizeof(uint64_t));
        uint64_t* sizeDelta = (uint64_t*)malloc(outerDim * sizeof(uint64_t));

        // Calculate the size of each vector and write the size of each vector
        #pragma omp parallel for 
        for (uint32_t i = 0; i < outerDim; i++) {
            sizeDelta[i] = (uint8_t*)endPointers[i] - (uint8_t*)data[i];
            pwrite(fileno(fp), &sizeDelta[i], sizeof(uint64_t), META_DATA_SIZE + (i * 8)); // axis pointer (size of axis for parallel read)
        }

        // calculate the start of each vector from the beginning of the file
        sizes[0] = META_DATA_SIZE + (outerDim * 8);

        for (uint32_t i = 0; i < outerDim; i++) {
            sizes[i + 1] = sizes[i] + sizeDelta[i];
        }
        free(sizeDelta);


        // write the size of each vector
        #pragma omp parallel for
        for (uint32_t i = 0; i < outerDim; i++) {
            pwrite(fileno(fp), data[i], (uint8_t*)endPointers[i] - (uint8_t*)data[i], sizes[i]); // data
        }

        // close the file
        fclose(fp);
        free(sizes);
    }
}