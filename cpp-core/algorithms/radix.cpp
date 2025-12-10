#include "../include/SortEngine.hpp"
#include <algorithm>
#include <vector>

void SortEngine::radixSort(std::vector<int>& arr, StepRecorder& rec, Metrics& metrics) {
    if (arr.empty()) return;

    int maxVal = *std::max_element(arr.begin(), arr.end());
    
    // Perform counting sort for every digit. Note: instead of passing digit number, 
    // exp is passed. exp is 10^i where i is current digit number
    for (int exp = 1; maxVal / exp > 0; exp *= 10) {
        std::vector<int> output(arr.size());
        int count[10] = {0};
        int n = arr.size();

        // Store count of occurrences in count[]
        for (int i = 0; i < n; i++) {
            count[(arr[i] / exp) % 10]++;
            // Visualization: Highlight current element being counted
            rec.record({arr, {i}, {}, "compare", metrics.comparisons, metrics.swaps});
            metrics.comparisons++;
        }

        // Change count[i] so that count[i] now contains actual
        // position of this digit in output[]
        for (int i = 1; i < 10; i++) {
            count[i] += count[i - 1];
        }

        // Build the output array
        for (int i = n - 1; i >= 0; i--) {
            int digit = (arr[i] / exp) % 10;
            output[count[digit] - 1] = arr[i];
            count[digit]--;
            
            // Visualization: Highlight implicit move to auxiliary array (conceptually)
            // Since we can't show aux array easily, we just highlight the source index
            rec.record({arr, {i}, {}, "move_to_aux", metrics.comparisons, metrics.swaps});
        }

        // Copy the output array to arr[], so that arr[] now
        // contains sorted numbers according to current digit
        for (int i = 0; i < n; i++) {
            arr[i] = output[i];
            // Visualization: Overwrite operation
            rec.record({arr, {}, {i}, "overwrite", metrics.comparisons, metrics.swaps});
            metrics.swaps++; // Treating overwrite as a swap for metrics simplicity
        }
    }
    
    rec.record({arr, {}, {}, "sorted", metrics.comparisons, metrics.swaps, {}, rec.getSteps().back().sorted_indices});
}
