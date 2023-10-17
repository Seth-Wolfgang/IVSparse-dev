#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <pybind11/stl.h>
#include <pybind11/eigen.h>
#include "../IVSparse/SparseMatrix"


namespace py = pybind11;



// template <typename T, typename indexT, uint8_t compressionLevel, bool columnMajor>
// class PySparseMatrixBase{
//     using IVSparse::SparseMatrix<T, indexT, compressionLevel, columnMajor>::SparseMatrix;
//     // using IVSparse::SparseMatrix<T, indexT, compressionLevel, columnMajor>::operator=;
//     // using IVSparse::SparseMatrix<T, indexT, compressionLevel, columnMajor>::operator==;
//     // using IVSparse::SparseMatrix<T, indexT, compressionLevel, columnMajor>::operator!=;
//     // using IVSparse::SparseMatrix<T, indexT, compressionLevel, columnMajor>::operator*;
//     // using IVSparse::SparseMatrix<T, indexT, compressionLevel, columnMajor>::operator*=;

//     // template <typename T2, typename indexT2>
//     // void compressCSC(T2* vals, indexT2* innerIndices, indexT2* outerPointers) override {
//     //     PYBIND11_OVERRIDE_PURE(
//     //         void,
//     //         IVSparse::SparseMatrix<T, indexT, compressionLevel, columnMajor>,
//     //         compressCSC,
//     //         vals,
//     //         innerIndices,
//     //         outerPointers
//     //     );
//     // }

//     void encodeValueType() override {
//         PYBIND11_OVERRIDE_PURE(
//             void,
//             IVSparse::SparseMatrix<T, indexT, compressionLevel, columnMajor>,
//             encodeValueType,
//         );
//     }

//     void checkValueType() override {
//         PYBIND11_OVERRIDE_PURE(
//             void,
//             IVSparse::SparseMatrix<T, indexT, compressionLevel, columnMajor>,
//             checkValueType
//         );
//     }

//     void userChecks() override {
//         PYBIND11_OVERRIDE_PURE(
//             void,
//             IVSparse::SparseMatrix<T, indexT, compressionLevel, columnMajor>,
//             userChecks
//         );
//     }

//     // void calculateCompSize() override {
//     //     PYBIND11_OVERRIDE_PURE(
//     //         void,
//     //         IVSparse::SparseMatrix<T, indexT, compressionLevel, columnMajor>,
//     //         calculateCompSize
//     //     );
//     // }

//     // void inPlaceScalarMultiply(T scalar) {
//     //     PYBIND11_OVERRIDE_PURE(
//     //         void,
//     //         IVSparse::SparseMatrix<T, indexT, compressionLevel, columnMajor>,
//     //         inPlaceScalarMultiply,
//     //         scalar
//     //     );
//     // }

//     // IVSparse::SparseMatrix<T, indexT, compressionLevel, columnMajor> scalarMultiply(T scalar) {
//     //     PYBIND11_OVERRIDE_PURE(
//     //         IVSparse::SparseMatrix<T, indexT, compressionLevel, columnMajor>,
//     //         IVSparse::SparseMatrix<T, indexT, compressionLevel, columnMajor>,
//     //         scalarMultiply,
//     //         scalar
//     //     );
//     // }

//     // Eigen::Matrix<T, -1, 1> vectorMultiply(Eigen::Matrix<T, -1, 1> vec) {
//     //     PYBIND11_OVERRIDE_PURE(
//     //         Eigen::Matrix<T, -1, 1>,
//     //         IVSparse::SparseMatrix<T, indexT, compressionLevel, columnMajor>,
//     //         vectorMultiply,
//     //         vec
//     //     );
//     // }

//     public:

//     void write(const char* filename) {
//         PYBIND11_OVERRIDE_PURE(
//             void,
//             IVSparse::SparseMatrix<T, indexT, compressionLevel, columnMajor>,
//             write,
//             filename
//         );
//     }

//     // T coeff(uint32_t row, uint32_t col) {
//     //     PYBIND11_OVERRIDE_PURE(
//     //         T,
//     //         IVSparse::SparseMatrix<T, indexT, compressionLevel, columnMajor>,
//     //         coeff,
//     //         row,
//     //         col
//     //     );
//     // }

