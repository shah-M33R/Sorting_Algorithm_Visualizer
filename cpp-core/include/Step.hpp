#pragma once
#include <vector>
#include <string>
#include <optional>

struct Step {
    std::vector<int> array;
    std::vector<int> compare_indices;
    std::vector<int> swap_indices;
    std::string operation; // "compare", "swap", "overwrite", "pivot", "mark_sorted", "none"
    size_t cumulative_comparisons = 0;
    size_t cumulative_swaps = 0;
    std::optional<int> pivot_index;
    std::vector<int> sorted_indices;
};

struct Metadata {
    std::string algorithm;
    size_t input_size;
    unsigned int seed;
    std::string start_time;
    long long total_time_ms;
    size_t total_comparisons;
    size_t total_swaps;
};

struct Metrics {
    size_t comparisons = 0;
    size_t swaps = 0;
};
