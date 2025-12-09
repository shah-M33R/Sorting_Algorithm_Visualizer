#pragma once
#include "Step.hpp"
#include <string>
#include <vector>
#include <nlohmann/json.hpp>

class StepRecorder {
public:
    void record(const Step& s);
    void flushToFile(const std::string& path, const Metadata& m);
    void clear();
    const std::vector<Step>& getSteps() const { return steps; }

private:
    std::vector<Step> steps;
};
