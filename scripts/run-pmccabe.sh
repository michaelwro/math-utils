#!/bin/bash
# Run pmccabe cyclomatic complexity tool on project
#
# Code By: Michael Wrona
# Created: 17 March 2023

# get repo base directory
# https://stackoverflow.com/a/4774063
REPO_DIR="$( cd -- "$(dirname "$0")" >/dev/null 2>&1 ; pwd -P )/../"

# find files and run cppcheck
pmccabe $REPO_DIR/src/**/** $REPO_DIR/include/**/** -X | sort -nr
