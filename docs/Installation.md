# Installation:

## CMake

### Embedded: 
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

### FetchContent


### External


## Usage:
