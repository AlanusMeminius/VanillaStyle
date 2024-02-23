cmake_minimum_required(VERSION 3.27)
project(Example)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

add_subdirectory(lib/qwindowkit EXCLUDE_FROM_ALL)
add_subdirectory(${CMAKE_SOURCE_DIR}/Theme theme)
include_directories(${CMAKE_SOURCE_DIR}/Theme)
#add_subdirectory(../src theme)
find_package(Qt6 COMPONENTS Core Gui Widgets Svg REQUIRED)

add_executable(Example main.cpp
        MainWindow.cpp
        MainWindow.h
        MainWindow.ui
        res/res.qrc
)
target_link_libraries(Example
        theme
        Qt::Core Qt::Gui Qt::Widgets Qt::Svg
        QWindowKit::Widgets
)

