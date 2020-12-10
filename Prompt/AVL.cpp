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


int AVLNode::balance_factor(std::shared_ptr<AVLNode> v) {
    if (v == nullptr) {
        return 0;
    }
    return getHeight(v->right_) - getHeight(v->left_);
}

int AVLNode::getHeight(std::shared_ptr<AVLNode> currentNode) {
    int height_ = 0;
    while ((currentNode -> parent_).lock() != nullptr){
        if (currentNode == nullptr) {
            return height_;
        }
        else if ((currentNode -> right_ != nullptr) | (currentNode -> left_ != nullptr)){
            height_++;
        }
    }
    return height_;
}

void AVLNode::Replace_left_Child(std::shared_ptr<AVLNode> v, std::shared_ptr<AVLNode> u) {
    v -> left_ = u;
    if (u){
        u -> parent_ = v;
    }
}

void AVLNode::Replace_Right_Child(std::shared_ptr<AVLNode> v, std::shared_ptr<AVLNode> u) {
    v -> right_ = u;
    if (u){
        u -> parent_ = v;
    }
}


std::shared_ptr<AVLNode> AVLTree::leftRotation(std::shared_ptr<AVLNode> currentNode) {
    std::shared_ptr<AVLNode> new_root = currentNode -> right;
    std::shared_ptr<AVLNode> ancestor = currentNode -> parent_.lock();
    std::shared_ptr<AVLNode> leaf = new_root-> left_;
    if (currentNode->HasLeftChild() != false) {                             //check the circumstances whether the right child is nullptr or not
        Replace_left_Child(ancestor, new_root);
    }
    else if(currentNode->HasRightChild() != false) {
        Replace_Right_Child(ancestor, new_root);
    }
    else {
        root_ = new_root;
        new_root->parent_.reset();
    }
    Replace_left_Child(new_root, currentNode);
    Replace_right_Child(currentNode, leaf);

    return new_root;
}

std::shared_ptr<AVLNode> AVLTree::rightRotation(std::shared_ptr<AVLNode> currentNode) {
    std::shared_ptr<AVLNode> new_root = currentNode -> left_;
    std::shared_ptr<AVLNode> ancestor = currentNode -> parent_.lock();
    std::shared_ptr<AVLNode> leaf = new_root-> right_;
    if (currentNode->HasLeftChild() != false) {                             //check the circumstances whether the right child is nullptr or not
        Replace_left_Child(ancestor, new_root);
    }
    else if(currentNode->HasRightChild() != false) {
        Replace_Right_Child(ancestor, new_root);
    }
    else {
        root_ = new_root;
        new_root->parent_.reset();
    }
    Replace_Right_Child(new_root, currentNode);
    Replace_left_Child(currentNode, leaf);

    return new_root;
}

std::shared_ptr<AVLNode> AVLTree::left_right_rotation(std::shared_ptr<AVLNode> currentNode) {
    leftRotation(currentNode->left_);
    return rightRotation(currentNode)
}

std::shared_ptr<AVLNode> AVLTree::right_left_rotation(std::shared_ptr<AVLNode> currentNode) {
    rightRotation(currentNode->right_);
    return leftRotation(currentNode)
}

void AVLTree::Insert(int key, std::shared_ptr<AVLNode> currentNode) {
    if (root_ == nullptr) {
        root_ = std::make_shared<AVLNode>(key);
        size_++;
        return;
    }
    std::shared_ptr<AVLNode> currentNode = root_, lastNode = nullptr;


    while (currentNode != nullptr) {
        lastNode = currentNode;
        currentNode = (key < currentNode->key_) ?
                      currentNode->left_ : currentNode->right_;
    }
    if (key < lastNode->key_) {
        lastNode->left_ = std::make_shared<BSTNode>(key, lastNode);
    } else {
        lastNode->right_ = std::make_shared<BSTNode>(key, lastNode);
    }
    size_++;
        
    //
        if( balance_factor(lastNode) < -1 && balance_factor(lastNode -> left < 0){      
                return rightRotation(lastNode);
        }

        else if( balance_factor(lastNode) > 1 && balance_factor(lastNode -> right > 0){
                return leftRotation(lastNode);
        }

        else if( balance_factor(lastNode) < -1 && balance_factor(lastNode -> left > 0){
                return right_left_rotation(lastNode);
        }

        else if( balance_factor(lastNode) > 1 && balance_factor(lastNode -> right < 0){
                return left_right_rotatio(lastNode);
        }
     //
        
        
        
}

nlohmann::json AVLTree::JSON() const {
    nlohmann::json result;
    std::queue< std::shared_ptr<AVLNode> > nodes;

    if (root_ != nullptr) {
        result["root"] = root_->key_;
        nodes.push(root_);
        while (!nodes.empty()) {
            auto v = nodes.front();
            nodes.pop();
            std::string key = std::to_string(v->key_);
            if (v->left_ != nullptr) {
                result[key]["left"] = v->left_->key_;
                nodes.push(v->left_);
            }
            if (v->right_ != nullptr) {
                result[key]["right"] = v->right_->key_;
                nodes.push(v->right_);
            }
            if (v->parent_.lock() != nullptr) {
                result[key]["parent"] = v->parent_.lock()->key_;
            } else {
                result[key]["root"] = true;
            }
        }
    }
    result["size"] = size_;
    return result + "\n";



