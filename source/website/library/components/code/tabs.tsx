'use client';

/// Vendor Modules
import clsx from 'clsx';
import React from 'react';
import { mergeRefs } from '@fumadocs/ui/merge-refs';
import * as Unstyled from '@fumadocs/base-ui/components/ui/tabs';

/** Available Tabs Context. */
export const Context = React.createContext<{
    containerRef: React.RefObject<HTMLDivElement | null>;
    nested: boolean;
} | null>(null);

/** Code Block Tabs Element. */
export type Tabs = React.ComponentProps<typeof Unstyled.Tabs>;
export function Tabs({ ref, ...props }: Tabs) {
    const containerRef = React.useRef<HTMLDivElement>(null);
    const nested = React.use(Context) !== null;

    return (
        <Unstyled.Tabs
            {...props}
            ref={mergeRefs(containerRef, ref)}
            className={clsx('bg-fd-card rounded-xl border', !nested && 'my-4', props.className)}
        >
            <Context value={React.useMemo(() => ({ containerRef, nested }), [nested])}>{props.children}</Context>
        </Unstyled.Tabs>
    );
}

/** Code Block Tabs List. */
export type List = React.ComponentProps<typeof Unstyled.TabsList>;
export function List(props: List) {
    return (
        <Unstyled.TabsList
            {...props}
            className={clsx('flex flex-row px-2 overflow-x-auto text-fd-muted-foreground', props.className)}
        >
            {props.children}
        </Unstyled.TabsList>
    );
}

/** Code Block Tabs Trigger. */
export type Trigger = React.ComponentProps<typeof Unstyled.TabsTrigger>;
export function Trigger({ children, ...props }: Trigger) {
    return (
        <Unstyled.TabsTrigger
            {...props}
            className={clsx(
                'relative group inline-flex text-sm font-medium text-nowrap items-center transition-colors gap-2 px-2 py-1.5 hover:text-fd-accent-foreground data-active:text-fd-primary [&_svg]:size-3.5',
                props.className,
            )}
        >
            <div className="absolute inset-x-2 bottom-0 h-px group-data-active:bg-fd-primary" />
            {children}
        </Unstyled.TabsTrigger>
    );
}

/** Baseline Code-Block Tab. */
export type Tab = React.ComponentProps<typeof Unstyled.TabsContent>;
export function Tab(props: Tab) {
    return <Unstyled.TabsContent keepMounted {...props} />;
}
