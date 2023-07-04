#pragma once

namespace CSF {

    template <typename T, typename indexT, bool columnMajor>
    class SparseMatrix<T, indexT, 2, columnMajor>::InnerIterator {
        private:
        //* Private Class Variables *//

        indexT outer = 0;
        indexT index = 0;
        indexT newIndex = 0;
        T* val = nullptr;

        bool firstIndex = true;

        uint8_t indexWidth = sizeof(indexT);

        T* vals = nullptr;
        indexT* counts = nullptr;
        indexT* indices = nullptr;

        indexT valsSize = 0;
        indexT indexSize = 0;

        indexT count = 0;
        indexT countIndex = 0;

        //* Private Class Methods *//

        public:
        //* Constructors & Destructor *//

        InnerIterator();

        InnerIterator(SparseMatrix<T, indexT, 2, columnMajor>& mat, uint32_t col);

        InnerIterator(SparseMatrix<T, indexT, 2, columnMajor>::Vector& vec);

        //* Operator Overloads *//

        void __attribute__((hot)) operator++();

        bool operator==(const InnerIterator& other);

        bool operator!=(const InnerIterator& other);

        bool operator<(const InnerIterator& other);

        bool operator>(const InnerIterator& other);

        inline __attribute__((hot)) operator bool() {
            return countIndex < indexSize;
        }


        T& operator*();

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
    
}