/**
 * @file CSF_Operators.hpp
 * @author Skyler Ruiter and Seth Wolfgang
 * @brief The operator overloads for the CSF Sparse Matrix Library.
 * @version 0.1
 * @date 2023-06-21
 */

#pragma once

namespace CSF {

    // Assignment Operator
    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    SparseMatrix<T, indexT, compressionLevel, columnMajor>& SparseMatrix<T, indexT, compressionLevel, columnMajor>::operator=(const CSF::SparseMatrix<T, indexT, compressionLevel, columnMajor>& other) {

        if (this != &other) {

            // free old data
            if (data != nullptr) {
                for (uint32_t i = 0; i < outerDim; i++) {
                    if (data[i] != nullptr)
                        free(data[i]);
                }
                free(data);
            }

            // Free the endpointers
            if (endPointers != nullptr)
                free(endPointers);

            // Free the metadata
            if (metadata != nullptr)
                delete[] metadata;

            // Free the performance vectors
            if (valueArray != nullptr) {
                for (uint32_t i = 0; i < outerDim; i++) {
                    if (valueArray[i] != nullptr) {
                        free(valueArray[i]);
                    }
                }
                free(valueArray);
            }

            if (countsArray != nullptr) {
                for (uint32_t i = 0; i < outerDim; i++) {
                    if (countsArray[i] != nullptr) {
                        free(countsArray[i]);
                    }
                }
                free(countsArray);
            }

            if (valueArraySize != nullptr) {
                free(valueArraySize);
            }

            // Deep copy the matrix

            // set the dimensions
            numRows = other.numRows;
            numCols = other.numCols;
            outerDim = other.outerDim;
            innerDim = other.innerDim;
            nnz = other.nnz;
            compSize = other.compSize;

            // allocate the memory
            try {
                data = (void**)malloc(outerDim * sizeof(void*));
                endPointers = (void**)malloc(outerDim * sizeof(void*));
                metadata = new uint32_t[NUM_META_DATA];
            }
            catch (std::bad_alloc& e) {
                std::cerr << "Error: Could not allocate memory for CSF matrix" << std::endl;
                exit(1);
            }

            // copy the metadata
            memcpy(metadata, other.metadata, sizeof(uint32_t) * NUM_META_DATA);

            // set the index and value types
            encodeValueType();
            index_t = other.index_t;

            // copy the data
            for (uint32_t i = 0; i < outerDim; i++) {
                try {
                    data[i] = malloc(other.getVectorSize(i) * 1.2);
                }
                catch (std::bad_alloc& e) {
                    std::cerr << "Error: Could not allocate memory for CSF matrix" << std::endl;
                    exit(1);
                }

                memcpy(data[i], other.data[i], other.getVectorSize(i));
                endPointers[i] = (uint8_t*)data[i] + other.getVectorSize(i);
            }

            // if other's performance vectors are on turn on this matrix's
            if (compressionLevel == 2) {

                // allocate the memory
                try {
                    valueArray = (T**)malloc(other.outerDim * sizeof(T*));
                    countsArray = (uint32_t**)malloc(other.outerDim * sizeof(uint32_t*));
                    valueArraySize = (uint32_t*)malloc(other.outerDim * sizeof(uint32_t));
                }
                catch (std::bad_alloc& e) {
                    std::cerr << "Error: Could not allocate memory for CSF matrix" << std::endl;
                    exit(1);
                }

                memcpy(valueArraySize, other.valueArraySize, sizeof(uint32_t) * outerDim);

                for (uint32_t i = 0; i < outerDim; i++) {
                    valueArray[i] = (T*)malloc(sizeof(T*) * other.valueArraySize[i]);
                    countsArray[i] = (uint32_t*)malloc(sizeof(uint32_t*) * other.valueArraySize[i]);
                }

                // copy the performance vectors
                for (uint32_t i = 0; i < outerDim; i++) {
                    memcpy(valueArray[i], other.valueArray[i], sizeof(T) * other.valueArraySize[i]);
                    memcpy(countsArray[i], other.countsArray[i], sizeof(uint32_t) * other.valueArraySize[i]);
                }
            }
        }
        return *this;
    }

    // Equality Operator
    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    bool SparseMatrix<T, indexT, compressionLevel, columnMajor>::operator==(const SparseMatrix<T, indexT, compressionLevel, columnMajor>& other) {
        // check if the two matrices are equal

        // first check the metadata using memcompare
        if (memcmp(metadata, other.metadata, sizeof(uint32_t) * NUM_META_DATA) != 0)
            return false;

        // iterate through the data and compare each element
        for (uint32_t i = 0; i < outerDim; i++) {
            if (memcmp(data[i], other.data[i], getVectorSize(i)) != 0)
                return false;
        }

        return true;
    }

