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

template <typename Ts, typename... indexTs, typename compLevels, typename isColMajors>
void generatePyBindClasses(const char* name);

template <typename T, typename indexT, int compressionLevel, bool isColMajor>
void declareOtherFunc(py::module &m, const char* name);

template <typename T, int compLevel>
void generateForEachIndexType(py::module &m);

template <typename T, int compLevel>
void generateForEachOtherType(py::module &m);

// holds a list of types -> declared at compile time
//  typename IT, typename... Ts,



// template <typename T, typename IT>
// struct Generate {
//     static void generateBase(py::module &m, const char* name) {
//         declareBase<T, IT, 2, false>(m, name);
//         declareBase<T, IT, 2, true>(m, name);
//         declareBase<T, IT, 3, false>(m, name);
//         declareBase<T, IT, 3, true>(m, name);
//     }
// };


// template <typename T, typename... ITs>
// struct GenerateGenerater {

//     Generate <T, ITs...> generater;

//     static void generate(py::module &m, const char* name) {
//         generater = Generate<T, ITs...>();
//         generater<T, ITs...>::generate(m, name);
//     }
// };

//    static void generateBase(py::module &m, const char* name) {
//         Generate<T, Ts...> generate = Generate<T, Ts...>(); 
//         generate.generateBase(m, name);
//     }

//     static void generateSelfFunc(py::module &m, const char* name) {
//         Generate<T, Ts...> generate = Generate<T, Ts...>(); 
//         generate.generateSelfFunc(m, name);
//     }



//     static void generateSelfFunc(py::module &m, const char* name) {
//         declareSelfFunc<T, ITs, 2, false>(m, name);
//         declareSelfFunc<T, ITs, 2, true>(m, name);
//         declareSelfFunc<T, ITs, 3, false>(m, name);
//         declareSelfFunc<T, ITs, 3, true>(m, name);
//     }

    // static void generateOtherFunc() {
        // declareOtherFunc<T, ITs..., 2, false>();
        // declareOtherFunc<T, ITs..., 2, true>();
        // declareOtherFunc<T, ITs..., 3, false>();
        // declareOtherFunc<T, ITs..., 3, true>();
    // }

