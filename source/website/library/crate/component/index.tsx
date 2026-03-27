/// Vendor Modules
import * as React from 'react';
import { Heading } from '@fumadocs/base-ui/components/heading';

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

export namespace Component {
    //  TYPEDEFS  //

    /** Documentation Component Properties. */
    export type Props = React.PropsWithChildren<{ readonly name: string }>;
}
