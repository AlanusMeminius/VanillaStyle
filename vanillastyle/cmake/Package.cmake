include(FetchContent)

FetchContent_Declare(
        json
        GIT_REPOSITORY https://github.com/nlohmann/json
        GIT_TAG v3.11.3
)
FetchContent_MakeAvailable(json)
target_link_libraries(${PROJECT_NAME}
        PRIVATE
        nlohmann_json::nlohmann_json
)
FetchContent_Declare(
        fgblur
        GIT_REPOSITORY https://github.com/bfraboni/FastGaussianBlur.git
        GIT_TAG        main
)
FetchContent_MakeAvailable(fgblur)
target_include_directories(
        ${PROJECT_NAME}
        PRIVATE
        ${fgblur_SOURCE_DIR}
)

install(FILES ${fgblur_SOURCE_DIR}/fast_gaussian_blur_template.h DESTINATION include)
