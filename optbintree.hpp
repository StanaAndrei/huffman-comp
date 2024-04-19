#pragma once

#include <utility>
#include <unordered_map>

#include "bitarr.hpp"

using PairChInt = std::pair<char, int>;
constexpr char SPEC_CHAR = 0;

struct OptBinTreeNode {
    PairChInt data;
    OptBinTreeNode *left, *right;
    OptBinTreeNode(PairChInt data);
    OptBinTreeNode(OptBinTreeNode *left, OptBinTreeNode *right);
    bool isLeaf() const;
};

class OptBinTree {
public:
    void setRoot(OptBinTreeNode*);
    BitArr getReprOf(char);
    BitArr serialize();
    void deserialize(const BitArr&);
private:
    OptBinTreeNode *root = nullptr;
    std::unordered_map<char, BitArr> umap;
    void genUMap(OptBinTreeNode*, BitArr);
    OptBinTreeNode *deserializeHelper(const BitArr&, size_t &index);
};