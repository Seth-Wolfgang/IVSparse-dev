/**
 * @file CSF_Iterator.hpp
 * @author Skyler Ruiter and Seth Wolfgang
 * @brief The Inner Iterator decleration for the CSF class
 * @version 0.1
 * @date 2023-06-23
 */

#pragma once

namespace CSF {

    /**
     * The Iterator for the CSF Sparse Matrix Class \n \n
     * This class is used to iterate through the inner dimension of the matrix.
     * It is used much like the eigen inner iterator. This means that this iterator
     * is a forward iterator and can only be used to iterate through the matrix once.
    */
    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    class SparseMatrix<T, indexT, compressionLevel, columnMajor>::InnerIterator
    {
        private:
        //* Private Class Variables *//

        indexT outer; // The outer index of the current value
        indexT index; // The index of the current value
        T *val;      // The value where the iterator is pointing

        indexT newIndex; // The index of the next value

        uint8_t indexWidth = 1; // The width of the index in bytes

        void *data; // The pointer to the data
        void *endPtr; // The pointer to the end of the data

        bool firstIndex = true; // If the iterator is on the first index

        bool performanceVectors = false; // If the performance vectors are being used
        T *valueArray = nullptr; // The array of values if the performance vectors are being used

        //* Private Class Methods *//

        // Casts the index to the correct type
        void __attribute__((hot)) decodeIndex();

        public:
        //* Constructors & Destructor *//

        /**
         * Constructs a new blank Inner Iterator object.
         * 
         * @note The default iterator constructor is not used.
         */
        InnerIterator();

        /**
         * Constructs an iterator from a CSF matrix and a column/row. \n \n
         * This constructor is the main constructor used for iterating through 
         * a CSF matrix.
         * 
         * @attention This constructor only iterates along the inner dimension of the matrix.
        */
        InnerIterator(SparseMatrix<T, indexT, compressionLevel, columnMajor> &mat, uint32_t col);

        /**
         * Creates an iterator for a CSF vector. \n \n
         * This constructor is used to iterate through a CSF vector much like an entire matrix.
         */
        InnerIterator(SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector &vec);

        //* Getters *//

        /**
         * @returns The index of the current value.
        */
        indexT getIndex();

        /**
         * @returns The outer dimension of the iterating container.
        */
        indexT outerDim();

        /**
         * @returns The row of the current value.
        */
        indexT row();

        /**
         * @returns The column of the current value.
        */
        indexT col();

        /**
         * @returns The current value of the iterator.
        */
        T value();

        /**
         * Updates the current value of the iterator.
         * 
         * @note This is the only way to update specific values in a CSF matrix.
        */
        void coeff(T newValue);

        //* Utility Methods *//

        /**
         * @returns If the iterator is currently on a new CSF run.
         * 
         * @note A run is a value followed by its indices, so a new run is at the first index of a value.
        */
        bool isNewRun();        
        
        //* Operator Overloads *//

        // Prefix increment operator
        void __attribute__((hot)) operator++();

        // Equality operator
        bool operator==(const InnerIterator &other);

        // Inequality operator
        bool operator!=(const InnerIterator &other);

        // Less than operator
        bool operator<(const InnerIterator &other);

        // Greater than operator
        bool operator>(const InnerIterator &other);

        // Conversion to bool operator
        inline __attribute__((hot)) operator bool() { return (char *)endPtr - indexWidth > data; };

        // Dereference operator
        T &operator*();
    };
}