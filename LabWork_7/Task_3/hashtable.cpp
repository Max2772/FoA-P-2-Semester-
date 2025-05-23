#include "hashtable.h"

int HashTable::hash(int key) const {
    return key + 10;
}

void HashTable::insert(int key, int value) {
    int index = hash(key);
    if (index < 0 || index >= TABLE_SIZE) {
        return;
    }

    table[index].push(value);
}

void HashTable::remove(int key) {
    int index = hash(key);
    if (index < 0 || index >= TABLE_SIZE) {
        return;
    }

    if (!table[index].empty()) {
        table[index].pop();
    }
}

bool HashTable::search(int key, int value) const {
    int index = hash(key);
    if (index < 0 || index >= TABLE_SIZE) {
        return false;
    }

    std::stack<int> temp = table[index];
    while (!temp.empty()) {
        if (temp.top() == value) {
            return true;
        }
        temp.pop();
    }
    return false;
}

QString HashTable::print() const {
    QString result;
    for (int i = 0; i < TABLE_SIZE; ++i) {
        result += QString("Index %1: ").arg(i - 10);
        std::stack<int> temp = table[i];
        while (!temp.empty()) {
            result += QString("%1 ").arg(temp.top());
            temp.pop();
        }
        result += '\n';
    }
    return result;
}
