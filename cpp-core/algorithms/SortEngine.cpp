#include "../include/SortEngine.hpp"
#include <stdexcept>
#include <iostream>

void SortEngine::runAlgorithmByName(const std::string& name, std::vector<int>& arr, StepRecorder& rec, Metrics& metrics) {
    if (name == "bubble") {
        bubbleSort(arr, rec, metrics);
    } else if (name == "selection") {
        selectionSort(arr, rec, metrics);
    } else if (name == "insertion") {
        insertionSort(arr, rec, metrics);
    } else if (name == "merge") {
        mergeSort(arr, rec, metrics);
    } else if (name == "quick") {
        quickSort(arr, rec, metrics);
    } else if (name == "heap") {
        heapSort(arr, rec, metrics);
    } else if (name == "radix") {
        radixSort(arr, rec, metrics);
    } else if (name == "bucket") {
        bucketSort(arr, rec, metrics);
    } else {
        throw std::runtime_error("Unknown algorithm: " + name);
    }
}
