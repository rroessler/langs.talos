/// Vendor Modules
import clsx from 'clsx';
import * as React from 'react';
import { Heading } from '@fumadocs/base-ui/components/heading';

/// Website Modules
import { Product } from '@/website/product';
import { Portal } from '@/website/components';

/// Package Modules
import { Registry } from '../registry';

/** Crate Documentation Component. */
export interface Component extends Component.Props {}
export function Component({ name, children }: Component) {
    // attempt resolving the current manifest
    const manifest = Registry.resolve(name);
    if (typeof manifest === 'undefined') return;

    // and return the resulting documentation
    return (
        <React.Fragment>
            <Heading as="h2" id="overview" children="Overview" />
            {children ?? <p>Unimplemented...</p>}
            <Heading as="h2" id="exports" children="Exports" />
            <p>Unimplemented...</p>
        </React.Fragment>
    );
}

export interface Overview extends Omit<React.ComponentProps<'div'>, 'children'> {}
export function Overview({ className, ...props }: Overview) {
    // prepare all the available portals to be show now
    const portals = Registry.list().map(({ name, describe }) => {
        const base = name.slice(Product.identifier.length + 2); // ensure we get the base-name now to be used
        return <Portal key={name} name={`talos:${base}`} href={`/docs/crates/${base}`} description={describe} />;
    });

    // revise the incoming class-name to be used
    className = clsx(className, 'mt-8 grid grid-cols-1 gap-4 text-start md:grid-cols-2 w-full');

    // and construct the resulting output
    return <div {...props} className={className} children={portals} />;
}

export namespace Component {
    //  TYPEDEFS  //

    /** Documentation Component Properties. */
    export type Props = React.PropsWithChildren<{ readonly name: string }>;
}
