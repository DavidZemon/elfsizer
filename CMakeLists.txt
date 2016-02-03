cmake_minimum_required(VERSION 3.3)
project(elfsizer)

# Add unit test support
include(CTest)
enable_testing()
set(BUILD_GTEST ON)
set(BUILD_GMOCK OFF)
add_subdirectory(googletest)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall")

add_subdirectory(src)
add_subdirectory(test)
add_library(cpp-argparse cpp-argparse/OptionParser.cpp)
