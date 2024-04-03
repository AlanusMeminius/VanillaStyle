find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Widgets Svg)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Widgets Svg)

file(GLOB_RECURSE SRC
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h"
)
file(GLOB_RECURSE HEADER
        "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h"
)
set(RESOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/res/VanillaStyle.qrc
)

add_library(VanillaStyle STATIC)

target_include_directories(
        ${PROJECT_NAME}
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        PRIVATE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
)

target_sources(
        ${PROJECT_NAME}
        PUBLIC
        ${SRC}
        ${HEADER}
        ${RESOURCES}
)
target_include_directories(
        ${PROJECT_NAME}
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/FastGaussianBlur
)
if (NOT TARGET nlohmann_json)
    add_subdirectory(lib/json EXCLUDE_FROM_ALL)
    target_link_libraries(${PROJECT_NAME} PUBLIC nlohmann_json)
else ()
    target_link_libraries(${PROJECT_NAME} PUBLIC nlohmann_json)
endif ()

target_link_libraries(${PROJECT_NAME}
        PUBLIC
        Qt${QT_VERSION_MAJOR}::Core
        Qt${QT_VERSION_MAJOR}::Widgets
        Qt${QT_VERSION_MAJOR}::Svg
)

set_target_properties(${PROJECT_NAME}
        PROPERTIES
        AUTOMOC ON
        AUTORCC ON
        OUTPUT_NAME ${PROJECT_NAME}
        PROJECT_LABEL ${PROJECT_NAME}
        SOVERSION ${PROJECT_VERSION_MAJOR}
        VERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
        DEBUG_POSTFIX _debug
)

