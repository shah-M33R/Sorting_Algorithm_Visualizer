# 📊 Interactive Sorting Algorithm Visualizer

![C++](https://img.shields.io/badge/Backend-C%2B%2B17-blue)
![React](https://img.shields.io/badge/Frontend-React%20%7C%20TypeScript-61dafb)
![License](https://img.shields.io/badge/License-MIT-green)

A powerful hybrid tool designed to bridge the gap between abstract code and concrete understanding. This project uses a high-performance **C++ engine** to generate deterministic sorting logs and a **modern React frontend** to render frame-by-frame visualizations of complex algorithms.

---

## 📖 Documentation & Setup

**🚀 Ready to start?**

For complete installation instructions, VS Code setup, and a step-by-step walkthrough, please consult the **[User Manual](deliverables/UserManual.md)**.

---

## ✨ Key Features

*   **Hybrid Architecture:** Decoupled design (C++ Producer → JSON → React Consumer) ensures 100% algorithmic accuracy with high-performance rendering.
*   **Real-Time Metrics:** Track exact Comparison and Swap counts dynamically as the animation plays.
*   **Full Playback Control:** Play, Pause, Reset, scrub through the timeline, and adjust speed from **0.25x** (Slow Motion) to **4x** (Turbo).
*   **Delta Compression:** Optimized backend records only state changes, allowing for the visualization of massive datasets without memory bloat.
*   **Custom Datasets:** Generate random arrays via CLI or load specific test cases from files.

## 🛠️ Supported Algorithms

We support visualization for **9 distinct algorithms**, covering various time complexities and strategies:

| Comparison-Based | Non-Comparison Based |
| :--- | :--- |
| 🫧 Bubble Sort | 📦 Bucket Sort |
| 🔍 Selection Sort | 🔢 Radix Sort (LSD) |
| 📥 Insertion Sort | |
| 🐚 Shell Sort | |
| ⚡ Quick Sort (Lomuto) | |
| 🤝 Merge Sort | |
| 🌲 Heap Sort | |

## 📂 Project Structure

*   `cpp-core/` — **The Engine.** Contains C++17 source code, algorithm implementations, and the `StepRecorder` logic.
*   `frontend/` — **The View.** A Vite + React application using HTML5 Canvas for scalable rendering.
*   `deliverables/` — **The Docs.** Contains the Project Report, User Guide, and presentation slides.

---

## 🚀 Workflow Overview

1.  **Generate:** Use the C++ CLI tool (`sortgen`) to execute an algorithm and record its history to a JSON file.
2.  **Visualize:** Open the Web Interface, load the JSON file, and watch the algorithm in action.

> *Created for the Data Structures & Algorithms Course, Fall 2025, University Of Sargodha.*