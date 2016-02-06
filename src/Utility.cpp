/**
 * @file    Utility.cpp
 *
 * @author  David Zemon
 */

#include "Utility.h"
#include <sstream>

std::string Utility::expand_user(std::string path) {
    if (!path.empty() && path[0] == '~') {
        assert(path.size() == 1 || path[1] == '/');  // or other error handling

        std::string home = getenv("HOME");
        if ((0 != home.size()) || (0 != (home = getenv("USERPROFILE")).size())) {
            path.replace(0, 1, home);
        } else {
            const std::string homeDrive = getenv("HOMEDRIVE");
            const std::string homePath  = getenv("HOMEPATH");
            assert(homeDrive.size());  // or other error handling
            assert(homePath.size());
            home = homeDrive + homePath;
            path.replace(0, 1, home);
        }
    }
    return path;
}

std::vector<std::string> *Utility::whitespace_split(const std::string &s) {
    std::vector<std::string> *result = new std::vector<std::string>();

    std::stringstream ss(s);
    while (!ss.eof()) {
        std::string item;
        ss >> item;
        if (item.length())
            result->push_back(item);
    }

    return result;
}
