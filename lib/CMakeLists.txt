
find_package(Qt6 COMPONENTS Core Widgets Svg REQUIRED)

set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
add_subdirectory(extern/json EXCLUDE_FROM_ALL)

file(GLOB_RECURSE SRC
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)
file(GLOB_RECURSE HEADER
        "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h"
)

add_library(${PROJECT_NAME} STATIC)
target_include_directories(
        ${PROJECT_NAME}
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src>
)

target_sources(
        ${PROJECT_NAME}
        PUBLIC
        ${HEADER}
        ${SRC}
)

target_link_libraries(${PROJECT_NAME} PUBLIC
        nlohmann_json::nlohmann_json
        Qt::Core
        Qt::Widgets
        Qt::Svg
)


