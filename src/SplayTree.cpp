#include "../include/SplayTree.h"

void SplayTree::zig(TreeNode* node) {
    TreeNode* parent = node->parent;
    if (parent->left == node) {
        TreeNode* rightChild = node->right;
        node->parent = nullptr;
        node->right = parent;
        parent->parent = node;
        parent->left = rightChild;
        if (rightChild) rightChild->parent = parent;
    } else {
        TreeNode* leftChild = node->left;
        node->parent = nullptr;
        node->left = parent;
        parent->parent = node;
        parent->right = leftChild;
        if (leftChild) leftChild->parent = parent;
    }
}

void SplayTree::zig_zig(TreeNode* node) {
    TreeNode* parent = node->parent;
    TreeNode* grandparent = parent->parent;
    if (parent->left == node) {
        TreeNode* rightChild = node->right;
        TreeNode* leftChildOfParent = parent->right;
        node->parent = grandparent->parent;
        node->right = parent;
        parent->parent = node;
        parent->left = rightChild;
        parent->right = grandparent;
        grandparent->parent = parent;
        grandparent->left = leftChildOfParent;
        if (node->parent) {
            if (node->parent->left == grandparent) node->parent->left = node;
            else node->parent->right = node;
        }
        if (rightChild) rightChild->parent = parent;
        if (leftChildOfParent) leftChildOfParent->parent = grandparent;
    } else {
        TreeNode* leftChild = node->left;
        TreeNode* rightChildOfParent = parent->left;
        node->parent = grandparent->parent;
        node->left = parent;
        parent->parent = node;
        parent->right = leftChild;
        parent->left = grandparent;
        grandparent->parent = parent;
        grandparent->right = rightChildOfParent;
        if (node->parent) {
            if (node->parent->left == grandparent) node->parent->left = node;
            else node->parent->right = node;
        }
        if (leftChild) leftChild->parent = parent;
        if (rightChildOfParent) rightChildOfParent->parent = grandparent;
    }
}

void SplayTree::zig_zag(TreeNode* node) {
    TreeNode* parent = node->parent;
    TreeNode* grandparent = parent->parent;
    if (parent->right == node) {
        TreeNode* leftChild = node->left;
        TreeNode* rightChild = node->right;
        node->parent = grandparent->parent;
        node->left = parent;
        node->right = grandparent;
        parent->parent = node;
        parent->right = leftChild;
        grandparent->parent = node;
        grandparent->left = rightChild;
        if (node->parent) {
            if (node->parent->left == grandparent) node->parent->left = node;
            else node->parent->right = node;
        }
        if (leftChild) leftChild->parent = parent;
        if (rightChild) rightChild->parent = grandparent;
    } else {
        TreeNode* leftChild = node->left;
        TreeNode* rightChild = node->right;
        node->parent = grandparent->parent;
        node->left = grandparent;
        node->right = parent;
        parent->parent = node;
        parent->left = rightChild;
        grandparent->parent = node;
        grandparent->right = leftChild;
        if (node->parent) {
            if (node->parent->left == grandparent) node->parent->left = node;
            else node->parent->right = node;
        }
        if (leftChild) leftChild->parent = grandparent;
        if (rightChild) rightChild->parent = parent;
    }
}

void SplayTree::splay(TreeNode* node) {
    while (node->parent) {
        TreeNode* parent = node->parent;
        TreeNode* grandparent = parent->parent;
        if (!grandparent) zig(node);
        else if (grandparent->left == parent && parent->left == node) zig_zig(node);
        else if (grandparent->right == parent && parent->right == node) zig_zig(node);
        else zig_zag(node);
    }
    this->root = node;
}

SplayTree::SplayTree() : root(nullptr) {}

SplayTree::SplayTree(TreeNode* rootNode) : root(rootNode) {}

TreeNode* SplayTree::find(const std::string& key) {
    TreeNode* result = nullptr;
    TreeNode* currentNode = this->root;
    TreeNode* previousNode = nullptr;
    while (currentNode) {
        previousNode = currentNode;
        if (key < currentNode->key) currentNode = currentNode->left;
        else if (key > currentNode->key) currentNode = currentNode->right;
        else {
            result = currentNode;
            break;
        }
    }
    if (result) splay(result);
    else if (previousNode) splay(previousNode);
    return result;
}

void SplayTree::insert(const std::string& key) {
    if (!root) {
        root = new TreeNode(key);
        return;
    }
    TreeNode* currentNode = this->root;
    while (currentNode) {
        if (key < currentNode->key) {
            if (!currentNode->left) {
                TreeNode* newNode = new TreeNode(key);
                currentNode->left = newNode;
                newNode->parent = currentNode;
                splay(newNode);
                return;
            } else currentNode = currentNode->left;
        } else if (key > currentNode->key) {
            if (!currentNode->right) {
                TreeNode* newNode = new TreeNode(key);
                currentNode->right = newNode;
                newNode->parent = currentNode;
                splay(newNode);
                return;
            } else currentNode = currentNode->right;
        } else {
            splay(currentNode);
            return;
        }
    }
}

TreeNode* subtreeMax(TreeNode* subRoot) {
    TreeNode* currentNode = subRoot;
    while (currentNode->right) currentNode = currentNode->right;
    return currentNode;
}

TreeNode* subtreeMin(TreeNode* subRoot) {
    TreeNode* currentNode = subRoot;
    while (currentNode->left) currentNode = currentNode->left;
    return currentNode;
}

void SplayTree::Delete(const std::string& key) {
    TreeNode* nodeToDelete = find(key);
    if (!nodeToDelete) return;
    TreeNode* leftSubtree = nodeToDelete->left;
    TreeNode* rightSubtree = nodeToDelete->right;
    if (!leftSubtree && !rightSubtree) {
        this->root = nullptr;
    } else if (!leftSubtree) {
        this->root = rightSubtree;
        rightSubtree->parent = nullptr;
    } else if (!rightSubtree) {
        this->root = leftSubtree;
        leftSubtree->parent = nullptr;
    } else {
        TreeNode* maxLeftSubtree = subtreeMax(leftSubtree);
        splay(maxLeftSubtree);
        maxLeftSubtree->right = rightSubtree;
        rightSubtree->parent = maxLeftSubtree;
        this->root = maxLeftSubtree;
    }
    delete nodeToDelete;
}

TreeNode* SplayTree::getRoot() const {
    return root;
}
