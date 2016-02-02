cmake_minimum_required(VERSION 3.3)
project(elfsizer)
include(CTest)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

add_subdirectory(src)
add_subdirectory(test)

# BuildRequires libgtest-dev
