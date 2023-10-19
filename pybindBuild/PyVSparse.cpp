#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <pybind11/stl.h>
#include <pybind11/eigen.h>
#include "../IVSparse/SparseMatrix"


namespace py = pybind11;

template <typename T, typename indexT, int compressionLevel, bool isColMajor>
void declareBase(py::module &m, const char* name);

template <typename T, typename indexT, int compressionLevel, bool isColMajor>
void declareSelfFunc(py::module &m, const char* name);

template <typename... Ts, typename... indexTs, typename... compLevels, typename... isColMajors>
void generateCombinations(const char* name);

// holds a list of types -> declared at compile time


template <typename... Ts>
struct typeList {};

template <typename... ITs>
struct indexTypeList {};

template <int... Cs>
struct compressionLevelList {};

template <bool... Cm>
struct isColMajorList {};

PYBIND11_MODULE(PyVSparse, m) {
    m.doc() = "pybind11 example plugin"; // optional module docstring

// VCSC_int8t_int8_t_colMaj

    // const char* myType = "VCSC_int8t_int8_t_colMaj";


// VCSC
// IVCSC

// int8_t
// uint8_t
// int16_t
// uint16_t
// int32_t
// uint32_t
// int64_t
// uint64_t
// float
// double

// int8_t
// uint8_t
// int16_t
// uint16_t
// int32_t
// uint32_t
// int64_t
// uint64_t

// true
// false

    const typeList<int8_t, uint8_t, int16_t, uint16_t, int32_t, uint32_t, int64_t, uint64_t, float, double> myTypes;
    const indexTypeList<int8_t, uint8_t, int16_t, uint16_t, int32_t, uint32_t, int64_t, uint64_t> myIndexTypes;
    const compressionLevelList<2,3> myCompLevels;
    const isColMajorList<true, false> myColMajors;
    


    generateCombinations<>("test");


    // declareBase<T, indexT, (2 options), (2 options) >(m, myType);
    // declareSelfFunc<int8_t, int8_t, 2, true>(m, myType);



        // .def(py::init<IVSparse::SparseMatrix<uint8_t, int8_t, 2, false>& >())
        // .def(py::init<IVSparse::SparseMatrix<uint8_t, int8_t, 2 >& >())
        // .def(py::init<IVSparse::SparseMatrix<int8_t, int8_t, 3, false>& >())
        // .def(py::init<IVSparse::SparseMatrix<int8_t, int8_t, 3 >& >())

};

template <typename T, typename indexT, int compressionLevel, bool isColMajor>
void declareBase(py::module &m, const char* name){
    
    py::class_<IVSparse::SparseMatrixBase, IVSparse::SparseMatrix<T, indexT, compressionLevel, isColMajor>>(m, name)
        .def(py::init<Eigen::SparseMatrix<T>& >())
        .def(py::init<Eigen::SparseMatrix<T, Eigen::RowMajor>& >())
        .def(py::init<T*, T*, T*, uint32_t, uint32_t, uint32_t>())
        .def(py::init<std::vector<std::tuple<indexT, indexT, T>>&, uint32_t, uint32_t, uint32_t>())
        .def(py::init<const char*>())
        .def(py::init<>())
        .def("rows", &IVSparse::SparseMatrixBase::rows, " ", py::return_value_policy::copy)
        .def("cols", &IVSparse::SparseMatrixBase::cols, py::return_value_policy::copy)
        .def("innerSize", &IVSparse::SparseMatrixBase::innerSize, py::return_value_policy::copy)
        .def("outerSize", &IVSparse::SparseMatrixBase::outerSize, py::return_value_policy::copy)
        .def("nonZeros", &IVSparse::SparseMatrixBase::nonZeros, py::return_value_policy::copy)
        .def("byteSize", &IVSparse::SparseMatrixBase::byteSize, py::return_value_policy::copy)
        .def("write", &IVSparse::SparseMatrixBase::write, py::arg("filename"))
        .def("print", &IVSparse::SparseMatrixBase::print);
}


