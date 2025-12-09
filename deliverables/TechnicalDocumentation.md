# Technical Documentation - Sorting Visualizer

## Architecture Overview
The project follows a decoupled architecture:
1. **C++ Core**: Responsible for executing algorithms and recording every step (comparison, swap) into a deterministic JSON log.
2. **React Frontend**: A "dumb" player that renders the state defined in the JSON logs. It does not implement sorting logic itself, ensuring 100% fidelity to the C++ execution.

### Directory Structure
- `cpp-core/`: C++ source code, headers, and build scripts.
- `frontend/`: React + TypeScript application.
- `deliverables/`: Documentation and presentation materials.

## C++ Core Implementation

### Step Recording
The `StepRecorder` class captures the state of the array and any operations performed.
```cpp
struct Step {
    std::vector<int> array;
    std::vector<int> compare_indices;
    std::vector<int> swap_indices;
    std::string operation;
    // ...
};
```
Algorithms are instrumented to call `rec.record(...)` at critical points.

### Algorithms
Implemented in `cpp-core/algorithms/`:
- **Bubble Sort**: Optimized with early exit.
- **Selection Sort**: Minimizes swaps.
- **Insertion Sort**: efficient for small/nearly sorted data.
- **Merge Sort**: Recursive implementation.
- **Quick Sort**: Lomuto partition scheme.
- **Heap Sort**: In-place heap construction.

## Frontend Implementation

### Rendering
`VisualizerCanvas.tsx` uses the HTML5 Canvas API for high-performance rendering of bars. This avoids the DOM overhead of creating hundreds of `div` elements.

### State Management
`App.tsx` manages the current frame index and playback loop using `requestAnimationFrame`.

## JSON Schema
Logs follow a strict schema:
```json
{
  "metadata": { ... },
  "frames": [
    {
      "array": [ ... ],
      "highlights": { "compare": [0, 1] },
      "operation": "compare"
    },
    ...
  ]
}
```

## Testing Strategy
- **Unit Tests**: Verify that algorithms produce sorted output.
- **Integration Tests**: Verify that JSON logs can be parsed by the frontend.
- **Performance**: Canvas rendering ensures smooth 60fps playback even for large datasets.
