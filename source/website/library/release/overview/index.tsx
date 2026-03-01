/// Vendor Modules
import clsx from 'clsx';

/// Website Modules
import { Portal } from '@/website/components';

/// Package Modules
import { Registry } from '../registry';

/** Release Overview Component. */
export interface Overview extends Omit<React.ComponentProps<'div'>, 'children'> {}
export function Overview({ className, ...props }: Overview) {
    // prepare all the available portals to be show now
    const portals = Registry.list().map((page) => {
        const description = new Date(page.data.date).toDateString(); // prepare the date to be used now
        return <Portal key={page.url} name={page.data.title} href={page.url} description={description} />;
    });

    // revise the incoming class-name to be used
    className = clsx(className, 'mt-8 grid grid-cols-1 gap-4 text-start w-full');

    // and construct the resulting output
    return <div {...props} className={className} children={portals} />;
}
