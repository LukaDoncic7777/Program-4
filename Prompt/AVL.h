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
    int getHeight(std::shared_ptr<AVLNode> currentNode);
    int setHeight();
    void leftRotation(std::shared_ptr<AVLNode> currentNode);
    void rightRotation(std::shared_ptr<AVLNode> currentNode);
    void leftrightRotation(std::shared_ptr<AVLNode> currentNode);
    void rightleftRotation(std::shared_ptr<AVLNode> currentNode);

private:
    int key_;
    int height_;
    std::weak_ptr<AVLNode> parent_;
    std::shared_ptr<AVLNode> left_;
    std::shared_ptr<AVLNode> right_;

    friend AVLTree;
};


class AVLTree : public AVL{
public:
    AVLTree();
    void Insert(int key);
    std::string JSON() const;
    size_t size() const;
    bool empty() const;

private:
    std::shared_ptr<AVLNode> root_;
    size_t size_;

};
#endif //PROMPT_AVL_H