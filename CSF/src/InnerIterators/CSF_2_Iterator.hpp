#pragma once

namespace CSF {


    // ---------------- InnerIterator Constructors ---------------- //

    template <typename T, typename indexT, bool columnMajor>
    inline SparseMatrix<T, indexT, 2, columnMajor>::InnerIterator::InnerIterator(CSF::SparseMatrix<T, indexT, compressionLevel, columnMajor>& matrix, uint32_t vec) {

        // Sets the column
        this->outer = vec;

        if (matrix.isPerformanceVecsOn()) {
            performanceVectors = true;
            valueArray = matrix.valueArray[vec];
            countsArray = matrix.countsArray[vec];
        }

        // Sets the data pointer to the specified column of the matrix
        data = matrix.vectorPointer(vec);

        // If the column is all zeros, set the data to the end pointer
        if (data == nullptr) [[unlikely]] {
            // Trips bool operator
            data = endPtr;
            return;
        }

            // Sets the end pointer
        endPtr = (uint8_t*)data + matrix.getVecSize(vec);

        // Points value to the first value in the column
        val = (T*)data;
        data = (uint8_t*)data + sizeof(T);

        if constexpr (compressionLevel == 3) {
            // Sets row width to the width of the first run
            indexWidth = *(uint8_t*)data;
            data = (uint8_t*)data + sizeof(uint8_t);
        }
        else {
            indexWidth = sizeof(indexT);
        }

        decodeIndex();
        index = newIndex;
    }

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    SparseMatrix<T, indexT, compressionLevel, columnMajor>::InnerIterator::InnerIterator(SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector& vector) {
        // set the column to -1
        this->outer = 0;

        if (vector.isPerformanceVecsOn()) {
            performanceVectors = true;
            valueArray = vector.valueArray[0];
            countsArray = vector.countsArray[0];
        }

        // set the data pointer
        data = vector.begin();

        // If the column is all zeros, set the data to the end pointer
        if (data == nullptr) {
            // Trips bool operator
            data = endPtr;
            return;
        }

        val = (T*)data;
        data = (uint8_t*)data + sizeof(T);

        // set the end pointer
        endPtr = vector.end();

        if constexpr (compressionLevel == 3) {
            // Sets row width to the width of the first run
            indexWidth = *(uint8_t*)data;
            data = (uint8_t*)data + sizeof(uint8_t);
        }
        else {
            indexWidth = sizeof(indexT);
        }

        decodeIndex();
        index = newIndex;
    }

    // ------------------------------- InnerIterator Methods ----------------------------------- //

    // ---------------- Public Methods ---------------- //

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    inline bool SparseMatrix<T, indexT, compressionLevel, columnMajor>::InnerIterator::isNewRun() { return firstIndex; }

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    indexT SparseMatrix<T, indexT, compressionLevel, columnMajor>::InnerIterator::outerDim() { return outer; }

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    T SparseMatrix<T, indexT, compressionLevel, columnMajor>::InnerIterator::value() {
        if (performanceVectors)
            return valueArray[(int)*val];
        else
            return *val;
    }

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    T& SparseMatrix<T, indexT, compressionLevel, columnMajor>::InnerIterator::operator*() {
        if (performanceVectors)
            return valueArray[*val];
        else
            return *val;
    }

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    bool SparseMatrix<T, indexT, compressionLevel, columnMajor>::InnerIterator::operator==(const InnerIterator& other) { return data == other.getIndex(); }

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    bool SparseMatrix<T, indexT, compressionLevel, columnMajor>::InnerIterator::operator!=(const InnerIterator& other) { return data != other.getIndex(); }

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    bool SparseMatrix<T, indexT, compressionLevel, columnMajor>::InnerIterator::operator<(const InnerIterator& other) { return data < other.getIndex(); }

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    bool SparseMatrix<T, indexT, compressionLevel, columnMajor>::InnerIterator::operator>(const InnerIterator& other) { return data > other.getIndex(); }

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    indexT SparseMatrix<T, indexT, compressionLevel, columnMajor>::InnerIterator::getIndex() { return index; }

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    inline void SparseMatrix<T, indexT, compressionLevel, columnMajor>::InnerIterator::coeff(T newValue) {
        if (!performanceVectors)
            *val = newValue;
        else
            valueArray[(int)*val] = newValue;
    }


    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    indexT SparseMatrix<T, indexT, compressionLevel, columnMajor>::InnerIterator::row() {
        if constexpr (!columnMajor)
            return outer;
        else
            return index;
    }

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    indexT SparseMatrix<T, indexT, compressionLevel, columnMajor>::InnerIterator::col() {
        if constexpr (!columnMajor)
            return index;
        else
            return outer;
    }


    void operator++() {
        data = (uint8_t*)data + indexWidth;

        decodeIndex();
        // If new_row is 0 and not the first row, then the row is a delimitor
        if constexpr (compressionLevel == 2) {
            if (countsArray[0] == count) {

                if (data >= (uint8_t*)endPtr - indexWidth) [[unlikely]] {
                    return;
                }

                    // val is the first row of the run
                val = (T*)data;
                data = (uint8_t*)data + sizeof(T);

                // Make row 0 as it is a new run
                decodeIndex();
                index = newIndex;
                firstIndex = true;
                count = 1;
                countsArray = (uint8_t*)countsArray + sizeof(uint32_t);
                return;
            }
            count++;
        }

        firstIndex = false;
        // Depending on if the CSF::SparseMatrix is at compression level 2 or 3, we handle the row differently
        // Compression level 3 is postive delta encoded, so we return the sum of the current row and the previous ones
        index = newIndex;
    }



    // ---------------- Private Methods ---------------- //

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    inline void __attribute__((hot)) SparseMatrix<T, indexT, compressionLevel, columnMajor>::InnerIterator::decodeIndex() {

        switch (indexWidth) {
        case 1:
            newIndex = static_cast<indexT>(*static_cast<uint8_t*>(data));
            break;
        case 2:
            newIndex = static_cast<indexT>(*static_cast<uint16_t*>(data));
            break;
        case 4:
            newIndex = static_cast<indexT>(*static_cast<uint32_t*>(data));
            break;
        case 8:
            newIndex = static_cast<indexT>(*static_cast<uint64_t*>(data));
            break;
        }
    }

}