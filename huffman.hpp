#pragma once
#include <string>
#include <vector>
#include <utility>

using PairChInt = std::pair<char, int>;

class Huffman {
public:
    Huffman() = delete;
    static std::string encode(const std::string&);
    static std::string decode(const std::string&);
private:
    static std::vector<PairChInt> getFreqVec(const std::string&);
};