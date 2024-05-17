cmake_minimum_required(VERSION 3.16)
project(VanillaStyleExample)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Gui Widgets Svg)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Gui Widgets Svg)

add_executable(VanillaStyleExample
        main.cpp
        MainWindow.cpp
        MainWindow.h
        MainWindow.ui
        res/res.qrc
)

if (NOT TARGET QWindowKit::Core)
    add_subdirectory(lib/qwindowkit EXCLUDE_FROM_ALL)
endif ()

target_link_libraries(VanillaStyleExample
        PRIVATE
        VanillaStyle
        Qt${QT_VERSION_MAJOR}::Core
        Qt${QT_VERSION_MAJOR}::Gui
        Qt${QT_VERSION_MAJOR}::Widgets
        Qt${QT_VERSION_MAJOR}::Svg
        QWindowKit::Core
        QWindowKit::Widgets
)
