/// Vendor Modules
import type { Metadata } from 'next';
import { notFound } from 'next/navigation';
import { createRelativeLink } from 'fumadocs-ui/mdx';
import { InlineTOC } from 'fumadocs-ui/components/inline-toc';

/// Website Modules
import { Source } from '@/website/source';
import { Release } from '@/website/release';
import { Anchor } from '@/website/components';
import { Markdown } from '@/website/markdown';

//  PROPERTIES  //

/** Ensure no caching of documentation. */
export const revalidate = false;

/** Ensure the parameters are not dynamic. */
export const dynamicParams = false;

//  PUBLIC METHODS  //

/** Handles getting static parameters. */
export async function generateStaticParams() {
    return Source.blog.getPages().map((page) => ({ slug: page.slugs[0] }));
}

/** Handles getting available metadata. */
export async function generateMetadata(props: PageProps<'/blog/[slug]'>): Promise<Metadata> {
    return Source.blog.getPage(await props.params.then((params) => [params.slug]))?.data ?? notFound();
}

/** Constructs the documentation page component. */
export default async function Page(props: PageProps<'/blog/[slug]'>) {
    const page = Source.blog.getPage(await props.params.then((params) => [params.slug]));
    if (typeof page === 'undefined') notFound(); // ignore when we have invalid pages

    // construct the necessary components to be used
    const components = Markdown.Components({
        a: (props) => <Anchor component={createRelativeLink(Source.blog, page)} {...props} />,
    });

    // alias the incoming "MDX" content as necessary
    const { body: Content, toc, title, description, date, author } = page.data;

    // and finally construct the resulting blog-post
    return (
        <article className="flex flex-col mx-auto w-full px-4 py-8">
            <h1 className="text-3xl font-semibold mb-4">{title}</h1>
            {description && <p className="text-fd-muted-foreground mb-4">{description}</p>}

            <div className="flex flex-row text-sm mb-8">
                <span className="text-fd-muted-foreground" children="Written by&nbsp;" />
                <span className="font-medium me-auto" children={author} />

                <span className="text-fd-muted-foreground" children="@&nbsp;" />
                <span className="font-medium" children={new Date(date).toDateString()} />
            </div>

            <div className="prose min-w-0 flex-1">
                <InlineTOC className="mb-8" items={toc} />
                <Release.Forward page={page} />
                <Content components={components} />
            </div>
        </article>
    );
}
