
find_package(Qt6 COMPONENTS Core Widgets Svg REQUIRED)

add_subdirectory(extern/json EXCLUDE_FROM_ALL)

file(GLOB_RECURSE SRC
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h"
)
file(GLOB_RECURSE HEADER
        "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h"
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
)

target_link_libraries(${PROJECT_NAME} PUBLIC
        nlohmann_json::nlohmann_json
        Qt::Core
        Qt::Widgets
        Qt::Svg
)

