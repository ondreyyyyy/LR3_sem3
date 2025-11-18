#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <queue>
#include <map>
#include <fstream>
#include <dlfcn.h>  
#include <stdexcept>
#include "stack.hpp"
#include "queue.hpp"
#include "array.hpp"
#include "onelinkedlist.hpp"
#include "doubleFL.hpp"
#include "tree.hpp"
#include "hashchain.hpp"
#include "hashaddress.hpp"

using namespace std;

struct ArrayLibrary {
    void* handle = nullptr;
    DynArray* (*createArray)() = nullptr;
    void (*destroyArray)(DynArray*) = nullptr;
    void (*arrayPushBack)(DynArray*, const string&) = nullptr;
    void (*arrayAddAtIndex)(DynArray*, const int&, const string&) = nullptr;
    char* (*arrayGetElementIndex)(DynArray*, const int&) = nullptr;
    void (*arrayRemoveIndex)(DynArray*, const int&) = nullptr;
    void (*arrayReplacement)(DynArray*, const int&, const string&) = nullptr;
    int (*arrayGetSize)(DynArray*) = nullptr;
    void (*arrayPrint)(DynArray*) = nullptr;
    bool isLoaded = false;
};

struct ForwardListLibrary {
    void* handle = nullptr;
    forwardList* (*createFL)() = nullptr;
    void (*deleteFL)(forwardList*) = nullptr;
    void (*flAddAtHead)(forwardList*, const string&) = nullptr;
    void (*flAddAtTail)(forwardList*, const string&) = nullptr;
    void (*flSearchNode)(forwardList*, const string&) = nullptr;
    void (*flAddBeforeIndex)(forwardList*, const string&, const int&) = nullptr;
    void (*flAddAfterIndex)(forwardList*, const string&, const int&) = nullptr;
    void (*flDeleteAtHead)(forwardList*) = nullptr;
    void (*flDeleteAtTail)(forwardList*) = nullptr;
    void (*flDeleteBeforeIndex)(forwardList*, const int&) = nullptr;
    void (*flDeleteAfterIndex)(forwardList*, const int&) = nullptr;
    void (*flValueDelete)(forwardList*, const string&) = nullptr;
    void (*flPrint)(forwardList*) = nullptr;
    bool isLoaded = false;
};

struct DoubleListLibrary {
    void* handle = nullptr;
    doubleFL* (*dflCreate)() = nullptr;
    void (*deleteDFL)(doubleFL*) = nullptr;
    void (*dflAddAtHead)(doubleFL*, const string&) = nullptr;
    void (*dflAddAtTail)(doubleFL*, const string&) = nullptr;
    void (*dflSearchValue)(doubleFL*, const string&) = nullptr;
    void (*dflAddBeforeIndex)(doubleFL*, const string&, const int&) = nullptr;
    void (*dflAddAfterIndex)(doubleFL*, const string&, const int&) = nullptr;
    void (*dflDeleteAtHead)(doubleFL*) = nullptr;
    void (*dflDeleteAtTail)(doubleFL*) = nullptr;
    void (*dflDeleteBeforeIndex)(doubleFL*, const int&) = nullptr;
    void (*dflDeleteAfterIndex)(doubleFL*, const int&) = nullptr;
    void (*dflDeleteValue)(doubleFL*, const string&) = nullptr;
    void (*dflPrint)(doubleFL*) = nullptr;
    bool isLoaded = false;
};

struct StackLibrary {
    void* handle = nullptr;
    Stack* (*createStack)() = nullptr;
    void (*destroyStack)(Stack*) = nullptr;
    void (*pushStack)(Stack*, const string&) = nullptr;
    void (*popStack)(Stack*) = nullptr;
    void (*stackPrint)(Stack*) = nullptr;
    bool isLoaded = false;
};

struct QueueLibrary {
    void* handle = nullptr;
    Queue* (*createQueue)() = nullptr;
    void (*destroyQueue)(Queue*) = nullptr;
    void (*queueEnqueue)(Queue*, const string&) = nullptr;
    void (*queueDequeue)(Queue*) = nullptr;
    void (*queuePrint)(Queue*) = nullptr;
    bool isLoaded = false;
};

struct TreeLibrary {
    void* handle = nullptr;
    Tree* (*createTree)() = nullptr;
    void (*deleteTree)(Tree*) = nullptr;
    void (*treeInsert)(Tree*, const int&) = nullptr;
    void (*treeDeleteNode)(Tree*, TNode*) = nullptr;
    void (*treePrint)(Tree*) = nullptr;
    void (*treeFindNode)(Tree*, const int&) = nullptr;
    bool isLoaded = false;
};

struct HashChainLibrary {
    void* handle = nullptr;
    HashC* (*createHashC)() = nullptr;
    void (*deleteHashC)(HashC*) = nullptr;
    void (*hashcAddElement)(HashC*, const string&, const int&) = nullptr;
    void (*hashcDeleteElement)(HashC*, const string&) = nullptr;
    int (*hashcFindElement)(HashC*, const string&) = nullptr;
    void (*hashcPrint)(HashC*) = nullptr;
    bool isLoaded = false;
};

struct HashAddressLibrary {
    void* handle = nullptr;
    HashA* (*createHashA)() = nullptr;
    void (*deleteHashA)(HashA*) = nullptr;
    void (*hashAAddElement)(HashA*, const string&, const int&) = nullptr;
    void (*hashADeleteElement)(HashA*, const string&) = nullptr;
    int (*hashAFindElement)(HashA*, const string&) = nullptr;
    void (*hashAPrint)(HashA*) = nullptr;
    bool isLoaded = false;
};

ArrayLibrary arrayLib;
ForwardListLibrary forwardListLib;
DoubleListLibrary doubleListLib;
StackLibrary stackLib;
QueueLibrary queueLib;
TreeLibrary treeLib;
HashChainLibrary hashChainLib;
HashAddressLibrary hashAddressLib;

map<string, DynArray*> arrays;
map<string, forwardList*> forwardLists;
map<string, doubleFL*> doubleLists;
map<string, Stack*> stacks;
map<string, Queue*> queues;
map<string, Tree*> trees;
map<string, HashC*> hashChains;
map<string, HashA*> hashAddresses;

auto loadArrayLibrary() -> bool {
    arrayLib.handle = dlopen("./libarray.so", RTLD_LAZY);
    if (arrayLib.handle == nullptr) {
        cerr << "Предупреждение: библиотека массивов (libarray.so) не найдена. Работа с массивами будет недоступна.\n";
        return false;
    }

    arrayLib.createArray = (DynArray* (*)())dlsym(arrayLib.handle, "createArray");
    arrayLib.destroyArray = (void (*)(DynArray*))dlsym(arrayLib.handle, "destroyArray");
    arrayLib.arrayPushBack = (void (*)(DynArray*, const string&))dlsym(arrayLib.handle, "arrayPushBack");
    arrayLib.arrayAddAtIndex = (void (*)(DynArray*, const int&, const string&))dlsym(arrayLib.handle, "arrayAddAtIndex");
    arrayLib.arrayGetElementIndex = (char* (*)(DynArray*, const int&))dlsym(arrayLib.handle, "arrayGetElementIndex");
    arrayLib.arrayRemoveIndex = (void (*)(DynArray*, const int&))dlsym(arrayLib.handle, "arrayRemoveIndex");
    arrayLib.arrayReplacement = (void (*)(DynArray*, const int&, const string&))dlsym(arrayLib.handle, "arrayReplacement");
    arrayLib.arrayGetSize = (int (*)(DynArray*))dlsym(arrayLib.handle, "arrayGetSize");
    arrayLib.arrayPrint = (void (*)(DynArray*))dlsym(arrayLib.handle, "arrayPrint");

    if (arrayLib.createArray == nullptr || arrayLib.destroyArray == nullptr) {
        cerr << "Ошибка: не удалось загрузить основные функции библиотеки массивов\n";
        dlclose(arrayLib.handle);
        return false;
    }

    arrayLib.isLoaded = true;
    return true;
}

auto loadForwardListLibrary() -> bool {
    forwardListLib.handle = dlopen("./libforwardlist.so", RTLD_LAZY);
    if (forwardListLib.handle == nullptr) {
        cerr << "Предупреждение: библиотека односвязных списков (libforwardlist.so) не найдена. Работа с односвязными списками будет недоступна.\n";
        return false;
    }

    forwardListLib.createFL = (forwardList* (*)())dlsym(forwardListLib.handle, "createFL");
    forwardListLib.deleteFL = (void (*)(forwardList*))dlsym(forwardListLib.handle, "deleteFL");
    forwardListLib.flAddAtHead = (void (*)(forwardList*, const string&))dlsym(forwardListLib.handle, "flAddAtHead");
    forwardListLib.flAddAtTail = (void (*)(forwardList*, const string&))dlsym(forwardListLib.handle, "flAddAtTail");
    forwardListLib.flSearchNode = (void (*)(forwardList*, const string&))dlsym(forwardListLib.handle, "flSearchNode");
    forwardListLib.flAddBeforeIndex = (void (*)(forwardList*, const string&, const int&))dlsym(forwardListLib.handle, "flAddBeforeIndex");
    forwardListLib.flAddAfterIndex = (void (*)(forwardList*, const string&, const int&))dlsym(forwardListLib.handle, "flAddAfterIndex");
    forwardListLib.flDeleteAtHead = (void (*)(forwardList*))dlsym(forwardListLib.handle, "flDeleteAtHead");
    forwardListLib.flDeleteAtTail = (void (*)(forwardList*))dlsym(forwardListLib.handle, "flDeleteAtTail");
    forwardListLib.flDeleteBeforeIndex = (void (*)(forwardList*, const int&))dlsym(forwardListLib.handle, "flDeleteBeforeIndex");
    forwardListLib.flDeleteAfterIndex = (void (*)(forwardList*, const int&))dlsym(forwardListLib.handle, "flDeleteAfterIndex");
    forwardListLib.flValueDelete = (void (*)(forwardList*, const string&))dlsym(forwardListLib.handle, "flValueDelete");
    forwardListLib.flPrint = (void (*)(forwardList*))dlsym(forwardListLib.handle, "flPrint");

    if (forwardListLib.createFL == nullptr || forwardListLib.deleteFL == nullptr) {
        cerr << "Ошибка: не удалось загрузить основные функции библиотеки односвязных списков\n";
        dlclose(forwardListLib.handle);
        return false;
    }

    forwardListLib.isLoaded = true;
    return true;
}

