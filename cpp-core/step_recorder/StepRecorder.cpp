#include "../include/StepRecorder.hpp"
#include <fstream>
#include <iostream>
#include <filesystem>

using json = nlohmann::json;

void StepRecorder::record(const Step& s) {
    steps.push_back(s);
}

void StepRecorder::clear() {
    steps.clear();
}

void StepRecorder::flushToFile(const std::string& path, const Metadata& m) {
    json j;
    
    // Metadata
    j["metadata"] = {
        {"algorithm", m.algorithm},
        {"input_size", m.input_size},
        {"seed", m.seed},
        {"start_time", m.start_time},
        {"total_time_ms", m.total_time_ms},
        {"total_comparisons", m.total_comparisons},
        {"total_swaps", m.total_swaps},
        {"time_complexity", m.time_complexity},
        {"space_complexity", m.space_complexity}
    };

    // Frames
    j["frames"] = json::array();
    for (const auto& step : steps) {
        json frame;
        frame["array"] = step.array;
        frame["operation"] = step.operation;
        frame["cumulative_comparisons"] = step.cumulative_comparisons;
        frame["cumulative_swaps"] = step.cumulative_swaps;

        json highlights;
        if (!step.compare_indices.empty()) highlights["compare"] = step.compare_indices;
        if (!step.swap_indices.empty()) highlights["swap"] = step.swap_indices;
        if (step.pivot_index.has_value()) highlights["pivot"] = step.pivot_index.value();
        
        frame["highlights"] = highlights;
        
        // Optional: sorted indices for visualization
        if (!step.sorted_indices.empty()) {
             frame["sorted_indices"] = step.sorted_indices;
        }

        j["frames"].push_back(frame);
    }

    std::filesystem::path p(path);
    if (p.has_parent_path()) {
        std::filesystem::create_directories(p.parent_path());
    }

    std::ofstream file(path);
    if (file.is_open()) {
        file << j.dump(2); // Pretty print with indentation 2
        file.close();
    } else {
        std::cerr << "Error: Could not open file " << path << " for writing." << std::endl;
    }
}
