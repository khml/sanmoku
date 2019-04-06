cmake_minimum_required(VERSION 3.0)
project(sammoku CXX)

set(CMAKE_CXX_FLAGS  -std=c++14)

file(GLOB SOURCES src/*.cpp)

add_executable(sanmoku ${SOURCES})