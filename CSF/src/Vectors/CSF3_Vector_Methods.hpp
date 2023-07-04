/**
 * @file CSF3_Vector_Methods.hpp
 * @author Skyler Ruiter and Seth Wolfgang
 * @brief CSF3 Vector Methods
 * @version 0.1
 * @date 2023-07-03
 */

#pragma once

namespace CSF {

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector::Vector(uint32_t length) {

        // set the length
        this->length = length;

    }

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector::Vector(CSF::SparseMatrix<T, indexT, compressionLevel, columnMajor>& mat, uint32_t vec) {

        #ifdef CSF_DEBUG
        // make sure the vector is in bounds
        assert((vec >= 0 && vec < mat.outerSize()) && "Vector index out of bounds");

        // make sure the matrix is not empty
        assert((mat.outerSize() > 0 && mat.innerSize() > 0) && "Matrix is empty");
        #endif

        // get the length of the vector
        size = mat.getVectorSize(vec);
        length = mat.innerSize();

        // if the size is 0 then the vector is empty
        if (size == 0) {
            data = nullptr;
            endPtr = nullptr;
            return;
        }

        // set data pointer
        try {
            data = malloc(size);
        }
        catch (std::bad_alloc& e) {
            std::cerr << e.what() << '\n';
        }

        // copy the vector data into the vector
        memcpy(data, mat.vectorPointer(vec), size);

        // set the end pointer
        endPtr = (uint8_t*)data + size;

        // set the nnz
        if (nnz == 0 && size > 0) {
            // make an iterator for the vector
            CSF::SparseMatrix<T, indexT, compressionLevel, columnMajor>::InnerIterator it(*this);

            // iterate through the vector until the index is found
            while (it) {
                nnz++;
                ++it;
            }
        }

    }

    // Deep copy constructor
    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector::Vector(CSF::SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector& vec) {
        // set the size
        size = vec.size;

        // set the length
        length = vec.length;

        // if the size is 0 then the vector is empty
        if (size == 0) {
            data = nullptr;
            endPtr = nullptr;
            return;
        }

        // set data pointer
        try {
            data = malloc(size);
        }
        catch (std::bad_alloc& e) {
            std::cerr << e.what() << '\n';
        }

        // copy the vector data into the vector
        memcpy(data, vec.data, size);

        // set the end pointer
        endPtr = (uint8_t*)data + size;

        // set the nnz
        nnz = vec.nonZeros();

        #ifdef CSF_DEBUG
        userChecks();
        #endif
    }

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector::~Vector() { if (data != nullptr) { free(data); } }

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    void SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector::userChecks() {
        assert(std::is_floating_point<indexT>::value == false && "The index type must be a non-floating point type");

        assert((compressionLevel == 1 || compressionLevel == 2 || compressionLevel == 3) && "The compression level must be either 1, 2, or 3");

        assert((std::is_arithmetic<T>::value && std::is_arithmetic<indexT>::value) && "The value and index types must be numeric types");

        assert((std::is_same<indexT, bool>::value == false) && "The index type must not be bool");
    }

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    uint32_t SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector::innerSize() { return length; }

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    uint32_t SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector::outerSize() { return 1; }

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    uint32_t SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector::nonZeros() { return nnz; }

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    void* SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector::begin() { return data; }

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    void* SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector::end() { return endPtr; }

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    size_t SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector::byteSize() { return size; }

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    T SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector::coeff(uint32_t index) { return (*this)[index]; }

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    uint32_t SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector::getLength() { return length; }

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    typename SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector::operator=(typename SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector& other) {
        // check if the vector is the same
        if (this == &other) {
            return *this;
        }

        // free the data if it is not null
        if (data != nullptr) {
            free(data);
        }

        // if the other vector is empty then return
        if (other.data == nullptr) {
            data = nullptr;
            endPtr = nullptr;
            size = 0;
            length = other.length;
            nnz = 0;
            return *this;
        }

        // copy the data
        data = (uint8_t*)malloc(other.size);
        memcpy(data, other.data, other.size);

        // set the size
        size = other.size;

        // set the length
        length = other.length;

        // set the nnz
        nnz = other.nnz;

        // set the end pointer
        endPtr = (uint8_t*)data + size;

        // return this
        return *this;
    }

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    T SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector::operator[](uint32_t index) {

        #ifdef CSF_DEBUG
        // check if the index is out of bounds
        assert(index < length && "The index is out of bounds");
        #endif

        // make an iterator for the vector
        CSF::SparseMatrix<T, indexT, compressionLevel, columnMajor>::InnerIterator it(*this);

        // iterate through the vector until the index is found
        while (it) {
            if (it.getIndex() == (indexT)index) {
                return it.value();
            }
            ++it;
        }

        // if the index is not found then return 0
        return 0;
    }

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    void SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector::print() {

        // if length is larger than 100 then print then don't print
        if (length > 100) {
            std::cout << "Vector is too large to print" << std::endl;
            return;
        }

        std::cout << "Vector: ";
        std::cout << std::endl;

        // print a dense vector
        for (uint32_t i = 0; i < length; i++) {
            std::cout << (*this)[i] << " ";
        }

        std::cout << std::endl;
    }

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    inline double SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector::norm() {
        double norm = 0;
        for (typename SparseMatrix<T, indexT, compressionLevel, columnMajor>::InnerIterator it(*this); it; ++it) {
            norm += it.value() * it.value();
        }
        return sqrt(norm);
    }

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    inline T SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector::sum() {
        double sum = 0;
        for (typename SparseMatrix<T, indexT, compressionLevel, columnMajor>::InnerIterator it(*this); it; ++it) {
            sum += it.value();
        }
        return sum;
    }

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    void SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector::operator*=(T scalar) {
        for (typename SparseMatrix<T, indexT, compressionLevel, columnMajor>::InnerIterator it(*this); it; ++it) {
            if (it.isNewRun()) {
                it.coeff(it.value() * scalar);
            }
        }
    }

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    typename CSF::SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector::operator*(T scalar) {
        typename CSF::SparseMatrix<T, indexT, 2, columnMajor>::Vector newVector(*this);

        for (typename SparseMatrix<T, indexT, compressionLevel, columnMajor>::InnerIterator it(newVector); it; ++it) {
            if (it.isNewRun()) {
                it.coeff(it.value() * scalar);
            }
        }
        return newVector;
    }

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    double SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector::dot(Eigen::Vector<T, -1>& other) {
        double dot = 0;

        for (typename SparseMatrix<T, indexT, compressionLevel, columnMajor>::InnerIterator it(*this); it; ++it) {
            dot += it.value() * other.coeff(it.row());
        }

        return dot;
    }

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    double SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector::dot(Eigen::SparseVector<T, -1>& other) {
        double dot = 0;

        for (typename SparseMatrix<T, indexT, compressionLevel, columnMajor>::InnerIterator it(*this); it; ++it) {
            dot += it.value() * other.coeff(it.row());
        }
        return dot;
    }
}