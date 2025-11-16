#include <benchmark/benchmark.h>
#include "onelinkedlist.hpp"
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

static void BM_AddAtHead(benchmark::State& state) {
    for (auto _ : state) {
        state.PauseTiming();
        forwardList list;
        for (int i = 0; i < state.range(0); i++) {
            list.addAtTail("element" + std::to_string(i));
        }
        state.ResumeTiming();
        
        list.addAtHead("newHead");
    }
}
BENCHMARK(BM_AddAtHead)->Arg(10)->Arg(20)->Arg(30);

static void BM_AddAtTail(benchmark::State& state) {
    for (auto _ : state) {
        state.PauseTiming();
        forwardList list;
        for (int i = 0; i < state.range(0); i++) {
            list.addAtTail("element" + std::to_string(i));
        }
        state.ResumeTiming();
        
        list.addAtTail("newTail");
    }
}
BENCHMARK(BM_AddAtTail)->Arg(10)->Arg(20)->Arg(30);

static void BM_SearchNodeHead(benchmark::State& state) {
    forwardList list;
    for (int i = 0; i < state.range(0); i++) {
        list.addAtTail("element" + std::to_string(i));
    }
    
    for (auto _ : state) {
        OutputDisabler disabler;
        list.searchNode("element0");
        benchmark::ClobberMemory();
    }
}
BENCHMARK(BM_SearchNodeHead)->Arg(10)->Arg(20)->Arg(30);

static void BM_SearchNodeMiddle(benchmark::State& state) {
    forwardList list;
    for (int i = 0; i < state.range(0); i++) {
        list.addAtTail("element" + std::to_string(i));
    }
    
    for (auto _ : state) {
        int middle = state.range(0) / 2;
        OutputDisabler disabler;
        list.searchNode("element" + std::to_string(middle));
        benchmark::ClobberMemory();
    }
}
BENCHMARK(BM_SearchNodeMiddle)->Arg(10)->Arg(20)->Arg(30);

static void BM_SearchNodeTail(benchmark::State& state) {
    forwardList list;
    for (int i = 0; i < state.range(0); i++) {
        list.addAtTail("element" + std::to_string(i));
    }
    
    for (auto _ : state) {
        OutputDisabler disabler;
        list.searchNode("element" + std::to_string(state.range(0) - 1));
        benchmark::ClobberMemory();
    }
}
BENCHMARK(BM_SearchNodeTail)->Arg(10)->Arg(20)->Arg(30);

static void BM_SearchNodeNotFound(benchmark::State& state) {
    forwardList list;
    for (int i = 0; i < state.range(0); i++) {
        list.addAtTail("element" + std::to_string(i));
    }
    
    for (auto _ : state) {
        OutputDisabler disabler;
        list.searchNode("nonexistent");
        benchmark::ClobberMemory();
    }
}
BENCHMARK(BM_SearchNodeNotFound)->Arg(10)->Arg(20)->Arg(30);

static void BM_AddBeforeIndex(benchmark::State& state) {
    for (auto _ : state) {
        state.PauseTiming();
        forwardList list;
        for (int i = 0; i < state.range(0); i++) {
            list.addAtTail("element" + std::to_string(i));
        }
        state.ResumeTiming();
        
        int middle = state.range(0) / 2;
        OutputDisabler disabler;
        list.addBeforeIndex("newMiddle", middle);
    }
}
BENCHMARK(BM_AddBeforeIndex)->Arg(10)->Arg(20)->Arg(30);

static void BM_AddAfterIndex(benchmark::State& state) {
    for (auto _ : state) {
        state.PauseTiming();
        forwardList list;
        for (int i = 0; i < state.range(0); i++) {
            list.addAtTail("element" + std::to_string(i));
        }
        state.ResumeTiming();
        
        int middle = state.range(0) / 2;
        OutputDisabler disabler;
        list.addAfterIndex("newMiddle", middle);
    }
}
BENCHMARK(BM_AddAfterIndex)->Arg(10)->Arg(20)->Arg(30);

