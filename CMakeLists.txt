cmake_minimum_required(VERSION 3.5)
project(newton)

# this works differently
set(CMAKE_VERBOSE_MAKEFILE ON)

include_directories(inc ../../eigen)

# this works differently
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -Wall -std=c++14")

file(GLOB SOURCE_FILES
	src/*
)

add_executable(main ${SOURCE_FILES})
