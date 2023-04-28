c#!/bin/bash
# Run cppcheck static analyzer on project
#
# Code By: Michael Wrona
# Created: 17 March 2023

# get repo base directory
# https://stackoverflow.com/a/4774063
REPO_DIR="$( cd -- "$(dirname "$0")" >/dev/null 2>&1 ; pwd -P )/../"

# find project files and run cppcheck
find $REPO_DIR/src/ $REPO_DIR/include/ -type f \( -iname *.cpp -o -iname *.h \) | \
    cppcheck --file-list=- \
        --enable=style,warning \
        --language=c++ \
        --std=c++17 \
        --platform=unix64 \
        --inline-suppr \
        -I $REPO_DIR/include/ \
        -i $REPO_DIR/build/ \
        -i $REPO_DIR/test/