//     // uint32_t rows() const {
//     //     PYBIND11_OVERRIDE_PURE(
//     //         uint32_t,
//     //         IVSparse::SparseMatrix<T, indexT, compressionLevel, columnMajor>,
//     //         rows
//     //     );
//     // }

//     // uint32_t cols() const {
//     //     PYBIND11_OVERRIDE_PURE(
//     //         uint32_t,
//     //         IVSparse::SparseMatrix<T, indexT, compressionLevel, columnMajor>,
//     //         cols
//     //     );
//     // }

//     // uint32_t innerSize() const {
//     //     PYBIND11_OVERRIDE_PURE(
//     //         uint32_t,
//     //         IVSparse::SparseMatrix<T, indexT, compressionLevel, columnMajor>,
//     //         innerSize
//     //     );
//     // }

//     // uint32_t outerSize() const {
//     //     PYBIND11_OVERRIDE_PURE(
//     //         uint32_t,
//     //         IVSparse::SparseMatrix<T, indexT, compressionLevel, columnMajor>,
//     //         outerSize
//     //     );
//     // }

//     // uint32_t nonZeros() const {
//     //     PYBIND11_OVERRIDE_PURE(
//     //         uint32_t,
//     //         IVSparse::SparseMatrix<T, indexT, compressionLevel, columnMajor>,
//     //         nonZeros
//     //     );
//     // }

//     // uint64_t byteSize() const {
//     //     PYBIND11_OVERRIDE_PURE(
//     //         uint64_t,
//     //         IVSparse::SparseMatrix<T, indexT, compressionLevel, columnMajor>,
//     //         byteSize
//     //     );
//     // }

//     // void print() {
//     //     PYBIND11_OVERRIDE_PURE(
//     //         void,
//     //         IVSparse::SparseMatrix<T, indexT, compressionLevel, columnMajor>,
//     //         print
//     //     );
//     // }

//     // bool isColumnMajor() const {
//     //     PYBIND11_OVERRIDE_PURE(
//     //         bool,
//     //         IVSparse::SparseMatrix<T, indexT, compressionLevel, columnMajor>,
//     //         isColumnMajor
//     //     );
//     // }

//     // T* getValues(uint32_t vec) const {
//     //     PYBIND11_OVERRIDE_PURE(
//     //         T*,
//     //         IVSparse::SparseMatrix<T, indexT, compressionLevel, columnMajor>,
//     //         getValues,
//     //         vec
//     //     );
//     // }

//     // indexT* getCounts(uint32_t vec) const {
//     //     PYBIND11_OVERRIDE_PURE(
//     //         indexT*,
//     //         IVSparse::SparseMatrix<T, indexT, compressionLevel, columnMajor>,
//     //         getCounts,
//     //         vec
//     //     );
//     // }

//     // indexT* getIndices(uint32_t vec) const {
//     //     PYBIND11_OVERRIDE_PURE(
//     //         indexT*,
//     //         IVSparse::SparseMatrix<T, indexT, compressionLevel, columnMajor>,
//     //         getIndices,
//     //         vec
//     //     );
//     // }

//     // uint32_t getNumUniqueVals(uint32_t vec) const {
//     //     PYBIND11_OVERRIDE_PURE(
//     //         uint32_t,
//     //         IVSparse::SparseMatrix<T, indexT, compressionLevel, columnMajor>,
//     //         getNumUniqueVals,
//     //         vec
//     //     );
//     // }

//     // uint32_t getNumIndices(uint32_t vec) const {
//     //     PYBIND11_OVERRIDE_PURE(
//     //         uint32_t,
//     //         IVSparse::SparseMatrix<T, indexT, compressionLevel, columnMajor>,
//     //         getNumIndices,
//     //         vec
//     //     );
//     // }

//     // std::vector<T> outerSum(uint32_t vec) override {
//     //     PYBIND11_OVERRIDE_PURE(
//     //         std::vector<T>,
//     //         IVSparse::SparseMatrix<T, indexT, compressionLevel, columnMajor>,
//     //         outerSum,
//     //         vec
//     //     );
//     // }

//     // std::vector<T> innerSum(uint32_t vec) override {
//     //     PYBIND11_OVERRIDE_PURE(
//     //         std::vector<T>,
//     //         IVSparse::SparseMatrix<T, indexT, compressionLevel, columnMajor>,
//     //         innerSum,
//     //         vec
//     //     );
//     // }

