#ifndef AVLTREE_H
#define AVLTREE_H

class AVLTree {

    AVLTree *left;
    AVLTree *right;
    AVLTree *parent;

    int balanceFactor;
    int data;

    explicit AVLTree(int value, AVLTree *parent = nullptr);

    void removeNode();
    void reBalance();
    void updateBalance();
    AVLTree *findRight();
    int calculateHeight(AVLTree *node);
    void rotateRight();
    void rotateLeft();

public:
    AVLTree();
    ~AVLTree() = default;

    void insert(int value);
    bool contains(int value);
    void remove(int value);
    void clear();
    int get();

    AVLTree *Left();
    AVLTree *Right();
    AVLTree *Parent();
    AVLTree *operator=(const AVLTree &other);
};


#endif //AVLTREE_H
