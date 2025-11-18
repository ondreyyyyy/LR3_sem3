#ifndef DOUBLEFL_HPP
#define DOUBLEFL_HPP

#include <string>

using namespace std;

class DNode {
private:
    DNode* next;
    DNode* prev;
    string value;
public:
    friend class doubleFL;
    DNode(DNode* next, const string& data, DNode* prev);
    [[nodiscard]] auto getNext() const -> DNode*;
    [[nodiscard]] auto getPrev() const -> DNode*;
    [[nodiscard]] auto getValue() const -> string;
};

class doubleFL {
private:
    DNode* tail;
    DNode* head;
public:
    doubleFL();
    ~doubleFL();
    [[nodiscard]] auto getHead() const -> DNode*;

    void addAtHead(const string& data);
    void addAtTail(const string& data);
    void addBeforeIndex(const string& data, const int& index);
    void addAfterIndex(const string& data, const int& index);
    
    void deleteAtHead();
    void deleteAtTail();
    void deleteBeforeIndex(const int& index);
    void deleteAfterIndex(const int& index);
    void deleteValue(const string& targetValue);
    
    void searchValue(const string& targetValue) const;
    void printDoubleFL() const;
};

extern "C" {
    auto dflCreate() -> doubleFL*;
    void deleteDFL(doubleFL* dfl);
    void dflAddAtHead(doubleFL* dfl, const string& data);
    void dflAddAtTail(doubleFL* dfl, const string& data);
    void dflSearchValue(doubleFL* dfl, const string& targetValue);
    void dflAddBeforeIndex(doubleFL* dfl, const string& data, const int& index);
    void dflAddAfterIndex(doubleFL* dfl, const string& data, const int& index);
    void dflDeleteAtHead(doubleFL* dfl);
    void dflDeleteAtTail(doubleFL* dfl);
    void dflDeleteBeforeIndex(doubleFL* dfl, const int& index);
    void dflDeleteAfterIndex(doubleFL* dfl, const int& index);
    void dflDeleteValue(doubleFL* dfl, const string& data);
    void dflPrint(doubleFL* dfl);
}

#endif