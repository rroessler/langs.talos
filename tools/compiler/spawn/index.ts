/// Node Modules
import * as cp from 'node:child_process';

/// Package Modules
import { Target, Worker } from '../target';

/** Handles constructing spawn-options. */
export function Spawn(options?: Spawn.Options): Spawn.Options {
    return options ?? {};
}

/** Handles Spawning Compilation Targets. */
export namespace Spawn {
    //  TYPEDEFS  //

    /** Spawn Interface Options. */
    export interface Options {
        stdio?: boolean;
        outdir?: string;
        abort?: AbortSignal;
    }

    //  PUBLIC METHODS  //

    /**
     * Handles spawning compilation targets.
     * @param target            Target to compile.
     * @param options           Spawn options.
     */
    export function target(target: Target, options?: Options): Worker;
    export function target(targets: Target[], options?: Options): Worker[];
    export function target(input: Target | Target[], options = {}): Worker | Worker[] {
        return Array.isArray(input) ? input.map((input) => cmake(input, options)) : cmake(input, options);
    }

    /**
     * Handles spawning "CMake" compilation targets.
     * @param target            Target to compile.
     * @param options           Spawn options.
     */
    export function cmake(target: Target, { abort, outdir, stdio }: Options = {}): Worker {
        // pull out the base command and arguments
        const [command, ...argv] = Target.script();

        // otherwise we have a singular target, so destructure into our desired arguments
        argv.push(target.system, target.arch, outdir ?? 'build');

        // attempt calling the shell script that runs the command
        const child = cp.spawn(command, argv, {
            shell: true, // want to run inside a shell
            signal: abort, // allow attaching a abort-signal
            stdio: stdio ? 'inherit' : 'pipe', // pipe output
        });

        // prepare the internal buffers for stdout/stderr
        const stdout: Buffer[] = [];

        // prepare the resulting promise to be used
        const start = function () {
            return new Promise<boolean>((resolve, reject) => {
                // pipe the outputs as necessary
                child.stdout?.on('data', (buffer) => stdout.push(buffer));
                child.stderr?.on('data', (buffer) => stdout.push(buffer));

                // handle normal rejections that may occur
                child.on('error', (error) => (abort?.aborted ? resolve(true) : reject(error)));

                // handle incoming exits that occur
                child.on('exit', (code, signal) => {
                    if (abort?.aborted) return resolve(true); // ignore if an abort signal occured
                    if (signal !== null) return reject(m_onError(target, `Terminated due to '${signal}'`));
                    if (code === null || code === 0) return resolve(false); // can safely resolve here as needed
                    return reject(m_onError(target, 'failed to cross-compile'));
                });
            });
        };

        // and return the final result to be contained
        return { target, stdout, start };
    }

    //  PRIVATE METHODS  //

    /**
     * Handles incoming errors.
     * @param target                Target that failed.
     * @param reason                The reason for failure.
     */
    function m_onError({ arch, system }: Target, reason: string) {
        return new Error(`Target '${system}-${arch}' ${reason}`);
    }
}
