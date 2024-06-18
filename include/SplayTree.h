#ifndef SPLAYTREE_H
#define SPLAYTREE_H

#include "TreeNode.h"
#include <string>

class SplayTree {
private:
    TreeNode* root;

    void zig(TreeNode*);
    void zig_zig(TreeNode*);
    void zig_zag(TreeNode*);
    void splay(TreeNode*);

public:
    SplayTree();
    SplayTree(TreeNode*);
    TreeNode* find(const std::string&);
    void insert(const std::string&);
    void Delete(const std::string&);
    void inOrderPrint(bool);
    TreeNode* getRoot() const;
};

#endif // SPLAYTREE_H
