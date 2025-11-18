#ifndef STACK_HPP
#define STACK_HPP

#include <string>

using namespace std;

class SNode {
private:
    string value;
    SNode* next;
public:
    friend class Stack;
    SNode(const string& data, SNode* next);
    [[nodiscard]] auto getValue() const -> string;
    [[nodiscard]] auto getNext() const -> SNode*;
};

class Stack {
private:
    SNode* head;
public:
    Stack();
    ~Stack();
    [[nodiscard]] auto getHead() const -> SNode*;
    
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