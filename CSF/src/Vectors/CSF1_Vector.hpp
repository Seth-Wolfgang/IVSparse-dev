/**
 * @file CSF1_Vector.hpp
 * @author Skyler Ruiter and Seth Wolfgang
 * @brief CSF1 Vector Class Declerations
 * @version 0.1
 * @date 2023-07-03
 */

#pragma once

namespace CSF {

    template <typename T, typename indexT, bool columnMajor>
    class SparseMatrix<T, indexT, 1, columnMajor>::Vector {

        private:

        //* Private Class Variables *//


        size_t size = 0;

        T *vals = nullptr;
        indexT *innerIdx = nullptr;

        uint32_t length = 0;
        uint32_t nnz = 0;

        //* Private Class Methods *//

        void userChecks();

        void calculateCompSize();

        public:

        //* Constructors & Destructor *//
        Vector() {};

        Vector(CSF::SparseMatrix<T, indexT, 1, columnMajor> &mat, uint32_t vec);

        Vector(CSF::SparseMatrix<T, indexT, 1, columnMajor>::Vector &vec);

        ~Vector();

        //* Operator Overloads *//

        T operator[](uint32_t index);

        typename SparseMatrix<T, indexT, 1, columnMajor>::Vector operator=(typename SparseMatrix<T, indexT, 1, columnMajor>::Vector &vec);

        // equality operator
        bool operator==(typename SparseMatrix<T, indexT, 1, columnMajor>::Vector &vec);

        bool operator!=(typename SparseMatrix<T, indexT, 1, columnMajor>::Vector &vec);

        //* Getters *//

        T coeff(uint32_t index);

        size_t byteSize();

        uint32_t innerSize();

        uint32_t outerSize();

        uint32_t nonZeros();

        uint32_t getLength();

        T *getValues() const;

        indexT *getInnerIndices() const;

        //* Utility Methods *//

        void print();
    };
    
}