#include <gtest/gtest.h>
#include <sstream>
#include <fstream>
#include "array.hpp"

TEST(arrayTest, addAtIndexInputMore) {
    DynArray arr(10);

    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    arr.addAtIndex(57,"test1");

    std::string output = buffer.str();
    EXPECT_NE(output.find("Индекс неверный."), std::string::npos);

    std::cout.rdbuf(old);
}

TEST(arrayTest, addAtIndexInputLess) {
    DynArray arr(10);

    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    arr.addAtIndex(-1,"test1");

    std::string output = buffer.str();
    EXPECT_NE(output.find("Индекс неверный."), std::string::npos);

    std::cout.rdbuf(old);
}

TEST(arrayTest, addAtIndexResize) {
    DynArray arr(5);

    arr.pushBackArr("test1");
    arr.pushBackArr("test2");
    arr.pushBackArr("test3");
    arr.pushBackArr("test4");
    arr.pushBackArr("test5");
    arr.pushBackArr("test6");

    EXPECT_EQ(arr.getCap(), 10);
    
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    arr.printArray();

    std::string output = buffer.str();
    EXPECT_NE(output.find("test1"), std::string::npos);
    EXPECT_NE(output.find("test2"), std::string::npos);
    EXPECT_NE(output.find("test3"), std::string::npos);
    EXPECT_NE(output.find("test4"), std::string::npos);
    EXPECT_NE(output.find("test5"), std::string::npos);

    std::cout.rdbuf(old);
}

TEST(arrayTest, addAtIndexZero) {
    DynArray arr(0);

    arr.pushBackArr("test1");

    EXPECT_EQ(arr.getSize(), 1);
    
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    arr.printArray();

    std::string output = buffer.str();
    EXPECT_NE(output.find("test1"), std::string::npos);

    std::cout.rdbuf(old);
}

TEST(arrayTest, createEmptyArr) {
    DynArray arr;

    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    arr.printArray();

    std::string output = buffer.str();
    EXPECT_NE(output.find("Массив пуст."), std::string::npos);   

    std::cout.rdbuf(old);
}

TEST(arrayTest, getElementInputMore) {
    DynArray arr(5);

    arr.pushBackArr("test1");
    arr.pushBackArr("test2");
    arr.pushBackArr("test3");
    arr.pushBackArr("test4");

    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    std::string returned = arr.getElementIndex(57);
    arr.getElementIndex(57);

    std::string output = buffer.str();
    EXPECT_EQ(returned, "");
    EXPECT_NE(output.find("Индекс не является элементом массива."), std::string::npos);  
    
    std::cout.rdbuf(old);    
}

TEST(arrayTest, getElementInputLess) {
    DynArray arr(5);

    arr.pushBackArr("test1");
    arr.pushBackArr("test2");
    arr.pushBackArr("test3");
    arr.pushBackArr("test4");

    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    arr.getElementIndex(-5);

    std::string output = buffer.str();
    EXPECT_NE(output.find("Индекс не является элементом массива."), std::string::npos);  
    
    std::cout.rdbuf(old);    
}

TEST(arrayTest, getElement) {
    DynArray arr(5);

    arr.pushBackArr("test1");
    arr.pushBackArr("test2");
    arr.pushBackArr("test3");
    arr.pushBackArr("test4");

    std::string returned = arr.getElementIndex(2);

    EXPECT_EQ(returned, "test3");  
}

TEST(arrayTest, removeIndexInputMore) {
    DynArray arr(5);

    arr.pushBackArr("test1");
    arr.pushBackArr("test2");
    arr.pushBackArr("test3");
    arr.pushBackArr("test4");

    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    arr.removeFromIndex(57);

    std::string output = buffer.str();
    EXPECT_NE(output.find("Индекс не является элементом массива."), std::string::npos);  
    
    std::cout.rdbuf(old);  
}

TEST(arrayTest, removeIndexInputLess) {
    DynArray arr(5);

    arr.pushBackArr("test1");
    arr.pushBackArr("test2");
    arr.pushBackArr("test3");
    arr.pushBackArr("test4");

    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    arr.removeFromIndex(-57);

    std::string output = buffer.str();
    EXPECT_NE(output.find("Индекс не является элементом массива."), std::string::npos);  
    
    std::cout.rdbuf(old);  
}

TEST(arrayTest, removeIndex) {
    DynArray arr(5);

    arr.pushBackArr("test1");
    arr.pushBackArr("test2");
    arr.pushBackArr("test3");
    arr.pushBackArr("test4");
    
    arr.removeFromIndex(1);

    EXPECT_EQ(arr.getSize(), 3);
    EXPECT_EQ(arr.getElementIndex(1), "test3");
}

TEST(arrayTest, replacementInputLess) {
    DynArray arr(5);

    arr.pushBackArr("test1");
    arr.pushBackArr("test2");
    arr.pushBackArr("test3");
    arr.pushBackArr("test4");

    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    arr.replacementElement(-57,"77");

    std::string output = buffer.str();
    EXPECT_NE(output.find("Индекс не является элементом массива."), std::string::npos);  
    
    std::cout.rdbuf(old);  
}

TEST(arrayTest, replacementInputMore) {
    DynArray arr(5);

    arr.pushBackArr("test1");
    arr.pushBackArr("test2");
    arr.pushBackArr("test3");
    arr.pushBackArr("test4");

    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    arr.replacementElement(57,"77");

    std::string output = buffer.str();
    EXPECT_NE(output.find("Индекс не является элементом массива."), std::string::npos);  
    
    std::cout.rdbuf(old);  
}

TEST(arrayTest, replacement) {
    DynArray arr(5);

    arr.pushBackArr("test1");
    arr.pushBackArr("test2");
    arr.pushBackArr("test3");
    arr.pushBackArr("test4");
    
    arr.replacementElement(1, "77");

    EXPECT_EQ(arr.getElementIndex(1), "77");
}
