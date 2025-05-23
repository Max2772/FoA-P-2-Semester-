#include "heap.h"
#include <iostream>

Heap::Heap() {
    array = std::make_unique<int[]>(capacity);
}

void Heap::resize() {
    capacity *= 2;
    std::unique_ptr<int[]> newArray = std::make_unique<int[]>(capacity);
    for (int i = 0; i < size; ++i) {
        newArray[i] = array[i];
    }
    array = std::move(newArray);
}

void Heap::insert(int value) {
    if (size == capacity) {
        resize();
    }
    array[size] = value;
    size++;
    shiftUp(size - 1);
}

int Heap::extractMin() {
    if (size == 0) {
        throw std::runtime_error("Heap пуст");
    }
    int min = array[0];
    array[0] = array[size - 1];
    size--;
    if (size > 0) {
        shiftDown(0);
    }
    return min;
}

int Heap::getSize()
{
    return size;
}

void Heap::printHeap() {
    for (int i = 0; i < size; ++i) {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;
}

void Heap::shiftUp(int index) {
    while (index > 0 && array[index] < array[index / 2]) {
        std::swap(array[index], array[index / 2]);
        index /= 2;
    }
}

void Heap::shiftDown(int index) {
    while (2 * index + 1 < size) {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int smallest_child_index = left;
        if (right < size && array[right] < array[left]) {
            smallest_child_index = right;
        }
        if (array[index] <= array[smallest_child_index]) {
            break;
        }
        std::swap(array[index], array[smallest_child_index]);
        index = smallest_child_index;
    }
}

void Heap::buildHeap() {
    for (int i = size / 2; i > 0; i--) {
        shiftDown(i);
    }
}
