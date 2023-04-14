#pragma once

namespace CSF
{

    template <typename T, typename indexT = uint64_t, uint8_t compressionLevel = 3, bool columnMajor = true>
    class SparseMatrix
    {
    private:
        //* Private Class Variables *//

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

        // Benchmarking Data //

        //! j Vector HERE

        //* Private Class Methods *//

        template <typename T2, typename indexT2>
        void compress(T2 *vals, indexT2 *innerIndices, indexT2 *outerPtr);

        uint8_t byteWidth(size_t size);

        uint32_t encodeVal();

        void checkVal();

        void userChecks();

    public:
        //* Nested Subclasses *//

        class Vector;

        class InnerIterator;

        //* Constructors & Destructor *//

        // default empty constructor
        SparseMatrix();

        // eigen sparse matrix constructor
        SparseMatrix(Eigen::SparseMatrix<T> &mat);

        // eigen sparse matrix constructor (row major)
        SparseMatrix(Eigen::SparseMatrix<T, Eigen::RowMajor> &mat);

        // deep copy constructor
        SparseMatrix(const CSF::SparseMatrix<T, indexT, compressionLevel, columnMajor> &mat);

        // RAW CSC constructor
        template <typename T2, typename indexT2>
        SparseMatrix(T2 *vals, indexT2 *innerIndices, indexT2 *outerPtr, uint32_t num_rows, uint32_t num_cols, uint32_t nnz);

        // file constructor
        SparseMatrix(const char *filename);

        // array of vectors constructor
        SparseMatrix(typename CSF::SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector vec[], size_t size);

        // map constructor (for transposing)
        SparseMatrix(std::map<indexT, std::unordered_map<T, std::vector<indexT>>> &map, uint32_t num_rows, uint32_t num_cols);

        // single vector constructor
        SparseMatrix(typename CSF::SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector &vec);

        // destructor
        ~SparseMatrix();

        //* Utility Methods *//

        void write(const char *filename);

        void print();

        //* Getters *//

        T coeff(uint32_t row, uint32_t col) const;

        void *getVecPointer(uint32_t vec) const;

        typename CSF::SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector getVector(uint32_t vec);

        size_t getVecSize(uint32_t vec) const;

        uint32_t innerSize() const;

        uint32_t outerSize() const;

        uint32_t rows() const;

        uint32_t cols() const;

        uint32_t nonZeros() const;

        size_t compressionSize() const;

        //* Conversion Methods *//

        CSF::SparseMatrix<T, indexT, 1, columnMajor> toCSF1();

        Eigen::SparseMatrix<T, columnMajor ? Eigen::ColMajor : Eigen::RowMajor> toEigen();

        CSF::SparseMatrix<T, indexT, compressionLevel, columnMajor> transpose();

        void append(typename SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector &vec);

        // method to slice a matrix and return an array of vectors
        typename CSF::SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector *slice(uint32_t start, uint32_t end);

        //* Operator Overloads *//

        bool operator==(const SparseMatrix<T, indexT, compressionLevel, columnMajor> &other);

        bool operator!=(const SparseMatrix<T, indexT, compressionLevel, columnMajor> &other);

        CSF::SparseMatrix<T, indexT, compressionLevel, columnMajor> operator*(T scalar) const;

        void operator*=(T scalar);

        CSF::SparseMatrix<T, indexT, compressionLevel, columnMajor>& operator=(const CSF::SparseMatrix<T, indexT, compressionLevel, columnMajor> &other);

        Eigen::VectorXd operator*(typename SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector &vec);

        Eigen::VectorXd operator*(Eigen::VectorXd& vec);

        Eigen::Matrix<T, -1,-1> operator*(Eigen::Matrix<T, -1,-1> mat);

        T operator()(uint32_t row, uint32_t col);

        typename CSF::SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector operator[](uint32_t vec);
        
        inline Eigen::Matrix<T, -1,-1> vectorMultiply(Eigen::VectorXd& vec);

        inline Eigen::Matrix<T,-1, 1> vectorMultiply(typename SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector& vec);

        inline Eigen::Matrix<T, -1,-1> matrixMultiply(Eigen::Matrix<T, -1,-1>& mat);

        inline Eigen::Matrix<T, -1,-1> matrixMultiply2(Eigen::Matrix<T, -1,-1>& mat);
    };

    template <typename T, typename indexT, bool columnMajor>
    class SparseMatrix<T, indexT, 1, columnMajor>
    {
    private:
        //* Private Class Variables *//

        const uint8_t delim = DELIM;

        uint32_t innerDim = 0;
        uint32_t outerDim = 0;
        uint32_t numRows = 0;
        uint32_t numCols = 0;
        uint32_t nnz = 0;

        uint32_t val_t;
        uint32_t index_t;

        size_t compSize = 0;

        T *vals = nullptr;
        indexT *innerIdx = nullptr;
        indexT *outerPtr = nullptr;

        uint32_t *metadata = nullptr;

        //* Private Class Methods *//

        uint8_t byteWidth(size_t size);

        uint32_t encodeVal();

        void checkVal();

        void userChecks();

    public:
        //* Nested Subclasses *//

        class Vector;

        class InnerIterator;

        //* Constructors & Destructor *//

        // default empty constructor
        SparseMatrix();

        // eigen sparse matrix constructor
        SparseMatrix(Eigen::SparseMatrix<T> &mat);

        // eigen sparse matrix constructor (row major)
        SparseMatrix(Eigen::SparseMatrix<T, Eigen::RowMajor> &mat);

        // deep copy constructor
        SparseMatrix(CSF::SparseMatrix<T, indexT, 1, columnMajor> &mat);

        // file constructor
        SparseMatrix(const char *filename);

