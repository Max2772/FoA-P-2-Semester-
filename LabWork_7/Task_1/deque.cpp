#include "deque.h"

#include <stdexcept>

Deque::Deque() : first(nullptr), last(nullptr), size_(0) {}

Deque::~Deque() {
    clear();
}

Deque::Deque(const Deque& other) : first(nullptr), last(nullptr), size_(0) {
    Node* current = other.first;
    while (current) {
        push_back(current->element_);
        current = current->next;
    }
}

Deque& Deque::operator=(const Deque& other) {
    if (this != &other) {
        clear();
        Node* current = other.first;
        while (current) {
            push_back(current->element_);
            current = current->next;
        }
    }
    return *this;
}

int Deque::front() const {
    if (empty()) {
        throw std::out_of_range("Deque is empty");
    }
    return first->element_;
}

int Deque::back() const {
    if (empty()) {
        throw std::out_of_range("Deque is empty");
    }
    return last->element_;
}

int Deque::size() const {
    return size_;
}

bool Deque::empty() const {
    return size_ == 0;
}

int Deque::at(int index) const
{
    if (index < 0 || index >= size_) {
        throw std::out_of_range("Index out of range");
    }
    Node* current = first;
    for (int i = 0; i < index; ++i) {
        current = current->next;
    }
    return current->element_;
}

void Deque::push_front(int element) {
    Node* tmp = new Node(element);
    if (size_) {
        tmp->next = first;
        first->previous = tmp;
        first = tmp;
    } else {
        first = tmp;
        last = tmp;
    }
    ++size_;
}

void Deque::push_back(int element) {
    Node* tmp = new Node(element);
    if (size_) {
        tmp->previous = last;
        last->next = tmp;
        last = tmp;
    } else {
        first = tmp;
        last = tmp;
    }
    ++size_;
}

void Deque::delFirst() {
    if (first) {
        Node* tmp = first;
        first = first->next;
        if (first) {
            first->previous = nullptr;
        } else {
            last = nullptr;
        }
        delete tmp;
    }
}

void Deque::delLast() {
    if (last) {
        Node* tmp = last;
        last = last->previous;
        if (last) {
            last->next = nullptr;
        } else {
            first = nullptr;
        }
        delete tmp;
    }
}

void Deque::pop_front() {
    if (empty()) {
        return;
    }
    delFirst();
    --size_;
}

void Deque::pop_back() {
    if (empty()) {
        return;
    }
    delLast();
    --size_;
}

void Deque::erase(int index)
{
    if (index < 0 || index >= size_) {
        throw std::out_of_range("Index out of range");
    }
    if (index == 0) {
        pop_front();
        return;
    }
    if (index == size_ - 1) {
        pop_back();
        return;
    }

    Node* current = first;
    for (int i = 0; i < index; ++i) {
        current = current->next;
    }

    current->previous->next = current->next;
    current->next->previous = current->previous;

    delete current;
    --size_;
}

void Deque::clear() {
    while (first) {
        Node* tmp = first;
        first = first->next;
        delete tmp;
    }
    last = nullptr;
    size_ = 0;
}
