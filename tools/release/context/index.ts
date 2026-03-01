/// Node Modules
import * as assert from 'node:assert';

/// Vendor Modules
import { Spinner } from '@topcli/spinner';
import { Octokit } from '@octokit/rest';
import git, { SimpleGit } from 'simple-git';

/// Tool Modules
import { Inversify } from '~/tools/vendors';

/// Package Modules
import { Task } from '../task';
import { Branch, Product } from '../product';

/** Available Contextual Options. */
const TOKEN_CONTEXT_OPTIONS = Symbol(`${Product.version}/context.options`);

/** Release Context Given. */
@Inversify.injectable()
export class Context implements Context.Readonly {
    //  INJECTABLES  //

    /** Contextual options. */
    @Inversify.inject(TOKEN_CONTEXT_OPTIONS) protected readonly m_options!: Context.Options;

    //  PROPERTIES  //

    /** Helper for executing git-based requests. */
    readonly git = git();

    /** Constructs an integration kit. */
    readonly octo = new Octokit({ auth: process.env.GITHUB_TOKEN });

    /** Prepare the base spinner instance. */
    readonly spinner = new Spinner();

    /** Prepare our assertion instance to be used. */
    readonly assert = assert;

    /** Buffer standard outputs. */
    readonly stdout = new Context.Buffered();

    /** Denotes if currently mocking this release-script. */
    readonly mock = Product.development;

    /** Current task scoping. */
    private m_scope?: Task.Scope;

    /** Prepare a current timestamp. */
    private readonly m_timestamp = (() => {
        const now = new Date(); // prepare the incoming date to be built
        const padded = (input: number) => input.toString().padStart(2, '0');

        // prepare the components to be added
        const year = now.getUTCFullYear();
        const month = padded(now.getUTCMonth() + 1);
        const day = padded(now.getUTCDate());
        const hours = padded(now.getUTCHours());
        const minutes = padded(now.getUTCMinutes());
        const seconds = padded(now.getUTCSeconds());

        // return the resulting date processed
        return `${year}${month}${day}${hours}${minutes}${seconds}`;
    })();

    /** Currently cached version value. */
    private m_version?: Context.Version;

    //  GETTERS x SETTERS  //

    /** Gets the stable branch flag. */
    get stable() {
        return this.branch === 'stable';
    }

    /** Gets the context branch. */
    get branch() {
        return this.m_options.branch ?? 'nightly';
    }

    /** Gets the underlying revision hash. */
    get revision() {
        return this.git.revparse(['--short', 'HEAD']);
    }

    /** Gets the available context versions. */
    get version(): Context.Version {
        // return the base cached value if necessary
        if (typeof this.m_version === 'object') return this.m_version;

        const branch = this.branch; // cache the branch now
        const base = this.m_options.version ?? Product.version;
        const release = `${base}-${branch}`; // prepare base release
        const semantic = this.stable ? base : release;
        const build = `${release}+${this.m_timestamp}`;
        const tag = `v${this.stable ? release : build}`;

        // cache the outgoing version to be used now
        return (this.m_version = { tag, base, build, release, semantic });
    }

    //  LIFECYCLE METHODS  //

    /**
     * Handles launching the release instance.
     * @param steps                 Plugin factory steps.
     */
    async launch(...steps: Task.Factory[]) {
        // attempt executing all of our incoming steps now
        for (const factory of steps) await this.m_step(new factory());

        // finally declare a suitable result success when completed
        this.spinner.succeed(`Finished ${Product.shortName} Release: ${this.version.tag}`);

        // show our final statistics and details now
        console.log(`    Revision  - ${await this.revision}`);
        console.log(`    Version   - v${this.version.release}`);
        console.log(`    Timestamp - ${this.m_timestamp}`);
    }

    /**
     * Handles chaining incoming callbacks.
     * @param callbacks             Callbacks to chain.
     */
    async chain<T extends (...args: any) => any>(callbacks: T[], ...args: Parameters<T>): Promise<void> {
        for (const callback of callbacks) await callback(...args);
    }

    //  PRIVATE METHODS  //

    /**
     * Handles executing an incoming task.
     * @param plugin                Plugin instance.
     */
    private async m_step(plugin: Task) {
        const actions = plugin.skip(this) ? [] : Task.Action; // prepare items
        for (const action of actions) await this.m_attempt(plugin, action);
    }

    /**
     * Handles a plugin action.
     * @param plugin                Plugin instance.
     * @param action                Action to attempt.
     */
    private async m_attempt(plugin: Task, action: keyof Task) {
        // prepare the underlying callback instance
        const callback = plugin[action];

        // ignore if the callback does not exist
        if (typeof callback === 'undefined') return;

        // prepare the current scoping to be executed now
        this.m_scope = { plugin: plugin.constructor.name, action };

        // attempt executing the callback now
        await Promise.resolve(callback.bind(plugin)(this)).catch(this.m_failure.bind(this));
    }

    /**
     * Handles chained failures.
     * @param error                 Error that occurred.
     */
    private m_failure(error?: any) {
        // pull out the current details for failure
        const { plugin = '<unknown>', action } = this.m_scope ?? {};

        // prepare the error message to be used now
        const message = error instanceof Error ? error.message : 'An unknown error occurred';

        // show the current failure details now for the spinner
        this.spinner.failed(`Plugin.${action ?? 'unknown'} '${plugin}' failed: ${message}`);

        // always attempt dumping the buffered outputs
        this.stdout.dump();

        // and rethrow the incoming error for an immediate exit
        throw typeof error === 'undefined' ? new Error(message) : error;
    }
}

export namespace Context {
    //  TYPEDEFS  //

    /** Available version components. */
    export interface Version {
        readonly base: string; // 0.0.0
        readonly release: string; // 0.0.0-branch
        readonly semantic: string; // 0.0.0-branch or 0.0.0
        readonly tag: string; // v$release or v$build
        readonly build: string; // 0.0.0-branch+timestamp
    }

    /** Handles an execution chain. */
    export interface Chain {
        <T extends (...args: any[]) => any>(callbacks: T[], ...args: Parameters<T>): Promise<void>;
    }

    /** Contains Output Buffering. */
    export class Buffered {
        //  PROPERTIES  //

        /** Currently buffered stdio details. */
        private m_buffers: ReadonlyArray<Buffer> = [];

        //  PUBLIC METHODS  //

        /** Handles dumping the outputs. */
        dump() {
            process.stdout.write('\n'); // pre-write a newline for brevity
            for (const buffer of this.m_buffers) process.stderr.write(buffer);
            if (this.m_buffers.length) process.stdout.write('\n');
        }

        /** Updates with an empty output. */
        clear() {
            this.update([]);
        }

        /**
         * Updates the current buffered outputs.
         * @param buffers           Outputs to bind.
         */
        update(buffers: ReadonlyArray<Buffer>) {
            this.m_buffers = buffers;
        }
    }

    /** Readonly Context Instance. */
    export interface Readonly {
        readonly chain: Chain;
        readonly git: SimpleGit;
        readonly octo: Octokit;
        readonly spinner: Spinner;
        readonly stdout: Buffered;
        readonly assert: typeof assert;

        readonly mock: boolean;
        readonly stable: boolean;
        readonly branch: Branch;
        readonly version: Version;
        readonly revision: Promise<string>;
    }

    /** Available Context Options. */
    export const Options = TOKEN_CONTEXT_OPTIONS;
    export interface Options {
        readonly version?: string;
        readonly branch?: Branch;
    }
}
