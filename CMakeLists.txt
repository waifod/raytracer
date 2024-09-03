cmake_minimum_required(VERSION 3.25)
project(rtnya
  VERSION 1.0
  DESCRIPTION "rtnya - A simple ray tracer nya~"
  LANGUAGES CXX
)

# CMake configuration
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "-O3")
set(CMAKE_CXX_FLAGS_DEBUG "-g -O3")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

# Dependencies - None so far

# Library
file(GLOB_RECURSE SOURCES "src/*")
add_library(RTNyaLib SHARED ${SOURCES})

# Executable (CLI application)
add_executable(rtnya "main.cpp")
target_link_libraries(rtnya PRIVATE RTNyaLib)

# Testing
add_subdirectory(tst)
