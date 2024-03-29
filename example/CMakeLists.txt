cmake_minimum_required(VERSION 3.27)
project(Example)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Gui Widgets Svg)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Gui Widgets Svg)

add_executable(Example
        main.cpp
        MainWindow.cpp
        MainWindow.h
        MainWindow.ui
        res/res.qrc
)
target_link_libraries(Example
        PRIVATE
        VanillaStyle
        Qt::Core
        Qt::Gui
        Qt::Widgets
        Qt::Svg
)
if (NOT TARGET QWindowKit::Core)
    add_subdirectory(lib/qwindowkit EXCLUDE_FROM_ALL)
    target_link_libraries(${PROJECT_NAME} PUBLIC QWindowKit::Core QWindowKit::Widgets)
else ()
    target_link_libraries(${PROJECT_NAME} PUBLIC QWindowKit::Core QWindowKit::Widgets)
endif ()