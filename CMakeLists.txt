cmake_minimum_required(VERSION 3.12)
project(MathUtils LANGUAGES CXX)

include(CTest)

# PROJECT CONFIGURATION ===============================================================================================
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# set path to CMake modules
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/modules/)

# define compiler and preprocessor options
# compile with -DCMAKE_BUILD_TYPE=Release or -DCMAKE_BUILD_TYPE=Debug
set(MATHUTILS_COMPILE_DEFINITIONS_DEBUG "")
set(MATHUTILS_COMPILE_DEFINITIONS_RELEASE "NDEBUG")

# include coverage module
# if(CMAKE_COMPILER_IS_GNUCXX)
#     include(CodeCoverage)
#     set(CODE_COVERAGE_VERBOSE true)

#     set(COVERAGE_EXCLUDES
#         "/usr/*"
#         "*/gtest/*"
#         "${PROJECT_SOURCE_DIR}/include/Internal/*"
#         "${PROJECT_SOURCE_DIR}/test/TestTools/*"
#     )
# endif()

set(MATHUTILS_COMPILE_OPTIONS "-Wall;-Wextra;-Wpedantic;-Wshadow;-Wconversion;-Wdouble-promotion;-Wfloat-equal;-Wundef;-Wformat=2;-fno-common")
set(MATHUTILS_COMPILE_OPTIONS_DEBUG "${MATHUTILS_COMPILE_OPTIONS};-g3;-Werror;-O0;-Wduplicated-cond;-Wcast-align;-Wcast-qual;--coverage")
set(MATHUTILS_COMPILE_OPTIONS_RELEASE "${MATHUTILS_COMPILE_OPTIONS};-O1")

# library name
set(MATHUTILS_LIB "mathutils")
set(MATHUTILS_LIB_OUTPUT_DIR ${PROJECT_BINARY_DIR}/lib/)

# source and include folders
set(SRC_DIR "src/")
set(INCL_DIR "include/")

# folder names for sub-folders
set(ATTITUDE_DIR "Attitude/")
set(LINALG_DIR "LinAlg/")


# BUILD PROJECT =======================================================================================================

# FIND SOURCE FILES
file(GLOB SRC_DIR_SRC
    ${SRC_DIR}/*.cpp
)
file(GLOB ATTITUDE_SRC
    ${SRC_DIR}/${ATTITUDE_DIR}/*.cpp
)

file(GLOB LINALG_SRC
    ${SRC_DIR}/${LINALG_DIR}/*.cpp
)

# # link gcov for debug
# link_libraries("$<$<CONFIG:DEBUG>:gcov>")

# BUILD LIBRARY
add_library(${MATHUTILS_LIB} SHARED
    ${ATTITUDE_SRC}
    ${LINALG_SRC}
    ${SRC_DIR_SRC}
)

target_compile_definitions(${MATHUTILS_LIB} PUBLIC "$<$<CONFIG:DEBUG>:${MATHUTILS_COMPILE_DEFINITIONS_DEBUG}>")
target_compile_definitions(${MATHUTILS_LIB} PUBLIC "$<$<CONFIG:RELEASE>:${MATHUTILS_COMPILE_DEFINITIONS_RELEASE}>")

target_compile_options(${MATHUTILS_LIB} PRIVATE "$<$<CONFIG:DEBUG>:${MATHUTILS_COMPILE_OPTIONS_DEBUG}>")
target_compile_options(${MATHUTILS_LIB} PRIVATE "$<$<CONFIG:RELEASE>:${MATHUTILS_COMPILE_OPTIONS_RELEASE}>")

target_include_directories(${MATHUTILS_LIB} PUBLIC
    ${INCL_DIR}
    # ${INCL_DIR}/${LINALG_DIR}
)
# include_directories(${MATHUTILS_LIB} PUBLIC
#     ${INCL_DIR}
# )

set_target_properties(${MATHUTILS_LIB} PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${MATHUTILS_LIB_OUTPUT_DIR}
)


# ADD TESTS ===========================================================================================================
enable_testing()
add_subdirectory("./test/")
