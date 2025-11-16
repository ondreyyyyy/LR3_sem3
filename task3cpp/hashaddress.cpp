#include "hashaddress.hpp"
#include <iostream>
#include <stdexcept>
#include <string>
#include <fstream>

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

bool HashA::hashaSerializeToText(const string& filename, const string& hashaName) {
    ofstream file(filename, ios::app);
    if (!file.is_open()) { 
        cout << "Ошибка при попытке открытия файла '" << filename << "' со структурой.\n";
        return false;
    }

    file << "HASH_ADDRESS " << hashaName << " "; 
    file << capacity << " ";
    file << size << " ";
    
    for (int i = 0; i < capacity; i++) {
        if (!table[i].isEmpty && !table[i].isDeleted) {
            file << table[i].key << " " << table[i].data << " ";
        }
    }
    
    file << "\n"; 
    file.close();
    cout << "Хэш-таблица (открытая адресация) '" << hashaName << "' успешно сохранена в файл '" << filename << "'\n";
    return true;
}

bool HashA::hashaDeserializeFromText(const string& filename, const string& hashaName) {
    ifstream file(filename);
    if (!file.is_open()) {  
        cout << "Ошибка при попытке открытия файла '" << filename << "' со структурой.\n";
        return false;
    }

    string type, name;
    while (file >> type) {
        if (type == "HASH_ADDRESS") {
            file >> name;
            if (name == hashaName) {
                int newCapacity, newSize;
                file >> newCapacity;
                file >> newSize;
                
                if (newCapacity <= 0 || newSize < 0 || newSize > newCapacity) {
                    cout << "Некорректные размеры хэш-таблицы в файле\n";
                    file.close();
                    return false;
                }
                
                delete[] table;
                
                capacity = newCapacity;
                size = 0;
                table = new HANode[capacity];
                for (int i = 0; i < capacity; i++) {
                    table[i].isDeleted = false;
                    table[i].isEmpty = true;
                }
                
                for (int i = 0; i < newSize; i++) {
                    if (file.eof()) {
                        cout << "Недостаточно данных в файле\n";
                        file.close();
                        return false;
                    }
                    string key;
                    int value;
                    file >> key >> value;
                    addElementA(key, value);
                }
                
                file.close();
                cout << "Хэш-таблица (открытая адресация) '" << hashaName << "' успешно загружена из файла\n";
                return true;
            }
        }
        
        string line;
        getline(file, line);
    }
    
    file.close();
    cout << "Хэш-таблица (открытая адресация) с именем '" << hashaName << "' не найдена в файле '" << filename << "'\n";
    return false;
}

bool HashA::hashaSerializeToBinary(const string& filename, const string& hashaName) {
    ofstream file(filename, ios::binary | ios::app);
    if (!file.is_open()) {
        cout << "Ошибка при открытии бинарного файла.\n";
        return false;
    }

    string type = "HASH_ADDRESS";
    size_t typeLength = type.length();
    file.write(reinterpret_cast<const char*>(&typeLength), sizeof(typeLength));
    file.write(type.c_str(), typeLength);

    size_t nameLength = hashaName.length();
    file.write(reinterpret_cast<const char*>(&nameLength), sizeof(nameLength));
    file.write(hashaName.c_str(), nameLength);

    file.write(reinterpret_cast<const char*>(&capacity), sizeof(capacity));
    file.write(reinterpret_cast<const char*>(&size), sizeof(size));

    for (int i = 0; i < capacity; i++) {
        if (!table[i].isEmpty && !table[i].isDeleted) {
            size_t keyLength = table[i].key.length();
            file.write(reinterpret_cast<const char*>(&keyLength), sizeof(keyLength));
            file.write(table[i].key.c_str(), keyLength);
            
            file.write(reinterpret_cast<const char*>(&table[i].data), sizeof(table[i].data));
        }
    }

    file.close();
    cout << "Хэш-таблица (открытая адресация) '" << hashaName << "' успешно сохранена в бинарный файл '" << filename << "'\n";
    return true;
}

