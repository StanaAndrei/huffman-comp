#include "optbintree.hpp"

OptBinTreeNode::OptBinTreeNode(PairChInt data): data(data), left(nullptr), right(nullptr) {}
OptBinTreeNode::OptBinTreeNode(OptBinTreeNode *left, OptBinTreeNode *right): left(left), right(right) {
    data = PairChInt(SPEC_CHAR, left->data.second + right->data.second);
}