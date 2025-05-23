#include "hashtable.h"

int HashTable::hash(int key) const {
    return key + 10;
}

void HashTable::insert(int key, int value) {
    int index = hash(key);
    table[index].push(value);
}

void HashTable::remove(int key) {
    int index = hash(key);
    if (!table[index].empty()) {
        table[index].pop();
    }
}

bool HashTable::search(int key, int value) const {
    int index = hash(key);
    std::stack<int> temp = table[index];
    while (!temp.empty()) {
        if (temp.top() == value) {
            return true;
        }
        temp.pop();
    }
    return false;
}

void HashTable::print() const {
    for (int i = 0; i < TABLE_SIZE; ++i) {
        std::cout << "Index " << i - 10 << ": ";
        std::stack<int> temp = table[i];
        while (!temp.empty()) {
            std::cout << temp.top() << " ";
            temp.pop();
        }
        std::cout << std::endl;
    }
}
