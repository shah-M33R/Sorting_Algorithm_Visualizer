import React from 'react';

interface ControlPanelProps {
    isPlaying: boolean;
    onPlayPause: () => void;
    onStepForward: () => void;
    onStepBack: () => void;
    onReset: () => void;
    speed: number;
    onSpeedChange: (speed: number) => void;
    progress: number;
    totalFrames: number;
    onSeek: (frame: number) => void;
}

const ControlPanel: React.FC<ControlPanelProps> = ({
    isPlaying, onPlayPause, onStepForward, onStepBack, onReset,
    speed, onSpeedChange, progress, totalFrames, onSeek
}) => {
    return (
        <div className="flex flex-col gap-4 p-4 bg-white rounded-xl shadow-sm border border-slate-200">
            <div className="flex items-center justify-between gap-4">
                <button onClick={onReset} className="px-4 py-2 text-sm font-medium text-slate-600 hover:bg-slate-100 rounded-lg">Reset</button>
                <div className="flex items-center gap-2">
                    <button onClick={onStepBack} className="p-2 text-slate-600 hover:bg-slate-100 rounded-full" disabled={progress <= 0}>
                        ⏮
                    </button>
                    <button onClick={onPlayPause} className="px-6 py-2 bg-indigo-600 text-white rounded-lg hover:bg-indigo-700 font-semibold shadow-md transition-all active:scale-95">
                        {isPlaying ? 'Pause' : 'Play'}
                    </button>
                    <button onClick={onStepForward} className="p-2 text-slate-600 hover:bg-slate-100 rounded-full" disabled={progress >= totalFrames - 1}>
                        ⏭
                    </button>
                </div>
                <div className="flex items-center gap-2">
                    <span className="text-xs font-medium text-slate-500">Speed</span>
                    <input 
                        type="range" 
                        min="0.25" 
                        max="4" 
                        step="0.25" 
                        value={speed} 
                        onChange={(e) => onSpeedChange(parseFloat(e.target.value))}
                        className="w-24 accent-indigo-600"
                    />
                    <span className="text-xs w-8 text-right text-slate-600">{speed}x</span>
                </div>
            </div>
            <div className="flex items-center gap-3">
                <span className="text-xs text-slate-400 font-mono w-12 text-right">{progress}</span>
                <input 
                    type="range" 
                    min="0" 
                    max={totalFrames - 1} 
                    value={progress} 
                    onChange={(e) => onSeek(parseInt(e.target.value))}
                    className="flex-1 h-2 bg-slate-200 rounded-lg appearance-none cursor-pointer accent-indigo-600"
                />
                <span className="text-xs text-slate-400 font-mono w-12">{totalFrames - 1}</span>
            </div>
        </div>
    );
};

export default ControlPanel;
