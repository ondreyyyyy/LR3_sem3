#include <gtest/gtest.h>
#include <sstream>
#include <fstream>
#include "onelinkedlist.hpp"

TEST(ollTest, addHeadEmpty) {
    forwardList oll;

    oll.addAtHead("test1");

    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    oll.searchNode("test1");

    std::string output = buffer.str();
    EXPECT_NE(output.find("Элемент test1 найден. Индекс: 0"), std::string::npos);

    std::cout.rdbuf(old);
}

TEST(ollTest, addHead) {
    forwardList oll;

    oll.addAtHead("test1");
    oll.addAtHead("test2");
    oll.addAtHead("test3");

    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    oll.printFL();

    std::string output = buffer.str();
    EXPECT_NE(output.find("test3"), std::string::npos);
    EXPECT_NE(output.find("test2"), std::string::npos);
    EXPECT_NE(output.find("test1"), std::string::npos);

    std::cout.rdbuf(old);
}

TEST(ollTest, addTailEmpty) {
    forwardList oll;

    oll.addAtTail("test1");

    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    oll.searchNode("test1");

    std::string output = buffer.str();
    EXPECT_NE(output.find("Элемент test1 найден. Индекс: 0"), std::string::npos);

    std::cout.rdbuf(old);
}

TEST(ollTest, addTail) {
    forwardList oll;

    oll.addAtTail("test1");
    oll.addAtTail("test2");
    oll.addAtTail("test3");

    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    oll.printFL();

    std::string output = buffer.str();
    EXPECT_NE(output.find("test1"), std::string::npos);
    EXPECT_NE(output.find("test2"), std::string::npos);
    EXPECT_NE(output.find("test3"), std::string::npos);

    std::cout.rdbuf(old);
}

TEST(ollTest, searchEmpty) {
    forwardList oll;  
    
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    
    oll.searchNode("test1");

    std::string output = buffer.str();
    EXPECT_NE(output.find("Список пуст."), std::string::npos);

    std::cout.rdbuf(old);
}

TEST(ollTest, searchNotFound) {
    forwardList oll;  

    oll.addAtTail("test1");
    oll.addAtTail("test2");
    oll.addAtTail("test3");
    
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    
    oll.searchNode("77");

    std::string output = buffer.str();
    EXPECT_NE(output.find("Элемент не найден."), std::string::npos);

    std::cout.rdbuf(old);
}

TEST(ollTest, printEmpty) {
    forwardList oll;  
    
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    
    oll.printFL();

    std::string output = buffer.str();
    EXPECT_NE(output.find("Элементов нет."), std::string::npos);

    std::cout.rdbuf(old);
}

TEST(ollTest, addBeforeInputErr) {
    forwardList oll;  
    
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    
    oll.addBeforeIndex("test1", -5);

    std::string output = buffer.str();
    EXPECT_NE(output.find("Неверный индекс!"), std::string::npos);

    std::cout.rdbuf(old);
}

TEST(ollTest, addBeforeEmpty) {
    forwardList oll;  
    
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    
    oll.addBeforeIndex("test1", 1);

    std::string output = buffer.str();
    EXPECT_NE(output.find("Список пуст."), std::string::npos);

    std::cout.rdbuf(old);
}

TEST(ollTest, addBeforeZero) {
    forwardList oll;  

    oll.addAtTail("test1");
    oll.addAtTail("test2");
    oll.addAtTail("test3");

    oll.addBeforeIndex("test77", 0);
    
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    oll.searchNode("test77");

    std::string output = buffer.str();
    EXPECT_NE(output.find("Элемент test77 найден. Индекс: 0"), std::string::npos);

    std::cout.rdbuf(old);
}

TEST(ollTest, addBefore) {
    forwardList oll;  

    oll.addAtTail("test1");
    oll.addAtTail("test2");
    oll.addAtTail("test3");

    oll.addBeforeIndex("test77", 1);
    
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    oll.searchNode("test77");

    std::string output = buffer.str();
    EXPECT_NE(output.find("Элемент test77 найден. Индекс: 1"), std::string::npos);

    std::cout.rdbuf(old);
}

TEST(ollTest, addBeforeInputErrIdx) {
    forwardList oll;  
    
    oll.addAtTail("test1");
    oll.addAtTail("test2");
    oll.addAtTail("test3");

    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    
    oll.addBeforeIndex("test77", 5);

    std::string output = buffer.str();
    EXPECT_NE(output.find("Элемента с таким индексом не существует!"), std::string::npos);

    std::cout.rdbuf(old);
}

TEST(ollTest, addAfterInputErr) {
    forwardList oll;  
    
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    
    oll.addAfterIndex("test1", -5);

    std::string output = buffer.str();
    EXPECT_NE(output.find("Неверный индекс!"), std::string::npos);

    std::cout.rdbuf(old);
}

