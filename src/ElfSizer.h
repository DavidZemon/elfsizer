/**
 * @file    ElfSizerTest.h
 *
 * @author  David Zemon
 */

#pragma once

#include <string>

class ElfSizer {
    public:
        typedef enum {
            NO_ERROR,
            BAD_INPUT_FILE
        } ErrorCode;

    public:
        ElfSizer(const std::string inputFile);

        int run ();

        const std::string& get_input() const;

    protected:
        const std::string m_input;
};

