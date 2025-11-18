#include <iostream>
#include "array.hpp"
#include "doubleFL.hpp"
#include "hashaddress.hpp"
#include "hashchain.hpp"
#include "onelinkedlist.hpp"
#include "queue.hpp"
#include "stack.hpp"
#include "tree.hpp"

using namespace std;

void testArraySerialization() {
    cout << "=== ТЕСТ МАССИВА ===\n";
    
    DynArray arr;
    arr.pushBackArr("array_element1");
    arr.pushBackArr("array_element2");
    arr.pushBackArr("array_element3");
    
    cout << "Исходный массив:\n";
    arr.printArray();
    
    arr.MsaveToFile("array.txt", "test_array");
    arr.MsaveToFile("array.bin", "test_array");
    
    DynArray arrLoaded;
    arrLoaded.MloadFromFile("array.txt", "test_array");
    cout << "Массив из текстового файла:\n";
    arrLoaded.printArray();
    
    DynArray arrLoadedBin;
    arrLoadedBin.MloadFromFile("array.bin", "test_array");
    cout << "Массив из бинарного файла:\n";
    arrLoadedBin.printArray();
    
    cout << "\n";
}

void testStackSerialization() {
    cout << "=== ТЕСТ СТЕКА ===\n";
    
    Stack stack;
    stack.push("stack_element1");
    stack.push("stack_element2");
    stack.push("stack_element3");
    
    cout << "Исходный стек:\n";
    stack.printStack();
    
    stack.SsaveToFile("stack.txt", "test_stack");
    stack.SsaveToFile("stack.bin", "test_stack");
    
    Stack stackLoaded;
    stackLoaded.SloadFromFile("stack.txt", "test_stack");
    cout << "Стек из текстового файла:\n";
    stackLoaded.printStack();
    
    Stack stackLoadedBin;
    stackLoadedBin.SloadFromFile("stack.bin", "test_stack");
    cout << "Стек из бинарного файла:\n";
    stackLoadedBin.printStack();
    
    cout << "\n";
}

void testQueueSerialization() {
    cout << "=== ТЕСТ ОЧЕРЕДИ ===\n";
    
    Queue queue;
    queue.enqueue("queue_element1");
    queue.enqueue("queue_element2");
    queue.enqueue("queue_element3");
    
    cout << "Исходная очередь:\n";
    queue.printQueue();
    
    queue.QsaveToFile("queue.txt", "test_queue");
    queue.QsaveToFile("queue.bin", "test_queue");
    
    Queue queueLoaded;
    queueLoaded.QloadFromFile("queue.txt", "test_queue");
    cout << "Очередь из текстового файла:\n";
    queueLoaded.printQueue();
    
    Queue queueLoadedBin;
    queueLoadedBin.QloadFromFile("queue.bin", "test_queue");
    cout << "Очередь из бинарного файла:\n";
    queueLoadedBin.printQueue();
    
    cout << "\n";
}

void testForwardListSerialization() {
    cout << "=== ТЕСТ ОДНОСВЯЗНОГО СПИСКА ===\n";
    
    forwardList list;
    list.addAtTail("forward_element1");
    list.addAtTail("forward_element2");
    list.addAtTail("forward_element3");
    
    cout << "Исходный односвязный список:\n";
    list.printFL();
    
    list.OLLsaveToFile("forward_list.txt", "test_forward_list");
    list.OLLsaveToFile("forward_list.bin", "test_forward_list");
    
    forwardList listLoaded;
    listLoaded.OLLloadFromFile("forward_list.txt", "test_forward_list");
    cout << "Односвязный список из текстового файла:\n";
    listLoaded.printFL();
    
    forwardList listLoadedBin;
    listLoadedBin.OLLloadFromFile("forward_list.bin", "test_forward_list");
    cout << "Односвязный список из бинарного файла:\n";
    listLoadedBin.printFL();
    
    cout << "\n";
}

void testDoubleListSerialization() {
    cout << "=== ТЕСТ ДВУСВЯЗНОГО СПИСКА ===\n";
    
    doubleFL dlist;
    dlist.addAtTail("double_element1");
    dlist.addAtTail("double_element2");
    dlist.addAtTail("double_element3");
    
    cout << "Исходный двусвязный список:\n";
    dlist.printDoubleFL();
    
    dlist.DFLsaveToFile("double_list.txt", "test_double_list");
    dlist.DFLsaveToFile("double_list.bin", "test_double_list");
    
    doubleFL dlistLoaded;
    dlistLoaded.DFLloadFromFile("double_list.txt", "test_double_list");
    cout << "Двусвязный список из текстового файла:\n";
    dlistLoaded.printDoubleFL();
    
    doubleFL dlistLoadedBin;
    dlistLoadedBin.DFLloadFromFile("double_list.bin", "test_double_list");
    cout << "Двусвязный список из бинарного файла:\n";
    dlistLoadedBin.printDoubleFL();
    
    cout << "\n";
}

