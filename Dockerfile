# Dockerfile for developing math-utils

FROM ubuntu:22.04

LABEL AUTHOR="Michael Wrona"

# define useful variables
ENV HOME_DIR=/home/math-utils-dev/
ENV DEBIAN_FRONTEND=noninteractive


# download packages
RUN apt-get update && apt-get install -y \
    build-essential \
    git \
    cmake \
    python3.10 \
    python3-pip

# install python deps
WORKDIR /app/

ADD ./requirements.txt /app/
RUN python3 -m pip install -r requirements.txt

# download & install cppcheck static analyzer
RUN git clone https://github.com/danmar/cppcheck.git
RUN cd cppcheck/
RUN git checkout 2.10
RUN mkdir -p build/
RUN cd build/
RUN cmake ..
RUN make -j
RUN make install

# goto home directory!
WORKDIR $HOME_DIR
