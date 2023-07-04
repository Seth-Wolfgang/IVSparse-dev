#pragma once

namespace CSF {

    template <typename T, typename indexT, bool columnMajor>
    SparseMatrix<T, indexT, 1, columnMajor>::InnerIterator::InnerIterator(SparseMatrix<T, indexT, 1, columnMajor>& mat, uint32_t vec) {
        this->outer = vec;

        // check if the vector is empty
        if (mat.getOuterPointers()[vec] == mat.getOuterPointers()[vec + 1]) {
            vals = nullptr;
            indices = nullptr;
            endPtr = nullptr;
            return;
        }

        vals = &mat.vals[mat.outerPtr[vec]];
        indices = &mat.innerIdx[mat.outerPtr[vec]];
        endPtr = &mat.innerIdx[mat.outerPtr[vec + 1]];

        val = vals;
        index = indices[0];
    }

    template <typename T, typename indexT, bool columnMajor>
    SparseMatrix<T, indexT, 1, columnMajor>::InnerIterator::InnerIterator(SparseMatrix<T, indexT, 1, columnMajor>::Vector& vec) {
        this->outer = 0;

        vals = vec.values();
        indices = vec.indexPtr();
        endPtr = vec.indexPtr() + vec.nonZeros();

        val = vals;
        index = indices[0];
    }

    // //* Overloaded Operators *//

    template <typename T, typename indexT, bool columnMajor>
    void SparseMatrix<T, indexT, 1, columnMajor>::InnerIterator::operator++() {
        vals++;
        indices++;

        // check if the iterator is at the end of the vector
        if (indices == endPtr) {
            return;
        }

        val = vals;
        index = *indices;
    }

    template <typename T, typename indexT, bool columnMajor>
    bool SparseMatrix<T, indexT, 1, columnMajor>::InnerIterator::operator==(const InnerIterator& other) { return (vals == other.vals && indices == other.index); }

    template <typename T, typename indexT, bool columnMajor>
    bool SparseMatrix<T, indexT, 1, columnMajor>::InnerIterator::operator!=(const InnerIterator& other) { return (vals != other.vals || indices != other.index); }

    template <typename T, typename indexT, bool columnMajor>
    bool SparseMatrix<T, indexT, 1, columnMajor>::InnerIterator::operator<(const InnerIterator& other) { return (vals < other.vals && indices < other.index); }

    template <typename T, typename indexT, bool columnMajor>
    bool SparseMatrix<T, indexT, 1, columnMajor>::InnerIterator::operator>(const InnerIterator& other) { return (vals > other.vals && indices > other.index); }

    template <typename T, typename indexT, bool columnMajor>
    T& SparseMatrix<T, indexT, 1, columnMajor>::InnerIterator::operator*() { return val; }

    // //* Getters & Setters *//

    template <typename T, typename indexT, bool columnMajor>
    indexT SparseMatrix<T, indexT, 1, columnMajor>::InnerIterator::getIndex() { return index; }

    template <typename T, typename indexT, bool columnMajor>
    indexT SparseMatrix<T, indexT, 1, columnMajor>::InnerIterator::outerDim() { return outer; }

    template <typename T, typename indexT, bool columnMajor>
    indexT SparseMatrix<T, indexT, 1, columnMajor>::InnerIterator::row() {
        if (columnMajor) {
            return index;
        }
        else {
            return outer;
        }
    }

    template <typename T, typename indexT, bool columnMajor>
    indexT SparseMatrix<T, indexT, 1, columnMajor>::InnerIterator::col() {
        if (columnMajor) {
            return outer;
        }
        else {
            return index;
        }
    }

    template <typename T, typename indexT, bool columnMajor>
    T SparseMatrix<T, indexT, 1, columnMajor>::InnerIterator::value() { return *val; }

}