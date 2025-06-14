cmake_minimum_required(VERSION 3.31)

project(stochastic_lib VERSION 1.0)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED true)

include(cmake/doctest.cmake)
enable_testing()

find_package(Python3 3.10 COMPONENTS Interpreter Development NumPy REQUIRED)

message(STATUS "Python executable: '${Python3_EXECUTABLE}'")
message(STATUS "Python include directories: '${Python3_INCLUDE_DIRS}'")
message(STATUS "Python libraries: '${Python3_LIBRARIES}'")
message(STATUS "NumPy include dirs: ${Python3_NumPy_INCLUDE_DIRS}")

include_directories(${Python3_INCLUDE_DIRS} ${Python3_NumPy_INCLUDE_DIRS})

include_directories(include/stochastic)

add_subdirectory(src)
add_subdirectory(examples)
add_subdirectory(tests)
