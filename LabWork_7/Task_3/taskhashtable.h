#ifndef TASKHASHTABLE_H
#define TASKHASHTABLE_H

#include "hashtable.h"

class TaskHashTable : public HashTable {
public:
    void RemoveNegativeKeys();
};

#endif // TASKHASHTABLE_H
