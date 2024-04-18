#pragma once

#include <utility>

using PairChInt = std::pair<char, int>;
constexpr char SPEC_CHAR = -1;

struct OptBinTreeNode {
    PairChInt data;
    OptBinTreeNode *left, *right;
    OptBinTreeNode(PairChInt data);
    OptBinTreeNode(OptBinTreeNode *left, OptBinTreeNode *right);
};

class OptBinTree {
public:
private:
    OptBinTreeNode *root = nullptr;
};