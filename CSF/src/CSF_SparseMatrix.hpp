#pragma once

#define DELIM 0

namespace CSF
{

    template <typename T, typename indexT = uint64_t, uint8_t compressionLevel = 3, bool columnMajor = true>
    class SparseMatrix
    {
    private:
        // Private Class Variables //

        const uint8_t delim = DELIM;

        uint32_t innerDim = 0;
        uint32_t outerDim = 0;
        uint32_t numRows = 0;
        uint32_t numCols = 0;
        uint32_t nnz = 0;

        uint32_t val_t;
        uint32_t index_t;

        size_t compSize = 0;

        // Class Data //

        void **data;
        void **endPointers;
        uint32_t *metadata;

        // Private Class Methods //

        template <typename T2, typename indexT2>
        void compress(T2 *vals, indexT2 *innerIndices, indexT2 *outerPtr);

        uint8_t byteWidth(size_t size);

        uint32_t encodeVal();

        void checkVal();

        void userChecks();

    public:
        // Nested Subclasses //

        class Vector;

        class InnerIterator;

        // Constructors & Destructor //

        SparseMatrix();

        SparseMatrix(Eigen::SparseMatrix<T> &mat);

        SparseMatrix(Eigen::SparseMatrix<T, Eigen::RowMajor> &mat);

        SparseMatrix(CSF::SparseMatrix<T, indexT, compressionLevel, columnMajor> &mat);

        SparseMatrix(const char *filename);

        SparseMatrix(typename CSF::SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector vec[], size_t size);

        SparseMatrix(std::map<indexT, std::unordered_map<T, std::vector<indexT>>> &map, uint32_t num_rows, uint32_t num_cols);

        ~SparseMatrix();

        // Utility Methods //

        void write(const char *filename);

        void print();

        // Getters //

        T coeff(uint32_t row, uint32_t col);

        void *getVecPointer(uint32_t vec);

        typename CSF::SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector getVector(uint32_t vec);

        size_t getVecSize(uint32_t vec);

        uint32_t innerSize();

        uint32_t outerSize();

        uint32_t rows();

        uint32_t cols();

        uint32_t nonZeros();

        size_t compressionSize();

        // Conversion Methods //

        CSF::SparseMatrix<T, indexT, 1, columnMajor> toCSF1();

        Eigen::SparseMatrix<T, columnMajor ? Eigen::ColMajor : Eigen::RowMajor> toEigen();

        CSF::SparseMatrix<T, indexT, compressionLevel, columnMajor> transpose();

        void append(typename SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector &vec);

        // Operator Overloads //

        bool operator==(const SparseMatrix<T, indexT, compressionLevel, columnMajor> &other);

        bool operator!=(const SparseMatrix<T, indexT, compressionLevel, columnMajor> &other);

        void operator*(T scalar);

        typename CSF::SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector operator*(typename SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector &vec);

        T operator()(uint32_t row, uint32_t col);
    };

    template <typename T, typename indexT, bool columnMajor>
    class SparseMatrix<T, indexT, 1, columnMajor>
    {
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
        class Vector;

        class InnerIterator;

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
    };

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    class SparseMatrix<T, indexT, compressionLevel, columnMajor>::InnerIterator
    {
    private:
        indexT outer;
        indexT index;
        T *val;

        indexT newIdx;

        uint8_t indexWidth = 1;

        void *data;
        void *endPtr;

        void decodeIndex();

        bool firstIndex = true;

    public:
        InnerIterator();

        InnerIterator(SparseMatrix<T, indexT, compressionLevel, columnMajor> &mat, uint32_t col);

        InnerIterator(SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector &vec);

        void operator++(int);

        void operator++();

        indexT getIndex();

        indexT outerDim();

        indexT row();

        indexT col();

        T value();

        bool operator==(const InnerIterator &other);

        bool operator!=(const InnerIterator &other);

        bool operator<(const InnerIterator &other);

        bool operator>(const InnerIterator &other);

        void coeff(T newValue);

        T &operator*();

        bool isNewRun();

        operator bool() { return (char *)endPtr - indexWidth > data; };
    };

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    class SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector
    {
        private:
        size_t size;

        void *data;

        void *endPtr;

        uint32_t vecLength;

        uint8_t indexWidth = 1;

        uint32_t nnz = 0;

        public:
        Vector();

        Vector(CSF::SparseMatrix<T, indexT, compressionLevel, columnMajor> &mat, uint32_t vec);

        Vector(CSF::SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector &vec);

        Vector(std::unordered_map<T, std::vector<indexT>> &map, uint32_t vecLength);

        ~Vector();

        T operator[](uint32_t index);

        T coeff(uint32_t index);

        void *begin();

        void *end();

        size_t byteSize();

        uint32_t length();

        uint32_t outerSize();

        uint32_t nonZeros();

        operator bool() { return (char *)endPtr - indexWidth > data; };
    };

}