#pragma once

namespace CSF {

    //* BLAS Level 1 Routines *//

    // Scalar Multiplication
    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    inline CSF::SparseMatrix<T, indexT, compressionLevel, columnMajor> SparseMatrix<T, indexT, compressionLevel, columnMajor>::scalarMultiply(T scalar) {
        
        // Deep copy the matrix
        CSF::SparseMatrix<T, indexT, compressionLevel, columnMajor> newMatrix(*this);

        // If performance vectors are active use them for the scalar multiplication
        if constexpr (compressionLevel == 2) {
            if (performanceVectors) {
                #pragma omp parallel for schedule(dynamic)
                for (int i = 0; i < outerDim; i++) {
                    for (int j = 0; j < valueArraySize[i]; j++) {
                        newMatrix.valueArray[i][j] *= scalar;
                    }
                }
                return newMatrix;
            }
        }

        // else use the iterator
        #pragma omp parallel for schedule(dynamic)
        for (uint32_t i = 0; i < this->outerDim; ++i) {
            for (typename SparseMatrix<T, indexT, compressionLevel>::InnerIterator it(newMatrix, i); it; ++it) {
                if (it.isNewRun()) {
                    it.coeff(it.value() * scalar);
                }
            }
        }
        return newMatrix;
    }

    // In place Scalar Multiplication
    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    inline void SparseMatrix<T, indexT, compressionLevel, columnMajor>::inPlaceScalarMultiply(T scalar) {
        
        // if performance vectors are active use them for the scalar multiplication
        if constexpr (compressionLevel == 2) {
            if (performanceVectors) {
            #pragma omp parallel for schedule(dynamic)
                for (int i = 0; i < outerDim; i++) {
                    for (int j = 0; j < valueArraySize[i]; j++) {
                        valueArray[i][j] *= scalar;
                    }
                }
            }
            return;
        }

        // else use the iterator
        #pragma omp parallel for schedule(dynamic)
        for (uint32_t i = 0; i < outerDim; ++i) {
            for (typename SparseMatrix<T, indexT, compressionLevel>::InnerIterator it(*this, i); it; ++it) {
                if (it.isNewRun()) {
                    it.coeff(it.value() * scalar);
                }
            }
        }
    }


    //* BLAS Level 2 Routines *//

    // Matrix Vector Multiplication (Eigen Vector)
    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    inline Eigen::Matrix<T, -1, -1> SparseMatrix<T, indexT, compressionLevel, columnMajor>::vectorMultiply(Eigen::VectorXi& vec) {
        // check that the vector is the correct size
        #ifdef CSF_DEBUG
        assert(vec.rows() == outerDim && "The vector must be the same size as the number of columns in the matrix!");
        #endif

        Eigen::Matrix<T, -1, 1> eigenTemp(innerDim, 1);
        eigenTemp.setZero();

        // iterate over the vector and multiply the corresponding row of the matrix by the vecIter value
        for (int i = 0; i < vec.rows(); ++i) {
            if (vec(i) == 0) continue;
            for (typename SparseMatrix<T, indexT, compressionLevel>::InnerIterator matIter(*this, i); matIter; ++matIter) {
                eigenTemp.coeffRef(matIter.row()) += matIter.value() * vec(i);
            }
        }
        return eigenTemp;
    }

    // Matrix Vector Multiplication (CSF Vector)
    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    inline Eigen::Matrix<T, -1, 1> SparseMatrix<T, indexT, compressionLevel, columnMajor>::vectorMultiply(typename SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector& vec) {
        // check that the vector is the correct size
        #ifdef CSF_DEBUG
        if (vec.length() != outerDim)
            throw std::invalid_argument("The vector must be the same size as the number of columns in the matrix!");
        #endif

        Eigen::Matrix<T, -1, 1> newVector = Eigen::Matrix<T, -1, 1>::Zero(innerDim, 1);

        // iterate over the vector and multiply the corresponding row of the matrix by the vecIter value
        for (typename SparseMatrix<T, indexT, compressionLevel>::InnerIterator vecIter(vec); vecIter; ++vecIter) {
            for (typename SparseMatrix<T, indexT, compressionLevel>::InnerIterator matIter(*this, vecIter.row()); matIter; ++matIter) {
                newVector.coeffRef(matIter.row()) += matIter.value() * vecIter.value();
            }
        }
        return newVector;
    }


    //* BLAS Level 3 Routines *//

