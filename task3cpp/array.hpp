#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <string>
using namespace std;

class DynArray {
private:
    string* data;
    int size;
    int capacity;
public:
    DynArray();
    DynArray(int capacity);
    ~DynArray();
    [[nodiscard]] auto getCapacity() const -> int;

    void addAtIndex(const int& index, const string& newData);
    void pushBackArr(const string& newData);
    [[nodiscard]] auto getElementIndex(const int& index) const -> string;
    void removeFromIndex(const int& index);
    void replacementElement(const int& index, const string& newValue);
    [[nodiscard]] auto getSize() const -> int;
    void printArray() const;

    bool MserializeToText(const string& filename, const string& arrayName);
    bool MserializeToBinary(const string& filename, const string& arrayName);
    bool MdeserializeFromText(const string& filename, const string& arrayName);
    bool MdeserializeFromBinary(const string& filename, const string& arrayName);
    bool MsaveToFile(const string& filename, const string& arrayName);
    bool MloadFromFile(const string& filename, const string& arrayName);
};

#endif