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


int AVLNode::get_balance_factor(std::shared_ptr<AVLNode> v) {
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


AVLTree::AVLTree() : root_(nullptr), size_(0) {}

std::shared_ptr<AVLNode> AVLTree::leftRotation(std::shared_ptr<AVLNode> currentNode) {
    std::shared_ptr<AVLNode> new_root = currentNode -> right_;
    std::shared_ptr<AVLNode> ancestor = currentNode -> parent_.lock();
    std::shared_ptr<AVLNode> leaf = new_root-> left_;
    if (currentNode->left_) {                             //check the circumstances whether the right child is nullptr or not
        Replace_left_Child(ancestor, new_root);
    }
    else if(currentNode->right_) {
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
    if (currentNode->left_ != nullptr) {                             //check the circumstances whether the right child is nullptr or not
        Replace_left_Child(ancestor, new_root);
    }
    else if(currentNode->right_ != nullptr) {
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

std::shared_ptr<AVLNode> AVLTree::left_right_rotation(std::shared_ptr<AVLNode> currentNode) {   //u only do the left right rotation
    leftRotation(currentNode->left_);
    return rightRotation(currentNode);
}

std::shared_ptr<AVLNode> AVLTree::right_left_rotation(std::shared_ptr<AVLNode> currentNode) {   //u only do the right left rotation
    rightRotation(currentNode->right_);
    return leftRotation(currentNode);
}

void AVLTree::Insert(int key) {
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
        lastNode->left_ = std::make_shared<AVLNode>(key, lastNode);
    } else {
        lastNode->right_ = std::make_shared<AVLNode>(key, lastNode);
    }
    size_++;

    lastNode -> height_ = 1 + lastNode -> getHeight(lastNode);
    lastNode -> balance_factor = lastNode -> get_balance_factor(lastNode);

    while (lastNode != nullptr){
        //lastNode -> height_ = this -> getHeight(lastNode);    //set the lastNode's height to 0
        //lastNode -> balance_factor_ = this -> balance_factor(lastNode); //set the lastNode's balance factor to 0
        //Right Right case
        if(lastNode -> balance_factor > 1 && key < lastNode->left_->key_){
            lastNode -> rightRotation(lastNode);
            return;
        }
        //Left Right Case
        else if(lastNode -> balance_factor > 1 && key > lastNode->left_->key_){
            lastNode->left_ = lastNode->leftRotation(lastNode->left_);
            lastNode->rightRotation(lastNode);
            return;
        }
        //Right Right Case
        else if(lastNode -> balance_factor < -1 && key > lastNode->right_->key_){
            lastNode -> leftRotation(lastNode);
            return;
        }
        //Right Left Case
        else if(lastNode -> balance_factor < -1 && key > lastNode->right_->key_){
            lastNode -> right_ = lastNode -> rightRotation(lastNode->right_);
            lastNode -> leftRotation(lastNode);
            return;
        }
    }


nlohmann::json AVLTree::JSON() const {
    nlohmann::json result;
    std::queue<std::shared_ptr<AVLNode> > nodes;
    if (root_ != nullptr) {
        result["height"] = root_->height_;
        result["root"] = root_->key_;
        nodes.push(root_);
        while (!nodes.empty()) {
            auto v = nodes.front();
            nodes.pop();
            std::string key = std::to_string(v->key_);
            if (v->left_ != nullptr) {
                result[key]["balance factor"] = v->left_->balance_factor;
                result[key]["left"] = v->left_->key_;
                nodes.push(v->left_);
            }
            if (v->right_ != nullptr) {
                result[key]["balance factor"] = v->right_->balance_factor;
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
    return result;
}
}

