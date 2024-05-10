cmake_minimum_required(VERSION 3.5)
project(homework VERSION 1.0)

add_library(compiler_flags INTERFACE)
target_compile_features(compiler_flags INTERFACE cxx_std_11)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/lib")

add_library(mytinyimg STATIC
    src/image.h
    src/image_load_save.cpp
    src/image_base_operation.cpp
    src/image_resample.cpp
    src/image_filter.cpp
    src/image_harris_corner.cpp
    src/image_match.cpp
    src/matrix.h
    src/matrix.cpp
    src/stb_image.h
    src/stb_image_write.h
)

target_link_libraries(mytinyimg PUBLIC compiler_flags)
target_include_directories(mytinyimg INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
    )


add_executable(test src/test/test.cpp)
target_link_libraries(test PUBLIC mytinyimg compiler_flags)

# add other executable program below