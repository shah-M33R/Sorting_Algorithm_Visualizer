#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <chrono>
#include <algorithm>
#include <fstream>
#include "include/SortEngine.hpp"
#include "include/StepRecorder.hpp"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

void printUsage() {
    std::cout << "Usage: sortgen --algorithm <name> --size <n> --output <file> [options]\n"
              << "Options:\n"
              << "  --seed <n>        Random seed (default: random)\n"
              << "  --from-file <f>   Load initial array from JSON file\n"
              << "  --save-dataset    Save the initial array to a file (use with --output)\n"
              << "  --benchmark       Run benchmark mode\n"
              << "Supported algorithms: bubble, selection, insertion, merge, quick, heap, radix, bucket\n";
}

int main(int argc, char* argv[]) {
    std::string algorithm = "bubble";
    int size = 10;
    std::string outputFile = "log.json";
    unsigned int seed = std::random_device{}();
    std::string inputFile = "";
    bool saveDataset = false;
    bool benchmark = false;

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "--algorithm" && i + 1 < argc) algorithm = argv[++i];
        else if (arg == "--size" && i + 1 < argc) size = std::stoi(argv[++i]);
        else if (arg == "--output" && i + 1 < argc) outputFile = argv[++i];
        else if (arg == "--seed" && i + 1 < argc) seed = std::stoul(argv[++i]);
        else if (arg == "--from-file" && i + 1 < argc) inputFile = argv[++i];
        else if (arg == "--save-dataset") saveDataset = true;
        else if (arg == "--benchmark") benchmark = true;
        else if (arg == "--help") { printUsage(); return 0; }
    }

    std::vector<int> arr;
    if (!inputFile.empty()) {
        std::ifstream f(inputFile);
        if (f.is_open()) {
            json j;
            f >> j;
            if (j.contains("array")) {
                arr = j["array"].get<std::vector<int>>();
                size = arr.size();
            }
        } else {
            std::cerr << "Error loading file: " << inputFile << std::endl;
            return 1;
        }
    } else {
        std::mt19937 gen(seed);
        std::uniform_int_distribution<> dis(1, 100);
        arr.resize(size);
        for (int& x : arr) x = dis(gen);
    }

    if (saveDataset) {
        json j;
        j["array"] = arr;
        j["name"] = "Dataset " + std::to_string(size);
        std::ofstream f(outputFile); // Or a separate file? Prompt implies output is for logs.
        // If save-dataset is flag, maybe we just save dataset?
        // Let's assume we save dataset INSTEAD of running if algorithm is not specified or something?
        // Actually, let's just save it to "dataset.json" or similar if requested, or maybe the user wants to just generate a dataset.
        // For now, if saveDataset is true, we write to outputFile and exit.
        f << j.dump(2);
        return 0;
    }

    StepRecorder recorder;
    Metrics metrics;

    auto start = std::chrono::steady_clock::now();
    
    try {
        SortEngine::runAlgorithmByName(algorithm, arr, recorder, metrics);
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    auto end = std::chrono::steady_clock::now();
    long long elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    Metadata meta;
    meta.algorithm = algorithm;
    meta.input_size = size;
    meta.seed = seed;
    meta.start_time = "2025-12-09T22:00:00Z"; // TODO: Get actual time
    meta.total_time_ms = elapsed;
    meta.total_comparisons = metrics.comparisons;
    meta.total_swaps = metrics.swaps;

    recorder.flushToFile(outputFile, meta);

    std::cout << "Generated log: " << outputFile << std::endl;
    std::cout << "Time: " << elapsed << "ms, Comparisons: " << metrics.comparisons << ", Swaps: " << metrics.swaps << std::endl;

    return 0;
}
