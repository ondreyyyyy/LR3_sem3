#include "array.hpp"
#include "doubleFL.hpp"
#include "hashaddress.hpp"
#include "hashchain.hpp"
#include "onelinkedlist.hpp"
#include "queue.hpp"
#include "stack.hpp"
#include "tree.hpp"
#include <iostream>
#include <string>

using namespace std;

void testArraySerialization() {
    cout << "=== Тестирование сериализации массива ===" << endl;
    DynArray arr;
    arr.pushBackArr("Привет");
    arr.pushBackArr("Мир");
    arr.pushBackArr("!");

    cout << "Массив до сохранения: ";
    arr.printArray();

    arr.MsaveToFile("array_data.txt", "test_array");
    arr.MsaveToFile("array_data.bin", "test_array");

    DynArray arr2;
    arr2.MloadFromFile("array_data.txt", "test_array");

    cout << "Массив после загрузки из текстового файла: ";
    arr2.printArray();

    DynArray arr3;
    arr3.MloadFromFile("array_data.bin", "test_array");

    cout << "Массив после загрузки из бинарного файла: ";
    arr3.printArray();
    cout << endl;
}

void testQueueSerialization() {
    cout << "=== Тестирование сериализации очереди ===" << endl;
    Queue queue;
    queue.enqueue("Яблоко");
    queue.enqueue("Банан");
    queue.enqueue("Вишня");

    cout << "Очередь до сохранения: ";
    queue.printQueue();

    queue.QsaveToFile("queue_data.txt", "test_queue");
    queue.QsaveToFile("queue_data.bin", "test_queue");

    Queue queue2;
    queue2.QloadFromFile("queue_data.txt", "test_queue");

    cout << "Очередь после загрузки из текстового файла: ";
    queue2.printQueue();

    Queue queue3;
    queue3.QloadFromFile("queue_data.bin", "test_queue");

    cout << "Очередь после загрузки из бинарного файла: ";
    queue3.printQueue();
    cout << endl;
}

void testTreeSerialization() {
    cout << "=== Тестирование сериализации дерева ===" << endl;
    Tree tree;
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.insert(40);
    tree.insert(50);

    cout << "Дерево до сохранения:" << endl;
    tree.printTree();

    tree.treeSaveToFile("tree_data.txt", "test_tree");
    tree.treeSaveToFile("tree_data.bin", "test_tree");

    Tree tree2;
    tree2.treeLoadFromFile("tree_data.txt", "test_tree");

    cout << "Дерево после загрузки из текстового файла:" << endl;
    tree2.printTree();

    Tree tree3;
    tree3.treeLoadFromFile("tree_data.bin", "test_tree");

    cout << "Дерево после загрузки из бинарного файла:" << endl;
    tree3.printTree();
    cout << endl;
}

void testHashAddressSerialization() {
    cout << "=== Тестирование сериализации хэш-таблицы (открытая адресация) ===" << endl;
    HashA hashTable;
    hashTable.addElementA("ключ1", 100);
    hashTable.addElementA("ключ2", 200);
    hashTable.addElementA("ключ3", 300);

    cout << "Хэш-таблица до сохранения:" << endl;
    hashTable.printHashTableA();

    hashTable.hashaSaveToFile("hash_address_data.txt", "test_hash_address");
    hashTable.hashaSaveToFile("hash_address_data.bin", "test_hash_address");

    HashA hashTable2;
    hashTable2.hashaLoadFromFile("hash_address_data.txt", "test_hash_address");

    cout << "Хэш-таблица после загрузки из текстового файла:" << endl;
    hashTable2.printHashTableA();

    HashA hashTable3;
    hashTable3.hashaLoadFromFile("hash_address_data.bin", "test_hash_address");

    cout << "Хэш-таблица после загрузки из бинарного файла:" << endl;
    hashTable3.printHashTableA();
    cout << endl;
}

