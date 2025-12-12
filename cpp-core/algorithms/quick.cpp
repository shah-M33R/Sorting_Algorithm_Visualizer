#include "../include/SortEngine.hpp"

// Partition function using Lomuto partition scheme
int partition(std::vector<int>& arr, int low, int high, StepRecorder& rec, Metrics& metrics) {
    int pivotValue = arr[high]; // Pivot is the last element
    int partitionIndex = (low - 1); // Index of smaller element

    // Highlight pivot selection
    rec.record({arr, {high}, {}, "pivot", metrics.comparisons, metrics.swaps, high});

    for (int j = low; j <= high - 1; j++) {
        metrics.comparisons++;
        rec.record({arr, {j, high}, {}, "compare", metrics.comparisons, metrics.swaps, high});

        if (arr[j] < pivotValue) {
            partitionIndex++; // Increment index of smaller element
            std::swap(arr[partitionIndex], arr[j]);
            metrics.swaps++;
            rec.record({arr, {partitionIndex, j}, {partitionIndex, j}, "swap", metrics.comparisons, metrics.swaps, high});
        }
    }
    // Place pivot in correct position
    std::swap(arr[partitionIndex + 1], arr[high]);
    metrics.swaps++;
    rec.record({arr, {partitionIndex + 1, high}, {partitionIndex + 1, high}, "swap", metrics.comparisons, metrics.swaps, high});
    
    return (partitionIndex + 1);
}

void quickSortRecursive(std::vector<int>& arr, int low, int high, StepRecorder& rec, Metrics& metrics) {
    if (low < high) {
        // partitionIndex is partitioning index, arr[p] is now at right place
        int pivotIndex = partition(arr, low, high, rec, metrics);

        // Separately sort elements before partition and after partition
        quickSortRecursive(arr, low, pivotIndex - 1, rec, metrics);
        quickSortRecursive(arr, pivotIndex + 1, high, rec, metrics);
    }
}

void SortEngine::quickSort(std::vector<int>& arr, StepRecorder& rec, Metrics& metrics) {
    rec.record({arr, {}, {}, "none", metrics.comparisons, metrics.swaps});
    quickSortRecursive(arr, 0, arr.size() - 1, rec, metrics);
    rec.record({arr, {}, {}, "none", metrics.comparisons, metrics.swaps});
}
