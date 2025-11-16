#include "tree.hpp"
#include <iostream>
#include <stdexcept>
#include <string>
#include <fstream>

using namespace std;

TNode::TNode(const int& key, const Color& color, TNode* parent) {
    this->key = key;
    this->color = color;
    left = nullptr;
    right = nullptr;
    this->parent = parent;
}

Tree::Tree() {
    nil = new TNode(0, BLACK, nullptr);
    nil->parent = nil;
    nil->left = nil;
    nil->right = nil;
    root = nil;
}

Tree::~Tree() {
    removeSubTree(root);
    delete nil;
}

void Tree::removeSubTree(TNode* node) {
    if (node == nil) {
        return;
    }

    removeSubTree(node->left);
    removeSubTree(node->right);
    delete node;
}

void Tree::printTreeHelper(TNode* node, const string& prefix, bool isLeft, bool isRoot) const {
    if (node == nil) {
        return;
    }
    
    cout << prefix;
    
    if (isRoot) {
        cout << "└── ";
    } else {
        cout << (isLeft ? "├── " : "└── ");
    }
    
    string colorStr = (node->color == RED) ? "R" : "B";
    cout << node->key << "(" << colorStr << ")\n";
    
    string indent;

    if (isRoot || !isLeft) { 
        indent = "   ";
    }
    else { 
        indent = "|  ";
    }

    string newPrefix = prefix + indent;
    
    bool hasRight = (node->right != nil);
    bool hasLeft = (node->left != nil);
    
    if (hasRight) {
        printTreeHelper(node->right, newPrefix, true, false);
    }
    
    if (hasLeft) {
        printTreeHelper(node->left, newPrefix, false, false);
    }
    
    if (!hasRight && !hasLeft) {
        cout << newPrefix;
        if (isRoot) {
            cout << "└── ";
        } else {
            cout << (isLeft ? "├── " : "└── ");
        }
        cout << "nil\n";
    }
}

void Tree::leftRotate(TNode* pivotNode) {
    TNode* rightChild = pivotNode->right;
    pivotNode->right = rightChild->left;
    if (rightChild->left != nullptr) {
        rightChild->left->parent = pivotNode;
    }

    rightChild->parent = pivotNode->parent;
    if (pivotNode->parent == nil) {
        root = rightChild;
    }
    else if (pivotNode == pivotNode->parent->left) {
        pivotNode->parent->left = rightChild;
    }
    else {
        pivotNode->parent->right = rightChild;
    }

    rightChild->left = pivotNode;
    pivotNode->parent = rightChild;
}

void Tree::rightRotate(TNode* pivotNode) {
    TNode* leftChild = pivotNode->left;
    pivotNode->left = leftChild->right;
    if (leftChild->right != nullptr) {
        leftChild->right->parent = pivotNode;
    }

    leftChild->parent = pivotNode->parent;
    if (pivotNode->parent == nil) {
        root = leftChild;
    }
    else if (pivotNode == pivotNode->parent->left) {
        pivotNode->parent->left = leftChild;
    }
    else {
        pivotNode->parent->right = leftChild;
    }

    leftChild->right = pivotNode;
    pivotNode->parent = leftChild;
}

void Tree::insertFixup(TNode* newNode) {
    while (newNode->parent != nullptr && newNode->parent->color == RED) {
        if (newNode->parent == newNode->parent->parent->left) {
            TNode* uncleNode = newNode->parent->parent->right;
            if (uncleNode->color == RED) {
                uncleNode->color = BLACK;
                newNode->parent->color = BLACK;
                newNode->parent->parent->color = RED;
                newNode = newNode->parent->parent;
            }   
            else {
                if (newNode == newNode->parent->right) {
                    newNode = newNode->parent;
                    leftRotate(newNode);
                }

                newNode->parent->color = BLACK;
                newNode->parent->parent->color = RED;
                rightRotate(newNode->parent->parent);
            }
        }
        else {
            TNode* uncleNode = newNode->parent->parent->left;
            if (uncleNode->color == RED) {
                uncleNode->color = BLACK;
                newNode->parent->color = BLACK;
                newNode->parent->parent->color = RED;
                newNode = newNode->parent->parent;
            }
            else {
                if (newNode == newNode->parent->left) {
                    newNode = newNode->parent;
                    rightRotate(newNode);
                }

                newNode->parent->color = BLACK;
                newNode->parent->parent->color = RED;
                leftRotate(newNode->parent->parent);
            }
        }
    }
    root->color = BLACK;
}

