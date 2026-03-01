/// Vendor Modules
import React from 'react';
import { clsx } from 'clsx';

/// Package Modules
import { Icon } from '../icon';
import { Anchor } from '../anchor';
import { Variant } from '../intrinsic';

export type Button = Button.Props | Button.Anchor;
export function Button(props: Button.Props): React.ReactNode;
export function Button(props: Button.Anchor): React.ReactNode;
export function Button({ variant = 'primary', href, className, icon, ...props }: any): React.ReactNode {
    // prepare the potential variants to be used now
    const classes = Variant(variant, {
        primary: 'bg-brand text-brand-foreground! hover:bg-brand-200',
        secondary: 'bg-fd-secondary text-fd-secondary-foreground! hover:bg-fd-accent',
    });

    // update the children if they are empty at all as necessary
    if (React.Children.count(props.children) === 0) props.children = props.title;

    const count = React.Children.count(props.children); // prepare the icon
    const prefix = <Button.Prefix key="prefix" icon={icon} count={count} />;
    props.children = [prefix, props.children]; // finally update the children

    // prepare the class-name to be used no
    className = clsx(
        className,
        classes,
        'inline-flex justify-center rounded font-medium px-2 py-1 border transition-colors',
    );

    // construct the resulting button now
    if (!href?.length) return <button className={className} {...props} />;
    else return <Anchor sleek href={href} className={className} {...props} />;
}

export namespace Button {
    //  TYPEDEFS  //

    /** Button Component Properties. */
    export type Common = Prefix & { variant?: Variant };
    export type Props = React.JSX.IntrinsicElements['button'] & Common;
    export type Anchor = React.JSX.IntrinsicElements['a'] & Common & { href?: string };

    //  PUBLIC METHODS  //

    export type Prefix = { icon?: Icon };
    export function Prefix({ icon, count = 0 }: Prefix & { count?: number }) {
        // ignore if there is no valid icon to be prefixed
        if (typeof icon === 'undefined') return null;

        // prepare the class-name to be used now
        const className = clsx('flex items-center justify-center', count && 'me-2');

        // construct the necessary prefix now
        return <span className={className}>{Icon.Dynamic(icon as any)}</span>;
    }
}
