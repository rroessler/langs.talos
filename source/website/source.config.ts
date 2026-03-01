/// Vendor Modules
import { z } from 'zod';
import * as fumadocs from 'fumadocs-mdx/config';
import * as plugins from 'fumadocs-core/mdx-plugins';

/// Library Modules
import { Assets } from '@/website/assets';
import { Language } from '@/website/language';

// The available documentation cache.
export const docs = fumadocs.defineDocs({
    dir: Assets.documentation(),
    meta: { schema: fumadocs.metaSchema },
    docs: {
        schema: fumadocs.frontmatterSchema,
        postprocess: { includeProcessedMarkdown: true },
    },
});

// The available crates cache.
export const crates = fumadocs.defineDocs({
    dir: Assets.crates(),
    meta: { schema: fumadocs.metaSchema },
    docs: {
        files: ['**/*.mdx'],
        schema: fumadocs.frontmatterSchema,
        postprocess: { includeProcessedMarkdown: true },
    },
});

// The available blogs cache.
export const blog = fumadocs.defineCollections({
    type: 'doc',
    dir: Assets.blog(),
    schema: fumadocs.frontmatterSchema.extend({
        author: z.string(),
        date: z.iso.date().or(z.date()),
    }),
});

// Fumadocs Configuration.
export default fumadocs.defineConfig({
    mdxOptions: {
        providerImportSource: '@/website/markdown/_bootstrap',
        rehypeCodeOptions: { langs: [await Language.Grammar()] } as plugins.RehypeCodeOptions,
    },
});
