cmake_minimum_required(VERSION 3.15...3.26)
project(PyVSparse LANGUAGES CXX)

find_package(pybind11 REQUIRED)  # or add_subdirectory(pybind11)

set(PROJECT_ROOT "${CMAKE_SOURCE_DIR}/..")
set(IVSPARSE "${PROJECT_ROOT}/IVSparse")
set(SPARSE_MATRIX "${IVSPARSE}/SparseMatrix")

link_directories(${PROJECT_ROOT})

add_compile_options(fopenmp)

pybind11_add_module(PyVSparse ${CMAKE_SOURCE_DIR}/PyVSparse.cpp)

add_library(IVSparse STATIC ${SPARSE_MATRIX} )
set_target_properties(IVSparse PROPERTIES LINKER_LANGUAGE CXX)


target_link_libraries(PyVSparse PRIVATE pybind11::module pybind11::lto pybind11::windows_extras )


pybind11_extension(PyVSparse)

if(NOT MSVC AND NOT ${CMAKE_BUILD_TYPE} MATCHES Debug|RelWithDebInfo)
    # Strip unnecessary sections of the binary on Linux/macOS
    pybind11_strip(PyVSparse)
endif()

target_compile_options(PyVSparse PRIVATE -O2)

find_package(OpenMP)
if(OpenMP_CXX_FOUND)
    target_link_libraries(PyVSparse PUBLIC OpenMP::OpenMP_CXX)
endif()


set_target_properties(PyVSparse PROPERTIES CXX_VISIBILITY_PRESET "hidden"
                                         CUDA_VISIBILITY_PRESET "hidden")
target_compile_definitions(PyVSparse PRIVATE VERSION_INFO=${EXAMPLE_VERSION_INFO})




