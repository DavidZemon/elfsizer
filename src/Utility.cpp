/**
 * @file    Utility.cpp
 *
 * @author  David Zemon
 */

#include "Utility.h"
#include <sstream>
#include <PoppyDebugTools.h>
#include <memory>
#include <sys/stat.h>

std::string Utility::expand_user(std::string path) {
    STACK

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
    STACK

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

bool Utility::contains(const std::string &searchable, const std::string &target, const bool case_sensitive) {
    STACK

    if (case_sensitive) {
        return std::string::npos != searchable.find(target);
    } else {
        auto it = std::search(
            searchable.begin(), searchable.end(),
            target.begin(), target.end(),
            [](char ch1, char ch2) { return std::toupper(ch1) == std::toupper(ch2); }
        );
        return (it != searchable.end());
    }
}

std::string Utility::exec(const std::string &command) {
    STACK

    // Taken from http://stackoverflow.com/a/478960/2784641
    FILE                  *pipeFileNumber = popen(command.c_str(), "r");
    std::shared_ptr<FILE> pipe(pipeFileNumber, pclose);
    if (!pipe)
        throw std::ios_base::failure("Failed to open pipe");

    const unsigned int bufferSize = 128;
    char               buffer[bufferSize];
    std::string        result     = "";
    while (!feof(pipe.get()))
        if (fgets(buffer, bufferSize, pipe.get()) != NULL)
            result += buffer;

    return result;
}

bool Utility::exists(const std::string &name) {
    struct stat buffer;
    return (stat(name.c_str(), &buffer) == 0);
}
