#include <random>

#include "Geometry.cpp"
#include "benchmark/benchmark.h"

const int N = 10000;

template <typename T>
static void BM_GeometryRealAddition(benchmark::State& state) {
    for (auto _ : state) {
        T x = 0;
        benchmark::DoNotOptimize(x += 3);
        benchmark::DoNotOptimize(x = -x + 7);
        benchmark::DoNotOptimize(x + 10);
        benchmark::DoNotOptimize(x + x + x);
        benchmark::DoNotOptimize(x += 12.5);
        benchmark::DoNotOptimize(x -= 1e-7);
        benchmark::DoNotOptimize(x -= 4);
        benchmark::DoNotOptimize(8 - x);
        benchmark::DoNotOptimize(-x + 3);
        benchmark::DoNotOptimize(x += (x + 1e7));
    }
}

BENCHMARK(BM_GeometryRealAddition<float>);
BENCHMARK(BM_GeometryRealAddition<double>);
BENCHMARK(BM_GeometryRealAddition<long double>);
BENCHMARK(BM_GeometryRealAddition<Real>);
