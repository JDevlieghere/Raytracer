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

# Boost
find_package(Boost COMPONENTS program_options REQUIRED)
set(Boost_USE_STATIC_LIBS ON)

# Include Directories
include_directories(
        ${SOURCE_DIR}
        ${HEADER_DIR}
        ${Boost_INCLUDE_DIR})

# Executables
add_executable(Main
        ${SOURCE_FILES}
        ${HEADER_FILES})

# Linking
target_link_libraries(Main 
		${Boost_LIBRARIES})
         
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
target_compile_features(Main PRIVATE cxx_range_for)
add_executable(Raytracer ${SOURCE_FILES})