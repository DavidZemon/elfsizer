/**
 * @file    Utility.h
 *
 * @author  David Zemon
 */

#pragma once

#include <string>
#include <cassert>
#include <vector>
#include <algorithm>

class Utility {
    public:
        static std::string expand_user(std::string path);

        static std::vector<std::string> *whitespace_split(const std::string &s);

        static bool find(const std::string &searchable, const std::string &target, const bool case_sensitive = true);
};
