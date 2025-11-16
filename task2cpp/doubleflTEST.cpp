#include <gtest/gtest.h>
#include <sstream>
#include <fstream>
#include "doubleFL.hpp"

TEST(dflTEST, addHeadEmpty) {
    doubleFL dfl;

    dfl.addAtHead("test1");

    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    dfl.printDoubleFL();

    std::string output = buffer.str();

    EXPECT_NE(output.find("test1"), std::string::npos);

    std::cout.rdbuf(old);
}

TEST(dflTEST, addHead) {
    doubleFL dfl;

    dfl.addAtHead("test1");
    dfl.addAtHead("test2");

    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    dfl.printDoubleFL();

    std::string output = buffer.str();

    EXPECT_NE(output.find("test2 test1"), std::string::npos);

    std::cout.rdbuf(old);
}

TEST(dflTEST, printEmpty) {
    doubleFL dfl;

    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    dfl.printDoubleFL();

    std::string output = buffer.str();

    EXPECT_NE(output.find("Список пуст"), std::string::npos);

    std::cout.rdbuf(old);
}

TEST(dflTEST, addTailEmpty) {
    doubleFL dfl;

    dfl.addAtTail("test1");

    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    dfl.printDoubleFL();

    std::string output = buffer.str();

    EXPECT_NE(output.find("test1"), std::string::npos);

    std::cout.rdbuf(old);
}

TEST(dflTEST, addTail) {
    doubleFL dfl;

    dfl.addAtTail("test1");
    dfl.addAtTail("test2");

    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    dfl.printDoubleFL();

    std::string output = buffer.str();

    EXPECT_NE(output.find("test1 test2"), std::string::npos);

    std::cout.rdbuf(old);
}

TEST(dflTest, searchEmpty) {
    doubleFL dfl;  
    
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    
    dfl.searchValue("test1");

    std::string output = buffer.str();
    EXPECT_NE(output.find("Список пуст."), std::string::npos);

    std::cout.rdbuf(old);
}

TEST(dflTest, searchNotFound) {
    doubleFL dfl;  

    dfl.addAtTail("test1");
    dfl.addAtTail("test2");
    dfl.addAtTail("test3");
    
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    
    dfl.searchValue("77");

    std::string output = buffer.str();
    EXPECT_NE(output.find("Элемент не найден."), std::string::npos);

    std::cout.rdbuf(old);
}

TEST(dflTest, searchValue) {
    doubleFL dfl;  

    dfl.addAtTail("test1");
    dfl.addAtTail("test2");
    dfl.addAtTail("test3");
    
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    
    dfl.searchValue("test2");

    std::string output = buffer.str();
    EXPECT_NE(output.find("Элемент test2 найден. Индекс: 1"), std::string::npos);

    std::cout.rdbuf(old);
}

TEST(dflTest, addBeforeInputErr) {
    doubleFL dfl;  
    
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    
    dfl.addBeforeIndex("test1", -5);

    std::string output = buffer.str();
    EXPECT_NE(output.find("Неверный индекс!"), std::string::npos);

    std::cout.rdbuf(old);
}

TEST(dflTest, addBeforeEmpty) {
    doubleFL dfl;  
    
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    
    dfl.addBeforeIndex("test1", 1);

    std::string output = buffer.str();
    EXPECT_NE(output.find("Список пуст."), std::string::npos);

    std::cout.rdbuf(old);
}

TEST(dflTest, addBeforeZero) {
    doubleFL dfl;  

    dfl.addAtTail("test1");
    dfl.addAtTail("test2");
    dfl.addAtTail("test3");

    dfl.addBeforeIndex("test77", 0);
    
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    dfl.searchValue("test77");

    std::string output = buffer.str();
    EXPECT_NE(output.find("Элемент test77 найден. Индекс: 0"), std::string::npos);

    std::cout.rdbuf(old);
}

TEST(dflTest, addBefore) {
    doubleFL dfl;  

    dfl.addAtTail("test1");
    dfl.addAtTail("test2");
    dfl.addAtTail("test3");

    dfl.addBeforeIndex("test77", 1);
    
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    dfl.searchValue("test77");

    std::string output = buffer.str();
    EXPECT_NE(output.find("Элемент test77 найден. Индекс: 1"), std::string::npos);

    std::cout.rdbuf(old);
}

TEST(dflTest, addBeforeInputErrIdx) {
    doubleFL dfl;  
    
    dfl.addAtTail("test1");
    dfl.addAtTail("test2");
    dfl.addAtTail("test3");

    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    
    dfl.addBeforeIndex("test77", 5);

    std::string output = buffer.str();
    EXPECT_NE(output.find("Элемента с таким индексом не существует!"), std::string::npos);

    std::cout.rdbuf(old);
}

TEST(dflTest, addAfterInputErr) {
    doubleFL dfl;  
    
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    
    dfl.addAfterIndex("test1", -5);

    std::string output = buffer.str();
    EXPECT_NE(output.find("Неверный индекс!"), std::string::npos);

    std::cout.rdbuf(old);
}

