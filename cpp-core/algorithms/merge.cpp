#include "../include/SortEngine.hpp"

void merge(std::vector<int>& arr, int l, int m, int r, StepRecorder& rec, Metrics& metrics) {
    int n1 = m - l + 1;
    int n2 = r - m;

    std::vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    int i = 0;
    int j = 0;
    int k = l;

    while (i < n1 && j < n2) {
        metrics.comparisons++;
        rec.record({arr, {l + i, m + 1 + j}, {}, "compare", metrics.comparisons, metrics.swaps});

        if (L[i] <= R[j]) {
            arr[k] = L[i];
            rec.record({arr, {k}, {k}, "overwrite", metrics.comparisons, metrics.swaps});
            i++;
        } else {
            arr[k] = R[j];
            rec.record({arr, {k}, {k}, "overwrite", metrics.comparisons, metrics.swaps});
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        rec.record({arr, {k}, {k}, "overwrite", metrics.comparisons, metrics.swaps});
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        rec.record({arr, {k}, {k}, "overwrite", metrics.comparisons, metrics.swaps});
        j++;
        k++;
    }
}

void mergeSortRecursive(std::vector<int>& arr, int l, int r, StepRecorder& rec, Metrics& metrics) {
    if (l >= r) return;
    
    int m = l + (r - l) / 2;
    mergeSortRecursive(arr, l, m, rec, metrics);
    mergeSortRecursive(arr, m + 1, r, rec, metrics);
    merge(arr, l, m, r, rec, metrics);
}

void SortEngine::mergeSort(std::vector<int>& arr, StepRecorder& rec, Metrics& metrics) {
    rec.record({arr, {}, {}, "none", metrics.comparisons, metrics.swaps});
    mergeSortRecursive(arr, 0, arr.size() - 1, rec, metrics);
    rec.record({arr, {}, {}, "none", metrics.comparisons, metrics.swaps});
}
