# Demo Video Script

**0:00 - 0:15**: Intro
"Hi, this is our Sorting Algorithm Visualizer. We built this to help students understand the internal mechanics of sorting algorithms."

**0:15 - 0:45**: The CLI
"First, we use our C++ engine to generate a sorting log. Here I'm running the `sortgen` command for Quick Sort with 50 elements. It runs the algorithm and saves every comparison and swap to a JSON file."
*(Show terminal running command)*

**0:45 - 1:30**: The Frontend
"Now we load this file into our React web app. You can see the array represented as bars. I'll hit Play."
*(Click Play, watch bars move)*
"We can speed it up or slow it down. Notice the violet bar—that's the pivot in Quick Sort. The yellow bars are being compared, and red ones are swapped."

**1:30 - 2:00**: Controls & Metrics
"I can pause at any time and step backward to see exactly what happened. On the right, we track real-time metrics. You can see how Quick Sort minimizes swaps compared to Bubble Sort."

**2:00 - 2:30**: Conclusion
"This architecture allows us to add any algorithm in C++ and immediately visualize it without changing the frontend code. Thanks for watching."

---

# Speaker Notes (Cheat Sheet)

## Member 1 (Leader)
- **Intro**: "We separated the logic (C++) from the view (React) to ensure our visualizations are 100% accurate to the code."
- **Architecture**: Explain the JSON hand-off.

## Member 2 (Simple Algos)
- **Bubble**: "Lots of swaps. Good for teaching, bad for performance."
- **Insertion**: "Great for nearly sorted data. Watch how it just slides elements in."

## Member 3 (Divide & Conquer)
- **Merge**: "It's stable. You'll see it working on left and right halves independently."
- **Quick**: "Fastest in practice. The pivot selection is key."

## Member 4 (Heap & Backend)
- **Heap**: "It builds a max-heap first. It's like an in-place selection sort but smarter."
- **StepRecorder**: "We had to inject recording calls into every swap to make this work."

## Member 5 (Frontend & Demo)
- **Canvas**: "We used Canvas instead of DOM elements so we can render 1000 bars without lag."
- **Demo**: *Drive the UI smoothly. Don't rush.*
