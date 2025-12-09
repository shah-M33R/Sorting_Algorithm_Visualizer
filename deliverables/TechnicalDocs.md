# Technical Documentation

## 1. System Architecture

The **Interactive Sorting Algorithm Visualizer** uses a decoupled architecture:

*   **Backend (C++17)**: High-performance sorting engine. It executes sorting algorithms and records every comparison and swap into a structured JSON log.
*   **Data Layer (JSON)**: The interface between backend and frontend. Contains a frame-by-frame snapshot of the sorting process configuration.
*   **Frontend (React + TypeScript)**: A modern web application that parses the JSON logs and renders the playback on an HTML5 Canvas.

## 2. Folder Structure & File Responsibilities

### `cpp-core/` (Backend)
Contains the C++ source code for generating sorting logs.

*   **`main.cpp`**: entry point for the CLI tool (`sortgen`). Parses arguments (algorithm, size, output path) and orchestrates the sorting process.
*   **`CMakeLists.txt`**: Build configuration file. Handles dependencies (like `nlohmann/json`) and compilation flags.
*   **`algorithms/`**:
    *   **`SortEngine.cpp`**: Abstract base class for all sorters.
    *   **`[algorithm].cpp`**: (e.g. `quick.cpp`, `bubble.cpp`) specific implementations. Each file implements the `sort()` method and calls `recordFrame()` to save steps.
*   **`step_recorder/`**: Handles the JSON object construction, ensuring efficient appending of frames during key operations (compare, swap).

### `frontend/` (Frontend)
The web application for visualization.

*   **`src/App.tsx`**: Main application logic. Manages state (`isPlaying`, `currentFrameIndex`), handles file uploads (Load JSON), and the generator modal.
*   **`src/types.ts`**: TypeScript definitions for the JSON schema (`Log`, `Frame`, `Metadata`), ensuring type safety across the app.
*   **`src/utils/StepParser.ts`**: Helper to validate and parse raw JSON data into the application's internal state format.
*   **`src/components/`**:
    *   **`VisualizerCanvas.tsx`**: The rendering engine. Takes the current `Frame` and draws the bars on HTML Canvas. Uses color coding (Yellow=Compare, Red=Swap, Green=Sorted).
    *   **`ControlPanel.tsx`**: UI for Play/Pause, Slider, and Stepping controls.

### `deliverables/`
Project documentation and artifacts.
*   `UserManual.md`: Guide for end-users.
*   `TechnicalDocs.md`: (This file) Developer guide.

## 3. Data Flow

1.  **Generation**: User runs `./sortgen --algorithm bubble --size 10`.
2.  **Execution**: `main.cpp` instantiates `BubbleSort`. It runs the loop.
3.  **Recording**: Every time `BubbleSort` compares or swaps, it notifies `StepRecorder`.
4.  **Serialization**: `StepRecorder` writes the state to a JSON file (e.g., `bubble_10.json`).
5.  **Visualization**:
    *   User opens the Web App.
    *   App fetches/uploads the JSON file.
    *   `App.tsx` reads `frames` array.
    *   `requestAnimationFrame` loop updates the frame index based on `speed`.
    *   `VisualizerCanvas` redraws the new state.

## 4. Requirement Verification
*   **C++17 / CMake**: Used in `cpp-core`.
*   **React / TypeScript / Vite**: Used in `frontend`.
*   **JSON Schema**: Implemented in `step_recorder` and `types.ts`.
*   **Manual/Docs**: Provided in `deliverables`.
