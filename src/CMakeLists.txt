set(SOURCE_FILES main.cpp ElfSizer.cpp ElfSizer.h)
add_executable(elfsizer ${SOURCE_FILES})
install(TARGETS elfsizer
    DESTINATION bin)
