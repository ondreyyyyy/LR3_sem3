#include "queue.hpp"
#include <iostream>
#include <stdexcept>
#include <string>
#include <fstream>

using namespace std;

QNode::QNode(const string& data, QNode* next) {
    value = data;
    this->next = next;
}

Queue::Queue() {
    head = nullptr;
    tail = nullptr;
}

Queue::~Queue() {
    QNode* curElem = head;
    while (curElem != nullptr) {
        head = head->next;
        delete curElem;
        curElem = head;
    }
}

void Queue::enqueue(const string& data) {
    auto *newNode = new QNode(data, nullptr);
    if (head == nullptr) {
        head = newNode;
        tail = newNode;
        return;
    }
    
    tail->next = newNode;
    tail = newNode;
}

void Queue::dequeue() {
    if (head == nullptr) {
        cout << "Очередь пустая. Нечего удалять.\n";
        return;
    }

    QNode* deleteNode = head;
    if (deleteNode == tail) {
        head = nullptr;
        tail = nullptr;
    }
    else {
        head = head->next;
    }
    delete deleteNode;
}

void Queue::printQueue() const {
    if (head == nullptr) {
        cout << "Очередь пуста.\n";
        return;
    }

    cout << "Очередь: ";
    QNode* curElem = head;
    while (curElem != nullptr) {
        cout << curElem->value << " ";
        curElem = curElem->next;
    }

    cout << "\n";
}

bool Queue::QserializeToText(const string& filename, const string& queueName) {
    ofstream file(filename, ios::app);
    if (!file.is_open()) { 
        cout << "Ошибка при попытке открытия файла '" << filename << "' со структурой.\n";
        return false;
    }

    file << "QUEUE " << queueName << " "; 

    int count = 0;
    QNode* current = head;
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
    cout << "Очередь '" << queueName << "' успешно сохранена в файл '" << filename << "'\n";
    return true;
}

bool Queue::QdeserializeFromText(const string& filename, const string& queueName) {
    ifstream file(filename);
    if (!file.is_open()) {  
        cout << "Ошибка при попытке открытия файла '" << filename << "' со структурой.\n";
        return false;
    }

    string type, name;
    while (file >> type) {
        if (type == "QUEUE") {
            file >> name;
            if (name == queueName) {
                int count;
                file >> count;
                
                if (count < 0) {
                    cout << "Некорректное количество элементов в файле\n";
                    file.close();
                    return false;
                }
                
                while (head != nullptr) {
                    dequeue();
                }
                
                for (int i = 0; i < count; i++) {
                    if (file.eof()) {
                        cout << "Недостаточно данных в файле\n";
                        file.close();
                        return false;
                    }
                    string value;
                    file >> value;
                    enqueue(value);
                }
                
                file.close();
                cout << "Очередь '" << queueName << "' успешно загружена из файла\n";
                return true;
            }
        }
        
        string line;
        getline(file, line);
    }
    
    file.close();
    cout << "Очередь с именем '" << queueName << "' не найдена в файле '" << filename << "'\n";
    return false;
}

bool Queue::QserializeToBinary(const string& filename, const string& queueName) {
    ofstream file(filename, ios::binary | ios::app);
    if (!file.is_open()) {
        cout << "Ошибка при открытии бинарного файла.\n";
        return false;
    }

    string type = "QUEUE";
    size_t typeLength = type.length();
    file.write(reinterpret_cast<const char*>(&typeLength), sizeof(typeLength));
    file.write(type.c_str(), typeLength);

    size_t nameLength = queueName.length();
    file.write(reinterpret_cast<const char*>(&nameLength), sizeof(nameLength));
    file.write(queueName.c_str(), nameLength);

    int count = 0;
    QNode* current = head;
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
    cout << "Очередь '" << queueName << "' успешно сохранена в бинарный файл '" << filename << "'\n";
    return true;
}

bool Queue::QdeserializeFromBinary(const string& filename, const string& queueName) {
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

        if (type != "QUEUE") {
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

        if (currentName == queueName) {
            int count;
            file.read(reinterpret_cast<char*>(&count), sizeof(count));

            if (count < 0) {
                cout << "Некорректное количество элементов в бинарном файле\n";
                file.close();
                return false;
            }

            while (head != nullptr) {
                dequeue();
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
                enqueue(value);
            }

            file.close();
            cout << "Очередь '" << queueName << "' успешно загружена из бинарного файла\n";
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
    cout << "Очередь с именем '" << queueName << "' не найдена в бинарном файле '" << filename << "'\n";
    return false;
}

bool Queue::QsaveToFile(const string& filename, const string& queueName) {
    if (filename.length() >= 4 && filename.substr(filename.length() - 4) == ".bin") {
        return QserializeToBinary(filename, queueName);
    } else {
        return QserializeToText(filename, queueName);
    }
}

bool Queue::QloadFromFile(const string& filename, const string& queueName) {
    if (filename.length() >= 4 && filename.substr(filename.length() - 4) == ".bin") {
        return QdeserializeFromBinary(filename, queueName);
    } else {
        return QdeserializeFromText(filename, queueName);
    }
}