static void BM_DeleteAtHead(benchmark::State& state) {
    for (auto _ : state) {
        state.PauseTiming();
        forwardList list;
        for (int i = 0; i < state.range(0); i++) {
            list.addAtTail("element" + std::to_string(i));
        }
        state.ResumeTiming();
        
        OutputDisabler disabler;
        list.deleteAtHead();
    }
}
BENCHMARK(BM_DeleteAtHead)->Arg(10)->Arg(20)->Arg(30);

static void BM_DeleteAtTail(benchmark::State& state) {
    for (auto _ : state) {
        state.PauseTiming();
        forwardList list;
        for (int i = 0; i < state.range(0); i++) {
            list.addAtTail("element" + std::to_string(i));
        }
        state.ResumeTiming();
        
        OutputDisabler disabler;
        list.deleteAtTail();
    }
}
BENCHMARK(BM_DeleteAtTail)->Arg(10)->Arg(20)->Arg(30);

static void BM_ValueDeleteHead(benchmark::State& state) {
    for (auto _ : state) {
        state.PauseTiming();
        forwardList list;
        for (int i = 0; i < state.range(0); i++) {
            list.addAtTail("element" + std::to_string(i));
        }
        state.ResumeTiming();
        
        OutputDisabler disabler;
        list.valueDelete("element0");
    }
}
BENCHMARK(BM_ValueDeleteHead)->Arg(10)->Arg(20)->Arg(30);

static void BM_ValueDeleteMiddle(benchmark::State& state) {
    for (auto _ : state) {
        state.PauseTiming();
        forwardList list;
        for (int i = 0; i < state.range(0); i++) {
            list.addAtTail("element" + std::to_string(i));
        }
        state.ResumeTiming();
        
        int middle = state.range(0) / 2;
        OutputDisabler disabler;
        list.valueDelete("element" + std::to_string(middle));
    }
}
BENCHMARK(BM_ValueDeleteMiddle)->Arg(10)->Arg(20)->Arg(30);

static void BM_PrintList(benchmark::State& state) {
    forwardList list;
    for (int i = 0; i < state.range(0); i++) {
        list.addAtTail("element" + std::to_string(i));
    }
    
    for (auto _ : state) {
        OutputDisabler disabler;
        list.printFL();
        benchmark::ClobberMemory();
    }
}
BENCHMARK(BM_PrintList)->Arg(10)->Arg(20)->Arg(30);

static void BM_MixedOperations(benchmark::State& state) {
    for (auto _ : state) {
        state.PauseTiming();
        forwardList list;
        state.ResumeTiming();
        
        OutputDisabler disabler;
        for (int i = 0; i < state.range(0); i++) {
            list.addAtTail("element" + std::to_string(i));
        }
        
        if (state.range(0) > 2) {
            list.addBeforeIndex("middle1", state.range(0) / 2);
            list.addAfterIndex("middle2", state.range(0) / 2);
            list.deleteAtHead();
            list.deleteAtTail();
            list.searchNode("middle1");
        }
    }
}
BENCHMARK(BM_MixedOperations)->Arg(10)->Arg(20)->Arg(30);

static void BM_DeleteBeforeIndex(benchmark::State& state) {
    for (auto _ : state) {
        state.PauseTiming();
        forwardList list;
        for (int i = 0; i < state.range(0); i++) {
            list.addAtTail("element" + std::to_string(i));
        }
        state.ResumeTiming();
        
        int middle = state.range(0) / 2;
        if (middle > 0) {
            OutputDisabler disabler;
            list.deleteBeforeIndex(middle);
        }
    }
}
BENCHMARK(BM_DeleteBeforeIndex)->Arg(10)->Arg(20)->Arg(30);

static void BM_DeleteAfterIndex(benchmark::State& state) {
    for (auto _ : state) {
        state.PauseTiming();
        forwardList list;
        for (int i = 0; i < state.range(0); i++) {
            list.addAtTail("element" + std::to_string(i));
        }
        state.ResumeTiming();
        
        int middle = state.range(0) / 2;
        if (middle < state.range(0) - 1) {
            OutputDisabler disabler;
            list.deleteAfterIndex(middle);
        }
    }
}
BENCHMARK(BM_DeleteAfterIndex)->Arg(10)->Arg(20)->Arg(30);

BENCHMARK_MAIN();