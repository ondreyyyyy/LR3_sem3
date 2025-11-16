#include "onelinkedlist.hpp"
#include <iostream>
#include <stdexcept>
#include <string>
#include <fstream>

using namespace std;

FNode::FNode(const string& data, FNode* next) {
    value = data;
    this->next = next;
}

forwardList::forwardList() {
    head = nullptr;
    tail = nullptr;
}

forwardList::~forwardList() {
    FNode* current = head;
    while (current != nullptr) {
        head = head->next;
        delete current;
        current = head;
    }
    tail = nullptr;
}

void forwardList::addAtHead(const string& data) {
    if (head == nullptr) {
        auto *frstNode = new FNode(data, nullptr);
        head = frstNode;
        tail = frstNode;
    }
    else {
        auto *newHead = new FNode(data, head);
        head = newHead;
    }
}

void forwardList::addAtTail(const string& data) {
    if (head == nullptr) {
        auto *frstNode = new FNode(data, nullptr);
        head = frstNode;
        tail = frstNode;
    }
    else {
        auto *newNode = new FNode(data, nullptr);
        tail->next = newNode;
        tail = newNode;
    }
}

void forwardList::searchNode(const string& targetValue) const {
    if (head == nullptr) {
        cout << "Список пуст.\n";
        return;
    }
    
    bool isFound = false;
    FNode* curElem = head;
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
    
    cout << "Элемент " << targetValue << " найден. Индекс: " << index << "\n";
}

void forwardList::addBeforeIndex(const string& data, const int& index) {
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
    FNode* curElem = head;

    for (; iterator != index - 1 && curElem != nullptr; iterator++) {
        curElem  = curElem->next;
    }

    if (curElem == nullptr) {
        cout << "Элемента с таким индексом не существует!\n";
        return;
    }

    auto *newNode = new FNode(data, curElem->next);
    curElem->next = newNode;
}

void forwardList::addAfterIndex(const string& data, const int& index) {
    if (head == nullptr) {
        cout << "Список пуст.\n";
        return;
    }
    if (index < 0) {
        cout << "Неверный индекс!\n";
        return;
    }

    FNode* curElem = head;
    int iterator = 0;

    for (; iterator != index && curElem != nullptr; iterator++) {
        curElem = curElem->next;
    }

    if (curElem == nullptr) {
        cout << "Элемента с таким индексом не существует!\n";
        return;
    }

    auto *newNode = new FNode(data, curElem->next);
    curElem->next = newNode;

    if (curElem == tail) {
        tail = newNode;
    }
}

void forwardList::deleteAtHead() {
    if (head == nullptr) {
        cout << "Нечего удалять.\n";
        return;
    }
    
    FNode* deleteNode = head;
    head = head->next;

    if (head == nullptr) {
        tail = nullptr;
    }

    delete deleteNode;
}

void forwardList::deleteAtTail() {
    if (head == nullptr) {
        cout << "Список пуст.\n";
        return;
    }
    if (head == tail) {
        deleteAtHead();
        return;
    }
    
    FNode* curElem = head;
    
    while (curElem->next != tail) {
        curElem = curElem->next;
    }
    
    FNode* temp = tail;
    tail = curElem;
    tail->next = nullptr;
    delete temp;
}

void forwardList::deleteBeforeIndex(const int& index) {
    if (head == nullptr || head == tail) {
        cout << "Удаление невозможно.\n";
        return;
    }
    if (index <= 0) {
        cout << "Неверный индекс.\n";
        return;
    }
    if (index == 1) {
        deleteAtHead();
        return;
    }

    FNode* curElem = head;
    int iterator = 0;

    for (; iterator != index - 2 && curElem != nullptr; iterator++) {
        curElem = curElem->next;
    }

    if (curElem == nullptr || curElem == tail || curElem->next == nullptr) {
        cout << "Неверный индекс.\n";
        return;
    }
    
    FNode* deleteNode = curElem->next;
    curElem->next = deleteNode->next;
    delete deleteNode;
}

void forwardList::deleteAfterIndex(const int& index) {
    if (head == nullptr || head == tail) {
        cout << "Удаление невозможно.\n";
        return;
    }
    if (index < 0) {
        cout << "Неверный индекс.\n";
        return;
    }
    
    FNode* curElem = head;
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

    FNode* deleteNode = curElem->next;
    curElem->next = deleteNode->next;
    delete deleteNode;
}

