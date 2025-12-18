export interface Step {
    array: number[];
    compare_indices: number[];
    swap_indices: number[];
    operation: string;
    cumulative_comparisons: number;
    cumulative_swaps: number;
    pivot_index?: number;
    sorted_indices?: number[];
}

export interface Frame {
    array: number[];
    highlights: {
        compare?: number[];
        swap?: number[];
        pivot?: number;
    };
    operation: string;
    cumulative_comparisons: number;
    cumulative_swaps: number;
    sorted_indices?: number[];
}

export interface Metadata {
    algorithm: string;
    input_size: number;
    seed?: number; // Made optional
    start_time?: string; // Made optional
    total_time_ms?: number; // Made optional
    total_comparisons?: number; // Made optional
    total_swaps?: number; // Made optional
    initial_config?: string; // Added for client-side
    time_complexity?: string; // Added for client-side
    space_complexity?: string; // Added for client-side
}

export interface Log {
    metadata: Metadata;
    frames: Frame[];
}
