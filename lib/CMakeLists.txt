
find_package(Qt6 COMPONENTS Core Widgets Svg REQUIRED)


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
target_include_directories(
        ${PROJECT_NAME}
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/extern/FastGaussianBlur
)
if (NOT TARGET nlohmann_json)
    add_subdirectory(extern/json EXCLUDE_FROM_ALL)
    target_link_libraries(${PROJECT_NAME} PUBLIC nlohmann_json)
else ()
    target_link_libraries(${PROJECT_NAME} PUBLIC nlohmann_json)
endif ()

target_link_libraries(${PROJECT_NAME} PUBLIC
        Qt::Core
        Qt::Widgets
        Qt::Svg
)

