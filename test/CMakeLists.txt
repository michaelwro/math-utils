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
add_subdirectory("./LinAlg/")
