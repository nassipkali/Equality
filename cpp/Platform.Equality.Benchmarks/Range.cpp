#include <Platform.Equality.h>
#include <benchmark/benchmark.h>

#include <chrono>
#include <random>
#include <span>


namespace Platform::Equality::Benchmarks
{
    namespace Range
    {
        namespace
        {
            constexpr int test_size = 100000;
            std::mt19937 random(std::chrono::high_resolution_clock().now().time_since_epoch().count());
        }

        static void Foreach_VectorCompare(benchmark::State& state)
        {
            std::vector<int> a(test_size);
            for (auto& it : a)
            {
                it = random();
            }

            auto b = a;

            for (auto _ : state)
            {
                bool result = true;
                for (int i = 0; i < a.size(); i++)
                {
                    if (a[i] != b[i])
                    {
                        result = false;
                        break;
                    }
                }
                benchmark::DoNotOptimize(result);
            }
        }

        BENCHMARK(Foreach_VectorCompare);

        static void PlatformEquality_VectorCompare(benchmark::State& state)
        {
            std::vector<int> list1(test_size);
            for (auto& it : list1)
            {
                it = random();
            }

            auto list2 = list1;
            
            auto a = std::span<int>(list1);
            auto b = std::span<int>(list2);

            bool result;
            for (auto _ : state)
            {
                benchmark::DoNotOptimize(result = std::equal_to<std::span<int>>{}(a, b));
            }
        }

        BENCHMARK(PlatformEquality_VectorCompare);

        static void STL_VectorCompare(benchmark::State& state)
        {
            std::vector<int> a(test_size);
            for (auto& it : a)
            {
                it = random();
            }
            std::vector<int> b = a;

            bool result;
            for (auto _ : state)
            {
                benchmark::DoNotOptimize(result = a == b);
            }
        }

        BENCHMARK(STL_VectorCompare);
    }
}
