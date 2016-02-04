/**
 * @file    Utility.h
 *
 * @author  David Zemon
 */

#pragma once

#include <string>
#include <cassert>

class Utility {
    public:
        static std::string expand_user(std::string path);
};
