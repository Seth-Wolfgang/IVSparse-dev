# To build, type: cmake -B /path/to/folder/you/want/it/built/in -S .
# Or else you will have 4 new directories and 3 new files in source
# Makefile will be in the build folder
#cmake_minimum_required(VERSION 3.14)
#set(CMAKE_CXX_STANDARD 17)
#project(build)

#find_package(pybind11 REQUIRED)

# add_subdirectory(pybind11)
#pybind11_add_module(PyVSparse ${CMAKE_SOURCE_DIR}/PyVSparse.cpp)


#target_compile_definitions(PyVSparse PRIVATE VERSION_INFO=${EXAMPLE_VERSION_INFO})