#include <benchmark/benchmark.h>
#include "stack.hpp"
#include <sstream>
#include <iostream>

// заглушка для вывода
class OutputDisabler {
    std::streambuf* original_cout;
    std::stringstream buffer;
public:
    OutputDisabler() : original_cout(std::cout.rdbuf()) {
        std::cout.rdbuf(buffer.rdbuf());  
    }
    
    ~OutputDisabler() {
        std::cout.rdbuf(original_cout); 
    }
};

// для pop из пустого стека 
static void BM_StackPopEmpty(benchmark::State& state) {
    Stack stack;
    OutputDisabler disabler;  
    
    for (auto _ : state) {
        stack.pop();  
        benchmark::ClobberMemory();
    }
}
BENCHMARK(BM_StackPopEmpty);

// для печати пустого стека 
static void BM_StackPrintEmpty(benchmark::State& state) {
    Stack stack;
    OutputDisabler disabler;  
    
    for (auto _ : state) {
        stack.printStack();  
        benchmark::ClobberMemory();
    }
}
BENCHMARK(BM_StackPrintEmpty);

// для множественных операций pop
static void BM_StackMultiplePop(benchmark::State& state) {
    Stack stack;
    OutputDisabler disabler;
    int iterations = state.range(0);
    
    for (auto _ : state) {
        for (int i = 0; i < iterations; ++i) {
            stack.pop();
        }
        benchmark::ClobberMemory();
    }
}
BENCHMARK(BM_StackMultiplePop)->Arg(1000)->Arg(10000);

// для push/pop операций
static void BM_StackPushPop(benchmark::State& state) {
    Stack stack;
    OutputDisabler disabler;
    
    for (auto _ : state) {
        stack.push("test");
        stack.pop();
        benchmark::ClobberMemory();
    }
}
BENCHMARK(BM_StackPushPop);

BENCHMARK_MAIN();