TEST(dflTest, addAfterEmpty) {
    doubleFL dfl;  
    
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    
    dfl.addAfterIndex("test1", 1);

    std::string output = buffer.str();
    EXPECT_NE(output.find("Список пуст."), std::string::npos);

    std::cout.rdbuf(old);
}

TEST(dflTest, addAfterTail) {
    doubleFL dfl;  

    dfl.addAtTail("test1");
    dfl.addAtTail("test2");
    dfl.addAtTail("test3");

    dfl.addAfterIndex("test77", 2);
    
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    dfl.searchValue("test77");

    std::string output = buffer.str();
    EXPECT_NE(output.find("Элемент test77 найден. Индекс: 3"), std::string::npos);

    std::cout.rdbuf(old);
}

TEST(dflTest, addAfter) {
    doubleFL dfl;  

    dfl.addAtTail("test1");
    dfl.addAtTail("test2");
    dfl.addAtTail("test3");

    dfl.addAfterIndex("test77", 1);
    
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    dfl.searchValue("test77");

    std::string output = buffer.str();
    EXPECT_NE(output.find("Элемент test77 найден. Индекс: 2"), std::string::npos);

    std::cout.rdbuf(old);
}

TEST(dflTest, addAfterInputErrIdx) {
    doubleFL dfl;  
    
    dfl.addAtTail("test1");
    dfl.addAtTail("test2");
    dfl.addAtTail("test3");

    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    
    dfl.addAfterIndex("test77", 5);

    std::string output = buffer.str();
    EXPECT_NE(output.find("Элемента с таким индексом не существует!"), std::string::npos);

    std::cout.rdbuf(old);
}

TEST(dflTest, deleteHeadEmpty) {
    doubleFL dfl;  
    
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    
    dfl.deleteAtHead();

    std::string output = buffer.str();
    EXPECT_NE(output.find("Список пуст."), std::string::npos);

    std::cout.rdbuf(old);
}

TEST(dflTest, deleteHeadSingle) {
    doubleFL dfl;  

    dfl.addAtTail("test1");

    dfl.deleteAtHead();
    
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    dfl.printDoubleFL();

    std::string output = buffer.str();
    EXPECT_NE(output.find("Список пуст"), std::string::npos);

    std::cout.rdbuf(old);
}

TEST(dflTest, deleteHead) {
    doubleFL dfl;  

    dfl.addAtTail("test1");
    dfl.addAtTail("test2");

    dfl.deleteAtHead();
    
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    dfl.printDoubleFL();

    std::string output = buffer.str();
    EXPECT_NE(output.find("test2"), std::string::npos);

    std::cout.rdbuf(old);
}

TEST(dflTest, deleteTailEmpty) {
    doubleFL dfl;  
    
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    
    dfl.deleteAtTail();

    std::string output = buffer.str();
    EXPECT_NE(output.find("Список пуст."), std::string::npos);

    std::cout.rdbuf(old);
}

TEST(dflTest, deleteTailSingle) {
    doubleFL dfl;  

    dfl.addAtTail("test1");

    dfl.deleteAtTail();
    
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    dfl.printDoubleFL();

    std::string output = buffer.str();
    EXPECT_NE(output.find("Список пуст"), std::string::npos);

    std::cout.rdbuf(old);
}

TEST(dflTest, deleteTail) {
    doubleFL dfl;  

    dfl.addAtTail("test1");
    dfl.addAtTail("test2");
    dfl.addAtTail("test3");

    dfl.deleteAtTail();
    
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    dfl.printDoubleFL();

    std::string output = buffer.str();
    EXPECT_NE(output.find("test1 test2"), std::string::npos);

    std::cout.rdbuf(old);
}

TEST(dflTest, deleteBeforeInputErr) {
    doubleFL dfl;

    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    dfl.deleteBeforeIndex(2);

    std::string output = buffer.str();
    
    EXPECT_NE(output.find("Удаление невозможно."), std::string::npos);

    std::cout.rdbuf(old);
}

TEST(dflTest, deleteBeforeInputErrZero) {
    doubleFL dfl;

    dfl.addAtTail("test1");
    dfl.addAtTail("test2");
    dfl.addAtTail("test3");

    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    dfl.deleteBeforeIndex(0);

    std::string output = buffer.str();
    
    EXPECT_NE(output.find("Неверный индекс."), std::string::npos);

    std::cout.rdbuf(old);
}

TEST(dflTest, deleteBeforeNotFound) {
    doubleFL dfl;

    dfl.addAtTail("test1");
    dfl.addAtTail("test2");
    dfl.addAtTail("test3");

    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    dfl.deleteBeforeIndex(5);

    std::string output = buffer.str();
    
    EXPECT_NE(output.find("Неверный индекс."), std::string::npos);

    std::cout.rdbuf(old);
}

