add_custom_target(test-all
    COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure)

include_directories("${PROJECT_SOURCE_DIR}/src")
include_directories(SYSTEM "${PROJECT_SOURCE_DIR}/googletest/googletest/include")
include_directories(SYSTEM ${PROJECT_SOURCE_DIR}/cpp-argparse)

macro(create_test name src1)
    add_executable(${name} ${src1} ${ARGN})
    target_link_libraries(${name} elfsizer gtest pthread)
    add_test(NAME ${name}
        COMMAND ${name}
        WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")
    add_dependencies(test-all ${name})
endmacro()

create_test(ElfSizerTest ElfSizerTest.cpp)
create_test(ElfSizerBuilderTest ElfSizerBuilderTest.cpp)
create_test(UtilityTest UtilityTest.cpp)
