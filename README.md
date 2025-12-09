# Interactive Sorting Algorithm Visualizer

A web-based tool to visualize sorting algorithms step-by-step, powered by a C++ backend.

## Quick Start

### 1. Frontend (The Visualizer)
This runs the web interface where you can watch the sorting animations.

1.  Open a terminal in the `frontend` directory:
    ```powershell
    cd frontend
    ```
2.  Install dependencies (first time only):
    ```powershell
    npm install
    ```
3.  Start the server:
    ```powershell
    npm run dev
    ```
4.  Open the local link shown in the terminal (usually `http://localhost:5173`).
    *   *Note: If you see "Loading...", ensure valid JSON logs exist in `frontend/public/sample_logs/`.*

### 2. Backend (Log Generator) - Optional
Running the backend is only necessary if you want to generate **new** visualization logs with different parameters (size, algorithm, etc.). The frontend comes with sample logs by default.

1.  Open a terminal in the `cpp-core` directory:
    ```powershell
    cd cpp-core
    ```
2.  Create a build folder and compile:
    ```powershell
    mkdir build
    cd build
    cmake ..
    cmake --build . --config Release
    ```
3.  Generate a log file:
    ```powershell
    ./sortgen --algorithm quick --size 50 --output ../../frontend/public/sample_logs/quick_50.json
    ```
    *   *Then restart the frontend or reload the page to see the new log (if you modify the code to load it).*

## Documentation
*   **User Guide**: [deliverables/UserManual.md](deliverables/UserManual.md) - How to use the tool.
*   **Technical Details**: [deliverables/TechnicalDocs.md](deliverables/TechnicalDocs.md) - Codebase structure and developer guide.
