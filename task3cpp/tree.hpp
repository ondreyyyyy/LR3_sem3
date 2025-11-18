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
private:
    int key;
    Color color;
    TNode* left;
    TNode* right;
    TNode* parent;
public:
    friend class Tree;
    TNode(const int& key, const Color& color, TNode* parent);
    [[nodiscard]] auto getKey() const -> int;
    [[nodiscard]] auto getColor() const -> Color;
    [[nodiscard]] auto getLeft() const -> TNode*;
    [[nodiscard]] auto getRight() const -> TNode*;
    [[nodiscard]] auto getParent() const -> TNode*;
};

class Tree {
private:
    TNode* root;
    TNode* nil;
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
    Tree();
    ~Tree();
    [[nodiscard]] auto getRoot() const -> TNode*;
    [[nodiscard]] auto getNil() const -> TNode*;

    void insert(const int& value);
    void findNodeV(const int& value) const;
    void deleteNode(TNode* nodeToDelete);
    [[nodiscard]] auto findNode(const int& value) const -> TNode*;
    void printTree() const;

    bool treeSerializeToText(const string& filename, const string& treeName);
    bool treeSerializeToBinary(const string& filename, const string& treeName);
    bool treeDeserializeFromText(const string& filename, const string& treeName);
    bool treeDeserializeFromBinary(const string& filename, const string& treeName);
    bool treeSaveToFile(const string& filename, const string& treeName);
    bool treeLoadFromFile(const string& filename, const string& treeName);
};

#endif