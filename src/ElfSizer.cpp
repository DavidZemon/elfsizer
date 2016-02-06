/**
 * @file    ElfSizer.cpp
 *
 * @author  David Zemon
 */

#include "ElfSizer.h"
#include "Utility.h"
#include <fstream>
#include <PoppyDebugTools.h>

// FIXME
#include <iostream>

ElfSizer::ElfSizer(const std::string input)
    : m_input(Utility::expand_user(input)) {
    STACK

}

const std::string &ElfSizer::get_input() const {
    STACK
    return this->m_input;
}

ElfSizer::Map ElfSizer::run() {
    STACK

    std::vector<std::string> lines;
    this->readLinesIntoVector(lines);

    Map map;

    const unsigned long totalLines = lines.size();
    for (unsigned int   lineNumber = 0; lineNumber < totalLines; ++lineNumber) {
        const std::string line     = lines[lineNumber];
        const std::string nextLine = lines[lineNumber + 1];

        if (line.length()) {
            const unsigned long indexOfDot = line.find(".");
            if (std::string::npos != indexOfDot) {
                const std::string              lineAfterDot = line.substr(indexOfDot);
                const std::vector<std::string> *words       = Utility::whitespace_split(lineAfterDot);

                if (nullptr != words && 2 < words->size()) {
                    if (ElfSizer::lineIsBss(lineAfterDot)) {
                        map.totalSize += ElfSizer::convertFromHex((*words)[1]);
                    } else if (ElfSizer::lineIsHeap(lineAfterDot)) {
                        // TODO: Why is this commented out? It is commented out in the original SimpleIDE code
                        //codeSize += 4;
                        //memorySize += 4;
                    } else if (lineNumber != (totalLines - 1)) {
                        if (Utility::contains(nextLine, "load", false)) {
                            int lineSize = ElfSizer::convertFromHex((*words)[1]);
                            map.totalSize += lineSize;
                            map.codeSize += lineSize;
                        }
                    }
                }

                if (nullptr != words)
                    delete words;
            }
        }
    }

    return map;
}

void ElfSizer::readLinesIntoVector(std::vector<std::string> &lines) const {
    STACK

    if (!Utility::exists(this->m_input))
        throw std::ios_base::failure("File does not exist (" + this->m_input + ")");

    const std::string command       = "/opt/parallax/bin/propeller-elf-objdump -h " + this->m_input;
    std::stringstream commandOutput = std::stringstream(Utility::exec(command));

    const unsigned int bufferSize = 1024;
    char               buffer[bufferSize];
    while (commandOutput.getline(buffer, bufferSize)) {
        std::string line = buffer;
        lines.push_back(line);
    }
}

bool ElfSizer::lineIsHeap(const std::string &line) {
    STACK
    return Utility::contains(line, "heap", false);
}

bool ElfSizer::lineIsBss(const std::string &line) {
    STACK
    return Utility::contains(line, ".bss", false);
}

int ElfSizer::convertFromHex(const std::string word) {
    size_t charsProcessed;
    try {
        return std::stoi(word, &charsProcessed, 16);
    } catch (std::invalid_argument ignored) {
        return 0;
    }
}
