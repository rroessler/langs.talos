/** Exposing a custom MDX module importer. */
declare module '*.mdx' {
    declare const content: import('mdx/types').MDXContent;
    export default content; // expose the content now
}
