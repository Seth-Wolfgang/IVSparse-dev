#find_package(Python COMPONENTS Interpreter Development)
#find_package(pybind11 CONFIG)


cmake_minimum_required(VERSION 3.14)
set(CMAKE_CXX_STANDARD 17)
project(build)

find_package(pybind11 REQUIRED)

#add_subdirectory(pybind11)
pybind11_add_module(PyVSparse ${CMAKE_SOURCE_DIR}/PyVSparse.cpp)


target_compile_definitions(PyVSparse PRIVATE VERSION_INFO=${EXAMPLE_VERSION_INFO})