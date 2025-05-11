#ifndef DEQUE_H
#define DEQUE_H

class Deque {
private:
    struct Node {
        int element_;
        Node* previous;
        Node* next;
        Node(int element) : element_(element), previous(nullptr), next(nullptr) {}
    };

    Node* first;
    Node* last;
    int size_;

    void delFirst();
    void delLast();

public:
    Deque();
    Deque(const Deque& other);
    ~Deque();
    Deque& operator=(const Deque& other);

    [[nodiscard]] int front() const;
    [[nodiscard]] int back() const;

    [[nodiscard]] int size() const;
    [[nodiscard]] bool empty() const;

    [[nodiscard]] int at(int index) const;

    void push_front(int element);
    void push_back(int element);
    void pop_front();
    void pop_back();
    void erase(int index);

    void clear();
};

#endif // DEQUE_H
