#include <benchmark/benchmark.h>
#include "doubleFL.hpp"
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
        doubleFL list;
        for (int i = 0; i < state.range(0); i++) {
            list.addAtTail("element" + std::to_string(i));
        }
        state.ResumeTiming();
        
        OutputDisabler disabler;
        list.addAtHead("newHead");
        benchmark::ClobberMemory();
    }
}
BENCHMARK(BM_AddAtHead)->Arg(10)->Arg(20)->Arg(30);

static void BM_AddAtTail(benchmark::State& state) {
    for (auto _ : state) {
        state.PauseTiming();
        doubleFL list;
        for (int i = 0; i < state.range(0); i++) {
            list.addAtTail("element" + std::to_string(i));
        }
        state.ResumeTiming();
        
        OutputDisabler disabler;
        list.addAtTail("newTail");
        benchmark::ClobberMemory();
    }
}
BENCHMARK(BM_AddAtTail)->Arg(10)->Arg(20)->Arg(30);

static void BM_AddBeforeIndex(benchmark::State& state) {
    for (auto _ : state) {
        state.PauseTiming();
        doubleFL list;
        for (int i = 0; i < state.range(0); i++) {
            list.addAtTail("element" + std::to_string(i));
        }
        state.ResumeTiming();
        
        int middle = state.range(0) / 2;
        OutputDisabler disabler;
        list.addBeforeIndex("newMiddle", middle);
        benchmark::ClobberMemory();
    }
}
BENCHMARK(BM_AddBeforeIndex)->Arg(10)->Arg(20)->Arg(30);

static void BM_AddAfterIndex(benchmark::State& state) {
    for (auto _ : state) {
        state.PauseTiming();
        doubleFL list;
        for (int i = 0; i < state.range(0); i++) {
            list.addAtTail("element" + std::to_string(i));
        }
        state.ResumeTiming();
        
        int middle = state.range(0) / 2;
        OutputDisabler disabler;
        list.addAfterIndex("newMiddle", middle);
        benchmark::ClobberMemory();
    }
}
BENCHMARK(BM_AddAfterIndex)->Arg(10)->Arg(20)->Arg(30);

static void BM_SearchValueHead(benchmark::State& state) {
    doubleFL list;
    for (int i = 0; i < state.range(0); i++) {
        list.addAtTail("element" + std::to_string(i));
    }
    
    for (auto _ : state) {
        OutputDisabler disabler;
        list.searchValue("element0");
        benchmark::ClobberMemory();
    }
}
BENCHMARK(BM_SearchValueHead)->Arg(10)->Arg(20)->Arg(30);

static void BM_SearchValueMiddle(benchmark::State& state) {
    doubleFL list;
    for (int i = 0; i < state.range(0); i++) {
        list.addAtTail("element" + std::to_string(i));
    }
    
    for (auto _ : state) {
        int middle = state.range(0) / 2;
        OutputDisabler disabler;
        list.searchValue("element" + std::to_string(middle));
        benchmark::ClobberMemory();
    }
}
BENCHMARK(BM_SearchValueMiddle)->Arg(10)->Arg(20)->Arg(30);

static void BM_SearchValueTail(benchmark::State& state) {
    doubleFL list;
    for (int i = 0; i < state.range(0); i++) {
        list.addAtTail("element" + std::to_string(i));
    }
    
    for (auto _ : state) {
        OutputDisabler disabler;
        list.searchValue("element" + std::to_string(state.range(0) - 1));
        benchmark::ClobberMemory();
    }
}
BENCHMARK(BM_SearchValueTail)->Arg(10)->Arg(20)->Arg(30);

static void BM_SearchValueNotFound(benchmark::State& state) {
    doubleFL list;
    for (int i = 0; i < state.range(0); i++) {
        list.addAtTail("element" + std::to_string(i));
    }
    
    for (auto _ : state) {
        OutputDisabler disabler;
        list.searchValue("nonexistent");
        benchmark::ClobberMemory();
    }
}
BENCHMARK(BM_SearchValueNotFound)->Arg(10)->Arg(20)->Arg(30);

static void BM_DeleteAtHead(benchmark::State& state) {
    for (auto _ : state) {
        state.PauseTiming();
        doubleFL list;
        for (int i = 0; i < state.range(0); i++) {
            list.addAtTail("element" + std::to_string(i));
        }
        state.ResumeTiming();
        
        OutputDisabler disabler;
        list.deleteAtHead();
        benchmark::ClobberMemory();
    }
}
BENCHMARK(BM_DeleteAtHead)->Arg(10)->Arg(20)->Arg(30);

static void BM_DeleteAtTail(benchmark::State& state) {
    for (auto _ : state) {
        state.PauseTiming();
        doubleFL list;
        for (int i = 0; i < state.range(0); i++) {
            list.addAtTail("element" + std::to_string(i));
        }
        state.ResumeTiming();
        
        OutputDisabler disabler;
        list.deleteAtTail();
        benchmark::ClobberMemory();
    }
}
BENCHMARK(BM_DeleteAtTail)->Arg(10)->Arg(20)->Arg(30);

static void BM_DeleteBeforeIndex(benchmark::State& state) {
    for (auto _ : state) {
        state.PauseTiming();
        doubleFL list;
        for (int i = 0; i < state.range(0); i++) {
            list.addAtTail("element" + std::to_string(i));
        }
        state.ResumeTiming();
        
        int middle = state.range(0) / 2;
        if (middle > 0) {
            OutputDisabler disabler;
            list.deleteBeforeIndex(middle);
            benchmark::ClobberMemory();
        }
    }
}
BENCHMARK(BM_DeleteBeforeIndex)->Arg(10)->Arg(20)->Arg(30);

