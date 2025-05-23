#ifndef HEAP_H
#define HEAP_H

#include <memory>

class Heap {
public:
    Heap();
    void insert(int value);
    int extractMin();
    int getSize();
    void printHeap();
private:
    std::unique_ptr<int[]> array;
    int size = 0;
    int capacity = 1;
    void shiftUp(int index);
    void shiftDown(int index);
    void buildHeap();
    void resize();
};

#endif // HEAP_H
