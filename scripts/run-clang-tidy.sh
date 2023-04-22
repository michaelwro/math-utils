#!/bin/bash
# Run clang-tidy analysis
#
# Code By: Michael Wrona
# Created: 22 April 2023

REPO_DIR="$( cd -- "$(dirname "$0")" >/dev/null 2>&1 ; pwd -P )/../"

# build first (to get compile commands)
BUILD_DIR=$REPO_DIR/build/

if [ ! -d "$BUILD_DIR" ]; then
    echo "Build directory does not exist, building."
    bash $REPO_DIR/scripts/debug-build.sh
fi

# run analysis
clang-tidy --config="$(cat $REPO_DIR/.clang-tidy)" \
    -p $BUILD_DIR --quiet \
    $(find $REPO_DIR/src/ $REPO_DIR/include/ -type f \( -iname *.cpp -o -iname *.h \))