# Dockerfile for developing math-utils

ARG UBUNTU_VERSION
FROM docker.io/library/ubuntu:$UBUNTU_VERSION

LABEL AUTHOR="Michael Wrona"

# download packages
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y \
    build-essential \
    clang-format \
    clang-tidy \
    cmake \
    cppcheck \
    doxygen \
    gdb \
    git \
    graphviz \
    lcov \
    nano \
    pmccabe \
    python3-pip \
    python3.10

# install python deps
COPY ./requirements.txt /opt/
RUN python3 -m pip install --disable-pip-version-check --no-cache-dir -r /opt/requirements.txt && \
    rm -rf /opt/requirements.txt
