cmake_minimum_required(VERSION 3.21)
project(sqlite_bd)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_EXE main.cpp)

set(SOURCE_LIB tinyxml2.cpp
        sqlite3.c)

add_library(libs STATIC ${SOURCE_LIB})

add_executable(sqlite_bd main.cpp)

target_link_libraries(sqlite_bd libs)