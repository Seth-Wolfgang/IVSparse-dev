/**
 * @file CSF1_Iterator.hpp
 * @author Skyler Ruiter and Seth Wolfgang
 * @brief Inner Iterator for CSF1 Declerations
 * @version 0.1
 * @date 2023-07-03
 */

#pragma once

namespace CSF {

    /**
     * CSF1 Inner Iterator Class \n \n
     * 
     */
    template <typename T, typename indexT, bool columnMajor>
    class SparseMatrix<T, indexT, 1, columnMajor>::InnerIterator {
        
        private:
        
        //* Private Class Variables *//

        T *val;
        indexT index;
        indexT outer;

        T *vals;
        indexT *indices;
        T *endPtr;

    
        public:
        
        //* Constructors & Destructor *//

        InnerIterator();

        InnerIterator(SparseMatrix<T, indexT, 1, columnMajor> &mat, uint32_t vec);

        InnerIterator(SparseMatrix<T, indexT, 1, columnMajor>::Vector &vec);

        //* Operator Overloads *//

        void __attribute__((hot)) operator++();

        bool operator==(const InnerIterator &other);

        bool operator!=(const InnerIterator &other);

        bool operator<(const InnerIterator &other);

        bool operator>(const InnerIterator &other);

        T &operator*();

        inline __attribute__((hot)) operator bool() { return indices < endPtr; };

        //* Getters *//

        indexT getIndex();

        indexT outerDim();

        indexT row();

        indexT col();

        T value();

    }; // class InnerIterator

} // namespace CSF