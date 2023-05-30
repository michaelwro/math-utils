#!/bin/bash
# Build and run test coverage report
#
# Code By: Michael Wrona
# Created: 28 May 2023

PROJ_DIR="$( cd -- "$(dirname "$0")" >/dev/null 2>&1 ; pwd -P )/../"

# if not debug build, rebuild
# https://stackoverflow.com/a/36166097
# https://stackabuse.com/how-to-check-if-string-contains-substring-in-bash/
if [[ "$(cmake -L $PROJ_DIR/build | grep CMAKE_BUILD_TYPE)" != *"Debug"* ]]
then
    echo "[WARNING] Not Debug build, rebuilding as Debug build."
    bash $PROJ_DIR/scripts/build-debug.sh
fi

# exit if there was an error
if [$? -ne 0]; then
    echo "[ERROR] Error building code."
    exit 1
fi

# run tests
ctest -V --test-dir $PROJ_DIR/build/ --output-on-failure -T Test

# exit if there was an error
if [$? -ne 0]; then
    echo "[ERROR] Error testing code."
    exit 1
fi

# generate coverage data
lcov --capture --directory $PROJ_DIR/build/ --output-file $PROJ_DIR/build/coverage.info
lcov --remove $PROJ_DIR/build/coverage.info -o $PROJ_DIR/build/lcov.info \
    '/usr/include/*' \
    '/usr/local/include/*' \
    '*/test/*' \
    '*google*'

# generate coverage HTML site
genhtml $PROJ_DIR/build/lcov.info --output-directory $PROJ_DIR/build/coverage_html
