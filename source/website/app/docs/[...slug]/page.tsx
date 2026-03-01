/// Vendor Modules
import type { Metadata } from 'next';
import { notFound } from 'next/navigation';
import { createRelativeLink } from '@fumadocs/base-ui/mdx';
import { DocsBody, DocsDescription, DocsPage, DocsTitle } from '@fumadocs/base-ui/layouts/notebook/page';

/// Library Modules
import { Crate } from '@/website/crate';
import { Source } from '@/website/source';
import { Product } from '@/website/product';
import { Anchor } from '@/website/components';
import { Markdown } from '@/website/markdown';

/** Ensure no caching of documentation. */
export const revalidate = false;

/** Ensure the parameters are not dynamic. */
export const dynamicParams = false;

/** Handles getting static parameters. */
export async function generateStaticParams() {
    return Source.docs.generateParams();
}

/** Handles getting available metadata. */
export async function generateMetadata(props: PageProps<'/docs/[...slug]'>): Promise<Metadata> {
    const page = Source.docs.getPage(await props.params.then((params) => params.slug));
    const title = page ? `${page.data.title} | ${Product.shortName}` : undefined;
    return page ? { title, description: Crate.Registry.describe(page) } : notFound();
}

/** Constructs the documentation page component. */
export default async function Page(props: PageProps<'/docs/[...slug]'>) {
    const page = Source.docs.getPage(await props.params.then((params) => params.slug));
    if (typeof page === 'undefined') notFound(); // ignore when we have invalid pages

    // alias the incoming "MDX" content as necessary
    const { body: Content, toc } = page.data;

    // construct the necessary components to be used
    const components = Markdown.Components({
        a: (props) => <Anchor component={createRelativeLink(Source.docs, page)} {...props} />,
    });

    // prepare each of our components to be used
    const title = <DocsTitle key="title" children={page.data.title} />;
    const body = <DocsBody key="body" children={<Content components={components} />} />;
    const description = <DocsDescription key="description" className="mb-2" children={Crate.Registry.describe(page)} />;
    const actions = <div key="actions" className="border-b" />;

    // and finally construct the resulting page
    return <DocsPage toc={toc} tableOfContent={{ style: 'clerk' }} children={[title, description, actions, body]} />;
}
