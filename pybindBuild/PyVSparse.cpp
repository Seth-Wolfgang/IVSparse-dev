#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <pybind11/stl.h>
#include <pybind11/eigen.h>
#include "../IVSparse/SparseMatrix"
#include <any>

namespace py = pybind11;

template <typename T, int compLevel>
void generateForEachIndexType(py::module& m);

template <typename T, typename indexT, int compressionLevel, bool isColMajor>
void declareForOtherTypes(py::class_<IVSparse::SparseMatrix<T, indexT, compressionLevel, isColMajor>>& mat);

template <typename T> 
constexpr const char* returnTypeName();

template <typename T, typename indexT, int compressionLevel, bool isColMajor>
py::class_<IVSparse::SparseMatrix<T, indexT, compressionLevel, isColMajor>> declareSelfFunc(py::module& m);

/*

Make typedefs for all of these

// [[int8_t], [uint8_t], [int16_t], [uint16_t], [int32_t], [uint32_t], [int64_t], [uint64_t], [float], [double]]

// [uint8_t], [uint16_t], [uint32_t], [uint64_t]]

// 2 3

// [[true],[false]]


*/




PYBIND11_MODULE(PyVSparse, m) {
    m.doc() = "pybind11 example plugin"; // optional module docstring

    // #pragma omp parallel sections 
    // {
    //     #pragma omp section 
    //     {
    //         generateForEachIndexType<int8_t, 2>(m);
    //     }
    //     #pragma omp section 
    //     {
            // generateForEachIndexType<uint8_t, 2>(m);
    //     }
    //     #pragma omp section 
    //     {
    //         generateForEachIndexType<int16_t, 2>(m);
    //     }
    //     #pragma omp section 
    //     {
    //         generateForEachIndexType<uint16_t, 2>(m);
    //     }
    //     #pragma omp section 
        // {
            generateForEachIndexType<int32_t, 2>(m);
    //     }
    //     #pragma omp section 
    //     {
    //         generateForEachIndexType<uint32_t, 2>(m);
    //     }
    //     #pragma omp section 
    //     {
    //         generateForEachIndexType<int64_t, 2>(m);
    //     }
    //     #pragma omp section 
    //     {
    //         generateForEachIndexType<uint64_t, 2>(m);
    //     }
    //     #pragma omp section 
    //     {
    //         generateForEachIndexType<float, 2>(m);
    //     }
    //     #pragma omp section 
    //     {
    //         generateForEachIndexType<double, 2>(m);
    //     }
    // }


    // #pragma omp parallel sections 
    // {
    //     #pragma omp section 
    //     {
            // generateForEachIndexType<int8_t, 3>(m);
    //     }
    //     #pragma omp section 
    //     {
            // generateForEachIndexType<uint8_t, 3>(m);
    //     }
    //     #pragma omp section 
    //     {
    //         generateForEachIndexType<int16_t, 3>(m);
    //     }
    //     #pragma omp section 
    //     {
    //         generateForEachIndexType<uint16_t, 3>(m);
    //     }
    //     #pragma omp section 
    //     {
            generateForEachIndexType<int32_t, 3>(m);
    //     }
    //     #pragma omp section 
    //     {
    //         generateForEachIndexType<uint32_t, 3>(m);
    //     }
    //     #pragma omp section 
    //     {
    //         generateForEachIndexType<int64_t, 3>(m);
    //     }
    //     #pragma omp section 
    //     {
    //         generateForEachIndexType<uint64_t, 3>(m);
    //     }
    //     #pragma omp section 
    //     {
    //         generateForEachIndexType<float, 3>(m);
    //     }
    //     #pragma omp section 
    //     {
    //         generateForEachIndexType<double, 3>(m);
    //     }
    // }
};



