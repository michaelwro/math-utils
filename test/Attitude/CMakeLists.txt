# BUILD TESTS ======================================================================================
set(TEST_ATTITUDE_EXEC attitude_test)

# get sources
file(GLOB TEST_LINALG_SRC
    ./*.cpp
    ${MATHUTILS_TEST_DIR}/TestTools/*.cpp
)

add_executable(${TEST_ATTITUDE_EXEC}
    ${TEST_LINALG_SRC}
)

target_include_directories(${TEST_ATTITUDE_EXEC} PUBLIC
    ${CMAKE_SOURCE_DIR}/${INCL_DIR}
    ${MATHUTILS_TEST_DIR}
)

target_link_libraries(${TEST_ATTITUDE_EXEC} PUBLIC
    "$<$<CONFIG:DEBUG>:--coverage>"
    ${MATHUTILS_LIB}
    GTest::gtest_main
)

target_compile_options(${TEST_ATTITUDE_EXEC} PUBLIC
    "$<$<CONFIG:DEBUG>:--coverage>"
)

target_link_options(${TEST_ATTITUDE_EXEC} PUBLIC
    "$<$<CONFIG:DEBUG>:--coverage>"
)


# ADD TESTS ========================================================================================
add_test(NAME ${TEST_ATTITUDE_EXEC}
    COMMAND ${TEST_ATTITUDE_EXEC}
)
