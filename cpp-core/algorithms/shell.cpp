#include "../include/SortEngine.hpp"

void SortEngine::shellSort(std::vector<int>& arr, StepRecorder& rec, Metrics& metrics) {
    size_t n = arr.size();
    
    // Initial state
    rec.record({arr, {}, {}, "none", metrics.comparisons, metrics.swaps});

    for (size_t gap = n / 2; gap > 0; gap /= 2) {
        for (size_t i = gap; i < n; i += 1) {
            int temp = arr[i];
            size_t j;
            
            // Compare
            metrics.comparisons++;
            rec.record({arr, {(int)i, (int)(i - gap)}, {}, "compare", metrics.comparisons, metrics.swaps});

            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                // Swap/Shift
                metrics.comparisons++; // Loop check comparison
                metrics.swaps++; // Treating shift as swap for visualizer metric simplicity or just counting assignments
                
                arr[j] = arr[j - gap];
                
                // Visualization of the shift/swap
                rec.record({arr, {(int)j, (int)(j - gap)}, {(int)j, (int)(j - gap)}, "swap", metrics.comparisons, metrics.swaps});
            }
            if (j >= gap) {
                 metrics.comparisons++; // Failed loop check
            }
            
            arr[j] = temp;
            // Record final placement of temp
            if (j != i) {
                metrics.swaps++;
                rec.record({arr, {(int)j, (int)i}, {(int)j}, "swap", metrics.comparisons, metrics.swaps});
            }
        }
    }

    // Final state
    rec.record({arr, {}, {}, "none", metrics.comparisons, metrics.swaps});
}
