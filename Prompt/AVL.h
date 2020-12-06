//
// Created by LukaDoncic on 11/28/20.
//

#ifndef PROMPT_AVL_H
#define PROMPT_AVL_H
#include "BST.h"
#include <memory>

class AVLNode{
public:
    AVLNode(int key);
    AVLNode(int key, std::weak_ptr<AVLNode> parent);
    bool IsLeaf() const;
    bool HasLeftChild() const;
    bool HasRightChild() const;
    int balancefactor(std::shared_ptr<AVLNode> v);
    int height(std::shared_ptr<AVLNode> v);
    void leftRotation(std::shared_ptr<BSTNode> currentNode);
    void rightRotation(std::shared_ptr<BSTNode> currentNode);

private:
    int key_;
    std::weak_ptr<AVLNode> parent_;
    std::shared_ptr<AVLNode> left_;
    std::shared_ptr<AVLNode> right_;
    friend AVLTree;
};


class AVLTree : public BST{
public:
    AVLTree();
    void Insert(int key);
    int getHeight(std::shared_ptr<BSTNode> currentNode);
    int setHeight();


private:
    int height_;
    std::shared_ptr<AVLNode> root_;
    size_t size_;

};
#endif //PROMPT_AVL_H
