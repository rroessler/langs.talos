/// Vendor Modules
import * as React from 'react';

/// Library Modules
import { Product } from '@/website/product';

/** Handles formatting version-text. */
export interface Version extends Version.Props {}
export function Version({ branch }: Version) {
    // prepare the baseline version text now
    const version = <React.Fragment key="version">v{Product.version}</React.Fragment>;

    // prepare the branch to be used now
    const details = branch && Product.branch && <React.Fragment key="branch">-{Product.branch}</React.Fragment>;

    // and combine the outgoing version items now
    return <React.Fragment>{[version, details]}</React.Fragment>;
}

export namespace Version {
    //  TYPEDEFS  //

    /** Versioning Component Properties. */
    export type Props = { branch?: boolean };
}
