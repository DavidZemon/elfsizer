/**
 * @file    main.cpp
 *
 * @author  David Zemon
 */

#include <iostream>
#include <PoppyDebugTools.h>
#include "ElfSizer.h"
#include "ElfSizerBuilder.h"

int main (const int argc, char const* const* const argv) {
    STACK

    try {
        ElfSizer            *sizer = ElfSizerBuilder::build(argc, argv);
        const ElfSizer::Map map    = sizer->run();
        std::cout << "Code size:  " << map.codeSize << std::endl;
        std::cout << "Total size: " << map.totalSize << std::endl;
        return 0;
    } catch (std::exception &e) {
        std::cerr << Stack::GetTraceString();
        std::cerr << e.what();
        return -1;
    }
}
