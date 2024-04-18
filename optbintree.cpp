#include "optbintree.hpp"

OptBinTreeNode::OptBinTreeNode(PairChInt data): data(data), left(nullptr), right(nullptr) {}
OptBinTreeNode::OptBinTreeNode(OptBinTreeNode *left, OptBinTreeNode *right): left(left), right(right) {
    data = PairChInt(SPEC_CHAR, left->data.second + right->data.second);
}

#include <cstdlib>
void OptBinTree::genUMap(OptBinTreeNode *node, BitArr bitArr) {
    if (node->isLeaf()) {
        this->umap[node->data.first] = bitArr;
        return;
    }
    this->genUMap(node->left, bitArr + 0);
    this->genUMap(node->right, bitArr + 1);
}

void OptBinTree::setRoot(OptBinTreeNode *root) {
    this->root = root;
    BitArr bitArr;
    this->genUMap(this->root, bitArr);
}

bool OptBinTreeNode::isLeaf() const {
    return !this->left && !this->right;
}

BitArr OptBinTree::getReprOf(char ch) {
    return this->umap[ch];
}