TEST(ollTest, addAfterEmpty) {
    forwardList oll;  
    
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    
    oll.addAfterIndex("test1", 1);

    std::string output = buffer.str();
    EXPECT_NE(output.find("Список пуст."), std::string::npos);

    std::cout.rdbuf(old);
}

TEST(ollTest, addAfterTail) {
    forwardList oll;  

    oll.addAtTail("test1");
    oll.addAtTail("test2");
    oll.addAtTail("test3");

    oll.addAfterIndex("test77", 2);
    
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    oll.searchNode("test77");

    std::string output = buffer.str();
    EXPECT_NE(output.find("Элемент test77 найден. Индекс: 3"), std::string::npos);

    std::cout.rdbuf(old);
}

TEST(ollTest, addAfter) {
    forwardList oll;  

    oll.addAtTail("test1");
    oll.addAtTail("test2");
    oll.addAtTail("test3");

    oll.addAfterIndex("test77", 1);
    
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    oll.searchNode("test77");

    std::string output = buffer.str();
    EXPECT_NE(output.find("Элемент test77 найден. Индекс: 2"), std::string::npos);

    std::cout.rdbuf(old);
}

TEST(ollTest, addAfterInputErrIdx) {
    forwardList oll;  
    
    oll.addAtTail("test1");
    oll.addAtTail("test2");
    oll.addAtTail("test3");

    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    
    oll.addAfterIndex("test77", 5);

    std::string output = buffer.str();
    EXPECT_NE(output.find("Элемента с таким индексом не существует!"), std::string::npos);

    std::cout.rdbuf(old);
}

TEST(ollTest, deleteHeadEmpty) {
    forwardList oll;  
    
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    
    oll.deleteAtHead();

    std::string output = buffer.str();
    EXPECT_NE(output.find("Нечего удалять."), std::string::npos);

    std::cout.rdbuf(old);
}

TEST(ollTest, deleteHead) {
    forwardList oll;  

    oll.addAtTail("test1");

    oll.deleteAtHead();
    
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    oll.printFL();

    std::string output = buffer.str();
    EXPECT_NE(output.find("Элементов нет."), std::string::npos);

    std::cout.rdbuf(old);
}

TEST(ollTest, deleteTailEmpty) {
    forwardList oll;  
    
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    
    oll.deleteAtTail();

    std::string output = buffer.str();
    EXPECT_NE(output.find("Список пуст."), std::string::npos);

    std::cout.rdbuf(old);
}

TEST(ollTest, deleteTailSingle) {
    forwardList oll;  

    oll.addAtTail("test1");

    oll.deleteAtTail();
    
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    oll.printFL();

    std::string output = buffer.str();
    EXPECT_NE(output.find("Элементов нет."), std::string::npos);

    std::cout.rdbuf(old);
}

TEST(ollTest, deleteTail) {
    forwardList oll;  

    oll.addAtTail("test1");
    oll.addAtTail("test2");
    oll.addAtTail("test3");

    oll.deleteAtTail();
    
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    oll.printFL();

    std::string output = buffer.str();
    EXPECT_NE(output.find("test1"), std::string::npos);
    EXPECT_NE(output.find("test2"), std::string::npos);

    std::cout.rdbuf(old);
}

TEST(ollTest, deleteBeforeInputErr) {
    forwardList oll;

    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    oll.deleteBeforeIndex(2);

    std::string output = buffer.str();
    
    EXPECT_NE(output.find("Удаление невозможно."), std::string::npos);

    std::cout.rdbuf(old);
}

TEST(ollTest, deleteBeforeInputErrZero) {
    forwardList oll;

    oll.addAtTail("test1");
    oll.addAtTail("test2");
    oll.addAtTail("test3");

    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    oll.deleteBeforeIndex(0);

    std::string output = buffer.str();
    
    EXPECT_NE(output.find("Неверный индекс."), std::string::npos);

    std::cout.rdbuf(old);
}

TEST(ollTest, deleteBeforeNotFound) {
    forwardList oll;

    oll.addAtTail("test1");
    oll.addAtTail("test2");
    oll.addAtTail("test3");

    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    oll.deleteBeforeIndex(5);

    std::string output = buffer.str();
    
    EXPECT_NE(output.find("Неверный индекс."), std::string::npos);

    std::cout.rdbuf(old);
}

TEST(ollTest, deleteBeforeInputHead) {
    forwardList oll;

    oll.addAtTail("test1");
    oll.addAtTail("test2");
    oll.addAtTail("test3");

    oll.deleteBeforeIndex(1);

    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    oll.printFL();

    std::string output = buffer.str();

    EXPECT_EQ(output.find("test1"), std::string::npos);
    EXPECT_NE(output.find("test2"), std::string::npos);
    EXPECT_NE(output.find("test3"), std::string::npos);

    std::cout.rdbuf(old);
}