void Tree::handleLeftCase(TNode*& fixupNode) {
    TNode* siblingNode = fixupNode->parent->right;

    // случай 1.1 - брат красный
    if (siblingNode->color == RED) {
        siblingNode->color = BLACK;
        siblingNode->parent->color = RED;
        leftRotate(fixupNode->parent);
        siblingNode = fixupNode->parent->right;
    }
    
    // случай 1.2 - оба потомка брата черные
    if (siblingNode->left->color == BLACK && siblingNode->right->color == BLACK) {
        siblingNode->color = RED;
        fixupNode = fixupNode->parent;
    }
    else {
        handleLeftSubcases(fixupNode, siblingNode);
    }
}

void Tree::handleLeftSubcases(TNode*& fixupNode, TNode* siblingNode) {
    // случай 1.3 - правый потомок брата черный
    if (siblingNode->right->color == BLACK) {
        siblingNode->left->color = BLACK;
        siblingNode->color = RED;
        rightRotate(siblingNode);
        siblingNode = fixupNode->parent->right;
    }
    
    // случай 1.4 - правый потомок брата красный
    siblingNode->color = fixupNode->parent->color;
    fixupNode->parent->color = BLACK;
    siblingNode->right->color = BLACK;
    leftRotate(fixupNode->parent);
    fixupNode = root;
}

void Tree::handleRightCase(TNode*& fixupNode) {
    TNode* siblingNode = fixupNode->parent->left;

    // случай 2.1 - брат красный
    if (siblingNode->color == RED) {
        siblingNode->color = BLACK;
        siblingNode->parent->color = RED;
        rightRotate(fixupNode->parent);
        siblingNode = fixupNode->parent->left;
    }
    
    // случай 2.2 - оба потомка брата черные
    if (siblingNode->right->color == BLACK && siblingNode->left->color == BLACK) {
        siblingNode->color = RED;
        fixupNode = fixupNode->parent;
    }
    else {
        handleRightSubcases(fixupNode, siblingNode);
    }
}

void Tree::handleRightSubcases(TNode*& fixupNode, TNode* siblingNode) {
    // случай 2.3 - левый потомок брата черный
    if (siblingNode->left->color == BLACK) {
        siblingNode->right->color = BLACK;
        siblingNode->color = RED;
        leftRotate(siblingNode);
        siblingNode = fixupNode->parent->left;
    }
    
    // случай 2.4 - левый потомок брата красный
    siblingNode->color = fixupNode->parent->color;
    fixupNode->parent->color = BLACK;
    siblingNode->left->color = BLACK;
    rightRotate(fixupNode->parent);
    fixupNode = root;
}

void Tree::deleteFixup(TNode* fixupNode) {
    while (fixupNode != root && fixupNode->color == BLACK) {
        if (fixupNode == fixupNode->parent->left) {
            handleLeftCase(fixupNode);
        }
        else {
            handleRightCase(fixupNode);
        }
    }
    fixupNode->color = BLACK;
}

auto Tree::findMinimum(TNode* node) const -> TNode* {
    while (node->left != nil) {
        node = node->left;
    }
    return node;
}

void Tree::insert(const int& value) {
    auto *newNode = new TNode(value, RED, nil); 
    newNode->left = nil;
    newNode->right = nil;
    
    TNode* parentNode = nil;
    TNode* currentNode = root;
    
    while (currentNode != nil) {
        parentNode = currentNode;
        if (newNode->key < currentNode->key) {
            currentNode = currentNode->left;
        }
        else if (newNode->key > currentNode->key) {
            currentNode = currentNode->right;
        }
        else {
            delete newNode;
            return;
        }
    }

    newNode->parent = parentNode;
    if (parentNode == nil) {
        root = newNode;
    }
    else if (newNode->key < parentNode->key) {
        parentNode->left = newNode;
    }
    else {
        parentNode->right = newNode;
    }

    insertFixup(newNode);
}


auto Tree::findNode(const int& value) const -> TNode* {
    TNode* currentNode = root;

    while (currentNode != nil && currentNode->key != value) {
        if (value < currentNode->key) {
            currentNode = currentNode->left;
        }
        else {
            currentNode = currentNode->right;
        }
    }
    return currentNode;
}

void Tree::findNodeV(const int& value) const {
    TNode* currentNode = findNode(value);
    if (currentNode == nil) {
        cout << "Узел " << value << " не найден.\n";
    }
    else {
        string colorStr = (currentNode->color == RED) ? "красный" : "черный";
        cout << "Узел " << value << " найден. ";
        cout << "Цвет: " << colorStr << "\n";
    }
}

