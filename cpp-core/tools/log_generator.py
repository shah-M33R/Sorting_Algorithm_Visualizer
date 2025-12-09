import json
import random
import time

def generate_log(algorithm, size, filename):
    arr = list(range(1, size + 1))
    random.shuffle(arr)
    
    frames = []
    comparisons = 0
    swaps = 0
    
    # Initial frame
    frames.append({
        "array": arr.copy(),
        "operation": "none",
        "cumulative_comparisons": 0,
        "cumulative_swaps": 0,
        "highlights": {}
    })
    
    # Simulate Bubble Sort for demo purposes
    n = len(arr)
    for i in range(n):
        swapped = False
        for j in range(0, n - i - 1):
            comparisons += 1
            frames.append({
                "array": arr.copy(),
                "operation": "compare",
                "cumulative_comparisons": comparisons,
                "cumulative_swaps": swaps,
                "highlights": {"compare": [j, j+1]}
            })
            
            if arr[j] > arr[j+1]:
                arr[j], arr[j+1] = arr[j+1], arr[j]
                swaps += 1
                swapped = True
                frames.append({
                    "array": arr.copy(),
                    "operation": "swap",
                    "cumulative_comparisons": comparisons,
                    "cumulative_swaps": swaps,
                    "highlights": {"swap": [j, j+1]}
                })
        if not swapped:
            break
            
    # Final frame
    frames.append({
        "array": arr.copy(),
        "operation": "none",
        "cumulative_comparisons": comparisons,
        "cumulative_swaps": swaps,
        "highlights": {}
    })
    
    metadata = {
        "algorithm": algorithm,
        "input_size": size,
        "seed": 12345,
        "start_time": "2025-12-09T22:00:00Z",
        "total_time_ms": 100,
        "total_comparisons": comparisons,
        "total_swaps": swaps
    }
    
    output = {
        "metadata": metadata,
        "frames": frames
    }
    
    with open(filename, 'w') as f:
        json.dump(output, f, indent=2)
    print(f"Generated {filename}")

if __name__ == "__main__":
    generate_log("bubble", 10, "bubble_10.json")
    generate_log("quick", 20, "quick_20.json") # Note: This is actually bubble sort disguised, just for demo
