/**
 * @file CSF_Vector.hpp
 * @author Skyler Ruiter and Seth Wolfgang
 * @brief The CSF Vector class declerations.
 * @version 0.1
 * @date 2023-06-23
 */

#pragma once

namespace CSF
{

    /**
     * 
    */
    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    class SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector
    {
        private:
        //* Private Class Variables *//

        size_t size = 0; // Size of the vector in bytes

        void *data = nullptr; // Pointer to the start of the vector
        void *endPtr = nullptr; // Pointer to the end of the vector

        uint32_t length = 0; // Length of the vector

        uint8_t indexWidth = 1; // Width of the index in bytes

        uint32_t nnz = 0; // Number of non-zero elements in the vector

        bool performanceVectors = false; // Whether or not to use performance vectors
        T *valueArray = nullptr; // Array of values
        uint32_t *countsArray = nullptr; // Array of counts of each value
        uint32_t valueArraySize = 0; // Size of the value array

        //* Private Class Methods *//

        // Does checks on the vectors metadata
        void userChecks();

        // Initializes the performance vectors
        void initPerformanceVectors();

        // Deletes the performance vectors
        void deletePerformanceVectors();

        public:

        //* Constructors & Destructor *//

        /**
         * Default Vector Constructor
        */
        Vector();

        /**
         * CSF Matrix Vector Constructor \n \n 
         * Constructs a vector from a CSF matrix row or column.
         * 
         * @note Can only get vectors in the same orientation as the matrix.
        */
        Vector(CSF::SparseMatrix<T, indexT, compressionLevel, columnMajor> &mat, uint32_t vec);

        /**
         * Copy Constructor \n \n
         * Constructs a vector from another vector.
        */
        Vector(CSF::SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector &vec);

        /**
         * Destructor
        */
        ~Vector();

        //* Getters *//

        /**
         * 
        */
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

        double norm();

        //* Operator Overloads *//

        void operator*=(T scalar);

        typename CSF::SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector operator*(T scalar);
        
        T operator[](uint32_t index);

        operator bool() { return (char *)endPtr - indexWidth > data; };

        typename SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector operator=(typename SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector &vec);
    };

}