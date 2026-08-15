/// Website Modules
import { Source } from '@/website/source';
import { Product } from '@/website/product';
import { Portal } from '@/website/components';

/** Available blog metadata. */
export const metadata = { title: 'Blog', description: '' };

/** Constructs the indexed blog page. */
export default async function Blog() {
    // get a view of all the available pages
    const pages = Source.blog.getPages();

    // and sort the pages inplace with their associated dates
    pages.sort((a, b) => new Date(b.data.date).getTime() - new Date(a.data.date).getTime());

    // prepare all the incoming links now
    const links = pages.map((page) => (
        <Portal
            key={page.url}
            href={page.url}
            name={page.data.title}
            description={new Date(page.data.date).toDateString()}
        />
    ));

    // we want to show the releases and blog-posts seperately
    return (
        <div className="flex flex-col items-center justify-center flex-1">
            <h2 className="mt-0 mb-3 text-4xl">Blog Posts</h2>
            <h3 className="font-thin mb-8">Latest announcements about {Product.shortName}.</h3>
            <div className="grid grid-cols-1 gap-2 md:grid-cols-3 xl:grid-cols-4 w-full" children={links} />
        </div>
    );
}
