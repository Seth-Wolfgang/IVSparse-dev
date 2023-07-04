/**
 * @file CSF2_Vector.hpp
 * @author Skyler Ruiter and Seth Wolfgang
 * @brief CSF2 Vector Class Declerations
 * @version 0.1
 * @date 2023-07-03
 */

#pragma once

namespace CSF {

    // vector of the SparseMatrixBase class
    template <typename T, typename indexT, bool columnMajor>
    class SparseMatrix<T, indexT, 2, columnMajor>::Vector {
        private:

        //* Private Class Variables *//

        size_t size = 0;

        T *values = nullptr;
        indexT *counts = nullptr;
        indexT *indices = nullptr;
        indexT valuesSize = 0;
        indexT indexSize = 0;

        uint32_t length = 0;

        uint8_t indexWidth = 1;

        uint32_t nnz = 0;

        //* Private Class Methods *//

        void userChecks();

        void calculateCompSize();

        public:

        //* Constructors & Destructor *//
        Vector() {};

        Vector(CSF::SparseMatrix<T, indexT, 2, columnMajor> &mat, uint32_t vec);

        Vector(CSF::SparseMatrix<T, indexT, 2, columnMajor>::Vector &vec);

        ~Vector();

        //* Operator Overloads *//

        T operator[](uint32_t index);

        //operator bool(  );

        typename SparseMatrix<T, indexT, 2, columnMajor>::Vector operator=(typename SparseMatrix<T, indexT, 2, columnMajor>::Vector &vec);

        // equality operator
        bool operator==(typename SparseMatrix<T, indexT, 2, columnMajor>::Vector &vec);

        bool operator!=(typename SparseMatrix<T, indexT, 2, columnMajor>::Vector &vec);

        //* Getters *//

        T coeff(uint32_t index);

        size_t byteSize();

        uint32_t innerSize();

        uint32_t outerSize();

        uint32_t nonZeros();

        uint32_t getLength();

        T *getValues();

        indexT *getCounts();

        indexT *getIndices();

        indexT uniqueVals();

        //* Utility Methods *//

        void print();

        void operator*=(T scalar);

        typename CSF::SparseMatrix<T, indexT, 2, columnMajor>::Vector operator*(T scalar);

        double norm();

        T sum();

        double dot(Eigen::Vector<T, -1>& other);

        double dot(Eigen::SparseVector<T, -1>& other);
    };
    
}