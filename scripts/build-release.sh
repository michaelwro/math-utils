#!/bin/bash
# Release build project
#
# Code By: Michael Wrona
# Created: 21 April 2023

REPO_DIR="$( cd -- "$(dirname "$0")" >/dev/null 2>&1 ; pwd -P )/../"

cmake --preset release
cmake --build --preset release -j4
