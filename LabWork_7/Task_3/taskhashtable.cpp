#include "taskhashtable.h"

void TaskHashTable::RemoveNegativeKeys()
{
    for (int key = -10; key < 0; ++key) {
        int index = hash(key);
        while (!table[index].empty()) {
            table[index].pop();
        }
    }
}
