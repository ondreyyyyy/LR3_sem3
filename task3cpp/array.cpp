#include "array.hpp"
#include <iostream>
#include <stdexcept>
#include <string>
#include <cstring>
#include <fstream>

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

auto DynArray::getCapacity() const -> int { 
    return capacity;
}

void DynArray::addAtIndex(const int& index, const string& newData) {
    if (index < 0 || index > size) {
        cout << "Индекс неверный.\n";
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

bool DynArray::MserializeToText(const string& filename, const string& arrayName) {
    ofstream file(filename, ios::app);
    if (!file.is_open()) { 
        cout << "Ошибка при попытке открытия файла '" << filename << "' со структурой.\n";
        return false;
    }

    file << "ARRAY " << arrayName << " "; 

    file << size << " ";
    file << capacity << " ";
    for (int i = 0; i < size; i++) {
        file << data[i] << " ";
    }
    file << "\n"; 
    file.close();
    cout << "Массив '" << arrayName << "' успешно сохранен в файл '" << filename << "'\n";
    return true;
}

bool DynArray::MdeserializeFromText(const string& filename, const string& arrayName) {
    ifstream file(filename);
    if (!file.is_open()) {  
        cout << "Ошибка при попытке открытия файла '" << filename << "' со структурой.\n";
        return false;
    }

    string type, name;
    while (file >> type) {
        if (type == "ARRAY") {
            file >> name;
            if (name == arrayName) {
                int newSize, newCapacity;
                file >> newSize;
                file >> newCapacity;
                
                if (newSize < 0 || newCapacity < newSize || newCapacity <= 0) {
                    cout << "Ошибка: некорректные размеры массива в файле\n";
                    file.close();
                    return false;
                }
                
                delete[] data;
                
                size = newSize;
                capacity = newCapacity;
                data = new string[capacity];

                for (int i = 0; i < size; i++) {
                    if (file.eof()) {
                        cout << "Ошибка: недостаточно данных в файле\n";
                        delete[] data;
                        data = nullptr;
                        size = capacity = 0;
                        file.close();
                        return false;
                    }
                    file >> data[i];
                }
                
                file.close();
                cout << "Массив '" << arrayName << "' успешно загружен из файла\n";
                return true;
            }
        }
        
        string line;
        getline(file, line);
    }
    
    file.close();
    cout << "Массив с именем '" << arrayName << "' не найден в файле '" << filename << "'\n";
    return false;
}

bool DynArray::MserializeToBinary(const string& filename, const string& arrayName) {
    ofstream file(filename, ios::binary | ios::app);
    if (!file.is_open()) {
        cout << "Ошибка при открытии бинарного файла.\n";
        return false;
    }

    string type = "ARRAY";
    size_t typeLength = type.length();
    file.write(reinterpret_cast<const char*>(&typeLength), sizeof(typeLength));
    file.write(type.c_str(), typeLength);

    size_t nameLength = arrayName.length();
    file.write(reinterpret_cast<const char*>(&nameLength), sizeof(nameLength));
    file.write(arrayName.c_str(), nameLength);

    file.write(reinterpret_cast<const char*>(&size), sizeof(size));
    file.write(reinterpret_cast<const char*>(&capacity), sizeof(capacity));

    for (int i = 0; i < size; i++) {
        size_t strLength = data[i].length();
        file.write(reinterpret_cast<const char*>(&strLength), sizeof(strLength));
        file.write(data[i].c_str(), strLength);
    }

    file.close();
    cout << "Массив " << arrayName << " успешно сохранен в бинарный файл " << filename << "\n";
    return true;
}

bool DynArray::MdeserializeFromBinary(const string& filename, const string& arrayName) {
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

        if (type != "ARRAY") {
            continue;
        }

        size_t nameLength;
        file.read(reinterpret_cast<char*>(&nameLength), sizeof(nameLength));
        string currentName(nameLength, '\0');
        file.read(&currentName[0], nameLength);

        if (currentName == arrayName) {
            int newSize, newCapacity;
            file.read(reinterpret_cast<char*>(&newSize), sizeof(newSize));
            file.read(reinterpret_cast<char*>(&newCapacity), sizeof(newCapacity));

            if (newSize < 0 || newCapacity < newSize || newCapacity < 0) {
                cout << "Ошибка: некорректные размеры массива в бинарном файле\n";
                file.close();
                return false;
            }

            delete[] data;

            size = newSize;
            capacity = newCapacity;
            data = new string[capacity];

            for (int i = 0; i < size; i++) {
                if (file.eof()) {
                    cout << "Недостаточно данных в бинарном файле\n";
                    delete[] data;
                    data = nullptr;
                    size = capacity = 0;
                    file.close();
                    return false;
                }
                
                size_t strLength;
                file.read(reinterpret_cast<char*>(&strLength), sizeof(strLength));
                
                string value(strLength, '\0');
                file.read(&value[0], strLength);
                data[i] = value;
            }

            file.close();
            cout << "Массив " << arrayName << " успешно загружен из бинарного файла\n.";
            return true;
        }
        else {
            int skipSize, skipCapacity;
            file.read(reinterpret_cast<char*>(&skipSize), sizeof(skipSize));
            file.read(reinterpret_cast<char*>(&skipCapacity), sizeof(skipCapacity));

            for (int i = 0; i < skipSize; i++) {
                size_t strLength;
                file.read(reinterpret_cast<char*>(&strLength), sizeof(strLength));
                file.seekg(strLength, ios::cur);
            }
        }
    }

    file.close();
    cout << "Массив с именем '" << arrayName << "' не найден в бинарном файле '" << filename << "'\n";
    return false;
}

bool DynArray::MsaveToFile(const string& filename, const string& arrayName) {
    if (filename.length() >= 4 && filename.substr(filename.length() - 4) == ".bin") {
        return MserializeToBinary(filename, arrayName);
    } else {
        return MserializeToText(filename, arrayName);
    }
}

bool DynArray::MloadFromFile(const string& filename, const string& arrayName) {
    if (filename.length() >= 4 && filename.substr(filename.length() - 4) == ".bin") {
        return MdeserializeFromBinary(filename, arrayName);
    } else {
        return MdeserializeFromText(filename, arrayName);
    }
}