auto loadDoubleListLibrary() -> bool {
    doubleListLib.handle = dlopen("./libdoublelist.so", RTLD_LAZY);
    if (doubleListLib.handle == nullptr) {
        cerr << "Предупреждение: библиотека двусвязных списков (libdoublelist.so) не найдена. Работа с двусвязными списками будет недоступна.\n";
        return false;
    }

    doubleListLib.dflCreate = (doubleFL* (*)())dlsym(doubleListLib.handle, "dflCreate");
    doubleListLib.deleteDFL = (void (*)(doubleFL*))dlsym(doubleListLib.handle, "deleteDFL");
    doubleListLib.dflAddAtHead = (void (*)(doubleFL*, const string&))dlsym(doubleListLib.handle, "dflAddAtHead");
    doubleListLib.dflAddAtTail = (void (*)(doubleFL*, const string&))dlsym(doubleListLib.handle, "dflAddAtTail");
    doubleListLib.dflSearchValue = (void (*)(doubleFL*, const string&))dlsym(doubleListLib.handle, "dflSearchValue");
    doubleListLib.dflAddBeforeIndex = (void (*)(doubleFL*, const string&, const int&))dlsym(doubleListLib.handle, "dflAddBeforeIndex");
    doubleListLib.dflAddAfterIndex = (void (*)(doubleFL*, const string&, const int&))dlsym(doubleListLib.handle, "dflAddAfterIndex");
    doubleListLib.dflDeleteAtHead = (void (*)(doubleFL*))dlsym(doubleListLib.handle, "dflDeleteAtHead");
    doubleListLib.dflDeleteAtTail = (void (*)(doubleFL*))dlsym(doubleListLib.handle, "dflDeleteAtTail");
    doubleListLib.dflDeleteBeforeIndex = (void (*)(doubleFL*, const int&))dlsym(doubleListLib.handle, "dflDeleteBeforeIndex");
    doubleListLib.dflDeleteAfterIndex = (void (*)(doubleFL*, const int&))dlsym(doubleListLib.handle, "dflDeleteAfterIndex");
    doubleListLib.dflDeleteValue = (void (*)(doubleFL*, const string&))dlsym(doubleListLib.handle, "dflDeleteValue");
    doubleListLib.dflPrint = (void (*)(doubleFL*))dlsym(doubleListLib.handle, "dflPrint");

    if (doubleListLib.dflCreate == nullptr || doubleListLib.deleteDFL == nullptr) {        
        cerr << "Ошибка: не удалось загрузить основные функции библиотеки двусвязных списков\n";
        dlclose(doubleListLib.handle);
        return false;
    }

    doubleListLib.isLoaded = true;
    return true;
}

auto loadStackLibrary() -> bool {
    stackLib.handle = dlopen("./libstack.so", RTLD_LAZY);
    if (stackLib.handle == nullptr) {
        cerr << "Предупреждение: библиотека стеков (libstack.so) не найдена. Работа со стеками будет недоступна.\n";
        return false;
    }

    stackLib.createStack = (Stack* (*)())dlsym(stackLib.handle, "createStack");
    stackLib.destroyStack = (void (*)(Stack*))dlsym(stackLib.handle, "destroyStack");
    stackLib.pushStack = (void (*)(Stack*, const string&))dlsym(stackLib.handle, "pushStack");
    stackLib.popStack = (void (*)(Stack*))dlsym(stackLib.handle, "popStack");
    stackLib.stackPrint = (void (*)(Stack*))dlsym(stackLib.handle, "stackPrint");

    if (stackLib.createStack == nullptr || stackLib.destroyStack == nullptr) {
        cerr << "Ошибка: не удалось загрузить основные функции библиотеки стеков\n";
        dlclose(stackLib.handle);
        return false;
    }

    stackLib.isLoaded = true;
    return true;
}

auto loadQueueLibrary() -> bool {
    queueLib.handle = dlopen("./libqueue.so", RTLD_LAZY);
    if (queueLib.handle == nullptr) {
        cerr << "Предупреждение: библиотека очередей (libqueue.so) не найдена. Работа с очередями будет недоступна.\n";
        return false;
    }

    queueLib.createQueue = (Queue* (*)())dlsym(queueLib.handle, "createQueue");
    queueLib.destroyQueue = (void (*)(Queue*))dlsym(queueLib.handle, "destroyQueue");
    queueLib.queueEnqueue = (void (*)(Queue*, const string&))dlsym(queueLib.handle, "queueEnqueue");
    queueLib.queueDequeue = (void (*)(Queue*))dlsym(queueLib.handle, "queueDequeue");
    queueLib.queuePrint = (void (*)(Queue*))dlsym(queueLib.handle, "queuePrint");

    if (queueLib.createQueue == nullptr || queueLib.destroyQueue == nullptr) {
        cerr << "Ошибка: не удалось загрузить основные функции библиотеки очередей\n";
        dlclose(queueLib.handle);
        return false;
    }

    queueLib.isLoaded = true;
    return true;
}

auto loadTreeLibrary() -> bool {
    treeLib.handle = dlopen("./libtree.so", RTLD_LAZY);
    if (treeLib.handle == nullptr) {
        cerr << "Предупреждение: библиотека деревьев (libtree.so) не найдена. Работа с деревьями будет недоступна.\n";
        return false;
    }

    treeLib.createTree = (Tree* (*)())dlsym(treeLib.handle, "createTree");
    treeLib.deleteTree = (void (*)(Tree*))dlsym(treeLib.handle, "deleteTree");
    treeLib.treeInsert = (void (*)(Tree*, const int&))dlsym(treeLib.handle, "treeInsert");
    treeLib.treeDeleteNode = (void (*)(Tree*, TNode*))dlsym(treeLib.handle, "treeDeleteNode");
    treeLib.treePrint = (void (*)(Tree*))dlsym(treeLib.handle, "treePrint");
    treeLib.treeFindNode = (void (*)(Tree*, const int&))dlsym(treeLib.handle, "treeFindNode");

    if (treeLib.createTree == nullptr || treeLib.deleteTree == nullptr) {
        cerr << "Ошибка: не удалось загрузить основные функции библиотеки деревьев\n";
        dlclose(treeLib.handle);
        return false;
    }

    treeLib.isLoaded = true;
    return true;
}

auto loadHashChainLibrary() -> bool {
    hashChainLib.handle = dlopen("./libhashchain.so", RTLD_LAZY);
    if (hashChainLib.handle == nullptr) {
        cerr << "Предупреждение: библиотека хэш-таблиц (цепочки) (libhashchain.so) не найдена. Работа с хэш-таблицами (цепочки) будет недоступна.\n";
        return false;
    }

    hashChainLib.createHashC = (HashC* (*)())dlsym(hashChainLib.handle, "createHashC");
    hashChainLib.deleteHashC = (void (*)(HashC*))dlsym(hashChainLib.handle, "deleteHashC");
    hashChainLib.hashcAddElement = (void (*)(HashC*, const string&, const int&))dlsym(hashChainLib.handle, "hashcAddElement");
    hashChainLib.hashcDeleteElement = (void (*)(HashC*, const string&))dlsym(hashChainLib.handle, "hashcDeleteElement");
    hashChainLib.hashcFindElement = (int (*)(HashC*, const string&))dlsym(hashChainLib.handle, "hashcFindElement");
    hashChainLib.hashcPrint = (void (*)(HashC*))dlsym(hashChainLib.handle, "hashcPrint");

    if (hashChainLib.createHashC == nullptr || hashChainLib.deleteHashC == nullptr) {
        cerr << "Ошибка: не удалось загрузить основные функции библиотеки хэш-таблиц (цепочки)\n";
        dlclose(hashChainLib.handle);
        return false;
    }

    hashChainLib.isLoaded = true;
    return true;
}

auto loadHashAddressLibrary() -> bool {
    hashAddressLib.handle = dlopen("./libhashaddress.so", RTLD_LAZY);
    if (hashAddressLib.handle == nullptr) {
        cerr << "Предупреждение: библиотека хэш-таблиц (открытая адресация) (libhashaddress.so) не найдена. Работа с хэш-таблицами (открытая адресация) будет недоступна.\n";
        return false;
    }

    hashAddressLib.createHashA = (HashA* (*)())dlsym(hashAddressLib.handle, "createHashA");
    hashAddressLib.deleteHashA = (void (*)(HashA*))dlsym(hashAddressLib.handle, "deleteHashA");
    hashAddressLib.hashAAddElement = (void (*)(HashA*, const string&, const int&))dlsym(hashAddressLib.handle, "hashAAddElement");
    hashAddressLib.hashADeleteElement = (void (*)(HashA*, const string&))dlsym(hashAddressLib.handle, "hashADeleteElement");
    hashAddressLib.hashAFindElement = (int (*)(HashA*, const string&))dlsym(hashAddressLib.handle, "hashAFindElement");
    hashAddressLib.hashAPrint = (void (*)(HashA*))dlsym(hashAddressLib.handle, "hashAPrint");

    if (hashAddressLib.createHashA == nullptr || hashAddressLib.deleteHashA == nullptr) {
        cerr << "Ошибка: не удалось загрузить основные функции библиотеки хэш-таблиц (открытая адресация)\n";
        dlclose(hashAddressLib.handle);
        return false;
    }

    hashAddressLib.isLoaded = true;
    return true;
}

void loadAllLibraries() {
    loadArrayLibrary();
    loadForwardListLibrary();
    loadDoubleListLibrary();
    loadStackLibrary();
    loadQueueLibrary();
    loadTreeLibrary();
    loadHashChainLibrary();
    loadHashAddressLibrary();
}

