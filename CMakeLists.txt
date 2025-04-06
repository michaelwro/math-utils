cmake_minimum_required(VERSION 3.19)
project(mathutils
    LANGUAGES CXX
    HOMEPAGE_URL https://github.com/michaelwro/math-utils
)

include(CTest)

# set some configs
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)  # for clang-tidy

# source and include folders
set(mathutils_SOURCES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/)

# option to en/disable treating warnings as errors
option(WARNINGS_AS_ERRORS "Treat warnings as errors" OFF)

# define library and get sources
add_library(mathutils STATIC)
add_subdirectory(${mathutils_SOURCES_DIR})

target_compile_features(mathutils PUBLIC cxx_std_17)

# pre-processor definitions
target_compile_definitions(mathutils
    PUBLIC
        $<$<CONFIG:RELEASE>:NDEBUG;>
)

# compile options
target_compile_options(mathutils
    PRIVATE
        -Wall
        -Wextra
        -Wpedantic
        -Wshadow
        -Wconversion
        -Wdouble-promotion
        -Wfloat-equal
        -Wundef
        -Wformat=2
        $<$<CONFIG:DEBUG>:-g3;-O0;-Wcast-align;-Wcast-qual;>
        $<$<CONFIG:RELEASE>:-O2>
        $<$<BOOL:WARNINGS_AS_ERRORS>:-Werror>
)

target_include_directories(mathutils
    PUBLIC
        ${mathutils_SOURCES_DIR}
)

# set_target_properties(mathutils PROPERTIES
#     LIBRARY_OUTPUT_DIRECTORY ${mathutils_LIB_OUTPUT_DIR}
# )

# # add tests
# enable_testing()
# add_subdirectory("./test/")
