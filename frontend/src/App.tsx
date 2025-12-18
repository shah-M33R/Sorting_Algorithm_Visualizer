import React, { useState, useEffect, useRef } from 'react';
import VisualizerCanvas from './components/VisualizerCanvas';
import ControlPanel from './components/ControlPanel';
import { Log } from './types';
import { StepParser } from './utils/StepParser';



const App: React.FC = () => {
    const [log, setLog] = useState<Log | null>(null);
    const [currentFrameIndex, setCurrentFrameIndex] = useState(0);
    const [isPlaying, setIsPlaying] = useState(false);
    const [speed, setSpeed] = useState(1);
    const [showGenModal, setShowGenModal] = useState(false);
    
    const animationRef = useRef<number>();
    const lastTimeRef = useRef<number>(0);
    const fileInputRef = useRef<HTMLInputElement>(null);

    // Load sample log on mount
    useEffect(() => {
        fetch('/sample_logs/bubble_10.json')
            .then(res => res.json())
            .then(data => {
                const parsed = StepParser.parse(data);
                setLog(parsed);
            })
            .catch(err => console.error("Failed to load sample log", err));
    }, []);

    const handlePlayPause = () => {
        setIsPlaying(!isPlaying);
    };

    const animate = (time: number) => {
        if (!isPlaying || !log) return;
        
        if (time - lastTimeRef.current > (500 / speed)) {
            setCurrentFrameIndex(prev => {
                if (prev >= log.frames.length - 1) {
                    setIsPlaying(false);
                    return prev;
                }
                return prev + 1;
            });
            lastTimeRef.current = time;
        }
        animationRef.current = requestAnimationFrame(animate);
    };

    useEffect(() => {
        if (isPlaying) {
            animationRef.current = requestAnimationFrame(animate);
        } else {
            if (animationRef.current) cancelAnimationFrame(animationRef.current);
        }
        return () => {
            if (animationRef.current) cancelAnimationFrame(animationRef.current);
        };
    }, [isPlaying, log, speed]);

    // Handle File Upload
    const handleFileLoad = (e: React.ChangeEvent<HTMLInputElement>) => {
        const file = e.target.files?.[0];
        if (!file) return;

        const reader = new FileReader();
        reader.onload = (ev) => {
            try {
                const json = JSON.parse(ev.target?.result as string);
                const parsed = StepParser.parse(json);
                setLog(parsed);
                setCurrentFrameIndex(0);
                setIsPlaying(false);
            } catch (err) {
                alert("Invalid JSON log file.");
                console.error(err);
            }
        };
        reader.readAsText(file);
    };



    const currentFrame = log ? log.frames[currentFrameIndex] : null;

    return (
        <div className="min-h-screen bg-slate-100 text-slate-900 font-sans p-8">
            {/* Hidden Input for File Loading */}
            <input 
                type="file" 
                ref={fileInputRef} 
                className="hidden" 
                accept=".json" 
                onChange={handleFileLoad} 
            />

            {/* Generator Modal */}
            {showGenModal && (
                <div className="fixed inset-0 bg-black/50 flex items-center justify-center z-50">
                    <div className="bg-white p-6 rounded-xl shadow-xl max-w-lg w-full">
                        <h3 className="text-xl font-bold mb-4">Generate New Sorting Log</h3>
                        <div className="space-y-4">
                            <div className="p-4 bg-slate-50 rounded-lg border border-slate-200">
                                <p className="text-sm text-slate-600 mb-2">To generate a new dataset, run one of the following commands in your terminal (cpp-core/build):</p>
                                <div className="space-y-2 mb-3">
                                    <code className="block bg-slate-800 text-white p-3 rounded text-xs overflow-x-auto font-mono">
                                        ./sortgen --algorithm [type] --size [N] --output [filename].json
                                    </code>
                                    <code className="block bg-slate-800 text-white p-3 rounded text-xs overflow-x-auto font-mono">
                                        ./sortgen --algorithm [type] --array "[1, 5, 2, ...]" --output [filename].json
                                    </code>
                                </div>
                                <div className="text-sm text-slate-700">
                                    <p className="font-semibold mb-1">Available Types:</p>
                                    <ul>
                                        <li>bubble</li>
                                        <li>selection</li>
                                        <li>insertion</li>
                                        <li>merge</li>
                                        <li>quick</li>
                                        <li>heap</li>
                                        <li>shell</li>
                                        <li>radix</li>
                                        <li>bucket</li>
                                    </ul>
                                </div>
                                <p className="text-xs text-slate-500 mt-4">After generating, click "Load JSON" to view your new dataset.</p>
                            </div>
                        </div>
                        <button 
                            onClick={() => setShowGenModal(false)}
                            className="mt-6 w-full py-2 border border-slate-300 rounded-lg text-slate-600 hover:bg-slate-50"
                        >
                            Close
                        </button>
                    </div>
                </div>
            )}

            <div className="max-w-4xl mx-auto space-y-6">
                <header className="flex justify-between items-center">
                    <div>
                        <h1 className="text-3xl font-bold text-slate-800">Sorting Visualizer</h1>
                        <p className="text-slate-500">Interactive Algorithm Demonstration</p>
                    </div>
                    <div className="flex gap-2">
                        <button 
                            onClick={() => fileInputRef.current?.click()}
                            className="px-4 py-2 bg-white border border-slate-300 rounded-lg text-sm hover:bg-slate-50"
                        >
                            Load JSON
                        </button>
                        <button 
                            onClick={() => setShowGenModal(true)}
                            className="px-4 py-2 bg-indigo-600 text-white rounded-lg text-sm hover:bg-indigo-700 shadow-sm"
                        >
                            Generate New
                        </button>
                    </div>
                </header>

                <main className="grid grid-cols-1 lg:grid-cols-3 gap-6">
                    <div className="lg:col-span-2 space-y-4">
                        <div className="bg-white p-1 rounded-xl shadow-sm border border-slate-200">
                            {currentFrame ? (
                                <VisualizerCanvas 
                                    frame={currentFrame} 
                                    width={580} 
                                    height={300} 
                                />
                            ) : (
                                <div className="h-[300px] flex items-center justify-center text-slate-400">Loading...</div>
                            )}
                        </div>
                        <ControlPanel 
                            isPlaying={isPlaying}
                            onPlayPause={handlePlayPause}
                            onStepForward={() => setCurrentFrameIndex(i => Math.min(i + 1, (log?.frames.length || 1) - 1))}
                            onStepBack={() => setCurrentFrameIndex(i => Math.max(0, i - 1))}
                            onReset={() => { setIsPlaying(false); setCurrentFrameIndex(0); }}
                            speed={speed}
                            onSpeedChange={setSpeed}
                            progress={currentFrameIndex}
                            totalFrames={log?.frames.length || 0}
                            onSeek={setCurrentFrameIndex}
                        />
                    </div>

                    <div className="space-y-4">
                        <div className="bg-white p-6 rounded-xl shadow-sm border border-slate-200">
                            <h2 className="text-lg font-semibold mb-4 text-slate-700">Metrics</h2>
                            <div className="space-y-3">
                                <div className="flex justify-between">
                                    <span className="text-slate-500">Comparisons</span>
                                    <span className="font-mono font-medium">{currentFrame?.cumulative_comparisons || 0}</span>
                                </div>
                                <div className="flex justify-between">
                                    <span className="text-slate-500">Swaps</span>
                                    <span className="font-mono font-medium">{currentFrame?.cumulative_swaps || 0}</span>
                                </div>
                                <div className="pt-3 border-t border-slate-100">
                                    <div className="flex justify-between">
                                        <span className="text-slate-500">Algorithm</span>
                                        <span className="font-medium capitalize">{log?.metadata.algorithm || '-'}</span>
                                    </div>
                                    <div className="flex justify-between">
                                        <span className="text-slate-500">Size</span>
                                        <span className="font-medium">{log?.metadata.input_size || '-'}</span>
                                    </div>
                                    <div className="flex justify-between mt-2 pt-2 border-t border-slate-100 text-xs text-slate-600">
                                        <span>Time Complexity</span>
                                        <span className="font-mono">{log?.metadata.time_complexity || 'N/A'}</span>
                                    </div>
                                    <div className="flex justify-between text-xs text-slate-600">
                                        <span>Space Complexity</span>
                                        <span className="font-mono">{log?.metadata.space_complexity || 'N/A'}</span>
                                    </div>
                                </div>
                            </div>
                        </div>
                        
                        <div className="bg-indigo-50 p-4 rounded-xl border border-indigo-100">
                            <h3 className="text-sm font-semibold text-indigo-900 mb-2">Current Step</h3>
                            <p className="text-sm text-indigo-700">
                                {currentFrame?.operation === 'compare' && `Comparing indices ${currentFrame.highlights.compare?.join(' & ')}`}
                                {currentFrame?.operation === 'swap' && `Swapping indices ${currentFrame.highlights.swap?.join(' & ')}`}
                                {currentFrame?.operation === 'none' && 'Ready'}
                            </p>
                        </div>
                    </div>
                </main>
            </div>
        </div>
    );
};

export default App;
