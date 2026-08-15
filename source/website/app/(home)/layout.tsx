/// Vendor Modules
import { type Metadata } from 'next';
import { HomeLayout } from 'fumadocs-ui/layouts/home';
import { LinkItemType } from 'fumadocs-ui/layouts/shared';

/// Website Modules
import { Options } from '@/website/options';
import { Product } from '@/website/product';

/** Common item metadata. */
export const metadata: Metadata = {
    description: Product.description,
    title: {
        absolute: `Home | ${Product.shortName}`,
        template: `%s | ${Product.shortName}`,
    },
};

/** Documentation Layout Component. */
export default function Layout({ children }: React.PropsWithChildren) {
    // define some common home links to be used
    const links: LinkItemType[] = [
        { text: 'Blog', url: '/blog' },
        { text: 'Docs', url: '/language' },
        { text: 'Crates', url: '/crates' },
    ];

    // and construct the home layout to be shown
    return (
        <HomeLayout {...Options({ links })}>
            <div className="flex flex-col flex-1 w-screen max-w-[1100px] p-5" children={children} />
        </HomeLayout>
    );
}
