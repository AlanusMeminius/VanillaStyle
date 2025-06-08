cmake_minimum_required(VERSION 3.19)
project(VanillaStyle VERSION 0.0.1 LANGUAGES CXX)

option(BUILD_EXAMPLES "Build example" OFF)

set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Widgets Svg)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Widgets Svg)

# MSVC并行编译 cmake -j xxx 对于MSVC没有作用
add_compile_options($<$<CXX_COMPILER_ID:MSVC>:/Gm->) #高版本已被废弃，但是低版本的Gm会影响并行
cmake_host_system_information(RESULT CPU_NUMBER_OF_LOGICAL_CORES QUERY NUMBER_OF_LOGICAL_CORES)
add_compile_options($<$<CXX_COMPILER_ID:MSVC>:/MP${CPU_NUMBER_OF_LOGICAL_CORES}>)

add_subdirectory(vanillastyle)

if (BUILD_EXAMPLES)
    add_subdirectory(example)
endif ()
