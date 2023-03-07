# linalg tests
set(TEST_LINALG_EXEC test_linalg)

# get sources
file(GLOB LINALG_SRC
    "./*.cpp"
)

add_executable(${TEST_LINALG_EXEC}
    ${LINALG_SRC}
)

target_include_directories(${TEST_LINALG_EXEC} PUBLIC
    ${CMAKE_SOURCE_DIR}/${INCL_DIR}
)

target_link_libraries(${TEST_LINALG_EXEC} PUBLIC
    GTest::gtest_main
    # ${MATHUTILS_LIB}
)

target_compile_definitions(${TEST_LINALG_EXEC} PRIVATE MATHUTILS_TEST_REPORT_DIR="${MATHUTILS_TEST_REPORT_DIR}")

add_test(NAME ${TEST_LINALG_EXEC}
    COMMAND ${TEST_LINALG_EXEC}
)
