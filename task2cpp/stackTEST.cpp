#include <gtest/gtest.h>
#include <sstream>
#include <fstream>
#include "stack.hpp"

TEST(stackTest, push) { // тест добавление
    Stack stack;
    stack.push("value1");
    stack.push("value2");
    stack.push("value3");

    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    stack.printStack();

    std::string output = buffer.str();
    EXPECT_NE(output.find("value3"), std::string::npos);
    EXPECT_NE(output.find("value2"), std::string::npos);
    EXPECT_NE(output.find("value1"), std::string::npos);

    std::cout.rdbuf(old);
}

TEST(stackTest, pop) { // тест удаление
    Stack stack;
    stack.push("value1");
    stack.push("value2");
    stack.push("value3");

    stack.pop();

    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());  
    
    stack.printStack();

    std::string output = buffer.str();
    EXPECT_NE(output.find("value2"), std::string::npos);
    EXPECT_NE(output.find("value1"), std::string::npos);

    std::cout.rdbuf(old);
}

TEST(stackTest, popEmptyStack) { // тест удаление из пустого стека
    Stack stack;

    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());  

    stack.pop();

    std::string output = buffer.str();
    EXPECT_NE(output.find("Стек пуст."), std::string::npos);

    std::cout.rdbuf(old);
}

TEST(stackTest, printEmptyStack) { // тест печать пустого стека
    Stack stack;

    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());  

    stack.printStack();

    std::string output = buffer.str();
    EXPECT_NE(output.find("Стек пуст."), std::string::npos);

    std::cout.rdbuf(old);
}