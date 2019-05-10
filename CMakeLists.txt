cmake_minimum_required(VERSION 3.0)
set(project sanmoku)
project(${project} CXX)

find_package(Torch REQUIRED)

file(GLOB SOURCES src/*.cpp src/*.hpp)

add_executable(${project} ${SOURCES})
target_link_libraries(${project} "${TORCH_LIBRARIES}")
set_property(TARGET ${project} PROPERTY CXX_STANDARD 11)
