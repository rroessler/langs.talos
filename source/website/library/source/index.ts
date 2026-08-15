/// Vendor Modules
import { loader } from 'fumadocs-core/source';
import { toFumadocsSource } from 'fumadocs-mdx/runtime/server';
import { DocsCollectionEntry } from 'fumadocs-mdx/runtime/server';
import { lucideIconsPlugin } from 'fumadocs-core/source/plugins/lucide-icons';

/// Collections Modules
import * as Collections from '@/collections/server';

/// Website Modules
import { Crate } from '@/website/crate';
import { Builtins } from '@/website/builtins';

/** Source Loaders Available. */
export namespace Source {
    //  PROPERTIES  //

    /** Available source plugins. */
    const m_plugins = [lucideIconsPlugin()];

    export const blog = loader(toFumadocsSource(Collections.blog, []), m_options('/blog'));
    export const proposals = loader(toFumadocsSource(Collections.proposals, []), m_options('/proposals'));

    export const builtins = m_rebuild('builtins', Collections.builtins);
    export const crates = m_rebuild('crates', Collections.crates);

    /** Documentation Loader. */
    export const docs = loader({ builtins, crates, docs: Collections.docs.toFumadocsSource() }, m_options('/'));

    //  PRIVATE METHODS  //

    /**
     * Constructs a set of suitable loader options.
     * @param baseUrl                   Base URL.
     */
    function m_options(baseUrl: string) {
        return { baseUrl, plugins: m_plugins } as const;
    }

    /**
     * Handles rebuilding the `toc` based on dynamic content.
     * @param baseDir                   Base directory.
     * @param entries                   Entries collection.
     */
    function m_rebuild<K extends string, S extends DocsCollectionEntry<K>>(baseDir: K, entries: S) {
        // prepare the source details to be used now
        const source = entries.toFumadocsSource({ baseDir });

        // transform our items as necessary
        if (baseDir === 'crates') Crate.Registry.transform(source);
        if (baseDir === 'builtins') Builtins.Registry.transform(source);

        // finally return the resolved source
        return source;
    }
}