// self as in self types T = T 
template <typename T, typename indexT, int compressionLevel, bool isColMajor>
py::class_<IVSparse::SparseMatrix<T, indexT, compressionLevel, isColMajor>> declareSelfFunc(py::module& m) {

    const char* format = (compressionLevel == 2) ? "VCSC_" : "IVCSC_";
    const char* isCol = (isColMajor) ? "Col" : "Row";

    std::string uniqueName = format;
    uniqueName += "_";
    uniqueName += returnTypeName<T>();
    uniqueName += "_";
    uniqueName += returnTypeName<indexT>();
    uniqueName += "_";
    uniqueName += isCol;

    py::class_<IVSparse::SparseMatrix<T, indexT, compressionLevel, isColMajor>> mat(m, uniqueName.c_str());
        mat.def(py::init<Eigen::SparseMatrix<T>& >())
        .def(py::init<Eigen::SparseMatrix<T, Eigen::RowMajor>& >())
        .def(py::init<T*, indexT*, indexT*, uint32_t, uint32_t, uint32_t>())
        .def(py::init<std::vector<std::tuple<indexT, indexT, T>>&, uint32_t, uint32_t, uint32_t>())
        .def(py::init<std::unordered_map<T, std::vector<indexT>>*, uint32_t, uint32_t>()) //<std::unordered_map<T, std::vector<indexT>>[], uint32_t, uint32_t> 
        .def(py::init<const char*>())
        .def(py::init<>())
        .def("rows", &IVSparse::SparseMatrix<T, indexT, compressionLevel, isColMajor>::rows, py::return_value_policy::copy) 
        .def("cols", &IVSparse::SparseMatrix<T, indexT, compressionLevel, isColMajor>::cols, py::return_value_policy::copy) 
        .def("innerSize", &IVSparse::SparseMatrix<T, indexT, compressionLevel, isColMajor>::innerSize, py::return_value_policy::copy)
        .def("outerSize", &IVSparse::SparseMatrix<T, indexT, compressionLevel, isColMajor>::outerSize, py::return_value_policy::copy)
        .def("nonZeros", &IVSparse::SparseMatrix<T, indexT, compressionLevel, isColMajor>::nonZeros, py::return_value_policy::copy)
        .def("byteSize", &IVSparse::SparseMatrix<T, indexT, compressionLevel, isColMajor>::byteSize, py::return_value_policy::copy)
        .def("write", &IVSparse::SparseMatrix<T, indexT, compressionLevel, isColMajor>::write, py::arg("filename"))
        .def("print", &IVSparse::SparseMatrix<T, indexT, compressionLevel, isColMajor>::print)
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
            mat.def("getNumUniqueVals", &IVSparse::SparseMatrix<T, indexT, compressionLevel, isColMajor>::getNumUniqueVals, py::return_value_policy::copy)
            .def("getValues", &IVSparse::SparseMatrix<T, indexT, compressionLevel, isColMajor>::getValues, py::return_value_policy::copy)
            .def("getCounts", &IVSparse::SparseMatrix<T, indexT, compressionLevel, isColMajor>::getCounts, py::return_value_policy::copy)
            .def("getNumIndices", &IVSparse::SparseMatrix<T, indexT, compressionLevel, isColMajor>::getNumIndices, py::return_value_policy::copy)
            .def("getIndices", &IVSparse::SparseMatrix<T, indexT, compressionLevel, isColMajor>::getIndices, py::return_value_policy::copy);
        }
        else if constexpr(compressionLevel == 3){
            mat.def("vectorPointer", &IVSparse::SparseMatrix<T, indexT, compressionLevel, isColMajor>::vectorPointer, py::return_value_policy::reference)
            .def("getVectorSize", &IVSparse::SparseMatrix<T, indexT, compressionLevel, isColMajor>::getVectorSize, py::return_value_policy::copy);
        }

    return mat;
}

// For other adding other constructors, basically conversions
// template <typename T, typename indexT, int compressionLevel, bool isColMajor>
// void declareForOtherTypes(py::class_<IVSparse::SparseMatrix<T, indexT, compressionLevel, isColMajor>>& mat) {




//         mat.def(py::init<IVSparse::SparseMatrix<T, uint8_t, 2, isColMajor>&>())
//            .def(py::init<IVSparse::SparseMatrix<T, uint8_t, 3, isColMajor>&>())
//            .def(py::init<IVSparse::SparseMatrix<T, uint16_t,2, isColMajor>&>())
//            .def(py::init<IVSparse::SparseMatrix<T, uint16_t,3, isColMajor>&>())
//            .def(py::init<IVSparse::SparseMatrix<T, uint32_t,2, isColMajor>&>())
//            .def(py::init<IVSparse::SparseMatrix<T, uint32_t,3, isColMajor>&>())
//            .def(py::init<IVSparse::SparseMatrix<T, uint64_t,2, isColMajor>&>())
//            .def(py::init<IVSparse::SparseMatrix<T, uint64_t,3, isColMajor>&>());

//         .def("__mul__", [](IVSparse::SparseMatrix<T, indexT, compressionLevel, isColMajor> self, uint8_t a) {
//             return self * a;
// }

