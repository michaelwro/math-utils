# Dockerfile for developing math-utils

ARG UBUNTU_VERSION
FROM ubuntu:22.04

LABEL AUTHOR="Michael Wrona"

# download packages
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y \
    build-essential \
    cmake \
    cppcheck \
    doxygen \
    gdb \
    git \
    lcov \
    nano \
    pmccabe \
    python3-pip \
    python3.10

# install python deps
COPY ./requirements.txt /opt/
RUN python3 -m pip install --disable-pip-version-check --no-cache-dir -r /opt/requirements.txt && \
    rm -rf /opt/requirements.txt

