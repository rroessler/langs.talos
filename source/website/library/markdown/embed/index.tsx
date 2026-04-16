/// Vendor Modules
import Markdown from 'react-markdown';

/** Handles embedding dynamic markdown. */
export interface Embed extends Embed.Props {}
export function Embed({ markdown }: Embed) {
    return <Markdown children={markdown} />;
}

export namespace Embed {
    //  TYPEDEFS  //

    /** Embedded Component Properties. */
    export interface Props {
        readonly markdown?: string;
    }
}
