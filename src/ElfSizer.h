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
        ElfSizer(const std::string &input, const std::string &objdump);

        Map run();

        const std::string &get_input() const;

        const std::string &get_objdump() const;

    protected:
        void readLinesIntoVector(std::vector<std::string> &lines) const;

    protected:
        static bool lineIsHeap(const std::string &line);
        static bool lineIsBss(const std::string &line);
        static int  convertFromHex(const std::string word);

    protected:
        const std::string m_input;
        const std::string m_objdump;
};

