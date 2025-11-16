#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <string>
using namespace std;

class DynArray {
private:
    string* data;
    int size;
public:
    int capacity;
    DynArray();
    DynArray(int capacity);
    ~DynArray();

    void addAtIndex(const int& index, const string& newData);
    void pushBackArr(const string& newData);
    [[nodiscard]] auto getElementIndex(const int& index) const -> string;
    void removeFromIndex(const int& index);
    void replacementElement(const int& index, const string& newValue);
    [[nodiscard]] auto getSize() const -> int;
    void printArray() const;
};

extern "C" {
    auto createArray() -> DynArray*;
    void destroyArray(DynArray* arr);
    void arrayPushBack(DynArray* arr, const string& newData);
    void arrayAddAtIndex(DynArray* arr, const int& index, const string& newData);
    auto arrayGetElementIndex(DynArray* arr, const int& index) -> char*;
    void arrayRemoveIndex(DynArray* arr, const int& index);
    void arrayReplacement(DynArray* arr, const int& index, const string& newValue);
    auto arrayGetSize(DynArray* arr) -> int;
    void arrayPrint(DynArray* arr);
}

#endif