void Tree::deleteNode(TNode* nodeToDelete) {
    if (nodeToDelete == nil) {
        throw runtime_error("Ошибка: узел не найден.\n");
    }

    TNode* nodeBeingRemoved = nodeToDelete;
    TNode* replacementNode;
    Color colorOfRemovedNode = nodeBeingRemoved->color;

    // cлучай 1: нет правого потомка
    if (nodeToDelete->right == nil) {
        replacementNode = nodeToDelete->left;
        replaceNode(nodeToDelete, replacementNode);
        delete nodeToDelete;
    }
    // cлучай 2: нет левого потомка  
    else if (nodeToDelete->left == nil) {
        replacementNode = nodeToDelete->right;
        replaceNode(nodeToDelete, replacementNode);
        delete nodeToDelete;
    }
    // cлучай 3: есть оба потомка
    else {
        nodeBeingRemoved = findMaximum(nodeToDelete->left);
        colorOfRemovedNode = nodeBeingRemoved->color;
        replacementNode = nodeBeingRemoved->left;

        if (nodeBeingRemoved->parent == nodeToDelete) {
            replacementNode->parent = nodeBeingRemoved;
        } else {
            replaceNode(nodeBeingRemoved, replacementNode);
            nodeBeingRemoved->left = nodeToDelete->left;
            nodeBeingRemoved->left->parent = nodeBeingRemoved;
        }

        replaceNode(nodeToDelete, nodeBeingRemoved);
        nodeBeingRemoved->right = nodeToDelete->right;
        nodeBeingRemoved->right->parent = nodeBeingRemoved;
        nodeBeingRemoved->color = nodeToDelete->color;
        delete nodeToDelete;
    }

    if (colorOfRemovedNode == BLACK) {
        deleteFixup(replacementNode);
    }
}

void Tree::replaceNode(TNode* oldNode, TNode* newNode) {
    if (oldNode->parent == nil) {
        root = newNode;
    }
    else if (oldNode == oldNode->parent->left) {
        oldNode->parent->left = newNode;
    }
    else {
        oldNode->parent->right = newNode;
    }
    
    if (newNode != nil) {
        newNode->parent = oldNode->parent;
    }
}

auto Tree::findMaximum(TNode* node) const -> TNode* {
    while (node->right != nil) {
        node = node->right;
    }
    return node;
}

void Tree::printTree() const {
    if (root == nil) {
        cout << "Дерево пустое\n";
        return;
    }
    cout << "Красно-черное дерево:\n";
    printTreeHelper(root, "", false, true);
}

void Tree::treeSerializeHelperText(ofstream& file, TNode* node) const {
    if (node == nil) {
        file << "N ";  // nil узел
        return;
    }
    
    file << node->key << " " << static_cast<int>(node->color) << " ";
    
    treeSerializeHelperText(file, node->left);
    treeSerializeHelperText(file, node->right);
}

void Tree::treeSerializeHelperBinary(ofstream& file, TNode* node) const {
    if (node == nil) {
        bool isNil = true;
        file.write(reinterpret_cast<const char*>(&isNil), sizeof(isNil));
        return;
    }
    
    bool isNil = false;
    file.write(reinterpret_cast<const char*>(&isNil), sizeof(isNil));
    
    file.write(reinterpret_cast<const char*>(&node->key), sizeof(node->key));
    file.write(reinterpret_cast<const char*>(&node->color), sizeof(node->color));
    
    treeSerializeHelperBinary(file, node->left);
    treeSerializeHelperBinary(file, node->right);
}

auto Tree::treeDeserializeHelperText(ifstream& file) -> TNode* {
    string token;
    file >> token;
    
    if (token == "N") {
        return nil;
    }
    
    int key = stoi(token);
    int colorInt;
    file >> colorInt;
    Color color = static_cast<Color>(colorInt);
    
    auto* newNode = new TNode(key, color, nil);
    newNode->left = nil;
    newNode->right = nil;
    
    newNode->left = treeDeserializeHelperText(file);
    newNode->right = treeDeserializeHelperText(file);
    
    if (newNode->left != nil) {
        newNode->left->parent = newNode;
    }
    if (newNode->right != nil) {
        newNode->right->parent = newNode;
    }
    
    return newNode;
}

auto Tree::treeDeserializeHelperBinary(ifstream& file) -> TNode* {
    bool isNilNode;
    if (!file.read(reinterpret_cast<char*>(&isNilNode), sizeof(isNilNode))) {
        return nil;
    }
    
    if (isNilNode) {
        return nil;
    }
    
    int key;
    Color color;
    file.read(reinterpret_cast<char*>(&key), sizeof(key));
    file.read(reinterpret_cast<char*>(&color), sizeof(color));
    
    auto* newNode = new TNode(key, color, nil);
    newNode->left = nil;
    newNode->right = nil;
    
    newNode->left = treeDeserializeHelperBinary(file);
    newNode->right = treeDeserializeHelperBinary(file);

    if (newNode->left != nil) {
        newNode->left->parent = newNode;
    }
    if (newNode->right != nil) {
        newNode->right->parent = newNode;
    }
    
    return newNode;
}

