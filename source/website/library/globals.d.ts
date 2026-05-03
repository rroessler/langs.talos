/** A CSS styling module. */
declare module '*.css' {}

/** A YAML module. */
declare module '*.yaml' {
    declare const content: string;
    export default content;
}

/** Exposing a custom MDX module importer. */
declare module '*.mdx' {
    declare const content: import('mdx/types').MDXContent;
    export default content; // expose the content now
}

/** The language module. */
declare module '~/dist/vscode/syntaxes/talos.tmLanguage.json' {
    declare const syntax: import('shiki').LanguageInput;
    export default syntax; // expose the syntax now
}
