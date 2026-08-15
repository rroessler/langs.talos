/// Node Modules
import * as path from 'node:path';

/** Tools Assets. */
export type Assets = typeof path.resolve;
export namespace Assets {
    //  PROPERTIES  //

    const m_root = path.resolve(__dirname, '..', '..');
    const m_icons = path.resolve(m_root, 'icons');
    const m_configs = path.resolve(m_root, 'configs');
    const m_syntaxes = path.resolve(m_root, 'syntaxes');
    const m_examples = path.resolve(m_root, 'examples');
    const m_vscode = path.resolve(m_root, 'dist', 'vscode');
    const m_crates = path.resolve(m_root, 'source', 'crates');

    //  PUBLIC METHODS  //

    /** The underlying root directory. */
    export const root = m_bind(m_root);

    /** The "vscode" output directory. */
    export const vscode = m_bind(m_vscode);

    /** The underlying icons directory. */
    export const icons = m_bind(m_icons);

    /** The underlying configurations directory. */
    export const configs = m_bind(m_configs);

    /** The available language configuration. */
    export const syntaxes = m_bind(m_syntaxes);

    /** The available examples directory. */
    export const examples = m_bind(m_examples);

    /** The available crates directory. */
    export const crates = m_bind(m_crates);

    /** Handles base resolution of paths. */
    export const resolve = path.resolve;

    //  PRIVATE METHODS  //

    /**
     * Handles binding asset resolvers.
     * @param base              Base path.
     */
    function m_bind(base: string | Assets): Assets {
        if (typeof base === 'function') return base; // should be a normal passthrough
        return (...segments) => (segments.length ? path.resolve(base, ...segments) : base);
    }
}
