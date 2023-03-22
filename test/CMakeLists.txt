# GET GTEST ===========================================================================================================
# add gtest for unit tests
include(FetchContent)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest/
    GIT_TAG v1.13.0
)

FetchContent_MakeAvailable(googletest)


# MAKE TESTS ==========================================================================================================
link_directories(
    ${MATHUTILS_LIB_OUTPUT_DIR}
)

# test tools dir
set(MATHUTILS_TEST_DIR ${CMAKE_SOURCE_DIR}/test/)

# Make tests in this folder
set(MATHUTILS_TEST_EXEC test_math_utils)
file(GLOB MATHUTILS_TEST_SRC
    ./*.cpp
    ${MATHUTILS_TEST_DIR}/TestTools/*.cpp
)

add_executable(${MATHUTILS_TEST_EXEC}
    ${MATHUTILS_TEST_SRC}
)

target_include_directories(${MATHUTILS_TEST_EXEC} PUBLIC
    ${CMAKE_SOURCE_DIR}/${INCL_DIR}
    ${MATHUTILS_TEST_DIR}
)

target_link_libraries(${MATHUTILS_TEST_EXEC} PUBLIC
    ${MATHUTILS_LIB}
    GTest::gtest_main
)


# MAKE OTHER TESTS ====================================================================================================
add_subdirectory("./LinAlg/")
add_subdirectory("./Attitude/")
