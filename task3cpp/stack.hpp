#ifndef STACK_HPP
#define STACK_HPP

#include <string>

using namespace std;

class SNode {
public:
    string value;
    SNode* next;
    SNode(const string& data, SNode* next);
};

class Stack {
public:
    SNode* head;
    Stack();
    ~Stack();
    void push(const string& data);
    void pop();
    void printStack() const;

    bool SserializeToText(const string& filename, const string& stackName);
    bool SserializeToBinary(const string& filename, const string& stackName);
    bool SdeserializeFromText(const string& filename, const string& stackName);
    bool SdeserializeFromBinary(const string& filename, const string& stackName);
    bool SsaveToFile(const string& filename, const string& stackName);
    bool SloadFromFile(const string& filename, const string& stackName);
};

#endif