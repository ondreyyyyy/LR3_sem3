#include "hashaddress.hpp"
#include <iostream>
#include <cmath>

using namespace std;

HANode::HANode() {
    key = " ";
    data = 0;
    isEmpty = true;
    isDeleted = false;
}

HANode::HANode(const string& key, const int& data) {
    this->key = key;
    this->data = data;
    isDeleted = false;
    isEmpty = false;
}

auto hashaFunc::operator()(const string& key, const int& capacity) const -> int {
    int hash = 0;
    for (char symbol: key) {
        hash = (hash * hashPrime + symbol) % capacity;
    }
    return hash % capacity;
}

HashA::HashA() {
    size = 0;
    capacity = initCapacity;
    table = new HANode[capacity];
    for (int i = 0; i < capacity; i++) {
        table[i].isDeleted = false;
        table[i].isEmpty = true;
    }
}

HashA::~HashA() {
    delete[] table;
}

void HashA::rehash() {
    int oldCapacity = capacity;
    HANode* oldTable = table;
    
    capacity = oldCapacity * 2;
    table = new HANode[capacity];
    size = 0;
    
    for (int i = 0; i < capacity; i++) {
        table[i].isEmpty = true;
        table[i].isDeleted = false;
    }
    
    for (int i = 0; i < oldCapacity; i++) {
        if (!oldTable[i].isEmpty && !oldTable[i].isDeleted) {
            int iterator = 0;
            int index = hfA(oldTable[i].key, capacity);
            int originalIndex = index;
            
            while (iterator < capacity) {
                if (table[index].isEmpty) {
                    table[index].key = oldTable[i].key;
                    table[index].data = oldTable[i].data;
                    table[index].isDeleted = false;
                    table[index].isEmpty = false;
                    size++;
                    break;
                }
                iterator++;
                index = (originalIndex + iterator) % capacity;
            }
        }
    }
    
    delete[] oldTable;
}

void HashA::addElementA(const string& key, const int& data) {
    if (size >= capacity * fillFactor) {
        rehash();
    }
    
    int iterator = 0;
    int index = hfA(key, capacity);
    int originalIndex = index;

    while (!table[index].isEmpty) {
        if (!table[index].isDeleted && table[index].key == key) {
            table[index].data = data;
            return;
        }
        iterator++;
        index = (originalIndex + iterator) % capacity;
        
        if (iterator == capacity) {
            cout << "Нет места для вставки.\n";
            return;
        }
    }

    table[index].key = key;
    table[index].data = data;
    table[index].isDeleted = false;
    table[index].isEmpty = false;
    size++;
}

auto HashA::findElementA(const string& key) const -> int {
    int iterator = 0;
    int index = hfA(key, capacity);
    int originalIndex = index;

    while (iterator < capacity) {
        if (table[index].isEmpty && !table[index].isDeleted) {
            return -1;
        }

        if (!table[index].isEmpty && !table[index].isDeleted) {
            if (table[index].key == key) {
                return table[index].data;
            }
        }

        iterator++;
        index = (originalIndex + iterator) % capacity;
    }

    return -1;
}

void HashA::deleteElementA(const string& key) {
    int iterator = 0;
    int index = hfA(key, capacity);
    int originalIndex = index;

    while (iterator < capacity) {
        if (table[index].isEmpty && !table[index].isDeleted) {
            break;
        }

        if (!table[index].isEmpty && !table[index].isDeleted) {
            if (table[index].key == key) {
                table[index].isDeleted = true;
                size--;
                cout << "Элемент удален.\n";
                return;
            }
        }

        iterator++;
        index = (originalIndex + iterator) % capacity;
    }

    cout << "Элемент не найден!\n";
}

void HashA::printHashTableA() const {
    cout << "Хэш-таблица, размер: " << size << ", вместимость: " << capacity << "):\n";
    
    for (int i = 0; i < capacity; i++) {
        cout << "Ячейка " << i << ": ";
        
        if (table[i].isEmpty) {
            if (table[i].isDeleted) {
                cout << "[УДАЛЕНО]";
            } else {
                cout << "пусто";
            }
        } else {
            cout << "[" << table[i].key << " -> " << table[i].data << "]";
            if (table[i].isDeleted) {
                cout << " (удалено)";
            }
        }
        cout << "\n";
    }
}

extern "C" {
    auto createHashA() -> HashA* {
        return new HashA();
    }

    void deleteHashA(HashA* hasha) {
        delete hasha;
    }

    void hashAAddElement(HashA* hasha, const string& key, const int& data) {
        hasha->addElementA(key, data);
    }

    void hashADeleteElement(HashA* hasha, const string& key) {
        hasha->deleteElementA(key);
    }

    auto hashAFindElement(HashA* hasha, const string& key) -> int {
        return hasha->findElementA(key);
    }

    void hashAPrint(HashA* hasha) {
        hasha->printHashTableA();
    }
}