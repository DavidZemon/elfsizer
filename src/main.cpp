/**
 * @file    main.cpp
 *
 * @author  David Zemon
 */

#include <iostream>
#include "ElfSizer.h"
#include "ElfSizerBuilder.h"

int main(const int argc, char const *const *const argv) {
    ElfSizer            *sizer = ElfSizerBuilder::build(argc, argv);
    const ElfSizer::Map map    = sizer->run();
    std::cout << "Code size:  " << map.codeSize << std::endl;
    std::cout << "Total size: " << map.totalSize << std::endl;
    return 0;
}
