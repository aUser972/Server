cmake_minimum_required(VERSION 3.0)
project(echo-server)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c1y")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -O0 -g")

file(GLOB SOURCES   "connection.hpp"
                    "container.hpp"
                    "iterator.hpp"
                    "allocator.hpp"
                    "main.cpp")

add_executable(echo-server ${SOURCES})