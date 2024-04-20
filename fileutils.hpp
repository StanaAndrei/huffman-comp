#pragma once

#include <fstream>
#include <ios> 
#include <iostream>

class FileUtils {
public:
    FileUtils() = delete;
    static const std::ios_base::openmode READ_BIN_OPEN = std::ios::in | std::ios::binary;
    static const std::ios_base::openmode WRITE_BIN_OPEN = std::ios::out | std::ios::binary;
    static void openFile(std::fstream &fs, const char *const, std::ios_base::openmode);
};