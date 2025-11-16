#include "array.hpp"
#include <iostream>
#include <stdexcept>
#include <string>
#include <cstring>

using namespace std;

DynArray::DynArray() {
    data = nullptr;
    size = 0;
    capacity = 0;
}

DynArray::DynArray(int capacity) {
    this->capacity = capacity;
    size = 0;

    if (capacity > 0) {
        data = new string[capacity];
    }
    else {
        data = nullptr;
    }
}

DynArray::~DynArray() {
    delete[] data;
}

void DynArray::addAtIndex(const int& index, const string& newData) {
    if (index < 0 || index > size) {
        return;
    }

    if (capacity == size) {
        int newCapacity = (capacity == 0) ? 1 : capacity * 2;
        auto *tempArr = new string[newCapacity];

        for (int i = 0; i < index; i++) {
            tempArr[i] = this->data[i];
        }

        tempArr[index] = newData;

        for (int i = index; i < size; i++) {
            tempArr[i + 1] = this->data[i];
        }

        delete[] this->data;
        capacity = newCapacity;
        this->data = tempArr;
    }
    else {
        for (int i = size; i > index; i--) {
            this->data[i] = this->data[i - 1];
        }

        this->data[index] = newData;
    }

    size++;
}

void DynArray::pushBackArr(const string& newData) {
    addAtIndex(size, newData);
}

auto DynArray::getElementIndex(const int& index) const -> string {
    if (index < 0 || index >= size) {
        cout << "Индекс не является элементом массива.\n";
        return "";
    }
    return data[index];
}

void DynArray::removeFromIndex(const int& index) {
    if (index < 0 || index >= size) {
        return;
    }
    for(int i = index; i < size - 1; i++) {
        data[i] = data[i + 1];
    }

    size--;
}

void DynArray::replacementElement(const int& index, const string& newValue) {
    if (index < 0 || index >= size) {
        return;
    }
    this->data[index] = newValue;
}

auto DynArray::getSize() const -> int {
    return size;
}

void DynArray::printArray() const {
    if (size == 0) {
        cout << "Массив пуст.\n";
        return;
    }

    for (int i = 0; i < size; ++i) {
        cout << data[i] << " ";
    }
    cout << "\nВсего элементов массива: " << capacity <<
    "\nИз них заполнено: " << size << "\n";
}

extern "C" {
    auto createArray() -> DynArray* {
        return new DynArray();
    }

    void destroyArray(DynArray* arr) {
        delete arr;
    }

    void arrayPushBack(DynArray* arr, const string& newData) {
        arr->pushBackArr(newData);
    }

    void arrayAddAtIndex(DynArray* arr, const int& index, const string& newData) {
        arr->addAtIndex(index, newData);
    }

    auto arrayGetElementIndex(DynArray* arr, const int& index) -> char* {
        if (arr == nullptr) {
            return nullptr;
        }
        
        string result = arr->getElementIndex(index);
        if (result.empty()) {
            return nullptr;
        }
        
        char* cstr = new char[result.length() + 1];
        size_t length = result.length();
        for (size_t i = 0; i < length; i++) {
            cstr[i] = result[i];
        }
        cstr[length] = '\0';
        
        return cstr;
    }

    void arrayRemoveIndex(DynArray* arr, const int& index) {
        arr->removeFromIndex(index);
    }

    void arrayReplacement(DynArray* arr, const int& index, const string& newValue) {
        arr->replacementElement(index, newValue);
    }

    auto arrayGetSize(DynArray* arr) -> int {
        return arr->getSize();
    }

    void arrayPrint(DynArray* arr) {
        arr->printArray();
    }
}