#include <benchmark/benchmark.h>
#include <string>
#include <memory>

#include "trie.hpp"

static void BM_ConstructTrie(benchmark::State& state) {
    auto trie = std::make_unique<Trie>();
    for ([[maybe_unused]] auto stt : state) {
        trie->construct_trie(std::vector<std::string>{
                "the", "a", "there", "answer", "any", "by", "bye", "their", "abc"});
    }
}
BENCHMARK(BM_ConstructTrie);

static void BM_SearchByPrefix(benchmark::State& state) {
    auto trie = std::make_unique<Trie>();
    trie->construct_trie(std::vector<std::string>{
            "the", "a", "there", "answer", "any", "by", "bye", "their", "abc"});

    for ([[maybe_unused]] auto stt : state) {
        std::ignore = trie->search_by_prefix("th");
    }
}
BENCHMARK(BM_SearchByPrefix);

BENCHMARK_MAIN();