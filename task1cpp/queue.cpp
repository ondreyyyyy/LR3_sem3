#include "queue.hpp"
#include <iostream>

using namespace std;

QNode::QNode(const string& data, QNode* next) {
    value = data;
    this->next = next;
}

auto QNode::getValue() const -> string { 
    return value; 
}

auto QNode::getNext() const -> QNode* { 
    return next; 
}

Queue::Queue() {
    head = nullptr;
    tail = nullptr;
}

Queue::~Queue() {
    QNode* curElem = head;
    while (curElem != nullptr) {
        head = head->next;
        delete curElem;
        curElem = head;
    }
}

auto Queue::getHead() const -> QNode* { 
    return head; 
}

void Queue::enqueue(const string& data) {
    auto *newNode = new QNode(data, nullptr);
    if (head == nullptr) {
        head = newNode;
        tail = newNode;
        return;
    }
    
    tail->next = newNode;
    tail = newNode;
}

void Queue::dequeue() {
    if (head == nullptr) {
        cout << "Очередь пустая. Нечего удалять.\n";
        return;
    }

    QNode* deleteNode = head;
    if (deleteNode == tail) {
        head = nullptr;
        tail = nullptr;
    }
    else {
        head = head->next;
    }
    delete deleteNode;
}

void Queue::printQueue() const {
    if (head == nullptr) {
        cout << "Очередь пуста.\n";
        return;
    }

    cout << "Очередь: ";
    QNode* curElem = head;
    while (curElem != nullptr) {
        cout << curElem->value << " ";
        curElem = curElem->next;
    }

    cout << "\n";
}

extern "C" {
    auto createQueue() -> Queue* {
        return new Queue();
    }

    void destroyQueue(Queue* que) {
        delete que;
    }

    void queueEnqueue(Queue* que, const string& data) {
        que->enqueue(data);
    }

    void queueDequeue(Queue* que) {
        que->dequeue();
    }

    void queuePrint(Queue* que) {
        que->printQueue();
    }
}