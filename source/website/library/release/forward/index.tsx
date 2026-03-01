/// Package Modules
import { Details, Registry } from '../registry';

/// Markdown Modules
import Content from './content.mdx';

/** Preview Component. */
export interface Forward extends Forward.Props {}
export function Forward({ page }: Forward) {
    return Registry.validate(page) ? <Content /> : null;
}

export namespace Forward {
    //  TYPEDEFS  //

    /** Preview Component Properties. */
    export interface Props {
        readonly page: Details;
    }
}
