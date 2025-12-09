cmake_minimum_required(VERSION 3.14)
project(SortGen VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

# Fetch nlohmann_json
FetchContent_Declare(
    json
    URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz
)
FetchContent_MakeAvailable(json)

# Include directories
include_directories(include)

# Source files
file(GLOB ALGO_SOURCES "algorithms/*.cpp")
set(SOURCES
    main.cpp
    step_recorder/StepRecorder.cpp
    ${ALGO_SOURCES}
)

# Executable
add_executable(sortgen ${SOURCES})

# Link libraries
target_link_libraries(sortgen PRIVATE nlohmann_json::nlohmann_json)

# Enable testing
enable_testing()
# add_subdirectory(tests) # Uncomment when tests are added
