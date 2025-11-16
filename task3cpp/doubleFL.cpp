#include "doubleFL.hpp"
#include <iostream>
#include <stdexcept>
#include <string>
#include <fstream>

using namespace std;

DNode::DNode(DNode* next, const string& data, DNode* prev) {
    value = data;
    this->next = next;
    this->prev = prev;
}

doubleFL::doubleFL() {
    head = nullptr;
    tail = nullptr;
}

doubleFL::~doubleFL() {
    DNode* current = head;
    while (current != nullptr) {
        DNode* next = current->next;
        delete current;
        current = next;
    }
    head = nullptr;
    tail = nullptr;
}

void doubleFL::addAtHead(const string& data) {
    if (head == nullptr) {
        head = new DNode(nullptr, data, nullptr);
        tail = head;
        return;
    }
    
    auto *newHead = new DNode(head, data, nullptr);
    head->prev = newHead;
    head = newHead;
}

void doubleFL::addAtTail(const string& data) {
    if (head == nullptr) {
        head = new DNode(nullptr, data, nullptr);
        tail = head;
        return;
    }
    
    auto *newNode = new DNode(nullptr, data, tail);
    tail->next = newNode;
    tail = newNode;
}

void doubleFL::addBeforeIndex(const string& data, const int& index) {
    if (head == nullptr) {
        cout << "Список пуст.\n";
        return;
    }
    if (index == 0) {
        addAtHead(data);
        return;
    }
    if (index < 0) {
        cout << "Неверный индекс!\n";
        return;
    }

    int iterator = 0;
    DNode* curElem = head;

    for (; iterator != index && curElem != nullptr; iterator++) {
        curElem = curElem->next;
    }

    if (curElem == nullptr) {
        cout << "Элемента с таким индексом не существует!\n";
        return;
    }

    auto *newNode = new DNode(curElem, data, curElem->prev);
    curElem->prev->next = newNode;
    curElem->prev = newNode;
}

void doubleFL::addAfterIndex(const string& data, const int& index) {
    if (head == nullptr) {
        cout << "Список пуст.\n";
        return;
    }
    if (index < 0) {
        cout << "Неверный индекс!\n";
        return;
    }

    DNode* curElem = head;
    int iterator = 0;

    for (; iterator != index && curElem != nullptr; iterator++) {
        curElem = curElem->next;
    }

    if (curElem == nullptr) {
        cout << "Элемента с таким индексом не существует!\n";
        return;
    }

    if (curElem == tail) {
        addAtTail(data);
        return;
    }

    auto *newNode = new DNode(curElem->next, data, curElem);
    curElem->next->prev = newNode;
    curElem->next = newNode;
}

void doubleFL::deleteAtHead() {
    if (head == nullptr) {
        cout << "Список пуст.\n";
        return;
    }
    
    DNode* deleteNode = head;

    if (head == tail) {
        head = tail = nullptr;
    }
    else {
        head = head->next;
        head->prev = nullptr;
    }

    delete deleteNode;
}

void doubleFL::deleteAtTail() {
    if (head == nullptr) {
        cout << "Список пуст.\n";
        return;
    }
    
    DNode* deleteNode = tail;

    if (head == tail) {
        head = tail = nullptr;
    }
    else {
        tail->prev->next = nullptr;
        tail = tail->prev;
    }

    delete deleteNode;
}

void doubleFL::deleteBeforeIndex(const int& index) {
    if (head == nullptr || head == tail) {
        cout << "Удаление невозможно.\n";
        return;
    }
    if (index == 1) {
        deleteAtHead();
        return;
    }
    if (index <= 0) {
        cout << "Неверный индекс.\n";
        return;
    }

    DNode* curElem = head;
    int iterator = 0;

    for (; iterator != index && curElem != nullptr; iterator++) {
        curElem = curElem->next;
    }

    if (curElem == nullptr || curElem->prev == nullptr) {
        cout << "Неверный индекс.\n";
        return;
    }

    DNode* deleteNode = curElem->prev;
    
    if (deleteNode == head) {
        deleteAtHead();
        return;
    }

    deleteNode->prev->next = curElem;
    curElem->prev = deleteNode->prev;
    delete deleteNode;
}

