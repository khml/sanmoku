cmake_minimum_required(VERSION 3.13)

project(play)

file(GLOB SOURCES src/sanmoku/*.cpp src/sanmoku/core/*.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME})
target_include_directories(${PROJECT_NAME} PRIVATE include/)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 11)
