#include "benchmark/benchmark.h"
#include "CrossProduct.h"
#include <random>
#include <algorithm>
/*
 * A bit hacky way to create random inputs
 */
double a[3];
double b[3];
class InitArray
{
public:
  InitArray()
  {
    std::mt19937 gen;
    std::uniform_real_distribution<> dis(1.0, 10.0);
    for (size_t i = 0; i < 3; ++i) {
      a[i] = dis(gen);
    }
    for (size_t i = 0; i < 3; ++i) {
      b[i] = dis(gen);
    }
  }
};
InitArray initArray;

static void
CrossProduct_bench(benchmark::State& state)
{

  double c[3] = {};
  for (auto _ : state) {
    const int n = state.range(0);
    for (int i = 0; i < n; ++i) {
      crossScalar(c, a, b);;
      benchmark::DoNotOptimize(c);
      benchmark::ClobberMemory();
    }
  }
}
BENCHMARK(CrossProduct_bench)->RangeMultiplier(2)->Range(1024, 8192);

static void
CrossProductVec_bench(benchmark::State& state)
{
  double c[3] = {};
  for (auto _ : state) {
    const int n = state.range(0);
    for (int i = 0; i < n; ++i) {
      crossVecSSE(c, a, b);;
      benchmark::DoNotOptimize(c);
      benchmark::ClobberMemory();
    }
  }
}
BENCHMARK(CrossProductVec_bench)->RangeMultiplier(2)->Range(1024, 8192);

BENCHMARK_MAIN();
