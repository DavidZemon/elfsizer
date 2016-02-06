/**
 * @file    ElfSizerBuilder.h
 *
 * @author  David Zemon
 */

#pragma once

#include "ElfSizer.h"
#include <OptionParser.h>

class ElfSizerBuilder {
    public:
        static ElfSizer *build(const int argc, char const *const *const argv);

    private:
        static std::string getRequiredOption(const optparse::Values &values, const std::string &option,
                                             const std::string failureString);
};
