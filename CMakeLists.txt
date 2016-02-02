cmake_minimum_required(VERSION 3.3)
project(elfsizer)
include(CTest)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall")

add_subdirectory(src)
add_subdirectory(test)
include(CMakeCppArgparse.cmake)

# BuildRequires libgtest-dev
