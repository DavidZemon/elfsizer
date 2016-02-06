/**
 * @file    ElfSizerBuilder.cpp
 *
 * @author  David Zemon
 */

#include <OptionParser.h>
#include "ElfSizerBuilder.h"

ElfSizer *ElfSizerBuilder::build(const int argc, char const *const *const argv) {
    optparse::OptionParser parser;

    parser.add_option("-i", "--input")
        .help("Map file for binary (such as main.rawmap)");
    parser.add_option("-o", "--objdump")
        .help("Path to propeller-elf-objdump (such as /opt/parallax/bin/propeller-elf-objdump)");

    optparse::Values values = parser.parse_args(argc, argv);

    std::string inputFile   = ElfSizerBuilder::getRequiredOption(values, "input",
                                                                 "Input file must be provided as non-empty string");
    std::string objdumpPath = ElfSizerBuilder::getRequiredOption(values, "objdump",
                                                                 "Objdump must be provided as non-empty string");

    return new ElfSizer(inputFile, objdumpPath);
}

std::string ElfSizerBuilder::getRequiredOption(const optparse::Values &values, const std::string &option,
                                               const std::string failureString) {
    if (values.is_set(option)) {
        const std::string inputFile = std::string(values.get(option));
        if (!inputFile.empty())
            return inputFile;
    }
    throw std::invalid_argument(failureString);
}
