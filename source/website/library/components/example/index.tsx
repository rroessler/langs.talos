/// Node Modules
import * as fs from 'node:fs';

/// Vendor Modules
import { SwordIcon } from 'lucide-react';

/// Library Modules
import { Assets } from '@/website/assets';

/// Package Modules
import { Code } from '../code';

/** Code Example Component. */
export interface Example extends Example.Props {}
export async function Example({ href, lang, ...props }: Example) {
    // ignore if the incoming reference is invalid
    if (typeof href === 'undefined') return null;

    // attempt resolving the incoming path to be used
    const example = await fs.promises.readFile(Assets.examples(href), 'utf-8');

    // render the incoming code now as necessary
    const rendered = <Code.Dynamic code={example.trim()} lang={lang} />;

    // resolve a suitable icon as necessary now
    const icon = lang === 'talos' ? <SwordIcon size="16" /> : undefined;

    // resolve a title as necessary now
    const title = href.includes('/') ? href : `examples/${href}`;

    // prepare the code-block to be shown now
    return <Code.Block icon={icon} title={title} {...props} children={rendered} />;
}

export namespace Example {
    //  TYPEDEFS  //

    /** Example Component Properties. */
    export type Props = Code & { href?: string; lang?: string };
}
