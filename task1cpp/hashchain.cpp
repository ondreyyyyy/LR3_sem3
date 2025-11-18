#include "hashchain.hpp"
#include <iostream>
#include <cmath>

using namespace std;

HNode::HNode(const string& key, const int& data) {
    this->key = key;
    this->data = data;
    next = nullptr;
    prev = nullptr;
}

auto HNode::getData() const -> int { 
    return data; 
}

auto HNode::getPrev() const -> HNode* { 
    return prev; 
}

auto HNode::getKey() const -> string { 
    return key; 
}

auto HNode::getNext() const -> HNode* { 
    return next; 
}

auto hashFunc::operator()(const string& key, const int& capacity) const -> int {
    int total = 0;
    for (size_t i = 0; i < key.length(); i += partSize) {
        int partValue = 0;
        
        for (size_t j = i; j < i + partSize && j < key.length(); j++) {
            partValue = partValue * hashBase + static_cast<unsigned char>(key[j]);
        }
        
        total += partValue;
    }
    
    return abs(total) % capacity;
}

HashC::HashC() {
    size = 0;
    capacity = initCapacity;
    table = new HNode*[capacity];
    for (int i = 0; i < capacity; i++) {
        table[i] = nullptr;
    }
}

HashC::~HashC() {
    for (int i = 0; i < capacity; ++i) {
        HNode* current = table[i];
        while (current != nullptr) {
            HNode* temp = current;
            current = current->next;
            delete temp;
        }
    }
    delete[] table;
}

auto HashC::getTable() const -> HNode** { 
    return table; 
}

auto HashC::getCapacity() const -> int { 
    return capacity; 
}

void HashC::addElement(const string& key, const int& data) {
    int index = hf(key, capacity);
    HNode* begin = table[index];
    HNode* curElem = begin;

    while (curElem != nullptr) {
        if (curElem->key == key) {
            curElem->data = data;
            return;
        }
        curElem = curElem->next;
    }

    auto *addNode = new HNode(key, data);
    addNode->next = begin;
    addNode->prev =  nullptr;
    if (table[index] != nullptr) {
        table[index]->prev = addNode;
    }
    
    table[index] = addNode;
    size++;
}

auto HashC::findElement(const string& key) -> int {
    int index = hf(key, capacity);
    HNode* begin = table[index];
    HNode* curElem = begin;

    while (curElem != nullptr) {
        if (curElem->key == key) {
            return curElem->data;
        }
        curElem = curElem->next;
    }
    
    throw runtime_error("Элемент не надйен.\n");
}

void HashC::deleteElement(const string& key) {
    int index = hf(key, capacity);
    HNode* deleteNode = table[index];

    while (deleteNode != nullptr) {
        if (deleteNode->key == key) {
            if (deleteNode->prev != nullptr) {
                deleteNode->prev->next = deleteNode->next;
            }
            else {
                table[index] = deleteNode->next;
            }
            if (deleteNode->next != nullptr) {
                deleteNode->next->prev = deleteNode->prev;
            }
            delete deleteNode;
            size--;
            return;
        }
        deleteNode = deleteNode->next;
    }
}

void HashC::printHashTable() const {
    cout << "Хэш-таблица (элементов: " << size << ", вместимость: " << capacity << "):\n";
    
    for (int i = 0; i < capacity; i++) {
        cout << "Цепочка " << i << ": ";
        
        HNode* current = table[i];
        if (current == nullptr) {
            cout << "пусто";
        } else {
            while (current != nullptr) {
                cout << "[" << current->key << " -> " << current->data << "]";
                if (current->next != nullptr) {
                    cout << " -> ";
                }
                current = current->next;
            }
        }
        cout << "\n";
    }
}

extern "C" {
    auto createHashC() -> HashC* {
        return new HashC();
    }

    void deleteHashC(HashC* hashc) {
        delete hashc;
    }

    void hashcAddElement(HashC* hashc, const string& key, const int& data) {
        hashc->addElement(key, data);
    }

    void hashcDeleteElement(HashC* hashc, const string& key) {
        hashc->deleteElement(key);
    }

    auto hashcFindElement(HashC* hashc, const string& key) -> int {
        return hashc->findElement(key);
    }

    void hashcPrint(HashC* hashc) {
        hashc->printHashTable();
    }
}