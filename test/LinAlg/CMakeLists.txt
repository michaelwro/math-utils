# BUILD TESTS ======================================================================================
set(TEST_LINALG_EXEC linalg_test)

# get sources
file(GLOB TEST_LINALG_SRC
    ./*.cpp
    ${MATHUTILS_TEST_DIR}/TestTools/*.cpp
)

add_executable(${TEST_LINALG_EXEC}
    ${TEST_LINALG_SRC}
)

target_include_directories(${TEST_LINALG_EXEC} PUBLIC
    ${CMAKE_SOURCE_DIR}/${INCL_DIR}
    ${MATHUTILS_TEST_DIR}
)

target_link_libraries(${TEST_LINALG_EXEC} PUBLIC
    "$<$<CONFIG:DEBUG>:--coverage>"
    ${MATHUTILS_LIB}
    GTest::gtest_main
)

target_compile_options(${TEST_LINALG_EXEC} PUBLIC
    "$<$<CONFIG:DEBUG>:--coverage>"
)

target_link_options(${TEST_LINALG_EXEC} PUBLIC
    "$<$<CONFIG:DEBUG>:--coverage>"
)

# ADD TESTS ========================================================================================
add_test(NAME ${TEST_LINALG_EXEC}
    COMMAND ${TEST_LINALG_EXEC}
)
