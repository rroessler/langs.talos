/// Vendor Modules
import * as React from 'react';
import * as shiki from 'shiki';
import * as runtime from 'react/jsx-runtime';
import * as hast from 'hast-util-to-jsx-runtime';

/// Package Modules
import { Grammar } from './grammar';

/** Highlighting Functionality. */
export namespace Highlight {
    //  TYPEDEFS  //

    export type Engine = 'js' | 'oniguruma';
    export type Root = import('hast').Root;
    export type Themes = shiki.CodeOptionsThemes;
    export type Options = Common & (Themes | Record<never, never>);
    export type Common = shiki.CodeOptionsMeta &
        Omit<shiki.CodeToHastOptionsCommon, 'lang' | 'theme'> & {
            lang?: string;
            engine?: Engine;
            components?: Partial<hast.Components>;
        };

    //  PROPERTIES  //

    /** Languages that we require. */
    const m_langs = Object.keys(shiki.bundledLanguages);

    /** Available themes for use. */
    const m_themes: Record<string, shiki.BundledTheme> = { light: 'github-light', dark: 'github-dark' };

    /** Currently cached higlighters. */
    const m_highlighters = new Map<string, Promise<shiki.Highlighter>>();

    //  PUBLIC METHODS  //

    /**
     * Handles rendering code.
     * @param code              Code to render.
     * @param options           Code options.
     */
    export const render = (code: string, options: Options = {}): Promise<React.ReactNode> =>
        m_highlight(code, options).then((root) => m_jsxify(root, { components: options.components }));

    /**
     * Handles resolving highlighters.
     * @param engine            Engine to bind.
     * @param options           Highlighter options.
     */
    export const resolve = async (
        engine: Engine,
        options: Omit<
            shiki.BundledHighlighterOptions<shiki.BundledLanguage, shiki.BundledTheme>,
            'engine' | 'langs' | 'themes'
        >,
    ) => {
        // prepare the higlighter creation handler
        const { createHighlighter } = await import('shiki');

        // if the higlighter exists, then resolve now
        const highlighter =
            m_highlighters.get(engine) ??
            createHighlighter({
                ...options,
                engine: m_engine(engine),
                themes: Object.values(m_themes),
                langs: [await Grammar(), ...m_langs],
            });

        // ensure we forcibly update the current highlighters available
        if (!m_highlighters.has(engine)) m_highlighters.set(engine, highlighter);

        // and finally resolve the higlighter instance
        return highlighter;
    };

    //  PRIVATE METHODS  //

    /**
     * Converts "hast" to "jsx".
     * @param root                  Root to convert.
     * @param options               Given options.
     */
    const m_jsxify = (root: Root, options: Partial<hast.Options> = {}) =>
        hast.toJsxRuntime(root, {
            jsx: runtime.jsx,
            jsxs: runtime.jsxs,
            development: false,
            Fragment: React.Fragment,
            ...options,
        });

    /**
     * Handles resolving shiki engines.
     * @param engine                Engine to inherit.
     */
    const m_engine = async (engine?: Engine) => {
        if (engine === 'js') return import('shiki/engine/javascript').then((res) => res.createJavaScriptRegexEngine());
        return import('shiki/engine/oniguruma').then((res) => res.createOnigurumaEngine(import('shiki/wasm')));
    };

    /**
     * Handles highlighting code.
     * @param code                  Code to highlight.
     * @param options               Highlight options.
     */
    const m_highlight = async (code: string, options: Options): Promise<Root> => {
        // prepare the baseline options to be handled now
        const { lang: original, components: _, engine = 'oniguruma', ...rest } = options;

        // alias the incoming language now
        const lang = original as shiki.CodeToHastOptionsCommon['lang'];

        // attempt resolving the desired higlighter now
        return resolve(engine, {}).then((instance) =>
            instance.codeToHast(code, {
                lang,
                themes: m_themes,
                defaultColor: false,
                ...rest,
            }),
        );
    };
}
