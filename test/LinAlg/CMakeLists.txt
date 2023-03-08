# BUILD TESTS =========================================================================================================
set(TEST_LINALG_EXEC test_linalg)

# get sources
file(GLOB TEST_LINALG_SRC
    "./*.cpp"
)

add_executable(${TEST_LINALG_EXEC}
    ${TEST_LINALG_SRC}
)

target_include_directories(${TEST_LINALG_EXEC} PUBLIC
    ${CMAKE_SOURCE_DIR}/${INCL_DIR}
)

target_link_libraries(${TEST_LINALG_EXEC} PUBLIC
    GTest::gtest_main
    ${MATHUTILS_LIB}
)

# ADD TESTS ===========================================================================================================
add_test(NAME ${TEST_LINALG_EXEC}
    COMMAND ${TEST_LINALG_EXEC}
)
