#include "../include/SortEngine.hpp"

void heapify(std::vector<int>& arr, int n, int i, StepRecorder& rec, Metrics& metrics) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n) {
        metrics.comparisons++;
        rec.record({arr, {left, largest}, {}, "compare", metrics.comparisons, metrics.swaps});
        if (arr[left] > arr[largest])
            largest = left;
    }

    if (right < n) {
        metrics.comparisons++;
        rec.record({arr, {right, largest}, {}, "compare", metrics.comparisons, metrics.swaps});
        if (arr[right] > arr[largest])
            largest = right;
    }

    if (largest != i) {
        std::swap(arr[i], arr[largest]);
        metrics.swaps++;
        rec.record({arr, {i, largest}, {i, largest}, "swap", metrics.comparisons, metrics.swaps});

        heapify(arr, n, largest, rec, metrics);
    }
}

void SortEngine::heapSort(std::vector<int>& arr, StepRecorder& rec, Metrics& metrics) {
    int n = arr.size();
    rec.record({arr, {}, {}, "none", metrics.comparisons, metrics.swaps});

    // Build heap (rearrange array)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i, rec, metrics);

    // One by one extract an element from heap
    for (int i = n - 1; i > 0; i--) {
        // Move current root to end
        std::swap(arr[0], arr[i]);
        metrics.swaps++;
        rec.record({arr, {0, i}, {0, i}, "swap", metrics.comparisons, metrics.swaps});

        // call max heapify on the reduced heap
        heapify(arr, i, 0, rec, metrics);
    }
    rec.record({arr, {}, {}, "none", metrics.comparisons, metrics.swaps});
}
