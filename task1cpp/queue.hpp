#ifndef QUEUE_H
#define QUEUE_H

#include <string>

using namespace std;

class QNode {
public:
    string value;
    QNode* next;
    QNode(const string& data, QNode* next);
};

class Queue {
private:
    QNode* tail;
public:
    QNode* head;
    Queue();
    ~Queue();

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