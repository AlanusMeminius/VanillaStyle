cmake_minimum_required(VERSION 3.19)
project(VanillaStyle VERSION 0.0.1 LANGUAGES CXX)

option(BUILD_EXAMPLES "Build example" ON)

set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)


add_subdirectory(lib)

if (BUILD_EXAMPLES)
    add_subdirectory(example)
endif ()