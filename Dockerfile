#FROM rikorose/gcc-cmake
#WORKDIR bd
#COPY . .
#WORKDIR bd
#RUN cmake .. && make
#ENTRYPOINT ./bd
#VOLUME ./build:/main/buil

#FROM rikorose/gcc-cmake
#WORKDIR bd
#COPY . .
#RUN cmake-build-debug/sqlite_bd
#ENTRYPOINT ./cmake-build-debug
#VOLUME ./build:/bd/build

FROM debian:latest
ENV WORKSPACE="/root/bd"
WORKDIR ${WORKSPACE}
COPY . .
RUN apt-get update && \
    apt-get --no-install-recommends install -y \
        gcc \
        g++ \
        make \
        pkg-config \
        cmake

# RUN apt -y install build-essential cmake
#RUN make .
RUN rm -rf build/
WORKDIR ${WORKSPACE}/build
RUN cmake .. && make
RUN cp ../*.xml ../*.db ./
ENTRYPOINT ./sqlite_bd