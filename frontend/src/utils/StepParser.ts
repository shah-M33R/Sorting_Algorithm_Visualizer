import { Log, Frame } from '../types';

export class StepParser {
    static parse(json: any): Log {
        if (!json.metadata || !json.frames) {
            throw new Error("Invalid log format: missing metadata or frames");
        }
        return json as Log;
    }
}
