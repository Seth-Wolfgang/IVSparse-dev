#pragma once

namespace CSF {

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    class SparseMatrix<T, indexT, compressionLevel, columnMajor>::InnerIterator {
    private:
        //* Private Class Variables *//

        indexT outer;
        indexT index;
        T* val;

        indexT newIndex;

        uint8_t indexWidth = 1;

        void* data;
        void* endPtr;

        bool firstIndex = true;

        T* valueArray = nullptr;
        uint32_t* countsArray = nullptr;
        uint32_t* valueArraySize = nullptr;
        uint32_t count = 1;

        //* Private Class Methods *//

        void __attribute__((hot)) decodeIndex();

    public:
        //* Constructors & Destructor *//

        InnerIterator();

        InnerIterator(SparseMatrix<T, indexT, compressionLevel, columnMajor>& mat, uint32_t col);

        InnerIterator(SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector& vec);

        //* Operator Overloads *//

        void __attribute__((hot)) operator++();

        bool operator==(const InnerIterator& other);

        bool operator!=(const InnerIterator& other);

        bool operator<(const InnerIterator& other);

        bool operator>(const InnerIterator& other);

        inline __attribute__((hot)) operator bool() { return (char*)endPtr - indexWidth > data; };

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