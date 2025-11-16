#include "doubleFL.hpp"
#include <iostream>

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

extern "C" {
    auto dflCreate() -> doubleFL* {
        return new doubleFL();
    }

    void deleteDFL(doubleFL* dfl) {
        delete dfl;
    }

    void dflAddAtHead(doubleFL* dfl, const string& data) {
        dfl->addAtHead(data);
    }

    void dflAddAtTail(doubleFL* dfl, const string& data) {
        dfl->addAtTail(data);
    }

    void dflSearchValue(doubleFL* dfl, const string& targetValue) {
        dfl->searchValue(targetValue);
    }

    void dflAddBeforeIndex(doubleFL* dfl, const string& data, const int& index) {
        dfl->addBeforeIndex(data, index);
    }

    void dflAddAfterIndex(doubleFL* dfl, const string& data, const int& index) {
        dfl->addAfterIndex(data, index);
    }

    void dflDeleteAtHead(doubleFL* dfl) {
        dfl->deleteAtHead();
    }

    void dflDeleteAtTail(doubleFL* dfl) {
        dfl->deleteAtTail();
    }

    void dflDeleteBeforeIndex(doubleFL* dfl, const int& index) {
        dfl->deleteBeforeIndex(index);
    }

    void dflDeleteAfterIndex(doubleFL* dfl, const int& index) {
        dfl->deleteAfterIndex(index);
    }

    void dflDeleteValue(doubleFL* dfl, const string& data) {
        dfl->deleteValue(data);
    }

    void dflPrint(doubleFL* dfl) {
        dfl->printDoubleFL();
    }
}