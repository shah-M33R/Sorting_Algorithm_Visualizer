#include "../include/SortEngine.hpp"
#include <algorithm>
#include <vector>

void SortEngine::bucketSort(std::vector<int>& arr, StepRecorder& rec, Metrics& metrics) {
    if (arr.empty()) return;
    int n = arr.size();
    
    // 1. Create buckets
    int max_val = *std::max_element(arr.begin(), arr.end());
    int min_val = *std::min_element(arr.begin(), arr.end());
    
    // Use n buckets roughly spaced
    int bucket_count = n;
    std::vector<std::vector<int>> buckets(bucket_count);
    double range = (double)(max_val - min_val + 1) / bucket_count;

    // 2. Distribute into buckets
    for (int i = 0; i < n; i++) {
        int bucket_idx = (arr[i] - min_val) / range;
        if (bucket_idx >= bucket_count) bucket_idx = bucket_count - 1; // safety
        
        buckets[bucket_idx].push_back(arr[i]);
        
        // Visualize: Highlight element being moved to bucket
        rec.record({arr, {i}, {}, "to_bucket", metrics.comparisons, metrics.swaps});
    }
    
    // 3. Sort individual buckets and gather
    int idx = 0;
    for (int i = 0; i < bucket_count; i++) {
        // Sort individual bucket
        // For a demonstration, we use std::sort (IntroSort). 
        // In a strict Bucket Sort, you might recursively use Bucket Sort or Insertion Sort.
        std::sort(buckets[i].begin(), buckets[i].end());
        
        // Gather back to array
        for (int val : buckets[i]) {
            arr[idx] = val;
            // Visualize: Overwrite from bucket back to array
            rec.record({arr, {}, {idx}, "overwrite", metrics.comparisons, metrics.swaps});
            metrics.swaps++;
            idx++;
        }
    }
    
    rec.record({arr, {}, {}, "sorted", metrics.comparisons, metrics.swaps});
}
