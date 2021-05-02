#include <Platform.Equality.h>
#include <benchmark/benchmark.h>

#include <chrono>
#include <random>

namespace Platform::Equality::Benchmarks
{
    namespace Any
    {
        namespace
        {
            std::mt19937 random(std::chrono::high_resolution_clock().now().time_since_epoch().count());
        }

        static void AnyCompare(benchmark::State& state)
        {
            for (auto _ : state)
            {
                auto a = random();
                auto b = random();

                bool result;
                benchmark::DoNotOptimize(result = std::any(a) == std::any(b));
            }
        }

        BENCHMARK(AnyCompare);

        static void NormalCompare(benchmark::State& state)
        {
            srand(time(nullptr));

            for (auto _ : state)
            {
                auto a = random();
                auto b = random();

                bool result;
                benchmark::DoNotOptimize(result = a == b);
            }
        }

        BENCHMARK(NormalCompare);
    }
}
