/// Vendor Modules
import { loader, multiple } from 'fumadocs-core/source';
import { toFumadocsSource } from 'fumadocs-mdx/runtime/server';
import { lucideIconsPlugin } from 'fumadocs-core/source/lucide-icons';

/// Collections Modules
import * as collections from 'fumadocs-mdx:collections/server';

/// Website Modules
import { Product } from '@/website/product';

/** Gets the avialable source details. */
export namespace Source {
    //  PROPERTIES  //

    /** The documentation collection. */
    export const docs = (() => {
        // convert the incoming crates and buitings path to be valid
        const crates = m_rebuild('crates', collections.crates.toFumadocsSource(), 'Overview', 'Exports');
        const builtins = m_rebuild('builtins', collections.builtins.toFumadocsSource(), 'Overview');

        // prepare the incoming sources to be used
        const sources = multiple({ docs: m_filter(collections.docs.toFumadocsSource()), builtins, crates });

        // construct the resulting loader to be used now
        return loader(sources, { baseUrl: '/docs', plugins: [lucideIconsPlugin()] });
    })();

    /** The blogs collection. */
    export const blog = (() => {
        const sources = multiple({ blogs: m_filter(toFumadocsSource(collections.blog, [])) });
        return loader(sources, { baseUrl: '/blog', plugins: [lucideIconsPlugin()] });
    })();

    //  PRIVATE METHODS  //

    /**
     * Handles filtering source collections.
     * @param items                     Items to filter.
     */
    function m_filter<T extends import('fumadocs-core/source').Source<any>>(source: T): T {
        if (Product.development) return source; // ignore when running in development mode at all
        return ((source.files = source.files.filter((file) => file.data.draft !== true)), source);
    }

    /**
     * Handles rebuilding sources contents.
     * @param source            Source to rebuild.
     * @param prefix            Prefix to bind.
     * @param sections          Sections to bind.
     */
    function m_rebuild<T extends import('fumadocs-core/source').Source<any>>(
        prefix: string,
        source: T,
        ...sections: string[]
    ): T {
        // prepare all the incoming keys to be used for metadata
        const keys = new Set<string>();
        const index = `${prefix}/index.mdx`;

        // prepare the common set of TOC items to be used
        const toc = sections.map((title) => ({ title, url: `#${title.toLowerCase()}`, depth: 2 }));

        // iteratively update our items as necessary now
        for (const file of source.files) {
            file.data.info.path = file.path = `${prefix}/${file.path}`;
            if (file.type === 'meta' || file.path === index) continue;
            (keys.add(file.path.split('/')[1]), (file.data.toc = toc));
        }

        // iteratively construct "meta" files as well
        for (const key of keys) {
            const path = `${prefix}/${key}/meta.json`;
            const info = { path, fullPath: 'dummy.json' }; // we use a dummy to force
            source.files.push({ type: 'meta', path, data: { info, collapsible: false } });
        }

        // resolve the resulting source now
        return source;
    }
}
