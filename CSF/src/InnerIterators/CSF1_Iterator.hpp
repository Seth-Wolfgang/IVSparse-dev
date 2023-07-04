#pragma once

namespace CSF {

    template <typename T, typename indexT, bool columnMajor>
    class SparseMatrix<T, indexT, 1, columnMajor>::InnerIterator
    {
    private:
        //* Private Class Variables *//

        T *val;
        indexT index;
        indexT outer;

        T *vals;
        indexT *indices;
        indexT *endPtr;

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
    };
}