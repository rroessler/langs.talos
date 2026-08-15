/// Vendor Modules
import type { Metadata } from 'next';
import { notFound } from 'next/navigation';
import { Page } from 'fumadocs-core/source';
import { createRelativeLink } from 'fumadocs-ui/mdx';
import { DocsBody, DocsDescription, DocsPage, DocsTitle } from 'fumadocs-ui/layouts/notebook/page';

/// Website Modules
import { Crate } from '@/website/crate';
import { Source } from '@/website/source';
import { Builtins } from '@/website/builtins';
import { Markdown } from '@/website/markdown';
import { Anchor } from '@/website/components';

//  PROPERTIES  //

/** Ensure no caching of documentation. */
export const revalidate = false;

/** Ensure the parameters are not dynamic. */
export const dynamicParams = false;

//  PUBLIC METHODS  //

/** Handles getting static parameters. */
export async function generateStaticParams() {
    return Source.docs.generateParams();
}

/** Handles getting available metadata. */
export async function generateMetadata(props: PageProps<'/[...slug]'>): Promise<Metadata> {
    const slug = await props.params.then((params) => params.slug);
    const page = Source.docs.getPage(slug); // get the page instance
    const base = slug[0][0].toUpperCase() + slug[0].slice(1);
    const title = page ? `${base} | ${page.data.title}` : undefined;
    return page ? { title, description: m_describe(page) } : notFound();
}

/** Documentation Page Component. */
export default async function Docs(props: PageProps<'/[...slug]'>) {
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
    const description = <DocsDescription key="description" className="mb-2" children={m_describe(page)} />;
    const actions = <div key="actions" className="border-b" />;

    // and finally construct the resulting page
    return <DocsPage toc={toc} tableOfContent={{ style: 'clerk' }} children={[title, description, actions, body]} />;
}

//  PRIVATE METHODS  //

/**
 * Handles describing pages.
 * @param page                  Page to describe.
 */
function m_describe(page?: Page): string | undefined {
    // ignore if there is no valid page at all
    if (typeof page === 'undefined') return;

    // get the current page title being used
    const title = page.data.title;
    const description = page.data.description;

    // ignore if there is no valid title being used
    if (typeof title === 'undefined') return description;

    // handle based on the starting part of the path
    if (page.path.startsWith('crates')) return Crate.Registry.resolve(title)?.describe ?? description;
    if (page.path.startsWith('builtins')) return Builtins.Registry.resolve(title)?.describe ?? description;

    // otherwise resolve a baseline description
    return description;
}