void unloadAllLibraries() {
    if (arrayLib.isLoaded && arrayLib.handle != nullptr) {
        dlclose(arrayLib.handle);
    }
    if (forwardListLib.isLoaded && forwardListLib.handle != nullptr) {
        dlclose(forwardListLib.handle);
    }
    if (doubleListLib.isLoaded && doubleListLib.handle != nullptr) {
        dlclose(doubleListLib.handle);
    }
    if (stackLib.isLoaded && stackLib.handle != nullptr) {
        dlclose(stackLib.handle);
    }
    if (queueLib.isLoaded && queueLib.handle != nullptr) {
        dlclose(queueLib.handle);
    }
    if (treeLib.isLoaded && treeLib.handle != nullptr) {
        dlclose(treeLib.handle);
    }
    if (hashChainLib.isLoaded && hashChainLib.handle != nullptr) {
        dlclose(hashChainLib.handle);
    }
    if (hashAddressLib.isLoaded && hashAddressLib.handle != nullptr) {
        dlclose(hashAddressLib.handle);
    }
}

void saveToFile(const string& filename);
void loadFromFile(const string& filename);
void processArrayCommand(const vector<string>& args);
void processForwardListCommand(const vector<string>& args);
void processDoubleListCommand(const vector<string>& args);
void processStackCommand(const vector<string>& args);
void processQueueCommand(const vector<string>& args);
void processTreeCommand(const vector<string>& args);
void processHashChainCommand(const vector<string>& args);
void processHashAddressCommand(const vector<string>& args);
void processPrintCommand(const vector<string>& args);
auto split(const string& str) -> vector<string>;
void printHelp();

auto processCommand(const string& command, const vector<string>& args) -> int {
    if (command == "MCREATE" || command == "MPUSH" || command == "MINSERT" || 
        command == "MDEL" || command == "MGET" || command == "MSET" || 
        command == "MSIZE") {
        processArrayCommand(args);
    }
    else if (command == "FCREATE" || command == "FPUSHHEAD" || command == "FPUSHTAIL" || 
             command == "FINSERTBEFORE" || command == "FINSERTAFTER" || 
             command == "FDELHEAD" || command == "FDELTAIL" ||
             command == "FDELBEFORE" || command == "FDELAFTER" ||
             command == "FDELVALUE" || command == "FSEARCH") {
        processForwardListCommand(args);
    }
    else if (command == "LCREATE" || command == "LPUSHHEAD" || command == "LPUSHTAIL" || 
             command == "LINSERTBEFORE" || command == "LINSERTAFTER" || 
             command == "LDELHEAD" || command == "LDELTAIL" ||
             command == "LDELBEFORE" || command == "LDELAFTER" ||
             command == "LDELVALUE" || command == "LSEARCH") {
        processDoubleListCommand(args);
    }
    else if (command == "SCREATE" || command == "SPUSH" || command == "SPOP") {
        processStackCommand(args);
    }
    else if (command == "QCREATE" || command == "QPUSH" || command == "QPOP") {
        processQueueCommand(args);
    }
    else if (command == "TCREATE" || command == "TINSERT" || command == "TDELETE" || command == "TSEARCH") {
        processTreeCommand(args);
    }
    else if (command == "HCCREATE" || command == "HCPUT" || command == "HCGET" || command == "HCDELETE") {
        processHashChainCommand(args);
    }
    else if (command == "HACREATE" || command == "HAPUT" || command == "HAGET" || command == "HADELETE") {
        processHashAddressCommand(args);
    }
    else if (command == "PRINT") {
        processPrintCommand(args);
    }
    else if (command == "HELP") {
        printHelp();
    }
    else {
        cerr << "Неизвестная команда: " << command << "\n";
        return 1;
    }
    return 0;
}

auto main(int argc, char* argv[]) -> int {
    if (argc < 2) {
        cerr << "Ошибка: неверное количество аргументов. Используйте --help для справки.\n";
        return 1;
    }
    
    loadAllLibraries();

    string filename;
    string query;
    
    for (int i = 1; i < argc; i++) {
        string arg = argv[i];
        if (arg == "--file" && i + 1 < argc) {
            filename = argv[++i];
        }
        else if (arg == "--query" && i + 1 < argc) {
            query = argv[++i];
        }
        else if (arg == "--help" || arg == "-h") {
            printHelp();
            return 0;
        }
        else {
            cerr << "Ошибка: неизвестный аргумент " << arg << "\n";
            return 1;
        }
    }
    
    if (filename.empty() || query.empty()) {
        cerr << "Ошибка: необходимо указать --file и --query\n";
        return 1;
    }
    
    loadFromFile(filename);
    
    vector<string> args = split(query);
    if (args.empty()) {
        cerr << "Ошибка: пустой запрос\n";
        return 1;
    }
    
    string command = args[0];
    
    if (int commandResult = processCommand(command, args); commandResult != 0) {
        return commandResult;
    }
    
    saveToFile(filename);
    
    for (auto& pair : arrays) {
        arrayLib.destroyArray(pair.second);
    }
    for (auto& pair : forwardLists) {
        forwardListLib.deleteFL(pair.second);
    }
    for (auto& pair : doubleLists) {
        doubleListLib.deleteDFL(pair.second);
    }
    for (auto& pair : stacks) {
        stackLib.destroyStack(pair.second);
    }
    for (auto& pair : queues) {
        queueLib.destroyQueue(pair.second);
    }
    for (auto& pair : trees) {
        treeLib.deleteTree(pair.second);
    }
    for (auto& pair : hashChains) {
        hashChainLib.deleteHashC(pair.second);
    }
    for (auto& pair : hashAddresses) {
        hashAddressLib.deleteHashA(pair.second);
    }
    
    return 0;
}

void processPrintCommand(const vector<string>& args) {
    if (args.size() != 2) {
        cerr << "Ошибка: неверное количество аргументов для PRINT. Ожидается: PRINT <name>\n";
        return;
    }
    
    const string& name = args[1];
    
    if (arrays.find(name) != arrays.end()) {
        if (!arrayLib.isLoaded) {
            cerr << "Ошибка: библиотека массивов не загружена. Невозможно вывести массив '" << name << "'\n";
            return;
        }
        cout << "Содержимое массива '" << name << "': ";
        arrayLib.arrayPrint(arrays[name]);
        return;
    }
    
    if (forwardLists.find(name) != forwardLists.end()) {
        if (!forwardListLib.isLoaded) {
            cerr << "Ошибка: библиотека односвязных списков не загружена. Невозможно вывести список '" << name << "'\n";
            return;
        }
        cout << "Содержимое односвязного списка '" << name << "': ";
        forwardListLib.flPrint(forwardLists[name]);
        return;
    }
    
    if (doubleLists.find(name) != doubleLists.end()) {
        if (!doubleListLib.isLoaded) {
            cerr << "Ошибка: библиотека двусвязных списков не загружена. Невозможно вывести список '" << name << "'\n";
            return;
        }
        cout << "Содержимое двусвязного списка '" << name << "': ";
        doubleListLib.dflPrint(doubleLists[name]);
        return;
    }
    
    if (stacks.find(name) != stacks.end()) {
        if (!stackLib.isLoaded) {
            cerr << "Ошибка: библиотека стеков не загружена. Невозможно вывести стек '" << name << "'\n";
            return;
        }
        cout << "Содержимое стека '" << name << "': ";
        stackLib.stackPrint(stacks[name]);
        return;
    }
    
    if (queues.find(name) != queues.end()) {
        if (!queueLib.isLoaded) {
            cerr << "Ошибка: библиотека очередей не загружена. Невозможно вывести очередь '" << name << "'\n";
            return;
        }
        cout << "Содержимое очереди '" << name << "': ";
        queueLib.queuePrint(queues[name]);
        return;
    }
    
    if (trees.find(name) != trees.end()) {
        if (!treeLib.isLoaded) {
            cerr << "Ошибка: библиотека деревьев не загружена. Невозможно вывести дерево '" << name << "'\n";
            return;
        }
        cout << "Содержимое дерева '" << name << "':\n"; 
        treeLib.treePrint(trees[name]); 
        return;
    }
    
    if (hashChains.find(name) != hashChains.end()) {
        if (!hashChainLib.isLoaded) {
            cerr << "Ошибка: библиотека хэш-таблиц (цепочки) не загружена. Невозможно вывести хэш-таблицу '" << name << "'\n";
            return;
        }
        cout << "Содержимое хэш-таблицы (цепочки) '" << name << "':\n";
        hashChainLib.hashcPrint(hashChains[name]);
        return;
    }
    
    if (hashAddresses.find(name) != hashAddresses.end()) {
        if (!hashAddressLib.isLoaded) {
            cerr << "Ошибка: библиотека хэш-таблиц (открытая адресация) не загружена. Невозможно вывести хэш-таблицу '" << name << "'\n";
            return;
        }
        cout << "Содержимое хэш-таблицы (открытая адресация) '" << name << "':\n";
        hashAddressLib.hashAPrint(hashAddresses[name]);
        return;
    }
    
    cerr << "Ошибка: структура данных с именем '" << name << "' не найдена\n";
}

void handleMCreate(const vector<string>& args, const string& name) {
    if (args.size() > 3) {
        cerr << "Ошибка: слишком много аргументов для MCREATE\n";
        return;
    }
    if (arrays.find(name) != arrays.end()) {
        cerr << "Ошибка: массив '" << name << "' уже существует\n";
        return;
    }
    arrays[name] = arrayLib.createArray();
    cout << "Создание массива '" << name << "' успешно\n";
}

void handleMPush(const vector<string>& args, const string& name) {
    if (args.size() != 3) {
        cerr << "Ошибка: неверное количество аргументов для MPUSH\n";
        return;
    }
    if (arrays.find(name) == arrays.end()) {
        cerr << "Ошибка: массив '" << name << "' не существует\n";
        return;
    }
    arrayLib.arrayPushBack(arrays[name], args[2]);
    cout << "Добавление элемента в массив '" << name << "' успешно\n";
}

