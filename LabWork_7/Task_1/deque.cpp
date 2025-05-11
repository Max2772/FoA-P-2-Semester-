#include "deque.h"

#include <stdexcept>

Deque::Deque() : first(nullptr), last(nullptr), _size(0) {}

Deque::~Deque() {
    clear();
}

Deque::Deque(const Deque& other) : first(nullptr), last(nullptr), _size(0) {
    Node* current = other.first;
    while (current) {
        push_back(current->_element);
        current = current->next;
    }
}

Deque& Deque::operator=(const Deque& other) {
    if (this != &other) {
        clear();
        Node* current = other.first;
        while (current) {
            push_back(current->_element);
            current = current->next;
        }
    }
    return *this;
}

int Deque::front() const {
    if (empty()) {
        throw std::out_of_range("Deque is empty");
    }
    return first->_element;
}

int Deque::back() const {
    if (empty()) {
        throw std::out_of_range("Deque is empty");
    }
    return last->_element;
}

int Deque::size() const {
    return _size;
}

bool Deque::empty() const {
    return _size == 0;
}

void Deque::push_front(int element) {
    Node* tmp = new Node(element);
    if (_size) {
        tmp->next = first;
        first->previous = tmp;
        first = tmp;
    } else {
        first = tmp;
        last = tmp;
    }
    ++_size;
}

void Deque::push_back(int element) {
    Node* tmp = new Node(element);
    if (_size) {
        tmp->previous = last;
        last->next = tmp;
        last = tmp;
    } else {
        first = tmp;
        last = tmp;
    }
    ++_size;
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
    --_size;
}

void Deque::pop_back() {
    if (empty()) {
        return;
    }
    delLast();
    --_size;
}

void Deque::clear() {
    while (first) {
        Node* tmp = first;
        first = first->next;
        delete tmp;
    }
    last = nullptr;
    _size = 0;
}
