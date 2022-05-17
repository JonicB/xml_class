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

FROM ubuntu
WORKDIR bd
COPY . .
RUN apt-get update
#RUN apt-get install g++
RUN apt -y install build-essential
RUN apt-get install -y cmake
WORKDIR bd
#RUN make .
#RUN cmake --build .
RUN cmake .. && make
#RUN make .
ENTRYPOINT ./main