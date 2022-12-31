#include <random>

#include "Geometry.hpp"
#include "benchmark/benchmark.h"

using namespace acmlib::geometry;

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
    T y = 2;
    benchmark::DoNotOptimize(++y);
    benchmark::DoNotOptimize(x++);
    benchmark::DoNotOptimize(--x);
    benchmark::DoNotOptimize(y--);
    benchmark::DoNotOptimize(+y);
    benchmark::DoNotOptimize(-x);
  }
}

template <typename T>
static void BM_GeometryRealMultiplication(benchmark::State& state) {
  for (auto _ : state) {
    T x = 3, y = 4;
    benchmark::DoNotOptimize(x * y);
    benchmark::DoNotOptimize(x * (-1.4));
    benchmark::DoNotOptimize(3 * y);
    benchmark::DoNotOptimize(y *= 10);
    benchmark::DoNotOptimize(y *= 1e-8);
    benchmark::DoNotOptimize(x *= (y *= y));
  }
}

template <typename T>
static void BM_GeometryRealDivision(benchmark::State& state) {
  for (auto _ : state) {
    T x = 123;
    T y = -78.848924;
    benchmark::DoNotOptimize(x / y);
    benchmark::DoNotOptimize(x / 89.333);
    benchmark::DoNotOptimize(54 / y);
    benchmark::DoNotOptimize(x /= (y / 3));
    benchmark::DoNotOptimize(x /= x);
    benchmark::DoNotOptimize(x /= (y /= 3));
  }
}

template <typename T>
static void BM_GeometryRealComparison(benchmark::State& state) {
  for (auto _ : state) {
    T x = -9.8;
    T y = 13;
    benchmark::DoNotOptimize(x < y);
    benchmark::DoNotOptimize(y > -14);
    benchmark::DoNotOptimize(x == -9.9);
    benchmark::DoNotOptimize(x != 2 * y);
    benchmark::DoNotOptimize(7 <= x);
    benchmark::DoNotOptimize(y >= 13);
  }
}

BENCHMARK(BM_GeometryRealAddition<long double>);
BENCHMARK(BM_GeometryRealAddition<Real>);
BENCHMARK(BM_GeometryRealMultiplication<long double>);
BENCHMARK(BM_GeometryRealMultiplication<Real>);
BENCHMARK(BM_GeometryRealDivision<long double>);
BENCHMARK(BM_GeometryRealDivision<Real>);
BENCHMARK(BM_GeometryRealComparison<long double>);
BENCHMARK(BM_GeometryRealComparison<Real>);