void testHashChainSerialization() {
    cout << "=== ТЕСТ ХЭШ-ТАБЛИЦЫ (ЦЕПОЧКИ) ===\n";
    
    HashC hash;
    hash.addElement("key1", 100);
    hash.addElement("key2", 200);
    hash.addElement("key3", 300);
    
    cout << "Исходная хэш-таблица (цепочки):\n";
    hash.printHashTable();
    
    hash.hashcSaveToFile("hash_chain.txt", "test_hash_chain");
    hash.hashcSaveToFile("hash_chain.bin", "test_hash_chain");
    
    HashC hashLoaded;
    hashLoaded.hashcLoadFromFile("hash_chain.txt", "test_hash_chain");
    cout << "Хэш-таблица (цепочки) из текстового файла:\n";
    hashLoaded.printHashTable();
    
    HashC hashLoadedBin;
    hashLoadedBin.hashcLoadFromFile("hash_chain.bin", "test_hash_chain");
    cout << "Хэш-таблица (цепочки) из бинарного файла:\n";
    hashLoadedBin.printHashTable();
    
    cout << "\n";
}

void testHashAddressSerialization() {
    cout << "=== ТЕСТ ХЭШ-ТАБЛИЦЫ (ОТКРЫТАЯ АДРЕСАЦИЯ) ===\n";
    
    HashA hash;
    hash.addElementA("keyA1", 150);
    hash.addElementA("keyA2", 250);
    hash.addElementA("keyA3", 350);
    
    cout << "Исходная хэш-таблица (открытая адресация):\n";
    hash.printHashTableA();
    
    hash.hashaSaveToFile("hash_address.txt", "test_hash_address");
    hash.hashaSaveToFile("hash_address.bin", "test_hash_address");
    
    HashA hashLoaded;
    hashLoaded.hashaLoadFromFile("hash_address.txt", "test_hash_address");
    cout << "Хэш-таблица (открытая адресация) из текстового файла:\n";
    hashLoaded.printHashTableA();
    
    HashA hashLoadedBin;
    hashLoadedBin.hashaLoadFromFile("hash_address.bin", "test_hash_address");
    cout << "Хэш-таблица (открытая адресация) из бинарного файла:\n";
    hashLoadedBin.printHashTableA();
    
    cout << "\n";
}

void testTreeSerialization() {
    cout << "=== ТЕСТ КРАСНО-ЧЕРНОГО ДЕРЕВА ===\n";
    
    Tree tree;
    tree.insert(50);
    tree.insert(30);
    tree.insert(70);
    tree.insert(20);
    
    cout << "Исходное дерево:\n";
    tree.printTree();
    
    tree.treeSaveToFile("tree.txt", "test_tree");
    tree.treeSaveToFile("tree.bin", "test_tree");
    
    Tree treeLoaded;
    treeLoaded.treeLoadFromFile("tree.txt", "test_tree");
    cout << "Дерево из текстового файла:\n";
    treeLoaded.printTree();
    
    Tree treeLoadedBin;
    treeLoadedBin.treeLoadFromFile("tree.bin", "test_tree");
    cout << "Дерево из бинарного файла:\n";
    treeLoadedBin.printTree();
    
    cout << "\n";
}

void cleanupFiles() {
    remove("array.txt");
    remove("array.bin");
    remove("stack.txt");
    remove("stack.bin");
    remove("queue.txt");
    remove("queue.bin");
    remove("forward_list.txt");
    remove("forward_list.bin");
    remove("double_list.txt");
    remove("double_list.bin");
    remove("hash_chain.txt");
    remove("hash_chain.bin");
    remove("hash_address.txt");
    remove("hash_address.bin");
    remove("tree.txt");
    remove("tree.bin");
}

int main() {
    cout << "ТЕСТИРОВАНИЕ СЕРИАЛИЗАЦИИ И ДЕСЕРИАЛИЗАЦИИ\n";
    cout << "==========================================\n\n";
    
    cleanupFiles();
    
    testArraySerialization();
    testStackSerialization();
    testQueueSerialization();
    testForwardListSerialization();
    testDoubleListSerialization();
    testHashChainSerialization();
    testHashAddressSerialization();
    testTreeSerialization();
    
    cout << "==========================================\n";
    cout << "Все тесты завершены успешно!\n";
    cout << "Созданы файлы: array.txt/bin, stack.txt/bin, queue.txt/bin, etc.\n";
    
    return 0;
}