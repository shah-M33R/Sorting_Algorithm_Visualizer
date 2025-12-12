#include "../include/SortEngine.hpp"

// Merges two subarrays of arr[].
// First subarray is arr[left..mid]
// Second subarray is arr[mid+1..right]
void merge(std::vector<int>& arr, int left, int mid, int right, StepRecorder& rec, Metrics& metrics) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Create temporary arrays
    std::vector<int> LeftArray(n1), RightArray(n2);

    // Copy data to temp arrays
    for (int i = 0; i < n1; i++)
        LeftArray[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        RightArray[j] = arr[mid + 1 + j];

    // Merge the temp arrays back into arr[left..right]
    int i = 0; // Initial index of first subarray
    int j = 0; // Initial index of second subarray
    int k = left; // Initial index of merged subarray

    while (i < n1 && j < n2) {
        metrics.comparisons++;
        rec.record({arr, {left + i, mid + 1 + j}, {}, "compare", metrics.comparisons, metrics.swaps});

        if (LeftArray[i] <= RightArray[j]) {
            arr[k] = LeftArray[i];
            // Visualizing overwrite action
            rec.record({arr, {k}, {k}, "overwrite", metrics.comparisons, metrics.swaps});
            i++;
        } else {
            arr[k] = RightArray[j];
            rec.record({arr, {k}, {k}, "overwrite", metrics.comparisons, metrics.swaps});
            j++;
        }
        k++;
    }

    // Copy the remaining elements of LeftArray[], if there are any
    while (i < n1) {
        arr[k] = LeftArray[i];
        rec.record({arr, {k}, {k}, "overwrite", metrics.comparisons, metrics.swaps});
        i++;
        k++;
    }

    // Copy the remaining elements of RightArray[], if there are any
    while (j < n2) {
        arr[k] = RightArray[j];
        rec.record({arr, {k}, {k}, "overwrite", metrics.comparisons, metrics.swaps});
        j++;
        k++;
    }
}

void mergeSortRecursive(std::vector<int>& arr, int left, int right, StepRecorder& rec, Metrics& metrics) {
    if (left >= right) return;
    
    int mid = left + (right - left) / 2;
    mergeSortRecursive(arr, left, mid, rec, metrics);
    mergeSortRecursive(arr, mid + 1, right, rec, metrics);
    merge(arr, left, mid, right, rec, metrics);
}

void SortEngine::mergeSort(std::vector<int>& arr, StepRecorder& rec, Metrics& metrics) {
    rec.record({arr, {}, {}, "none", metrics.comparisons, metrics.swaps});
    mergeSortRecursive(arr, 0, arr.size() - 1, rec, metrics);
    rec.record({arr, {}, {}, "none", metrics.comparisons, metrics.swaps});
}
