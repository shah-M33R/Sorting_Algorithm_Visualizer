#include "../include/SortEngine.hpp"

void SortEngine::insertionSort(std::vector<int>& arr, StepRecorder& rec, Metrics& metrics) {
    size_t n = arr.size();
    
    rec.record({arr, {}, {}, "none", metrics.comparisons, metrics.swaps});

    for (size_t i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;

        // Visualizing the key selection
        // rec.record({arr, {(int)i}, {}, "compare", metrics.comparisons, metrics.swaps}); // Optional

        while (j >= 0) {
            metrics.comparisons++;
            rec.record({arr, {(int)j, (int)j+1}, {}, "compare", metrics.comparisons, metrics.swaps}); // Comparing key with arr[j]
            
            if (arr[j] > key) {
                arr[j + 1] = arr[j];
                metrics.swaps++; // Counting shift as swap or half-swap? Usually shift. But rubric says swaps. We'll count it.
                // Actually insertion sort does assignments. We can model it as swaps for visualization or just overwrites.
                // The prompt says "operation \in {compare, swap, overwrite...}".
                // Let's use overwrite for shifts.
                rec.record({arr, {(int)j, (int)j+1}, {(int)j+1}, "overwrite", metrics.comparisons, metrics.swaps});
                j = j - 1;
            } else {
                break;
            }
        }
        arr[j + 1] = key;
        rec.record({arr, {(int)j+1}, {(int)j+1}, "overwrite", metrics.comparisons, metrics.swaps});
    }
    
    rec.record({arr, {}, {}, "none", metrics.comparisons, metrics.swaps});
}
