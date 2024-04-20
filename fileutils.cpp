#include "fileutils.hpp"

#include <cstdlib>

void FileUtils::openFile(std::fstream &fs, const char *const path, std::ios_base::openmode openmode) {
    fs.exceptions(std::fstream::failbit | std::fstream::badbit);
    try {
        fs.open(path, openmode);
    } catch (std::system_error &e) {
        std::cerr << e.code().message() << '\n';
        exit(1);
    }
}