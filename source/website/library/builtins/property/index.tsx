/// Vendor Modules
import * as React from 'react';
import { Heading } from '@fumadocs/base-ui/components/heading';

/// Website Modules
import { Markdown } from '@/website/markdown';
import { Anchor, Code } from '@/website/components';

/** Code Snippet Component. */
export type Snippet = { code: string };
export function Snippet({ code }: Snippet) {
    if (typeof code === 'undefined') return; // ignore
    const rendered = <Code.Dynamic lang="talos" code={code} />;
    return <Code.Block children={rendered} />;
}

/** Builtins Property Component. */
export interface Property extends Property.Props {}
export function Property({ name, parent, typedef, describe, ancillary }: Property) {
    // prepare the href to be used now
    const href = `#${parent ? `${parent}-` : ''}${name}`;

    // prepare the top-most link to be used
    const title = <Anchor href={href} children={<code>.{name}</code>} />;

    // construct the resulting fragments to be used now
    return (
        <div className="mb-4">
            <Heading as="h3" children={title} />
            {typedef && <Snippet code={typedef} />}
            <Markdown.Embed markdown={describe} />
            {ancillary /** additional details */}
        </div>
    );
}

export namespace Property {
    //  TYPEDEFS  //

    /** Property Component Properties. */
    export interface Props {
        readonly name: string;
        readonly parent?: string;
        readonly typedef?: string;
        readonly describe?: string;
        readonly ancillary?: React.ReactNode;
    }
}
