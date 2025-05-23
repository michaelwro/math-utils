#!/bin/bash
# Run cppcheck static analyzer on project
#
# Code By: Michael Wrona
# Created: 17 March 2023

# get repo base directory
# https://stackoverflow.com/a/4774063
REPO_DIR="$( cd -- "$(dirname "$0")" >/dev/null 2>&1 ; pwd -P )/../"

CPPCHECK_CACHE_DIR=$REPO_DIR/.cppcheck/
# make cache dir if it doesn't exist
mkdir -p $CPPCHECK_CACHE_DIR/

# find project files and run cppcheck
find $REPO_DIR/src/ -type f \( -iname *.cpp \) | \
    cppcheck --file-list=- \
        --quiet \
        --enable=style \
        --check-level=exhaustive \
        --std=c++20 \
        --platform=unix64 \
        --inline-suppr \
        --cppcheck-build-dir=$CPPCHECK_CACHE_DIR \
        -I $REPO_DIR/src/ \
        -i $REPO_DIR/build/ \
        -i $REPO_DIR/test/
