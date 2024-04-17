#pragma once

using PairChInt = std::pair<char, int>;
constexpr char SPEC_CHAR = -1;

struct TreeNode {
    PairChInt data;
    TreeNode *left, *right;
    TreeNode(PairChInt data): data(data), left(nullptr), right(nullptr) {}
    TreeNode(PairChInt data, TreeNode *left, TreeNode *right): data(data), left(left), right(right) {}
};

