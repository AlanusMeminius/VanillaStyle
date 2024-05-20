# Make beautiful QT desktop applications quite simple.

## Features
• More beautiful and elegant.

• Highly customizable, simple interface, easy to use.

• Get rid of the CSS stylesheet and achieve a unified UI style through a simpler JSON configuration file.

• Some controls that are not in Qt have been added.

• Cross-platform, support Windows, Linux, and macOS.

## Requirements
• C++20 or later

• Qt 5.15 or later

• Cmake 3.17 or later

## Installation:

1 . Add the VanillaStyle as a Git submodule.
```bash
git submodule add https://github.com/AlanusMeminius/VanillaStyle.git submodules/VanillaStyle
```
2 . Download submodules.
```bash
git submodule update --init --recursive
```
3 . Add the library to Cmake project.
```
add_subdirectory(submodules/VanillaStyle)
```
4 . Link the library.
```
target_link_libraries(${PROJECT_NAME} VanillaStyle)
```
