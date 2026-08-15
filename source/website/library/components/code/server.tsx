/// Vendor Modules
import { Pre } from 'fumadocs-ui/components/codeblock';

/// Website Modules
import { cn } from '@/website/utilities';
import { Language } from '@/website/language';

/// Package Modules
import { Client } from './client';

/** Server Code-Block Component. */
export interface Server extends Server.Props {}
export async function Server({ code, block, icon, title, actions, ...options }: Server) {
    return Language.Highlight.render(code, {
        ...options,
        components: {
            pre: ({ children, className, ...props }) => {
                return (
                    <Client
                        {...props}
                        {...block}
                        icon={icon}
                        title={title}
                        actions={actions}
                        children={<Pre children={children} />}
                        className={cn('my-0', className, block?.className)}
                    />
                );
            },
        },
    });
}

export namespace Server {
    //  TYPEDEFS  //

    /** Server Code-Block Properties. */
    export interface Props extends Language.Highlight.Options {
        code: string;
        block?: Client;
        title?: string;
        icon?: React.ReactNode;
        actions?: Client['actions'];
    }
}
