/// Tool Modules
import { Inversify } from '~/tools/vendors';

/// Package Modules
import type { Context } from '../context';

/** Abstract Task for Releases. */
export abstract class Task {
    //  PUBLIC METHODS  //

    /** Denotes whether to skip this task. */
    skip(_: Context.Readonly) {
        return false;
    }

    /** Handles setting up the task. */
    setup?(context: Context.Readonly): void | Promise<void>;

    /** Potential Release Executor. */
    execute?(context: Context.Readonly): void | Promise<void>;

    /** Handles tearing down the task. */
    teardown?(context: Context.Readonly): void | Promise<void>;
}

export namespace Task {
    //  TYPEDEFS  //

    /** Factory Typing for Tasks. */
    export type Factory = Inversify.Newable<Task, ConstructorParameters<typeof Task>>;

    /** Current Task Details. */
    export interface Scope {
        readonly plugin: string;
        readonly action: Action;
    }

    /** All available actions. */
    export type Action = keyof Task;
    export const Action: Action[] = ['setup', 'execute', 'teardown'];
}