void handleMInsert(const vector<string>& args, const string& name) {
    if (args.size() != 4) {
        cerr << "Ошибка: неверное количество аргументов для MINSERT\n";
        return;
    }
    if (arrays.find(name) == arrays.end()) {
        cerr << "Ошибка: массив '" << name << "' не существует\n";
        return;
    }
    int index = stoi(args[2]);
    if (index < 0 || index > arrayLib.arrayGetSize(arrays[name])) {
        cerr << "Ошибка: индекс вне диапазона\n";
        return;
    }
    arrayLib.arrayAddAtIndex(arrays[name], index, args[3]);
    cout << "Вставка элемента в массив '" << name << "' успешна\n";
}

void handleMDel(const vector<string>& args, const string& name) {
    if (args.size() != 3) {
        cerr << "Ошибка: неверное количество аргументов для MDEL\n";
        return;
    }
    if (arrays.find(name) == arrays.end()) {
        cerr << "Ошибка: массив '" << name << "' не существует\n";
        return;
    }
    int index = stoi(args[2]);
    if (index < 0 || index >= arrayLib.arrayGetSize(arrays[name])) {
        cerr << "Ошибка: индекс вне диапазона\n";
        return;
    }
    arrayLib.arrayRemoveIndex(arrays[name], index);
    cout << "Удаление элемента из массива '" << name << "' успешно\n";
}

void handleMGet(const vector<string>& args, const string& name) {
    if (args.size() != 3) {
        cerr << "Ошибка: неверное количество аргументов для MGET\n";
        return;
    }
    if (arrays.find(name) == arrays.end()) {
        cerr << "Ошибка: массив '" << name << "' не существует\n";
        return;
    }
    int index = stoi(args[2]);
    if (index < 0 || index >= arrayLib.arrayGetSize(arrays[name])) {
        cerr << "Ошибка: индекс вне диапазона\n";
        return;
    }
    string value = arrayLib.arrayGetElementIndex(arrays[name], index); 
    cout << "Элемент " << value << "\n";
}

void handleMSet(const vector<string>& args, const string& name) {
    if (args.size() != 4) {
        cerr << "Ошибка: неверное количество аргументов для MSET\n";
        return;
    }
    if (arrays.find(name) == arrays.end()) {
        cerr << "Ошибка: массив '" << name << "' не существует\n";
        return;
    }
    int index = stoi(args[2]);
    if (index < 0 || index >= arrayLib.arrayGetSize(arrays[name])) {
        cerr << "Ошибка: индекс вне диапазона\n";
        return;
    }
    arrayLib.arrayReplacement(arrays[name], index, args[3]);
    cout << "Замена элемента в массиве '" << name << "' успешна\n";
}

void handleMSize(const vector<string>& args, const string& name) {
    if (args.size() != 2) {
        cerr << "Ошибка: неверное количество аргументов для MSIZE\n";
        return;
    }
    if (arrays.find(name) == arrays.end()) {
        cerr << "Ошибка: массив '" << name << "' не существует\n";
        return;
    }
    int size = arrayLib.arrayGetSize(arrays[name]);
    cout << "Размер массива '" << name << "': " << size << "\n";
}

void processArrayCommand(const vector<string>& args) {
    if (!arrayLib.isLoaded) {
        cerr << "Ошибка: библиотека массивов не загружена. Команда недоступна.\n";
        return;
    }

    if (args.size() < 2) {
        cerr << "Ошибка: недостаточно аргументов\n";
        return;
    }

    const string& name = args[1];
    
    try {
        const string& command = args[0];
        
        if (command == "MCREATE") {
            handleMCreate(args, name);
        }
        else if (command == "MPUSH") {
            handleMPush(args, name);
        }
        else if (command == "MINSERT") {
            handleMInsert(args, name);
        }
        else if (command == "MDEL") {
            handleMDel(args, name);
        }
        else if (command == "MGET") {
            handleMGet(args, name);
        }
        else if (command == "MSET") {
            handleMSet(args, name);
        }
        else if (command == "MSIZE") {
            handleMSize(args, name);
        }
        else {
            cerr << "Неизвестная команда массива: " << command << "\n";
        }
    } catch (const exception& e) {
        cerr << "Ошибка: " << e.what() << "\n";
    }
}

void handleFCreate(const vector<string>& args, const string& name) {
    if (args.size() != 3) {
        cerr << "Ошибка: неверное количество аргументов для FCREATE\n";
        return;
    }
    if (forwardLists.find(name) != forwardLists.end()) {
        cerr << "Ошибка: список '" << name << "' уже существует\n";
        return;
    }
    forwardLists[name] = forwardListLib.createFL();
    forwardListLib.flAddAtHead(forwardLists[name], args[2]);
    cout << "Создание односвязного списка '" << name << "' успешно\n";
}

void handleFPushHead(const vector<string>& args, const string& name) {
    if (args.size() != 3) {
        cerr << "Ошибка: неверное количество аргументов для FPUSHHEAD\n";
        return;
    }
    if (forwardLists.find(name) == forwardLists.end()) {
        cerr << "Ошибка: список '" << name << "' не существует\n";
        return;
    }
    forwardListLib.flAddAtHead(forwardLists[name], args[2]);
    cout << "Добавление элемента в голову списка '" << name << "' успешно\n";
}

void handleFPushTail(const vector<string>& args, const string& name) {
    if (args.size() != 3) {
        cerr << "Ошибка: неверное количество аргументов для FPUSHTAIL\n";
        return;
    }
    if (forwardLists.find(name) == forwardLists.end()) {
        cerr << "Ошибка: список '" << name << "' не существует\n";
        return;
    }
    forwardListLib.flAddAtTail(forwardLists[name], args[2]);
    cout << "Добавление элемента в хвост списка '" << name << "' успешно\n";
}

void handleFInsertBefore(const vector<string>& args, const string& name) {
    if (args.size() != 4) {
        cerr << "Ошибка: неверное количество аргументов для FINSERTBEFORE\n";
        return;
    }
    if (forwardLists.find(name) == forwardLists.end()) {
        cerr << "Ошибка: список '" << name << "' не существует\n";
        return;
    }
    int index = stoi(args[2]);
    if (index < 0) {
        cerr << "Ошибка: индекс не может быть отрицательным\n";
        return;
    }
    forwardListLib.flAddBeforeIndex(forwardLists[name], args[3], index);
    cout << "Вставка элемента перед индексом " << index << " списка '" << name << "' успешна\n";
}

void handleFInsertAfter(const vector<string>& args, const string& name) {
    if (args.size() != 4) {
        cerr << "Ошибка: неверное количество аргументов для FINSERTAFTER\n";
        return;
    }
    if (forwardLists.find(name) == forwardLists.end()) {
        cerr << "Ошибка: список '" << name << "' не существует\n";
        return;
    }
    int index = stoi(args[2]);
    if (index < 0) {
        cerr << "Ошибка: индекс не может быть отрицательным\n";
        return;
    }
    forwardListLib.flAddAfterIndex(forwardLists[name], args[3], index);
    cout << "Вставка элемента после индекса " << index << " списка '" << name << "' успешна\n";
}

void handleFDelHead(const vector<string>& args, const string& name) {
    if (args.size() != 2) {
        cerr << "Ошибка: неверное количество аргументов для FDELHEAD\n";
        return;
    }
    if (forwardLists.find(name) == forwardLists.end()) {
        cerr << "Ошибка: список '" << name << "' не существует\n";
        return;
    }
    forwardListLib.flDeleteAtHead(forwardLists[name]);
    cout << "Удаление головы списка '" << name << "' успешно\n";
}

void handleFDelTail(const vector<string>& args, const string& name) {
    if (args.size() != 2) {
        cerr << "Ошибка: неверное количество аргументов для FDELTAIL\n";
        return;
    }
    if (forwardLists.find(name) == forwardLists.end()) {
        cerr << "Ошибка: список '" << name << "' не существует\n";
        return;
    }
    forwardListLib.flDeleteAtTail(forwardLists[name]);
    cout << "Удаление хвоста списка '" << name << "' успешно\n";
}

void handleFDelBefore(const vector<string>& args, const string& name) {
    if (args.size() != 3) {
        cerr << "Ошибка: неверное количество аргументов для FDELBEFORE\n";
        return;
    }
    if (forwardLists.find(name) == forwardLists.end()) {
        cerr << "Ошибка: список '" << name << "' не существует\n";
        return;
    }
    int index = stoi(args[2]);
    if (index < 0) {
        cerr << "Ошибка: индекс не может быть отрицательным\n";
        return;
    }
    forwardListLib.flDeleteBeforeIndex(forwardLists[name], index);
    cout << "Удаление элемента перед индексом " << index << " списка '" << name << "' успешно\n";
}

void handleFDelAfter(const vector<string>& args, const string& name) {
    if (args.size() != 3) {
        cerr << "Ошибка: неверное количество аргументов для FDELAFTER\n";
        return;
    }
    if (forwardLists.find(name) == forwardLists.end()) {
        cerr << "Ошибка: список '" << name << "' не существует\n";
        return;
    }
    int index = stoi(args[2]);
    if (index < 0) {
        cerr << "Ошибка: индекс не может быть отрицательным\n";
        return;
    }
    forwardListLib.flDeleteAfterIndex(forwardLists[name], index);
    cout << "Удаление элемента после индекса " << index << " списка '" << name << "' успешно\n";
}

void handleFDelValue(const vector<string>& args, const string& name) {
    if (args.size() != 3) {
        cerr << "Ошибка: неверное количество аргументов для FDELVALUE\n";
        return;
    }
    if (forwardLists.find(name) == forwardLists.end()) {
        cerr << "Ошибка: список '" << name << "' не существует\n";
        return;
    }
    forwardListLib.flValueDelete(forwardLists[name], args[2]);
    cout << "Удаление элемента по значению из списка '" << name << "' успешно\n";
}

