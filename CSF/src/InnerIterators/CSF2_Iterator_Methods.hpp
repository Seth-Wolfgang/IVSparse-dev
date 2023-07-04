/**
 * @file CSF2_Iterator_Methods.hpp
 * @author Skyler Ruiter and Seth Wolfgang
 * @brief Iterator Methods for CSF2 Sparse Matrices
 * @version 0.1
 * @date 2023-07-03
 */

#pragma once

namespace CSF {


    // ---------------- InnerIterator Constructors ---------------- //

    template <typename T, typename indexT, bool columnMajor>
    inline SparseMatrix<T, indexT, 2, columnMajor>::InnerIterator::InnerIterator(CSF::SparseMatrix<T, indexT, 2, columnMajor>& matrix, uint32_t vec) {

        // check if the vector is empty
        if (matrix.getNumUniqueVals(vec) == 0) {
            this->vals = nullptr;
            this->counts = nullptr;
            this->indices = nullptr;
            this->val = nullptr;
            this->index = 0;
            this->count = 0;

            countIndex = 0;
            indexSize = 0;

            return;
        }

        this->outer = vec;

        this->vals = matrix.getValues(vec);
        this->counts = matrix.getCounts(vec);
        this->indices = matrix.getIndices(vec);

        this->valsSize = matrix.getNumUniqueVals(vec);
        this->indexSize = matrix.getNumIndices(vec);
        
        this->val = vals;
        this->index = indices[0];

        this->count = counts[0];
    }

    template <typename T, typename indexT, bool columnMajor>
    SparseMatrix<T, indexT, 2, columnMajor>::InnerIterator::InnerIterator(SparseMatrix<T, indexT, 2, columnMajor>::Vector& vector) {
        
    }

    // ------------------------------- InnerIterator Methods ----------------------------------- //

    // ---------------- Public Methods ---------------- //

    template <typename T, typename indexT, bool columnMajor>
    inline bool SparseMatrix<T, indexT, 2, columnMajor>::InnerIterator::isNewRun() { return firstIndex; }

    template <typename T, typename indexT, bool columnMajor>
    indexT SparseMatrix<T, indexT, 2, columnMajor>::InnerIterator::outerDim() { return outer; }

    template <typename T, typename indexT, bool columnMajor>
    T SparseMatrix<T, indexT, 2, columnMajor>::InnerIterator::value() {
        return *val;
    }

    template <typename T, typename indexT, bool columnMajor>
    T& SparseMatrix<T, indexT, 2, columnMajor>::InnerIterator::operator*() {
        return *val;
    }

    template <typename T, typename indexT, bool columnMajor>
    bool SparseMatrix<T, indexT, 2, columnMajor>::InnerIterator::operator==(const InnerIterator& other) { 
        return values == other.values;
    }

    template <typename T, typename indexT, bool columnMajor>
    bool SparseMatrix<T, indexT, 2, columnMajor>::InnerIterator::operator!=(const InnerIterator& other) { 
        return values != other.values;
    }

    template <typename T, typename indexT, bool columnMajor>
    bool SparseMatrix<T, indexT, 2, columnMajor>::InnerIterator::operator<(const InnerIterator& other) { 
        return values < other.values;
    }

    template <typename T, typename indexT, bool columnMajor>
    bool SparseMatrix<T, indexT, 2, columnMajor>::InnerIterator::operator>(const InnerIterator& other) { 
        return values > other.values;
    }

    template <typename T, typename indexT, bool columnMajor>
    indexT SparseMatrix<T, indexT, 2, columnMajor>::InnerIterator::getIndex() { return index; }

    template <typename T, typename indexT, bool columnMajor>
    inline void SparseMatrix<T, indexT, 2, columnMajor>::InnerIterator::coeff(T newValue) {
        *val = newValue;
    }

    template <typename T, typename indexT, bool columnMajor>
    indexT SparseMatrix<T, indexT, 2, columnMajor>::InnerIterator::row() {
        if constexpr (!columnMajor)
            return outer;
        else
            return index;
    }

    template <typename T, typename indexT, bool columnMajor>
    indexT SparseMatrix<T, indexT, 2, columnMajor>::InnerIterator::col() {
        if constexpr (!columnMajor)
            return index;
        else
            return outer;
    }

    template <typename T, typename indexT, bool columnMajor>
    void SparseMatrix<T, indexT, 2, columnMajor>::InnerIterator::operator++() {
        
        // decriment count
        count--;

        // if count is 0 then we need to move to the next value
        if (count == 0) {

            // Check if we are at the end of the values array
            countIndex++;
            if (countIndex >= indexSize) {
                return;
            }

            firstIndex = true;

            // Move to the next value
            val++;

            // Get the new count
            counts++;
            count = *counts;

            // Get the new index
            indices++;
            index = *indices;
        } else {
            // Move to the next index
            countIndex++;
            indices++;
            index = *indices;

            firstIndex = false;
        }

    }

}