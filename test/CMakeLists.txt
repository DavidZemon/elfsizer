enable_testing()

find_package(GTest REQUIRED)

add_custom_target(test-all
    COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure)

include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(SYSTEM ${GTEST_INCLUDE_DIRS})

add_executable(ElfSizerTest ElfSizerTest.cpp)
target_link_libraries(ElfSizerTest elfsizer ${GTEST_LIBRARIES} pthread)
add_test(ElfSizerTest ElfSizerTest)
add_dependencies(test-all ElfSizerTest)
