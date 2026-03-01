/// Vendor Modules
import * as collections from 'fumadocs-mdx:collections/server';
import { loader, multiple } from 'fumadocs-core/source';
import { toFumadocsSource } from 'fumadocs-mdx/runtime/server';
import { lucideIconsPlugin } from 'fumadocs-core/source/lucide-icons';

/** Gets the avialable source details. */
export namespace Source {
    //  PROPERTIES  //

    /** The documentation collection. */
    export const docs = (() => {
        // prepare all the incoming keys to be used for metadata
        const keys = new Set<string>();

        // convert the incoming crates path to be valid
        const crates = collections.crates.toFumadocsSource();

        // prepare the common set of TOC items to be used
        const toc = ['Overview', 'Exports'].map((title) => ({ title, url: `#${title.toLowerCase()}`, depth: 2 }));

        // iteratively update our items as necessary now
        for (const file of crates.files) {
            file.data.info.path = file.path = `crates/${file.path}`; // prepare here
            if (file.type === 'meta' || file.path === 'crates/index.mdx') continue;
            (keys.add(file.path.split('/')[1]), (file.data.toc = toc)); // update
        }

        // iteratively construct "meta" files as well
        for (const key of keys) {
            const path = `crates/${key}/meta.json`;
            const info = { path, fullPath: 'dummy.json' }; // we use a dummy to force
            crates.files.push({ type: 'meta', path, data: { info, collapsible: false } });
        }

        // prepare the incoming sources to be used
        const sources = multiple({ docs: collections.docs.toFumadocsSource(), crates });

        // construct the resulting loader to be used now
        return loader(sources, { baseUrl: '/docs', plugins: [lucideIconsPlugin()] });
    })();

    /** The blogs collection. */
    export const blog = (() => {
        const sources = multiple({ blogs: toFumadocsSource(collections.blog, []) });
        return loader(sources, { baseUrl: '/blog', plugins: [lucideIconsPlugin()] });
    })();
}
