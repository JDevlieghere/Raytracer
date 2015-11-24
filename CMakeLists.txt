cmake_minimum_required(VERSION 3.3)
project(Raytracer)

# Version Number
set (VERSION_MAJOR 1)
set (VERSION_MINOR 0)

# Directories
set(SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)
set(HEADER_DIR ${CMAKE_SOURCE_DIR}/include)

# Files
file(GLOB_RECURSE SOURCE_FILES ${SOURCE_DIR}/*.cpp)
file(GLOB_RECURSE HEADER_FILES ${HEADER_DIR}/*.h)


# Include Directories
include_directories(
        ${SOURCE_DIR}
        ${HEADER_DIR})

# Executables
add_executable(Main
        ${SOURCE_FILES}
        ${HEADER_FILES})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
add_executable(Raytracer ${SOURCE_FILES})