#include "../include/SortEngine.hpp"

void SortEngine::selectionSort(std::vector<int>& arr, StepRecorder& rec, Metrics& metrics) {
    size_t n = arr.size();
    
    rec.record({arr, {}, {}, "none", metrics.comparisons, metrics.swaps});

    for (size_t i = 0; i < n - 1; i++) {
        size_t min_idx = i;
        for (size_t j = i + 1; j < n; j++) {
            metrics.comparisons++;
            rec.record({arr, {(int)min_idx, (int)j}, {}, "compare", metrics.comparisons, metrics.swaps});
            
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }

        if (min_idx != i) {
            std::swap(arr[min_idx], arr[i]);
            metrics.swaps++;
            rec.record({arr, {(int)min_idx, (int)i}, {(int)min_idx, (int)i}, "swap", metrics.comparisons, metrics.swaps});
        }
    }
    
    rec.record({arr, {}, {}, "none", metrics.comparisons, metrics.swaps});
}
