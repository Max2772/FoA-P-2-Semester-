#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stack>
#include <vector>
#include <iostream>
#include <string>

class HashTable {
protected:
    std::vector<std::stack<int>> table;

    int hash(int key) const;

public:
    HashTable() : table(TABLE_SIZE) {}

    static const int TABLE_SIZE = 20;

    void insert(int key, int value);

    void remove(int key);

    bool search(int key, int value) const;

    void print() const;
};

#endif // HASHTABLE_H