    // Matrix Matrix Multiplication (Eigen Matrix)
    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    inline Eigen::Matrix<T, -1, -1> SparseMatrix<T, indexT, compressionLevel, columnMajor>::matrixMultiply(Eigen::Matrix<T, -1, -1>& mat) {
        // check that the matrix is the correct size
        #ifdef CSF_DEBUG
        if (mat.rows() != outerDim)
            throw std::invalid_argument("The matrix must be the same size as the number of columns in the matrix!");
        #endif

        Eigen::Matrix<T, -1, -1> newMatrix = Eigen::Matrix<T, -1, -1>::Zero(innerDim, mat.cols());

        // #pragma omp parallel for num_threads(8)
        for (int col = 0; col < mat.cols(); col++) {
            for (int row = 0; row < mat.rows(); row++) {
                for (typename SparseMatrix<T, indexT, compressionLevel>::InnerIterator matIter(*this, row); matIter; ++matIter) {
                    newMatrix.coeffRef(matIter.row(), col) += matIter.value() * mat(row, col);
                }
            }
        }
        return newMatrix;
    }

    //* Other Matrix Calculations *//

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    inline std::vector<T> SparseMatrix<T, indexT, compressionLevel, columnMajor>::outerSum() {
        std::vector<T> outerSum = std::vector<T>(outerDim);

        if constexpr (compressionLevel == 2) {
            if (performanceVectors) {

                #pragma omp parallel for schedule(dynamic)
                for (int i = 0; i < outerDim; i++) {
                    for (int j = 0; j < valueArraySize[i]; j++) {
                        outerSum[i] += valueArray[i][j] * countsArray[i][j];
                    }
                }
                return outerSum;
            }
        }

        for (int i = 0; i < outerDim; i++) {
            for (typename SparseMatrix<T, indexT, compressionLevel>::InnerIterator it(*this, i); it; ++it) {
                outerSum[i] += it.value();
            }
        }
        return outerSum;
    }

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    inline std::vector<T> SparseMatrix<T, indexT, compressionLevel, columnMajor>::innerSum() {
        std::vector<T> innerSum = std::vector<T>(innerDim);

        for (int i = 0; i < outerDim; i++) {
            for (typename SparseMatrix<T, indexT, compressionLevel>::InnerIterator it(*this, i); it; ++it) {
                innerSum[it.row()] += it.value();
            }
        }
        return innerSum;
    }

    //! Make aware of storage order?
    template<typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    inline std::vector<T> SparseMatrix<T, indexT, compressionLevel, columnMajor>::maxColCoeff() {
        std::vector<T> maxCoeff = std::vector<T>(innerDim);

        if constexpr (compressionLevel == 2) {
            if (performanceVectors) {
                #pragma omp parallel for schedule(dynamic)
                for (int i = 0; i < outerDim; i++) {
                    for (int j = 0; j < valueArraySize[i]; j++) {
                        if (valueArray[i][j] > maxCoeff[i]) {
                            maxCoeff[i] = valueArray[i][j];
                        }
                    }
                }
                return maxCoeff;
            }
        }

        for (int i = 0; i < outerDim; i++) {
            for (typename SparseMatrix<T, indexT, compressionLevel>::InnerIterator it(*this, i); it; ++it) {
                if (it.value() > maxCoeff[i]) {
                    maxCoeff[i] = it.value();
                }
            }
        }
        return maxCoeff;
    }


    template<typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    inline std::vector<T>  SparseMatrix<T, indexT, compressionLevel, columnMajor>::maxRowCoeff() {
        std::vector<T> maxCoeff = std::vector<T>(innerDim);

        for (int i = 0; i < outerDim; i++) {
            for (typename SparseMatrix<T, indexT, compressionLevel>::InnerIterator it(*this, i); it; ++it) {
                if (it.value() > maxCoeff[it.row()]) {
                    maxCoeff[it.row()] = it.value();
                }
            }
        }
        return maxCoeff;
    }


    template<typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    inline std::vector<T> SparseMatrix<T, indexT, compressionLevel, columnMajor>::minColCoeff() {
        std::vector<T> minCoeff = std::vector<T>(innerDim);

        if constexpr (compressionLevel == 2) {
            if (performanceVectors) {
                #pragma omp parallel for schedule(dynamic)
                for (int i = 0; i < outerDim; i++) {
                    for (int j = 0; j < valueArraySize[i]; j++) {
                        if (valueArray[i][j] < minCoeff[i]) {
                            minCoeff[i] = valueArray[i][j];
                        }
                    }
                }
                return minCoeff;
            }
        }

        for (int i = 0; i < outerDim; i++) {
            for (typename SparseMatrix<T, indexT, compressionLevel>::InnerIterator it(*this, i); it; ++it) {
                if (it.value() < minCoeff[i]) {
                    minCoeff[i] = it.value();
                }
            }
        }
        return minCoeff;
    }


    template<typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    inline std::vector<T> SparseMatrix<T, indexT, compressionLevel, columnMajor>::minRowCoeff() {
        std::vector<T> minCoeff = std::vector<T>(innerDim);
        memset(minCoeff.data(), 0xF, innerDim * sizeof(T));

        for (int i = 0; i < outerDim; i++) {
            for (typename SparseMatrix<T, indexT, compressionLevel>::InnerIterator it(*this, i); it; ++it) {
                if (it.value() < minCoeff[it.row()]) {
                    minCoeff[it.row()] = it.value();
                }
            }
        }
        return minCoeff;
    }