// self as in self types T = T 
template <typename T, typename indexT, int compressionLevel, bool isColMajor>
void declareSelfFunc(py::module &m, const char* name){
    py::class_<IVSparse::SparseMatrix<T, indexT, compressionLevel, isColMajor>, IVSparse::SparseMatrixBase>(m, name)
        .def("isColumnMajor", &IVSparse::SparseMatrix<T, indexT, compressionLevel, isColMajor>::isColumnMajor, py::return_value_policy::copy)
        .def("coeff", &IVSparse::SparseMatrix<T, indexT, compressionLevel, isColMajor>::coeff, py::return_value_policy::copy, "Sets value at run of coefficient", py::arg("row").none(false), py::arg("col").none(false))
        .def("isColumnMajor", &IVSparse::SparseMatrix<T, indexT, compressionLevel, isColMajor>::isColumnMajor, py::return_value_policy::copy)
        .def("getValues", &IVSparse::SparseMatrix<T, indexT, compressionLevel, isColMajor>::getValues, py::return_value_policy::copy)
        .def("getCounts", &IVSparse::SparseMatrix<T, indexT, compressionLevel, isColMajor>::getCounts, py::return_value_policy::copy)
        .def("getIndices", &IVSparse::SparseMatrix<T, indexT, compressionLevel, isColMajor>::getIndices, py::return_value_policy::copy)
        .def("getNumUniqueVals", &IVSparse::SparseMatrix<T, indexT, compressionLevel, isColMajor>::getNumUniqueVals, py::return_value_policy::copy)
        .def("getNumIndices", &IVSparse::SparseMatrix<T, indexT, compressionLevel, isColMajor>::getNumIndices, py::return_value_policy::copy)
        .def("outerSum", &IVSparse::SparseMatrix<T, indexT, compressionLevel, isColMajor>::outerSum, py::return_value_policy::copy)
        .def("innerSum", &IVSparse::SparseMatrix<T, indexT, compressionLevel, isColMajor>::innerSum, py::return_value_policy::copy)
        .def("MaxColCoeff", &IVSparse::SparseMatrix<T, indexT, compressionLevel, isColMajor>::maxColCoeff, py::return_value_policy::copy)
        .def("MaxRowCoeff", &IVSparse::SparseMatrix<T, indexT, compressionLevel, isColMajor>::maxRowCoeff, py::return_value_policy::copy)
        .def("minRowCoeff", &IVSparse::SparseMatrix<T, indexT, compressionLevel, isColMajor>::minRowCoeff, py::return_value_policy::copy)
        .def("minColCoeff", &IVSparse::SparseMatrix<T, indexT, compressionLevel, isColMajor>::minColCoeff, py::return_value_policy::copy)
        .def("trace", &IVSparse::SparseMatrix<T, indexT, compressionLevel, isColMajor>::trace, py::return_value_policy::copy)
        .def("sum", &IVSparse::SparseMatrix<T, indexT, compressionLevel, isColMajor>::sum, py::return_value_policy::copy)
        .def("norm", &IVSparse::SparseMatrix<T, indexT, compressionLevel, isColMajor>::norm, py::return_value_policy::copy)
        .def("vectorLength", &IVSparse::SparseMatrix<T, indexT, compressionLevel, isColMajor>::vectorLength, py::return_value_policy::copy)
        .def("toCSC", &IVSparse::SparseMatrix<T, indexT, compressionLevel, isColMajor>::toCSC, py::return_value_policy::copy)
        .def("toEigen", &IVSparse::SparseMatrix<T, indexT, compressionLevel, isColMajor>::toEigen, py::return_value_policy::copy)
        .def("transpose", &IVSparse::SparseMatrix<T, indexT, compressionLevel, isColMajor>::transpose, py::return_value_policy::copy)
        .def("inPlaceTranspose", &IVSparse::SparseMatrix<T, indexT, compressionLevel, isColMajor>::inPlaceTranspose)
        .def(py::self *= int8_t())
        .def(py::self *= uint8_t())
        .def(py::self *= int16_t())
        .def(py::self *= uint16_t())
        .def(py::self *= int32_t())
        .def(py::self *= uint32_t())
        .def(py::self *= int64_t())
        .def(py::self *= uint64_t())
        .def("__copy__", [](const IVSparse::SparseMatrix<T, indexT, compressionLevel, isColMajor>& self) {
                return IVSparse::SparseMatrix<T, indexT, compressionLevel, isColMajor>(self);
        })
        .def("__deepcopy__", [](const IVSparse::SparseMatrix<T, indexT, compressionLevel, isColMajor>& self, py::dict) {                  //TODO: NEED TO CHECK
                 return IVSparse::SparseMatrix<T, indexT, compressionLevel, isColMajor>(self);
        })
        .def("__eq__", [](const IVSparse::SparseMatrix<T, indexT, compressionLevel, isColMajor>& self, const IVSparse::SparseMatrix<T, indexT, compressionLevel, isColMajor>& other) {
            return self == other;
        }, py::is_operator())
        .def("__ne__", [](const IVSparse::SparseMatrix<T, indexT, compressionLevel, isColMajor>& self, const IVSparse::SparseMatrix<T, indexT, compressionLevel, isColMajor>& other) {
            return !(self == other);
        }, py::is_operator())
        .def("__mul__", [](IVSparse::SparseMatrix<T, indexT, compressionLevel, isColMajor> self, int8_t a) {
            return self * a;
        }, py::is_operator())
        .def("__mul__", [](IVSparse::SparseMatrix<T, indexT, compressionLevel, isColMajor> self, uint8_t a) {
            return self * a;
        }, py::is_operator())
        .def("__mul__", [](IVSparse::SparseMatrix<T, indexT, compressionLevel, isColMajor> self, int16_t a) {
            return self * a;
        }, py::is_operator())
        .def("__mul__", [](IVSparse::SparseMatrix<T, indexT, compressionLevel, isColMajor> self, uint16_t a) {
            return self * a;
        }, py::is_operator())
        .def("__mul__", [](IVSparse::SparseMatrix<T, indexT, compressionLevel, isColMajor> self, int32_t a) {
            return self * a;
        }, py::is_operator())
        .def("__mul__", [](IVSparse::SparseMatrix<T, indexT, compressionLevel, isColMajor> self, uint32_t a) {
            return self * a;
        }, py::is_operator())
        .def("__mul__", [](IVSparse::SparseMatrix<T, indexT, compressionLevel, isColMajor> self, int64_t a) {
            return self * a;
        }, py::is_operator())
        .def("__mul__", [](IVSparse::SparseMatrix<T, indexT, compressionLevel, isColMajor> self, uint64_t a) {
            return self * a;
        }, py::is_operator())
        .def("__mul__", [](IVSparse::SparseMatrix<T, indexT, compressionLevel, isColMajor> self, double a) {
            return self * a;
        }, py::is_operator())
        .def("__mul__", [](IVSparse::SparseMatrix<T, indexT, compressionLevel, isColMajor> self, float a) {
            return self * a;
        }, py::is_operator())
        .def("__mul__", [](IVSparse::SparseMatrix<T, indexT, compressionLevel, isColMajor> self, Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic>& a) {
            return self * a;
        }, py::is_operator())
        .def("__mul__", [](IVSparse::SparseMatrix<T, indexT, compressionLevel, isColMajor> self, Eigen::Matrix<T, Eigen::Dynamic, 1>& a) {
            return self * a;
        }, py::is_operator());
}


