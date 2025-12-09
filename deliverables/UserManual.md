# Interactive Sorting Algorithm Visualizer - User Manual

## Introduction
Welcome to the Interactive Sorting Algorithm Visualizer! This tool allows you to explore how different sorting algorithms work through step-by-step visualization.

## Quick Start

### Running the Visualizer (Frontend)
1. Navigate to the `frontend` directory.
2. Run `npm install` to install dependencies.
3. Run `npm run dev` to start the local server.
4. Open your browser to the URL shown (usually `http://localhost:5173`).

### Generating New Logs (CLI)
To generate new visualization logs, you need to compile the C++ core.
1. Navigate to `cpp-core`.
2. Create a build directory: `mkdir build && cd build`.
3. Run CMake: `cmake ..` (requires CMake and a C++ compiler).
4. Build: `cmake --build . --config Release`.
5. Run the generator:
   ```bash
   ./sortgen --algorithm quick --size 50 --output ../../frontend/public/sample_logs/quick_50.json
   ```

## Features

### Control Panel
- **Play/Pause**: Start or stop the animation.
- **Step Forward/Back**: Move one frame at a time when paused.
- **Speed Slider**: Adjust playback speed from 0.25x to 4x.
- **Reset**: Return to the initial unsorted state.
- **Seek Bar**: Jump to any point in the sorting process.

### Metrics
The right-hand panel shows real-time statistics:
- **Comparisons**: Number of times two elements were compared.
- **Swaps**: Number of times elements were moved.
- **Algorithm**: The current algorithm being visualized.

### Visual Guide
- **Grey Bars**: Unsorted elements.
- **Amber**: Elements being compared.
- **Red**: Elements being swapped.
- **Violet**: Pivot element (Quick Sort).
- **Green**: Sorted elements.

## Troubleshooting
- **"Failed to load log"**: Ensure the JSON file exists in `frontend/public/sample_logs` and is formatted correctly.
- **CLI Errors**: Make sure you have a C++17 compatible compiler installed.
