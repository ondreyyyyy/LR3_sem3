#ifndef HASHCHAIN_HPP
#define HASHCHAIN_HPP

#include <string>

using namespace std;

class HNode {
private:
    int data;
    HNode* prev;
    string key;
    HNode* next;
public:
    friend class HashC;
    HNode(const string& key, const int& data);
    [[nodiscard]] auto getData() const -> int;
    [[nodiscard]] auto getPrev() const -> HNode*;
    [[nodiscard]] auto getKey() const -> string;
    [[nodiscard]] auto getNext() const -> HNode*;
};

class hashFunc {
private:
    const int hashBase = 256;
    int partSize = 3;
public:
    auto operator()(const string& key, const int& capacity) const -> int;
};

class HashC {
private:
    hashFunc hf;
    const int initCapacity = 8;
    int size;
    HNode** table;
    int capacity;
public:
    HashC();
    ~HashC();
    [[nodiscard]] auto getTable() const -> HNode**;
    [[nodiscard]] auto getCapacity() const -> int;

    void addElement(const string& key, const int& data);
    auto findElement(const string& key) -> int;
    void deleteElement(const string& key);
    void printHashTable() const;
};

extern "C" {
    auto createHashC() -> HashC*;
    void deleteHashC(HashC* hashc);
    void hashcAddElement(HashC* hashc, const string& key, const int& data);
    void hashcDeleteElement(HashC* hashc, const string& key);
    auto hashcFindElement(HashC* hashc, const string& key) -> int;
    void hashcPrint(HashC* hashc);
}

#endif