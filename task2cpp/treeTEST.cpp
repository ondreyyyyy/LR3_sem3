#include <gtest/gtest.h>
#include "tree.hpp"
#include <sstream>
#include <random>
#include <stdexcept>

std::string captureOutput(std::function<void()> func) {
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    func();
    std::cout.rdbuf(old);
    return buffer.str();
}

TEST(TreeTests, EmptyTreePrint) {
    Tree tree;
    std::string output = captureOutput([&]() { tree.printTree(); });
    EXPECT_NE(output.find("Дерево пустое"), std::string::npos);
}

TEST(TreeTests, InsertSingleNode) {
    Tree tree;
    tree.insert(10);
    auto node = tree.findNode(10);
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->key, 10);
    EXPECT_EQ(node->color, BLACK);
}

TEST(TreeTests, DuplicateInsertIgnored) {
    Tree tree;
    tree.insert(8);
    tree.insert(8);
    int count = 0;
    if (tree.findNode(8) != tree.nil) count++;
    EXPECT_EQ(count, 1);
}

TEST(TreeTests, FindExistingAndMissing) {
    Tree tree;
    tree.insert(4);
    EXPECT_NE(tree.findNode(4), tree.nil);
    EXPECT_EQ(tree.findNode(99), tree.nil);
}

TEST(TreeTests, FindNodeVOutput) {
    Tree tree;
    tree.insert(20);
    std::string found = captureOutput([&]() { tree.findNodeV(20); });
    std::string notFound = captureOutput([&]() { tree.findNodeV(99); });
    EXPECT_NE(found.find("найден"), std::string::npos);
    EXPECT_NE(notFound.find("не найден"), std::string::npos);
}

TEST(TreeTests, FindMinMax) {
    Tree tree;
    tree.insert(10);
    tree.insert(2);
    tree.insert(15);
    auto minNode = tree.findMinimum(tree.root);
    auto maxNode = tree.findMaximum(tree.root);
    EXPECT_EQ(minNode->key, 2);
    EXPECT_EQ(maxNode->key, 15);
}

TEST(TreeTests, DeleteSingleNode) {
    Tree tree;
    tree.insert(10);
    auto node = tree.findNode(10);
    ASSERT_NE(node, tree.nil);
    tree.deleteNode(node);
    EXPECT_EQ(tree.findNode(10), tree.nil);
}

TEST(TreeTests, DeleteNilThrows) {
    Tree tree;
    EXPECT_THROW(tree.deleteNode(tree.nil), std::runtime_error);
}

TEST(TreeTests, DeleteNodeWithChildren) {
    Tree tree;
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.insert(12);
    auto node = tree.findNode(10);
    tree.deleteNode(node);
    EXPECT_EQ(tree.findNode(10), tree.nil);
}

TEST(TreeTests, PrintTreeStructure) {
    Tree tree;
    tree.insert(10);
    tree.insert(5);
    std::string output = captureOutput([&]() { tree.printTree(); });
    EXPECT_NE(output.find("10"), std::string::npos);
    EXPECT_NE(output.find("5"), std::string::npos);
    EXPECT_NE(output.find("nil"), std::string::npos);
}

TEST(TreeTests, InsertFixupUncleRed) {
    Tree tree;
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.insert(1);
    auto node1 = tree.findNode(1);
    EXPECT_NE(node1, tree.nil);
    EXPECT_EQ(tree.root->color, BLACK);
}

TEST(TreeTests, RotateCheck) {
    Tree tree;

    for (int i = 0; i < 30; i++) {
        tree.insert(i);
    }

    std::string output = captureOutput([&]() { tree.printTree(); });

    for (int i = 0; i < 30; i++) {
        EXPECT_NE(tree.findNode(i), tree.nil);
    }
    
    TNode* nodeToDelete1 = tree.findNode(16);
    TNode* nodeToDelete2 = tree.findNode(4);
    TNode* nodeToDelete3 = tree.findNode(5);
    TNode* nodeToDelete4 = tree.findNode(14);
    TNode* nodeToDelete5 = tree.findNode(25);
    TNode* nodeToDelete6 = tree.findNode(13);
    TNode* nodeToDelete7 = tree.findNode(20);
    TNode* nodeToDelete8 = tree.findNode(3);
    TNode* nodeToDelete9 = tree.findNode(27);

    tree.deleteNode(nodeToDelete1);
    tree.deleteNode(nodeToDelete2);
    tree.deleteNode(nodeToDelete3);
    tree.deleteNode(nodeToDelete4);
    tree.deleteNode(nodeToDelete5);
    tree.deleteNode(nodeToDelete6);
    tree.deleteNode(nodeToDelete7);
    tree.deleteNode(nodeToDelete8);
    tree.deleteNode(nodeToDelete9);

    std::string output2 = captureOutput([&]() { tree.printTree(); });
    EXPECT_EQ(tree.findNode(16), tree.nil);
    EXPECT_EQ(tree.findNode(4), tree.nil);
    EXPECT_EQ(tree.findNode(5), tree.nil);
    EXPECT_EQ(tree.findNode(14), tree.nil);
    EXPECT_EQ(tree.findNode(25), tree.nil);
    EXPECT_EQ(tree.findNode(13), tree.nil);
    EXPECT_EQ(tree.findNode(20), tree.nil);
    EXPECT_EQ(tree.findNode(3), tree.nil);
    EXPECT_EQ(tree.findNode(27), tree.nil);
}