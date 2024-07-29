cmake_minimum_required(VERSION 3.28)
project(raytracer
  VERSION 1.0
  DESCRIPTION "raytracer - A simple ray tracing implementation"
  LANGUAGES CXX
)

# CMake configuration
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "-O2")
set(CMAKE_CXX_FLAGS_DEBUG "-g -O2")
set(CMAKE_CXX_FLAGS_RELEASE "-O2")
    
# Dependencies - None so far

# Library
file(GLOB_RECURSE SOURCES "src/*.cpp")
add_library(RayTracer SHARED ${SOURCES})

# Executable (CLI application)
add_executable(raytracer "main.cpp")
target_link_libraries(raytracer PRIVATE RayTracer)

# Testing
add_subdirectory(tst)