void forwardList::valueDelete(const string& data) {
    if (head == nullptr) {
        cout << "Удаление невозможно.\n";
        return;
    }

    FNode* curElem = head;
    FNode* prevElem = nullptr;
    bool isFound = false;
    
    while (curElem != nullptr) {
        if (curElem->value == data) {
            isFound = true;
            break;
        }

        prevElem = curElem;
        curElem = curElem->next;
    }

    if (!isFound) {
        cout << "Элемент не найден.\n";
        return;
    }

    if (curElem == head) {
        deleteAtHead();
    }
    else if (curElem == tail) {
        deleteAtTail();
    }
    else {
        prevElem->next = curElem->next;
        delete curElem;
    }
}

void forwardList::printFL() const {
    cout << "Односвязный список: ";

    if (head == nullptr) {
        cout << "элементов нет.\n";
        return;
    }

    FNode* current = head;

    while (current != nullptr) {
        cout << current->value << " ";
        current = current->next;
    }

    cout << "\n";
}

bool forwardList::OLLserializeToText(const string& filename, const string& ollName) {
    ofstream file(filename, ios::app);
    if (!file.is_open()) { 
        cout << "Ошибка при попытке открытия файла '" << filename << "' со структурой.\n";
        return false;
    }

    file << "FORWARD_LIST " << ollName << " "; 

    int count = 0;
    FNode* current = head;
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
    cout << "Односвязный список '" << ollName << "' успешно сохранен в файл '" << filename << "'\n";
    return true;
}

bool forwardList::OLLdeserializeFromText(const string& filename, const string& ollName) {
    ifstream file(filename);
    if (!file.is_open()) {  
        cout << "Ошибка при попытке открытия файла '" << filename << "' со структурой.\n";
        return false;
    }

    string type, name;
    while (file >> type) {
        if (type == "FORWARD_LIST") {
            file >> name;
            if (name == ollName) {
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
                cout << "Односвязный список '" << ollName << "' успешно загружен из файла\n";
                return true;
            }
        }
        
        string line;
        getline(file, line);
    }
    
    file.close();
    cout << "Односвязный список с именем '" << ollName << "' не найден в файле '" << filename << "'\n";
    return false;
}

bool forwardList::OLLserializeToBinary(const string& filename, const string& ollName) {
    ofstream file(filename, ios::binary | ios::app);
    if (!file.is_open()) {
        cout << "Ошибка при открытии бинарного файла.\n";
        return false;
    }

    string type = "FORWARD_LIST";
    size_t typeLength = type.length();
    file.write(reinterpret_cast<const char*>(&typeLength), sizeof(typeLength));
    file.write(type.c_str(), typeLength);

    size_t nameLength = ollName.length();
    file.write(reinterpret_cast<const char*>(&nameLength), sizeof(nameLength));
    file.write(ollName.c_str(), nameLength);

    int count = 0;
    FNode* current = head;
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
    cout << "Односвязный список '" << ollName << "' успешно сохранен в бинарный файл '" << filename << "'\n";
    return true;
}

bool forwardList::OLLdeserializeFromBinary(const string& filename, const string& ollName) {
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

        if (type != "FORWARD_LIST") {
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

        if (currentName == ollName) {
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
            cout << "Односвязный список '" << ollName << "' успешно загружен из бинарного файла\n";
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
    cout << "Односвязный список с именем '" << ollName << "' не найден в бинарном файле '" << filename << "'\n";
    return false;
}

bool forwardList::OLLsaveToFile(const string& filename, const string& ollName) {
    if (filename.length() >= 4 && filename.substr(filename.length() - 4) == ".bin") {
        return OLLserializeToBinary(filename, ollName);
    } else {
        return OLLserializeToText(filename, ollName);
    }
}

bool forwardList::OLLloadFromFile(const string& filename, const string& ollName) {
    if (filename.length() >= 4 && filename.substr(filename.length() - 4) == ".bin") {
        return OLLdeserializeFromBinary(filename, ollName);
    } else {
        return OLLdeserializeFromText(filename, ollName);
    }
}