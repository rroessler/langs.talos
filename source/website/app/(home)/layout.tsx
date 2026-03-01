/// Vendor Modules
import { Metadata } from 'next';
import { PropsWithChildren } from 'react';
import { HomeLayout } from '@fumadocs/base-ui/layouts/home';

/// Library Modules
import { Options } from '@/website/options';
import { Product } from '@/website/product';
import { LinkItemType } from '@fumadocs/ui/link-item';

/** Common item metadata. */
export const metadata: Metadata = {
    description: Product.description,
    title: {
        absolute: `Home | ${Product.shortName}`,
        template: `%s | ${Product.shortName}`,
    },
};

/** Constructs a home-page layout. */
export default function Layout({ children }: PropsWithChildren) {
    // prepare the links to be used
    const links: LinkItemType[] = [
        { text: 'Blog', url: '/blog' },
        { text: 'Docs', url: '/docs' },
        { text: 'Crates', url: '/docs/crates' },
    ];

    // prepare the main content
    const content = <div className="flex flex-col flex-1 w-screen max-w-[1100px] p-5" children={children} />;

    // and construct the home-layout now
    return <HomeLayout {...Options({ links })} children={content} />;
}
