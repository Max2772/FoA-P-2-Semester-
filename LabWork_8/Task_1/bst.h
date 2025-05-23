#ifndef BST_H
#define BST_H

#include <vector>
#include <stdexcept>

template<typename T>
class BinarySearchTree {
    class BST_Node {
        enum Direction {
            Left,
            Right
        };

        void bind(BST_Node *node, Direction direction) {
            switch (direction) {
            case Left:
                left = node;
                break;
            case Right:
                right = node;
                break;
            }
        }

        BST_Node *left;
        BST_Node *right;
        int _key;
        T _value;

    public:
        BST_Node(int key, T value) : _key(key), _value(value), left(nullptr), right(nullptr) {}

        void insert(BST_Node *node) {
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

        friend class BinarySearchTree<T>;
    };

    BST_Node *root;

    BST_Node* search(BST_Node *node, int key) {
        if (node == nullptr || node->_key == key) {
            return node;
        }
        if (key < node->_key) {
            return search(node->left, key);
        } else {
            return search(node->right, key);
        }
    }

    BST_Node* deleteNode(BST_Node *node, int key) {
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

    BST_Node* minValueNode(BST_Node *node) {
        BST_Node *current = node;
        while (current && current->left != nullptr) {
            current = current->left;
        }
        return current;
    }

    void inorderTraversal(BST_Node *node, std::vector<T> &travers) {
        if (node != nullptr) {
            inorderTraversal(node->left, travers);
            travers.push_back(node->_value);
            inorderTraversal(node->right, travers);
        }
    }

    void preorderTraversal(BST_Node *node, std::vector<T> &travers) {
        if (node != nullptr) {
            travers.push_back(node->_value);
            preorderTraversal(node->left, travers);
            preorderTraversal(node->right, travers);
        }
    }

    void postorderTraversal(BST_Node *node, std::vector<T> &travers) {
        if (node != nullptr) {
            postorderTraversal(node->left, travers);
            postorderTraversal(node->right, travers);
            travers.push_back(node->_value);
        }
    }

    BST_Node* findLCA(BST_Node* node, int n1, int n2) {
        if (node == nullptr) return nullptr;
        if (node->_key > n1 && node->_key > n2) {
            return findLCA(node->left, n1, n2);
        }
        if (node->_key < n1 && node->_key < n2) {
            return findLCA(node->right, n1, n2);
        }
        return node;
    }

public:
    BinarySearchTree() : root(nullptr) {}

    void add(T value, int key) {
        if (root != nullptr) {
            root->insert(new BST_Node(key, value));
        } else {
            root = new BST_Node(key, value);
        }
    }

    T search(int key) {
        BST_Node *node = search(root, key);
        if (node != nullptr) {
            return node->_value;
        } else {
            throw std::runtime_error("Ключ не найден");
        }
    }

    void remove(int key) {
        root = deleteNode(root, key);
    }

    std::vector<T> inorderTraversal() {
        std::vector<T> travers;
        inorderTraversal(root, travers);
        return travers;
    }

    std::vector<T> preorderTraversal() {
        std::vector<T> travers;
        preorderTraversal(root, travers);
        return travers;
    }

    std::vector<T> postorderTraversal() {
        std::vector<T> travers;
        postorderTraversal(root, travers);
        return travers;
    }

    void insertSubtree(BinarySearchTree<T> &subtree) {
        if (subtree.root != nullptr) {
            if (root != nullptr) {
                root->insert(subtree.root);
            } else {
                root = subtree.root;
            }
        }
    }

    void removeSubtree(int key) {
        BST_Node* node = search(root, key);
        if (node != nullptr) {
            deleteNode(root, key);
        }
    }

    void insertBranch(T value, int key, int parentKey, bool left) {
        BST_Node* parent = search(root, parentKey);
        if (parent != nullptr) {
            if (left && parent->left == nullptr) {
                parent->left = new BST_Node(key, value);
            } else if (!left && parent->right == nullptr) {
                parent->right = new BST_Node(key, value);
            } else {
                throw std::runtime_error("Узел уже занят");
            }
        } else {
            throw std::runtime_error("Родитель ключа не найден");
        }
    }

    void removeBranch(int parentKey, bool left) {
        BST_Node* parent = search(root, parentKey);
        if (parent != nullptr) {
            if (left && parent->left != nullptr) {
                parent->left = deleteNode(parent->left, parent->left->_key);
            } else if (!left && parent->right != nullptr) {
                parent->right = deleteNode(parent->right, parent->right->_key);
            } else {
                throw std::runtime_error("Узел не существует");
            }
        } else {
            throw std::runtime_error("Родитель ключа не найден");
        }
    }

    BST_Node* findLCA(int n1, int n2) {
        return findLCA(root, n1, n2);
    }
};

#endif //BST_H
