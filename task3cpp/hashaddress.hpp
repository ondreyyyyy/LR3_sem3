#ifndef HASHADDRESS_HPP
#define HASHADDRESS_HPP

#include <string>

using namespace std;

class HANode {
public:
    string key;
    int data;
    bool isDeleted;
    bool isEmpty;
    HANode();
    HANode(const string& key, const int& data);
};

class hashaFunc {
private:
    const int hashPrime = 47;
public:
    auto operator()(const string& key, const int& capacity) const -> int;
};

class HashA {
private:
    hashaFunc hfA;
    void rehash();
    int size;
    const int initCapacity = 8;
    const double fillFactor = 0.75;
public:
    HANode* table;
    int capacity;
    HashA();
    ~HashA();

    void addElementA(const string& key, const int& data);
    [[nodiscard]] auto findElementA(const string& key) const -> int;
    void deleteElementA(const string& key);
    void printHashTableA() const;

    bool hashaSerializeToText(const string& filename, const string& hashaName);
    bool hashaSerializeToBinary(const string& filename, const string& hashaName);
    bool hashaDeserializeFromText(const string& filename, const string& hashaName);
    bool hashaDeserializeFromBinary(const string& filename, const string& hashaName);
    bool hashaSaveToFile(const string& filename, const string& hashaName);
    bool hashaLoadFromFile(const string& filename, const string& hashaName);
};

#endif