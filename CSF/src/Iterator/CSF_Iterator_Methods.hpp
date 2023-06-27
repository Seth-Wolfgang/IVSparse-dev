#pragma once

namespace CSF {


    // ---------------- InnerIterator Constructors ---------------- //

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    inline SparseMatrix<T, indexT, compressionLevel, columnMajor>::InnerIterator::InnerIterator(CSF::SparseMatrix<T, indexT, compressionLevel, columnMajor>& matrix, uint32_t vec) {

        // Sets the column
        this->outer = vec;

        // Points value to the first value in the column
        data = matrix.vectorPointer(vec);

        // Sets the end pointer
        endPtr = (uint8_t*)data + matrix.getVectorSize(vec);

        // If the column is all zeros, set the data to fail operator bool() 
        if (data == nullptr || data == endPtr) [[unlikely]] {
            // Trips bool operator
            // std::cout << "At vec: " << vec << std::endl;
            data = (void*)0xFFFFFFFFFFFFFFFF;
            return;
        }

        if constexpr (compressionLevel == 3) {
            val = (T*)data;
            data = (uint8_t*)data + sizeof(T);

            // Sets row width to the width of the first run
            indexWidth = *(uint8_t*)data;
            data = (uint8_t*)data + sizeof(uint8_t);
        }
        else {
            val = matrix.valueArray[vec];
            countsArray = matrix.countsArray[vec];
            valueArraySize = matrix.valueArraySize[vec];
            indexWidth = sizeof(indexT);
        }

        decodeIndex();
        index = newIndex;
    }

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    SparseMatrix<T, indexT, compressionLevel, columnMajor>::InnerIterator::InnerIterator(SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector& vector) {
        // set the column to -1
        this->outer = 0;

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
        return *val;
    }

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    T& SparseMatrix<T, indexT, compressionLevel, columnMajor>::InnerIterator::operator*() {
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
        *val = newValue;
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

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    void SparseMatrix<T, indexT, compressionLevel, columnMajor>::InnerIterator::operator++() {

        data = (uint8_t*)data + indexWidth;

        decodeIndex();

        if constexpr (compressionLevel == 2) {

            if (countsArray[0] == count) {

                if (valueArrayCounter == valueArraySize) [[unlikely]] {
                    return;
                }

                // val will be moved forward to the next value since
                // count is equal to the current value's number of occurences
                val++;

                // update the current row
                index = newIndex;
                firstIndex = true;

                // Reset count and iterate
                count = 1;
                countsArray++;
                valueArrayCounter++;

                return;
            }
            //else
            count++;
            index = newIndex;
        }
        else {

        
            // CSF 3
            // If new_row is 0 and not the first row, then the row is a delimitor
            if (newIndex == 0) {

                if (data >= (uint8_t*)endPtr - indexWidth) [[unlikely]] {
                    return;
                    }

                data = (uint8_t*)data + indexWidth;

                // val is the first row of the run
                val = (T*)data;
                data = (uint8_t*)data + sizeof(T);

                    // Sets row width to the width of the first run
                indexWidth = *(uint8_t*)data;
                data = (uint8_t*)data + sizeof(uint8_t);
                

                // update currentCol to the next column

                // Make row 0 as it is a new run
                decodeIndex();
                index = newIndex;
                firstIndex = true;
                return;
            }
            index += newIndex;
        }

        firstIndex = false;
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