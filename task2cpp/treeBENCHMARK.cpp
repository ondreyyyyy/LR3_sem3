#include <benchmark/benchmark.h>
#include "tree.hpp"
#include <random>
#include <vector>
#include <unordered_set>

std::vector<int> generateUniqueRandomNumbers(int count, int minVal = 1, int maxVal = 1000) {
    std::unordered_set<int> numbers;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(minVal, maxVal);
    
    while (numbers.size() < count) {
        numbers.insert(dist(gen));
    }
    return std::vector<int>(numbers.begin(), numbers.end());
}

static void BM_InsertSingleNode(benchmark::State& state) {
    for (auto _ : state) {
        Tree tree;
        tree.insert(42);
    }
}
BENCHMARK(BM_InsertSingleNode);

static void BM_InsertMultipleNodes(benchmark::State& state) {
    int numNodes = state.range(0);
    std::vector<int> keys = generateUniqueRandomNumbers(numNodes);
    
    for (auto _ : state) {
        Tree tree;
        for (int key : keys) {
            tree.insert(key);
        }
    }
}
BENCHMARK(BM_InsertMultipleNodes)->Arg(5)->Arg(10)->Arg(20);

static void BM_FindExistingNode(benchmark::State& state) {
    Tree tree;
    std::vector<int> keys = generateUniqueRandomNumbers(10);
    for (int key : keys) {
        tree.insert(key);
    }
    int targetKey = keys[5];
    
    for (auto _ : state) {
        auto node = tree.findNode(targetKey);
        benchmark::DoNotOptimize(node);
    }
}
BENCHMARK(BM_FindExistingNode);

static void BM_FindMissingNode(benchmark::State& state) {
    Tree tree;
    std::vector<int> keys = generateUniqueRandomNumbers(10);
    for (int key : keys) {
        tree.insert(key);
    }
    
    for (auto _ : state) {
        auto node = tree.findNode(9999);
        benchmark::DoNotOptimize(node);
    }
}
BENCHMARK(BM_FindMissingNode);

static void BM_DeleteNode(benchmark::State& state) {
    std::vector<int> keys = generateUniqueRandomNumbers(10);
    int keyToDelete = keys[5];
    
    for (auto _ : state) {
        state.PauseTiming();
        Tree tree;
        for (int key : keys) {
            tree.insert(key);
        }
        auto nodeToDelete = tree.findNode(keyToDelete);
        state.ResumeTiming();
        
        tree.deleteNode(nodeToDelete);
    }
}
BENCHMARK(BM_DeleteNode);

static void BM_FindMinimum(benchmark::State& state) {
    Tree tree;
    std::vector<int> keys = generateUniqueRandomNumbers(10);
    for (int key : keys) {
        tree.insert(key);
    }
    
    for (auto _ : state) {
        auto minNode = tree.findMinimum(tree.root);
        benchmark::DoNotOptimize(minNode);
    }
}
BENCHMARK(BM_FindMinimum);

static void BM_FindMaximum(benchmark::State& state) {
    Tree tree;
    std::vector<int> keys = generateUniqueRandomNumbers(10);
    for (int key : keys) {
        tree.insert(key);
    }
    
    for (auto _ : state) {
        auto maxNode = tree.findMaximum(tree.root);
        benchmark::DoNotOptimize(maxNode);
    }
}
BENCHMARK(BM_FindMaximum);

static void BM_MixedOperations(benchmark::State& state) {
    std::vector<int> initialKeys = generateUniqueRandomNumbers(5);
    std::vector<int> operationKeys = generateUniqueRandomNumbers(3, 100, 200);
    
    for (auto _ : state) {
        Tree tree;
        for (int key : initialKeys) {
            tree.insert(key);
        }
        
        for (int i = 0; i < 3; ++i) {
            tree.insert(operationKeys[i]);
            auto node = tree.findNode(initialKeys[i % initialKeys.size()]);
            benchmark::DoNotOptimize(node);
        }
    }
}
BENCHMARK(BM_MixedOperations);

static void BM_InsertSortedData(benchmark::State& state) {
    int numNodes = state.range(0);
    
    for (auto _ : state) {
        Tree tree;
        for (int i = 1; i <= numNodes; ++i) {
            tree.insert(i);
        }
    }
}
BENCHMARK(BM_InsertSortedData)->Arg(5)->Arg(10);

BENCHMARK_MAIN();