void doubleFL::deleteAfterIndex(const int& index) {
    if (head == nullptr || head == tail) {
        cout << "Удаление невозможно.\n";
        return;
    }
    if (index < 0) {
        cout << "Неверный индекс.\n";
        return;
    }
    
    DNode* curElem = head;
    int iterator = 0;

    for (; iterator != index && curElem != nullptr; iterator++) {
        curElem = curElem->next;
    }

    if (curElem == nullptr || curElem == tail) {
        cout << "Неверный индекс.\n";
        return;
    }

    if (curElem->next == tail) {
        deleteAtTail();
        return;
    }

    DNode* deleteNode = curElem->next;
    curElem->next = deleteNode->next;
    deleteNode->next->prev = curElem;
    delete deleteNode;
}

void doubleFL::deleteValue(const string& targetValue) {
    if (head == nullptr) {
        cout << "Список пуст.\n";
        return;
    }

    DNode* curElem = head;
    bool isFound = false;

    while (curElem != nullptr) {
        if (curElem->value == targetValue) {
            isFound = true;
            break;
        }

        curElem = curElem->next;
    }

    if (!isFound) {
        cout << "Элемент не найден.\n";
        return;
    }

    if (curElem == head) {
        deleteAtHead();
        return;
    }

    if (curElem == tail) {
        deleteAtTail();
        return;
    }

    DNode* deleteNode = curElem;
    deleteNode->prev->next = deleteNode->next;
    deleteNode->next->prev = deleteNode->prev;
    delete deleteNode;
}

void doubleFL::searchValue(const string& targetValue) const {
    if (head == nullptr) {
        cout << "Список пуст.\n";
        return;
    }

    DNode* curElem = head;
    bool isFound = false;
    int index = 0;

    while (curElem != nullptr) {
        if (curElem->value == targetValue) {
            isFound = true;
            break;
        }

        curElem = curElem->next;
        index++;
    }

    if (!isFound) {
        cout << "Элемент не найден.\n";
        return;
    }
    
    cout << "Элемент " << curElem->value << " найден. Индекс: " << index << "\n";
}

void doubleFL::printDoubleFL() const {
    DNode* current = head;

    if (current == nullptr) {
        cout << "Список пуст\n";
        return;
    }

    while (current != nullptr) {
        cout << current->value << " ";
        current = current->next;
    }

    cout << "\n";
}

bool doubleFL::DFLserializeToText(const string& filename, const string& dflName) {
    ofstream file(filename, ios::app);
    if (!file.is_open()) { 
        cout << "Ошибка при попытке открытия файла '" << filename << "' со структурой.\n";
        return false;
    }

    file << "DOUBLE_LIST " << dflName << " "; 

    int count = 0;
    DNode* current = head;
    while (current != nullptr) {
        count++;
        current = current->next;
    }

    file << count << " ";
    
    current = head;
    while (current != nullptr) {
        file << current->value << " ";
        current = current->next;
    }
    
    file << "\n"; 
    file.close();
    cout << "Двусвязный список '" << dflName << "' успешно сохранен в файл '" << filename << "'\n";
    return true;
}

bool doubleFL::DFLdeserializeFromText(const string& filename, const string& dflName) {
    ifstream file(filename);
    if (!file.is_open()) {  
        cout << "Ошибка при попытке открытия файла '" << filename << "' со структурой.\n";
        return false;
    }

    string type, name;
    while (file >> type) {
        if (type == "DOUBLE_LIST") {
            file >> name;
            if (name == dflName) {
                int count;
                file >> count;
                
                if (count < 0) {
                    cout << "Некорректное количество элементов в файле\n";
                    file.close();
                    return false;
                }
                
                while (head != nullptr) {
                    deleteAtHead();
                }
                
                for (int i = 0; i < count; i++) {
                    if (file.eof()) {
                        cout << "Недостаточно данных в файле\n";
                        file.close();
                        return false;
                    }
                    string value;
                    file >> value;
                    addAtTail(value);
                }
                
                file.close();
                cout << "Двусвязный список '" << dflName << "' успешно загружен из файла\n";
                return true;
            }
        }
        
        string line;
        getline(file, line);
    }
    
    file.close();
    cout << "Двусвязный список с именем '" << dflName << "' не найден в файле '" << filename << "'\n";
    return false;
}

