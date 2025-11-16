#ifndef HASHCHAIN_HPP
#define HASHCHAIN_HPP

#include <string>

using namespace std;

class HNode {
public:
    int data;
    HNode* prev;
    string key;
    HNode* next;
    HNode(const string& key, const int& data);
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
public:
    HNode** table;
    int capacity;
    HashC();
    ~HashC();

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