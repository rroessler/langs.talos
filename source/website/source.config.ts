/// Vendor Modules
import { z } from 'zod';
import * as fumadocs from 'fumadocs-mdx/config';
import * as plugins from 'fumadocs-core/mdx-plugins';

/// Library Modules
import { Assets } from '@/website/assets';
import { Language } from '@/website/language';

// Prepare a baseline draft schema property
const g_draft = z.boolean().optional();

// Extend the baseline schemas to be used.
const g_metadata = fumadocs.metaSchema.extend({ draft: g_draft });
const g_frontmatter = fumadocs.frontmatterSchema.extend({ draft: g_draft });

// The available documentation cache.
export const docs = fumadocs.defineDocs({
    dir: Assets.documentation(),
    meta: { schema: g_metadata },
    docs: {
        schema: g_frontmatter,
        files: ['**/*.md', '**/*.mdx', '!internal'],
        postprocess: { includeProcessedMarkdown: true },
    },
});

// The available crates cache.
export const crates = fumadocs.defineDocs({
    dir: Assets.crates(),
    meta: { files: ['**/meta.json'], schema: g_metadata },
    docs: {
        files: ['**/*.mdx'],
        schema: g_frontmatter,
        postprocess: { includeProcessedMarkdown: true },
    },
});

// The available builtins cache.
export const builtins = fumadocs.defineDocs({
    dir: Assets.builtins(),
    meta: { files: ['**/meta.json'], schema: g_metadata },
    docs: {
        files: ['**/*.mdx'],
        schema: g_frontmatter,
        postprocess: { includeProcessedMarkdown: true },
    },
});

// The available blogs cache.
export const blog = fumadocs.defineCollections({
    type: 'doc',
    dir: Assets.blog(),
    schema: g_frontmatter.extend({
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