// other as in other types (Other constructors like IVCSC -> VCSC)
// template <typename T, typename indexT, int compressionLevel, bool isColMajor>
// void declareOtherFunc(py::module &m, std::string& name){


// }


template <typename... Ts, typename... indexTs, typename... compLevels, typename... isColMajors>
void generateCombinations(const char* name) {
    // Generate combinations for all types
    (declareBase<Ts, indexTs, compLevels, isColMajors>(name), ...);
}


// const char** myTypes = [["VCSC_int8t_int8t_true"],
// ["VCSC_int8t_int8t_false"],
// ["VCSC_int8t_uint8t_true"],
// ["VCSC_int8t_uint8t_false"],
// ["VCSC_int8t_int16t_true"],
// ["VCSC_int8t_int16t_false"],
// ["VCSC_int8t_uint16t_true"],
// ["VCSC_int8t_uint16t_false"],
// ["VCSC_int8t_int32t_true"],
// ["VCSC_int8t_int32t_false"],
// ["VCSC_int8t_uint32t_true"],
// ["VCSC_int8t_uint32t_false"],
// ["VCSC_int8t_int64t_true"],
// ["VCSC_int8t_int64t_false"],
// ["VCSC_int8t_uint64t_true"],
// ["VCSC_int8t_uint64t_false"],
// ["VCSC_uint8t_int8t_true"],
// ["VCSC_uint8t_int8t_false"],
// ["VCSC_uint8t_uint8t_true"],
// ["VCSC_uint8t_uint8t_false"],
// ["VCSC_uint8t_int16t_true"],
// ["VCSC_uint8t_int16t_false"],
// ["VCSC_uint8t_uint16t_true"],
// ["VCSC_uint8t_uint16t_false"],
// ["VCSC_uint8t_int32t_true"],
// ["VCSC_uint8t_int32t_false"],
// ["VCSC_uint8t_uint32t_true"],
// ["VCSC_uint8t_uint32t_false"],
// ["VCSC_uint8t_int64t_true"],
// ["VCSC_uint8t_int64t_false"],
// ["VCSC_uint8t_uint64t_true"],
// ["VCSC_uint8t_uint64t_false"],
// ["VCSC_int16t_int8t_true"],
// ["VCSC_int16t_int8t_false"],
// ["VCSC_int16t_uint8t_true"],
// ["VCSC_int16t_uint8t_false"],
// ["VCSC_int16t_int16t_true"],
// ["VCSC_int16t_int16t_false"],
// ["VCSC_int16t_uint16t_true"],
// ["VCSC_int16t_uint16t_false"],
// ["VCSC_int16t_int32t_true"],
// ["VCSC_int16t_int32t_false"],
// ["VCSC_int16t_uint32t_true"],
// ["VCSC_int16t_uint32t_false"],
// ["VCSC_int16t_int64t_true"],
// ["VCSC_int16t_int64t_false"],
// ["VCSC_int16t_uint64t_true"],
// ["VCSC_int16t_uint64t_false"],
// ["VCSC_uint16t_int8t_true"],
// ["VCSC_uint16t_int8t_false"],
// ["VCSC_uint16t_uint8t_true"],
// ["VCSC_uint16t_uint8t_false"],
// ["VCSC_uint16t_int16t_true"],
// ["VCSC_uint16t_int16t_false"],
// ["VCSC_uint16t_uint16t_true"],
// ["VCSC_uint16t_uint16t_false"],
// ["VCSC_uint16t_int32t_true"],
// ["VCSC_uint16t_int32t_false"],
// ["VCSC_uint16t_uint32t_true"],
// ["VCSC_uint16t_uint32t_false"],
// ["VCSC_uint16t_int64t_true"],
// ["VCSC_uint16t_int64t_false"],
// ["VCSC_uint16t_uint64t_true"],
// ["VCSC_uint16t_uint64t_false"],
// ["VCSC_int32t_int8t_true"],
// ["VCSC_int32t_int8t_false"],
// ["VCSC_int32t_uint8t_true"],
// ["VCSC_int32t_uint8t_false"],
// ["VCSC_int32t_int16t_true"],
// ["VCSC_int32t_int16t_false"],
// ["VCSC_int32t_uint16t_true"],
// ["VCSC_int32t_uint16t_false"],
// ["VCSC_int32t_int32t_true"],
// ["VCSC_int32t_int32t_false"],
// ["VCSC_int32t_uint32t_true"],
// ["VCSC_int32t_uint32t_false"],
// ["VCSC_int32t_int64t_true"],
// ["VCSC_int32t_int64t_false"],
// ["VCSC_int32t_uint64t_true"],
// ["VCSC_int32t_uint64t_false"],
// ["VCSC_uint32t_int8t_true"],
// ["VCSC_uint32t_int8t_false"],
// ["VCSC_uint32t_uint8t_true"],
// ["VCSC_uint32t_uint8t_false"],
// ["VCSC_uint32t_int16t_true"],
// ["VCSC_uint32t_int16t_false"],
// ["VCSC_uint32t_uint16t_true"],
// ["VCSC_uint32t_uint16t_false"],
// ["VCSC_uint32t_int32t_true"],
// ["VCSC_uint32t_int32t_false"],
// ["VCSC_uint32t_uint32t_true"],
// ["VCSC_uint32t_uint32t_false"],
// ["VCSC_uint32t_int64t_true"],
// ["VCSC_uint32t_int64t_false"],
// ["VCSC_uint32t_uint64t_true"],
// ["VCSC_uint32t_uint64t_false"],
// ["VCSC_int64t_int8t_true"],
// ["VCSC_int64t_int8t_false"],
// ["VCSC_int64t_uint8t_true"],
// ["VCSC_int64t_uint8t_false"],
// ["VCSC_int64t_int16t_true"],
// ["VCSC_int64t_int16t_false"],
// ["VCSC_int64t_uint16t_true"],
// ["VCSC_int64t_uint16t_false"],
// ["VCSC_int64t_int32t_true"],
// ["VCSC_int64t_int32t_false"],
// ["VCSC_int64t_uint32t_true"],
// ["VCSC_int64t_uint32t_false"],
// ["VCSC_int64t_int64t_true"],
// ["VCSC_int64t_int64t_false"],
// ["VCSC_int64t_uint64t_true"],
// ["VCSC_int64t_uint64t_false"],
// ["VCSC_uint64t_int8t_true"],
// ["VCSC_uint64t_int8t_false"],
// ["VCSC_uint64t_uint8t_true"],
// ["VCSC_uint64t_uint8t_false"],
// ["VCSC_uint64t_int16t_true"],
// ["VCSC_uint64t_int16t_false"],
// ["VCSC_uint64t_uint16t_true"],
// ["VCSC_uint64t_uint16t_false"],
// ["VCSC_uint64t_int32t_true"],
// ["VCSC_uint64t_int32t_false"],
// ["VCSC_uint64t_uint32t_true"],
// ["VCSC_uint64t_uint32t_false"],
// ["VCSC_uint64t_int64t_true"],
// ["VCSC_uint64t_int64t_false"],
// ["VCSC_uint64t_uint64t_true"],
// ["VCSC_uint64t_uint64t_false"],
// ["VCSC_float_int8t_true"],
// ["VCSC_float_int8t_false"],
// ["VCSC_float_uint8t_true"],
// ["VCSC_float_uint8t_false"],
// ["VCSC_float_int16t_true"],
// ["VCSC_float_int16t_false"],
// ["VCSC_float_uint16t_true"],
// ["VCSC_float_uint16t_false"],
// ["VCSC_float_int32t_true"],
// ["VCSC_float_int32t_false"],
// ["VCSC_float_uint32t_true"],
// ["VCSC_float_uint32t_false"],
// ["VCSC_float_int64t_true"],
// ["VCSC_float_int64t_false"],
// ["VCSC_float_uint64t_true"],
// ["VCSC_float_uint64t_false"],
// ["VCSC_double_int8t_true"],
// ["VCSC_double_int8t_false"],
// ["VCSC_double_uint8t_true"],
// ["VCSC_double_uint8t_false"],
// ["VCSC_double_int16t_true"],
// ["VCSC_double_int16t_false"],
// ["VCSC_double_uint16t_true"],
// ["VCSC_double_uint16t_false"],
// ["VCSC_double_int32t_true"],
// ["VCSC_double_int32t_false"],
// ["VCSC_double_uint32t_true"],
// ["VCSC_double_uint32t_false"],
// ["VCSC_double_int64t_true"],
// ["VCSC_double_int64t_false"],
// ["VCSC_double_uint64t_true"],
// ["VCSC_double_uint64t_false"],
// ["IVCSC_int8t_int8t_true"],
// ["IVCSC_int8t_int8t_false"],
// ["IVCSC_int8t_uint8t_true"],
// ["IVCSC_int8t_uint8t_false"],
// ["IVCSC_int8t_int16t_true"],
// ["IVCSC_int8t_int16t_false"],
// ["IVCSC_int8t_uint16t_true"],
// ["IVCSC_int8t_uint16t_false"],
// ["IVCSC_int8t_int32t_true"],
// ["IVCSC_int8t_int32t_false"],
// ["IVCSC_int8t_uint32t_true"],
// ["IVCSC_int8t_uint32t_false"],
// ["IVCSC_int8t_int64t_true"],
// ["IVCSC_int8t_int64t_false"],
// ["IVCSC_int8t_uint64t_true"],
// ["IVCSC_int8t_uint64t_false"],
// ["IVCSC_uint8t_int8t_true"],
// ["IVCSC_uint8t_int8t_false"],
// ["IVCSC_uint8t_uint8t_true"],
// ["IVCSC_uint8t_uint8t_false"],
// ["IVCSC_uint8t_int16t_true"],
// ["IVCSC_uint8t_int16t_false"],
// ["IVCSC_uint8t_uint16t_true"],
// ["IVCSC_uint8t_uint16t_false"],
// ["IVCSC_uint8t_int32t_true"],
// ["IVCSC_uint8t_int32t_false"],
// ["IVCSC_uint8t_uint32t_true"],
// ["IVCSC_uint8t_uint32t_false"],
// ["IVCSC_uint8t_int64t_true"],
// ["IVCSC_uint8t_int64t_false"],
// ["IVCSC_uint8t_uint64t_true"],
// ["IVCSC_uint8t_uint64t_false"],
// ["IVCSC_int16t_int8t_true"],
// ["IVCSC_int16t_int8t_false"],
// ["IVCSC_int16t_uint8t_true"],
// ["IVCSC_int16t_uint8t_false"],
// ["IVCSC_int16t_int16t_true"],
// ["IVCSC_int16t_int16t_false"],
// ["IVCSC_int16t_uint16t_true"],
// ["IVCSC_int16t_uint16t_false"],
// ["IVCSC_int16t_int32t_true"],
// ["IVCSC_int16t_int32t_false"],
// ["IVCSC_int16t_uint32t_true"],
// ["IVCSC_int16t_uint32t_false"],
// ["IVCSC_int16t_int64t_true"],
// ["IVCSC_int16t_int64t_false"],
// ["IVCSC_int16t_uint64t_true"],
// ["IVCSC_int16t_uint64t_false"],
// ["IVCSC_uint16t_int8t_true"],
// ["IVCSC_uint16t_int8t_false"],
// ["IVCSC_uint16t_uint8t_true"],
// ["IVCSC_uint16t_uint8t_false"],
// ["IVCSC_uint16t_int16t_true"],
// ["IVCSC_uint16t_int16t_false"],
// ["IVCSC_uint16t_uint16t_true"],
// ["IVCSC_uint16t_uint16t_false"],
// ["IVCSC_uint16t_int32t_true"],
// ["IVCSC_uint16t_int32t_false"],
// ["IVCSC_uint16t_uint32t_true"],
// ["IVCSC_uint16t_uint32t_false"],
// ["IVCSC_uint16t_int64t_true"],
// ["IVCSC_uint16t_int64t_false"],
// ["IVCSC_uint16t_uint64t_true"],
// ["IVCSC_uint16t_uint64t_false"],
// ["IVCSC_int32t_int8t_true"],
// ["IVCSC_int32t_int8t_false"],
// ["IVCSC_int32t_uint8t_true"],
// ["IVCSC_int32t_uint8t_false"],
// ["IVCSC_int32t_int16t_true"],
// ["IVCSC_int32t_int16t_false"],
// ["IVCSC_int32t_uint16t_true"],
// ["IVCSC_int32t_uint16t_false"],
// ["IVCSC_int32t_int32t_true"],
// ["IVCSC_int32t_int32t_false"],
// ["IVCSC_int32t_uint32t_true"],
// ["IVCSC_int32t_uint32t_false"],
// ["IVCSC_int32t_int64t_true"],
// ["IVCSC_int32t_int64t_false"],
// ["IVCSC_int32t_uint64t_true"],
// ["IVCSC_int32t_uint64t_false"],
// ["IVCSC_uint32t_int8t_true"],
// ["IVCSC_uint32t_int8t_false"],
// ["IVCSC_uint32t_uint8t_true"],
// ["IVCSC_uint32t_uint8t_false"],
// ["IVCSC_uint32t_int16t_true"],
// ["IVCSC_uint32t_int16t_false"],
// ["IVCSC_uint32t_uint16t_true"],
// ["IVCSC_uint32t_uint16t_false"],
// ["IVCSC_uint32t_int32t_true"],
// ["IVCSC_uint32t_int32t_false"],
// ["IVCSC_uint32t_uint32t_true"],
// ["IVCSC_uint32t_uint32t_false"],
// ["IVCSC_uint32t_int64t_true"],
// ["IVCSC_uint32t_int64t_false"],
// ["IVCSC_uint32t_uint64t_true"],
// ["IVCSC_uint32t_uint64t_false"],
// ["IVCSC_int64t_int8t_true"],
// ["IVCSC_int64t_int8t_false"],
// ["IVCSC_int64t_uint8t_true"],
// ["IVCSC_int64t_uint8t_false"],
// ["IVCSC_int64t_int16t_true"],
// ["IVCSC_int64t_int16t_false"],
// ["IVCSC_int64t_uint16t_true"],
// ["IVCSC_int64t_uint16t_false"],
// ["IVCSC_int64t_int32t_true"],
// ["IVCSC_int64t_int32t_false"],
// ["IVCSC_int64t_uint32t_true"],
// ["IVCSC_int64t_uint32t_false"],
// ["IVCSC_int64t_int64t_true"],
// ["IVCSC_int64t_int64t_false"],
// ["IVCSC_int64t_uint64t_true"],
// ["IVCSC_int64t_uint64t_false"],
// ["IVCSC_uint64t_int8t_true"],
// ["IVCSC_uint64t_int8t_false"],
// ["IVCSC_uint64t_uint8t_true"],
// ["IVCSC_uint64t_uint8t_false"],
// ["IVCSC_uint64t_int16t_true"],
// ["IVCSC_uint64t_int16t_false"],
// ["IVCSC_uint64t_uint16t_true"],
// ["IVCSC_uint64t_uint16t_false"],
// ["IVCSC_uint64t_int32t_true"],
// ["IVCSC_uint64t_int32t_false"],
// ["IVCSC_uint64t_uint32t_true"],
// ["IVCSC_uint64t_uint32t_false"],
// ["IVCSC_uint64t_int64t_true"],
// ["IVCSC_uint64t_int64t_false"],
// ["IVCSC_uint64t_uint64t_true"],
// ["IVCSC_uint64t_uint64t_false"],
// ["IVCSC_float_int8t_true"],
// ["IVCSC_float_int8t_false"],
// ["IVCSC_float_uint8t_true"],
// ["IVCSC_float_uint8t_false"],
// ["IVCSC_float_int16t_true"],
// ["IVCSC_float_int16t_false"],
// ["IVCSC_float_uint16t_true"],
// ["IVCSC_float_uint16t_false"],
// ["IVCSC_float_int32t_true"],
// ["IVCSC_float_int32t_false"],
// ["IVCSC_float_uint32t_true"],
// ["IVCSC_float_uint32t_false"],
// ["IVCSC_float_int64t_true"],
// ["IVCSC_float_int64t_false"],
// ["IVCSC_float_uint64t_true"],
// ["IVCSC_float_uint64t_false"],
// ["IVCSC_double_int8t_true"],
// ["IVCSC_double_int8t_false"],
// ["IVCSC_double_uint8t_true"],
// ["IVCSC_double_uint8t_false"],
// ["IVCSC_double_int16t_true"],
// ["IVCSC_double_int16t_false"],
// ["IVCSC_double_uint16t_true"],
// ["IVCSC_double_uint16t_false"],
// ["IVCSC_double_int32t_true"],
// ["IVCSC_double_int32t_false"],
// ["IVCSC_double_uint32t_true"],
// ["IVCSC_double_uint32t_false"],
// ["IVCSC_double_int64t_true"],
// ["IVCSC_double_int64t_false"],
// ["IVCSC_double_uint64t_true"],
// ["IVCSC_double_uint64t_false"]];
