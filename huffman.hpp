#pragma once
#include <string>
#include <unordered_map>
#include <utility>

#include "optbintree.hpp"
#include "bitarr.hpp"

using PairChInt = std::pair<char, int>;

class Huffman {
public:
    Huffman() = delete;
    static std::pair<OptBinTree, BitArr> encode(const std::string&);
    static std::string decode(const std::string&);
private:
    static std::unordered_map<char, int> getFreq(const std::string&);
    static void makeOptBinTree(const std::unordered_map<char, int>&, OptBinTree&);
};