/// Vendor Modules
import React from 'react';
import { CodeBlock, Pre as P } from '@fumadocs/base-ui/components/codeblock';

/// Library Modules
import { Language } from '@/website/language';

/// Package Modules
import { Block as _Block } from './block';
import { Tabs as _Tabs, List as _List, Tab as _Tab, Trigger as _Trigger } from './tabs';

/** Code Block Component. */
export interface Code extends Code.Props {}
export async function Code({ ref: _ref, native, ...props }: Code) {
    const children = <Code.Pre key="pre" children={props.children} />;
    if (native) return <CodeBlock {...props} children={children} />;
    else return <Code.Block {...props} children={children} />;
}

export namespace Code {
    //  TYPEDEFS  //

    export type Pre = React.HTMLAttributes<HTMLPreElement>;
    export const Pre = P;

    export type Block = _Block;
    export const Block = _Block;

    export type Tabs = _Tabs;
    export const Tabs = _Tabs;

    export type List = _List;
    export const List = _List;

    export type Trigger = _Trigger;
    export const Trigger = _Trigger;

    export type Tab = _Tab;
    export const Tab = _Tab;

    /** Code Block Properties. */
    export type Props = Block & { native?: boolean };

    export type Native = Block;
    export function Native(props: Native) {
        return <Code native {...props} />;
    }

    /** Handles Rendering Dynamic Code. */
    export type Dynamic = Language.Highlight.Options & { code: string; lang?: string };
    export async function Dynamic({ code, lang, ...options }: Dynamic) {
        const components: Language.Highlight.Options['components'] = { pre: Code.Pre };
        return Language.Highlight.render(code, { lang, components, ...options });
    }
}