bool doubleFL::DFLserializeToBinary(const string& filename, const string& dflName) {
    ofstream file(filename, ios::binary | ios::app);
    if (!file.is_open()) {
        cout << "Ошибка при открытии бинарного файла.\n";
        return false;
    }

    string type = "DOUBLE_LIST";
    size_t typeLength = type.length();
    file.write(reinterpret_cast<const char*>(&typeLength), sizeof(typeLength));
    file.write(type.c_str(), typeLength);

    size_t nameLength = dflName.length();
    file.write(reinterpret_cast<const char*>(&nameLength), sizeof(nameLength));
    file.write(dflName.c_str(), nameLength);

    int count = 0;
    DNode* current = head;
    while (current != nullptr) {
        count++;
        current = current->next;
    }

    file.write(reinterpret_cast<const char*>(&count), sizeof(count));

    current = head;
    while (current != nullptr) {
        size_t strLength = current->value.length();
        file.write(reinterpret_cast<const char*>(&strLength), sizeof(strLength));
        file.write(current->value.c_str(), strLength);
        current = current->next;
    }

    file.close();
    cout << "Двусвязный список '" << dflName << "' успешно сохранен в бинарный файл '" << filename << "'\n";
    return true;
}

bool doubleFL::DFLdeserializeFromBinary(const string& filename, const string& dflName) {
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

        if (type != "DOUBLE_LIST") {
            size_t skipNameLength;
            file.read(reinterpret_cast<char*>(&skipNameLength), sizeof(skipNameLength));
            file.seekg(skipNameLength, ios::cur);
            
            int skipCount;
            file.read(reinterpret_cast<char*>(&skipCount), sizeof(skipCount));
            
            for (int i = 0; i < skipCount; i++) {
                size_t skipStrLength;
                file.read(reinterpret_cast<char*>(&skipStrLength), sizeof(skipStrLength));
                file.seekg(skipStrLength, ios::cur);
            }
            continue;
        }

        size_t nameLength;
        file.read(reinterpret_cast<char*>(&nameLength), sizeof(nameLength));
        string currentName(nameLength, '\0');
        file.read(&currentName[0], nameLength);

        if (currentName == dflName) {
            int count;
            file.read(reinterpret_cast<char*>(&count), sizeof(count));

            if (count < 0) {
                cout << "Некорректное количество элементов в бинарном файле\n";
                file.close();
                return false;
            }

            while (head != nullptr) {
                deleteAtHead();
            }

            for (int i = 0; i < count; i++) {
                if (file.eof()) {
                    cout << "Недостаточно данных в бинарном файле\n";
                    file.close();
                    return false;
                }
                
                size_t strLength;
                file.read(reinterpret_cast<char*>(&strLength), sizeof(strLength));
                
                string value(strLength, '\0');
                file.read(&value[0], strLength);
                addAtTail(value);
            }

            file.close();
            cout << "Двусвязный список '" << dflName << "' успешно загружен из бинарного файла\n";
            return true;
        }
        else {
            int skipCount;
            file.read(reinterpret_cast<char*>(&skipCount), sizeof(skipCount));
            
            for (int i = 0; i < skipCount; i++) {
                size_t skipStrLength;
                file.read(reinterpret_cast<char*>(&skipStrLength), sizeof(skipStrLength));
                file.seekg(skipStrLength, ios::cur);
            }
        }
    }

    file.close();
    cout << "Двусвязный список с именем '" << dflName << "' не найден в бинарном файле '" << filename << "'\n";
    return false;
}

bool doubleFL::DFLsaveToFile(const string& filename, const string& dflName) {
    if (filename.length() >= 4 && filename.substr(filename.length() - 4) == ".bin") {
        return DFLserializeToBinary(filename, dflName);
    } else {
        return DFLserializeToText(filename, dflName);
    }
}

bool doubleFL::DFLloadFromFile(const string& filename, const string& dflName) {
    if (filename.length() >= 4 && filename.substr(filename.length() - 4) == ".bin") {
        return DFLdeserializeFromBinary(filename, dflName);
    } else {
        return DFLdeserializeFromText(filename, dflName);
    }
}