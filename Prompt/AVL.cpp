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

int AVLNode::setHeight() {
    return height_;
}

int AVLNode::balancefactor(std::shared_ptr<AVLNode> v) {
    if (v == NULL) {
        return 0;
    }
    return getHeight(v->right_) - getHeight(v->left_);
}

int AVLNode::getHeight(std::shared_ptr<AVLNode> currentNode) {
    int height_ = 0;
    if (currentNode == NULL) {
        return height_;
    }
    else if ((currentNode -> right_ != NULL) | (currentNode -> left_ != NULL)){
        height_++;
    }
    return height_;
}

int AVLNode::setHeight() {          /*looks like useless*/
    return height_;
}


std::shared_ptr<AVLNode> AVLTree::leftRotation(std::weak_ptr<AVLNode> currentNode) {
    std::shared_ptr<AVLNode> temp = currentNode->right_;
    currentNode->right_ = temp->left_;
    temp->left_ = currentNode;
    if(currentNode->right_) {
        currentNode->right_->parent_ = currentNode;
    }
    temp->parent_ = currentNode->parent_;
    if(currentNode->parent_) {
        if(currentNode == currentNode->parent_->left_) {
            currentNode->parent->left = temp;
        } else if(currentNode == currentNode->parent_->right_) {
            currentNode->parent_->right_ = temp;
        }
    }
    currentNode->parent_ = temp;
    return temp;
}