void handleFSearch(const vector<string>& args, const string& name) {
    if (args.size() != 3) {
        cerr << "Ошибка: неверное количество аргументов для FSEARCH\n";
        return;
    }
    if (forwardLists.find(name) == forwardLists.end()) {
        cerr << "Ошибка: список '" << name << "' не существует\n";
        return;
    }
    forwardListLib.flSearchNode(forwardLists[name], args[2]);
}

void processForwardListCommand(const vector<string>& args) {
    if (!forwardListLib.isLoaded) {
        cerr << "Ошибка: библиотека односвязных списков не загружена. Команда недоступна.\n";
        return;
    }

    if (args.size() < 2) {
        cerr << "Ошибка: недостаточно аргументов для команды " << args[0] << "\n";
        return;
    }
    
    const string& name = args[1];
    const string& command = args[0];
    
    try {
        if (command == "FCREATE") {
            handleFCreate(args, name);
        }
        else if (command == "FPUSHHEAD") {
            handleFPushHead(args, name);
        }
        else if (command == "FPUSHTAIL") {
            handleFPushTail(args, name);
        }
        else if (command == "FINSERTBEFORE") {
            handleFInsertBefore(args, name);
        }
        else if (command == "FINSERTAFTER") {
            handleFInsertAfter(args, name);
        }
        else if (command == "FDELHEAD") {
            handleFDelHead(args, name);
        }
        else if (command == "FDELTAIL") {
            handleFDelTail(args, name);
        }
        else if (command == "FDELBEFORE") {
            handleFDelBefore(args, name);
        }
        else if (command == "FDELAFTER") {
            handleFDelAfter(args, name);
        }
        else if (command == "FDELVALUE") {
            handleFDelValue(args, name);
        }
        else if (command == "FSEARCH") {
            handleFSearch(args, name);
        }
        else {
            cerr << "Неизвестная команда односвязного списка: " << command << "\n";
        }
    } catch (const exception& e) {
        cerr << "Ошибка: " << e.what() << "\n";
    }
}

void handleLCreate(const vector<string>& args, const string& name) {
    if (args.size() != 3) {
        cerr << "Ошибка: неверное количество аргументов для LCREATE\n";
        return;
    }
    if (doubleLists.find(name) != doubleLists.end()) {
        cerr << "Ошибка: список '" << name << "' уже существует\n";
        return;
    }
    doubleLists[name] = doubleListLib.dflCreate();
    doubleListLib.dflAddAtHead(doubleLists[name], args[2]);
    cout << "Создание двусвязного списка '" << name << "' успешно\n";
}

void handleLPushHead(const vector<string>& args, const string& name) {
    if (args.size() != 3) {
        cerr << "Ошибка: неверное количество аргументов для LPUSHHEAD\n";
        return;
    }
    if (doubleLists.find(name) == doubleLists.end()) {
        cerr << "Ошибка: список '" << name << "' не существует\n";
        return;
    }
    doubleListLib.dflAddAtHead(doubleLists[name], args[2]);
    cout << "Добавление элемента в голову списка '" << name << "' успешно\n";
}

void handleLPushTail(const vector<string>& args, const string& name) {
    if (args.size() != 3) {
        cerr << "Ошибка: неверное количество аргументов для LPUSHTAIL\n";
        return;
    }
    if (doubleLists.find(name) == doubleLists.end()) {
        cerr << "Ошибка: список '" << name << "' не существует\n";
        return;
    }
    doubleListLib.dflAddAtTail(doubleLists[name], args[2]);
    cout << "Добавление элемента в хвост списка '" << name << "' успешно\n";
}

void handleLInsertBefore(const vector<string>& args, const string& name) {
    if (args.size() != 4) {
        cerr << "Ошибка: неверное количество аргументов для LINSERTBEFORE\n";
        return;
    }
    if (doubleLists.find(name) == doubleLists.end()) {
        cerr << "Ошибка: список '" << name << "' не существует\n";
        return;
    }
    int index = stoi(args[2]);
    if (index < 0) {
        cerr << "Ошибка: индекс не может быть отрицательным\n";
        return;
    }
    doubleListLib.dflAddBeforeIndex(doubleLists[name], args[3], index);
    cout << "Вставка элемента перед индексом " << index << " списка '" << name << "' успешна\n";
}

void handleLInsertAfter(const vector<string>& args, const string& name) {
    if (args.size() != 4) {
        cerr << "Ошибка: неверное количество аргументов для LINSERTAFTER\n";
        return;
    }
    if (doubleLists.find(name) == doubleLists.end()) {
        cerr << "Ошибка: список '" << name << "' не существует\n";
        return;
    }
    int index = stoi(args[2]);
    if (index < 0) {
        cerr << "Ошибка: индекс не может быть отрицательным\n";
        return;
    }
    doubleListLib.dflAddAfterIndex(doubleLists[name], args[3], index);
    cout << "Вставка элемента после индекса " << index << " списка '" << name << "' успешна\n";
}

void handleLDelHead(const vector<string>& args, const string& name) {
    if (args.size() != 2) {
        cerr << "Ошибка: неверное количество аргументов для LDELHEAD\n";
        return;
    }
    if (doubleLists.find(name) == doubleLists.end()) {
        cerr << "Ошибка: список '" << name << "' не существует\n";
        return;
    }
    doubleListLib.dflDeleteAtHead(doubleLists[name]);
    cout << "Удаление головы списка '" << name << "' успешно\n";
}

void handleLDelTail(const vector<string>& args, const string& name) {
    if (args.size() != 2) {
        cerr << "Ошибка: неверное количество аргументов для LDELTAIL\n";
        return;
    }
    if (doubleLists.find(name) == doubleLists.end()) {
        cerr << "Ошибка: список '" << name << "' не существует\n";
        return;
    }
    doubleListLib.dflDeleteAtTail(doubleLists[name]);
    cout << "Удаление хвоста списка '" << name << "' успешно\n";
}

void handleLDelBefore(const vector<string>& args, const string& name) {
    if (args.size() != 3) {
        cerr << "Ошибка: неверное количество аргументов для LDELBEFORE\n";
        return;
    }
    if (doubleLists.find(name) == doubleLists.end()) {
        cerr << "Ошибка: список '" << name << "' не существует\n";
        return;
    }
    int index = stoi(args[2]);
    if (index < 0) {
        cerr << "Ошибка: индекс не может быть отрицательным\n";
        return;
    }
    doubleListLib.dflDeleteBeforeIndex(doubleLists[name], index);
    cout << "Удаление элемента перед индексом " << index << " списка '" << name << "' успешно\n";
}

void handleLDelAfter(const vector<string>& args, const string& name) {
    if (args.size() != 3) {
        cerr << "Ошибка: неверное количество аргументов для LDELAFTER\n";
        return;
    }
    if (doubleLists.find(name) == doubleLists.end()) {
        cerr << "Ошибка: список '" << name << "' не существует\n";
        return;
    }
    int index = stoi(args[2]);
    if (index < 0) {
        cerr << "Ошибка: индекс не может быть отрицательным\n";
        return;
    }
    doubleListLib.dflDeleteAfterIndex(doubleLists[name], index);
    cout << "Удаление элемента после индекса " << index << " списка '" << name << "' успешно\n";
}

void handleLDelValue(const vector<string>& args, const string& name) {
    if (args.size() != 3) {
        cerr << "Ошибка: неверное количество аргументов для LDELVALUE\n";
        return;
    }
    if (doubleLists.find(name) == doubleLists.end()) {
        cerr << "Ошибка: список '" << name << "' не существует\n";
        return;
    }
    doubleListLib.dflDeleteValue(doubleLists[name], args[2]);
    cout << "Удаление элемента по значению из списка '" << name << "' успешно\n";
}

void handleLSearch(const vector<string>& args, const string& name) {
    if (args.size() != 3) {
        cerr << "Ошибка: неверное количество аргументов для LSEARCH\n";
        return;
    }
    if (doubleLists.find(name) == doubleLists.end()) {
        cerr << "Ошибка: список '" << name << "' не существует\n";
        return;
    }
    doubleListLib.dflSearchValue(doubleLists[name], args[2]);
}

void processDoubleListCommand(const vector<string>& args) {
    if (!doubleListLib.isLoaded) {
        cerr << "Ошибка: библиотека двусвязных списков не загружена. Команда недоступна.\n";
        return;
    }

    if (args.size() < 2) {
        cerr << "Ошибка: недостаточно аргументов для команды " << args[0] << "\n";
        return;
    }
    
    const string& name = args[1];
    const string& command = args[0];
    
    try {
        if (command == "LCREATE") {
            handleLCreate(args, name);
        }
        else if (command == "LPUSHHEAD") {
            handleLPushHead(args, name);
        }
        else if (command == "LPUSHTAIL") {
            handleLPushTail(args, name);
        }
        else if (command == "LINSERTBEFORE") {
            handleLInsertBefore(args, name);
        }
        else if (command == "LINSERTAFTER") {
            handleLInsertAfter(args, name);
        }
        else if (command == "LDELHEAD") {
            handleLDelHead(args, name);
        }
        else if (command == "LDELTAIL") {
            handleLDelTail(args, name);
        }
        else if (command == "LDELBEFORE") {
            handleLDelBefore(args, name);
        }
        else if (command == "LDELAFTER") {
            handleLDelAfter(args, name);
        }
        else if (command == "LDELVALUE") {
            handleLDelValue(args, name);
        }
        else if (command == "LSEARCH") {
            handleLSearch(args, name);
        }
        else {
            cerr << "Неизвестная команда двусвязного списка: " << command << "\n";
        }
    } catch (const exception& e) {
        cerr << "Ошибка: " << e.what() << "\n";
    }
}

