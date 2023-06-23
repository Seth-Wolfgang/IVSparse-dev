/**
 * @file CSF_Vector_Methods.hpp
 * @author Skyler Ruiter and Seth Wolfgang
 * @brief The CSF Vector class method definitions.
 * @version 0.1
 * @date 2023-06-23
 */

#pragma once

namespace CSF {

    //* Constructors & Destructor *//

    // Destructor
    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector::~Vector()
    {
        if (data != nullptr)
        {
            free(data);
        }

        if (valueArray != nullptr)
        {
            free(valueArray);
            free(countsArray);
        }
    }

    // Default constructor
    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector::Vector()
    {
        data = nullptr;
        endPtr = nullptr;
        size = 0;
        length = 0;
    }

    // Constructor for a vector from a CSF matrix
    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector::Vector(CSF::SparseMatrix<T, indexT, compressionLevel, columnMajor> &mat, uint32_t vec)
    {

        #ifdef CSF_DEBUG
        // make sure the vector is in bounds
        assert((vec >= 0 && vec < mat.outerSize()) && "Vector index out of bounds");

        // make sure the matrix is not empty
        assert((mat.outerSize() > 0 && mat.innerSize() > 0) && "Matrix is empty");
        #endif

        // get the length of the vector
        size = mat.getVectorSize(vec);
        length = mat.innerSize();

        // if the size is 0 then the vector is empty
        if (size == 0)
        {
            data = nullptr;
            endPtr = nullptr;
            return;
        }

        // set data pointer
        try
        {
            data = malloc(size);
        }
        catch (std::bad_alloc &e)
        {
            std::cerr << e.what() << '\n';
        }

        // copy the vector data into the vector
        memcpy(data, mat.vectorPointer(vec), size);

        // set the end pointer
        endPtr = (uint8_t *)data + size;

        if (mat.performanceVectorsInitialized())
        {
            performanceVectors = true;

            valueArraySize = mat.valueArraySize[vec];

            // allocate space for the value array
            try {
                valueArray = (T *)malloc(sizeof(T) * valueArraySize);
                countsArray = (uint32_t *)malloc(sizeof(uint32_t) * valueArraySize);
            } catch (std::bad_alloc &e) {
                std::cerr << e.what() << '\n';
            }

            // copy the value array
            memcpy(valueArray, mat.valueArray[vec], sizeof(T) * valueArraySize);

            // copy the counts array
            memcpy(countsArray, mat.countsArray[vec], sizeof(uint32_t) * valueArraySize);
        }

        // set the nnz
        if (nnz == 0 && size > 0)
        {
            // make an iterator for the vector
            CSF::SparseMatrix<T, indexT, compressionLevel, columnMajor>::InnerIterator it(*this);

            // iterate through the vector until the index is found
            while (it)
            {
                nnz++;
                ++it;
            }
        }

    }

    // Deep copy constructor
    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector::Vector(CSF::SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector &vec)
    {
        // set the size
        size = vec.size;

        // set the length
        length = vec.length;

        // if the size is 0 then the vector is empty
        if (size == 0)
        {
            data = nullptr;
            endPtr = nullptr;
            return;
        }

        // set data pointer
        try
        {
            data = malloc(size);
        }
        catch (std::bad_alloc &e)
        {
            std::cerr << e.what() << '\n';
        }

        // if performance vectors are on copy those as well
        if (vec.performanceVectors)
        {
            performanceVectors = true;

            valueArraySize = vec.valueArraySize;

            // allocate space for the value array
            try {
                valueArray = (T *)malloc(sizeof(T) * valueArraySize);
                countsArray = (uint32_t *)malloc(sizeof(uint32_t) * valueArraySize);
            } catch (std::bad_alloc &e) {
                std::cerr << e.what() << '\n';
            }

            // copy the value array
            memcpy(valueArray, vec.valueArray, sizeof(T) * valueArraySize);

            // copy the counts array
            memcpy(countsArray, vec.countsArray, sizeof(uint32_t) * valueArraySize);
        }

        // copy the vector data into the vector
        memcpy(data, vec.data, size);

        // set the end pointer
        endPtr = (uint8_t *)data + size;

        // set the nnz
        nnz = vec.nonZeros();

        #ifdef CSF_DEBUG
        userChecks();
        #endif
    }

    //* Methods *//

    // Does user checks on the vectors metadata
    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    void SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector::userChecks()
    {
        assert(std::is_floating_point<indexT>::value == false && "The index type must be a non-floating point type");

        assert((compressionLevel == 1 || compressionLevel == 2 || compressionLevel == 3) && "The compression level must be either 1, 2, or 3");

        assert((std::is_arithmetic<T>::value && std::is_arithmetic<indexT>::value) && "The value and index types must be numeric types");

        assert((std::is_same<indexT, bool>::value == false) && "The index type must not be bool");
    }

    // returns the inner dimension of the vector
    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    uint32_t SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector::innerSize() { return length; }

    // returns the outer dimension of the vector
    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    uint32_t SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector::outerSize() { return 1; }

    // returns the number of non-zero elements in the vector
    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    uint32_t SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector::nonZeros() { return nnz; }

    // returns a pointer to the beginning of the CSF Vector Data
    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    void *SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector::begin() { return data; }

    // Returns a pointer to the end of the CSF vector data
    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    void *SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector::end() { return endPtr; }

