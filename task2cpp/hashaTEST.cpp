#include <gtest/gtest.h>
#include <sstream>
#include <fstream>
#include "hashaddress.hpp"

TEST(hashcTest, inputSingle) {
    HashA table;
    table.addElementA("ww1", 77);

    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    table.printHashTableA();

    std::string output = buffer.str();

    EXPECT_NE(output.find("Хэш-таблица, размер: 1, вместимость: 8):"), std::string::npos);
    EXPECT_NE(output.find("[ww1 -> 77]"), std::string::npos);

    std::cout.rdbuf(old);
}

TEST(hashcTest, inputMany) {
    HashA table;
    table.addElementA("ww1", 77);
    table.addElementA("ww1", 777);
    table.addElementA("ww1", 7777);
    table.addElementA("ww2", 666);
    table.addElementA("ww3", 555);
    table.addElementA("ww4", 44);

    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    table.printHashTableA();

    std::string output = buffer.str();

    EXPECT_NE(output.find("Хэш-таблица, размер: 4, вместимость: 8):"), std::string::npos);
    EXPECT_NE(output.find("[ww1 -> 7777]"), std::string::npos);
    EXPECT_NE(output.find("[ww2 -> 666]"), std::string::npos);
    EXPECT_NE(output.find("[ww3 -> 555]"), std::string::npos);
    EXPECT_NE(output.find("[ww4 -> 44]"), std::string::npos);

    std::cout.rdbuf(old);
}

TEST(hashcTest, search) {
    HashA table;
    table.addElementA("ww1", 7777);
    table.addElementA("ww2", 666);
    table.addElementA("ww3", 555);
    table.addElementA("ww4", 44);

    int result = table.findElementA("ww4");

    EXPECT_EQ(result, 44);
}

TEST(hashcTest, searchNotFound) {
    HashA table;
    table.addElementA("ww1", 7777);
    table.addElementA("ww2", 666);
    table.addElementA("ww3", 555);
    table.addElementA("ww4", 44);

    int result = table.findElementA("ww44");

    EXPECT_EQ(result, -1);
}

TEST(hashcTest, deleteFromTable) {
    HashA table;
    table.addElementA("ww1", 77);
    table.addElementA("ww2", 666);
    table.addElementA("ww23", 666);
    table.addElementA("ww21", 666);
    table.addElementA("ww3", 555);
    table.addElementA("ww4", 44);

    table.deleteElementA("ww2");
    table.deleteElementA("ww4");

    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    table.printHashTableA();

    std::string output = buffer.str();

    EXPECT_NE(output.find("Хэш-таблица, размер: 4, вместимость: 8):"), std::string::npos);
    EXPECT_NE(output.find("[ww1 -> 77]"), std::string::npos);
    EXPECT_NE(output.find("[ww3 -> 555]"), std::string::npos);
    EXPECT_NE(output.find("[ww23 -> 666]"), std::string::npos);
    EXPECT_NE(output.find("[ww21 -> 666]"), std::string::npos);

    std::cout.rdbuf(old);
}

TEST(hashcTest, deleteSingle) {
    HashA table;
    table.addElementA("ww1", 77);

    table.deleteElementA("ww1");

    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    table.printHashTableA();

    std::string output = buffer.str();

    EXPECT_NE(output.find("Хэш-таблица, размер: 0, вместимость: 8):"), std::string::npos); 

    std::cout.rdbuf(old);
}

TEST(hashcTest, inputRehash) {
    HashA table;
    table.addElementA("ww1", 77);
    table.addElementA("ww1", 777);
    table.addElementA("ww1", 7777);
    table.addElementA("ww2", 666);
    table.addElementA("ww3", 555);
    table.addElementA("ww4", 41);
    table.addElementA("ww44", 42);
    table.addElementA("ww444", 43);
    table.addElementA("ww4444", 44);
    table.addElementA("ww41", 45);
    table.addElementA("ww411", 46);

    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    table.printHashTableA();

    std::string output = buffer.str();

    EXPECT_NE(output.find("Хэш-таблица, размер: 9, вместимость: 16):"), std::string::npos);
    EXPECT_NE(output.find("[ww1 -> 7777]"), std::string::npos);
    EXPECT_NE(output.find("[ww2 -> 666]"), std::string::npos);
    EXPECT_NE(output.find("[ww3 -> 555]"), std::string::npos);
    EXPECT_NE(output.find("[ww4 -> 41]"), std::string::npos);
    EXPECT_NE(output.find("[ww44 -> 42]"), std::string::npos);
    EXPECT_NE(output.find("[ww444 -> 43]"), std::string::npos);
    EXPECT_NE(output.find("[ww4444 -> 44]"), std::string::npos);
    EXPECT_NE(output.find("[ww41 -> 45]"), std::string::npos);
    EXPECT_NE(output.find("[ww411 -> 46]"), std::string::npos);

    std::cout.rdbuf(old);
}

TEST(hashcTest, createNode) {
    HashA table;
    HANode* node = new HANode("ww1", 77);
    table.addElementA(node->key, node->data);

    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    table.printHashTableA();

    std::string output = buffer.str();

    EXPECT_NE(output.find("Хэш-таблица, размер: 1, вместимость: 8):"), std::string::npos);
    EXPECT_NE(output.find("[ww1 -> 77]"), std::string::npos);

    std::cout.rdbuf(old);
}