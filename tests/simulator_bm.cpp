#include "benchmark/benchmark.h"
#include "examples.hpp"
#include "simulator.hpp"

#define ENDTIME 100

static void bm_simulation_multi_core(benchmark::State& state)
{
    for (auto _ : state) {
        state.PauseTiming();
        const auto seihr = stochastic::seihr(state.range(0));
        stochastic::Simulator sim{seihr};
        state.ResumeTiming();

        sim.simulateMultiple(100, ENDTIME, [](const int, double, const auto&) {});
        benchmark::ClobberMemory();
    }
}

static void bm_simulation_single_core(benchmark::State& state)
{
    for (auto _ : state) {
        state.PauseTiming();
        const auto seihr = stochastic::seihr(state.range(0));
        stochastic::Simulator sim{seihr};
        state.ResumeTiming();

        for (int i = 0; i < state.range(1); i++) {
            sim.simulate(ENDTIME, [](double, const auto&) {});
        }

        benchmark::ClobberMemory();
    }
}

BENCHMARK(bm_simulation_single_core)
    ->Args({10'000, 1})
    ->Unit(benchmark::kMillisecond)
    ->Name("1 sim single core");
BENCHMARK(bm_simulation_single_core)
    ->Args({10'000, 100})
    ->Unit(benchmark::kMillisecond)
    ->Name("100 sims single core");
BENCHMARK(bm_simulation_multi_core)
    ->Arg(10'000)
    ->Unit(benchmark::kMillisecond)
    ->Name("100 sims multi core");
