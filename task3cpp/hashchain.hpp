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

    bool hashcSerializeToText(const string& filename, const string& hashcName);
    bool hashcSerializeToBinary(const string& filename, const string& hashcName);
    bool hashcDeserializeFromText(const string& filename, const string& hashcName);
    bool hashcDeserializeFromBinary(const string& filename, const string& hashcName);
    bool hashcSaveToFile(const string& filename, const string& hashcName);
    bool hashcLoadFromFile(const string& filename, const string& hashcName);
};

#endif