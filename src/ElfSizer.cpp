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
    size_t numberOfCharactersProcessed;

    std::vector<std::string> lines;
    this->readLinesIntoVector(lines);

    Map map;

    for (unsigned int lineNumber = 0; lineNumber < lines.size(); ++lineNumber) {
        std::string line = lines[lineNumber];

        if (line.length() > 0) {
            // TODO: What is `ms`? Can we put some error handling in here?
            const unsigned long indexOfDot = line.find(".");
            if (std::string::npos != indexOfDot) {
                const std::string              ms     = line.substr(indexOfDot);
                const std::vector<std::string> *words = Utility::whitespace_split(ms);

                if (ElfSizer::bssInLine(ms)) {
                    if (2 < words->size()) {
                        try {
                            const std::string sizeInHex = (*words)[1];
                            int               lineSize  = std::stoi(sizeInHex, &numberOfCharactersProcessed, 16);
                            map.totalSize += lineSize;
                        } catch (std::invalid_argument ignored) {
                            // Just move on if string can't be converted
                        }
                    }
                } else if (ElfSizer::lineIsHeap(ms)) {
                    // TODO: Why is this commented out? It is commented out in the original SimpleIDE code
                    //codeSize += 4;
                    //memorySize += 4;
                    break;
                } else if (!lastLine(lines, lineNumber)) {
                    const std::string nextLine = lines[lineNumber + 1];
                    if (Utility::contains(nextLine, "load", false)) {
                        if (2 < words->size()) {
                            try {
                                int lineSize = std::stoi((*words)[1], &numberOfCharactersProcessed, 16);
                                map.totalSize += lineSize;
                                map.codeSize += lineSize;
                            } catch (std::invalid_argument ignored) {
                                // Just move on if string can't be converted
                            }
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

bool ElfSizer::bssInLine(const std::string &ms) {
    STACK
    return Utility::contains(ms, ".bss", false);
}

bool ElfSizer::lineIsHeap(const std::string &ms) {
    STACK
    return Utility::contains(ms, "heap", false);
}

bool ElfSizer::lastLine(const std::vector<std::string> &lines, const unsigned int lineNumber) {
    STACK
    return lineNumber == (lines.size() - 1);
}