PYBIND11_MODULE(PyVSparse, m) {
    m.doc() = "pybind11 example plugin"; // optional module docstring

[[VCSC],[IVCSC]]

[[int8_t], [uint8_t], [int16_t], [uint16_t], [int32_t], [uint32_t], [int64_t], [uint64_t], [float], [double]]

[[int8_t], [uint8_t], [int16_t], [uint16_t], [int32_t], [uint32_t], [int64_t], [uint64_t]]

[[true],[false]]

    // VCSC
    generateForEachIndexType<int8_t, 2>(m);
    generateForEachIndexType<uint8_t, 2>(m);
    generateForEachIndexType<int16_t, 2>(m);
    generateForEachIndexType<uint16_t, 2>(m);
    generateForEachIndexType<int32_t, 2>(m);
    generateForEachIndexType<uint32_t, 2>(m);
    generateForEachIndexType<int64_t, 2>(m);
    generateForEachIndexType<uint64_t, 2>(m);
    generateForEachIndexType<float, 2>(m);
    generateForEachIndexType<double, 2>(m);

    // IVCSC
    generateForEachIndexType<int8_t, 3>(m);
    generateForEachIndexType<uint8_t, 3>(m);
    generateForEachIndexType<int16_t, 3>(m);
    generateForEachIndexType<uint16_t, 3>(m);
    generateForEachIndexType<int32_t, 3>(m);
    generateForEachIndexType<uint32_t, 3>(m);
    generateForEachIndexType<int64_t, 3>(m);
    generateForEachIndexType<uint64_t, 3>(m);
    generateForEachIndexType<float, 3>(m);
    generateForEachIndexType<double, 3>(m);

    // VCSC
    generateForEachOtherType<int8_t, 2>(m);
    generateForEachOtherType<uint8_t, 2>(m);
    generateForEachOtherType<int16_t, 2>(m);
    generateForEachOtherType<uint16_t, 2>(m);
    generateForEachOtherType<int32_t, 2>(m);
    generateForEachOtherType<uint32_t, 2>(m);
    generateForEachOtherType<int64_t, 2>(m);
    generateForEachOtherType<uint64_t, 2>(m);
    generateForEachOtherType<float, 2>(m);
    generateForEachOtherType<double, 2>(m);

    // IVCSC
    generateForEachOtherType<int8_t, 3>(m);
    generateForEachOtherType<uint8_t, 3>(m);
    generateForEachOtherType<int16_t, 3>(m);
    generateForEachOtherType<uint16_t, 3>(m);
    generateForEachOtherType<int32_t, 3>(m);
    generateForEachOtherType<uint32_t, 3>(m);
    generateForEachOtherType<int64_t, 3>(m);
    generateForEachOtherType<uint64_t, 3>(m);
    generateForEachOtherType<float, 3>(m);
    generateForEachOtherType<double, 3>(m);
    

    
    

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
        .def(py::init<T*, indexT*, indexT*, uint32_t, uint32_t, uint32_t>())
        .def(py::init<std::vector<std::tuple<indexT, indexT, T>>&, uint32_t, uint32_t, uint32_t>())
        // .def(py::init<std::unordered_map<T, std::vector<indexT>>[], uint32_t, uint32_t>()) //<std::unordered_map<T, std::vector<indexT>>[], uint32_t, uint32_t>
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

    // if constexpr (compressionLevel == 2){
            // py::class_<IVSparse::SparseMatrixBase, IVSparse::SparseMatrix<T, indexT, compressionLevel, isColMajor>::InnerIterator>(m, "InnerIterator")
            //     .def(py::init<>)
            //     .def(py::init<IVSparse::SparseMatrix<T, indexT, compressionLevel, isColMajor>&, uint32_t>())
            //     .def("getIndex", &IVSparse::SparseMatrix<T, indexT, compressionLevel, isColMajor>::InnerIterator::getIndex, py::return_value_policy::copy)
            //     .def("outerDim", &IVSparse::SparseMatrix<T, indexT, compressionLevel, isColMajor>::InnerIterator::outerDim, py::return_value_policy::copy)
            //     .def("row", &IVSparse::SparseMatrix<T, indexT, compressionLevel, isColMajor>::InnerIterator::row, py::return_value_policy::copy)
            //     .def("col", &IVSparse::SparseMatrix<T, indexT, compressionLevel, isColMajor>::InnerIterator::col, py::return_value_policy::copy)
            //     .def("value", &IVSparse::SparseMatrix<T, indexT, compressionLevel, isColMajor>::InnerIterator::value, py::return_value_policy::copy)
            //     .def_readwrite("value", &IVSparse::SparseMatrix<T, indexT, compressionLevel, isColMajor>::InnerIterator, "Changes the value of the run", py::arg("newValue"))
            //     .def("isNewRun", &IVSparse::SparseMatrix<T, indexT, compressionLevel, isColMajor>::InnerIterator::isNewRun, py::return_value_policy::copy);

    // }
    // if constexpr(compressionLevel == 3){
    //     py::class<IVSparse::SparseMatrix<T, indexT, compressionLevel, isColMajor>::InnerIterator>(m, "InnerIterator")

    // }
}


// self as in self types T = T 
template <typename T, typename indexT, int compressionLevel, bool isColMajor>
void declareSelfFunc(py::module &m, const char* name){
    py::class_<IVSparse::SparseMatrix<T, indexT, compressionLevel, isColMajor>, IVSparse::SparseMatrixBase>(m, name)
        .def("isColumnMajor", &IVSparse::SparseMatrix<T, indexT, compressionLevel, isColMajor>::isColumnMajor, py::return_value_policy::copy)
        .def("coeff", &IVSparse::SparseMatrix<T, indexT, compressionLevel, isColMajor>::coeff, py::return_value_policy::copy, "Sets value at run of coefficient", py::arg("row").none(false), py::arg("col").none(false))
        .def("isColumnMajor", &IVSparse::SparseMatrix<T, indexT, compressionLevel, isColMajor>::isColumnMajor, py::return_value_policy::copy)
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


        if constexpr(compressionLevel == 2) {
            py::class_<IVSparse::SparseMatrix<T, indexT, compressionLevel, isColMajor>, IVSparse::SparseMatrixBase>(m, name)
                .def("getNumUniqueVals", &IVSparse::SparseMatrix<T, indexT, compressionLevel, isColMajor>::getNumUniqueVals, py::return_value_policy::copy)
                .def("getValues", &IVSparse::SparseMatrix<T, indexT, compressionLevel, isColMajor>::getValues, py::return_value_policy::copy)
                .def("getCounts", &IVSparse::SparseMatrix<T, indexT, compressionLevel, isColMajor>::getCounts, py::return_value_policy::copy)
                .def("getNumIndices", &IVSparse::SparseMatrix<T, indexT, compressionLevel, isColMajor>::getNumIndices, py::return_value_policy::copy)
                .def("getIndices", &IVSparse::SparseMatrix<T, indexT, compressionLevel, isColMajor>::getIndices, py::return_value_policy::copy);
        }
        else if constexpr(compressionLevel == 3){
                py::class_<IVSparse::SparseMatrix<T, indexT, compressionLevel, isColMajor>, IVSparse::SparseMatrixBase>(m, name)
                    .def("vectorPointer", &IVSparse::SparseMatrix<T, indexT, compressionLevel, isColMajor>::vectorPointer, py::return_value_policy::reference)
                    .def("getVectorSize", &IVSparse::SparseMatrix<T, indexT, compressionLevel, isColMajor>::getVectorSize, py::return_value_policy::copy);
        }
}

