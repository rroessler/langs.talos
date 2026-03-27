/// Node Modules
import * as path from 'node:path';

/** Contains Internal Asset Paths. */
export type Assets = typeof path.resolve;
export namespace Assets {
    //  PROPERTIES  //

    /** The project directory. */
    const m_project = process.cwd();

    /** The root directory. */
    const m_root = path.resolve(m_project, '..', '..');

    /** The scripts directory. */
    const m_scripts = path.resolve(m_root, 'scripts');

    /** The source directory. */
    const m_source = path.resolve(m_root, 'source');

    /** The crates directory. */
    const m_crates = path.resolve(m_source, 'crates');

    /** The builtins directory. */
    const m_builtins = path.resolve(m_source, 'talos', 'builtins');

    /** The examples directory. */
    const m_examples = path.resolve(m_root, 'examples');

    /** The syntaxes directory. */
    const m_syntaxes = path.resolve(m_root, 'syntaxes');

    /** The documentation directory. */
    const m_documentation = path.resolve(m_root, 'docs');

    /** The contents directory. */
    const m_content = path.resolve(m_project, 'content');

    /** The blog directory. */
    const m_blog = path.resolve(m_content, 'blog');

    /** The proposals directory. */
    const m_proposals = path.resolve(m_content, 'proposals');

    /** The language tour directory. */
    const m_tour = path.resolve(m_documentation, 'tour');

    //  PUBLIC METHODS  //

    /** The project directory. */
    export const project = m_bind(m_project);

    /** The underlying root directory. */
    export const root = m_bind(m_root);

    /** The underlying scripts director. */
    export const scripts = m_bind(m_scripts);

    /** The available language configuration. */
    export const syntaxes = m_bind(m_syntaxes);

    /** The documentation folder. */
    export const documentation = m_bind(m_documentation);

    /** The blogs folder. */
    export const blog = m_bind(m_blog);

    /** The proposals folder. */
    export const proposals = m_bind(m_proposals);

    /** The underlying examples path. */
    export const examples = m_bind(m_examples);

    /** The underlying crates path. */
    export const crates = m_bind(m_crates);

    /** The underlying builtins path. */
    export const builtins = m_bind(m_builtins);

    /** The underlying tour path. */
    export const tour = m_bind(m_tour);

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