        // COO constructor
        //! Decleration Here

        // destructor
        ~SparseMatrix();

        //* Utility Methods *//

        void write(const char *filename);

        void print();

        //* Getters *//

        T coeff(uint32_t row, uint32_t col);

        uint32_t innerSize();

        uint32_t outerSize();

        uint32_t rows();

        uint32_t cols();

        uint32_t nonZeros();

        size_t compressionSize();

        T *values();

        indexT *innerIdxPtr();

        indexT *outerPtrs();

        //* Conversion Methods *//

        Eigen::SparseMatrix<T> toEigen();

        CSF::SparseMatrix<T, indexT, 2, columnMajor> toCSF2();

        CSF::SparseMatrix<T, indexT, 3, columnMajor> toCSF3();

        CSF::SparseMatrix<T, indexT, 1, columnMajor> transpose();

        void append(typename SparseMatrix<T, indexT, 1, columnMajor>::Vector &vec);

        //* Operator Overloads *//

        bool operator==(const SparseMatrix<T, indexT, 1, columnMajor> &other);

        bool operator!=(const SparseMatrix<T, indexT, 1, columnMajor> &other);

        T operator()(uint32_t row, uint32_t col);
    };

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    class SparseMatrix<T, indexT, compressionLevel, columnMajor>::InnerIterator
    {
    private:
        //* Private Class Variables *//

        indexT outer;
        indexT index;
        T *val;

        indexT newIdx;

        uint8_t indexWidth = 1;

        void *data;
        void *endPtr;

        bool firstIndex = true;

        //* Private Class Methods *//

        void decodeIndex();

        void userChecks();

    public:
        //* Constructors & Destructor *//

        InnerIterator();

        InnerIterator(SparseMatrix<T, indexT, compressionLevel, columnMajor> &mat, uint32_t col);

        InnerIterator(SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector &vec);

        //* Operator Overloads *//

        void operator++(int);

        void operator++();

        bool operator==(const InnerIterator &other);

        bool operator!=(const InnerIterator &other);

        bool operator<(const InnerIterator &other);

        bool operator>(const InnerIterator &other);

        // operator bool() { return (char *)endPtr - indexWidth > data; };
        operator bool() { return (char*)endPtr - indexWidth  > data; };

        T &operator*();

        //* Getters *//

        indexT getIndex();

        indexT outerDim();

        indexT row();

        indexT col();

        T value();

        void coeff(T newValue);

        //* Utility Methods *//

        bool isNewRun();
    };

    template <typename T, typename indexT, bool columnMajor>
    class SparseMatrix<T, indexT, 1, columnMajor>::InnerIterator
    {
        private:

        //* Private Class Variables *//

        T *val;
        indexT index;
        indexT outer;

        //* Private Class Methods *//

        void userChecks();


        public:

        //* Constructors & Destructor *//

        InnerIterator();

        InnerIterator(SparseMatrix<T, indexT, 1, columnMajor> &mat, uint32_t col);

        InnerIterator(SparseMatrix<T, indexT, 1, columnMajor>::Vector &vec);

        //* Operator Overloads *//

        void operator++(int);

        void operator++();

        bool operator==(const InnerIterator &other);

        bool operator!=(const InnerIterator &other);

        bool operator<(const InnerIterator &other);

        bool operator>(const InnerIterator &other);

        T &operator*();

        //* Getters *//

        indexT getIndex();

        indexT outerDim();

        indexT row();

        indexT col();

        T value();

        //* Utility Methods *//
    };

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    class SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector
    {
    private:
        //* Private Class Variables *//

        size_t size;

        void *data;
        void *endPtr;

        uint32_t vecLength;

        uint8_t indexWidth = 1;

        uint32_t nnz = 0;

        //* Private Class Methods *//

        void userChecks();

    public:
        //* Constructors & Destructor *//

        // empty constructor
        Vector();

        // CSF matrix slice constructor
        Vector(CSF::SparseMatrix<T, indexT, compressionLevel, columnMajor> &mat, uint32_t vec);

        // deep copy constructor
        Vector(CSF::SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector &vec);

        // map encoding constructor (for testing and transpose)
        Vector(std::unordered_map<T, std::vector<indexT>> &map, uint32_t vecLength);

        // destructor
        ~Vector();

        //* Operator Overloads *//

        T operator[](uint32_t index);

        operator bool() { return (char *)endPtr - indexWidth > data; };

        typename SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector operator=(typename SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector &vec);

        //* Getters *//

        T coeff(uint32_t index);

        void *begin();

        void *end();

        size_t byteSize();

        uint32_t length();

        uint32_t outerSize();

        uint32_t nonZeros();

        //* Utility Methods *//

        void write(const char *filename);
    };

    template <typename T, typename indexT, bool columnMajor>
    class SparseMatrix<T, indexT, 1, columnMajor>::Vector
    {
        private:

        //* Private Class Variables *//

        size_t size = 0;

        T *vals = nullptr;
        indexT *indices = nullptr;

        uint32_t nnz = 0;
        uint32_t vecLength = 0;

        //* Private Class Methods *//

        void userChecks();

        public:

        //* Constructors & Destructor *//

        Vector();

        Vector(CSF::SparseMatrix<T, indexT, 1, columnMajor> &mat, uint32_t vec);

        Vector(CSF::SparseMatrix<T, indexT, 1, columnMajor>::Vector &vec);

        ~Vector();

        //* Operator Overloads *//

        T operator[](uint32_t index);

        //* Getters *//

        uint32_t length();

        uint32_t nonZeros();

        T *values();

        indexT *indexPtr();

        size_t byteSize();

        //* Utility Methods *//

        void write(const char *filename);
    };

}