bool Tree::treeSerializeToText(const string& filename, const string& treeName) {
    ofstream file(filename, ios::app);
    if (!file.is_open()) { 
        cout << "Ошибка при попытке открытия файла '" << filename << "' со структурой.\n";
        return false;
    }

    file << "TREE " << treeName << " "; 
    treeSerializeHelperText(file, root);
    file << "\n"; 
    file.close();
    cout << "Красно-черное дерево '" << treeName << "' успешно сохранено в файл '" << filename << "'\n";
    return true;
}

bool Tree::treeDeserializeFromText(const string& filename, const string& treeName) {
    ifstream file(filename);
    if (!file.is_open()) {  
        cout << "Ошибка при попытке открытия файла '" << filename << "' со структурой.\n";
        return false;
    }

    string type, name;
    while (file >> type) {
        if (type == "TREE") {
            file >> name;
            if (name == treeName) {
                removeSubTree(root);
                root = nil;
                
                root = treeDeserializeHelperText(file);
                if (root != nil) {
                    root->parent = nil;
                }
                
                file.close();
                cout << "Красно-черное дерево '" << treeName << "' успешно загружено из файла\n";
                return true;
            }
        }
        
        string line;
        getline(file, line);
    }
    
    file.close();
    cout << "Красно-черное дерево с именем '" << treeName << "' не найдено в файле '" << filename << "'\n";
    return false;
}

bool Tree::treeSerializeToBinary(const string& filename, const string& treeName) {
    ofstream file(filename, ios::binary | ios::app);
    if (!file.is_open()) {
        cout << "Ошибка при открытии бинарного файла.\n";
        return false;
    }

    string type = "TREE";
    size_t typeLength = type.length();
    file.write(reinterpret_cast<const char*>(&typeLength), sizeof(typeLength));
    file.write(type.c_str(), typeLength);

    size_t nameLength = treeName.length();
    file.write(reinterpret_cast<const char*>(&nameLength), sizeof(nameLength));
    file.write(treeName.c_str(), nameLength);

    treeSerializeHelperBinary(file, root);

    file.close();
    cout << "Красно-черное дерево '" << treeName << "' успешно сохранено в бинарный файл '" << filename << "'\n";
    return true;
}

void Tree::skipTreeDataBinary(ifstream& file) {
    bool isNilNode;
    if (!file.read(reinterpret_cast<char*>(&isNilNode), sizeof(isNilNode))) {
        return;
    }
    
    if (isNilNode) {
        return; 
    }
    
    file.seekg(sizeof(int) + sizeof(Color), ios::cur);
    
    skipTreeDataBinary(file);
    skipTreeDataBinary(file);
}

bool Tree::treeDeserializeFromBinary(const string& filename, const string& treeName) {
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

        if (type != "TREE") {
            size_t skipNameLength;
            if (!file.read(reinterpret_cast<char*>(&skipNameLength), sizeof(skipNameLength))) {
                break;
            }
            file.seekg(skipNameLength, ios::cur);
            
            skipTreeDataBinary(file);
            continue;
        }

        size_t nameLength;
        if (!file.read(reinterpret_cast<char*>(&nameLength), sizeof(nameLength))) {
            break;
        }
        string currentName(nameLength, '\0');
        file.read(&currentName[0], nameLength);

        if (currentName == treeName) {
            removeSubTree(root);
            root = nil;
            
            root = treeDeserializeHelperBinary(file);
            if (root != nil) {
                root->parent = nil;
            }
            
            file.close();
            cout << "Красно-черное дерево '" << treeName << "' успешно загружено из бинарного файла\n";
            return true;
        }
        else {
            skipTreeDataBinary(file);
        }
    }

    file.close();
    cout << "Красно-черное дерево с именем '" << treeName << "' не найдено в бинарном файле '" << filename << "'\n";
    return false;
}

bool Tree::treeSaveToFile(const string& filename, const string& treeName) {
    if (filename.length() >= 4 && filename.substr(filename.length() - 4) == ".bin") {
        return treeSerializeToBinary(filename, treeName);
    } else {
        return treeSerializeToText(filename, treeName);
    }
}

bool Tree::treeLoadFromFile(const string& filename, const string& treeName) {
    if (filename.length() >= 4 && filename.substr(filename.length() - 4) == ".bin") {
        return treeDeserializeFromBinary(filename, treeName);
    } else {
        return treeDeserializeFromText(filename, treeName);
    }
}