# BUILD TESTS =========================================================================================================
set(TEST_ATTITUDE_EXEC test_attitude)

# get sources
file(GLOB TEST_LINALG_SRC
    ./*.cpp
    ${MATHUTILS_TEST_DIR}/Tools/*.cpp
)

add_executable(${TEST_ATTITUDE_EXEC}
    ${TEST_LINALG_SRC}
)

# target_compile_options(${TEST_ATTITUDE_EXEC} PRIVATE
#     ${MATHUTILS_TEST_COMPILE_OPTIONS}
# )

target_include_directories(${TEST_ATTITUDE_EXEC} PUBLIC
    ${CMAKE_SOURCE_DIR}/${INCL_DIR}
    ${MATHUTILS_TEST_DIR}
)

target_link_libraries(${TEST_ATTITUDE_EXEC} PUBLIC
    ${MATHUTILS_LIB}
    GTest::gtest_main
)


# ADD TESTS ===========================================================================================================
add_test(NAME ${TEST_ATTITUDE_EXEC}
    COMMAND ${TEST_ATTITUDE_EXEC}
)
