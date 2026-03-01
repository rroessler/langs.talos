/** A CSS styling module. */
declare module '*.css' {}

/** A YAML module. */
declare module '*.yaml' {
    declare const content: string;
    export default content;
}

/** The language module. */
declare module '~/dist/vscode/syntaxes/talos.tmLanguage.json' {
    declare const syntax: import('shiki').LanguageInput;
    export default syntax; // expose the syntax now
}