TEST(ollTest, deleteBefore) {
    forwardList oll;

    oll.addAtTail("test1");
    oll.addAtTail("test2");
    oll.addAtTail("test3");

    oll.deleteBeforeIndex(2);

    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    oll.printFL();

    std::string output = buffer.str();

    EXPECT_NE(output.find("test1"), std::string::npos);
    EXPECT_EQ(output.find("test2"), std::string::npos);
    EXPECT_NE(output.find("test3"), std::string::npos);

    std::cout.rdbuf(old);
}

TEST(ollTest, valueDelete) {
    forwardList oll;

    oll.addAtTail("test1");
    oll.addAtTail("test2");
    oll.addAtTail("test3");

    oll.valueDelete("test2");

    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    oll.printFL();

    std::string output = buffer.str();

    EXPECT_NE(output.find("test1"), std::string::npos);
    EXPECT_EQ(output.find("test2"), std::string::npos);
    EXPECT_NE(output.find("test3"), std::string::npos);

    std::cout.rdbuf(old);
}

TEST(ollTest, valueDeleteEmpty) {
    forwardList oll;

    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    oll.valueDelete("test2");

    std::string output = buffer.str();

    EXPECT_NE(output.find("Удаление невозможно."), std::string::npos);

    std::cout.rdbuf(old);
}

TEST(ollTest, valueDeleteInputErr) {
    forwardList oll;

    oll.addAtTail("test1");
    oll.addAtTail("test2");
    oll.addAtTail("test3");

    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    oll.valueDelete("test77");

    std::string output = buffer.str();

    EXPECT_NE(output.find("Элемент не найден."), std::string::npos);

    std::cout.rdbuf(old);
}

TEST(ollTest, valueDeleteInputHead) {
    forwardList oll;

    oll.addAtTail("test1");
    oll.addAtTail("test2");
    oll.addAtTail("test3");

    oll.valueDelete("test1");

    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    std::string output = buffer.str();

    oll.printFL();

    EXPECT_EQ(output.find("test1"), std::string::npos);

    std::cout.rdbuf(old);
}

TEST(ollTest, valueDeleteInputTail) {
    forwardList oll;

    oll.addAtTail("test1");
    oll.addAtTail("test2");
    oll.addAtTail("test3");

    oll.valueDelete("test3");

    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    oll.printFL();

    std::string output = buffer.str();

    EXPECT_EQ(output.find("test3"), std::string::npos);

    std::cout.rdbuf(old);
}

TEST(ollTest, deleteAfterInputErr) {
    forwardList oll;

    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    oll.deleteAfterIndex(2);

    std::string output = buffer.str();
    
    EXPECT_NE(output.find("Удаление невозможно."), std::string::npos);

    std::cout.rdbuf(old);
}

TEST(ollTest, deleteAfterInputErrMinus) {
    forwardList oll;

    oll.addAtTail("test1");
    oll.addAtTail("test2");
    oll.addAtTail("test3");

    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    oll.deleteAfterIndex(-1);

    std::string output = buffer.str();
    
    EXPECT_NE(output.find("Неверный индекс."), std::string::npos);

    std::cout.rdbuf(old);
}

TEST(ollTest, deleteAfterNotFound) {
    forwardList oll;

    oll.addAtTail("test1");
    oll.addAtTail("test2");
    oll.addAtTail("test3");

    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    oll.deleteAfterIndex(5);

    std::string output = buffer.str();
    
    EXPECT_NE(output.find("Неверный индекс."), std::string::npos);

    std::cout.rdbuf(old);
}

TEST(ollTest, deleteAfterInputTail) {
    forwardList oll;

    oll.addAtTail("test1");
    oll.addAtTail("test2");
    oll.addAtTail("test3");

    oll.deleteAfterIndex(1);

    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    oll.printFL();

    std::string output = buffer.str();

    EXPECT_NE(output.find("test1"), std::string::npos);
    EXPECT_NE(output.find("test2"), std::string::npos);
    EXPECT_EQ(output.find("test3"), std::string::npos);

    std::cout.rdbuf(old);
}

TEST(ollTest, deleteAfter) {
    forwardList oll;

    oll.addAtTail("test1");
    oll.addAtTail("test2");
    oll.addAtTail("test3");

    oll.deleteAfterIndex(0);

    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    oll.printFL();

    std::string output = buffer.str();

    EXPECT_NE(output.find("test1"), std::string::npos);
    EXPECT_EQ(output.find("test2"), std::string::npos);
    EXPECT_NE(output.find("test3"), std::string::npos);

    std::cout.rdbuf(old);
}

TEST(ollTest, GetHead) {
    forwardList list;
    EXPECT_EQ(list.getHead(), nullptr);
}

TEST(ollTest, GetNextAndValue) {
    FNode* next = nullptr;
    FNode node("test", next);
    EXPECT_EQ(node.getNext(), nullptr);
    EXPECT_EQ(node.getValue(), "test");
}