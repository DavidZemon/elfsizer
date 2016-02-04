include_directories(SYSTEM ${PROJECT_SOURCE_DIR}/cpp-argparse)

add_library(elfsizer ElfSizer ElfSizerBuilder Utility.cpp Utility.h)
target_link_libraries(elfsizer cpp-argparse)

add_executable(elfsizer-bin main)
set_target_properties(elfsizer-bin PROPERTIES OUTPUT_NAME elfsizer)
target_link_libraries(elfsizer-bin elfsizer)
install(TARGETS elfsizer-bin
    DESTINATION bin)
