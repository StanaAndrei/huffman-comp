#include "huffman.hpp"
#include "optbintree.hpp"

#include <iostream>
#include <unordered_map>
#include <set>

std::unordered_map<char, int> Huffman::getFreq(const std::string &str) {
    std::unordered_map<char, int> freq;
    for (char ch : str) {
        freq[ch]++;
    }
    return freq;
}

std::pair<BitArr, OptBinTree> Huffman::encode(const std::string &str) {
    auto freq = getFreq(str);
    OptBinTree tree;
    Huffman::makeOptBinTree(freq, tree);
    BitArr binArr;
    for (char ch : str) {
        binArr += tree.getReprOf(ch);
    }
    return std::make_pair(binArr, tree);
}

void Huffman::makeOptBinTree(const std::unordered_map<char, int> &freq, OptBinTree &tree) {
    auto cmpF = [](const OptBinTreeNode *a, const OptBinTreeNode *b)->bool {
        return a->data.second <= b->data.second;
    };
    std::set<OptBinTreeNode*, decltype(cmpF)> set(cmpF);
    for (auto it = freq.cbegin(); it != freq.cend(); it++) {
        set.insert(new OptBinTreeNode(*it));
    }
    while (true) {
        OptBinTreeNode *node1 = *set.begin();
        set.erase(set.begin());
        OptBinTreeNode *node2 = *set.begin();
        set.erase(set.begin());
        auto newNode = new OptBinTreeNode(node1, node2);
        set.insert(newNode);
        if (set.size() == 1) {
            break;
        }
    }
    tree.setRoot(*set.begin());//*/
}