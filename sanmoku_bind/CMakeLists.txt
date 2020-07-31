cmake_minimum_required(VERSION 3.13)

project(ccsanmoku)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -O2")

file(GLOB SOURCES ../cc/src/sammoku/core/*.cpp)
file(GLOB BIND_SOURCES src/*.cpp)

add_subdirectory(pybind11)
pybind11_add_module(${PROJECT_NAME} SHARED ${SOURCES} ${BIND_SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE ../cc/include)
target_include_directories(${PROJECT_NAME} PRIVATE include)