template <typename T, int compLevel>
void generateForEachIndexType(py::module& m) {




    if constexpr (compLevel == 3) {
        py::class_<IVSparse::SparseMatrix<T, uint8_t,  3, false>> mat8  = declareSelfFunc<T, uint8_t , 3, false>(m);
        py::class_<IVSparse::SparseMatrix<T, uint8_t,  3, true >> mat9  = declareSelfFunc<T, uint8_t , 3, true>(m);
        py::class_<IVSparse::SparseMatrix<T, uint16_t, 3, false>> mat10 = declareSelfFunc<T, uint16_t, 3, false>(m);
        py::class_<IVSparse::SparseMatrix<T, uint16_t, 3, true >> mat11 = declareSelfFunc<T, uint16_t, 3, true>(m);
        py::class_<IVSparse::SparseMatrix<T, uint32_t, 3, false>> mat12 = declareSelfFunc<T, uint32_t, 3, false>(m);
        py::class_<IVSparse::SparseMatrix<T, int32_t, 3, false>> mat16 = declareSelfFunc<T, int32_t, 3, false>(m);
        py::class_<IVSparse::SparseMatrix<T, int32_t, 3, true>> mat17 = declareSelfFunc<T, int32_t, 3, true>(m);

        py::class_<IVSparse::SparseMatrix<T, uint32_t, 3, true >> mat13 = declareSelfFunc<T, uint32_t, 3, true>(m);
        py::class_<IVSparse::SparseMatrix<T, uint64_t, 3, false>> mat14 = declareSelfFunc<T, uint64_t, 3, false>(m);
        py::class_<IVSparse::SparseMatrix<T, uint64_t, 3, true >> mat15 = declareSelfFunc<T, uint64_t, 3, true>(m);
    }
    else {
        py::class_<IVSparse::SparseMatrix<T, uint8_t,  2, false>> mat0  = declareSelfFunc<T, uint8_t , 2, false>(m);
        py::class_<IVSparse::SparseMatrix<T, uint8_t,  2, true >> mat1  = declareSelfFunc<T, uint8_t , 2, true>(m);
        py::class_<IVSparse::SparseMatrix<T, uint16_t, 2, false>> mat2  = declareSelfFunc<T, uint16_t, 2, false>(m);
        py::class_<IVSparse::SparseMatrix<T, uint16_t, 2, true >> mat3  = declareSelfFunc<T, uint16_t, 2, true>(m);
        py::class_<IVSparse::SparseMatrix<T, uint32_t, 2, false>> mat4  = declareSelfFunc<T, uint32_t, 2, false>(m);
        py::class_<IVSparse::SparseMatrix<T, uint32_t, 2, true >> mat5  = declareSelfFunc<T, uint32_t, 2, true>(m);
        py::class_<IVSparse::SparseMatrix<T, uint64_t, 2, false>> mat6  = declareSelfFunc<T, uint64_t, 2, false>(m);
        py::class_<IVSparse::SparseMatrix<T, uint64_t, 2, true >> mat7  = declareSelfFunc<T, uint64_t, 2, true>(m);
    }
 

    // declareForOtherTypes<T, uint8_t,  2, false>(mat0 );
    // declareForOtherTypes<T, uint8_t,  2, true >(mat1 );
    // declareForOtherTypes<T, uint16_t, 2, false>(mat2 );
    // declareForOtherTypes<T, uint16_t, 2, true >(mat3 );
    // declareForOtherTypes<T, uint32_t, 2, false>(mat4 );
    // declareForOtherTypes<T, uint32_t, 2, true >(mat5 );
    // declareForOtherTypes<T, uint64_t, 2, false>(mat6 );
    // declareForOtherTypes<T, uint64_t, 2, true >(mat7 );

    // declareForOtherTypes<T, uint8_t,  3, false>(mat8 );
    // declareForOtherTypes<T, uint8_t,  3, true >(mat9 );
    // declareForOtherTypes<T, uint16_t, 3, false>(mat10);
    // declareForOtherTypes<T, uint16_t, 3, true >(mat11);
    // declareForOtherTypes<T, uint32_t, 3, false>(mat12);
    // declareForOtherTypes<T, uint32_t, 3, true >(mat13);
    // declareForOtherTypes<T, uint64_t, 3, false>(mat14);
    // declareForOtherTypes<T, uint64_t, 3, true >(mat15);

}

// template <class T>
// void generateForEachOtherType(py::class_<IVSparse::SparseMatrix<T, indexT, compressionLevel, isColMajor>>& mat) {

//     // self functions

// }


template <typename T> 
constexpr const char* returnTypeName() {

    if constexpr (std::is_same<T, std::int8_t>::value) return "int8_t";
    else if constexpr (std::is_same<T, std::uint8_t>::value) return "uint8_t";
    else if constexpr (std::is_same<T, std::int16_t>::value) return "int16_t";
    else if constexpr (std::is_same<T, std::uint16_t>::value) return "uint16_t";
    else if constexpr (std::is_same<T, std::int32_t>::value) return "int32_t";
    else if constexpr (std::is_same<T, std::uint32_t>::value) return "uint32_t";
    else if constexpr (std::is_same<T, std::int64_t>::value) return "int64_t";
    else if constexpr (std::is_same<T, std::uint64_t>::value) return "uint64_t";
    else if constexpr (std::is_same<T, float>::value) return "float";
    else if constexpr (std::is_same<T, double>::value) return "double";
    else return "unknown";
}
