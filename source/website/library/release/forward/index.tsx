/// Package Modules
import { Details, Registry } from '../registry';

/// Markdown Modules
import Snippet from './_snippet.mdx';

/** Preview Component. */
export interface Forward extends Forward.Props {}
export function Forward({ page }: Forward) {
    return Registry.validate(page) ? <Snippet /> : null;
}

export namespace Forward {
    //  TYPEDEFS  //

    /** Preview Component Properties. */
    export interface Props {
        readonly page: Details;
    }
}
