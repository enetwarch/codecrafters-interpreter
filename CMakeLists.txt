cmake_minimum_required(VERSION 3.13)
set(CMAKE_CXX_STANDARD 23)

project(codecrafters-interpreter)
file(GLOB_RECURSE SOURCE_FILES src/*.cpp src/*.hpp)
add_executable(interpreter ${SOURCE_FILES})
