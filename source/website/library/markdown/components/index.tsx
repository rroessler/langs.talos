/// Vendor Modules
import fumadocs from '@fumadocs/base-ui/mdx';
import { MDXComponents } from 'mdx/types';

/// Website Modules
import { Anchor, Callout, Code } from '@/website/components';

/** Gets the defaulted list of components. */
export function Components(components?: MDXComponents): MDXComponents {
    // prepare the builting components now
    const builtins: MDXComponents = {
        a: Anchor,
        pre: Code.Native,
        blockquote: Callout as any,
    };

    // and merge all the outgoing components now
    return { ...fumadocs, ...builtins, ...components };
}
