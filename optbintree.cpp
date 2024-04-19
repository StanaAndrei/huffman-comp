#include "optbintree.hpp"

#include <stack>

OptBinTreeNode::OptBinTreeNode(PairByteInt data): data(data), left(nullptr), right(nullptr) {}
OptBinTreeNode::OptBinTreeNode(OptBinTreeNode *left, OptBinTreeNode *right): left(left), right(right) {
    data = PairByteInt(SPEC_BYTE, left->data.second + right->data.second);
}

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

BitArr OptBinTree::getReprOf(BYTE ch) {
    return this->umap[ch];
}

BitArr OptBinTree::serialize() const {
    BitArr bitArr;
    std::stack<OptBinTreeNode*> st;
    st.push(this->root);
    while (!st.empty()) {
        OptBinTreeNode *curr = st.top();
        st.pop();
        if (curr->isLeaf()) {
            bitArr += 1;
            BitArr byteBitArr;
            for (int i = 0; i < BITS_IN_BYTE; i++) {
                byteBitArr += (curr->data.first >> i) & 1;
            }
            bitArr += byteBitArr;
        } else {
            bitArr += 0;
            if (curr->left) {
                st.push(curr->left);
            }
            if (curr->right) {
                st.push(curr->right);
            }
        }
    }
    return bitArr;
}

OptBinTreeNode *OptBinTree::deserializeHelper(const BitArr &bitArr, size_t &index) {
    if (index >= bitArr.getLen()) {
        return nullptr;
    }
    bool isLeaf = bitArr[index++];
    if (isLeaf) {
        BYTE ch = 0;
        for (int i = 0; i < BITS_IN_BYTE; i++) {
            ch |= (bitArr[index++] << i);
        }
        return new OptBinTreeNode(std::make_pair(ch, 0));
    }
    const auto left = deserializeHelper(bitArr, index);
    const auto right = deserializeHelper(bitArr, index);
    return new OptBinTreeNode(left, right);
}

void OptBinTree::deserialize(const BitArr &bitArr) {
    if (bitArr.getLen() == 0) {
        throw new std::invalid_argument("");
    }
    size_t index = 0;
    root = deserializeHelper(bitArr, index);
}

std::ostream& operator << (std::ostream &out, const OptBinTree &optBinTree) {
    BitArr bitArr = optBinTree.serialize();
    out << bitArr;
    return out;
}