#include "huffman.hpp"

#include <algorithm>
#include <unordered_map>

std::vector<PairChInt> Huffman::getFreqVec(const std::string &str) {
    std::unordered_map<char, int> freq;
    for (char ch : str) {
        freq[ch]++;
    }
    std::vector<PairChInt> freqVec;
    for (auto it = freq.cbegin(); it != freq.cend(); it++) {
        freqVec.push_back(*it);
    }
    return freqVec;
}

