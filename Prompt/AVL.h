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
    int balance_factor(std::shared_ptr<AVLNode> v);
    int getHeight(std::shared_ptr<AVLNode> currentNode);
    void Replace_left_Child(std::shared_ptr<AVLNode> v, std::shared_ptr<AVLNode> u);
    void Replace_Right_Child(std::shared_ptr<AVLNode> v, std::shared_ptr<AVLNode> u);

private:
    int key_;
    int height_;
    std::weak_ptr<AVLNode> parent_;
    std::shared_ptr<AVLNode> left_;
    std::shared_ptr<AVLNode> right_;
    friend AVLTree;
};


class AVLTree{
public:
    AVLTree();
    void Insert(int key);    // not implement yet
    nlohmann::json JSON() const;
    std::shared_ptr<AVLNode> leftRotation(std::shared_ptr<AVLNode> currentNode);
    std::shared_ptr<AVLNode> rightRotation(std::shared_ptr<AVLNode> currentNode);
    std::shared_ptr<AVLNode> left_right_rotation(std::shared_ptr<AVLNode> currentNode);
    std::shared_ptr<AVLNode> right_left_rotation(std::shared_ptr<AVLNode> currentNode);

private:
    std::shared_ptr<AVLNode> root_;

};
#endif //PROMPT_AVL_H
