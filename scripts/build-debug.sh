#!/bin/bash
# Debug build project
#
# Code By: Michael Wrona
# Created: 21 April 2023

REPO_DIR="$( cd -- "$(dirname "$0")" >/dev/null 2>&1 ; pwd -P )/../"

cmake -B $REPO_DIR/build/ -DCMAKE_BUILD_TYPE=Debug
cmake --build $REPO_DIR/build/ -j
