#ifndef TREE_HPP
#define TREE_HPP

#include <string>
#include <cstdint>

using namespace std;

enum Color : std::uint8_t {
    RED,
    BLACK
};

class TNode {
public:
    int key;
    Color color;
    TNode* left;
    TNode* right;
    TNode* parent;
    TNode(const int& key, const Color& color, TNode* parent);
};

class Tree {
private:
    void removeSubTree(TNode* node);
    void printTreeHelper(TNode* node, const string& prefix, bool isLeft, bool isRoot) const;
    void leftRotate(TNode* pivotNode);
    void rightRotate(TNode* pivotNode);
    void insertFixup(TNode* newNode);
    void deleteFixup(TNode* fixupNode);
    auto findMinimum(TNode* node) const -> TNode*;
    void handleLeftCase(TNode*& fixupNode);
    void handleLeftSubcases(TNode*& fixupNode, TNode* siblingNode);
    void handleRightCase(TNode*& fixupNode);
    void handleRightSubcases(TNode*& fixupNode, TNode* siblingNode);
    void replaceNode(TNode* oldNode, TNode* newNode);
    auto findMaximum(TNode* node) const -> TNode*;

    void treeSerializeHelperText(ofstream& file, TNode* node) const;
    void treeSerializeHelperBinary(ofstream& file, TNode* node) const;
    auto treeDeserializeHelperText(ifstream& file) -> TNode*;
    auto treeDeserializeHelperBinary(ifstream& file) -> TNode*;
    void skipTreeDataBinary(ifstream& file);
public:
    TNode* root;
    TNode* nil;
    Tree();
    ~Tree();

    void insert(const int& value);
    void findNodeV(const int& value) const;
    void deleteNode(TNode* nodeToDelete);
    auto findNode(const int& value) const -> TNode*;
    void printTree() const;

    bool treeSerializeToText(const string& filename, const string& treeName);
    bool treeSerializeToBinary(const string& filename, const string& treeName);
    bool treeDeserializeFromText(const string& filename, const string& treeName);
    bool treeDeserializeFromBinary(const string& filename, const string& treeName);
    bool treeSaveToFile(const string& filename, const string& treeName);
    bool treeLoadFromFile(const string& filename, const string& treeName);
};

#endif