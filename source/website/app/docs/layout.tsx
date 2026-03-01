/// Vendor Modules
import { PropsWithChildren } from 'react';
import { LinkItemType } from '@fumadocs/ui/link-item';
import { DocsLayout } from '@fumadocs/base-ui/layouts/notebook';

/// Library Modules
import { Source } from '@/website/source';
import { Options } from '@/website/options';
import { Release } from '@/website/release';

/** Constructs a docs-page layout. */
export default function Layout({ children }: PropsWithChildren) {
    // prepare the additional details
    const links: LinkItemType[] = [
        { text: 'Blog', url: '/blog' },
        { text: 'Latest', url: Release.Registry.latest() },
    ];

    // and construct the layout now
    return <DocsLayout tree={Source.docs.pageTree} {...Options({ links })} children={children} />;
}
