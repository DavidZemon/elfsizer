/**
 * @file    ElfSizerBuilder.cpp
 *
 * @author  David Zemon
 */

#include <OptionParser.h>
#include "ElfSizerBuilder.h"

ElfSizer *ElfSizerBuilder::build(const int argc, char const* const* const argv) {
    optparse::OptionParser parser;

    optparse::Values values = parser.parse_args(argc, argv);

    if (values.is_set("input")) {
        const std::string inputFile = std::string(values.get("input"));
        if (!inputFile.empty())
            return new ElfSizer(inputFile);
    }

    throw std::invalid_argument("Input file must be provided as non-empty string");
}