    template<typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    inline T SparseMatrix<T, indexT, compressionLevel, columnMajor>::trace() {
        assert(innerDim == outerDim && "Trace is only defined for square matrices!");

        T trace = 0;
        for (int i = 0; i < outerDim; i++) {
            for (typename SparseMatrix<T, indexT, compressionLevel>::InnerIterator it(*this, i); it; ++it) {
                if (it.row() == i) {

                    trace += it.value();
                }
                else if (it.row() > i) {
                    continue;
                }
            }
        }
        return trace;
    }

    template<typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    inline T SparseMatrix<T, indexT, compressionLevel, columnMajor>::sum() {
        T sum = 0;

        if constexpr (compressionLevel == 2) {
            if (performanceVectors) {
                #pragma omp parallel for schedule(dynamic)
                for (int i = 0; i < outerDim; i++) {
                    for (int j = 0; j < valueArraySize[i]; j++) {
                        sum += valueArray[i][j] * countsArray[i][j];
                    }
                }
                return sum;
            }
        }

        for (int i = 0; i < outerDim; i++) {
            for (typename SparseMatrix<T, indexT, compressionLevel>::InnerIterator it(*this, i); it; ++it) {
                sum += it.value();
            }
        }
        return sum;
    }

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    inline double SparseMatrix<T, indexT, compressionLevel, columnMajor>::norm() {
        double norm = 0;

        if constexpr (compressionLevel == 2) {
            if (performanceVectors) {
                #pragma omp parallel for schedule(dynamic)
                for (int i = 0; i < outerDim; i++) {
                    for (int j = 0; j < valueArraySize[i]; j++) {
                        norm += valueArray[i][j] * valueArray[i][j] * countsArray[i][j];
                    }
                }
                return sqrt(norm);
            }
        }

        for (int i = 0; i < outerDim; i++) {
            for (typename SparseMatrix<T, indexT, compressionLevel>::InnerIterator it(*this, i); it; ++it) {
                norm += it.value() * it.value();
            }
        }
        return sqrt(norm);
    }

    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    inline double SparseMatrix<T, indexT, compressionLevel, columnMajor>::vectorLength(uint32_t col) {
        double norm = 0;

        if constexpr (compressionLevel == 2) {
            if (performanceVectors) {
                #pragma omp parallel for schedule(dynamic)
                for (int i = 0; i < valueArraySize[col]; i++) {
                    norm += valueArray[col][i] * valueArray[col][i] * countsArray[col][i];
                }
                return sqrt(norm);
            }
        }

        for (typename SparseMatrix<T, indexT, compressionLevel>::InnerIterator it(*this, col); it; ++it) {
            norm += it.value() * it.value();
            return sqrt(norm);
        }
    }


    /************************************************************************************
     *
     *
     *                                 VECTOR METHODS
     *                                     (WIP)
     *
     *
     ************************************************************************************/


//     template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
//     inline double SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector::norm() {
//         double norm = 0;

//         if constexpr (compressionLevel == 2) {
//             if (performanceVectors) {
// #pragma omp parallel for schedule(dynamic)
//                 for (int i = 0; i < valueArraySize; i++) {
//                     norm += valueArray[i] * valueArray[i] * countsArray[i];
//                 }
//                 return sqrt(norm);
//             }
//         }
//         for (typename SparseMatrix<T, indexT, compressionLevel>::InnerIterator it(*this); it; ++it) {
//             norm += it.value() * it.value();
//         }
//         return sqrt(norm);
//     }

//     template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
//     double typename SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector SparseMatrix::operator*=(T scalar) {

//         if constexpr (compressionLevel == 2) {
//             if (performanceVectors) {
//                 #pragma omp parallel for schedule(dynamic)
//                 for (int i = 0; i < valueArraySize; i++) {
//                     valueArray[i] *= scalar;
//                 }
//                 return;
//             }
//         }
//     }

//     template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
//     typename CSF::SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector::operator*(T scalar) {

//         typename CSF::SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector newVector(*this);
//         if constexpr (compressionLevel == 2) {
//             if (performanceVectors) {
//                 #pragma omp parallel for schedule(dynamic)
//                 for (int i = 0; i < outerDim; i++) {
//                     for (int j = 0; j < valueArraySize[i]; j++) {
//                         newVector.valueArray[i][j] *= scalar;
//                     }
//                 }
//                 return newMatrix;
//             }
//         }

// #pragma omp parallel for schedule(dynamic)
//         for (typename SparseMatrix<T, indexT, compressionLevel>::InnerIterator it(newVector); it; ++it) {
//             if (it.isNewRun()) {
//                 it.coeff(it.value() * scalar);
//             }
//         }

//         return newMatrix;
//     }
}

