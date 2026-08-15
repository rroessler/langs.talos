/// Website Modules
import { cn } from '@/website/utilities';
import { Portal } from '@/website/components';

/// Package Modules
import { Registry } from '../registry';

/** Crate Overview Component. */
export interface Overview extends Omit<React.ComponentProps<'div'>, 'children'> {}
export function Overview({ className, ...props }: Overview) {
    // prepare all the available portals to be show now
    const portals = Registry.list().map(({ name, describe }) => {
        const href = `/builtins/${name.toLowerCase()}`; // get the location now
        return <Portal key={name} name={name} href={href} description={describe} />;
    });

    // revise the incoming class-name to be used
    className = cn(className, 'mt-8 grid grid-cols-1 gap-4 text-start md:grid-cols-2 w-full');

    // and construct the resulting output
    return <div {...props} className={className} children={portals} />;
}
