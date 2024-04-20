#include "optbintree.hpp"

#include <stack>

constexpr int BYTE_SIZE = 8; // Size of a byte in bits
constexpr int SIZE_T_SIZE = sizeof(size_t); // Size of a size_t type in bytes
constexpr int INT_SIZE = sizeof(int);


OptBinTreeNode::OptBinTreeNode(PairByteInt data): data(data), left(nullptr), right(nullptr) {}
OptBinTreeNode::OptBinTreeNode(OptBinTreeNode *left, OptBinTreeNode *right): left(left), right(right) {
    if (left != nullptr && right != nullptr) {
        data = PairByteInt(SPEC_BYTE, left->data.second + right->data.second);
    }
}

void OptBinTree::genUMap(OptBinTreeNode *node, BitArr bitArr) {
    if (node == nullptr) {
        return;
    }
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

std::ostream& operator << (std::ostream &out, const OptBinTree &optBinTree) {
    BitArr bitArr = optBinTree.serialize();
    out << bitArr;
    return out;
}

BYTE OptBinTree::iterateUtil(const OptBinTreeNode *const node, const BitArr &bitArr, size_t &index) const {
    if (node->isLeaf()) {
        return node->data.first;
    }
    if (bitArr[index++]) {
        return iterateUtil(node->right, bitArr, index);
    } else {
        return iterateUtil(node->left, bitArr, index);
    }
}

BYTE OptBinTree::iterate(const BitArr &bitArr, size_t &index) const {
    return iterateUtil(this->root, bitArr, index);
}

std::istream& operator >> (std::istream &in, OptBinTree &optBinTree) {
    BitArr bitArr;
    in >> bitArr;
    optBinTree.deserialize(bitArr);
    return in;
}

using std::cout;
void OptBinTree::print() const {
    cout << "----------------------\n";
    this->printOptBinTreeNode(this->root, 0);
    cout << "----------------------\n";
}

void OptBinTree::printOptBinTreeNode(const OptBinTreeNode *const node, int depth) const {
    if (node == nullptr)
        return;

    // Print the current node's data
    for (int i = 0; i < depth; ++i)
        std::cout << "  "; // Indent based on depth
    if (node->isLeaf()) {
        std::cout << "Leaf: " << static_cast<char>(node->data.first) << ", Frequency: " << node->data.second << std::endl;
    } else {
        std::cout << "Internal Node, Frequency: " << node->data.second << std::endl;
    }

    // Recursively print left and right subtrees
    printOptBinTreeNode(node->left, depth + 1);
    printOptBinTreeNode(node->right, depth + 1);
}

BitArr OptBinTree::serialize() const {
    BitArr bitArr;
    serializeHelper(this->root, bitArr);
    return bitArr;
}

void OptBinTree::serializeHelper(const OptBinTreeNode *const node, BitArr &bitArr) const {
    if (node == nullptr) {
        bitArr += BYTE(MARKER);
        return;
    }
    bitArr += node->data.first;
    serializeHelper(node->left, bitArr);
    serializeHelper(node->right, bitArr);
}

void OptBinTree::deserialize(const BitArr &bitArr) {
    size_t byteId = 0;
    this->deserializeHelper(bitArr, byteId, this->root);
}

void OptBinTree::deserializeHelper(const BitArr &bitArr, size_t &byteId, OptBinTreeNode*& node) {
    if (byteId == bitArr.getNrBytes()) {
        return;
    }
    BYTE val = bitArr.getByte(byteId++);
    if (val == MARKER) {
        return;
    }
    node = new OptBinTreeNode(std::make_pair(val, 0));
    deserializeHelper(bitArr, byteId, node->left);
    deserializeHelper(bitArr, byteId, node->right);
}