bool HashA::hashaDeserializeFromBinary(const string& filename, const string& hashaName) {
    ifstream file(filename, ios::binary);
    if (!file.is_open()) {
        cout << "Ошибка при открытии бинарного файла.\n";
        return false;
    }

    while (file.peek() != EOF) {
        size_t typeLength;
        if (!file.read(reinterpret_cast<char*>(&typeLength), sizeof(typeLength))) {
            break;
        }

        string type(typeLength, '\0');
        file.read(&type[0], typeLength);

        if (type != "HASH_ADDRESS") {
            size_t skipNameLength;
            file.read(reinterpret_cast<char*>(&skipNameLength), sizeof(skipNameLength));
            file.seekg(skipNameLength, ios::cur);
            
            int skipCapacity, skipSize;
            file.read(reinterpret_cast<char*>(&skipCapacity), sizeof(skipCapacity));
            file.read(reinterpret_cast<char*>(&skipSize), sizeof(skipSize));
            
            for (int i = 0; i < skipSize; i++) {
                size_t skipKeyLength;
                file.read(reinterpret_cast<char*>(&skipKeyLength), sizeof(skipKeyLength));
                file.seekg(skipKeyLength, ios::cur);
                
                int skipValue;
                file.read(reinterpret_cast<char*>(&skipValue), sizeof(skipValue));
            }
            continue;
        }

        size_t nameLength;
        file.read(reinterpret_cast<char*>(&nameLength), sizeof(nameLength));
        string currentName(nameLength, '\0');
        file.read(&currentName[0], nameLength);

        if (currentName == hashaName) {
            int newCapacity, newSize;
            file.read(reinterpret_cast<char*>(&newCapacity), sizeof(newCapacity));
            file.read(reinterpret_cast<char*>(&newSize), sizeof(newSize));

            if (newCapacity <= 0 || newSize < 0 || newSize > newCapacity) {
                cout << "Некорректные размеры хэш-таблицы в бинарном файле\n";
                file.close();
                return false;
            }

            delete[] table;
            
            capacity = newCapacity;
            size = 0;
            table = new HANode[capacity];
            for (int i = 0; i < capacity; i++) {
                table[i].isDeleted = false;
                table[i].isEmpty = true;
            }
            
            for (int i = 0; i < newSize; i++) {
                if (file.eof()) {
                    cout << "Недостаточно данных в бинарном файле\n";
                    file.close();
                    return false;
                }
                
                size_t keyLength;
                file.read(reinterpret_cast<char*>(&keyLength), sizeof(keyLength));
                
                string key(keyLength, '\0');
                file.read(&key[0], keyLength);
                
                int value;
                file.read(reinterpret_cast<char*>(&value), sizeof(value));
                
                addElementA(key, value);
            }

            file.close();
            cout << "Хэш-таблица (открытая адресация) '" << hashaName << "' успешно загружена из бинарного файла\n";
            return true;
        }
        else {
            int skipCapacity, skipSize;
            file.read(reinterpret_cast<char*>(&skipCapacity), sizeof(skipCapacity));
            file.read(reinterpret_cast<char*>(&skipSize), sizeof(skipSize));
            
            for (int i = 0; i < skipSize; i++) {
                size_t skipKeyLength;
                file.read(reinterpret_cast<char*>(&skipKeyLength), sizeof(skipKeyLength));
                file.seekg(skipKeyLength, ios::cur);
                
                int skipValue;
                file.read(reinterpret_cast<char*>(&skipValue), sizeof(skipValue));
            }
        }
    }

    file.close();
    cout << "Хэш-таблица (открытая адресация) с именем '" << hashaName << "' не найдена в бинарном файле '" << filename << "'\n";
    return false;
}

bool HashA::hashaSaveToFile(const string& filename, const string& hashaName) {
    if (filename.length() >= 4 && filename.substr(filename.length() - 4) == ".bin") {
        return hashaSerializeToBinary(filename, hashaName);
    } else {
        return hashaSerializeToText(filename, hashaName);
    }
}

bool HashA::hashaLoadFromFile(const string& filename, const string& hashaName) {
    if (filename.length() >= 4 && filename.substr(filename.length() - 4) == ".bin") {
        return hashaDeserializeFromBinary(filename, hashaName);
    } else {
        return hashaDeserializeFromText(filename, hashaName);
    }
}