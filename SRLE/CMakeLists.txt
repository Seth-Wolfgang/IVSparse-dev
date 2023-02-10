# To build, type: cmake -B /path/to/folder/you/want/it/built/in -S .
# Or else you will have 4 new directories and 3 new files in source
# Makefile will be in the build folder

cmake_minimum_required(VERSION 3.14)
project(CSF)
add_executable(main ${CMAKE_SOURCE_DIR}/src/main.cpp)


set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/CMake/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/CMake/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/CMake/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR})
        


include(FetchContent)
FetChContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

FetchContent_MakeAvailable(googletest)
