cmake_minimum_required(VERSION 3.0)

project(sanmoku)

include_directories(cc/include)
file(GLOB SOURCES cc/src/sanmoku/*.cpp cc/src/sanmoku/core/*.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME})
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 11)
