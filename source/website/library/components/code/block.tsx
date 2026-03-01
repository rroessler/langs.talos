'use client';

/// Vendor Modules
import clsx from 'clsx';
import React from 'react';
import { Check, Clipboard } from 'lucide-react';
import { useCopyButton } from '@fumadocs/base-ui/utils/use-copy-button';
import { buttonVariants } from '@fumadocs/base-ui/components/ui/button';

/// Package Modules
import { Context } from './tabs';

export interface Block extends Block.Props {}
export function Block({
    ref,
    icon,
    title,
    allowCopy = true,
    keepBackground = false,
    viewportProps = {},
    children,
    actions,
    ...props
}: Block) {
    // prepare the underlying context details now
    const inTab = React.use(Context) !== null;
    const areaRef = React.useRef<HTMLDivElement>(null);

    const copy: React.ReactNode = allowCopy ? <Block.Copy key="copy" containerRef={areaRef} /> : null;
    actions = React.Children.toArray(actions).concat(copy!); // update our actions now

    return (
        <figure
            ref={ref}
            dir="ltr"
            {...props}
            tabIndex={-1}
            className={clsx(
                inTab ? 'bg-fd-secondary -mx-px -mb-px last:rounded-b-xl' : 'my-4 bg-fd-card rounded-xl',
                keepBackground && 'bg-(--shiki-light-bg) dark:bg-(--shiki-dark-bg)',
                'shiki relative border shadow-sm not-prose overflow-hidden text-sm',
                props.className,
            )}
        >
            {title ? (
                <div className="flex text-fd-muted-foreground items-center gap-2 h-9.5 border-b px-4">
                    {typeof icon === 'string' ? (
                        <div
                            className="[&_svg]:size-3.5"
                            dangerouslySetInnerHTML={{
                                __html: icon,
                            }}
                        />
                    ) : (
                        icon
                    )}
                    <figcaption className="flex-1 truncate">{title}</figcaption>
                    {Block.Actions({ className: '-me-2', children: actions })}
                </div>
            ) : (
                Block.Actions({
                    className: 'absolute top-2 right-2 z-2 backdrop-blur-lg rounded-lg text-fd-muted-foreground',
                    children: actions,
                })
            )}
            <div
                ref={areaRef}
                {...viewportProps}
                role="region"
                tabIndex={0}
                className={clsx(
                    'text-[0.8125rem] py-3.5 overflow-auto max-h-[600px] fd-scroll-container focus-visible:outline-none focus-visible:ring-2 focus-visible:ring-inset focus-visible:ring-fd-ring',
                    viewportProps.className,
                )}
                style={
                    {
                        // space for toolbar
                        '--padding-right': !title ? 'calc(var(--spacing) * 8)' : undefined,
                        counterSet: props['data-line-numbers']
                            ? `line ${Number(props['data-line-numbers-start'] ?? 1) - 1}`
                            : undefined,
                        ...viewportProps.style,
                    } as object
                }
            >
                {children}
            </div>
        </figure>
    );
}

export namespace Block {
    //  TYPEDEFS  //

    /** Available Block Properties. */
    export interface Props extends React.ComponentProps<'figure'> {
        icon?: React.ReactNode;
        allowCopy?: boolean;
        actions?: React.ReactNode;

        keepBackground?: boolean;
        viewportProps?: React.HTMLAttributes<HTMLElement>;

        'data-line-numbers'?: boolean;
        'data-line-numbers-start'?: number;
    }

    //  PUBLIC METHODS  //

    /** Code Block Copy Button. */
    export type Copy = React.ComponentProps<'button'> & { containerRef: React.RefObject<HTMLElement | null> };
    export function Copy({ className, containerRef, ...props }: Copy) {
        // prepare the baseline details
        const [checked, onClick] = useCopyButton(() => {
            const pre = containerRef.current?.getElementsByTagName('pre').item(0);
            if (!pre) return;

            const clone = pre.cloneNode(true) as HTMLElement;
            clone.querySelectorAll('.nd-copy-ignore').forEach((node) => {
                node.replaceWith('\n');
            });

            void navigator.clipboard.writeText(clone.textContent ?? '');
        });

        return (
            <button
                type="button"
                data-checked={checked || undefined}
                className={clsx(
                    buttonVariants({
                        className: 'hover:text-fd-accent-foreground data-checked:text-fd-accent-foreground',
                        size: 'icon-xs',
                    }),
                    className,
                )}
                aria-label={checked ? 'Copied Text' : 'Copy Text'}
                onClick={onClick}
                {...props}
            >
                {checked ? <Check /> : <Clipboard />}
            </button>
        );
    }

    /** Handles containing actions. */
    export type Actions = React.HTMLAttributes<HTMLDivElement>;
    export function Actions(props: Actions) {
        return <div {...props} className={clsx('empty:hidden', props.className)} />;
    }
}
