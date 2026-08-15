/// Vendor Modules
import Link, { type LinkProps } from 'next/link';

/// Website Modules
import { cn } from '@/website/utilities';

/** Anchor Component. */
export interface Anchor extends Anchor.Props {}
export function Anchor({ href = '#', sleek, className, component, ...props }: Anchor) {
    const external = !href.startsWith('/'); // check if external at all
    const target = external && !href.includes('#') ? '_blank' : undefined;

    const base = !sleek && 'text-brand decoration-brand-200 decoration-1 hover:underline hover:text-brand-200';
    className = cn(className, 'no-underline', base); // prepare the class-name details to be used now

    // use the component if given at all
    if (typeof component === 'function') return component({ href, className, target, ...props });
    else return <Link href={href} className={className} target={target} {...props} />;
}

export namespace Anchor {
    //  TYPEDEFS  //

    /** Button Component Properties. */
    export type Props = React.PropsWithChildren<
        React.JSX.IntrinsicElements['a'] &
            Omit<LinkProps, 'href'> & {
                sleek?: boolean;
                href?: LinkProps['href'];
                component?: React.FC<React.ComponentProps<'a'>>;
            }
    >;

    /** Super Anchor Components. */
    export type Super = Omit<Props, 'href'> & { index: string };
    export function Super({ index, ...props }: Super) {
        const id = `mark-${index}`;
        const href = `#note-${index}`;
        const anchor = <Anchor href={href} children={`⚔️${index}`} {...props} />;
        return <sup id={id} children={anchor} />;
    }

    /** Footnote Anchor Components. */
    export type Footnote = Super;
    export function Footnote({ index, ...props }: Footnote) {
        const id = `note-${index}`;
        const href = `#mark-${index}`;
        return <Anchor id={id} href={href} children={`⚔️&nbsp;${index}`} {...props} />;
    }
}
