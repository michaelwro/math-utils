# Math Utilities

[![Build and Test](https://github.com/michaelwro/math-utils/actions/workflows/build-test.yml/badge.svg)](https://github.com/michaelwro/math-utils/actions/workflows/build-test.yml)  [![Pre-Commit](https://github.com/michaelwro/math-utils/actions/workflows/pre-commit.yml/badge.svg?branch=main)](https://github.com/michaelwro/math-utils/actions/workflows/pre-commit.yml)  [![Static Analysis](https://github.com/michaelwro/math-utils/actions/workflows/static-analysis.yml/badge.svg)](https://github.com/michaelwro/math-utils/actions/workflows/static-analysis.yml)

**Created By:** Michael Wrona

A collection of math utilities for MicWro Engineering projects.

## Install Dependencies

```shell
sudo apt-get update
sudo apt-get install -y build-essential cmake lcov gdb
```

## Build Instructions

This project gets compiled into a shared library `libmathutils.so`.

```shell
# Create a build folder at the top-level of the repo.
mkdir build/
cd build/

# Here are a few cmake build commands for the project
cmake ..  # automatically builds in debug mode
cmake .. -DCMAKE_BUILD_TYPE=Debug  # explicitly debug build
cmake .. -DCMAKE_BUILD_TYPE=Release  # release build

# compile
make -j
```

### VS Code Build Tasks

VS Code build tasks are configured for this project. They can be run with `CTRL+SHIFT+B`. Select between debug and release builds.

## Running Tests

Unit tests created with [Google Test](https://github.com/google/googletest) are included in the project.

```shell
cd build/
cmake .. && make -j
ctest
```

## Tests Code Coverage (TODO)

Generate a `lcov` code coverage report with the following commands. NOTE: be sure to `Debug` build and run all tests.

```shell
lcov --base-directory $(pwd) --directory $(pwd)/../ --capture --output-file coverage-results.info &&\

# run tests (debug built)
cd build/
ctest

# generate lcov report
cd ../
lcov --base-directory $(pwd) --directory $(pwd)/../ --capture --output-file coverage-results.info &&\
lcov --remove coverage-results.info '/usr/*' '*/gtest/*' --output-file coverage-results-cleaned.info &&\
genhtml -o coverage-html coverage-results-cleaned.info --legend --title "MathUtils Test Coverage"
```

## Repository

The code repo can be found [here](https://github.com/michaelwro/math-utils).

```shell
git clone https://github.com/michaelwro/math-utils.git
```
