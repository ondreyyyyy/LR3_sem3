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

    bool QserializeToText(const string& filename, const string& queueName);
    bool QserializeToBinary(const string& filename, const string& queueName);
    bool QdeserializeFromText(const string& filename, const string& queueName);
    bool QdeserializeFromBinary(const string& filename, const string& queueName);
    bool QsaveToFile(const string& filename, const string& queueName);
    bool QloadFromFile(const string& filename, const string& queueName);
};

#endif