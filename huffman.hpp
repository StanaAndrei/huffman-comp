#pragma once
#include <string>
#include <unordered_map>
#include <utility>

#include "optbintree.hpp"
#include "bitarr.hpp"
#include "defs.hpp"

using PairByteInt = std::pair<BYTE, int>;

class Huffman {
public:
    Huffman() = delete;
    static std::pair<OptBinTree, BitArr> encode(const std::vector<BYTE>&);
    static std::vector<BYTE> decode(const std::pair<OptBinTree, BitArr>&);
private:
    static std::unordered_map<BYTE, int> getFreq(const std::vector<BYTE>&);
    static void makeOptBinTree(const std::unordered_map<BYTE, int>&, OptBinTree&);
};