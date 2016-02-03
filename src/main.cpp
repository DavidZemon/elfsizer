#include "ElfSizer.h"
#include "ElfSizerBuilder.h"
/**
 *
 */

int main (const int argc, char const* const* const argv) {
    ElfSizer *sizer = ElfSizerBuilder::build(argc, argv);
    return sizer->run();
}
