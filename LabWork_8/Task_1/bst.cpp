#include "bst.h"

template<typename T>
BinarySearchTree<T>::BST_Node::BST_Node(int key, T value) : _key(key), _value(value), left(nullptr), right(nullptr) {}

template<typename T>
void BinarySearchTree<T>::BST_Node::bind(BST_Node *node, Direction direction) {
    switch (direction) {
    case Left:
        left = node;
        break;
    case Right:
        right = node;
        break;
    }
}

template<typename T>
void BinarySearchTree<T>::BST_Node::insert(BST_Node *node) {
    if (node->_key < _key) {
        if (left != nullptr) {
            left->insert(node);
        } else {
            bind(node, Left);
        }
    } else if (node->_key > _key) {
        if (right != nullptr) {
            right->insert(node);
        } else {
            bind(node, Right);
        }
    } else {
        _value = node->_value;
    }
}

template<typename T>
BinarySearchTree<T>::BinarySearchTree() : root(nullptr) {}

template<typename T>
typename BinarySearchTree<T>::BST_Node* BinarySearchTree<T>::search(BST_Node *node, int key) {
    if (node == nullptr || node->_key == key) {
        return node;
    }
    if (key < node->_key) {
        return search(node->left, key);
    } else {
        return search(node->right, key);
    }
}

template<typename T>
typename BinarySearchTree<T>::BST_Node* BinarySearchTree<T>::deleteNode(BST_Node *node, int key) {
    if (node == nullptr) return node;

    if (key < node->_key) {
        node->left = deleteNode(node->left, key);
    } else if (key > node->_key) {
        node->right = deleteNode(node->right, key);
    } else {
        if (node->left == nullptr) {
            BST_Node *temp = node->right;
            delete node;
            return temp;
        } else if (node->right == nullptr) {
            BST_Node *temp = node->left;
            delete node;
            return temp;
        }

        BST_Node *temp = minValueNode(node->right);
        node->_key = temp->_key;
        node->_value = temp->_value;
        node->right = deleteNode(node->right, temp->_key);
    }
    return node;
}

template<typename T>
typename BinarySearchTree<T>::BST_Node* BinarySearchTree<T>::minValueNode(BST_Node *node) {
    BST_Node *current = node;
    while (current && current->left != nullptr) {
        current = current->left;
    }
    return current;
}

template<typename T>
void BinarySearchTree<T>::inorderTraversal(BST_Node *node, std::vector<T> &travers) {
    if (node != nullptr) {
        inorderTraversal(node->left, travers);
        travers.push_back(node->_value);
        inorderTraversal(node->right, travers);
    }
}

template<typename T>
void BinarySearchTree<T>::preorderTraversal(BST_Node *node, std::vector<T> &travers) {
    if (node != nullptr) {
        travers.push_back(node->_value);
        preorderTraversal(node->left, travers);
        preorderTraversal(node->right, travers);
    }
}

template<typename T>
void BinarySearchTree<T>::postorderTraversal(BST_Node *node, std::vector<T> &travers) {
    if (node != nullptr) {
        postorderTraversal(node->left, travers);
        postorderTraversal(node->right, travers);
        travers.push_back(node->_value);
    }
}

template<typename T>
typename BinarySearchTree<T>::BST_Node* BinarySearchTree<T>::findLCA(BST_Node* node, int n1, int n2) {
    if (node == nullptr) return nullptr;
    if (node->_key > n1 && node->_key > n2) {
        return findLCA(node->left, n1, n2);
    }
    if (node->_key < n1 && node->_key < n2) {
        return findLCA(node->right, n1, n2);
    }
    return node;
}

template<typename T>
void BinarySearchTree<T>::add(T value, int key) {
    if (root != nullptr) {
        root->insert(new BST_Node(key, value));
    } else {
        root = new BST_Node(key, value);
    }
}

template<typename T>
void BinarySearchTree<T>::remove(int key) {
    root = deleteNode(root, key);
}

template<typename T>
T BinarySearchTree<T>::search(int key) {
    BST_Node *node = search(root, key);
    if (node != nullptr) {
        return node->_value;
    } else {
        throw std::runtime_error("Key not found");
    }
}

template<typename T>
std::vector<T> BinarySearchTree<T>::inorderTraversal() {
    std::vector<T> travers;
    inorderTraversal(root, travers);
    return travers;
}

template<typename T>
std::vector<T> BinarySearchTree<T>::preorderTraversal() {
    std::vector<T> travers;
    preorderTraversal(root, travers);
    return travers;
}

template<typename T>
std::vector<T> BinarySearchTree<T>::postorderTraversal() {
    std::vector<T> travers;
    postorderTraversal(root, travers);
    return travers;
}

template<typename T>
void BinarySearchTree<T>::insertSubtree(BinarySearchTree<T> &subtree) {
    if (subtree.root != nullptr) {
        if (root != nullptr) {
            root->insert(subtree.root);
        } else {
            root = subtree.root;
        }
    }
}

template<typename T>
void BinarySearchTree<T>::removeSubtree(int key) {
    BST_Node* node = search(root, key);
    if (node != nullptr) {
        deleteNode(root, key);
    }
}

template<typename T>
void BinarySearchTree<T>::insertBranch(T value, int key, int parentKey, bool left) {
    BST_Node* parent = search(root, parentKey);
    if (parent != nullptr) {
        if (left && parent->left == nullptr) {
            parent->left = new BST_Node(key, value);
        } else if (!left && parent->right == nullptr) {
            parent->right = new BST_Node(key, value);
        } else {
            throw std::runtime_error("Branch position already occupied");
        }
    } else {
        throw std::runtime_error("Parent key not found");
    }
}

template<typename T>
void BinarySearchTree<T>::removeBranch(int parentKey, bool left) {
    BST_Node* parent = search(root, parentKey);
    if (parent != nullptr) {
        if (left && parent->left != nullptr) {
            deleteNode(parent->left, parent->left->_key);
        } else if (!left && parent->right != nullptr) {
            deleteNode(parent->right, parent->right->_key);
        } else {
            throw std::runtime_error("Branch does not exist");
        }
    } else {
        throw std::runtime_error("Parent key not found");
    }
}

template<typename T>
typename BinarySearchTree<T>::BST_Node* BinarySearchTree<T>::findLCA(int n1, int n2) {
    return findLCA(root, n1, n2);
}

// Explicit template instantiation (optional, add as needed)
// template class BinarySearchTree<int>;
// template class BinarySearchTree<std::string>;

#endif //LAB8TASK1_BINARYSEARCHTREE_H
