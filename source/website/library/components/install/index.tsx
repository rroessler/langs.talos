/// Vendor Modules
import React from 'react';
import Link from 'next/link';
import { Eye } from 'lucide-react';
import { buttonVariants } from '@fumadocs/base-ui/components/ui/button';

/// Website Modules
import { Product } from '@/website/product';

/// Package Modules
import { Code } from '../code';
import { Version } from '../version';

/** Install Component Factory. */
export interface Install extends Install.Props {}
export function Install({ sleek = true, ...props }: Install) {
    // prepare the version text to be used now
    const version = !sleek && (
        <h2 key="version" {...props}>
            Install {Product.shortName} <Version />
        </h2>
    );

    // prepare the scripts to be shown now as well
    const scripts: Install.Script[] = [
        {
            href: '/install.sh',
            title: 'Linux / Darwin',
            language: 'bash',
            content: 'curl -fsSL https://talos.rroessler.io/install.sh | bash',
        },
        {
            title: 'Windows',
            href: '/install.ps1',
            language: 'powershell',
            content: 'powershell -c "irm https://talos.rroessler.io/install.ps1 | iex"',
        },
    ];

    // prepare the resulting tabs now
    const tabs = (
        <Code.Tabs key="tabs" defaultValue={scripts[0].title}>
            <Code.List>
                {scripts.map((script) => (
                    <Code.Trigger key={script.title} value={script.title} children={script.title} />
                ))}
            </Code.List>

            {scripts.map((props) => (
                <Code.Tab key={props.title} value={props.title} children={<Install.Script {...props} />} />
            ))}
        </Code.Tabs>
    );

    // prepare the output children now
    return <React.Fragment children={[version, tabs]} />;
}

export namespace Install {
    //  TYPEDEFS  //

    /** Install Component Properties. */
    export type Props = Omit<React.HTMLAttributes<HTMLElement>, 'children'> & { sleek?: boolean };

    /** Baseline script details. */
    export interface Script {
        href: string;
        title: string;
        content: string;
        language: string;
    }

    //  PUBLIC METHODS  //

    /** Shows the install actions. */
    export function Actions({ href }: Pick<Script, 'href'>) {
        const className = 'hover:text-fd-accent-foreground data-checked:text-fd-accent-foreground';
        const variant = buttonVariants({ className, size: 'icon-xs' }); // prepare variant
        return <Link href={href} target="_blank" type="button" className={variant} children={<Eye />} />;
    }

    /** Shows the install script. */
    export function Script({ href, content, language }: Script) {
        const actions = <Actions href={href} />;
        const dynamic = <Code.Dynamic lang={language} code={content} />;
        return <Code.Block children={dynamic} actions={actions} />;
    }
}
