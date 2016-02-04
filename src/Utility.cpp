/**
 * @file    Utility
 *
 * @author  David Zemon
 */

#include "Utility.h"

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
