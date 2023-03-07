# Dockerfile for developing math-utils

FROM ubuntu:22.04

LABEL AUTHOR="Michael Wrona"

# download packages
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y \
    build-essential \
    git \
    cmake \
    cppcheck \
    python3.10 \
    python3-pip

# install python deps
COPY ./requirements.txt /opt/
RUN python3 -m pip install --disable-pip-version-check --no-cache-dir -r /opt/requirements.txt && \
    rm -rf /opt/requirements.txt
