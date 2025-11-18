#include <gtest/gtest.h>
#include <sstream>
#include <fstream>
#include "hashchain.hpp"

TEST(hashcTest, inputSingle) {
    HashC table;
    table.addElement("ww1", 77);

    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    table.printHashTable();

    std::string output = buffer.str();

    EXPECT_NE(output.find("Хэш-таблица (элементов: 1, вместимость: 8):"), std::string::npos);
    EXPECT_NE(output.find("[ww1 -> 77]"), std::string::npos);

    std::cout.rdbuf(old);
}

TEST(hashcTest, inputMany) {
    HashC table;
    table.addElement("ww1", 77);
    table.addElement("ww1", 777);
    table.addElement("ww1", 7777);
    table.addElement("ww2", 666);
    table.addElement("ww3", 555);
    table.addElement("ww4", 44);

    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    table.printHashTable();

    std::string output = buffer.str();

    EXPECT_NE(output.find("Хэш-таблица (элементов: 4, вместимость: 8):"), std::string::npos);
    EXPECT_NE(output.find("[ww1 -> 7777]"), std::string::npos);
    EXPECT_NE(output.find("[ww2 -> 666]"), std::string::npos);
    EXPECT_NE(output.find("[ww3 -> 555]"), std::string::npos);
    EXPECT_NE(output.find("[ww4 -> 44]"), std::string::npos);

    std::cout.rdbuf(old);
}

TEST(hashcTest, search) {
    HashC table;
    table.addElement("ww1", 7777);
    table.addElement("ww2", 666);
    table.addElement("ww3", 555);
    table.addElement("ww4", 44);

    int result = table.findElement("ww4");

    EXPECT_EQ(result, 44);
}

TEST(hashcTest, searchNotFound) {
    HashC table;
    table.addElement("ww1", 7777);
    table.addElement("ww2", 666);
    table.addElement("ww3", 555);
    table.addElement("ww4", 44);

    int result = table.findElement("ww44");

    EXPECT_EQ(result, -1);
}

TEST(hashcTest, deleteFromTable) {
    HashC table;
    table.addElement("ww1", 77);
    table.addElement("ww2", 666);
    table.addElement("ww23", 666);
    table.addElement("ww21", 666);
    table.addElement("ww3", 555);
    table.addElement("ww4", 44);

    table.deleteElement("ww2");
    table.deleteElement("ww4");

    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    table.printHashTable();

    std::string output = buffer.str();

    EXPECT_NE(output.find("Хэш-таблица (элементов: 4, вместимость: 8):"), std::string::npos);
    EXPECT_NE(output.find("[ww1 -> 77]"), std::string::npos);
    EXPECT_NE(output.find("[ww3 -> 555]"), std::string::npos);
    EXPECT_NE(output.find("[ww23 -> 666]"), std::string::npos);
    EXPECT_NE(output.find("[ww21 -> 666]"), std::string::npos);

    std::cout.rdbuf(old);
}

TEST(hashcTest, deleteSingle) {
    HashC table;
    table.addElement("ww1", 77);

    table.deleteElement("ww1");

    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    table.printHashTable();

    std::string output = buffer.str();

    EXPECT_NE(output.find("Хэш-таблица (элементов: 0, вместимость: 8):"), std::string::npos);
    EXPECT_NE(output.find("Цепочка 0: пусто"), std::string::npos);
    EXPECT_NE(output.find("Цепочка 1: пусто"), std::string::npos);
    EXPECT_NE(output.find("Цепочка 2: пусто"), std::string::npos);
    EXPECT_NE(output.find("Цепочка 3: пусто"), std::string::npos);
    EXPECT_NE(output.find("Цепочка 4: пусто"), std::string::npos);
    EXPECT_NE(output.find("Цепочка 5: пусто"), std::string::npos);
    EXPECT_NE(output.find("Цепочка 6: пусто"), std::string::npos);
    EXPECT_NE(output.find("Цепочка 7: пусто"), std::string::npos);

    std::cout.rdbuf(old);
}

TEST(hashcTest, GetTableAndCapacity) {
    HashC hash;
    EXPECT_NE(hash.getTable(), nullptr);
    EXPECT_GT(hash.getCapacity(), 0);
}

TEST(hashcTest, GetDataPrevKeyAndNext) {
    HNode* prev = nullptr;
    HNode* next = nullptr;
    HNode node("key", 123);
    EXPECT_EQ(node.getData(), 123);
    EXPECT_EQ(node.getPrev(), nullptr);
    EXPECT_EQ(node.getKey(), "key");
    EXPECT_EQ(node.getNext(), nullptr);
}