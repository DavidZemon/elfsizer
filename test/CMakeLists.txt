add_custom_target(test-all
    COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure)

include_directories(${PROJECT_SOURCE_DIR}/src)

macro(create_test name src1)
    add_executable(${name} ${src1} ${ARGN})
    target_link_libraries(${name} elfsizer gtest pthread)
    add_test(${name} ${name})
    add_dependencies(test-all ${name})
endmacro()

create_test(ElfSizerTest ElfSizerTest.cpp)
create_test(ElfSizerBuilderTest ElfSizerBuilderTest.cpp)
