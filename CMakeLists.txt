cmake_minimum_required(VERSION 3.19)
cmake_policy(SET CMP0076 NEW)
project(Theme VERSION 0.0.1 LANGUAGES CXX)

option(THEME_BUILD_EXAMPLES "Build example" ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if (THEME_BUILD_EXAMPLES)
    add_subdirectory(example)
endif ()