void processStackCommand(const vector<string>& args) {
    if (!stackLib.isLoaded) {
        cerr << "Ошибка: библиотека стеков не загружена. Команда недоступна.\n";
        return;
    }

    const string& name = args[1];
    
    try {
        if (args[0] == "SCREATE") {
            if (args.size() != 2) {
                cerr << "Ошибка: неверное количество аргументов для SCREATE\n";
                return;
            }
            if (stacks.find(name) != stacks.end()) {
                cerr << "Ошибка: стек '" << name << "' уже существует\n";
                return;
            }
            stacks[name] = stackLib.createStack();
            cout << "Создание стека '" << name << "' успешно\n";
        }
        else if (args[0] == "SPUSH") {
            if (args.size() != 3) {
                cerr << "Ошибка: неверное количество аргументов для SPUSH\n";
                return;
            }
            if (stacks.find(name) == stacks.end()) {
                cerr << "Ошибка: стек '" << name << "' не существует\n";
                return;
            }
            stackLib.pushStack(stacks[name], args[2]);
            cout << "Добавление элемента в стек '" << name << "' успешно\n";
        }
        else if (args[0] == "SPOP") {
            if (args.size() != 2) {
                cerr << "Ошибка: неверное количество аргументов для SPOP\n";
                return;
            }
            if (stacks.find(name) == stacks.end()) {
                cerr << "Ошибка: стек '" << name << "' не существует\n";
                return;
            }
            stackLib.popStack(stacks[name]);
            cout << "Удаление элемента из стека '" << name << "' успешно\n";
        }
    } catch (const exception& e) {
        cerr << "Ошибка: " << e.what() << "\n";
    }
}

void processQueueCommand(const vector<string>& args) {
    if (!queueLib.isLoaded) {
        cerr << "Ошибка: библиотека очередей не загружена. Команда недоступна.\n";
        return;
    }

    const string& name = args[1];
    
    try {
        if (args[0] == "QCREATE") {
            if (args.size() != 2) {
                cerr << "Ошибка: неверное количество аргументов для QCREATE\n";
                return;
            }
            if (queues.find(name) != queues.end()) {
                cerr << "Ошибка: очередь '" << name << "' уже существует\n";
                return;
            }
            queues[name] = queueLib.createQueue();
            cout << "Создание очереди '" << name << "' успешно\n";
        }
        else if (args[0] == "QPUSH") {
            if (args.size() != 3) {
                cerr << "Ошибка: неверное количество аргументов для QPUSH\n";
                return;
            }
            if (queues.find(name) == queues.end()) {
                cerr << "Ошибка: очередь '" << name << "' не существует\n";
                return;
            }
            queueLib.queueEnqueue(queues[name], args[2]);
            cout << "Добавление элемента в очередь '" << name << "' успешно\n";
        }
        else if (args[0] == "QPOP") {
            if (args.size() != 2) {
                cerr << "Ошибка: неверное количество аргументов для QPOP\n";
                return;
            }
            if (queues.find(name) == queues.end()) {
                cerr << "Ошибка: очередь '" << name << "' не существует\n";
                return;
            }
            queueLib.queueDequeue(queues[name]);
            cout << "Удаление элемента из очереди '" << name << "' успешно\n";
        }
    } catch (const exception& e) {
        cerr << "Ошибка: " << e.what() << "\n";
    }
}

void processTreeCommand(const vector<string>& args) {
    if (!treeLib.isLoaded) {
        cerr << "Ошибка: библиотека деревьев не загружена. Команда недоступна.\n";
        return;
    }

    if (args.size() < 2) {
        cerr << "Ошибка: недостаточно аргументов для команды " << args[0] << "\n";
        return;
    }
    
    const string& name = args[1];
    
    try {
        if (args[0] == "TCREATE") {
            if (args.size() != 2) {
                cerr << "Ошибка: неверное количество аргументов для TCREATE\n";
                return;
            }
            if (trees.find(name) != trees.end()) {
                cerr << "Ошибка: дерево '" << name << "' уже существует\n";
                return;
            }
            trees[name] = treeLib.createTree();
            cout << "Создание красно-черного дерева '" << name << "' успешно\n";
        }
        else if (args[0] == "TINSERT") {
            if (args.size() != 3) {
                cerr << "Ошибка: неверное количество аргументов для TINSERT\n";
                return;
            }
            if (trees.find(name) == trees.end()) {
                cerr << "Ошибка: дерево '" << name << "' не существует\n";
                return;
            }
            int value = stoi(args[2]);
            treeLib.treeInsert(trees[name], value);
            cout << "Вставка элемента " << value << " в дерево '" << name << "' успешна\n";
        }
        else if (args[0] == "TDELETE") {
            if (args.size() != 3) {
                cerr << "Ошибка: неверное количество аргументов для TDELETE\n";
                return;
            }
            if (trees.find(name) == trees.end()) {
                cerr << "Ошибка: дерево '" << name << "' не существует\n";
                return;
            }
            int value = stoi(args[2]);
            TNode* nodeToDelete = trees[name]->findNode(value);
            if (nodeToDelete != nullptr) {
                treeLib.treeDeleteNode(trees[name], nodeToDelete);
                cout << "Удаление элемента " << value << " из дерева '" << name << "' успешно\n";
            }
        }
        else if (args[0] == "TSEARCH") {
            if (args.size() != 3) {
                cerr << "Ошибка: неверное количество аргументов для TSEARCH\n";
                return;
            }
            if (trees.find(name) == trees.end()) {
                cerr << "Ошибка: дерево '" << name << "' не существует\n";
                return;
            }
            int value = stoi(args[2]);
            treeLib.treeFindNode(trees[name], value);
        }
    } catch (const exception& e) {
        cerr << "Ошибка: " << e.what() << "\n";
    }
}

void handleHCCreate(const vector<string>& args, const string& name) {
    if (args.size() != 2) {
        cerr << "Ошибка: неверное количество аргументов для HCCREATE\n";
        return;
    }
    if (hashChains.find(name) != hashChains.end()) {
        cerr << "Ошибка: хэш-таблица (цепочки) '" << name << "' уже существует\n";
        return;
    }
    hashChains[name] = hashChainLib.createHashC();
    cout << "Создание хэш-таблицы (цепочки) '" << name << "' успешно\n";
}

void handleHCPut(const vector<string>& args, const string& name) {
    if (args.size() != 4) {
        cerr << "Ошибка: неверное количество аргументов для HCPUT\n";
        return;
    }
    if (hashChains.find(name) == hashChains.end()) {
        cerr << "Ошибка: хэш-таблица (цепочки) '" << name << "' не существует\n";
        return;
    }
    string key = args[2];
    int value = stoi(args[3]);
    hashChainLib.hashcAddElement(hashChains[name], key, value);
    cout << "Добавление элемента [" << key << " -> " << value << "] в хэш-таблицу '" << name << "' успешно\n";
}

void handleHCGet(const vector<string>& args, const string& name) {
    if (args.size() != 3) {
        cerr << "Ошибка: неверное количество аргументов для HCGET\n";
        return;
    }
    if (hashChains.find(name) == hashChains.end()) {
        cerr << "Ошибка: хэш-таблица (цепочки) '" << name << "' не существует\n";
        return;
    }
    string key = args[2];
    int value = hashChainLib.hashcFindElement(hashChains[name], key);
    if (value != -1) {
        cout << "Элемент [" << key << " -> " << value << "] найден в хэш-таблице '" << name << "'\n";
    } else {
        cout << "Элемент с ключом '" << key << "' не найден в хэш-таблице '" << name << "'\n";
    }
}

void handleHCDelete(const vector<string>& args, const string& name) {
    if (args.size() != 3) {
        cerr << "Ошибка: неверное количество аргументов для HCDELETE\n";
        return;
    }
    if (hashChains.find(name) == hashChains.end()) {
        cerr << "Ошибка: хэш-таблица (цепочки) '" << name << "' не существует\n";
        return;
    }
    string key = args[2];
    hashChainLib.hashcDeleteElement(hashChains[name], key);
    cout << "Удаление элемента с ключом '" << key << "' из хэш-таблицы '" << name << "' успешно\n";
}

void processHashChainCommand(const vector<string>& args) {
    if (!hashChainLib.isLoaded) {
        cerr << "Ошибка: библиотека хэш-таблиц (цепочки) не загружена. Команда недоступна.\n";
        return;
    }

    if (args.size() < 2) {
        cerr << "Ошибка: недостаточно аргументов для команды " << args[0] << "\n";
        return;
    }
    
    const string& name = args[1];
    const string& command = args[0];
    
    try {
        if (command == "HCCREATE") {
            handleHCCreate(args, name);
        }
        else if (command == "HCPUT") {
            handleHCPut(args, name);
        }
        else if (command == "HCGET") {
            handleHCGet(args, name);
        }
        else if (command == "HCDELETE") {
            handleHCDelete(args, name);
        }
        else {
            cerr << "Неизвестная команда хэш-таблицы (цепочки): " << command << "\n";
        }
    } catch (const exception& e) {
        cerr << "Ошибка: " << e.what() << "\n";
    }
}

void handleHACreate(const vector<string>& args, const string& name) {
    if (args.size() != 2) {
        cerr << "Ошибка: неверное количество аргументов для HACREATE\n";
        return;
    }
    if (hashAddresses.find(name) != hashAddresses.end()) {
        cerr << "Ошибка: хэш-таблица (открытая адресация) '" << name << "' уже существует\n";
        return;
    }
    hashAddresses[name] = hashAddressLib.createHashA();
    cout << "Создание хэш-таблицы (открытая адресация) '" << name << "' успешно\n";
}

void handleHAPut(const vector<string>& args, const string& name) {
    if (args.size() != 4) {
        cerr << "Ошибка: неверное количество аргументов для HAPUT\n";
        return;
    }
    if (hashAddresses.find(name) == hashAddresses.end()) {
        cerr << "Ошибка: хэш-таблица (открытая адресация) '" << name << "' не существует\n";
        return;
    }
    string key = args[2];
    int value = stoi(args[3]);
    hashAddressLib.hashAAddElement(hashAddresses[name], key, value);
    cout << "Добавление элемента [" << key << " -> " << value << "] в хэш-таблицу '" << name << "' успешно\n";
}