    // Inequality Operator
    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    bool SparseMatrix<T, indexT, compressionLevel, columnMajor>::operator!=(const SparseMatrix<T, indexT, compressionLevel, columnMajor>& other) {
        return !(*this == other);
    }

    // Coefficent Access Operator
    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    T SparseMatrix<T, indexT, compressionLevel, columnMajor>::operator()(uint32_t row, uint32_t col) {
        // check if the row and column are in bounds
        if (row >= numRows || col >= numCols) {
            std::cerr << "Error: Index out of bounds" << std::endl;
            exit(1);
        }

        uint32_t vector = columnMajor ? col : row;
        uint32_t index = columnMajor ? row : col;

        // get an iterator for the desired vector
        for (typename SparseMatrix<T, indexT, compressionLevel, columnMajor>::InnerIterator it(*this, vector); it; ++it) {
            if (it.getIndex() == (indexT)index) {
                return it.value();
            }
        }

        // if the index is not found return 0
        return 0;
    }

    // Vector Access Operator
    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    typename SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector SparseMatrix<T, indexT, compressionLevel, columnMajor>::operator[](uint32_t vec) {

        #ifdef CSF_DEBUG
        // check if the vector is out of bounds
        assert((vec < outerDim && vec >= 0) && "Vector index out of bounds");
        #endif

        // return a CSF vector
        CSF::SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector newVector(*this, vec);

        return newVector;
    }

    //* BLAS Operators *//

    // Scalar Multiplication
    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    CSF::SparseMatrix<T, indexT, compressionLevel, columnMajor> SparseMatrix<T, indexT, compressionLevel, columnMajor>::operator*(T scalar) {
        return scalarMultiply(scalar);
    }

    // In place scalar multiplication
    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    void SparseMatrix<T, indexT, compressionLevel, columnMajor>::operator*=(T scalar) {
        return inPlaceScalarMultiply(scalar);
    }

    // CSF Matrix * CSF Vector Multiplication
    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    Eigen::VectorXd SparseMatrix<T, indexT, compressionLevel, columnMajor>::operator*(SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector& vec) {
        return vectorMultiply(vec);
    }

    // Matrix Vector Multiplication (CSF Eigen -> Eigen)
    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    Eigen::VectorXd SparseMatrix<T, indexT, compressionLevel, columnMajor>::operator*(Eigen::VectorXd& vec) {
        return vectorMultiply(vec);
    }

    // Matrix Matrix Multiplication (CSF Eigen -> Eigen)
    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    Eigen::Matrix<T, -1, -1> SparseMatrix<T, indexT, compressionLevel, columnMajor>::operator*(Eigen::Matrix<T, -1, -1> mat) {
        return matrixMultiply(mat);
    }

    // Outstream Operator
    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    std::ostream& operator<<(std::ostream& os, CSF::SparseMatrix<T, indexT, compressionLevel, columnMajor>& mat) {
        #ifndef CSF_DEBUG
        if (mat.cols() > 110) {
            std::cout << "CSF matrix is too large to print" << std::endl;
            return os;
        }
        #endif

        // create a matrix to store the full matrix representation of the CSF matrix
        T** matrix = new T * [mat.rows()];
        for (size_t i = 0; i < mat.rows(); i++) {
            matrix[i] = (T*)calloc(mat.cols(), sizeof(T));
        }

        // Build the full matrix representation of the the CSF matrix
        for (size_t i = 0; i < mat.cols(); i++) {
            for (typename CSF::SparseMatrix<T, indexT, compressionLevel, columnMajor>::InnerIterator it(mat, i); it; ++it) {
                // std::cout << "it.row(): " << it.row() << " col: " << it.col() << " value: " << it.value() << std::endl;
                matrix[it.row()][it.col()] = it.value();
            }
        }


        // std::cout << "rows: " << mat.rows() << std::endl;
        // std::cout << "cols: " << mat.cols() << std::endl;

        // store all of matrix into the output stream
        for (size_t i = 0; i < mat.rows(); i++) {
            for (size_t j = 0; j < mat.cols(); j++) {
                os << matrix[i][j] << " ";
            }
            os << std::endl;
        }

        for (int i = 0; i < mat.rows(); i++) {
            free(matrix[i]);
        }
        delete [] matrix;

        return os;
    }
}