    // returns the byte size of the vector in memory
    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    size_t SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector::byteSize() { return size; }

    // returns the element at a given index
    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    T SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector::coeff(uint32_t index) { return (*this)[index]; }

    // returns the dimension of the vector
    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    uint32_t SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector::getLength() { return length; }

    // sets the performance vectors on or off
    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    void SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector::setPerformanceVectors(bool on)
    {
        if (on) { initPerformanceVectors(); }
        else { deletePerformanceVectors(); }
    }

    // returns if the performance vectors are in use or not
    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    bool SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector::performanceVectorsInitialized() { return performanceVectors; }

    // deletes the performance vectors 
    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    void SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector::deletePerformanceVectors()
    {

        if (!performanceVectors)
        {
            return;
        }
        performanceVectors = false;

        size_t valueArrayIndex = 0;

        for (typename CSF::SparseMatrix<T, indexT, compressionLevel, columnMajor> it(*this); it; ++it)
        {
            if (it.isNewRun())
            {
                it.coeff(valueArray[valueArrayIndex]);
                valueArrayIndex++;
            }
        }

        free(valueArray);
        free(countsArray);
        valueArraySize = 0;
    }

    // turns on the performance vectors
    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    void SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector::initPerformanceVectors()
    {

        if (performanceVectors)
        {
            return;
        }
        performanceVectors = true;

        std::vector<T> values;
        std::vector<uint32_t> countsVector;

        for (typename SparseMatrix<T, indexT, compressionLevel>::InnerIterator it(*this); it; ++it)
        {
            if (it.isNewRun())
            {
                values.push_back(it.value());
                countsVector.push_back(1);
                valueArraySize++;
            }
            else
            {
                countsVector[countsVector.size() - 1]++;
            }
        }

        try
        {
            valueArray = (T *)malloc(sizeof(T) * valueArraySize);
            memcpy(valueArray, values.data(), sizeof(T) * valueArraySize);

            countsArray = (uint32_t *)malloc(sizeof(uint32_t) * valueArraySize);
            memcpy(countsArray, countsVector.data(), sizeof(uint32_t) * valueArraySize);
        }
        catch (std::bad_alloc &e)
        {
            std::cout << "Error: " << e.what() << std::endl;
            exit(1);
        }

        values.clear();
        countsVector.clear();

        compSize += valueArraySize * sizeof(T) + valueArraySize * sizeof(uint32_t);
    }

    // Assignment Operator
    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    typename SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector::operator=(typename SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector &other)
    {
        // check if the vector is the same
        if (this == &other)
        {
            return *this;
        }

        // free the data if it is not null
        if (data != nullptr)
        {
            free(data);
        }

        if (valueArray != nullptr)
        {
            free(valueArray);
            free(countsArray);
        }

        // copy the data
        data = (uint8_t *)malloc(other.size);
        memcpy(data, other.data, other.size);

        // set the size
        size = other.size;

        // set the length
        length = other.length;

        // set the nnz
        nnz = other.nnz;

        // set the end pointer
        endPtr = (uint8_t *)data + size;

        if (other.performanceVectors)
        {
            valueArray = (T *)malloc(sizeof(T) * other.valueArraySize);
            countsArray = (uint32_t *)malloc(sizeof(uint32_t) * other.valueArraySize);

            memcpy(countsArray, other.countsArray, sizeof(uint32_t) * other.valueArraySize);
            memcpy(valueArray, other.valueArray, sizeof(T) * other.valueArraySize);

            valueArraySize = other.valueArraySize;
        }

        // return this
        return *this;
    }

    // Index acces operator
    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    T SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector::operator[](uint32_t index)
    {

        #ifdef CSF_DEBUG
        // check if the index is out of bounds
        assert(index < length && "The index is out of bounds");
        #endif

        // make an iterator for the vector
        CSF::SparseMatrix<T, indexT, compressionLevel, columnMajor>::InnerIterator it(*this);

        // iterate through the vector until the index is found
        while (it)
        {
            if (it.getIndex() == (indexT)index)
            {
                return it.value();
            }
            ++it;
        }

        // if the index is not found then return 0
        return 0;
    }

    // writes the vector to file (DOES NOT WRITE PERFORMANCE VECTORS)
    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    void SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector::write(const char *filename)
    {
        // open the file
        FILE *fp = fopen(filename, "wb");

        // write the data
        fwrite(data, size, 1, fp);

        // close the file
        fclose(fp);
    }

    // prints the vector to console
    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    void SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector::print()
    {

        // if length is larger than 100 then print then don't print
        if (length > 100)
        {
            std::cout << "Vector is too large to print" << std::endl;
            return;
        }

        std::cout << "Vector: ";
        std::cout << std::endl;

        // print a dense vector
        for (uint32_t i = 0; i < length; i++)
        {
            std::cout << (*this)[i] << " ";
        }

        std::cout << std::endl;
    }

    // returns the value performance vector
    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    T *SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector::getValues()
    {
        return valueArray;
    }

    // returns the counts performance vector
    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    uint32_t *SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector::getCounts()
    {
        return countsArray;
    }

    // returns the size of the performance vectors (equivalent to the number of unique values in the vector)
    template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
    uint32_t SparseMatrix<T, indexT, compressionLevel, columnMajor>::Vector::getValueArraySize()
    {
        return valueArraySize;
    }

}