//     // std::vector<T> MaxColCoeff(uint32_t vec) override {
//     //     PYBIND11_OVERRIDE_PURE(
//     //         std::vector<T>,
//     //         IVSparse::SparseMatrix<T, indexT, compressionLevel, columnMajor>,
//     //         MaxColCoeff,
//     //         vec
//     //     );
//     // }

//     // std::vector<T> MaxRowCoeff(uint32_t vec) override {
//     //     PYBIND11_OVERRIDE_PURE(
//     //         std::vector<T>,
//     //         IVSparse::SparseMatrix<T, indexT, compressionLevel, columnMajor>,
//     //         MaxRowCoeff,
//     //         vec
//     //     );
//     // }

//     // std::vector<T> minRowCoeff(uint32_t vec) override {
//     //     PYBIND11_OVERRIDE_PURE(
//     //         std::vector<T>,
//     //         IVSparse::SparseMatrix<T, indexT, compressionLevel, columnMajor>,
//     //         minRowCoeff,
//     //         vec
//     //     );
//     // }

//     // std::vector<T> minColCoeff(uint32_t vec) override {
//     //     PYBIND11_OVERRIDE_PURE(
//     //         std::vector<T>,
//     //         IVSparse::SparseMatrix<T, indexT, compressionLevel, columnMajor>,
//     //         minColCoeff,
//     //         vec
//     //     );
//     // }

//     // T trace() override {
//     //     PYBIND11_OVERRIDE_PURE(
//     //         T,
//     //         IVSparse::SparseMatrix<T, indexT, compressionLevel, columnMajor>,
//     //         trace
//     //     );
//     // }

//     // T sum() override {
//     //     PYBIND11_OVERRIDE_PURE(
//     //         T,
//     //         IVSparse::SparseMatrix<T, indexT, compressionLevel, columnMajor>,
//     //         sum
//     //     );
//     // }

//     // double norm() override {
//     //     PYBIND11_OVERRIDE_PURE(
//     //         T,
//     //         IVSparse::SparseMatrix<T, indexT, compressionLevel, columnMajor>,
//     //         norm
//     //     );
//     // }

//     // double vectorLength() override {
//     //     PYBIND11_OVERRIDE_PURE(
//     //         T,
//     //         IVSparse::SparseMatrix<T, indexT, compressionLevel, columnMajor>,
//     //         vectorLength
//     //     );
//     // }

//     // IVSparse::SparseMatrix<T, indexT, 1, columnMajor> toCSC() override {
//     //     PYBIND11_OVERRIDE_PURE(
//     //         Eigen::SparseMatrix<T, columnMajor>,
//     //         IVSparse::SparseMatrix<T, indexT, compressionLevel, columnMajor>,
//     //         toCSC
//     //     );
//     // }

//     // Eigen::SparseMatrix<T, !columnMajor> toEigen() override {
//     //     PYBIND11_OVERRIDE_PURE(
//     //         Eigen::SparseMatrix<T, !columnMajor>,
//     //         IVSparse::SparseMatrix<T, indexT, compressionLevel, columnMajor>,
//     //         toEigen
//     //     );
//     // }

//     // IVSparse::SparseMatrix<T, indexT, compressionLevel, !columnMajor> transpose() override {
//     //     PYBIND11_OVERRIDE_PURE(
//     //         IVSparse::SparseMatrix<T, indexT, compressionLevel, !columnMajor>,
//     //         IVSparse::SparseMatrix<T, indexT, compressionLevel, columnMajor>,
//     //         transpose
//     //     );
//     // }

//     // void inPlaceTranspose() override {
//     //     PYBIND11_OVERRIDE_PURE(
//     //         void,
//     //         IVSparse::SparseMatrix<T, indexT, compressionLevel, columnMajor>,
//     //         inPlaceTranspose
//     //     );
//     // }
// };






