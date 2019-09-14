cmake_minimum_required(VERSION 3.0)
set(project sanmoku)
project(${project} CXX)
include_directories(headers)
file(GLOB SOURCES src/*.cpp)

add_executable(${project} ${SOURCES})
target_link_libraries(${project} "${TORCH_LIBRARIES}")
set_property(TARGET ${project} PROPERTY CXX_STANDARD 11)
