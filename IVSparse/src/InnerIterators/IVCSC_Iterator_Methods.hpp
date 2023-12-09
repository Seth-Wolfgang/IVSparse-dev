/**
 * @file IVCSC_Iterator_Methods.hpp
 * @author Skyler Ruiter and Seth Wolfgang
 * @brief Iterator Methods for IVCSC Sparse Matrices
 * @version 0.1
 * @date 2023-07-03
 */

#pragma once

namespace IVSparse {

    //* Constructors *//

    // Matrix Constructor
    template<typename T, bool columnMajor>
    inline IVCSC<T, columnMajor>::InnerIterator::InnerIterator(IVSparse::IVCSC<T, columnMajor>& matrix, uint32_t vec) {
        // check if the vector is out of bounds
        #ifdef IVSPARSE_DEBUG
        assert((vec < matrix.outerDim && vec >= 0) && "Vector index out of bounds.");
        #endif

        // check if data is nullptr
        if (matrix.vectorPointer(vec) == nullptr || matrix.getVectorByteSize(vec) == 0) {
            // Trips bool operator
            data = (void*)0xFFFFFFFFFFFFFFFF;
            endPtr = (void*)0xFFFFFFFFFFFFFFFF;
            return;
        }

        // Sets the column
        this->outer = vec;

        // Points value to the first value in the column
        data = matrix.vectorPointer(vec);

        // Sets the end pointer
        endPtr = (uint8_t*)data + matrix.getVectorByteSize(vec);

        val = (T*)data;
        data = (uint8_t*)data + sizeof(T);

        // Sets row width to the width of the first run
        indexWidth = *(uint8_t*)data;
        data = (uint8_t*)data + sizeof(uint8_t);

        decodeIndex();
        index = newIndex;
    }

    //* Getters *//

    // If the iterator is at a new run
    template<typename T, bool columnMajor>
    inline bool IVCSC<T, columnMajor>::InnerIterator::isNewRun() {
        return firstIndex;
    }

    // Get the current outer dimension of the iterator
    template<typename T, bool columnMajor>
    size_t IVCSC<T, columnMajor>::InnerIterator::outerDim() {
        return outer;
    }

    // Get the current value of the iterator
    template<typename T, bool columnMajor>
    T IVCSC<T, columnMajor>::InnerIterator::value() {
        return *val;
    }

    // Get the current index of the iterator
    template<typename T, bool columnMajor>
    size_t IVCSC<T, columnMajor>::InnerIterator::getIndex() {
        return index;
    }

    // Updates the value of the iterator to newValue
    template<typename T, bool columnMajor>
    inline void IVCSC<T, columnMajor>::InnerIterator::coeff(T newValue) {
        *val = newValue;
    }

    // Current row of the iterator
    template<typename T, bool columnMajor>
    size_t IVCSC<T, columnMajor>::InnerIterator::row() {
        if constexpr (!columnMajor) {
            return outer;
        }
        else {
            return index;
        }
    }

    // Current column of the iterator
    template<typename T, bool columnMajor>
    size_t IVCSC<T, columnMajor>::InnerIterator::col() {
        if constexpr (!columnMajor) {
            return index;
        }
        else {
            return outer;
        }
    }

    //* Private Class Methods *//

    // Index decoder
    template<typename T, bool columnMajor>
    inline void __attribute__((hot)) IVCSC<T, columnMajor>::InnerIterator::decodeIndex() {
        switch (indexWidth) {
        case 1:
            newIndex = static_cast<size_t>(*static_cast<uint8_t*>(data));
            break;
        case 2:
            newIndex = static_cast<size_t>(*static_cast<uint16_t*>(data));
            break;
        case 3:
            newIndex = static_cast<size_t>(*static_cast<uint32_t*>(data) & 0xFFFFFF);
            break;
        case 4:
            newIndex = static_cast<size_t>(*static_cast<uint32_t*>(data));
            break;
        case 5:
            newIndex = static_cast<size_t>(*static_cast<uint64_t*>(data) & 0xFFFFFFFFFF);
            break;
        case 6:
            newIndex = static_cast<size_t>(*static_cast<uint64_t*>(data) & 0xFFFFFFFFFFFF);
            break;
        case 7:
            newIndex = static_cast<size_t>(*static_cast<uint64_t*>(data) & 0xFFFFFFFFFFFFFF);
            break;
        case 8:
            newIndex = static_cast<size_t>(*static_cast<uint64_t*>(data));
            break;
        default:
            printf("(IVSparse): Invalid index width (%d) after index (%ld, %ld). IVCSC matrix constructed incorrectly.\n", indexWidth, index, outer);
            exit(1);
            break;
        }
    }

    //* Operator Overloads *//

    // Dereference Operator
    template<typename T, bool columnMajor>
    T& IVCSC<T, columnMajor>::InnerIterator::operator*() {
        return *val;
    }

    // Equality Operator
    template<typename T, bool columnMajor>
    bool IVCSC<T, columnMajor>::InnerIterator::operator==(const InnerIterator& other) {
        return data == other.getIndex();
    }

    // Inequality Operator
    template<typename T, bool columnMajor>
    bool IVCSC<T, columnMajor>::InnerIterator::operator!=(const InnerIterator& other) {
        return data != other.getIndex();
    }

    // Less Than Operator
    template<typename T, bool columnMajor>
    bool IVCSC<T, columnMajor>::InnerIterator::operator<(const InnerIterator& other) {
        return data < other.getIndex();
    }

    // Greater Than Operator
    template<typename T, bool columnMajor>
    bool IVCSC<T, columnMajor>::InnerIterator::operator>(const InnerIterator& other) {
        return data > other.getIndex();
    }

    // Increment Operator
    template<typename T, bool columnMajor>
    void IVCSC<T, columnMajor>::InnerIterator::operator++() {
        data = (uint8_t*)data + indexWidth;
        decodeIndex();

        // IVSparse 3
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

            // Make row 0 as it is a new run
            decodeIndex();
            index = newIndex;
            firstIndex = true;
            return;
        }
        index += newIndex;

        firstIndex = false;
    }

}  // namespace IVSparse
