#include "taskhashtable.h"

void TaskHashTable::RemoveNegativeKeys()
{
    for (int key = -10; key < 0; ++key) {
        int index = hash(key);

        if (index < 0 || index >= TABLE_SIZE) {
            return;
        }

        while (!table[index].empty()) {
            table[index].pop();
        }
    }
}
