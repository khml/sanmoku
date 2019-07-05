cmake_minimum_required(VERSION 3.0)

project(ccsanmoku)
set(PYBIND11_CPP_STANDARD -std=c++14)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -O2")
add_subdirectory(pybind11)

file(GLOB SOURCES ../src/Board.*)
file(GLOB BIND_SOURCES *.cpp)

pybind11_add_module(ccsanmoku SHARED ${SOURCES} ${BIND_SOURCES})
