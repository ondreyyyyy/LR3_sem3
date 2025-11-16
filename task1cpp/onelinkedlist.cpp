#include "onelinkedlist.hpp"
#include <iostream>

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

extern "C" {
    auto createFL() -> forwardList* {
        return new forwardList();
    }

    void deleteFL(forwardList* flist) {
        delete flist;
    }

    void flAddAtHead(forwardList* flist, const string& data) {
        flist->addAtHead(data);
    }

    void flAddAtTail(forwardList* flist, const string& data) {
        flist->addAtTail(data);
    }

    void flSearchNode(forwardList* flist, const string& targetValue) {
        flist->searchNode(targetValue);
    }

    void flAddBeforeIndex(forwardList* flist, const string& data, const int& index) {
        flist->addBeforeIndex(data, index);
    }

    void flAddAfterIndex(forwardList* flist, const string& data, const int& index) {
        flist->addAfterIndex(data, index);
    }

    void flDeleteAtHead(forwardList* flist) {
        flist->deleteAtHead();
    }

    void flDeleteAtTail(forwardList* flist) {
        flist->deleteAtTail();
    }

    void flDeleteBeforeIndex(forwardList* flist, const int& index) {
        flist->deleteBeforeIndex(index);
    }

    void flDeleteAfterIndex(forwardList* flist, const int& index) {
        flist->deleteAfterIndex(index);
    }

    void flValueDelete(forwardList* flist, const string& data) {
        flist->valueDelete(data);
    }

    void flPrint(forwardList* flist) {
        flist->printFL();
    }
}