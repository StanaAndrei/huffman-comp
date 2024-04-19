#include "huffman.hpp"
#include "optbintree.hpp"

#include <iostream>
#include <unordered_map>
#include <set>

std::unordered_map<BYTE, int> Huffman::getFreq(const std::vector<BYTE> &buffer) {
    std::unordered_map<BYTE, int> freq;
    for (auto ch : buffer) {
        freq[ch]++;
    }
    return freq;
}

std::pair<OptBinTree, BitArr> Huffman::encode(const std::vector<BYTE> &buffer) {
    auto freq = getFreq(buffer);
    OptBinTree tree;
    Huffman::makeOptBinTree(freq, tree);
    BitArr bitArr;
    for (auto ch : buffer) {
        bitArr += tree.getReprOf(ch);
    }
    return std::make_pair(tree, bitArr);
}

void Huffman::makeOptBinTree(const std::unordered_map<BYTE, int> &freq, OptBinTree &tree) {
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