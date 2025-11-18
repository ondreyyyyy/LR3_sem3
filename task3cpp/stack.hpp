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

    bool SserializeToText(const string& filename, const string& stackName);
    bool SserializeToBinary(const string& filename, const string& stackName);
    bool SdeserializeFromText(const string& filename, const string& stackName);
    bool SdeserializeFromBinary(const string& filename, const string& stackName);
    bool SsaveToFile(const string& filename, const string& stackName);
    bool SloadFromFile(const string& filename, const string& stackName);
};

#endif