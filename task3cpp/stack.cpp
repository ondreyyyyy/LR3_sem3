#include "stack.hpp"
#include <iostream>
#include <fstream>

using namespace std;

SNode::SNode(const string& data, SNode* next) {
    value = data;
    this->next = next;
}

auto SNode::getValue() const -> string { 
    return value; 
}

auto SNode::getNext() const -> SNode* { 
    return next; 
}

Stack::Stack() {
    head = nullptr;
}

Stack::~Stack() {
    SNode* curElem = head;
    while (curElem != nullptr) {
        head = head->next;
        delete curElem;
        curElem = head;
    }
}

auto Stack::getHead() const -> SNode* { 
    return head; 
}

void Stack::push(const string& data) {
    auto *newNode = new SNode(data, head);
    head = newNode;
}

void Stack::pop() {
    if (head == nullptr) {
        cout << "Стек пуст.\n";
        return;
    }

    SNode* deleteNode = head;
    head = head->next;
    delete deleteNode;
}

void Stack::printStack() const {
    if (head == nullptr) {
        cout << "Стек пуст.\n";
        return;
    }

    cout << "Стек: ";
    SNode* curElem = head;
    while (curElem != nullptr) {
        cout << curElem->value << " ";
        curElem = curElem->next;
    }

    cout << "\n";
}

bool Stack::SserializeToText(const string& filename, const string& stackName) {
    ofstream file(filename, ios::app);
    if (!file.is_open()) { 
        cout << "Ошибка при попытке открытия файла '" << filename << "' со структурой.\n";
        return false;
    }

    file << "STACK " << stackName << " "; 

    int count = 0;
    SNode* current = head;
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
    cout << "Стек '" << stackName << "' успешно сохранен в файл '" << filename << "'\n";
    return true;
}

bool Stack::SdeserializeFromText(const string& filename, const string& stackName) {
    ifstream file(filename);
    if (!file.is_open()) {  
        cout << "Ошибка при попытке открытия файла '" << filename << "' со структурой.\n";
        return false;
    }

    string type, name;
    while (file >> type) {
        if (type == "STACK") {
            file >> name;
            if (name == stackName) {
                int count;
                file >> count;
                
                if (count < 0) {
                    cout << "Некорректное количество элементов в файле\n";
                    file.close();
                    return false;
                }
                
                while (head != nullptr) {
                    pop();
                }
                
                string* elements = new string[count];
                for (int i = 0; i < count; i++) {
                    if (file.eof()) {
                        cout << "Недостаточно данных в файле\n";
                        delete[] elements;
                        file.close();
                        return false;
                    }
                    file >> elements[i];
                }
                
                for (int i = count - 1; i >= 0; i--) {
                    push(elements[i]);
                }
                
                delete[] elements;
                file.close();
                cout << "Стек '" << stackName << "' успешно загружен из файла\n";
                return true;
            }
        }
        
        string line;
        getline(file, line);
    }
    
    file.close();
    cout << "Стек с именем '" << stackName << "' не найден в файле '" << filename << "'\n";
    return false;
}

bool Stack::SserializeToBinary(const string& filename, const string& stackName) {
    ofstream file(filename, ios::binary | ios::app);
    if (!file.is_open()) {
        cout << "Ошибка при открытии бинарного файла.\n";
        return false;
    }

    string type = "STACK";
    size_t typeLength = type.length();
    file.write(reinterpret_cast<const char*>(&typeLength), sizeof(typeLength));
    file.write(type.c_str(), typeLength);

    size_t nameLength = stackName.length();
    file.write(reinterpret_cast<const char*>(&nameLength), sizeof(nameLength));
    file.write(stackName.c_str(), nameLength);

    int count = 0;
    SNode* current = head;
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
    cout << "Стек '" << stackName << "' успешно сохранен в бинарный файл '" << filename << "'\n";
    return true;
}

bool Stack::SdeserializeFromBinary(const string& filename, const string& stackName) {
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

        if (type != "STACK") {
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

        if (currentName == stackName) {
            int count;
            file.read(reinterpret_cast<char*>(&count), sizeof(count));

            if (count < 0) {
                cout << "Некорректное количество элементов в бинарном файле\n";
                file.close();
                return false;
            }

            while (head != nullptr) {
                pop();
            }

            string* elements = new string[count];
            for (int i = 0; i < count; i++) {
                if (file.eof()) {
                    cout << "Недостаточно данных в бинарном файле\n";
                    delete[] elements;
                    file.close();
                    return false;
                }
                
                size_t strLength;
                file.read(reinterpret_cast<char*>(&strLength), sizeof(strLength));
                
                string value(strLength, '\0');
                file.read(&value[0], strLength);
                elements[i] = value;
            }

            for (int i = count - 1; i >= 0; i--) {
                push(elements[i]);
            }

            delete[] elements;
            file.close();
            cout << "Стек '" << stackName << "' успешно загружен из бинарного файла\n";
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
    cout << "Стек с именем '" << stackName << "' не найден в бинарном файле '" << filename << "'\n";
    return false;
}

bool Stack::SsaveToFile(const string& filename, const string& stackName) {
    if (filename.length() >= 4 && filename.substr(filename.length() - 4) == ".bin") {
        return SserializeToBinary(filename, stackName);
    } else {
        return SserializeToText(filename, stackName);
    }
}

bool Stack::SloadFromFile(const string& filename, const string& stackName) {
    if (filename.length() >= 4 && filename.substr(filename.length() - 4) == ".bin") {
        return SdeserializeFromBinary(filename, stackName);
    } else {
        return SdeserializeFromText(filename, stackName);
    }
}