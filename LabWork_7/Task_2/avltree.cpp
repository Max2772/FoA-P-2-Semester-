#include "avltree.h"
#include <algorithm>

AVLTree::AVLTree(int value, AVLTree *parent)
    : left(nullptr),
    right(nullptr),
    parent(parent),
    data(value),
    balanceFactor(0) {}

AVLTree::AVLTree() : left(nullptr),
    right(nullptr),
    parent(nullptr),
    data(0),
    balanceFactor(0) {}

void AVLTree::insert(int value) {
    if (parent == nullptr && left == nullptr && right == nullptr && data == 0) {
        data = value;
        return;
    }

    if (value < data) {
        if (left == nullptr) {
            left = new AVLTree(value, this);
        } else {
            left->insert(value);
        }
    } else {
        if (right == nullptr) {
            right = new AVLTree(value, this);
        } else {
            right->insert(value);
        }
    }
    updateBalance();
}

void AVLTree::reBalance() {
    if (balanceFactor > 1) {
        if (left != nullptr && left->balanceFactor < 0) {
            left->rotateLeft();
        }
        rotateRight();
    } else if (balanceFactor < -1) {
        if (right != nullptr && right->balanceFactor > 0) {
            right->rotateRight();
        }
        rotateLeft();
    }
}

int AVLTree::calculateHeight(AVLTree *node) {
    if (node == nullptr) {
        return 0;
    }
    return 1 + std::max(calculateHeight(node->left), calculateHeight(node->right));
}

void AVLTree::rotateRight() {
    AVLTree *newRoot = left;
    left = newRoot->right;
    if (newRoot->right != nullptr) {
        newRoot->right->parent = this;
    }
    newRoot->parent = parent;
    if (parent != nullptr) {
        if (this == parent->left) {
            parent->left = newRoot;
        } else {
            parent->right = newRoot;
        }
    }
    newRoot->right = this;
    parent = newRoot;

    balanceFactor = calculateHeight(left) - calculateHeight(right);
    newRoot->balanceFactor = calculateHeight(newRoot->left) - calculateHeight(newRoot->right);
}

void AVLTree::rotateLeft() {
    AVLTree *newRoot = right;
    right = newRoot->left;
    if (newRoot->left != nullptr) {
        newRoot->left->parent = this;
    }
    newRoot->parent = parent;
    if (parent != nullptr) {
        if (this == parent->left) {
            parent->left = newRoot;
        } else {
            parent->right = newRoot;
        }
    }
    newRoot->left = this;
    parent = newRoot;

    balanceFactor = calculateHeight(left) - calculateHeight(right);
    newRoot->balanceFactor = calculateHeight(newRoot->left) - calculateHeight(newRoot->right);
}

void AVLTree::remove(int value) {
    if (this->data == value) {
        removeNode();
        return;
    }
    if (value < this->data) {
        if (this->left != nullptr) {
            this->left->remove(value);
        }
    } else {
        if (this->right != nullptr) {
            this->right->remove(value);
        }
    }
}

void AVLTree::clear() {
    if (left != nullptr) {
        left->clear();
        delete left;
        left = nullptr;
    }
    if (right != nullptr) {
        right->clear();
        delete right;
        right = nullptr;
    }

    data = 0;
    balanceFactor = 0;
    parent = nullptr;
}


void AVLTree::removeNode() {
    if (left == nullptr || right == nullptr) {
        AVLTree *temp = left ? left : right;
        if (parent != nullptr) {
            if (parent->left == this) {
                parent->left = temp;
            } else {
                parent->right = temp;
            }
            if (temp != nullptr) {
                temp->parent = parent;
            }
            delete this;
            if (parent != nullptr) {
                parent->updateBalance();
            }
        } else {

            if (temp != nullptr) {
                temp->parent = nullptr;
            }
            delete this;
        }
    } else {
        AVLTree *temp = left->findRight();
        data = temp->data;
        temp->removeNode();
        if (parent != nullptr)
            parent->updateBalance();
    }
}

void AVLTree::updateBalance() {
    balanceFactor = calculateHeight(left) - calculateHeight(right);

    if (balanceFactor > 1 || balanceFactor < -1) {
        reBalance();
    }

    if (parent != nullptr) {
        parent->updateBalance();
    }
}



AVLTree *AVLTree::findRight() {
    AVLTree *tmp = this;
    while (tmp->right != nullptr) {
        tmp = tmp->right;
    }
    return tmp;
}

bool AVLTree::contains(int value) {
    if (this->data == value) return true;
    if (this->left == nullptr && this->right == nullptr) return false;
    if (value < this->data) {
        if (this->left != nullptr)
            return this->left->contains(value);
        else
            return false;
    } else {
        if (this->right != nullptr)
            return this->right->contains(value);
        else
            return false;
    }
}

int AVLTree::get() {
    return data;
}

AVLTree *AVLTree::Left() {
    return left;
}

AVLTree *AVLTree::Right() {
    return right;
}

AVLTree *AVLTree::Parent() {
    return parent;
}
