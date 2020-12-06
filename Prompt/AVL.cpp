//
// Created by LukaDoncic on 11/28/20.
//

#include "AVL.h"
#include <iostream>


AVLNode::AVLNode(int key) :
        key_(key),
        parent_(std::weak_ptr<AVLNode>()),
        left_(nullptr),
        right_(nullptr) {}

AVLNode::AVLNode(int key, std::weak_ptr<AVLNode> parent) :
        key_(key),
        parent_(parent),
        left_(nullptr),
        right_(nullptr) {}

bool AVLNode::IsLeaf() const {
    return left_ == nullptr && right_ == nullptr;
}

bool AVLNode::HasLeftChild() const {
    return left_ != nullptr;
}

bool AVLNode::HasRightChild() const {
    return right_ != nullptr;
}

int AVLNode::balancefactor(std::shared_ptr<AVLNode> v) {
    if (v == NULL) {
        return 0;
    }
    return height(v->right_) - height(v->left_);
}

int AVLNode::height(std::shared_ptr<AVLNode> v) {
    int height_ = 0;
    if (v == NULL) {
        return 0;
    }
    else if ((v -> right_ != NULL) | (v -> left_ != NULL)){
        height_++;
    }
    return height_;
}



int AVLTree::setHeight() {
    return height_;
}


int AVLTree::getHeight(std::shared_ptr<BSTNode> currentNode) {
    int height_ = 0;
    if (currentNode == NULL) {
        return 0;
    }
    else if ((currentNode -> right_ != NULL) | (v -> left_ != NULL)){
        height_++;
    }
    return height_;
}


void AVLTree::leftRotation(std::shared_ptr<BSTNode> currentNode) {

}

