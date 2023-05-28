#!/bin/bash
# Build and run test coverage report
#
# Code By: Michael Wrona
# Created: 28 May 2023

REPO_DIR="$( cd -- "$(dirname "$0")" >/dev/null 2>&1 ; pwd -P )/../"

cmake -B $REPO_DIR/build/ \
    -DCMAKE_BUILD_TYPE=Debug

cmake --build $REPO_DIR/build/ -j4

ctest -V --test-dir ./build/ --output-on-failure -T Test

lcov --capture --directory $REPO_DIR/build/ --output-file $REPO_DIR/build/coverage.info
lcov --remove $REPO_DIR/build/coverage.info -o $REPO_DIR/build/coverage_filtered.info \
    '/usr/include/*' \
    '/usr/local/include/*' \
    '*/test/*' \
    '*google*'
    # '*/build/*' \

genhtml $REPO_DIR/build/coverage_filtered.info --output-directory $REPO_DIR/build/covhtml
