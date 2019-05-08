cmake_minimum_required(VERSION 3.0)
set(project sanmoku)
project(${project} CXX)

add_executable(sanmoku src/Board.cpp src/Board.hpp src/Player.cpp src/Player.hpp src/main.cpp)
set_property(TARGET ${project} PROPERTY CXX_STANDARD 11)
