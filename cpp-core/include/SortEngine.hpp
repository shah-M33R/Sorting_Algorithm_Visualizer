#pragma once
#include <vector>
#include <string>
#include <functional>
#include "StepRecorder.hpp"
#include "Step.hpp"

// Function signature for sorting algorithms
using SortFunction = std::function<void(std::vector<int>&, StepRecorder&, Metrics&)>;

class SortEngine {
public:
    static void runAlgorithmByName(const std::string& name, std::vector<int>& arr, StepRecorder& rec, Metrics& metrics);
    
    // Algorithm declarations
    static void bubbleSort(std::vector<int>& arr, StepRecorder& rec, Metrics& metrics);
    static void selectionSort(std::vector<int>& arr, StepRecorder& rec, Metrics& metrics);
    static void insertionSort(std::vector<int>& arr, StepRecorder& rec, Metrics& metrics);
    static void mergeSort(std::vector<int>& arr, StepRecorder& rec, Metrics& metrics);
    static void quickSort(std::vector<int>& arr, StepRecorder& rec, Metrics& metrics);
    static void heapSort(std::vector<int>& arr, StepRecorder& rec, Metrics& metrics);
};
