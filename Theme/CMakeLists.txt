find_package(Qt6 COMPONENTS Core Gui Widgets Svg REQUIRED)
include_directories(.)
file(GLOB_RECURSE SRC "*.cpp")
add_library(theme ${SRC})
target_link_libraries(theme PRIVATE Qt::Core Qt::Gui Qt::Widgets Qt::Svg)



