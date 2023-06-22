#pragma once

namespace CSF
{

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    class SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector
    {
    private:
        //* Private Class Variables *//

        size_t size;

        void *data;
        void *endPtr;

        uint32_t length = 0;

        uint8_t indexWidth = 1;

        uint32_t nnz = 0;

        bool performanceVectors = false;
        T *valueArray = nullptr;
        uint32_t *countsArray = nullptr;
        uint32_t valueArraySize = 0;

        //* Private Class Methods *//

        void userChecks();

        void activatePerformanceVecs();

        void undoPerformanceVecs();

    public:
        //* Constructors & Destructor *//
        Vector();

        Vector(CSF::SparseMatrix<T, indexT, compressionLevel, columnMajor> &mat, uint32_t vec);

        Vector(CSF::SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector &vec);

        Vector(std::unordered_map<T, std::vector<indexT>> &map, uint32_t vecSize);

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

        uint32_t innerSize();

        uint32_t outerSize();

        uint32_t nonZeros();

        uint32_t getLength();

        T *getValues();

        uint32_t *getCounts();

        uint32_t getValueArraySize();

        //* Utility Methods *//

        void write(const char *filename);

        void print();

        bool performanceVectorsInitialized();

        void setPerformanceVectors(bool on);

        void operator*=(T scalar);

        typename CSF::SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector operator*(T scalar);

        double norm();

        T sum();

        double dot(Eigen::Vector<T, -1>& other);

        double dot(Eigen::SparseVector<T, -1>& other);
    };

}