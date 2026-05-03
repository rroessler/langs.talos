/** A CSS styling module. */
declare module '*.css' {}

/** A YAML module. */
declare module '*.yaml' {
    declare const content: string;
    export default content;
}

/** Exposing a custom MDX module importer. */
declare module '*.mdx' {
    export { MDXContent as default } from 'mdx/types';
}

/** The language module. */
declare module '~/dist/vscode/syntaxes/talos.tmLanguage.json' {
    declare const syntax: import('shiki').LanguageInput;
    export default syntax; // expose the syntax now
}
