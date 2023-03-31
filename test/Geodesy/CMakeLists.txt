# BUILD TESTS =========================================================================================================
set(TEST_GEODESY_EXEC geodesy_test)

# get sources
file(GLOB TEST_LINALG_SRC
    ./*.cpp
    ${MATHUTILS_TEST_DIR}/TestTools/*.cpp
)

add_executable(${TEST_GEODESY_EXEC}
    ${TEST_LINALG_SRC}
)

target_include_directories(${TEST_GEODESY_EXEC} PUBLIC
    ${CMAKE_SOURCE_DIR}/${INCL_DIR}
    ${MATHUTILS_TEST_DIR}
)

target_link_libraries(${TEST_GEODESY_EXEC} PUBLIC
    "$<$<CONFIG:DEBUG>:--coverage>"
    ${MATHUTILS_LIB}
    GTest::gtest_main
)

# ADD TESTS ===========================================================================================================
add_test(NAME ${TEST_GEODESY_EXEC}
    COMMAND ${TEST_GEODESY_EXEC}
)
