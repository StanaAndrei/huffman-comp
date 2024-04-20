#pragma once

#include <utility>
#include <unordered_map>
#include <iostream>

#include "bitarr.hpp"
#include "defs.hpp"

using PairByteInt = std::pair<BYTE, int>;
constexpr BYTE SPEC_BYTE = 0;

struct OptBinTreeNode {
    PairByteInt data;
    OptBinTreeNode *left, *right;
    OptBinTreeNode(PairByteInt data);
    OptBinTreeNode(OptBinTreeNode *left, OptBinTreeNode *right);
    bool isLeaf() const;
};

class OptBinTree {
public:
    void setRoot(OptBinTreeNode*);
    BitArr getReprOf(BYTE);
    BitArr serialize() const;
    void deserialize(const BitArr&);
    friend std::ostream& operator << (std::ostream&, const OptBinTree&);
    BYTE iterate(const BitArr&, size_t&) const;
    friend std::istream& operator >> (std::istream&, OptBinTree&);
private:
    OptBinTreeNode *root = nullptr;
    std::unordered_map<BYTE, BitArr> umap;
    void genUMap(OptBinTreeNode*, BitArr);
    OptBinTreeNode *deserializeHelper(const BitArr&, size_t &index);
    BYTE iterateUtil(const OptBinTreeNode *const, const BitArr&, size_t&) const;
};