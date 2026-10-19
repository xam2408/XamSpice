cmake_minimum_required(VERSION 3.20)
project(XamSpice CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)
include_directories(ext)

add_executable(XamSpice
    src/main.cpp
 "src/Simulation/Circuit.cpp" )