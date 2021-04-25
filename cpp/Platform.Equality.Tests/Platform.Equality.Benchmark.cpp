#include <Platform.Equality.h>
#include <benchmark/benchmark.h>

#include <ctime>
#include <iostream>
#include <span>
#include <any>

namespace Platform::Equality::Benchmark
{
    namespace Any
    {
        static void AnyCompare(benchmark::State& state)
        {
            srand(time(nullptr));

            for (auto _ : state)
            {
                auto a = rand();
                auto b = rand();

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
                auto a = rand();
                auto b = rand();

                bool result;
                benchmark::DoNotOptimize(result = a == b);
            }
        }

        BENCHMARK(NormalCompare);
    }

    namespace Range
    {
        namespace
        {
            constexpr int test_size = 10000;
        }

        static void Foreach_VectorCompare(benchmark::State& state)
        {
            srand(time(nullptr));

            std::vector<int> a(test_size);
            for (auto& it : a)
            {
                it = rand();
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
            srand(time(nullptr));

            std::vector<int> list(test_size);
            for (auto& it : list)
            {
                it = rand();
            }

            // std::span not have operator==
            auto a = std::span<int>(list); // span have Range initializer ==> std::span<int>(list.begin(), list.size())
            auto b = std::span<int>(list);

            bool result;
            for (auto _ : state)
            {
                benchmark::DoNotOptimize(result = std::equal_to<std::span<int>>{}(a, b));
            }
        }
        BENCHMARK(PlatformEquality_VectorCompare);

        static void STL_VectorCompare(benchmark::State& state)
        {
            srand(time(nullptr));

            std::vector<int> a(test_size);
            for (auto& it : a)
            {
                it = rand();
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

BENCHMARK_MAIN();