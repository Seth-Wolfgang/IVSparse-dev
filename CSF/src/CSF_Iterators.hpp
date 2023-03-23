#pragma once
#define META_DATA_SIZE 24 // number of bytes in metadata (7 * 4)
#define NUM_META_DATA 6   // number of metadata values

namespace CSF
{
    //** ------------------------------------------------------------------------------------------------------------------ **//
    //** --------------------------------------------- InnerIterator Class (2 & 3) --------------------------------------------- **//
    //** ------------------------------------------------------------------------------------------------------------------ **//

    // ---------------- InnerIterator Constructors ---------------- //

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    SparseMatrix<T, indexT, compressionLevel, columnMajor>::InnerIterator::InnerIterator(CSF::SparseMatrix<T, indexT, compressionLevel, columnMajor> &matrix, uint32_t vec)
    {

        // Sets the column
        this->outer = vec;

        // Sets the data pointer to the specified column of the matrix
        data = matrix.getVecPointer(vec);

        // If the column is all zeros, set the data to the end pointer
        if (data == nullptr)
        {
            // Trips bool operator
            data = endPtr;
            return;
        }

        // Sets the end pointer
        uint32_t vecSize = matrix.getVecSize(vec);
        endPtr = (uint8_t *)data + vecSize;

        // Points value to the first value in the column
        val = (T *)data;
        data = (uint8_t *)data + sizeof(T);

        // Sets row width to the width of the first run
        indexWidth = *(uint8_t *)data;
        data = (uint8_t *)data + sizeof(uint8_t);

        decodeIndex();
        index = newIdx;
    }

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    SparseMatrix<T, indexT, compressionLevel, columnMajor>::InnerIterator::InnerIterator(SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector &vector)
    {
        // set the column to -1
        this->outer = 0;

        // set the data pointer
        data = vector.begin();

        // If the column is all zeros, set the data to the end pointer
        if (data == nullptr)
        {
            // Trips bool operator
            data = endPtr;
            return;
        }

        // set the end pointer
        endPtr = vector.end();

        val = (T *)data;
        data = (uint8_t *)data + sizeof(T);

        indexWidth = *(uint8_t *)data;
        data = (uint8_t *)data + sizeof(uint8_t);

        decodeIndex();
        index = newIdx;
    }

    // ------------------------------- InnerIterator Methods ----------------------------------- //

    // ---------------- Public Methods ---------------- //

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    indexT SparseMatrix<T, indexT, compressionLevel, columnMajor>::InnerIterator::outerDim() { return outer; }

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    T SparseMatrix<T, indexT, compressionLevel, columnMajor>::InnerIterator::value() { return *val; }

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    T &SparseMatrix<T, indexT, compressionLevel, columnMajor>::InnerIterator::operator*() { return *val; }

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    bool SparseMatrix<T, indexT, compressionLevel, columnMajor>::InnerIterator::operator==(const InnerIterator &other) { return data == other.getIndex(); }

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    bool SparseMatrix<T, indexT, compressionLevel, columnMajor>::InnerIterator::operator!=(const InnerIterator &other) { return data != other.getIndex(); }

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    bool SparseMatrix<T, indexT, compressionLevel, columnMajor>::InnerIterator::operator<(const InnerIterator &other) { return data < other.getIndex(); }

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    bool SparseMatrix<T, indexT, compressionLevel, columnMajor>::InnerIterator::operator>(const InnerIterator &other) { return data > other.getIndex(); }

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    indexT SparseMatrix<T, indexT, compressionLevel, columnMajor>::InnerIterator::getIndex() { return index; }

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    void SparseMatrix<T, indexT, compressionLevel, columnMajor>::InnerIterator::operator++(int)
    {
        data = (uint8_t *)data + indexWidth;

        decodeIndex();

        // If new_row is 0 and not the first row, then the row is a delimitor
        if (newIdx == 0)
        {

            if (data >= (uint8_t *)endPtr - indexWidth) [[unlikely]]
            {
                return;
            }

            data = (uint8_t *)data + indexWidth;

            // val is the first row of the run
            val = (T *)data;
            data = (char *)data + sizeof(T);

            // indexWidth is the second val in the run
            indexWidth = *(uint8_t *)data;
            data = (uint8_t *)data + sizeof(uint8_t);

            // update currentCol to the next column

            // Make row 0 as it is a new run
            decodeIndex();
            index = newIdx;

            return;
        }

        if constexpr (compressionLevel == 2)
        {
            index = newIdx;
        }
        else
            index += newIdx;
    }

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    void SparseMatrix<T, indexT, compressionLevel, columnMajor>::InnerIterator::operator++()
    {

        data = (uint8_t *)data + indexWidth;

        decodeIndex();

        // If new_row is 0 and not the first row, then the row is a delimitor
        if (newIdx == 0)
        {

            if (data >= (uint8_t *)endPtr - indexWidth) [[unlikely]]
            {
                return;
            }

            data = (uint8_t *)data + indexWidth;

            // val is the first row of the run
            val = (T *)data;
            data = (char *)data + sizeof(T);

            // indexWidth is the second val in the run
            indexWidth = *(uint8_t *)data;
            data = (uint8_t *)data + sizeof(uint8_t);

            // update currentCol to the next column

            // Make row 0 as it is a new run
            decodeIndex();
            index = newIdx;

            return;
        }

        // Depending on if the CSF::SparseMatrix is at compression level 2 or 3, we handle the row differently
        // Compression level 3 is postive delta encoded, so we return the sum of the current row and the previous ones
        if constexpr (compressionLevel == 2)
        {
            index = newIdx;
        }
        else
            index += newIdx;
    }

    // ---------------- Private Methods ---------------- //

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    void SparseMatrix<T, indexT, compressionLevel, columnMajor>::InnerIterator::decodeIndex()
    {

        switch (indexWidth)
        {
        case 1:
            newIdx = (indexT) * (uint8_t *)data;
            break;
        case 2:
            newIdx = (indexT) * (uint16_t *)data;
            break;
        case 4:
            newIdx = (indexT) * (uint32_t *)data;
            break;
        case 8:
            newIdx = (indexT) * (uint64_t *)data;
            break;
        }
    }

    //** ------------------------------------------------------------------------------------------------------------------ **//
    //** ----------------------------------------------- InnerIterator Class (1) ----------------------------------------------- **//
    //** ------------------------------------------------------------------------------------------------------------------ **//

    // ---------------- Public Methods ---------------- //
}