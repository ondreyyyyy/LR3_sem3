#include <benchmark/benchmark.h>
#include "queue.hpp"
#include <sstream>
#include <iostream>

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

// для добавления в очередь
static void BM_QueueEnqueue(benchmark::State& state) {
    Queue queue;
    OutputDisabler disabler;
    int iterations = state.range(0);
    
    for (auto _ : state) {
        for (int i = 0; i < iterations; ++i) {
            queue.enqueue("item" + std::to_string(i));
        }
        benchmark::ClobberMemory();
    }
}
BENCHMARK(BM_QueueEnqueue)->Arg(100)->Arg(1000)->Arg(10000);

// для добавления в пустую очередь
static void BM_QueueEnqueueEmpty(benchmark::State& state) {
    Queue queue;
    OutputDisabler disabler;
    
    for (auto _ : state) {
        queue.enqueue("item");
        Queue temp;
        queue = temp;
        benchmark::ClobberMemory();
    }
}
BENCHMARK(BM_QueueEnqueueEmpty);

// для удаления из очереди 
static void BM_QueueDequeue(benchmark::State& state) {
    int iterations = state.range(0);
    
    for (auto _ : state) {
        state.PauseTiming(); 
        Queue queue;
        for (int i = 0; i < iterations; ++i) {
            queue.enqueue("item" + std::to_string(i));
        }
        state.ResumeTiming(); 
        
        OutputDisabler disabler;
        for (int i = 0; i < iterations; ++i) {
            queue.dequeue();
        }
        benchmark::ClobberMemory();
    }
}
BENCHMARK(BM_QueueDequeue)->Arg(100)->Arg(1000)->Arg(10000);

// для удаления из очереди с одним элементом 
static void BM_QueueDequeueSingle(benchmark::State& state) {
    Queue queue;
    OutputDisabler disabler;
    
    for (auto _ : state) {
        state.PauseTiming();
        queue.enqueue("item1"); 
        state.ResumeTiming();
        
        queue.dequeue();
        benchmark::ClobberMemory();
    }
}
BENCHMARK(BM_QueueDequeueSingle);

// для удаления из пустой очереди 
static void BM_QueueDequeueEmpty(benchmark::State& state) {
    Queue queue;
    OutputDisabler disabler;
    
    for (auto _ : state) {
        queue.dequeue();
        benchmark::ClobberMemory();
    }
}
BENCHMARK(BM_QueueDequeueEmpty);

// для операций enqueue/dequeue вперемешку
static void BM_QueueMixedOperations(benchmark::State& state) {
    Queue queue;
    OutputDisabler disabler;
    int iterations = state.range(0);
    
    for (auto _ : state) {
        for (int i = 0; i < iterations; ++i) {
            queue.enqueue("item" + std::to_string(i));
            if (i % 2 == 0) { 
                queue.dequeue();
            }
        }
        benchmark::ClobberMemory();
    }
}
BENCHMARK(BM_QueueMixedOperations)->Arg(100)->Arg(1000)->Arg(10000);

// для печати очереди
static void BM_QueuePrint(benchmark::State& state) {
    Queue queue;
    int iterations = state.range(0);

    for (int i = 0; i < iterations; ++i) {
        queue.enqueue("item" + std::to_string(i));
    }
    
    for (auto _ : state) {
        OutputDisabler disabler;
        queue.printQueue();
        benchmark::ClobberMemory();
    }
}
BENCHMARK(BM_QueuePrint)->Arg(10)->Arg(100)->Arg(1000);

BENCHMARK_MAIN();