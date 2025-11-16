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
};

extern "C" {
    auto createStack() -> Stack*;
    void destroyStack(Stack* stck);
    void pushStack(Stack* stck, const string& data);
    void popStack(Stack* stck);
    void stackPrint(Stack* stck);
}

#endif