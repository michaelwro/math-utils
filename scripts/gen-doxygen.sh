#!/bin/bash
# Generate Doxygen HTML documentation

PROJ_DIR="$( cd -- "$(dirname "$0")" >/dev/null 2>&1 ; pwd -P )/../"

doxygen $PROJ_DIR/docs/Doxyfile
