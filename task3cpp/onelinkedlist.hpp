#ifndef ONELINKEDLIST_HPP
#define ONELINKEDLIST_HPP

#include <string>

using namespace std;

class FNode {
public:
    FNode* next;
    string value;
    FNode(const string& data, FNode* next);
};

class forwardList {
private:
    FNode* tail;
public:
    FNode* head;
    forwardList();
    ~forwardList();

    void addAtHead(const string& data);
    void addAtTail(const string& data);
    void searchNode(const string& targetValue) const;
    void addBeforeIndex(const string& data, const int& index);
    void addAfterIndex(const string& data, const int& index);
    void deleteAtHead();
    void deleteAtTail();
    void deleteBeforeIndex(const int& index);
    void deleteAfterIndex(const int& index);
    void valueDelete(const string& data);
    void printFL() const;

    bool OLLserializeToText(const string& filename, const string& ollName);
    bool OLLserializeToBinary(const string& filename, const string& ollName);
    bool OLLdeserializeFromText(const string& filename, const string& ollName);
    bool OLLdeserializeFromBinary(const string& filename, const string& ollName);
    bool OLLsaveToFile(const string& filename, const string& ollName);
    bool OLLloadFromFile(const string& filename, const string& ollName);
};

#endif