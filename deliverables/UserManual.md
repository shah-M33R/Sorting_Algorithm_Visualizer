# 📘 Interactive Sorting Algorithm Visualizer - User Guide

Welcome to the **Interactive Sorting Algorithm Visualizer**! This comprehensive guide will help you set up your development environment, generate sorting data using the C++ engine, and visualize the algorithms in the web interface.

---

## 📑 Table of Contents
1. [Part 1: Environment Setup (VS Code & C++)](#part-1-environment-setup-vs-code--c)
2. [Part 2: Building the Backend](#part-2-building-the-backend)
3. [Part 3: Generating Visualization Data](#part-3-generating-visualization-data)
4. [Part 4: Running the Frontend](#part-4-running-the-frontend)
5. [Part 5: Using the Interface](#part-5-using-the-interface)
6. [Troubleshooting](#troubleshooting)

---

## Part 1: Environment Setup (VS Code & C++)

Before running the project, you need to ensure your computer is ready to compile C++ code. Follow these steps to set up **Visual Studio Code** and **CMake**.

### 1. Install Required Extensions
Open VS Code, go to the Extensions view (`Ctrl+Shift+X`), and install the following:
1.  **C/C++** (by Microsoft) - *For IntelliSense and debugging.*
2.  **CMake** (by twxs) - *For CMake language support.*
3.  **CMake Tools** (by Microsoft) - *For building the project easily.*

### 2. Install Build Tools (MinGW/GCC)
You need a C++ compiler to turn the code into an executable. We recommend **MSYS2 (MinGW)** for Windows.

1.  **Download & Install:** Download the installer from [msys2.org](https://www.msys2.org/) and follow the installation instructions.
2.  **Install Toolchain:** Open the MSYS2 terminal (MSYS2 UCRT64) and run:
    ```bash
    pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-cmake mingw-w64-x86_64-make
    ```
    *(Type `Y` and hit Enter when prompted).*
3.  **Add to System PATH:**
    *   Press the **Windows Key**, type "env", and select **Edit the system environment variables**.
    *   Click **Environment Variables**.
    *   Under **System variables**, find **Path**, select it, and click **Edit**.
    *   Click **New** and paste the path to your MinGW bin folder (usually `C:\msys64\mingw64\bin`).
    *   Click **OK** on all windows.
    *   **Restart VS Code** for these changes to take effect.

---

## Part 2: Building the Backend

The Backend is the "Engine" that runs the sorting algorithms.

1.  **Open Project:** Open the `cpp-core` folder in VS Code (`File > Open Folder...`).
2.  **Configure:** You should see a notification asking "Configure project?". Click **Yes**.
3.  **Build:** Look at the blue status bar at the bottom of VS Code. Click the **Build** (or Gear icon) button, or press `F7`.
    *   *Alternative (Command Line):* Open the terminal in `cpp-core` and run:
        ```powershell
        cmake -S . -B build
        cmake --build build
        ```
        *(Note: The first command configures the project and downloads dependencies. The second compiles it.)*

✅ **Success:** You should now have an executable file named `sortgen.exe` located in the `build/` or `build/Debug/` folder.

---

## Part 3: Generating Visualization Data

This tool works by "recording" an algorithm into a file. You must generate this file before you can watch it.

1.  Open the integrated terminal in VS Code (`Ctrl + ~`).
2.  Navigate to your build directory:
    ```bash
    cd build
    ```
    *Note: You can also run from the `cpp-core` root. If you specify an output path like `logs/data.json`, the tool will automatically create the `logs` folder for you.*
3.  Run the generator command using the following syntax:
    ```bash
    ./sortgen --algorithm [name] --size [number] --output [filename.json]
    ```

### Example Commands
*   **Quick Sort (50 elements):**
    ```bash
    ./sortgen --algorithm quick --size 50 --output quick_data.json
    ```
*   **Bubble Sort (20 elements):**
    ```bash
    ./sortgen --algorithm bubble --size 20 --output bubble_data.json
    ```

**Available Algorithms:** `bubble`, `selection`, `insertion`, `merge`, `quick`, `heap`, `shell`, `radix`, `bucket`.

---

## Part 4: Running the Frontend

The Frontend is the "Player" that shows the animation.

1.  Open a new terminal window.
2.  Navigate to the frontend folder:
    ```bash
    cd frontend
    ```
3.  Install dependencies (only required the first time):
    ```bash
    npm install
    ```
4.  Start the local server:
    ```bash
    npm run dev
    ```
5.  **Open the Link:** Hold `Ctrl` and click the link shown in the terminal (usually `http://localhost:5173`).

---

## Part 5: Using the Interface

Once the web page is open:

1.  **Load Data:**
    *   Click the **"Load JSON"** button in the top right corner.
    *   Navigate to your `cpp-core/build` folder and select the `.json` file you generated in Part 3 (e.g., `quick_data.json`).
2.  **Playback Controls:**
    *   ▶️ **Play/Pause:** Start or freeze the animation.
    *   ⏩ **Speed:** Use the slider to switch between Slow Motion (0.25x) and Fast Forward (4x).
    *   🔄 **Reset:** Returns the bars to the start.
    *   📍 **Seek:** Drag the progress bar to jump to any specific moment.
3.  **Visual Legend:**
    *   <span style="color:gray">■</span> **Grey:** Unsorted / Idle.
    *   <span style="color:orange">■</span> **Amber:** Elements being **Compared**.
    *   <span style="color:red">■</span> **Red:** Elements being **Swapped**.
    *   <span style="color:purple">■</span> **Violet:** Pivot Element (Quick Sort).
    *   <span style="color:green">■</span> **Green:** Sorted.

---

## Troubleshooting

### "CMake is not recognized"
*   **Cause:** CMake is not installed or not in your System PATH.
*   **Fix:** Revisit Part 1, Step 3. Ensure the path to the `bin` folder is correct. Restart your computer if necessary.

### "cl is not recognized"
*   **Cause:** You might be trying to use the Microsoft Visual C++ compiler without the Developer Command Prompt.
*   **Fix:** If using MinGW, ensure you selected the **GCC Kit** in VS Code (Part 2, Step 2). If you want to use MSVC, open VS Code from the "Developer Command Prompt for VS 2022".

### "npm is not recognized"
*   **Cause:** Node.js is not installed.
*   **Fix:** Download and install the LTS version from [nodejs.org](https://nodejs.org/).

### The Visualizer shows "Loading..." forever
*   **Cause:** No file has been loaded, or the JSON file is empty.
*   **Fix:** Ensure you successfully ran the `sortgen` command in Part 3 and selected that specific file using the "Load JSON" button.