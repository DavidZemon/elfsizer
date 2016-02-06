/**
 * @file    ElfSizer.cpp
 *
 * @author  David Zemon
 */

#include "ElfSizer.h"
#include "Utility.h"
#include <fstream>
#include <sstream>

ElfSizer::ElfSizer(const std::string &input, const std::string &objdump)
    : m_input(Utility::expand_user(input)), m_objdump(Utility::expand_user(objdump)) {
}

const std::string &ElfSizer::get_input() const {
    return this->m_input;
}

const std::string &ElfSizer::get_objdump() const {
    return this->m_objdump;
}

ElfSizer::Map ElfSizer::run() {
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
    if (!Utility::exists(this->m_objdump))
        throw std::ios_base::failure("Can not find propeller-elf-objdump (" + this->m_objdump + ")");
    if (!Utility::exists(this->m_input))
        throw std::ios_base::failure("File does not exist (" + this->m_input + ")");

    const std::string command      = this->m_objdump + " -h " + this->m_input;
    const std::string stringOutput = Utility::exec(command);
    std::stringstream streamOutput;
    streamOutput << stringOutput;

    const unsigned int bufferSize = 1024;
    char               buffer[bufferSize];
    while (streamOutput.getline(buffer, bufferSize)) {
        std::string line = buffer;
        lines.push_back(line);
    }
}

bool ElfSizer::lineIsHeap(const std::string &line) {
    return Utility::contains(line, "heap", false);
}

bool ElfSizer::lineIsBss(const std::string &line) {
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
