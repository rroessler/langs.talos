/// Vendor Modules
import * as React from 'react';
import { Heading } from '@fumadocs/base-ui/components/heading';

/** Builtins Documentation Component. */
export interface Component extends Component.Props {}
export function Component({ children }: Component) {
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
