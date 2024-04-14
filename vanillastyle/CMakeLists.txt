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
        ${CMAKE_CURRENT_SOURCE_DIR}/res/VanillaStyleRobotoFont.qrc
        $<$<PLATFORM_ID:Windows>:${CMAKE_CURRENT_SOURCE_DIR}/res/VanillaStyleFont.qrc>
)
set(LIBRAY_NAME VanillaStyle)

add_library(${LIBRAY_NAME} STATIC)
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
endif ()

target_link_libraries(${LIBRAY_NAME}
        PUBLIC
        Qt${QT_VERSION_MAJOR}::Core
        Qt${QT_VERSION_MAJOR}::Widgets
        Qt${QT_VERSION_MAJOR}::Svg
        nlohmann_json
)

set_target_properties(${LIBRAY_NAME}
        PROPERTIES
        AUTOMOC ON
        AUTORCC ON
        OUTPUT_NAME ${LIBRAY_NAME}
        PROJECT_LABEL ${LIBRAY_NAME}
        SOVERSION ${PROJECT_VERSION_MAJOR}
        VERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
        DEBUG_POSTFIX _debug
        PUBLIC_HEADER "${HEADER}"
)

set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/install})

install(
        TARGETS ${LIBRAY_NAME}
        EXPORT ${PROJECT_NAME}Targets
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin
        PUBLIC_HEADER DESTINATION include/${LIBRAY_NAME}
)
#
#install(DIRECTORY include/${LIBRAY_NAME}
#        DESTINATION include
#        FILES_MATCHING PATTERN "*.h"
#)
#
#include(CMakePackageConfigHelpers)
#write_basic_package_version_file(
#        ${LIBRAY_NAME}ConfigVersion.cmake
#        VERSION ${PROJECT_VERSION}
#        COMPATIBILITY AnyNewerVersion
#)
#
#configure_file(
#        cmake/${LIBRAY_NAME}Config.cmake.in
#        ${CMAKE_CURRENT_BINARY_DIR}/${LIBRAY_NAME}/${LIBRAY_NAME}Config.cmake
#        @ONLY
#)
#install(
#        EXPORT ${LIBRAY_NAME}Targets
#        FILE ${LIBRAY_NAME}Targets.cmake
#        NAMESPACE ${LIBRAY_NAME}::
#        DESTINATION lib/cmake/${LIBRAY_NAME}
#)
#install(
#        FILES
#        ${CMAKE_CURRENT_BINARY_DIR}/${LIBRAY_NAME}/${LIBRAY_NAME}Config.cmake
#        ${CMAKE_CURRENT_BINARY_DIR}/${LIBRAY_NAME}/${LIBRAY_NAME}ConfigVersion.cmake
#        DESTINATION lib/cmake/${LIBRAY_NAME}
#)

add_library(${PROJECT_NAME}::${LIBRAY_NAME} ALIAS ${LIBRAY_NAME})