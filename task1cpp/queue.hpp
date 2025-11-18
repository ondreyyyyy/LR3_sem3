#ifndef QUEUE_H
#define QUEUE_H

#include <string>

using namespace std;

class QNode {
private:
    string value;
    QNode* next;
public:
    friend class Queue;
    QNode(const string& data, QNode* next);
    [[nodiscard]] auto getValue() const -> string;
    [[nodiscard]] auto getNext() const -> QNode*;
};

class Queue {
private:
    QNode* tail;
    QNode* head;
public:
    Queue();
    ~Queue();
    [[nodiscard]] auto getHead() const -> QNode*;

    void enqueue(const string& data);
    void dequeue();
    void printQueue() const;
};

extern "C" {
    auto createQueue() -> Queue*;
    void destroyQueue(Queue* que);
    void queueEnqueue(Queue* que, const string& data);
    void queueDequeue(Queue* que);
    void queuePrint(Queue* que);
}

#endif