#include "hashchain.hpp"
#include <iostream>
#include <fstream>
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

bool HashC::hashcSerializeToText(const string& filename, const string& hashcName) {
    ofstream file(filename, ios::app);
    if (!file.is_open()) { 
        cout << "Ошибка при попытке открытия файла '" << filename << "' со структурой.\n";
        return false;
    }

    file << "HASH_CHAIN " << hashcName << " "; 
    file << capacity << " ";
    file << size << " ";
    
    for (int i = 0; i < capacity; i++) {
        HNode* current = table[i];
        while (current != nullptr) {
            file << current->key << " " << current->data << " ";
            current = current->next;
        }
    }
    
    file << "\n"; 
    file.close();
    cout << "Хэш-таблица (цепочки) '" << hashcName << "' успешно сохранена в файл '" << filename << "'\n";
    return true;
}

bool HashC::hashcDeserializeFromText(const string& filename, const string& hashcName) {
    ifstream file(filename);
    if (!file.is_open()) {  
        cout << "Ошибка при попытке открытия файла '" << filename << "' со структурой.\n";
        return false;
    }

    string type, name;
    while (file >> type) {
        if (type == "HASH_CHAIN") {
            file >> name;
            if (name == hashcName) {
                int newCapacity, newSize;
                file >> newCapacity;
                file >> newSize;
                
                if (newCapacity <= 0 || newSize < 0 || newSize > newCapacity) {
                    cout << "Некорректные размеры хэш-таблицы в файле\n";
                    file.close();
                    return false;
                }
                
                for (int i = 0; i < capacity; ++i) {
                    HNode* current = table[i];
                    while (current != nullptr) {
                        HNode* temp = current;
                        current = current->next;
                        delete temp;
                    }
                }
                delete[] table;
                
                capacity = newCapacity;
                size = 0;
                table = new HNode*[capacity];
                for (int i = 0; i < capacity; i++) {
                    table[i] = nullptr;
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
                    addElement(key, value);
                }
                
                file.close();
                cout << "Хэш-таблица (цепочки) '" << hashcName << "' успешно загружена из файла\n";
                return true;
            }
        }
        
        string line;
        getline(file, line);
    }
    
    file.close();
    cout << "Хэш-таблица (цепочки) с именем '" << hashcName << "' не найдена в файле '" << filename << "'\n";
    return false;
}

bool HashC::hashcSerializeToBinary(const string& filename, const string& hashcName) {
    ofstream file(filename, ios::binary | ios::app);
    if (!file.is_open()) {
        cout << "Ошибка при открытии бинарного файла.\n";
        return false;
    }

    string type = "HASH_CHAIN";
    size_t typeLength = type.length();
    file.write(reinterpret_cast<const char*>(&typeLength), sizeof(typeLength));
    file.write(type.c_str(), typeLength);

    size_t nameLength = hashcName.length();
    file.write(reinterpret_cast<const char*>(&nameLength), sizeof(nameLength));
    file.write(hashcName.c_str(), nameLength);

    file.write(reinterpret_cast<const char*>(&capacity), sizeof(capacity));
    file.write(reinterpret_cast<const char*>(&size), sizeof(size));

    for (int i = 0; i < capacity; i++) {
        HNode* current = table[i];
        while (current != nullptr) {
            size_t keyLength = current->key.length();
            file.write(reinterpret_cast<const char*>(&keyLength), sizeof(keyLength));
            file.write(current->key.c_str(), keyLength);
            
            file.write(reinterpret_cast<const char*>(&current->data), sizeof(current->data));
            
            current = current->next;
        }
    }

    file.close();
    cout << "Хэш-таблица (цепочки) '" << hashcName << "' успешно сохранена в бинарный файл '" << filename << "'\n";
    return true;
}

bool HashC::hashcDeserializeFromBinary(const string& filename, const string& hashcName) {
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

        if (type != "HASH_CHAIN") {
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

        if (currentName == hashcName) {
            int newCapacity, newSize;
            file.read(reinterpret_cast<char*>(&newCapacity), sizeof(newCapacity));
            file.read(reinterpret_cast<char*>(&newSize), sizeof(newSize));

            if (newCapacity <= 0 || newSize < 0 || newSize > newCapacity) {
                cout << "Некорректные размеры хэш-таблицы в бинарном файле\n";
                file.close();
                return false;
            }

            for (int i = 0; i < capacity; ++i) {
                HNode* current = table[i];
                while (current != nullptr) {
                    HNode* temp = current;
                    current = current->next;
                    delete temp;
                }
            }
            delete[] table;
            
            capacity = newCapacity;
            size = 0;
            table = new HNode*[capacity];
            for (int i = 0; i < capacity; i++) {
                table[i] = nullptr;
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
                
                addElement(key, value);
            }

            file.close();
            cout << "Хэш-таблица (цепочки) '" << hashcName << "' успешно загружена из бинарного файла\n";
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
    cout << "Хэш-таблица (цепочки) с именем '" << hashcName << "' не найдена в бинарном файле '" << filename << "'\n";
    return false;
}

bool HashC::hashcSaveToFile(const string& filename, const string& hashcName) {
    if (filename.length() >= 4 && filename.substr(filename.length() - 4) == ".bin") {
        return hashcSerializeToBinary(filename, hashcName);
    } else {
        return hashcSerializeToText(filename, hashcName);
    }
}

bool HashC::hashcLoadFromFile(const string& filename, const string& hashcName) {
    if (filename.length() >= 4 && filename.substr(filename.length() - 4) == ".bin") {
        return hashcDeserializeFromBinary(filename, hashcName);
    } else {
        return hashcDeserializeFromText(filename, hashcName);
    }
}