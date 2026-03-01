/** Crate Manifest Details. */
export interface Manifest {
    readonly name: string;
    readonly version: string;
    readonly describe?: string;
    readonly resource: string;

    /** Handles resolving crate paths. */
    resolve(...segments: string[]): string;
}
