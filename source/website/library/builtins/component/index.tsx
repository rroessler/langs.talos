/// Vendor Modules
import * as React from 'react';
import { Heading } from '@fumadocs/base-ui/components/heading';

/// Package Modules
import { Registry } from '../registry';

/** Builtins Documentation Component. */
export interface Component extends Component.Props {}
export function Component({ children, name }: Component) {
    // attempt resolving the required component
    const builtin = Registry.resolve(name);
    if (typeof builtin === 'undefined') return;

    // and return the resulting documentation
    return (
        <React.Fragment>
            <Heading as="h2" id="overview" children="Overview" />
            {children ?? <p>Unimplemented...</p>}
        </React.Fragment>
    );
}

export namespace Component {
    //  TYPEDEFS  //

    /** Documentation Component Properties. */
    export type Props = React.PropsWithChildren<{ readonly name: string }>;
}
