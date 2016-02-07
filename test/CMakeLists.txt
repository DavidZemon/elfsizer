add_custom_target(test-all
    COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure)

include_directories("${PROJECT_SOURCE_DIR}/src")
include_directories(SYSTEM "${PROJECT_SOURCE_DIR}/googletest/googletest/include")
include_directories(SYSTEM "${PROJECT_SOURCE_DIR}/cpp-argparse")
include_directories(SYSTEM "${PROJECT_SOURCE_DIR}/teamcity-cpp/common")
include_directories(SYSTEM "${PROJECT_SOURCE_DIR}/teamcity-cpp/gtest")

add_library(teamcity-gtest
    ${PROJECT_SOURCE_DIR}/teamcity-cpp/common/teamcity_messages.cpp
    ${PROJECT_SOURCE_DIR}/teamcity-cpp/gtest/teamcity_gtest.cpp)

find_program(PROPGCC_OBJDUMP propeller-elf-objdump
    PATHS /opt/parallax/bin)
if (PROPGCC_OBJDUMP)
    message("Found propeller-elf-objdump: ${PROPGCC_OBJDUMP}")
else ()
    message(FATAL_ERROR "Can not run unit tests without propeller-elf-objdump")
endif ()

macro(create_test name src1)
    add_executable(${name} ${src1} ${ARGN})
    target_link_libraries(${name} elfsizer gtest pthread teamcity-gtest)
    add_test(NAME ${name}
        COMMAND ${name} ${PROPGCC_OBJDUMP}
        WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")
    add_dependencies(test-all ${name})
endmacro()

create_test(ElfSizerTest ElfSizerTest.cpp)
create_test(ElfSizerBuilderTest ElfSizerBuilderTest.cpp)
create_test(UtilityTest UtilityTest.cpp)