PYBIND11_MODULE(PyVSparse, m) {
    m.doc() = "pybind11 example plugin"; // optional module docstring

    py::class_<IVSparse::SparseMatrixBase, IVSparse::SparseMatrix<int8_t, int8_t, 2, false>>(m, "VCSC_int8t_int8_t_colMaj")
        // .def(py::init<Eigen::SparseMatrix<int8_t>& >())
        // .def(py::init<Eigen::SparseMatrix<int8_t, Eigen::RowMajor>& >())
        // .def(py::init<IVSparse::SparseMatrix<uint8_t, int8_t, 2, false>& >())
        // .def(py::init<IVSparse::SparseMatrix<uint8_t, int8_t, 2 >& >())
        // .def(py::init<IVSparse::SparseMatrix<int8_t, int8_t, 3, false>& >())
        // .def(py::init<IVSparse::SparseMatrix<int8_t, int8_t, 3 >& >())
        // .def(py::init<int8_t*, int8_t*, int8_t*, uint32_t, uint32_t, uint32_t>())
        // .def(py::init<std::vector<std::tuple<int8_t, int8_t, int8_t>>&, uint32_t, uint32_t, uint32_t>())
        // .def(py::init<const char*>())
        .def(py::init<>())
        .def("rows", &IVSparse::SparseMatrixBase::rows, " ", py::return_value_policy::copy)
        .def("cols", &IVSparse::SparseMatrixBase::cols, py::return_value_policy::copy)
        .def("innerSize", &IVSparse::SparseMatrixBase::innerSize, py::return_value_policy::copy)
        .def("outerSize", &IVSparse::SparseMatrixBase::outerSize, py::return_value_policy::copy)
        .def("nonZeros", &IVSparse::SparseMatrixBase::nonZeros, py::return_value_policy::copy)
        .def("byteSize", &IVSparse::SparseMatrixBase::byteSize, py::return_value_policy::copy)
        .def("write", &IVSparse::SparseMatrixBase::write, py::arg("filename"))
        .def("print", &IVSparse::SparseMatrixBase::print)
        // .def("coeff", &IVSparse::SparseMatrixBase::coeff, py::return_value_policy::copy, py::arg("row"), py::arg("col"))
        .def("isColumnMajor", &IVSparse::SparseMatrix<int8_t, int8_t, 2, false>::isColumnMajor, py::return_value_policy::copy)
        .def("getValues", &IVSparse::SparseMatrix<int8_t, int8_t, 2, false>::getValues, py::return_value_policy::copy)
        .def("getCounts", &IVSparse::SparseMatrix<int8_t, int8_t, 2, false>::getCounts, py::return_value_policy::copy)
        .def("getIndices", &IVSparse::SparseMatrix<int8_t, int8_t, 2, false>::getIndices, py::return_value_policy::copy)
        .def("getNumUniqueVals", &IVSparse::SparseMatrix<int8_t, int8_t, 2, false>::getNumUniqueVals, py::return_value_policy::copy)
        .def("getNumIndices", &IVSparse::SparseMatrix<int8_t, int8_t, 2, false>::getNumIndices, py::return_value_policy::copy)
        .def("outerSum", &IVSparse::SparseMatrix<int8_t, int8_t, 2, false>::outerSum, py::return_value_policy::copy)
        .def("innerSum", &IVSparse::SparseMatrix<int8_t, int8_t, 2, false>::innerSum, py::return_value_policy::copy)
        .def("MaxColCoeff", &IVSparse::SparseMatrix<int8_t, int8_t, 2, false>::maxColCoeff, py::return_value_policy::copy)
        .def("MaxRowCoeff", &IVSparse::SparseMatrix<int8_t, int8_t, 2, false>::maxRowCoeff, py::return_value_policy::copy)
        .def("minRowCoeff", &IVSparse::SparseMatrix<int8_t, int8_t, 2, false>::minRowCoeff, py::return_value_policy::copy)
        .def("minColCoeff", &IVSparse::SparseMatrix<int8_t, int8_t, 2, false>::minColCoeff, py::return_value_policy::copy)
        .def("trace", &IVSparse::SparseMatrix<int8_t, int8_t, 2, false>::trace, py::return_value_policy::copy)
        .def("sum", &IVSparse::SparseMatrix<int8_t, int8_t, 2, false>::sum, py::return_value_policy::copy)
        .def("norm", &IVSparse::SparseMatrix<int8_t, int8_t, 2, false>::norm, py::return_value_policy::copy)
        .def("vectorLength", &IVSparse::SparseMatrix<int8_t, int8_t, 2, false>::vectorLength, py::return_value_policy::copy)
        .def("toCSC", &IVSparse::SparseMatrix<int8_t, int8_t, 2, false>::toCSC, py::return_value_policy::copy)
        .def("toEigen", &IVSparse::SparseMatrix<int8_t, int8_t, 2, false>::toEigen, py::return_value_policy::copy)
        .def("transpose", &IVSparse::SparseMatrix<int8_t, int8_t, 2, false>::transpose, py::return_value_policy::copy)
        .def("inPlaceTranspose", &IVSparse::SparseMatrix<int8_t, int8_t, 2, false>::inPlaceTranspose);
        // .def(py::self = py::self, py::return_value_policy::copy)
        // .def(py::self == py::self, py::return_value_policy::copy)
        // .def(py::self != py::self, py::return_value_policy::copy)
        // .def(py::self * int8_t(), py::return_value_policy::copy)
        // .def(py::self * uint8_t(), py::return_value_policy::copy)
        // .def(py::self * int16_t(), py::return_value_policy::copy)
        // .def(py::self * uint16_t(), py::return_value_policy::copy)
        // .def(py::self * int32_t(), py::return_value_policy::copy)
        // .def(py::self * uint32_t(), py::return_value_policy::copy)
        // .def(py::self * int64_t(), py::return_value_policy::copy)
        // .def(py::self * uint64_t(), py::return_value_policy::copy)
        // .def(py::self *= int8_t())
        // .def(py::self *= uint8_t())
        // .def(py::self *= int16_t())
        // .def(py::self *= uint16_t())
        // .def(py::self *= int32_t())
        // .def(py::self *= uint32_t())
        // .def(py::self *= int64_t())
        // .def(py::self *= uint64_t())
        // .def(py::self * Eigen::Matrix<int8_t, Eigen::Dynamic, Eigen::Dynamic>(), py::return_value_policy::copy)
        // .def(py::self * Eigen::Matrix<uint8_t, Eigen::Dynamic, Eigen::Dynamic>(), py::return_value_policy::copy)
        // .def(py::self * Eigen::Matrix<int16_t, Eigen::Dynamic, Eigen::Dynamic>(), py::return_value_policy::copy)
        // .def(py::self * Eigen::Matrix<uint16_t, Eigen::Dynamic, Eigen::Dynamic>(), py::return_value_policy::copy)
        // .def(py::self * Eigen::Matrix<int32_t, Eigen::Dynamic, Eigen::Dynamic>(), py::return_value_policy::copy)
        // .def(py::self * Eigen::Matrix<uint32_t, Eigen::Dynamic, Eigen::Dynamic>(), py::return_value_policy::copy)
        // .def(py::self * Eigen::Matrix<int64_t, Eigen::Dynamic, Eigen::Dynamic>(), py::return_value_policy::copy)
        // .def(py::self * Eigen::Matrix<uint64_t, Eigen::Dynamic, Eigen::Dynamic>(), py::return_value_policy::copy)
        // .def(py::self * Eigen::Matrix < int8_t, Eigen::Dynamic, 1, py::return_value_policy::copy)
        // .def(py::self * Eigen::Matrix < uint8_t, Eigen::Dynamic, 1, py::return_value_policy::copy)
        // .def(py::self * Eigen::Matrix < int16_t, Eigen::Dynamic, 1, py::return_value_policy::copy)
        // .def(py::self * Eigen::Matrix < uint16_t, Eigen::Dynamic, 1, py::return_value_policy::copy)
        // .def(py::self * Eigen::Matrix < int32_t, Eigen::Dynamic, 1, py::return_value_policy::copy)
        // .def(py::self * Eigen::Matrix < uint32_t, Eigen::Dynamic, 1, py::return_value_policy::copy)
        // .def(py::self * Eigen::Matrix < int64_t, Eigen::Dynamic, 1, py::return_value_policy::copy)
        // .def(py::self * Eigen::Matrix < uint64_t, Eigen::Dynamic, 1, py::return_value_policy::copy)



        // .def("slice", &IVSparse::SparseMatrix::slice, py::return_value_policy::copy, py::arg("start"), py::arg("end"))




};