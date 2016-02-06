/**
 * @file    ElfSizerTest.h
 *
 * @author  David Zemon
 */

#pragma once

#include <string>
#include <vector>

class ElfSizer {
    public:
        struct Map {
            unsigned int totalSize;
            unsigned int codeSize;

            Map() : totalSize(0), codeSize(0) {
            }
        };

    public:
        ElfSizer(const std::string inputFile);

        Map run();

        const std::string &get_input() const;

    protected:
        void readLinesIntoVector(std::vector<std::string> &lines) const;

    protected:
        static bool lineIsHeap(const std::string &ms);
        static bool bssInLine(const std::string &ms);
        static bool lastLine(const std::vector<std::string> &lines, const unsigned int lineNumber);

    protected:
        const std::string m_input;
};