void handleHAGet(const vector<string>& args, const string& name) {
    if (args.size() != 3) {
        cerr << "Ошибка: неверное количество аргументов для HAGET\n";
        return;
    }
    if (hashAddresses.find(name) == hashAddresses.end()) {
        cerr << "Ошибка: хэш-таблица (открытая адресация) '" << name << "' не существует\n";
        return;
    }
    string key = args[2];
    int value = hashAddressLib.hashAFindElement(hashAddresses[name], key);
    if (value != -1) {
        cout << "Элемент [" << key << " -> " << value << "] найден в хэш-таблице '" << name << "'\n";
    } else {
        cout << "Элемент с ключом '" << key << "' не найден в хэш-таблице '" << name << "'\n";
    }
}

void handleHADelete(const vector<string>& args, const string& name) {
    if (args.size() != 3) {
        cerr << "Ошибка: неверное количество аргументов для HADELETE\n";
        return;
    }
    if (hashAddresses.find(name) == hashAddresses.end()) {
        cerr << "Ошибка: хэш-таблица (открытая адресация) '" << name << "' не существует\n";
        return;
    }
    string key = args[2];
    hashAddressLib.hashADeleteElement(hashAddresses[name], key);
    cout << "Удаление элемента с ключом '" << key << "' из хэш-таблицы '" << name << "' успешно\n";
}

void processHashAddressCommand(const vector<string>& args) {
    if (!hashAddressLib.isLoaded) {
        cerr << "Ошибка: библиотека хэш-таблиц (открытая адресация) не загружена. Команда недоступна.\n";
        return;
    }

    if (args.size() < 2) {
        cerr << "Ошибка: недостаточно аргументов для команды " << args[0] << "\n";
        return;
    }
    
    const string& name = args[1];
    const string& command = args[0];
    
    try {
        if (command == "HACREATE") {
            handleHACreate(args, name);
        }
        else if (command == "HAPUT") {
            handleHAPut(args, name);
        }
        else if (command == "HAGET") {
            handleHAGet(args, name);
        }
        else if (command == "HADELETE") {
            handleHADelete(args, name);
        }
        else {
            cerr << "Неизвестная команда хэш-таблицы (открытая адресация): " << command << "\n";
        }
    } catch (const exception& e) {
        cerr << "Ошибка: " << e.what() << "\n";
    }
}

void saveArrayToFile(ofstream& file) {
    for (const auto& pair : arrays) {
        file << "ARRAY " << pair.first << " ";
        for (int i = 0; i < pair.second->getSize(); i++) {
            string value = arrayLib.arrayGetElementIndex(pair.second, i);
            file << value;
            if (i < pair.second->getSize() - 1) {
                file << " ";
            }
        }
        file << "\n";
    }
}

void saveForwardListToFile(ofstream& file) {
    for (const auto& pair : forwardLists) {
        file << "FORWARDLIST " << pair.first << " ";
        FNode* current = pair.second->getHead();
        while (current != nullptr) {
            file << current->getValue();
            if (current->getNext() != nullptr) {
                file << " ";
            }
            current = current->getNext();
        }
        file << "\n";
    }
}

void saveDoubleListToFile(ofstream& file) {
    for (const auto& pair : doubleLists) {
        file << "DOUBLELIST " << pair.first << " ";
        DNode* current = pair.second->getHead();
        while (current != nullptr) {
            file << current->getValue();
            if (current->getNext() != nullptr) {
                file << " ";
            }
            current = current->getNext();
        }
        file << "\n";
    }
}

void saveStackToFile(ofstream& file) {
    for (const auto& pair : stacks) {
        file << "STACK " << pair.first << " ";
        SNode* current = pair.second->getHead();
        while (current != nullptr) {
            file << current->getValue();
            if (current->getNext() != nullptr) {
                file << " ";
            }
            current = current->getNext();
        }
        file << "\n";
    }
}

void saveQueueToFile(ofstream& file) {
    for (const auto& pair : queues) {
        file << "QUEUE " << pair.first << " ";
        QNode* current = pair.second->getHead();
        while (current != nullptr) {
            file << current->getValue();
            if (current->getNext() != nullptr) {
                file << " ";
            }
            current = current->getNext();
        }
        file << "\n";
    }
}

void saveTreeToFile(ofstream& file) {
    for (const auto& pair : trees) {
        file << "TREE " << pair.first << " ";
        if (pair.second->getRoot() != pair.second->getNil()) {
            queue<TNode*> que;
            que.push(pair.second->getRoot());
            while (!que.empty()) {
                TNode* current = que.front();
                que.pop();
                if (current != pair.second->getNil()) {
                    file << current->getKey() << " ";
                    if (current->getLeft() != pair.second->getNil()) {
                        que.push(current->getLeft());
                    }
                    if (current->getRight() != pair.second->getNil()) {
                        que.push(current->getRight());
                    }
                }
            }
        }
        file << "\n";
    }
}

void saveHashChainToFile(ofstream& file) {
    for (const auto& pair : hashChains) {
        file << "HASHCHAIN " << pair.first << " ";
        bool firstElement = true;
        for (int i = 0; i < pair.second->getCapacity(); i++) {
            HNode* current = pair.second->getTable()[i];
            while (current != nullptr) {
                if (!firstElement) {
                    file << " ";
                }
                file << current->getKey() << ":" << current->getData();
                firstElement = false;
                current = current->getNext();
            }
        }
        file << "\n";
    }
}

void saveHashAddressToFile(ofstream& file) {
    for (const auto& pair : hashAddresses) {
        file << "HASHADDRESS " << pair.first << " ";
        bool firstElement = true;
        for (int i = 0; i < pair.second->getCapacity(); i++) {
            if (!pair.second->getTable()[i].getIsEmpty() && !pair.second->getTable()[i].getIsDeleted()) {
                if (!firstElement) {
                    file << " ";
                }
                file << pair.second->getTable()[i].getKey() << ":" << pair.second->getTable()[i].getData();
                firstElement = false;
            }
        }
        file << "\n";
    }
}

void saveToFile(const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Ошибка: не удалось открыть файл для записи\n";
        return;
    }

    if (arrayLib.isLoaded) {
        saveArrayToFile(file);
    } else {
        cerr << "Предупреждение: библиотека массивов недоступна, массивы не сохранены\n";
    }

    if (forwardListLib.isLoaded) {
        saveForwardListToFile(file);
    } else {
        cerr << "Предупреждение: библиотека односвязных списков недоступна, списки не сохранены\n";
    }

    if (doubleListLib.isLoaded) {
        saveDoubleListToFile(file);
    } else {
        cerr << "Предупреждение: библиотека двусвязных списков недоступна, списки не сохранены\n";
    }

    if (stackLib.isLoaded) {
        saveStackToFile(file);
    } else {
        cerr << "Предупреждение: библиотека стеков недоступна, стеки не сохранены\n";
    }

    if (queueLib.isLoaded) {
        saveQueueToFile(file);
    } else {
        cerr << "Предупреждение: библиотека очередей недоступна, очереди не сохранены\n";
    }

    if (treeLib.isLoaded) {
        saveTreeToFile(file);
    } else {
        cerr << "Предупреждение: библиотека деревьев недоступна, деревья не сохранены\n";
    }

    if (hashChainLib.isLoaded) {
        saveHashChainToFile(file);
    } else {
        cerr << "Предупреждение: библиотека хэш-таблиц (цепочки) недоступна, таблицы не сохранены\n";
    }

    if (hashAddressLib.isLoaded) {
        saveHashAddressToFile(file);
    } else {
        cerr << "Предупреждение: библиотека хэш-таблиц (открытая адресация) недоступна, таблицы не сохранены\n";
    }
    
    file.close();
    cout << "Данные сохранены в файл: " << filename << "\n";
}

auto loadArrayFromStream(stringstream& sstr, const string& name) -> bool {
    if (!arrayLib.isLoaded) {
        cerr << "Ошибка загрузки: библиотека массивов недоступна, массив '" << name << "' не загружен\n";
        return false;
    }
    arrays[name] = arrayLib.createArray();
    string value;
    while (sstr >> value) {
        arrayLib.arrayPushBack(arrays[name], value);
    }
    cout << "Загружен массив: " << name << " (элементов: " << arrayLib.arrayGetSize(arrays[name]) << ")\n";
    return true;
}

auto loadForwardListFromStream(stringstream& sstr, const string& name) -> bool {
    if (!forwardListLib.isLoaded) {
        cerr << "Ошибка загрузки: библиотека односвязных списков недоступна, список '" << name << "' не загружен\n";
        return false;
    }
    forwardLists[name] = forwardListLib.createFL();
    string value;
    bool first = true;
    while (sstr >> value) {
        if (first) {
            forwardListLib.flAddAtHead(forwardLists[name], value);
            first = false;
        } else {
            forwardListLib.flAddAtTail(forwardLists[name], value);
        }
    }
    cout << "Загружен односвязный список: " << name << "\n";
    return true;
}

auto loadDoubleListFromStream(stringstream& sstr, const string& name) -> bool {
    if (!doubleListLib.isLoaded) {
        cerr << "Ошибка загрузки: библиотека двусвязных списков недоступна, список '" << name << "' не загружен\n";
        return false;
    }
    doubleLists[name] = doubleListLib.dflCreate();
    string value;
    bool first = true;
    while (sstr >> value) {
        if (first) {
            doubleListLib.dflAddAtHead(doubleLists[name], value);
            first = false;
        } else {
            doubleListLib.dflAddAtTail(doubleLists[name], value);
        }
    }
    cout << "Загружен двусвязный список: " << name << "\n";
    return true;
}

auto loadStackFromStream(stringstream& sstr, const string& name) -> bool {
    if (!stackLib.isLoaded) {
        cerr << "Ошибка загрузки: библиотека стеков недоступна, стек '" << name << "' не загружен\n";
        return false;
    }
    stacks[name] = stackLib.createStack();
    string value;
    vector<string> values;
    while (sstr >> value) {
        values.push_back(value);
    }
    for (auto it = values.rbegin(); it != values.rend(); ++it) {
        stackLib.pushStack(stacks[name], *it);
    }
    cout << "Загружен стек: " << name << "\n";
    return true;
}