void testHashChainSerialization() {
    cout << "=== Тестирование сериализации хэш-таблицы (цепочи) ===" << endl;
    HashC hashTable;
    hashTable.addElement("ключ1", 100);
    hashTable.addElement("ключ2", 200);
    hashTable.addElement("ключ3", 300);

    cout << "Хэш-таблица (цепочи) до сохранения:" << endl;
    hashTable.printHashTable();

    hashTable.hashcSaveToFile("hash_chain_data.txt", "test_hash_chain");
    hashTable.hashcSaveToFile("hash_chain_data.bin", "test_hash_chain");

    HashC hashTable2;
    hashTable2.hashcLoadFromFile("hash_chain_data.txt", "test_hash_chain");

    cout << "Хэш-таблица (цепочи) после загрузки из текстового файла:" << endl;
    hashTable2.printHashTable();

    HashC hashTable3;
    hashTable3.hashcLoadFromFile("hash_chain_data.bin", "test_hash_chain");

    cout << "Хэш-таблица (цепочи) после загрузки из бинарного файла:" << endl;
    hashTable3.printHashTable();
    cout << endl;
}

void testSinglyLinkedListSerialization() {
    cout << "=== Тестирование сериализации односвязного списка ===" << endl;
    forwardList sll;
    sll.addAtHead("первый");
    sll.addAtTail("второй");
    sll.addAtTail("третий");

    cout << "Односвязный список до сохранения: ";
    sll.printFL();

    sll.OLLsaveToFile("sll_data.txt", "test_sll");
    sll.OLLsaveToFile("sll_data.bin", "test_sll");

    forwardList sll2;
    sll2.OLLloadFromFile("sll_data.txt", "test_sll");

    cout << "Односвязный список после загрузки из текстового файла: ";
    sll2.printFL();

    forwardList sll3;
    sll3.OLLloadFromFile("sll_data.bin", "test_sll");

    cout << "Односвязный список после загрузки из бинарного файла: ";
    sll3.printFL();
    cout << endl;
}

void testDoublyLinkedListSerialization() {
    cout << "=== Тестирование сериализации двусвязного списка ===" << endl;
    doubleFL dll;
    dll.addAtHead("первый");
    dll.addAtTail("второй");
    dll.addAtTail("третий");

    cout << "Двусвязный список до сохранения: ";
    dll.printDoubleFL();

    dll.DFLsaveToFile("dll_data.txt", "test_dll");
    dll.DFLsaveToFile("dll_data.bin", "test_dll");

    doubleFL dll2;
    dll2.DFLloadFromFile("dll_data.txt", "test_dll");

    cout << "Двусвязный список после загрузки из текстового файла: ";
    dll2.printDoubleFL();

    doubleFL dll3;
    dll3.DFLloadFromFile("dll_data.bin", "test_dll");

    cout << "Двусвязный список после загрузки из бинарного файла: ";
    dll3.printDoubleFL();
    cout << endl;
}

void testStackSerialization() {
    cout << "=== Тестирование сериализации стека ===" << endl;
    Stack stack;
    stack.push("верх");
    stack.push("середина");
    stack.push("низ");

    cout << "Стек до сохранения: ";
    stack.printStack();

    stack.SsaveToFile("stack_data.txt", "test_stack");
    stack.SsaveToFile("stack_data.bin", "test_stack");

    Stack stack2;
    stack2.SloadFromFile("stack_data.txt", "test_stack");

    cout << "Стек после загрузки из текстового файла: ";
    stack2.printStack();

    Stack stack3;
    stack3.SloadFromFile("stack_data.bin", "test_stack");

    cout << "Стек после загрузки из бинарного файла: ";
    stack3.printStack();
    cout << endl;
}

int main() {
    cout << "НАЧАЛО ТЕСТИРОВАНИЯ СЕРИАЛИЗАЦИИ И ДЕСЕРИАЛИЗАЦИИ" << endl;
    cout << "=============================================" << endl << endl;

    testArraySerialization();
    testQueueSerialization();
    testTreeSerialization();
    testHashAddressSerialization();
    testHashChainSerialization();
    testSinglyLinkedListSerialization();
    testDoublyLinkedListSerialization();
    testStackSerialization();

    cout << "=============================================" << endl;
    cout << "ВСЕ ТЕСТЫ СЕРИАЛИЗАЦИИ УСПЕШНО ЗАВЕРШЕНЫ!" << endl;
    
    return 0;
}