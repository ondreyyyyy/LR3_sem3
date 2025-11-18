#include <gtest/gtest.h>
#include <sstream>
#include <fstream>
#include "queue.hpp"

TEST(queueTest, enqueue) { // добавление (в пустой и не пустой)
    Queue queue;
    queue.enqueue("item1");
    queue.enqueue("item2");
    queue.enqueue("item3");

    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    queue.printQueue();

    std::string output = buffer.str();
    EXPECT_NE(output.find("item1"), std::string::npos);
    EXPECT_NE(output.find("item2"), std::string::npos);
    EXPECT_NE(output.find("item3"), std::string::npos);

    std::cout.rdbuf(old);
}

TEST(queueTest, dequeue) {
    Queue queue;
    queue.enqueue("item1");
    queue.enqueue("item2");
    queue.enqueue("item3"); 

    queue.dequeue();

    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    queue.printQueue();

    std::string output = buffer.str();
    EXPECT_NE(output.find("item2"), std::string::npos);
    EXPECT_NE(output.find("item3"), std::string::npos);

    std::cout.rdbuf(old);
}

TEST(queueTest, dequeueSingle) {
    Queue queue;
    queue.enqueue("item1");

    queue.dequeue();

    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    queue.printQueue();

    std::string output = buffer.str();
    EXPECT_NE(output.find("Очередь пуста."), std::string::npos);

    std::cout.rdbuf(old);
}

TEST(queueTest, dequeueEmpty) {
    Queue queue;

    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    queue.dequeue();

    std::string output = buffer.str();
    EXPECT_NE(output.find("Очередь пустая. Нечего удалять."), std::string::npos);

    std::cout.rdbuf(old);
}

TEST(queueTest, GetHead) {
    Queue queue;
    EXPECT_EQ(queue.getHead(), nullptr);
}

TEST(queueTest, GetNextAndValue) {
    QNode* next = nullptr;
    QNode node("test", next);
    EXPECT_EQ(node.getNext(), nullptr);
    EXPECT_EQ(node.getValue(), "test");
}