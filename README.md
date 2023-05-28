# Math Utilities

**Created By:** Michael Wrona

A collection of C++20 math utilities for MicWro Engineering projects. I add new utilities on an "as-required" basis.

## Getting Started

Below are instruction for getting the project set up.

### Dev Container Setup (Prefered)

I highly recommend using a [VS Code Dev Container](https://code.visualstudio.com/docs/devcontainers/containers) for the project. It will install all required dependencies and set up an Ubuntu dev environment - easy-peasy. Dev Containers require [Docker](https://docs.docker.com/engine/install/), so make sure you have it installed on your system beforehand.

Install the [VS Code Dev Containers](vscode:extension/ms-vscode-remote.remote-containers) extension. Open the Command Palette and run "Dev Containers: Reopen in Container..." to launch the Dev Container.

Install [pre-commit](https://pre-commit.com/) hooks.

```shell
pre-commit install
```

### Manually Install Dependencies

```shell
sudo apt update
sudo apt install -y build-essential cmake git python3 python3-pip cppcheck clang-tidy
python3 -m pip install -r .devcontainer/requirements.txt
pre-commit install
```

## Build Instructions

This project gets compiled into a shared library `build/lib/libmathutils.so`.

### VS Code Build Tasks (Preferred)

VS Code build tasks are configured for this project. They can be run with `CTRL+SHIFT+B`. Select between debug and release builds.

### Build Scripts

```shell
bash scripts/build-debug.sh
bash scripts/build-release.sh
```

## Doxygen Site

Find the Doxygen site at [https://michaelwro.github.io/math-utils/files.html](https://michaelwro.github.io/math-utils/files.html)

## Dev Workflow

### Unit Tests

Unit tests created with [Google Test](https://github.com/google/googletest) are included in the project. In the context of math utilities, tests are useful for verifying functions produce correct results. Unit tests also ensure changes "here" don't affect things "over there." Try to make at least one test for every utility.

I require pull requests to pass all tests.

```shell
# run tests
cd build/
ctest
```

### Pre-Commit

I use [pre-commit](https://pre-commit.com/) to run tasks such as removing trailing whitespace, ensuring structured text files are parsable, etc. See `.pre-commit-config.yaml` for the complete list of tasks.

I require pull requests to pass pre-commit checks.

```shell
# install pre-commit hooks into the repo
pre-commit install
```

### Static Analysis

I use [cppcheck](https://cppcheck.sourceforge.io/) and [clang-tidy](https://clang.llvm.org/extra/clang-tidy/) for static analysis. I require pull requests to pass cppcheck `style` and `warning` checks. Releases must pass clang-tidy checks. See `.clang-tidy` for the list of checks.

```shell
# run cppcheck
bash scripts/run-cppcheck.sh

# run clang-tidy
bash scripts/run-clang-tidy.sh
```

### Complexity

I use [pmccabe](https://manpages.ubuntu.com/manpages/focal/man1/pmccabe.1.html) to compute function cyclomatic complexity and line counts. I try to keep function complexity below 15.

```shell
# run pmccabe
bash scripts/run-pmccabe.sh
```

## Repository

The code repo can be found [here](https://github.com/michaelwro/math-utils).

```shell
git clone https://github.com/michaelwro/math-utils.git
```
