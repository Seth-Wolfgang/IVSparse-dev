#include "../CSF/SparseMatrix"
#include "../misc/matrix_creator.cpp"

int main() {

    /**
     * CSF offers a few options for creating a CSF::SparseMatrix. Each template is made to give
     * to create the sparse matrix format that fits your needs. There are 4 different templates:
     *
     *      CSF::SparseMatrix<T, indexType, compressioLevel, rowMajor>
     *
     *      typename T           -> the data type of each value in the matrix
     *
     *      typename IndexType   -> the data type of the index arrays, thing of
     *                              the width between each index, so an int is 4 bytes to
     *                              store an index whereas uint16_t is 2 bytes
     *                              and uint8_t is 1 byte.
     *
     *      int compressionLevel -> the compression level of the matrix.
     *                              - level 1 is CSC or CSR (see next tempalate for CSR)
     *                              - level 2 is CSF with only run length encoding with
     *                                optional performance array settings.
     *                              - level 3 is CSF with run length encoding,
     *                                positive delta encodin, and byte packing.
     *                                performance arrays are not included in this
     *                                template due to the purpose being for maximum
     *                                compression.
     *
     *      bool columnMajor     ->   whether the matrix is stored in row major or column major.
    */

    // The first constructor is not very useful, but it is there if you need it.
    CSF::SparseMatrix<double> csfMatrix1;

    // it simply creates the object, but everything is set to null or 0.

    // CSF was built in mind for compressing from CSC matrices.
    int values[] = { 1, 1, 1, 2, 2, 2, 3, 3, 3 };
    int rowIndices[] = { 0, 1, 2, 0, 1, 2, 0, 1, 2 };
    int colPointers[] = { 0, 3, 6, 9 };

    CSF::SparseMatrix<int, int, 2> csfMatrix2(values, rowIndices, colPointers, 3, 3, 9);
    std::cout << csfMatrix2 << std::endl;

    // and we can even change the templates for this constructor.

    CSF::SparseMatrix<int, uint8_t, 2> csfMatrix3(values, rowIndices, colPointers, 3, 3, 9);
    std::cout << csfMatrix2 << std::endl;

    // The difference here is the size in memory
    std::cout << "Size of csfMatrix2: " << csfMatrix2.compressionSize() << std::endl;
    std::cout << "Size of csfMatrix3: " << csfMatrix3.compressionSize() << std::endl;

    // we can also use CSF level 3

    CSF::SparseMatrix<int, uint64_t, 3> csfMatrix4(values, rowIndices, colPointers, 3, 3, 9);

    // The size for this is slightly higher due to added bytes for reading each run
    // in larger matrices, this value should be smaller than level 2.
    // The middle template, indexType, does not matter for level 3 compression due to byte packing.
    std::cout << "Size of csfMatrix3: " << csfMatrix4.compressionSize() << std::endl;
    std::cout << std::endl;
    // We can also create a CSF matrix from a CSR matrix.
    CSF::SparseMatrix<int, int, 2, false> csfMatrixRow(values, rowIndices, colPointers, 3, 3, 9);
    
    // The only difference is the last template, which is set to true by default, but we do treat 
    // the inputs a little differently, so the matrix is stored in row major.
    std::cout << csfMatrixRow << std::endl;
        

}