auto loadQueueFromStream(stringstream& sstr, const string& name) -> bool {
    if (!queueLib.isLoaded) {
        cerr << "Ошибка загрузки: библиотека очередей недоступна, очередь '" << name << "' не загружен\n";
        return false;
    }
    queues[name] = queueLib.createQueue();
    string value;
    while (sstr >> value) {
        queueLib.queueEnqueue(queues[name], value);
    }
    cout << "Загружена очередь: " << name << "\n";
    return true;
}

auto loadTreeFromStream(stringstream& sstr, const string& name) -> bool {
    if (!treeLib.isLoaded) {
        cerr << "Ошибка загрузки: библиотека деревьев недоступна, дерево '" << name << "' не загружено\n";
        return false;
    }
    
    trees[name] = treeLib.createTree();
    int value;
    while (sstr >> value) {
        treeLib.treeInsert(trees[name], value);
    }
    
    cout << "Загружено красно-черное дерево: " << name << "\n";
    return true;
}

auto loadHashChainFromStream(stringstream& sstr, const string& name) -> bool {
    if (!hashChainLib.isLoaded) {
        cerr << "Ошибка загрузки: библиотека хэш-таблиц (цепочки) недоступна, таблица '" << name << "' не загружена\n";
        return false;
    }
    hashChains[name] = hashChainLib.createHashC();
    string pair;
    while (sstr >> pair) {
        size_t colonPos = pair.find(':');
        if (colonPos != string::npos) {
            string key = pair.substr(0, colonPos);
            int data = stoi(pair.substr(colonPos + 1));
            hashChainLib.hashcAddElement(hashChains[name], key, data);
        }
    }
    cout << "Загружена хэш-таблица (цепочки): " << name << "\n";
    return true;
}

auto loadHashAddressFromStream(stringstream& sstr, const string& name) -> bool {
    if (!hashAddressLib.isLoaded) {
        cerr << "Ошибка загрузки: библиотека хэш-таблиц (открытая адресация) недоступна, таблица '" << name << "' не загружена\n";
        return false;
    }
    hashAddresses[name] = hashAddressLib.createHashA();
    string pair;
    while (sstr >> pair) {
        size_t colonPos = pair.find(':');
        if (colonPos != string::npos) {
            string key = pair.substr(0, colonPos);
            int data = stoi(pair.substr(colonPos + 1));
            hashAddressLib.hashAAddElement(hashAddresses[name], key, data);
        }
    }
    cout << "Загружена хэш-таблица (открытая адресация): " << name << "\n";
    return true;
}

void loadFromFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Файл " << filename << " не существует или не может быть открыт. Будет создан новый файл.\n";
        return;
    }
    
    string line;
    int loadedCount = 0;
    
    while (getline(file, line)) {
        if (line.empty()) {
            continue;
        }
        
        stringstream sstr(line);
        string type;
        string name;
        sstr >> type >> name;
        
        try {
            bool success = false;
            
            if (type == "ARRAY") {
                success = loadArrayFromStream(sstr, name);
            }
            else if (type == "FORWARDLIST") {
                success = loadForwardListFromStream(sstr, name);
            }
            else if (type == "DOUBLELIST") {
                success = loadDoubleListFromStream(sstr, name);
            }
            else if (type == "STACK") {
                success = loadStackFromStream(sstr, name);
            }
            else if (type == "QUEUE") {
                success = loadQueueFromStream(sstr, name);
            }
            else if (type == "TREE") {
                success = loadTreeFromStream(sstr, name);
            }
            else if (type == "HASHCHAIN") {
                success = loadHashChainFromStream(sstr, name);
            }
            else if (type == "HASHADDRESS") {
                success = loadHashAddressFromStream(sstr, name);
            }
            else {
                cerr << "Неизвестный тип данных: " << type << "\n";
                continue;
            }
            
            if (success) {
                loadedCount++;
            }
            
        } catch (const exception& e) {
            cerr << "Ошибка при загрузке " << type << " '" << name << "': " << e.what() << "\n";
        }
    }
    
    file.close();
    cout << "Загрузка завершена. Успешно загружено структур: " << loadedCount << "\n";
}

auto split(const string& str) -> vector<string> {
    vector<string> result;
    istringstream iss(str);
    string token;
    while (iss >> token) {
        result.push_back(token);
    }
    return result;
}

void printHelp() {
    cout << "Использование: program --file <filename> --query \"<command>\"\n\n";
    
    cout << "Доступные команды (зависит от загруженных библиотек):\n";
    
    if (arrayLib.isLoaded) {
        cout << "Команды для массивов:\n";
        cout << "  MCREATE <name> - создать массив\n";
        cout << "  MPUSH <name> <value> - добавить элемент в конец\n";
        cout << "  MINSERT <name> <index> <value> - вставить элемент по индексу\n";
        cout << "  MDEL <name> <index> - удалить элемент по индексу\n";
        cout << "  MGET <name> <index> - получить элемент по индексу\n";
        cout << "  MSET <name> <index> <value> - заменить элемент по индексу\n";
        cout << "  MSIZE <name> - получить размер массива\n";
    }
    
    if (forwardListLib.isLoaded) {
        cout << "Команды для односвязных списков:\n";
        cout << "  FCREATE <name> <value> - создать список с первым элементом\n";
        cout << "  FPUSHHEAD <name> <value> - добавить элемент в голову\n";
        cout << "  FPUSHTAIL <name> <value> - добавить элемент в хвост\n";
        cout << "  FINSERTBEFORE <name> <index> <value> - вставить перед индексом\n";
        cout << "  FINSERTAFTER <name> <index> <value> - вставить после индекса\n";
        cout << "  FDELHEAD <name> - удалить голову\n";
        cout << "  FDELTAIL <name> - удалить хвост\n";
        cout << "  FDELBEFORE <name> <index> - удалить перед индексом\n";
        cout << "  FDELAFTER <name> <index> - удалить после индекса\n";
        cout << "  FDELVALUE <name> <value> - удалить по значению\n";
        cout << "  FSEARCH <name> <value> - найти по значению\n";
    }
    
    if (doubleListLib.isLoaded) {
        cout << "Команды для двусвязных списков:\n";
        cout << "  LCREATE <name> <value> - создать список с первым элементом\n";
        cout << "  LPUSHHEAD <name> <value> - добавить элемент в голову\n";
        cout << "  LPUSHTAIL <name> <value> - добавить элемент в хвост\n";
        cout << "  LINSERTBEFORE <name> <index> <value> - вставить перед индексом\n";
        cout << "  LINSERTAFTER <name> <index> <value> - вставить после индекса\n";
        cout << "  LDELHEAD <name> - удалить голову\n";
        cout << "  LDELTAIL <name> - удалить хвост\n";
        cout << "  LDELBEFORE <name> <index> - удалить перед индексом\n";
        cout << "  LDELAFTER <name> <index> - удалить после индекса\n";
        cout << "  LDELVALUE <name> <value> - удалить по значению\n";
        cout << "  LSEARCH <name> <value> - найти по значению\n";
    }
    
    if (stackLib.isLoaded) {
        cout << "Команды для стеков:\n";
        cout << "  SCREATE <name> - создать стек\n";
        cout << "  SPUSH <name> <value> - добавить элемент\n";
        cout << "  SPOP <name> - удалить элемент\n";
    }
    
    if (queueLib.isLoaded) {
        cout << "Команды для очередей:\n";
        cout << "  QCREATE <name> - создать очередь\n";
        cout << "  QPUSH <name> <value> - добавить элемент\n";
        cout << "  QPOP <name> - удалить элемент\n";
    }
    
    if (treeLib.isLoaded) {
        cout << "Команды для красно-черных деревьев:\n"; 
        cout << "  TCREATE <name> - создать дерево\n";
        cout << "  TINSERT <name> <value> - вставить элемент\n";
        cout << "  TDELETE <name> <value> - удалить элемент\n";
        cout << "  TSEARCH <name> <value> - найти элемент\n";
    }
    
    if (hashChainLib.isLoaded) {
        cout << "Команды для хэш-таблиц (цепочки):\n";
        cout << "  HCCREATE <name> - создать хэш-таблицу\n";
        cout << "  HCPUT <name> <key> <value> - добавить элемент\n";
        cout << "  HCGET <name> <key> - получить элемент\n";
        cout << "  HCDELETE <name> <key> - удалить элемент\n";
    }
    
    if (hashAddressLib.isLoaded) {
        cout << "Команды для хэш-таблиц (открытая адресация):\n";
        cout << "  HACREATE <name> - создать хэш-таблицу\n";
        cout << "  HAPUT <name> <key> <value> - добавить элемент\n";
        cout << "  HAGET <name> <key> - получить элемент\n";
        cout << "  HADELETE <name> <key> - удалить элемент\n";
    }
    
    cout << "\nОбщие команды:\n";
    cout << "  PRINT <name> - вывести содержимое структуры данных\n";
    cout << "  HELP - показать эту справку\n";
    
    cout << "\nСтатус библиотек:\n";
    cout << "  Массивы: " << (arrayLib.isLoaded ? "доступно" : "недоступно") << "\n";
    cout << "  Односвязные списки: " << (forwardListLib.isLoaded ? "доступно" : "недоступно") << "\n";
    cout << "  Двусвязные списки: " << (doubleListLib.isLoaded ? "доступно" : "недоступно") << "\n";
    cout << "  Стеки: " << (stackLib.isLoaded ? "доступно" : "недоступно") << "\n";
    cout << "  Очереди: " << (queueLib.isLoaded ? "доступно" : "недоступно") << "\n";
    cout << "  Красно-черные деревья: " << (treeLib.isLoaded ? "доступно" : "недоступно") << "\n";
    cout << "  Хэш-таблицы (цепочки): " << (hashChainLib.isLoaded ? "доступно" : "недоступно") << "\n";
    cout << "  Хэш-таблицы (открытая адресация): " << (hashAddressLib.isLoaded ? "доступно" : "недоступно") << "\n";
}