// For other adding other constructors, basically conversions
template <typename T, typename indexT, int compressionLevel, bool isColMajor>
void declareForOtherTypes(py::module &m, const char* name){
    py::class_<IVSparse::SparseMatrixBase, IVSparse::SparseMatrix<T, indexT, compressionLevel, isColMajor>>(m, name)
        .def(py::init<IVSparse::SparseMatrix<T, uint8_t, 2, false>& >())
        .def(py::init<IVSparse::SparseMatrix<T, uint8_t, 2 >& >())
        .def(py::init<IVSparse::SparseMatrix<T, uint8_t, 3, false>& >())
        .def(py::init<IVSparse::SparseMatrix<T, uint8_t, 3 >& >())
        .def(py::init<IVSparse::SparseMatrix<T, uint16_t, 2, false>& >())
        .def(py::init<IVSparse::SparseMatrix<T, uint16_t, 2 >& >())
        .def(py::init<IVSparse::SparseMatrix<T, uint16_t, 3, false>& >())
        .def(py::init<IVSparse::SparseMatrix<T, uint16_t, 3 >& >())
        .def(py::init<IVSparse::SparseMatrix<T, uint32_t, 2, false>& >())
        .def(py::init<IVSparse::SparseMatrix<T, uint32_t, 2 >& >())
        .def(py::init<IVSparse::SparseMatrix<T, uint32_t, 3, false>& >())
        .def(py::init<IVSparse::SparseMatrix<T, uint32_t, 3 >& >())
        .def(py::init<IVSparse::SparseMatrix<T, uint64_t, 2, false>& >())
        .def(py::init<IVSparse::SparseMatrix<T, uint64_t, 2 >& >())
        .def(py::init<IVSparse::SparseMatrix<T, uint64_t, 3, false>& >())
        .def(py::init<IVSparse::SparseMatrix<T, uint64_t, 3 >& >());
}

template <typename T, int compLevel>
void generateForEachIndexType(py::module &m) {

    const char* format = (compLevel == 2) ? "VCSC_" : "IVCSC_";
    const char* underScore = "_";

    // Builds strings in the format: "[FORMAT]_[TYPE]_[INDEX_TYPE]_[COL/ROW]"
    const char* name1 = std::string(std::string(format) + std::string(typeid(T).name()) + underScore + std::string(typeid(uint8_t).name())+ underScore + std::to_string(compLevel) + std::string("_Row")).data();
    const char* name2 = std::string(std::string(format) + std::string(typeid(T).name()) + underScore + std::string(typeid(uint8_t).name())+ underScore + std::to_string(compLevel) + std::string("_Col")).data();
    const char* name3 = std::string(std::string(format) + std::string(typeid(T).name()) + underScore + std::string(typeid(uint16_t).name())+ underScore + std::to_string(compLevel) + std::string("_Row")).data();
    const char* name4 = std::string(std::string(format) + std::string(typeid(T).name()) + underScore + std::string(typeid(uint16_t).name())+ underScore + std::to_string(compLevel) + std::string("_Col")).data();
    const char* name5 = std::string(std::string(format) + std::string(typeid(T).name()) + underScore + std::string(typeid(uint32_t).name())+ underScore + std::to_string(compLevel) + std::string("_Row")).data();
    const char* name6 = std::string(std::string(format) + std::string(typeid(T).name()) + underScore + std::string(typeid(uint32_t).name())+ underScore + std::to_string(compLevel) + std::string("_Col")).data();
    const char* name7 = std::string(std::string(format) + std::string(typeid(T).name()) + underScore + std::string(typeid(uint64_t).name())+ underScore + std::to_string(compLevel) + std::string("_Row")).data();
    const char* name8 = std::string(std::string(format) + std::string(typeid(T).name()) + underScore + std::string(typeid(uint64_t).name())+ underScore + std::to_string(compLevel) + std::string("_Col")).data();


    // base functions
    declareBase<T, uint8_t, compLevel, false>(m, name1);
    declareBase<T, uint8_t, compLevel, true>(m, name2);
    declareBase<T, uint16_t, compLevel, false>(m, name3);
    declareBase<T, uint16_t, compLevel, true>(m, name4);
    declareBase<T, uint32_t, compLevel, false>(m, name5);
    declareBase<T, uint32_t, compLevel, true>(m, name6);
    declareBase<T, uint64_t, compLevel, false>(m, name7);
    declareBase<T, uint64_t, compLevel, true>(m, name8);

    // self functions
    declareSelfFunc<T, uint8_t, compLevel, false>(m, name1);
    declareSelfFunc<T, uint8_t, compLevel, true>(m, name2);
    declareSelfFunc<T, uint16_t, compLevel, false>(m, name3);
    declareSelfFunc<T, uint16_t, compLevel, true>(m, name4);
    declareSelfFunc<T, uint32_t, compLevel, false>(m, name5);
    declareSelfFunc<T, uint32_t, compLevel, true>(m, name6);
    declareSelfFunc<T, uint64_t, compLevel, false>(m, name7);
    declareSelfFunc<T, uint64_t, compLevel, true>(m, name8);
}

