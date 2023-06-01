cmake_minimum_required(VERSION 3.9)

project(colorConverters)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(lib)

enable_testing()

add_subdirectory(tests)