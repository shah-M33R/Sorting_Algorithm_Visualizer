# Presentation Slides

## Slide 1: Title
**Interactive Sorting Algorithm Visualizer**
*Team Members: [Member 1], [Member 2], [Member 3], [Member 4], [Member 5]*
*Course: Data Structures*

## Slide 2: Problem Statement
- **Goal**: Visualize how sorting algorithms work internally.
- **Challenge**: Textbooks are static; code is abstract.
- **Solution**: An interactive tool to see comparisons, swaps, and recursion in real-time.

## Slide 3: Architecture
- **C++ Backend**: High-performance execution, generates "Step Logs".
- **JSON Interface**: Decouples logic from view.
- **React Frontend**: Smooth canvas-based animation.

## Slide 4: C++ Core & Step Recorder
- **Design Pattern**: Observer-like pattern.
- **Mechanism**: Algorithms don't just sort; they "report" actions to a Recorder.
- **Benefit**: Deterministic replay. The same seed always produces the same animation.

## Slide 5: Algorithm Highlights - O(n^2)
- **Bubble Sort**: The classic bubbling effect.
- **Selection Sort**: Finding the minimum.
- **Insertion Sort**: Building a sorted subarray.
- *Key Metric*: Comparisons vs. Swaps.

## Slide 6: Algorithm Highlights - O(n log n)
- **Merge Sort**: Divide and Conquer. Visualized as merging sub-arrays.
- **Quick Sort**: Partitioning around a pivot.
- **Heap Sort**: Tree structure mapped to array.

## Slide 7: Frontend Implementation
- **Tech Stack**: React, TypeScript, Vite.
- **Rendering**: HTML5 Canvas for performance (handling 100+ bars).
- **Control**: Precise frame-by-frame navigation.

## Slide 8: Live Demo
*(Switch to Application)*
1. Load `quick_50.json`.
2. Play at 1x speed.
3. Pause at a partition step.
4. Show metrics updating.

## Slide 9: Benchmarks & Conclusion
- **Performance**: Quick Sort consistently outperforms Bubble Sort on large N.
- **Learning Outcome**: Visualizing "Big O" in practice.
- **Future Work**: Radix sort, sound effects.

## Slide 10: Q&A
- Thank you!
- Questions?
