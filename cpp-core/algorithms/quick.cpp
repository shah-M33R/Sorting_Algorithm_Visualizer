#include "../include/SortEngine.hpp"

int partition(std::vector<int>& arr, int low, int high, StepRecorder& rec, Metrics& metrics) {
    int pivot = arr[high];
    int i = (low - 1);

    // Highlight pivot
    rec.record({arr, {high}, {}, "pivot", metrics.comparisons, metrics.swaps, high});

    for (int j = low; j <= high - 1; j++) {
        metrics.comparisons++;
        rec.record({arr, {j, high}, {}, "compare", metrics.comparisons, metrics.swaps, high});

        if (arr[j] < pivot) {
            i++;
            std::swap(arr[i], arr[j]);
            metrics.swaps++;
            rec.record({arr, {i, j}, {i, j}, "swap", metrics.comparisons, metrics.swaps, high});
        }
    }
    std::swap(arr[i + 1], arr[high]);
    metrics.swaps++;
    rec.record({arr, {i + 1, high}, {i + 1, high}, "swap", metrics.comparisons, metrics.swaps, high});
    return (i + 1);
}

void quickSortRecursive(std::vector<int>& arr, int low, int high, StepRecorder& rec, Metrics& metrics) {
    if (low < high) {
        int pi = partition(arr, low, high, rec, metrics);
        quickSortRecursive(arr, low, pi - 1, rec, metrics);
        quickSortRecursive(arr, pi + 1, high, rec, metrics);
    }
}

void SortEngine::quickSort(std::vector<int>& arr, StepRecorder& rec, Metrics& metrics) {
    rec.record({arr, {}, {}, "none", metrics.comparisons, metrics.swaps});
    quickSortRecursive(arr, 0, arr.size() - 1, rec, metrics);
    rec.record({arr, {}, {}, "none", metrics.comparisons, metrics.swaps});
}
