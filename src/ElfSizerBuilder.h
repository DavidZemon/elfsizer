/**
 * @file    ElfSizerBuilder.h
 *
 * @author  David Zemon
 */

#pragma once

#include "ElfSizer.h"

class ElfSizerBuilder {
    public:
        static ElfSizer *build(const int argc, char const* const* const argv);
};

