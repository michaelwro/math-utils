cmake_minimum_required(VERSION 3.12)
project(MathUtils LANGUAGES CXX)


# PROJECT CONFIGURATION ===============================================================================================
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# define compiler and preprocessor options
# compile with -DCMAKE_BUILD_TYPE=Release or -DCMAKE_BUILD_TYPE=Debug
set(MATHUTILS_COMPILE_DEBUG_DEFINITIONS "")
set(MATHUTILS_COMPILE_RELEASE_DEFINITIONS "NDEBUG")

set(MATHUTILS_COMPILE_OPTIONS "-Wall;-Wextra;-Wpedantic;-Wshadow;-Wconversion;-Wdouble-promotion;-Wundef;-Wformat=2;-fno-common")
set(MATHUTILS_COMPILE_DEBUG_OPTIONS "${MATHUTILS_COMPILE_OPTIONS};-g3;-O0;-Werror")
set(MATHUTILS_COMPILE_RELEASE_OPTIONS "${MATHUTILS_COMPILE_OPTIONS};-O1")

# library name
set(MATHUTILS_LIB "mathutils")

# source and include folders
set(SRC_DIR "src/")
set(INCL_DIR "include/")

# folder names for sub-folders
# set(GEODESY_DIR "geodesy/")
set(LINALG_DIR "LinAlg/")


# BUILD PROJECT =======================================================================================================

# # FIND SOURCE FILES
# file(GLOB GEODESY_SRC
#     ${SRC_DIR}/${GEODESY_DIR}/*.cpp
# )

file(GLOB LINALG_SRC
    ${SRC_DIR}/${LINALG_DIR}/*.cpp
)

# BUILD LIBRARY
add_library(${MATHUTILS_LIB} SHARED
    # ${GEODESY_SRC}
    ${LINALG_SRC}
)

target_compile_definitions(${MATHUTILS_LIB} PRIVATE "$<$<CONFIG:DEBUG>:${MATHUTILS_COMPILE_DEBUG_DEFINITIONS}>")
target_compile_definitions(${MATHUTILS_LIB} PRIVATE "$<$<CONFIG:RELEASE>:${MATHUTILS_COMPILE_RELEASE_DEFINITIONS}>")

target_compile_options(${MATHUTILS_LIB} PRIVATE "$<$<CONFIG:DEBUG>:${MATHUTILS_COMPILE_DEBUG_OPTIONS}>")
target_compile_options(${MATHUTILS_LIB} PRIVATE "$<$<CONFIG:RELEASE>:${MATHUTILS_COMPILE_RELEASE_OPTIONS}>")

target_include_directories(${MATHUTILS_LIB} PUBLIC
    # ${INCL_DIR}/${GEODESY_DIR}
    ${INCL_DIR}/${LINALG_DIR}
)

include_directories(${MATHUTILS_LIB} PUBLIC
    ${INCL_DIR}
)


# ADD TESTS ===========================================================================================================
enable_testing()
add_subdirectory("./test/")
