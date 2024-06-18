#ifndef TREENODE_H
#define TREENODE_H

#include <string>

struct TreeNode {
    std::string key;
    TreeNode* parent;
    TreeNode* left;
    TreeNode* right;

    TreeNode(const std::string& key);
};

#endif // TREENODE_H