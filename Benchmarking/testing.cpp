#include "lib/benchmarkFunctions.h"

#define VALUE_TYPE double
#define INDEX_TYPE int


int main(int argc, char** argv) {
    if (argc == 1) {
    argv[1] = (char*)malloc(sizeof(char) * 100);
    argv[1] = "testMatrix.mtx";
    argv[2] = "1";
    argc = 3;
    }

    std::vector<Eigen::Triplet<VALUE_TYPE>> eigenTriplet;
    std::vector<double> matrixData;

    readFile(eigenTriplet, matrixData, argv[1]);

    // Create the matrix
    Eigen::SparseMatrix<VALUE_TYPE> eigen(matrixData[0], matrixData[1]);
    eigen.setFromTriplets(eigenTriplet.begin(), eigenTriplet.end());
    eigen.makeCompressed();

    // Create CSF matrix
    CSF::SparseMatrix<VALUE_TYPE, INDEX_TYPE, 2> csf2(eigen);
    CSF::SparseMatrix<VALUE_TYPE, INDEX_TYPE, 3> csf3(eigen);

    //Do something so none of this is optimized out
    eigen *= 2.0;
    csf2 *= 2.0;
    csf3 *= 2.0;

    std::cout << "Eigen size: " << eigen.nonZeros() * sizeof(double) + eigen.outerSize() * sizeof(uint32_t) + eigen.innerSize() * sizeof(uint32_t) << std::endl;
    std::cout << "CSF2 size: " << csf2.compressionSize() << std::endl;
    std::cout << "CSF3 size: " << csf3.compressionSize() << std::endl;

}

template <typename T>
void readFile(std::vector<Eigen::Triplet<T>>& eigenTriplet, std::vector<double>& matrixData, char* filename) {
    int retCode;
    MM_typecode matcode;
    FILE* f;
    int rows, cols, nonzeros;
    int i, * I, * J;
    double* val;

    // Check for correct number of arguments


    if ((f = fopen(filename, "r")) == NULL) {
        std::cout << "\033[31;1;4mError: Could not open matrix file!\033[0m" << std::endl;
        exit(1);
    }

    // Makes sure the banner can be read
    if (mm_read_banner(f, &matcode) != 0) {
        std::cout << "\033[31;1;4mError: Could not process Matrix Market banner.\033[0m" << std::endl;
        exit(1);
    }

    // Makes sure the matrix is not complex
    if (mm_is_complex(matcode) && !mm_is_matrix(matcode)) {
        std::cout << "\033[31;1;4mError: This application does not support \033[0m" << std::endl;
        std::cout << "\033[31;1;4mMarket Market type: \033[0m" << mm_typecode_to_str(matcode) << std::endl;
        std::cout << "Matrix might be complex or not a matrix";
        exit(1);
    }

    // Reads the dimensions and number of nonzeros
    if ((retCode = mm_read_mtx_crd_size(f, &rows, &cols, &nonzeros)) != 0) {
        std::cout << "\033[31;1;4mError: Could not read matrix dimensions.\033[0m" << std::endl;
        exit(1);
    }

    if (cols > 30000 || rows > 30000) {
        std::cout << "\033[31;1;4mMatrix too large, skipping...\033[0m" << std::endl;
        exit(1);
    }

    // Allocate memory for the matrix
    I = (int*)malloc(nonzeros * sizeof(int));
    J = (int*)malloc(nonzeros * sizeof(int));
    val = (double*)malloc(nonzeros * sizeof(double));

    // Read the matrix
    if (mm_is_pattern(matcode)) {
        for (i = 0; i < nonzeros; i++) {
            fscanf(f, "%d %d\n", &I[i], &J[i]);
            val[i] = 1.0;
            I[i]--;  /* adjust from 1-based to 0-based */
            J[i]--;
        }
    }
    else {
        for (i = 0; i < nonzeros; i++) {
            fscanf(f, "%d %d %lg\n", &I[i], &J[i], &val[i]);
            I[i]--;  /* adjust from 1-based to 0-based */
            J[i]--;
        }

    }

    // Close the file
    if (f != stdin) fclose(f);

    // Create the Eigen triplet
    for (int i = 0; i < nonzeros; i++) {
        eigenTriplet.push_back(Eigen::Triplet<VALUE_TYPE>(I[i], J[i], val[i]));
    }

    // Create the matrix data
    matrixData.push_back(rows);
    matrixData.push_back(cols);
    matrixData.push_back(nonzeros);

    //use a hash to store unique values
    std::unordered_set<double> uniqueValues;

    //iterates through the values and inserts them into the hash to record unique values
    for (int i = 0; i < nonzeros; i++) {
        uniqueValues.insert(val[i]);
    }
    matrixData.push_back(1.0 - ((double)uniqueValues.size() / nonzeros));

    // Calculate matrix density
    matrixData.push_back((double)nonzeros / (double)(rows * cols));

    // Free the memory
    free(I);
    free(J);
    free(val);
}