
#pragma once

#include <cstddef>
#include <stdexcept>

template <typename T>
class Stack {
private:
    struct Node {
        T data;
        Node* next;

        explicit Node(const T& value)
            : data(value), next(nullptr) {}
    };

    Node* topNode;
    std::size_t count;

public:
    Stack() : topNode(nullptr), count(0) {}

    ~Stack() {
        clear();
    }

    Stack(const Stack&) = delete;
    Stack& operator=(const Stack&) = delete;

    void push(const T& value) {
        Node* node = new Node(value);
        node->next = topNode;
        topNode = node;
        ++count;
    }

    T pop() {
        if (isEmpty()) {
            throw std::underflow_error("Cannot pop an empty stack.");
        }

        Node* temp = topNode;
        T value = temp->data;
        topNode = topNode->next;

        delete temp;
        --count;

        return value;
    }

    const T& peek() const {
        if (isEmpty()) {
            throw std::underflow_error("Cannot peek an empty stack.");
        }

        return topNode->data;
    }

    bool isEmpty() const {
        return topNode == nullptr;
    }

    std::size_t size() const {
        return count;
    }

    void clear() {
        while (topNode != nullptr) {
            Node* temp = topNode;
            topNode = topNode->next;
            delete temp;
        }

        count = 0;
    }
};
