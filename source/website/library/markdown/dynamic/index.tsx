/// Vendor Modules
import Markdown from 'react-markdown';

/** Handles embedding dynamic markdown. */
export interface Dynamic extends Dynamic.Props {}
export function Dynamic({ markdown }: Dynamic) {
    return <Markdown children={markdown} />;
}

export namespace Dynamic {
    //  TYPEDEFS  //

    /** Embedded Component Properties. */
    export interface Props {
        readonly markdown?: string;
    }
}
