/// Vendor Modules
import clsx from 'clsx';
import React from 'react';

/** Callout Component. */
export interface Callout extends Callout.Props {}
export function Callout({ children, type, title, className, style, ...props }: Callout) {
    // prepare the incoming class-name to be used
    className = clsx('flex gap-2 my-2 p-3 ps-1 text-sm text-fd-card-foreground', className);

    // update the current styling as well
    style = { '--callout-color': `var(--color-fd-${type ?? 'info'}, var(--color-fd-muted))`, ...style } as object;

    // construct the container of the callout now
    return (
        <div className={className} style={style} {...props}>
            <div role="none" className="w-0.5 bg-(--callout-color)/50 rounded-sm" />
            <div className="flex flex-col gap-2 min-w-0 flex-1">
                {title && <p className="font-medium my-0!">{title}</p>}
                <div className="text-fd-muted-foreground prose-no-margin empty:hidden" children={children} />
            </div>
        </div>
    );
}

export namespace Callout {
    //  TYPEDEFS  //

    /** Available Callout Types. */
    export type Type = 'info' | 'warning' | 'error' | 'success' | 'idea';

    /** Button Component Properties. */
    export interface Props extends Omit<React.ComponentProps<'div'>, 'title'> {
        type?: Type;
        title?: React.ReactNode;
    }
}
