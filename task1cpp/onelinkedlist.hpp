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
};

extern "C" {
    auto createFL() -> forwardList*;
    void deleteFL(forwardList* flist);
    void flAddAtHead(forwardList* flist, const string& data);
    void flAddAtTail(forwardList* flist, const string& data);
    void flSearchNode(forwardList* flist, const string& targetValue);
    void flAddBeforeIndex(forwardList* flist, const string& data, const int& index);
    void flAddAfterIndex(forwardList* flist, const string& data, const int& index);
    void flDeleteAtHead(forwardList* flist);
    void flDeleteAtTail(forwardList* flist);
    void flDeleteBeforeIndex(forwardList* flist, const int& index);
    void flDeleteAfterIndex(forwardList* flist, const int& index);
    void flValueDelete(forwardList* flist, const string& data);
    void flPrint(forwardList* flist);
}

#endif