template <typename T, int compLevel>
void generateForEachOtherType(py::module &m) {

    const char* format = (compLevel == 2) ? "VCSC_" : "IVCSC_";
    const char* underScore = "_";

    // Builds strings in the format: "[FORMAT]_[TYPE]_[INDEX_TYPE]_[COL/ROW]"
    const char* name1 = std::string(std::string(format) + std::string(typeid(T).name()) + underScore + std::string(typeid(uint8_t).name())+ underScore + std::to_string(compLevel) + std::string("_Row")).data();
    const char* name2 = std::string(std::string(format) + std::string(typeid(T).name()) + underScore + std::string(typeid(uint8_t).name())+ underScore + std::to_string(compLevel) + std::string("_Col")).data();
    const char* name3 = std::string(std::string(format) + std::string(typeid(T).name()) + underScore + std::string(typeid(uint16_t).name())+ underScore + std::to_string(compLevel) + std::string("_Row")).data();
    const char* name4 = std::string(std::string(format) + std::string(typeid(T).name()) + underScore + std::string(typeid(uint16_t).name())+ underScore + std::to_string(compLevel) + std::string("_Col")).data();
    const char* name5 = std::string(std::string(format) + std::string(typeid(T).name()) + underScore + std::string(typeid(uint32_t).name())+ underScore + std::to_string(compLevel) + std::string("_Row")).data();
    const char* name6 = std::string(std::string(format) + std::string(typeid(T).name()) + underScore + std::string(typeid(uint32_t).name())+ underScore + std::to_string(compLevel) + std::string("_Col")).data();
    const char* name7 = std::string(std::string(format) + std::string(typeid(T).name()) + underScore + std::string(typeid(uint64_t).name())+ underScore + std::to_string(compLevel) + std::string("_Row")).data();
    const char* name8 = std::string(std::string(format) + std::string(typeid(T).name()) + underScore + std::string(typeid(uint64_t).name())+ underScore + std::to_string(compLevel) + std::string("_Col")).data();

    declareOtherFunc<T, uint8_t, compLevel, false>(m, name1);
    declareOtherFunc<T, uint8_t, compLevel, true>(m, name2);
    declareOtherFunc<T, uint16_t, compLevel, false>(m, name3);
    declareOtherFunc<T, uint16_t, compLevel, true>(m, name4);
    declareOtherFunc<T, uint32_t, compLevel, false>(m, name5);
    declareOtherFunc<T, uint32_t, compLevel, true>(m, name6);
    declareOtherFunc<T, uint64_t, compLevel, false>(m, name7);
    declareOtherFunc<T, uint64_t, compLevel, true>(m, name8);
}



// template <typename T, int compressionLevel, bool isColMajor>
// void generateForEachOtherType(py::module &m, const char* name) {
    
//     // base functions
//     declareOtherFunc<T, uint8_t, compressionLevel, isColMajor>(m, name);
//     declareOtherFunc<T, uint16_t, compressionLevel, isColMajor>(m, name);
//     declareOtherFunc<T, uint32_t, compressionLevel, isColMajor>(m, name);
//     declareOtherFunc<T, uint64_t, compressionLevel, isColMajor>(m, name);


        //TO VCSC
        // TO IVCSC
// }




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
