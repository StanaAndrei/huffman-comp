#pragma once
#include <string>
#include <unordered_map>
#include <utility>

using PairChInt = std::pair<char, int>;

class Huffman {
public:
    Huffman() = delete;
    static std::string encode(const std::string&);
    static std::string decode(const std::string&);
private:
    static std::unordered_map<char, int> getFreq(const std::string&);
};