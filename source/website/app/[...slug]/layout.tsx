/// Vendor Modules
import { DocsLayout } from 'fumadocs-ui/layouts/notebook';
import { LinkItemType } from 'fumadocs-ui/layouts/shared';

/// Website Modules
import { Source } from '@/website/source';
import { Options } from '@/website/options';

/** Constructs a docs-page layout. */
export default async function Layout({ children }: React.PropsWithChildren) {
    // prepare the additional details
    const links: LinkItemType[] = [{ text: 'Blog', url: '/blog' }];

    // and construct the layout now
    return <DocsLayout tree={Source.docs.pageTree} {...Options({ links })} children={children} />;
}