TEST(dflTest, deleteBeforeInputHead) {
    doubleFL dfl;

    dfl.addAtTail("test1");
    dfl.addAtTail("test2");
    dfl.addAtTail("test3");

    dfl.deleteBeforeIndex(1);

    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    dfl.printDoubleFL();

    std::string output = buffer.str();

    EXPECT_NE(output.find("test2 test3"), std::string::npos);

    std::cout.rdbuf(old);
}

TEST(dflTest, deleteBefore) {
    doubleFL dfl;

    dfl.addAtTail("test1");
    dfl.addAtTail("test2");
    dfl.addAtTail("test3");

    dfl.deleteBeforeIndex(2);

    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    dfl.printDoubleFL();

    std::string output = buffer.str();

    EXPECT_NE(output.find("test1 test3"), std::string::npos);

    std::cout.rdbuf(old);
}


TEST(dflTest, deleteValue) {
    doubleFL dfl;

    dfl.addAtTail("test1");
    dfl.addAtTail("test2");
    dfl.addAtTail("test3");

    dfl.deleteValue("test2");

    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    dfl.printDoubleFL();

    std::string output = buffer.str();

    EXPECT_NE(output.find("test1"), std::string::npos);
    EXPECT_EQ(output.find("test2"), std::string::npos);
    EXPECT_NE(output.find("test3"), std::string::npos);

    std::cout.rdbuf(old);
}

TEST(dflTest, deleteValueEmpty) {
    doubleFL dfl;

    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    dfl.deleteValue("test2");

    std::string output = buffer.str();

    EXPECT_NE(output.find("Список пуст."), std::string::npos);

    std::cout.rdbuf(old);
}

TEST(dflTest, deleteValueInputErr) {
    doubleFL dfl;

    dfl.addAtTail("test1");
    dfl.addAtTail("test2");
    dfl.addAtTail("test3");

    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    dfl.deleteValue("test77");

    std::string output = buffer.str();

    EXPECT_NE(output.find("Элемент не найден."), std::string::npos);

    std::cout.rdbuf(old);
}

TEST(dflTest, deleteValueInputHead) {
    doubleFL dfl;

    dfl.addAtTail("test1");
    dfl.addAtTail("test2");
    dfl.addAtTail("test3");

    dfl.deleteValue("test1");

    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    std::string output = buffer.str();

    dfl.printDoubleFL();

    EXPECT_EQ(output.find("test1"), std::string::npos);

    std::cout.rdbuf(old);
}

TEST(dflTest, deleteValueInputTail) {
    doubleFL dfl;

    dfl.addAtTail("test1");
    dfl.addAtTail("test2");
    dfl.addAtTail("test3");

    dfl.deleteValue("test3");

    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    dfl.printDoubleFL();

    std::string output = buffer.str();

    EXPECT_EQ(output.find("test3"), std::string::npos);

    std::cout.rdbuf(old);
}

TEST(dflTest, deleteAfterInputErr) {
    doubleFL dfl;

    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    dfl.deleteAfterIndex(2);

    std::string output = buffer.str();
    
    EXPECT_NE(output.find("Удаление невозможно."), std::string::npos);

    std::cout.rdbuf(old);
}

TEST(dflTest, deleteAfterInputErrMinus) {
    doubleFL dfl;

    dfl.addAtTail("test1");
    dfl.addAtTail("test2");
    dfl.addAtTail("test3");

    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    dfl.deleteAfterIndex(-1);

    std::string output = buffer.str();
    
    EXPECT_NE(output.find("Неверный индекс."), std::string::npos);

    std::cout.rdbuf(old);
}

TEST(dflTest, deleteAfterNotFound) {
    doubleFL dfl;

    dfl.addAtTail("test1");
    dfl.addAtTail("test2");
    dfl.addAtTail("test3");

    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    dfl.deleteAfterIndex(5);

    std::string output = buffer.str();
    
    EXPECT_NE(output.find("Неверный индекс."), std::string::npos);

    std::cout.rdbuf(old);
}

TEST(dflTest, deleteAfterInputTail) {
    doubleFL dfl;

    dfl.addAtTail("test1");
    dfl.addAtTail("test2");
    dfl.addAtTail("test3");

    dfl.deleteAfterIndex(1);

    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    dfl.printDoubleFL();

    std::string output = buffer.str();

    EXPECT_NE(output.find("test1"), std::string::npos);
    EXPECT_NE(output.find("test2"), std::string::npos);
    EXPECT_EQ(output.find("test3"), std::string::npos);

    std::cout.rdbuf(old);
}

TEST(dflTest, deleteAfter) {
    doubleFL dfl;

    dfl.addAtTail("test1");
    dfl.addAtTail("test2");
    dfl.addAtTail("test3");

    dfl.deleteAfterIndex(0);

    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    dfl.printDoubleFL();

    std::string output = buffer.str();

    EXPECT_NE(output.find("test1"), std::string::npos);
    EXPECT_EQ(output.find("test2"), std::string::npos);
    EXPECT_NE(output.find("test3"), std::string::npos);

    std::cout.rdbuf(old);
}