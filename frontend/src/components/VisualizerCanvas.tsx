import React, { useEffect, useRef } from 'react';
import { Frame } from '../types';

interface VisualizerCanvasProps {
    frame: Frame;
    width: number;
    height: number;
}

const VisualizerCanvas: React.FC<VisualizerCanvasProps> = ({ frame, width, height }) => {
    const canvasRef = useRef<HTMLCanvasElement>(null);

    const n = frame.array.length;
    const MIN_BAR_WIDTH = 6;
    const actualWidth = Math.max(width, n * MIN_BAR_WIDTH);

    useEffect(() => {
        const canvas = canvasRef.current;
        if (!canvas) return;
        const ctx = canvas.getContext('2d');
        if (!ctx) return;

        // Clear canvas
        ctx.clearRect(0, 0, actualWidth, height);

        const array = frame.array;
        const barWidth = actualWidth / n;
        const maxVal = Math.max(...array, 10); // Avoid div by zero
        
        array.forEach((val, i) => {
            const barHeight = (val / maxVal) * (height - 20);
            const x = i * barWidth;
            const y = height - barHeight;

            // Determine color
            let color = '#64748b'; // Default slate-500
            
            if (frame.highlights.compare && frame.highlights.compare.includes(i)) {
                color = '#f59e0b'; // Amber (Compare)
            }
            if (frame.highlights.swap && frame.highlights.swap.includes(i)) {
                color = '#ef4444'; // Red (Swap)
            }
            if (frame.highlights.pivot === i) {
                color = '#8b5cf6'; // Violet (Pivot)
            }
            if (frame.sorted_indices && frame.sorted_indices.includes(i)) {
                color = '#22c55e'; // Green (Sorted)
            }

            ctx.fillStyle = color;
            
            // Rounded top bars
            ctx.beginPath();
            ctx.roundRect(x + 1, y, Math.max(1, barWidth - 2), barHeight, [4, 4, 0, 0]);
            ctx.fill();
        });

    }, [frame, width, height, actualWidth, n]); // Dependencies updated

    return (
        <div style={{ overflowX: 'auto', width: width }}>
            <canvas 
                ref={canvasRef} 
                width={actualWidth} 
                height={height} 
                className="rounded-lg shadow-inner bg-slate-50" 
                style={{ display: 'block' }} 
            />
        </div>
    );
};

export default VisualizerCanvas;
