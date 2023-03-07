# GET GTEST ===========================================================================================================
# add gtest for unit tests
include(FetchContent)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest/
    GIT_TAG v1.13.0
)

FetchContent_MakeAvailable(googletest)

# directory for test results XML files
# this is so CI pipelines can output to a specified directory
if (NOT MATHUTILS_TEST_REPORT_DIR)
    set(MATHUTILS_TEST_REPORT_DIR ${PROJECT_BINARY_DIR}/test-reports/)
endif()

# MAKE TESTS
add_subdirectory("./LinAlg/")
