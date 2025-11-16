#include "stack.hpp"
#include <iostream>

using namespace std;

SNode::SNode(const string& data, SNode* next) {
    value = data;
    this->next = next;
}

Stack::Stack() {
    head = nullptr;
}

Stack::~Stack() {
    SNode* curElem = head;
    while (curElem != nullptr) {
        head = head->next;
        delete curElem;
        curElem = head;
    }
}

void Stack::push(const string& data) {
    auto *newNode = new SNode(data, head);
    head = newNode;
}

void Stack::pop() {
    if (head == nullptr) {
        cout << "Стек пуст.\n";
        return;
    }

    SNode* deleteNode = head;
    head = head->next;
    delete deleteNode;
}

void Stack::printStack() const {
    if (head == nullptr) {
        cout << "Стек пуст.\n";
        return;
    }

    cout << "Стек: ";
    SNode* curElem = head;
    while (curElem != nullptr) {
        cout << curElem->value << " ";
        curElem = curElem->next;
    }

    cout << "\n";
}

extern "C" {
    auto createStack() -> Stack* {
        return new Stack();
    }

    void destroyStack(Stack* stck) {
        delete stck;
    }

    void pushStack(Stack* stck ,const string& data) {
        stck->push(data);
    }

    void popStack(Stack* stck) {
        stck->pop();
    }

    void stackPrint(Stack* stck) {
        stck->printStack();
    }
}