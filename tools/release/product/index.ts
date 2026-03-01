/// Node Modules
import * as fs from 'node:fs';

/** Gets the underlying branch details. */
export type Branch = ReturnType<typeof Branch.keys>[number];
export namespace Branch {
    //  PROPERTIES  //

    /** The underlying branch keys. */
    const m_keys = ['stable', 'nightly'] as const;

    //  PUBLIC METHODS  //

    /** Gets the available branch keys. */
    export const keys = () => m_keys;

    /** Gets a suitable either mapping. */
    export const either = () => m_keys.map((key) => `'${key}'`).join(' or ');

    /** Validates an incoming string as a branch. */
    export function validate(input: string): input is Branch;
    export function validate(input?: string): input is Branch | undefined;
    export function validate(input?: string): input is Branch | undefined {
        if (typeof input === 'undefined') return true;
        if (keys().includes(input as any)) return true;
        return (failure(input), false); // otherwise fail
    }

    /**
     * Checks if we have a valid release branch.
     * @param branch            Branch to check
     */
    export const release = (branch: any): branch is string => ['main', 'nightly'].includes(branch);

    /**
     * Handles showing branch failures.
     * @param branch            Invalid branch.
     */
    export function failure(branch?: string): never {
        throw new Error(`Expected a valid release branch, either ${Branch.either()}, received '${branch}'`);
    }
}

/** Product Details. */
export namespace Product {
    //  PROPERTIES  //

    /** Handles parsing the underlying package. */
    const m_package: any = JSON.parse(fs.readFileSync(require.resolve('~/package.json'), 'utf-8'));

    /** Get the underlying version details. */
    const m_version = m_package.version.split('-');

    /** The underlying identifier to be used. */
    export const identifier = m_package.publisher;

    /** GitHub Owner Username. */
    export const owner = 'rroessler';

    /** The repository name. */
    export const repo = 'langs.talos';

    /** Gets the incoming version details. */
    export const version = m_version[0];

    /** Checks if currently in development. */
    export const development = process.env.NODE_ENV === 'development';

    /** Gets the immediate branch details. */
    export const branch: Branch = m_version[1] ?? 'stable';

    /** Short descriptor name. */
    export const shortName = identifier[0].toUpperCase() + identifier.slice(1);
}
