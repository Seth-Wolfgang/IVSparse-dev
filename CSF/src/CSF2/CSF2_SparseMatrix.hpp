#pragma once

namespace CSF {

    template <typename T, typename indexT, bool columnMajor>
    class SparseMatrix<T, indexT, 2, columnMajor> : public SparseMatrixBase {

        private:

        //* The Matrix Data *//
        T **values = nullptr;       // The values of the matrix
        indexT **counts = nullptr;  // The counts of the matrix
        indexT **indices = nullptr; // The indices of the matrix

        indexT *valueSizes = nullptr;  // The sizes of the value arrays
        indexT *indexSizes = nullptr;  // The sizes of the index arrays

        // Compression Algorithm for going from CSC to CSF2 or CSF3
        template <typename T2, typename indexT2>
        void compressCSC(T2 *vals, indexT2 *innerIndices, indexT2 *outerPointers);

        void encodeValueType();

        void checkValueType();

        void userChecks();

        void calculateCompSize();

        // Private Helper Constructor for tranposing a CSF matrix
        SparseMatrix(std::unordered_map<T, std::vector<indexT>> maps[], uint32_t num_rows, uint32_t num_cols);

        // Scalar Multiplication
        inline CSF::SparseMatrix<T, indexT, 2, columnMajor> scalarMultiply(T scalar);

        // In Place Scalar Multiplication
        inline void inPlaceScalarMultiply(T scalar);

        // Matrix Vector Multiplication
        inline Eigen::VectorXd vectorMultiply(Eigen::VectorXd &vec);

        // Matrix Vector Multiplication 2 (with CSF Vector)
        inline Eigen::VectorXd vectorMultiply(typename SparseMatrix<T, indexT, 2, columnMajor>::Vector &vec);

        // Matrix Matrix Multiplication
        inline Eigen::Matrix<T, -1, -1> matrixMultiply(Eigen::Matrix<T, -1, -1> &mat);

        public:

        class Vector;

        class InnerIterator;

        SparseMatrix() {};

        SparseMatrix(Eigen::SparseMatrix<T> &mat);

        SparseMatrix(Eigen::SparseMatrix<T, Eigen::RowMajor> &mat);

        template <uint8_t compressionLevel2>
        SparseMatrix(CSF::SparseMatrix<T, indexT, compressionLevel2, columnMajor> &other);

        SparseMatrix(const CSF::SparseMatrix<T, indexT, 2, columnMajor> &other);

        template <typename T2, typename indexT2>
        SparseMatrix(T2 *vals, indexT2 *innerIndices, indexT2 *outerPtr, uint32_t num_rows, uint32_t num_cols, uint32_t nnz);

        SparseMatrix(typename CSF::SparseMatrix<T, indexT, 2, columnMajor>::Vector &vec);

        SparseMatrix(std::vector<typename CSF::SparseMatrix<T, indexT, 2, columnMajor>::Vector> &vecs);

        SparseMatrix(const char *filename);

        ~SparseMatrix();

        T coeff(uint32_t row, uint32_t col);

        bool isColumnMajor() const;

        T *getValues(uint32_t vec) const;

        indexT *getCounts(uint32_t vec) const;

        indexT *getIndices(uint32_t vec) const;

        indexT getNumUniqueVals(uint32_t vec) const;

        indexT getNumIndices(uint32_t vec) const;

        typename CSF::SparseMatrix<T, indexT, 2, columnMajor>::Vector getVector(uint32_t vec);

        inline std::vector<T> outerSum();

        inline std::vector<T> innerSum();

        inline std::vector<T> maxColCoeff();

        inline std::vector<T> maxRowCoeff();

        inline std::vector<T> minColCoeff();

        inline std::vector<T> minRowCoeff();

        inline T trace();

        inline T sum();

        inline double norm();

        inline double vectorLength(uint32_t vec);

        void write(const char *filename);

        void print();

        CSF::SparseMatrix<T, indexT, 1, columnMajor> toCSF1();

        CSF::SparseMatrix<T, indexT, 3, columnMajor> toCSF3();

        Eigen::SparseMatrix<T, columnMajor ? Eigen::ColMajor : Eigen::RowMajor> toEigen();

        CSF::SparseMatrix<T, indexT, 2, columnMajor> transpose();

        void inPlaceTranspose();

        void append(typename SparseMatrix<T, indexT, 2, columnMajor>::Vector &vec);

        std::vector<typename CSF::SparseMatrix<T, indexT, 2, columnMajor>::Vector> slice(uint32_t start, uint32_t end);

        CSF::SparseMatrix<T, indexT, 2, columnMajor> &operator=(const CSF::SparseMatrix<T, indexT, 2, columnMajor> &other);

        bool operator==(const SparseMatrix<T, indexT, 2, columnMajor> &other);

        bool operator!=(const SparseMatrix<T, indexT, 2, columnMajor> &other);

        T operator()(uint32_t row, uint32_t col);

        typename CSF::SparseMatrix<T, indexT, 2, columnMajor>::Vector operator[](uint32_t vec);

        CSF::SparseMatrix<T, indexT, 2, columnMajor> operator*(T scalar);

        void operator*=(T scalar);

        Eigen::VectorXd operator*(Eigen::VectorXd &vec);

        Eigen::VectorXd operator*(typename SparseMatrix<T, indexT, 2, columnMajor>::Vector &vec);

        Eigen::Matrix<T, -1, -1> operator*(Eigen::Matrix<T, -1, -1> mat);
    };

}