static void BM_DeleteAfterIndex(benchmark::State& state) {
    for (auto _ : state) {
        state.PauseTiming();
        doubleFL list;
        for (int i = 0; i < state.range(0); i++) {
            list.addAtTail("element" + std::to_string(i));
        }
        state.ResumeTiming();
        
        int middle = state.range(0) / 2;
        if (middle < state.range(0) - 1) {
            OutputDisabler disabler;
            list.deleteAfterIndex(middle);
            benchmark::ClobberMemory();
        }
    }
}
BENCHMARK(BM_DeleteAfterIndex)->Arg(10)->Arg(20)->Arg(30);

static void BM_DeleteValueHead(benchmark::State& state) {
    for (auto _ : state) {
        state.PauseTiming();
        doubleFL list;
        for (int i = 0; i < state.range(0); i++) {
            list.addAtTail("element" + std::to_string(i));
        }
        state.ResumeTiming();
        
        OutputDisabler disabler;
        list.deleteValue("element0");
        benchmark::ClobberMemory();
    }
}
BENCHMARK(BM_DeleteValueHead)->Arg(10)->Arg(20)->Arg(30);

static void BM_DeleteValueMiddle(benchmark::State& state) {
    for (auto _ : state) {
        state.PauseTiming();
        doubleFL list;
        for (int i = 0; i < state.range(0); i++) {
            list.addAtTail("element" + std::to_string(i));
        }
        state.ResumeTiming();
        
        int middle = state.range(0) / 2;
        OutputDisabler disabler;
        list.deleteValue("element" + std::to_string(middle));
        benchmark::ClobberMemory();
    }
}
BENCHMARK(BM_DeleteValueMiddle)->Arg(10)->Arg(20)->Arg(30);

static void BM_DeleteValueTail(benchmark::State& state) {
    for (auto _ : state) {
        state.PauseTiming();
        doubleFL list;
        for (int i = 0; i < state.range(0); i++) {
            list.addAtTail("element" + std::to_string(i));
        }
        state.ResumeTiming();
        
        OutputDisabler disabler;
        list.deleteValue("element" + std::to_string(state.range(0) - 1));
        benchmark::ClobberMemory();
    }
}
BENCHMARK(BM_DeleteValueTail)->Arg(10)->Arg(20)->Arg(30);

static void BM_PrintDoubleFL(benchmark::State& state) {
    doubleFL list;
    for (int i = 0; i < state.range(0); i++) {
        list.addAtTail("element" + std::to_string(i));
    }
    
    for (auto _ : state) {
        OutputDisabler disabler;
        list.printDoubleFL();
        benchmark::ClobberMemory();
    }
}
BENCHMARK(BM_PrintDoubleFL)->Arg(10)->Arg(20)->Arg(30);

static void BM_MixedAddRemove(benchmark::State& state) {
    for (auto _ : state) {
        doubleFL list;
        OutputDisabler disabler;
        
        for (int i = 0; i < state.range(0); i++) {
            list.addAtTail("element" + std::to_string(i));
            if (i % 3 == 0) {
                list.addAtHead("headElement" + std::to_string(i));
            }
            if (i % 4 == 0 && i > 0) {
                list.deleteAtTail();
            }
            if (i % 5 == 0 && i > 0) {
                list.deleteAtHead();
            }
        }
        benchmark::ClobberMemory();
    }
}
BENCHMARK(BM_MixedAddRemove)->Arg(10)->Arg(20)->Arg(30);

static void BM_MixedInsertOperations(benchmark::State& state) {
    for (auto _ : state) {
        doubleFL list;
        OutputDisabler disabler;
        
        for (int i = 0; i < state.range(0); i++) {
            list.addAtTail("base" + std::to_string(i));
        }
        
        if (state.range(0) > 2) {
            list.addBeforeIndex("before_middle", state.range(0) / 2);
            list.addAfterIndex("after_middle", state.range(0) / 2);
            list.addAtHead("new_head");
            list.addAtTail("new_tail");
        }
        benchmark::ClobberMemory();
    }
}
BENCHMARK(BM_MixedInsertOperations)->Arg(10)->Arg(20)->Arg(30);

static void BM_MixedDeleteOperations(benchmark::State& state) {
    for (auto _ : state) {
        state.PauseTiming();
        doubleFL list;
        for (int i = 0; i < state.range(0) * 2; i++) {
            list.addAtTail("element" + std::to_string(i));
        }
        state.ResumeTiming();
        
        OutputDisabler disabler;
        if (state.range(0) > 3) {
            list.deleteAtHead();
            list.deleteAtTail();
            list.deleteBeforeIndex(state.range(0) / 2);
            list.deleteAfterIndex(state.range(0) / 4);
            list.deleteValue("element" + std::to_string(state.range(0)));
        }
        benchmark::ClobberMemory();
    }
}
BENCHMARK(BM_MixedDeleteOperations)->Arg(10)->Arg(20)->Arg(30);

static void BM_EmptyListOperations(benchmark::State& state) {
    for (auto _ : state) {
        doubleFL list;
        OutputDisabler disabler;
        
        list.deleteAtHead();
        list.deleteAtTail();
        list.searchValue("anything");
        list.printDoubleFL();
        
        benchmark::ClobberMemory();
    }
}
BENCHMARK(BM_EmptyListOperations);

BENCHMARK_MAIN();