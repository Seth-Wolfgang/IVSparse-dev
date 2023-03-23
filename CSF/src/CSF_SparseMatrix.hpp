#pragma once

#define DELIM 0

namespace CSF {

    template <typename T, typename indexT=uint64_t, uint8_t compressionLevel=3, bool columnMajor=true>
    class SparseMatrix {
        private:

        const uint8_t delim = DELIM;

        uint32_t innerDim = 0; // rows
        uint32_t outerDim = 0; // cols
        uint32_t nnz = 0;

        uint32_t val_t;
        uint32_t index_t;

        size_t compSize = 0;

        void **data;
        void **endPointers;
        uint32_t *metadata;

        template <typename T2, typename indexT2>
        void compress(T2 *vals, indexT2 *rowIdx, indexT2 *colPtr);

        uint8_t byteWidth(size_t size);

        uint32_t encodeVal();

        void checkVal();

        void userChecks();

        public:

        SparseMatrix();

        SparseMatrix(Eigen::SparseMatrix<T> &mat);

        SparseMatrix(Eigen::SparseMatrix<T, Eigen::RowMajor> &mat);

        SparseMatrix(const char *filename);

        ~SparseMatrix();

        void write(const char *filename);

        void print();

        T operator()(uint32_t row, uint32_t col);

        T coeff(uint32_t row, uint32_t col);

        void *getVecPointer(uint32_t vec);

        size_t getVecSize(uint32_t vec);

        uint32_t innerSize();

        uint32_t outerSize();

        uint32_t nonZeros();

        size_t compressionSize();

        bool operator==(const SparseMatrix<T, indexT, compressionLevel, columnMajor> &other);

        bool operator!=(const SparseMatrix<T, indexT, compressionLevel, columnMajor> &other);

        CSF::SparseMatrix<T, indexT, 1, columnMajor> toCSF1();

        Eigen::SparseMatrix<T> toEigen();

        CSF::SparseMatrix<T, indexT, compressionLevel, !columnMajor> transpose();

        class Vector;

        class InnerIterator;
    };


    template <typename T, typename indexT, bool columnMajor>
    class SparseMatrix<T, indexT, 1, columnMajor> {
        private:

        const uint8_t delim = DELIM;

        uint32_t innerDim = 0;
        uint32_t outerDim = 0;
        uint32_t nnz = 0;

        uint32_t val_t;
        uint32_t index_t;

        size_t compSize;

        T *vals;
        indexT *innerIdx;
        indexT *outerPtr;

        uint8_t byteWidth(size_t size);

        uint32_t encodeVal();

        void checkVal();

        void userChecks();

        public:

        SparseMatrix();

        SparseMatrix(Eigen::SparseMatrix<T> &mat);

        SparseMatrix(Eigen::SparseMatrix<T, Eigen::RowMajor> &mat);

        SparseMatrix(const char *filename);

        ~SparseMatrix();

        void write(const char *filename);

        void print();

        T operator()(uint32_t row, uint32_t col);

        T coeff(uint32_t row, uint32_t col);

        uint32_t innerSize();

        uint32_t outerSize();

        uint32_t nonZeros();

        size_t compressionSize();

        bool operator==(const SparseMatrix<T, indexT, 1, columnMajor> &other);

        bool operator!=(const SparseMatrix<T, indexT, 1, columnMajor> &other);

        Eigen::SparseMatrix<T> toEigen();

        class Vector;

        class InnerIterator;
    };


    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    class SparseMatrix<T, indexT, compressionLevel, columnMajor>::InnerIterator {
        private:

        indexT outer;
        indexT index;
        T* val;

        indexT newIdx;

        uint8_t indexWidth = 1;

        void *data;
        void *endPtr;

        void decodeIndex();

        public:

        InnerIterator();

        InnerIterator(SparseMatrix<T, indexT, compressionLevel, columnMajor> &mat, uint32_t col);

        InnerIterator(SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector &vec);

        void operator++(int);

        void operator++();

        indexT getIndex();

        indexT outerDim();

        T value();

        bool operator==(const InnerIterator &other);

        bool operator!=(const InnerIterator &other);

        bool operator<(const InnerIterator &other);

        bool operator>(const InnerIterator &other);

        T& operator*();

        operator bool() { return (char*)endPtr - indexWidth > data; };

    };

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    class SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector {
        private:

        size_t size;
        void *data;
        void *endPtr;

        public:

        Vector();

        Vector(CSF::SparseMatrix<T, indexT, compressionLevel, columnMajor> &mat, uint32_t vec);

        T operator[](uint32_t index);

        void *begin();

        void *end();

        size_t byteSize();
        
    };

}