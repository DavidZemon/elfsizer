/**
 * @file    ElfSizer.cpp
 *
 * @author  David Zemon
 */

#include "ElfSizer.h"

ElfSizer::ElfSizer(const std::string input)
    : m_input(input) {

}

int ElfSizer::run() {
    return BAD_INPUT_FILE;
}

const std::string& ElfSizer::get_input() const {
    return this->m_input;
}
