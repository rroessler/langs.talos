//  TYPEDEFS  //

/** Available Toolchain Architectures. */
export type Arch = (typeof Arch)[number];
export const Arch = ['x64', 'arm64'] as const;

/** Available Toolchain Systems. */
export type System = (typeof System)[number];
export const System = ['darwin', 'linux', 'windows'] as const;

export type Vendor = (typeof Vendor)[number];
export const Vendor = ['pc', 'apple', 'unknown'] as const;

/** Target Compilation Process. */
export interface Worker {
    readonly target: Target;
    readonly stdout: ReadonlyArray<Buffer>;
    readonly start: () => Promise<boolean>;
}

/** Target Triple Details. */
export interface Target {
    readonly arch: Arch;
    readonly system: System;
}

//  NAMESPACES  //

export namespace Target {
    //  PRIVATE METHODS  //

    /** Handles getting an appropriate alias. */
    const m_aliases: Record<System, NodeJS.Platform> = {
        darwin: 'darwin',
        linux: 'linux',
        windows: 'win32',
    };

    /** Handles getting an appropriate vendor. */
    const m_vendors: Record<System, Vendor> = {
        darwin: 'apple',
        windows: 'pc',
        linux: 'unknown',
    };

    /** Handles getting the available environments. */
    const m_environments: Record<System, string | undefined> = {
        darwin: undefined,
        windows: 'msvc',
        linux: 'gnueabi',
    };

    /** All available targets. */
    const m_targets: Target[] = [
        // for darwin we should support x64/arm64
        { arch: 'x64', system: 'darwin' },
        { arch: 'arm64', system: 'darwin' },

        // for linux we should support x64/arm64
        { arch: 'x64', system: 'linux' },
        { arch: 'arm64', system: 'linux' },

        // for now we only support 64-bit windows
        { arch: 'x64', system: 'windows' },
    ];

    //  PUBLIC METHODS  //

    /** Gets the underlying cross-complation script. */
    export const script = () => {
        const extension = process.platform === 'win32' ? '.ps1' : '.sh';
        const filePath = require.resolve(`~/scripts/compile/target${extension}`);

        if (process.platform !== 'win32') return ['sh', filePath]; // unix-like are easier
        return ['powershell.exe', '-NoProfile', '-ExecutionPolicy', 'ByPass', '-File', filePath];
    };

    /** Gets all cross-compilable targets. */
    export const available = (): Target[] => m_targets.slice();

    /** Handles getting all native targets. */
    export const native = () =>
        available().filter((target) => {
            const valid = process.platform === platform(target);
            if (process.platform === 'darwin') return valid;
            return valid && process.arch === target.arch;
        });

    /**
     * Gets the associate vendor details.
     * @param target            Target to resolve.
     */
    export const vendor = (target: Target): Vendor => m_vendors[target.system];

    /**
     * Gets the associate environment details.
     * @param target            Target to resolve.
     */
    export const environment = (target: Target): string | undefined => m_environments[target.system];

    /**
     * Gets the underlying platform name.
     * @param target            Target to resolve.
     */
    export const platform = (target: Target): NodeJS.Platform => m_aliases[target.system];

    /**
     * Constructs a target-triple.
     * @param target            Target to resolve.
     */
    export const triple = (target: Target): string => {
        const env = environment(target); // pre-calculate the environment here if necessary
        return `${target.arch}-${vendor(target)}-${target.system}}${env ? `-${env}` : ''}`;
    };
}
