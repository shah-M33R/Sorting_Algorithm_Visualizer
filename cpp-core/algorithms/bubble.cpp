#include "../include/SortEngine.hpp"

void SortEngine::bubbleSort(std::vector<int>& arr, StepRecorder& rec, Metrics& metrics) {
    bool swapped;
    size_t n = arr.size();
    
    // Initial state
    rec.record({arr, {}, {}, "none", metrics.comparisons, metrics.swaps});

    for (size_t i = 0; i < n - 1; i++) {
        swapped = false;
        for (size_t j = 0; j < n - i - 1; j++) {
            // Compare
            metrics.comparisons++;
            rec.record({arr, {(int)j, (int)j + 1}, {}, "compare", metrics.comparisons, metrics.swaps});

            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
                metrics.swaps++;
                swapped = true;
                rec.record({arr, {(int)j, (int)j + 1}, {(int)j, (int)j + 1}, "swap", metrics.comparisons, metrics.swaps});
            }
        }
        
        // Mark sorted
        // We can optionally mark the last element as sorted
        if (!swapped) break;
    }
    
    // Final state
    rec.record({arr, {}, {}, "none", metrics.comparisons, metrics.swaps});
}
